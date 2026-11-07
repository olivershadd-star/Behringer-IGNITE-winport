#pragma once
//#include "Configs.h"
//#include "Constants.h"
//#include "midi_defs.h"
#include <stdint.h>
namespace Ignite {

	enum class PwmChannel {
		pitchCV2 = 0,
		pitchCV1 = 1,
		modCV
	};

	enum class CalibrationParam {
		calib1VPO = 0,
		calib2VPO,
		calib1HPV,
	};

#ifdef MIDI_CV_ENABLED

	class CMidiCV {
	public:
		CMidiCV ();
		~CMidiCV () = default;
		void onConfigChange (const Config config, const uint8_t value);
		void sendNoteOn (DataByte inNoteNumber, DataByte inVelocity, Channel inChannel);
		void sendNoteOff (DataByte inNoteNumber, DataByte inVelocity, Channel inChannel);
		void sendPitchBend (uint8_t inPitchValue, Channel inChannel);
		void sendControlChange (DataByte inControlNumber, DataByte inControlValue, Channel inChannel);
		void sendAfterTouch (DataByte inPressure, Channel inChannel);

	private:
		inline void sendPitchCV (MidiType type, uint8_t data1, uint8_t data2);
		inline void sendModCV (uint8_t value);
		inline void sendGateCV (MidiType type);
		inline void setCalibration (CalibrationParam param, float value);
		inline uint8_t getReferenceNotePitch () const;
		inline void calcDutyHertzPerVolt ();
		inline void calcDutyVoltsPerOctave ();
		inline void outputPWMCV (PwmChannel channel);
		inline float modCVReference () const;
		uint16_t _cv1Duty = 0;
		uint16_t _cv2Duty = 0;
		uint16_t _modDuty = 0;
		float _calib1VoltsPerOctave = 81.67f; // Constants::pitchOctaveDutyUnit;
		float _calib2VoltsPerOctave = 816.7f; // Constants::pitchNoteDutyUnit;
		float _calib1HertzPerVolts = 82.80f; // Constants::pitchOctaveDutyUnitHz;
		int _pitch = 0;
		// Settings
		ModCvSource _modCVSource;
		PitchCVType _pitchCVType;
		ModCVMaxVoltage _modCVMaxVoltage;
		NotePriority _notePriority;
		uint8_t _oneVoltMidiNote;
		uint8_t _zeroVoltMidiNote;
		uint8_t _pitchBendRange;
		GateCVOutput _gateCVOutput;
	};
#endif

}