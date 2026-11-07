#pragma once
#include <stdint.h>

namespace Ignite {

	// Supported output modes by the render methods
	enum class AudioMode : uint8_t {
		StereoInterleaved = 0,
		StereoUnweaved,
		Mono,
	};

	enum class SequencerMode : uint8_t {
		Off = 0,
		Play,
		StepRecord,
		LiveAppend,
		LiveReplace
	};

	enum class ArpStyle : uint8_t {
		Up = 0,
		Down,
		Exc,
		Up2,
		Down2,
		Exc2,
		Order,
		Random,
	};

	enum class EraseMode : uint8_t {
		EraseNone = 0,
		EraseLast,
		EraseAll
	};

	enum class TimeDiv : uint8_t {
		TimDiv_4 = 0,
		TimDiv_4T,
		TimDiv_8,
		TimDiv_8T,
		TimDiv_16,
		TimDiv_16T,
		TimDiv_32,
		TimDiv_32T,
		TimDivUndefined,
	};

	enum class TransportState : uint8_t {
		Stopped = 0,
		Paused,
		Playing,
	};

	enum class TransportBarEvent : uint8_t {
		RecordPressed = 0,
		RecordReleased,
		StopPressed,
		StopReleased,
		PlayPressed,
		PlayReleased
	};

	enum class DeviceMode : uint8_t {
		DeviceArp = 0,
		DeviceSeq
	};
/*
	enum class SyncSource : uint8_t {
		Internal = 0,
		Usb,
		Serial,
		SyncIn,
	};
*/

	enum class RatchetMode : uint8_t {
		Ratchet1 = 1,
		Ratchet2,
		Ratchet3,
		Ratchet4,
	};

	enum class TransportMode : uint8_t {
		Off = 0,
		Midicc,
		Mmc,
		Both,
	};

	enum class HoldSustainMode : uint8_t {
		Gate = 0,
		Toggle
	};

	enum class HoldSustainFunction : uint8_t {
		Hold = 1,
		Sustain,
		Both
	};

	enum class VelocityCurve : uint8_t {
		Linear = 0,
		Log,
		Antilog,
	};

	enum class AftertouchCurve : uint8_t {
		Linear = 0,
		Log,
		Antilog,
		Soft
	};

	enum class ClockMode : uint8_t {
		OneStepGate = 0,
		OneStepClock,
		OnePulseKorg,
		Mode24ppq,
		Mode48ppq,
		OutMirrorIn
	};

	enum class ClockStartMode : uint8_t {
		OnClock = 0,
		OnGate
	};

	enum class PlayPause : uint8_t {
		Pause = 0,
		Reset
	};

	enum class PitchCVType : uint8_t {
		VoltsPerOctave = 0,
		HertzPerVolt
	};

	enum class NotePriority : uint8_t {
		Low = 0,
		High,
		Last
	};

	enum class ModCvSource : uint8_t {
		ModWheel = 0,
		Velocity,
		Aftertouch
	};

	enum class ModCVMaxVoltage : uint8_t {
		_5V = 0,
		_6V,
		_7V,
		_8V,
		_9V,
		_10V,
		_11V,
		_12V
	};

	enum class GateCVOutput : uint8_t {
		STrigger = 0,
		VTrigger5V,
		VTrigger12V,
	};

	enum class NextSeqMode : uint8_t {
		End = 0,
		InstantReset,
		InstantContinue,
	};

	enum class TranspositionInputPort : uint8_t {
		Usb = 0,
		Midi,
		Both,
	};

	enum class TranspositionLatch : uint8_t {
		On = 0,
		Off,
	};

	enum class VelocityValue : uint8_t {
		AsRecorded = 0,
		Fixed,
	};

	enum class TempoKnobMode : uint8_t {
		Jump = 0,
		Pickup,
	};

	enum class TapTempoCount : uint8_t {
		Average2 = 0,
		Average3,
		Average4
	};

	enum class SeqTieMode : uint8_t {
		TieToPrevious = 0,
		TieToNext
	};

	enum class ArpRandomMode : uint8_t {
		Total = 0,
		Pattern,
		Brownian
	};

	enum class keyboardMode : uint8_t {
		Play = 0,
		Transpose
	};

	enum class GateValue : uint8_t {
		GateRnd = 0,
		Gate10,
		Gate20,
		Gate40,
		Gate60,
		Gate80,
		Max
	};

	enum class SwingValue : uint8_t {
		Off = 0,
		Swing54,
		Swing56,
		Swing58,
		Swing60,
		Swing62,
		Swing65,
		Swing68,
		Swing72,
		Swing76,
		Swing80,
		Max
	};

	enum class KbdOctave : uint8_t {
		OctMinus3 = 1,
		OctMinus2,
		OctMinus1,
		OctCenter,
		OctPlus1,
		OctPlus2,
		OctPlus3,
		OctPlus4,
		OctMin = OctMinus3,
		OctMax = OctPlus4
	};

}