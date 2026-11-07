// Copyright 2021 MUSIC Group Services EU GmbH
#ifdef WINDOWS_PLATFORM
#include "CSoundEngine.h"
//#include "MLog.h"
#include "minisdl_audio.h"
//#include "SwingConstants.h"
#include <iostream>
using namespace Ignite;
//#include "SoundFonts.c"
static CSoundEngine* _player = nullptr;
CSoundEngine::CSoundEngine()
    : CSoundFontEngine(AudioMode::StereoInterleaved, 48000, 32, 0)
{

    SDL_AudioSpec OutputAudioSpec;
    OutputAudioSpec.freq = 48000;
    OutputAudioSpec.format = AUDIO_S32;
    OutputAudioSpec.channels = 2;
    OutputAudioSpec.samples = 2048 / 2;
    OutputAudioSpec.callback = CSoundEngine::AudioCallback;

    // Initialize the audio system
    if (SDL_AudioInit(NULL) < 0) {
        log_error("Could not initialize audio hardware or driver\n");
    }
    log_debug("Construct");
    initEngineFromFile("AWE32_1MB.sf2");

    // Request the desired audio output format
    if (SDL_OpenAudio(&OutputAudioSpec, NULL) < 0) {
        log_error("Could not open the audio hardware or the desired audio output format\n");
    }
    _player = this;
    // Start the actual audio playback here
    // The audio thread will begin to call our AudioCallback function
    SDL_PauseAudio(0);
}

void CSoundEngine::AudioCallback(void* data, uint8_t* stream, int len)
{
    int SampleCount = (len / (2 * sizeof(short)));

    _player->processBlock((short*)stream, SampleCount);
}

void CSoundEngine::startAudio(void)
{
    SDL_PauseAudio(0);
}

void CSoundEngine::stopAudio(void)
{
    SDL_PauseAudio(1);
}
#endif
