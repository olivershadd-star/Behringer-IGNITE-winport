// Copyright 2021 MUSIC Group Services EU GmbH
#ifdef WINDOWS_PLATFORM
#pragma once

#include "CSoundFontEngine.h"
//#include "CThread.h"
#include <stdint.h>
namespace Ignite {

class CSoundEngine : public CSoundFontEngine {
public:
    static CSoundEngine& getInstance()
    {
        static CSoundEngine instance;
        return instance;
    }
    void startAudio(void);
    void stopAudio(void);

private:
    CSoundEngine();
    ~CSoundEngine() = default;
#ifdef BUILD_SIMULATOR
    static void AudioCallback(void* data, uint8_t* stream, int len);
#else
    void process(void);
    CThread _audioThread;
#endif
    bool _running = false;
};
}
#endif //WINDOWS_PLATFORM
