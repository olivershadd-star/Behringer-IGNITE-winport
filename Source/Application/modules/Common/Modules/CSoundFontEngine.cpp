// Copyright 2021 MUSIC Group Services EU GmbH
#include "CSoundFontEngine.h"
//#include "MLog.h"

using namespace Ignite;

CSoundFontEngine::CSoundFontEngine (AudioMode mode, uint32_t samplerate, uint32_t numvoices, float gain)
	: _mode (mode)
	, _samplerate (samplerate)
	, _numvoices (numvoices)
	, _gain (gain)
{
}
//#ifdef WINDOWS_PLATFORM
#if 0
CSoundFontEngine::~CSoundFontEngine ()
{
	if (!_tsf)
		return;
	tsf_reset (_tsf);
	tsf_close (_tsf);
}

void CSoundFontEngine::initEngineFromFile (const char* soundfontpath)
{
	if (_tsf)
		return;
	_tsf = tsf_load_filename (soundfontpath);

	setupAudioSpecs ();
}

void CSoundFontEngine::setupAudioSpecs (void)
{
	if (!_tsf)
		return;
	log_debug ("%u, %u, %f", _mode, _samplerate, _gain);
	tsf_channel_set_bank_preset (_tsf, 9, 128, 0);
	tsf_set_output (_tsf, (TSFOutputMode)_mode, _samplerate, _gain);
	tsf_set_max_voices (_tsf, _numvoices);
}

void CSoundFontEngine::setGain (float gain)
{
	_gain = gain;
	if (!_tsf)
		return;
	tsf_set_volume (_tsf, gain);
}

float CSoundFontEngine::getGain (void) const
{
	return _gain;
}

uint32_t CSoundFontEngine::getProgramCount (void) const
{
	if (!_tsf)
		return 0;
	return tsf_get_presetcount (_tsf);
}

uint8_t CSoundFontEngine::getChannelProgram (uint8_t channel) const
{
	if (!_tsf || channel == 0 || channel > 16)
		return 0;
	return tsf_channel_get_preset_number (_tsf, channel - 1);
}

const char* CSoundFontEngine::getChannelProgramName (uint8_t channel) const
{
	if (!_tsf || channel == 0 || channel > 16)
		return "";
	return tsf_get_presetname (_tsf, tsf_channel_get_preset_number (_tsf, channel - 1));
}

void CSoundFontEngine::processBlock (short* buffer, uint32_t samples)
{
	if (_tsf) {
		return tsf_render_short (_tsf, buffer, samples, 0);
	}
}

void CSoundFontEngine::processBlock (int32_t* buffer, uint32_t samples)
{
	if (_tsf) {
		return tsf_render_long (_tsf, buffer, samples, 0);
	}
}

void CSoundFontEngine::channelNoteOn (uint8_t pitch, uint8_t velocity, uint8_t channel)
{
	if (!_tsf || channel == 0 || channel > 16)
		return;
	tsf_channel_note_on (_tsf, channel - 1, pitch, (float)(velocity / 128.0f));
}

void CSoundFontEngine::channelNoteOff (uint8_t pitch, uint8_t channel)
{
	if (!_tsf || channel == 0 || channel > 16)
		return;
	tsf_channel_note_off (_tsf, channel - 1, pitch);
}

void CSoundFontEngine::presetNoteOn (uint8_t preset, uint8_t pitch, uint8_t velocity)
{
	if (!_tsf)
		return;
	tsf_note_on (_tsf, preset, pitch, (float)(velocity / 128.0f));
}

void CSoundFontEngine::presetNoteOff (uint8_t preset, uint8_t pitch)
{
	if (!_tsf)
		return;
	tsf_note_off (_tsf, preset, pitch);
}

void CSoundFontEngine::noteOffAll (void)
{
	if (!_tsf)
		return;
	tsf_note_off_all (_tsf);
}

void CSoundFontEngine::programChange (uint8_t program, uint8_t channel)
{
	if (!_tsf || channel == 0 || channel > 16)
		return;
	tsf_channel_note_off_all (_tsf, channel - 1);
	tsf_channel_set_presetnumber (_tsf, channel - 1, program, (channel == 10));
}

void CSoundFontEngine::controlChange (uint8_t control, uint8_t value, uint8_t channel)
{
	if (!_tsf || channel == 0 || channel > 16)
		return;
	tsf_channel_midi_control (_tsf, channel - 1, control, value);
}

void CSoundFontEngine::pitchBend (int16_t value, uint8_t channel)
{
	if (!_tsf || channel == 0 || channel > 16)
		return;
	tsf_channel_set_pitchwheel (_tsf, channel - 1, value);
}
#else
CSoundFontEngine::~CSoundFontEngine () {}
void CSoundFontEngine::initEngineFromFile (const char* soundfontpath) {}
//void CSoundFontEngine::setupAudioSpecs(void){}
void CSoundFontEngine::setGain (float gain) {}
float CSoundFontEngine::getGain (void) const { return (0.0); }
uint32_t CSoundFontEngine::getProgramCount (void) const { return 0; }
uint8_t CSoundFontEngine::getChannelProgram (uint8_t channel) const { return 0; }
const char* CSoundFontEngine::getChannelProgramName (uint8_t channel) const { return(" "); }
void CSoundFontEngine::processBlock (short* buffer, uint32_t samples) {}
void CSoundFontEngine::processBlock (int32_t* buffer, uint32_t samples) {}
void CSoundFontEngine::channelNoteOn (uint8_t pitch, uint8_t velocity, uint8_t channel) {}
void CSoundFontEngine::channelNoteOff (uint8_t pitch, uint8_t channel) {}
void CSoundFontEngine::presetNoteOn (uint8_t preset, uint8_t pitch, uint8_t velocity) {}
void CSoundFontEngine::presetNoteOff (uint8_t preset, uint8_t pitch) {}
void CSoundFontEngine::noteOffAll (void) {}
void CSoundFontEngine::programChange (uint8_t program, uint8_t channel) {}
void CSoundFontEngine::controlChange (uint8_t control, uint8_t value, uint8_t channel) {}
void CSoundFontEngine::pitchBend (int16_t value, uint8_t channel) {}
#endif
