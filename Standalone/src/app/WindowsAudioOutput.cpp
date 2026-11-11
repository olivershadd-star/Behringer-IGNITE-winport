// SPDX-License-Identifier: AGPL-3.0-or-later
#include "WindowsAudioOutput.h"
#include <algorithm>
#include <array>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <thread>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <mmsystem.h>
#include <avrt.h>
struct WindowsAudioOutput::Impl {
    static constexpr int frames=512,buffers=4,rate=48000;
    Prepare prepare;
    Render render;
    std::atomic<bool> alive{false},starting{false},playing{false};
    std::atomic<unsigned> failure{0};
    std::thread worker;
    HWAVEOUT device=nullptr;
    HANDLE event=nullptr;
    std::wstring name;
    std::array<WAVEHDR,buffers> headers{};
    std::array<std::array<int16_t,frames*2>,buffers> pcm{};
    std::array<bool,buffers> prepared{};
    std::array<float,frames> left{},right{};
    bool check(MMRESULT result){if(result==MMSYSERR_NOERROR)return true;failure.store(result);alive.store(false);return false;}
    void fill(int index){
        render(left.data(),right.data(),frames);
        for(int i=0;i<frames;++i){
            const float l=std::isfinite(left[static_cast<size_t>(i)])?std::clamp(left[static_cast<size_t>(i)],-1.f,1.f):0.f;
            const float r=std::isfinite(right[static_cast<size_t>(i)])?std::clamp(right[static_cast<size_t>(i)],-1.f,1.f):0.f;
            pcm[static_cast<size_t>(index)][static_cast<size_t>(i*2)]=static_cast<int16_t>(std::lround(l*32767));
            pcm[static_cast<size_t>(index)][static_cast<size_t>(i*2+1)]=static_cast<int16_t>(std::lround(r*32767));
        }
    }
    void run(){
        DWORD taskIndex=0;const auto task=AvSetMmThreadCharacteristicsW(L"Pro Audio",&taskIndex);
        if(task)AvSetMmThreadPriority(task,AVRT_PRIORITY_HIGH);
        prepare(rate);
        check(waveOutPause(device));
        for(int i=0;i<buffers&&alive.load();++i){
            auto& h=headers[static_cast<size_t>(i)];h={};h.lpData=reinterpret_cast<char*>(pcm[static_cast<size_t>(i)].data());h.dwBufferLength=static_cast<DWORD>(sizeof(pcm[static_cast<size_t>(i)]));
            if(!check(waveOutPrepareHeader(device,&h,sizeof(h))))break;
            prepared[static_cast<size_t>(i)]=true;fill(i);check(waveOutWrite(device,&h,sizeof(h)));
        }
        if(alive.load())check(waveOutRestart(device));
        playing.store(alive.load());starting.store(false);
        int next=0;
        while(alive.load()){
            // Completed buffers must be recycled in their original chronological order.
            while(alive.load()&&(headers[static_cast<size_t>(next)].dwFlags&WHDR_DONE)!=0){
                fill(next);if(!check(waveOutWrite(device,&headers[static_cast<size_t>(next)],sizeof(WAVEHDR))))break;
                next=(next+1)%buffers;
            }
            if(alive.load())WaitForSingleObject(event,50);
        }
        waveOutReset(device);
        for(int i=0;i<buffers;++i)if(prepared[static_cast<size_t>(i)])waveOutUnprepareHeader(device,&headers[static_cast<size_t>(i)],sizeof(WAVEHDR));
        waveOutClose(device);device=nullptr;CloseHandle(event);event=nullptr;
        if(task)AvRevertMmThreadCharacteristics(task);
        playing.store(false);starting.store(false);
    }
};
WindowsAudioOutput::WindowsAudioOutput():impl(std::make_unique<Impl>()){}
WindowsAudioOutput::~WindowsAudioOutput(){stop();}
bool WindowsAudioOutput::start(Prepare prepare,Render render,unsigned id){
    stop();impl->failure.store(0);impl->prepared.fill(false);impl->prepare=std::move(prepare);impl->render=std::move(render);
    WAVEOUTCAPSW caps{};impl->name=waveOutGetDevCapsW(id,&caps,sizeof(caps))==MMSYSERR_NOERROR?caps.szPname:L"Sortie Windows par defaut";
    impl->event=CreateEventW(nullptr,FALSE,FALSE,nullptr);
    if(!impl->event){impl->failure.store(MMSYSERR_NOMEM);return false;}
    WAVEFORMATEX fmt{};fmt.wFormatTag=WAVE_FORMAT_PCM;fmt.nChannels=2;fmt.nSamplesPerSec=Impl::rate;fmt.wBitsPerSample=16;fmt.nBlockAlign=4;fmt.nAvgBytesPerSec=Impl::rate*4;
    const auto result=waveOutOpen(&impl->device,id,&fmt,reinterpret_cast<DWORD_PTR>(impl->event),0,CALLBACK_EVENT);
    if(result!=MMSYSERR_NOERROR){impl->failure.store(result);CloseHandle(impl->event);impl->event=nullptr;return false;}
    impl->alive.store(true);impl->starting.store(true);
    impl->worker=std::thread([this]{impl->run();});return true;
}
void WindowsAudioOutput::stop(){impl->alive.store(false);if(impl->worker.joinable())impl->worker.join();impl->playing.store(false);impl->starting.store(false);}
bool WindowsAudioOutput::active() const{return impl->failure.load()==0&&(impl->playing.load()||impl->starting.load());}
bool WindowsAudioOutput::running() const{return impl->playing.load();}
unsigned WindowsAudioOutput::error() const{return impl->failure.load();}
std::wstring WindowsAudioOutput::errorText() const{wchar_t text[256]{};const auto code=error();if(code==0)return {};if(waveOutGetErrorTextW(code,text,256)!=MMSYSERR_NOERROR)return L"Erreur de sortie audio Windows";return text;}
std::wstring WindowsAudioOutput::deviceName() const{return impl->name;}
std::vector<std::pair<unsigned,std::wstring>> WindowsAudioOutput::devices(){std::vector<std::pair<unsigned,std::wstring>> result;for(UINT i=0;i<waveOutGetNumDevs();++i){WAVEOUTCAPSW caps{};if(waveOutGetDevCapsW(i,&caps,sizeof(caps))==MMSYSERR_NOERROR)result.emplace_back(i,caps.szPname);}return result;}
#else
struct WindowsAudioOutput::Impl{};
WindowsAudioOutput::WindowsAudioOutput():impl(std::make_unique<Impl>()){}
WindowsAudioOutput::~WindowsAudioOutput()=default;
bool WindowsAudioOutput::start(Prepare,Render,unsigned){return false;}
void WindowsAudioOutput::stop(){}
bool WindowsAudioOutput::active() const{return false;}
bool WindowsAudioOutput::running() const{return false;}
unsigned WindowsAudioOutput::error() const{return 1;}
std::wstring WindowsAudioOutput::errorText() const{return L"Sortie Windows uniquement";}
std::wstring WindowsAudioOutput::deviceName() const{return {};}
std::vector<std::pair<unsigned,std::wstring>> WindowsAudioOutput::devices(){return {};}
#endif
