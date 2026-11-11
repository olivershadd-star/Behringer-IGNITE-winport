// SPDX-License-Identifier: AGPL-3.0-or-later
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include "Pattern.h"
#include "SequenceManager.h"
#include "PatternPlayback.h"
#include "TrackEffects.h"
#include "EmbeddedBank.h"
#include "WindowsAudioOutput.h"
#include "WindowsInput.h"
#include <mutex>
#include <atomic>
#include <cmath>

static juce::String utf8(const char* text) { return juce::String::fromUTF8(text); }

class Editor final : public juce::Component,private juce::Timer,private Ignite::SequenceHost {
public:
    explicit Editor(bool test,bool startup):pattern(0,"Pattern 1",0,Ignite::TimeBase::Base_16,1,false,nullptr),sequence(*this),selfTest(test),startupCheck(startup) {
        setSize(1040,680);
        for(auto* button:{&play,&stop,&preview,&demo,&clear,&retry})addAndMakeVisible(button);
        play.setButtonText("Lecture");stop.setButtonText("Stop");preview.setButtonText(utf8("Écouter le son"));demo.setButtonText(utf8("Charger une démo"));clear.setButtonText("Vider le pattern");retry.setButtonText("Relancer l'audio");
        addAndMakeVisible(instruments);instruments.setTextWhenNothingSelected(utf8("Chargement des sons…"));
        addAndMakeVisible(status);status.setColour(juce::Label::textColourId,juce::Colour(0xffb9cad8));
        slider(tempo,tempoLabel,"Tempo",40,240,1,120);
        slider(velocity,velocityLabel,"Vélocité",1,127,1,100);velocity.setTooltip(utf8("Vélocité des nouvelles notes ajoutées à la grille"));
        slider(cutoff,cutoffLabel,"Filtre · Hz",20,20000,1,20000);cutoff.setSkewFactorFromMidPoint(1000);
        slider(resonance,resonanceLabel,"Résonance · %",0,90,1,10);
        slider(reverb,reverbLabel,"Réverbération · %",0,100,1,0);
        slider(volume,volumeLabel,"Volume · %",0,100,1,80);
        for(int row=0;row<8;++row) {
            addAndMakeVisible(rows[row]);
            for(int step=0;step<16;++step) {
                auto& b=grid[row][step];addAndMakeVisible(b);b.setButtonText(juce::String(step+1));
                b.setClickingTogglesState(false);b.onClick=[this,row,step]{edit(row,step);};
            }
        }
        const auto bank=getEmbeddedBank();loaded=audio.loadBank(bank.data,bank.size);
        if(loaded) {
            instruments.addSectionHeading("Instruments et kits internes");
            int id=1;for(const auto& preset:audio.presets()) instruments.addItem((preset.bank==128?utf8("Batterie · "):"")+juce::String::fromUTF8(preset.name.c_str()),id++);
            instruments.setSelectedId(1,juce::dontSendNotification);
            // GeneralUser catalogue order is program order; choose piano.
            selectedBank=0;selectedProgram=0;
            effects.prepare(48000);audio.setEffects(&effects);
        }
        instruments.onChange=[this]{chooseSound();};
        play.onClick=[this]{std::lock_guard<std::mutex> lock(audioMutex);if(audio.play())running.store(true);};
        stop.onClick=[this]{std::lock_guard<std::mutex> lock(audioMutex);audio.stop();running.store(false);cursor.store(-1);};
        preview.onClick=[this]{std::lock_guard<std::mutex> lock(audioMutex);audio.audition(selectedBank==128?36:60);};
        demo.onClick=[this]{loadDemo();};clear.onClick=[this]{pattern.clearPattern();publish();};retry.onClick=[this]{startDevice();};
        tempo.onValueChange=[this]{publish();};
        cutoff.onValueChange=[this]{effect(InternalAudioCC::FILTER_CUTOFF,cutoff.getValue());};
        resonance.onValueChange=[this]{effect(InternalAudioCC::RESONANCE,resonance.getValue());};
        reverb.onValueChange=[this]{std::lock_guard<std::mutex> lock(audioMutex);effects.setReverbMix(static_cast<float>(reverb.getValue()*0.01));};
        volume.onValueChange=[this]{effect(InternalAudioCC::VOLUME,volume.getValue());};
        if(loaded)loadDemo();
        if(!selfTest)startDevice();else {deviceReady=true;status.setText(utf8("Test hors ligne du cœur original — aucun périphérique audio simulé comme disponible"),juce::dontSendNotification);}
        updateEnabled();startTimerHz(50);
    }
    ~Editor() override {stopTimer();output.stop();audio.setEffects(nullptr);}
    void paint(juce::Graphics& g) override {
        g.fillAll(juce::Colour(0xff141c27));g.setColour(juce::Colour(0xff55dcc0));g.setFont(28);g.drawText("IGNITE",24,12,200,35,juce::Justification::left);
        g.setFont(15);g.setColour(juce::Colour(0xffc1ccd9));g.drawText(utf8("Un instrument · Pattern de 16 pas"),220,15,500,30,juce::Justification::left);
        g.setColour(juce::Colour(0xff1d2938));g.fillRoundedRectangle(18,144,getWidth()-36.0f,340,10);
        g.setColour(juce::Colour(0xffb9cad8));g.setFont(14);g.drawText("Clique une case pour ajouter ou retirer une note. Plusieurs notes peuvent partager un pas.",28,145,getWidth()-56,28,juce::Justification::left);
        const int x=150,w=(getWidth()-174)/16;
        if(cursor.load()>=0){g.setColour(juce::Colour(0xff55dcc0));g.fillRect(x+(cursor.load()%16)*w,178,w-3,3);}
    }
    void resized() override {
        instruments.setBounds(24,57,340,30);preview.setBounds(374,57,150,30);tempoLabel.setBounds(548,44,90,18);tempo.setBounds(540,62,190,26);
        play.setBounds(24,101,110,32);stop.setBounds(144,101,100,32);demo.setBounds(260,101,170,32);clear.setBounds(440,101,170,32);
        velocityLabel.setBounds(650,96,90,20);velocity.setBounds(735,101,250,28);
        const int w=(getWidth()-174)/16;
        for(int row=0;row<8;++row){rows[row].setBounds(28,187+row*35,115,30);for(int step=0;step<16;++step)grid[row][step].setBounds(150+step*w,187+row*35,w-4,30);}
        juce::Slider* controls[]={&cutoff,&resonance,&reverb,&volume};juce::Label* labels[]={&cutoffLabel,&resonanceLabel,&reverbLabel,&volumeLabel};
        const int width=(getWidth()-48)/4;
        for(int i=0;i<4;++i){labels[i]->setBounds(24+i*width,500,width-12,22);controls[i]->setBounds(24+i*width,526,width-12,30);}
        status.setBounds(24,575,getWidth()-220,64);retry.setBounds(getWidth()-190,588,166,30);
    }
private:
    Ignite::Pattern* findPattern(const std::string& name) override {return pattern.getName()==name?&pattern:nullptr;}
    void slider(juce::Slider& s,juce::Label& label,const char* name,double low,double high,double interval,double value) {
        addAndMakeVisible(s);addAndMakeVisible(label);label.setText(juce::String::fromUTF8(name),juce::dontSendNotification);
        s.setSliderStyle(juce::Slider::LinearHorizontal);s.setTextBoxStyle(juce::Slider::TextBoxRight,false,64,24);s.setRange(low,high,interval);s.setValue(value,juce::dontSendNotification);
    }
    int pitch(int row) const {static const int drums[]={36,38,42,46,49,51,45,47};static const int keys[]={72,71,69,67,65,64,62,60};return selectedBank==128?drums[row]:keys[row];}
    bool hasNote(int row,int step) const {
        const auto notes=pattern._patternData->barList.find(0)->second._BarData->stepList.find(step)->second.getNodeList();
        return std::any_of(notes.begin(),notes.end(),[&](const auto& n){return n.note==pitch(row);});
    }
    void addNote(int step,int note,int vel) {
        Ignite::ClientPatternNodeData n{};n.nodeId=note;n.note=note;n.velocity=vel;n.lenInTicks=6;n.onState=true;pattern.PatternAddNodeData(0,step,n);
    }
    void edit(int row,int step) {
        if(hasNote(row,step))pattern.PatternDelNodeData(0,step,pitch(row));else addNote(step,pitch(row),static_cast<int>(velocity.getValue()));
        publish();
    }
    void refreshGrid() {
        static const char* drumNames[]={"Kick","Snare","Hi-hat fermé","Hi-hat ouvert","Crash","Ride","Tom grave","Tom médium"};
        for(int row=0;row<8;++row){rows[row].setText(selectedBank==128?juce::String::fromUTF8(drumNames[row]):juce::MidiMessage::getMidiNoteName(pitch(row),true,true,4),juce::dontSendNotification);
            for(int step=0;step<16;++step)grid[row][step].setColour(juce::TextButton::buttonColourId,hasNote(row,step)?juce::Colour(0xff167d70):juce::Colour(step%4==0?0xff34465d:0xff253448));}
        repaint();
    }
    void publish() {
        if(!loaded)return;
        sequence.updateTrackPattern(&pattern);
        try {
            auto plan=Ignite::compilePatternPlayback(sequence,pattern);
            std::lock_guard<std::mutex> lock(audioMutex);const bool resume=audio.isPlaying();audio.setPattern(std::move(plan),tempo.getValue());if(resume)audio.play();
        }catch(const std::exception& e){status.setText(e.what(),juce::dontSendNotification);}
        refreshGrid();
    }
    void loadDemo() {
        pattern.clearPattern();
        if(selectedBank==128){for(int step=0;step<16;step+=4)addNote(step,36,110);addNote(4,38,100);addNote(12,38,100);for(int step=0;step<16;step+=2)addNote(step,42,75);}
        else {const int notes[]={60,64,67,72};for(int i=0;i<4;++i){addNote(i*4,notes[i],100);addNote(i*4,notes[i]+(i==3?-12:0),90);}}
        publish();
    }
    void chooseSound() {
        const auto index=instruments.getSelectedId()-1;if(index<0||index>=static_cast<int>(audio.presets().size()))return;
        const auto preset=audio.presets()[static_cast<size_t>(index)];selectedBank=preset.bank;selectedProgram=preset.program;
        {std::lock_guard<std::mutex> lock(audioMutex);audio.setPreset(selectedBank,selectedProgram);audio.audition(selectedBank==128?36:60);}
        refreshGrid();
    }
    void effect(InternalAudioCC parameter,double value){std::lock_guard<std::mutex> lock(audioMutex);effects.setInternalAudioEffects(static_cast<uint8_t>(parameter),static_cast<float>(value),false);}
    void startDevice() {
        output.stop();deviceReady=false;
        if(!loaded){status.setText(utf8("Banque interne absente ou illisible : les instruments n'ont pas été chargés."),juce::dontSendNotification);updateEnabled();return;}
        deviceReady=output.start([this,cutoffValue=cutoff.getValue(),resonanceValue=resonance.getValue(),volumeValue=volume.getValue(),reverbValue=reverb.getValue()](double rate){std::lock_guard<std::mutex> lock(audioMutex);audio.prepare(rate);effects.prepare(rate);effects.setInternalAudioEffects(static_cast<uint8_t>(InternalAudioCC::FILTER_CUTOFF),static_cast<float>(cutoffValue),false);effects.setInternalAudioEffects(static_cast<uint8_t>(InternalAudioCC::RESONANCE),static_cast<float>(resonanceValue),false);effects.setInternalAudioEffects(static_cast<uint8_t>(InternalAudioCC::VOLUME),static_cast<float>(volumeValue),false);effects.setReverbMix(static_cast<float>(reverbValue*0.01));running.store(false);},[this](float* l,float* r,int count){render(l,r,count);});
        status.setText(deviceReady?utf8("Audio Windows en cours d'ouverture…"):"Audio Windows indisponible : "+juce::String(output.errorText().c_str()),juce::dontSendNotification);updateEnabled();
    }
    void updateEnabled(){play.setEnabled(loaded&&deviceReady);preview.setEnabled(loaded&&deviceReady);instruments.setEnabled(loaded);}
    void render(float* l,float* r,int count) {
        std::unique_lock<std::mutex> lock(audioMutex,std::try_to_lock);
        if(!lock.owns_lock()){std::fill_n(l,count,0.0f);std::fill_n(r,count,0.0f);return;}
        audio.render(l,r,count);cursor.store(audio.playStep());running.store(audio.isPlaying());
        float peak=0;for(int i=0;i<count;++i)peak=std::max(peak,std::abs(l[i]));meter.store(peak);
    }
    bool click(juce::Component& component){const auto p=component.getScreenBounds().getCentre();return clickWindowsPoint(p.x,p.y);}
    void finishTest(bool ok,const juce::String& reason) {
        juce::File::getCurrentWorkingDirectory().getChildFile("original-desktop-test.txt").replaceWithText((ok?"PASS: ":"FAIL: ")+reason+"\n");
        auto image=createComponentSnapshot(getLocalBounds());juce::PNGImageFormat png;auto stream=juce::File::getCurrentWorkingDirectory().getChildFile("original-desktop.png").createOutputStream();if(stream)png.writeImageToStream(image,*stream);
        if(!recordL.empty()) {juce::AudioBuffer<float> buffer(2,static_cast<int>(recordL.size()));buffer.copyFrom(0,0,recordL.data(),buffer.getNumSamples());buffer.copyFrom(1,0,recordR.data(),buffer.getNumSamples());juce::WavAudioFormat format;
            auto file=juce::File::getCurrentWorkingDirectory().getChildFile("original-desktop-audio.wav");file.deleteFile();auto out=file.createOutputStream();if(out){std::unique_ptr<juce::AudioFormatWriter> writer(format.createWriterFor(out.release(),48000,2,16,{},0));if(writer)writer->writeFromAudioSampleBuffer(buffer,0,buffer.getNumSamples());}}
        juce::JUCEApplication::getInstance()->setApplicationReturnValue(ok?0:1);juce::JUCEApplication::getInstance()->quit();
    }
    void timerCallback() override {
        if(selfTest) {
            ++testTick;if(testTick<10)return;
            if(testTick==10){if(!loaded||instruments.getNumItems()<128||!click(play)){finishTest(false,"Bank/catalog/Play input");return;}}
            if(testTick>=11&&testTick<=92){float l[1024]{},r[1024]{};render(l,r,1024);testPeak=std::max(testPeak,meter.load());recordL.insert(recordL.end(),l,l+1024);recordR.insert(recordR.end(),r,r+1024);}
            if(testTick==60){if(!running.load()||testPeak<0.0001f||cursor.load()<1){finishTest(false,"Play did not advance original pattern into audible PCM");return;}click(stop);}
            if(testTick==61){if(running.load()||meter.load()!=0){finishTest(false,"Stop ignored or left sounding notes");return;}click(grid[0][1]);}
            if(testTick==62){if(!hasNote(0,1)){finishTest(false,"Grid did not edit original Pattern");return;}testPeak=0;click(preview);}
            if(testTick==70){
                if(testPeak<0.0001f){finishTest(false,"Instrument audition is silent");return;}
                int id=1;for(const auto& preset:audio.presets()){if(preset.bank==128){instruments.setSelectedId(id,juce::sendNotificationSync);break;}++id;}
                if(selectedBank!=128){finishTest(false,"Drum kit cannot be selected");return;}click(demo);testPeak=0;
            }
            if(testTick==71){if(!hasNote(0,0)||!hasNote(1,4)){finishTest(false,"Drum demo did not populate original Pattern");return;}click(play);}
            if(testTick==90){if(!running.load()||testPeak<0.0001f){finishTest(false,"Drum pattern is silent");return;}click(stop);}
            if(testTick==91){if(running.load()||meter.load()!=0){finishTest(false,"Drum Stop ignored");return;}click(clear);}
            if(testTick==92){if(hasNote(0,0)){finishTest(false,"Clear ignored");return;}loadDemo();}
            if(testTick==93){finishTest(true,"Embedded bank, instrument selection/audition, mouse Play/Stop/grid/demo/clear, original Pattern/SequenceManager and original Track effects -> audible piano and drum PCM. Physical sound device not tested.");return;}
        } else {
            if(output.running()) {deviceReady=true;status.setText("Sortie : "+juce::String(output.deviceName().c_str())+utf8("  ·  ")+(running.load()?"Lecture du pattern":utf8("Prêt — choisis un son, puis Lecture")),juce::dontSendNotification);}
            else if(output.error()!=0){deviceReady=false;status.setText("Audio Windows indisponible : "+juce::String(output.errorText().c_str()),juce::dontSendNotification);}
            updateEnabled();
            if(startupCheck&&++testTick==75){juce::File::getCurrentWorkingDirectory().getChildFile("original-desktop-startup.txt").replaceWithText(output.running()?"AUDIO_RUNNING\n":"AUDIO_UNAVAILABLE_REPORTED\n"+status.getText());juce::JUCEApplication::getInstance()->quit();}
        }
        repaint();
    }
    Ignite::Pattern pattern;Ignite::SequenceManager sequence;
    TrackEffects effects;Ignite::PatternPlayback audio;std::mutex audioMutex;WindowsAudioOutput output;
    juce::ComboBox instruments;juce::TextButton play,stop,preview,demo,clear,retry,grid[8][16];juce::Label rows[8],status;
    juce::Slider tempo,velocity,cutoff,resonance,reverb,volume;juce::Label tempoLabel,velocityLabel,cutoffLabel,resonanceLabel,reverbLabel,volumeLabel;
    std::atomic<int> cursor{-1};std::atomic<bool> running{false};std::atomic<float> meter{0};
    bool loaded=false,deviceReady=false,selfTest=false,startupCheck=false;int selectedBank=0,selectedProgram=0,testTick=0;float testPeak=0;
    std::vector<float> recordL,recordR;
};
class App final : public juce::JUCEApplication {
public:
    const juce::String getApplicationName() override{return "IGNITE Core Desktop";}
    const juce::String getApplicationVersion() override{return "0.2.0";}
    void initialise(const juce::String& args) override{window=std::make_unique<Window>(args.contains("--ui-self-test"),args.contains("--startup-check"));}
    void shutdown() override{window.reset();}
    void systemRequestedQuit() override{quit();}
private:
    class Window final : public juce::DocumentWindow {
    public:
        Window(bool test,bool startup):DocumentWindow(utf8("IGNITE — Pattern"),juce::Colour(0xff141c27),allButtons){setUsingNativeTitleBar(true);setContentOwned(new Editor(test,startup),true);setResizable(true,false);setResizeLimits(1000,680,1600,1000);centreWithSize(1040,680);setVisible(true);toFront(true);}
        void closeButtonPressed() override{juce::JUCEApplication::getInstance()->systemRequestedQuit();}
    };
    std::unique_ptr<Window> window;
};
START_JUCE_APPLICATION(App)
