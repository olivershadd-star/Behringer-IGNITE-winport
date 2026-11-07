// Copyright 2021 MUSIC Group Services EU GmbH
#pragma once
#define TSF_IMPLEMENTATION
#define TSF_STATIC
#if (!defined(_WIN32) && !defined(UNIX))
#define TSF_NO_STDIO
#endif
#include "EnumTypes.h"
#ifdef WINDOWS_PLATFORM
//#include "tsf.h"
#endif
#include <stdint.h>

namespace Ignite {

	struct AudioSpecs {
	};

	class CSoundFontEngine {
	public:
		CSoundFontEngine (AudioMode mode, uint32_t samplerate, uint32_t numvoices, float gain);
		~CSoundFontEngine ();
		CSoundFontEngine (const CSoundFontEngine&) = delete;
		CSoundFontEngine& operator=(const CSoundFontEngine&) = delete;
		CSoundFontEngine (CSoundFontEngine&&) = delete;
		CSoundFontEngine& operator=(CSoundFontEngine&&) = delete;
		void setGain (float gain);
		float getGain (void) const;
		uint32_t getProgramCount (void) const;
		uint8_t getChannelProgram (uint8_t channel) const;
		const char* getChannelProgramName (uint8_t channel) const;
		void channelNoteOn (uint8_t pitch, uint8_t velocity, uint8_t channel);
		void channelNoteOff (uint8_t pitch, uint8_t channel);
		void presetNoteOn (uint8_t preset, uint8_t pitch, uint8_t vel);
		void presetNoteOff (uint8_t preset, uint8_t pitch);
		void noteOffAll (void);
		void programChange (uint8_t program, uint8_t channel);
		void controlChange (uint8_t control, uint8_t value, uint8_t channel);
		void pitchBend (int16_t value, uint8_t channel);
		void processBlock (short* buffer, uint32_t samples);
		void processBlock (int32_t* buffer, uint32_t samples);
		void initEngineFromFile (const char* soundfontpath);

	private:
#ifdef WINDOWS_PLATFORM
		void setupAudioSpecs (void);
		tsf* _tsf = nullptr;
#endif
		AudioMode _mode;
		uint32_t _samplerate;
		uint32_t _numvoices;
		float _gain;
	};
}
