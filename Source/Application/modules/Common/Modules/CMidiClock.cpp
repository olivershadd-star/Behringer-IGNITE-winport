#include "CMidiClock.h"
using namespace Ignite;

CMidiClock::CMidiClock ()
{
	auto timercb = [](void* context)
	{
		static_cast<CMidiClock*>(context)->syncTimerCb ();
	};
	_synctimer = std::make_unique<CHardwareTimer> (timercb, this);

	_timerIntervalUs = (uint16_t)((_synctimer->getFrequency () * 60) / (_tempo * SET_PPQN));
}

void inline CMidiClock::syncTimerCb (void)
{
	//call songmanager tick()
	_engine->get_SongManager()->pulse(_pulse);
	_pulse++;
	if (_pulse >= SET_PPQN)
	{
		_pulse = 0;
	}
}

void CMidiClock::initialize (IgniteEngine* eng)
{
	_engine = eng;
}

void CMidiClock::setTempo (float bpm)
{
	if (bpm == _tempo)
	{
		return;
	}
	if (bpm < _minTempo)
	{
		bpm = _minTempo;
	}
	if (bpm > _maxTempo)
	{
		bpm = _maxTempo;
	}
	_tempo = bpm;
	_timerIntervalUs =(uint16_t) ((_synctimer->getFrequency () * 60.0f) / (_tempo * SET_PPQN));
	if (_playing)
	{
		_synctimer->changeInterval (_timerIntervalUs);
	}
}

void CMidiClock::pause ()
{
	_pause = true;
	_playing = false;
	_synctimer->stop ();
}

void CMidiClock::start ()
{
	_pause = false;
	_playing = true;
	_synctimer->start (_timerIntervalUs);
}

void CMidiClock::stop ()
{
	_pause = false;
	_playing = false;
	_synctimer->stop ();
	_pulse = 0;
}

bool CMidiClock::isPlaying()
{
	return _playing;
}

float CMidiClock::getTempo()
{
	return _tempo;
}