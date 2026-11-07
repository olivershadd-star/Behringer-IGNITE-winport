#include "CMidiCV.h"
//#include "CPlayManager.h"
//#include "Constants.h"
//#include "SwingHal.h"
#include <math.h>
using namespace Ignite;

CMidiCV::CMidiCV ()
{
	sendGateCV (MidiType::NoteOff); // All outputs low
}

void CMidiCV::onConfigChange (const Config config, const uint8_t value)
{
	switch (config) {
		case Config::modCVSource: {
			_modCVSource = (ModCvSource)value;
		} break;
		case Config::pitchCVType: {
			_pitchCVType = (PitchCVType)value;
		} break;
		case Config::modCVMaxVoltage: {
			_modCVMaxVoltage = (ModCVMaxVoltage)value;
		} break;
		case Config::notePriority: {
			_notePriority = (NotePriority)value;
		} break;
		case Config::onevMidiNote: {
			_oneVoltMidiNote = value;
		} break;
		case Config::zeroVMidiNote: {
			_zeroVoltMidiNote = value;
		} break;
		case Config::pitchBendRange: {
			_pitchBendRange = value;
		} break;
		case Config::gateCVOutput: {
			_gateCVOutput = (GateCVOutput)value;
		} break;
		default:
			break;
	}
}

void CMidiCV::sendNoteOn (DataByte inNoteNumber, DataByte inVelocity, Channel inChannel)
{
	sendGateCV (MidiType::NoteOn);
	sendPitchCV (MidiType::NoteOn, inNoteNumber, inVelocity);
	if (_modCVSource == ModCvSource::Velocity) {
		sendModCV (inVelocity);
	}
}

void CMidiCV::sendNoteOff (DataByte inNoteNumber, DataByte inVelocity, Channel inChannel)
{
	sendGateCV (MidiType::NoteOff);
}

void CMidiCV::sendPitchBend (uint8_t inPitchValue, Channel inChannel)
{
	_pitch = inPitchValue;
	sendPitchCV (MidiType::PitchBend, inPitchValue, 0);
}

void CMidiCV::sendControlChange (DataByte inControlNumber, DataByte inControlValue, Channel inChannel)
{
	if (inControlNumber == 1 && _modCVSource == ModCvSource::ModWheel) {
		sendModCV (inControlValue);
	}
}

void CMidiCV::sendAfterTouch (DataByte inPressure, Channel inChannel)
{
	if (_modCVSource == ModCvSource::Aftertouch) {
		sendModCV (inPressure);
	}
}

void CMidiCV::sendPitchCV (MidiType type, uint8_t data1, uint8_t data2)
{
	// KB CV
	if (type == MidiType::NoteOn || type == MidiType::PitchBend) {
		if (_pitchCVType == PitchCVType::VoltsPerOctave) {
			calcDutyVoltsPerOctave ();
		}
		else // (pitchcvtype == PitchCVType::HertzPerVolt) {
		{
			calcDutyHertzPerVolt ();
		}

		outputPWMCV (PwmChannel::pitchCV1);
		outputPWMCV (PwmChannel::pitchCV2);
	}

	// GATE CV
	sendModCV (type == MidiType::NoteOn);
}

float CMidiCV::modCVReference (void) const
{
	// Max voltage calculation (costants are from 5 to 12)
	return (100.0f * ((float)_modCVMaxVoltage + 5)) / 12.0f;
}

void CMidiCV::sendModCV (uint8_t value)
{
	_modDuty = ((90 * value * modCVReference ()) / 127);
	outputPWMCV (PwmChannel::modCV);
}

uint8_t CMidiCV::getReferenceNotePitch (void) const
{
	uint8_t pitch = 0;
	const auto priority = _notePriority;
	if (priority == NotePriority::High) {
		pitch = CPlayManager::getInstance ().highestNote ();
	}
	else if (priority == NotePriority::Low) {
		pitch = CPlayManager::getInstance ().lowestNote ();
	}
	else if (priority == NotePriority::Last) {
		pitch = CPlayManager::getInstance ().lastNote ();
	}
	return pitch;
}

void CMidiCV::calcDutyHertzPerVolt ()
{
	const auto ref_note = getReferenceNotePitch ();
	const int16_t relative_note = (ref_note - _oneVoltMidiNote);
	float output_voltage_mv = _calib1HertzPerVolts * (((float)relative_note)); // volts per octave value
	output_voltage_mv = powf (2, ((output_voltage_mv / 1000) - 1)); // Vhz = 2^(Voct - 1)
	_cv1Duty = (uint32_t)(output_voltage_mv * 1000);
	_cv2Duty = 0;
}

void CMidiCV::calcDutyVoltsPerOctave ()
{
	const auto ref_note = getReferenceNotePitch ();
	const int16_t relative_note = (ref_note - _zeroVoltMidiNote);
	if (relative_note >= 0) {
		float pb_variation = 0;
		if (_pitch != 0) {
			pb_variation = (_pitch / 64.0f) * _pitchBendRange;
		}
		_cv1Duty = (_calib1VoltsPerOctave * (((float)relative_note) + pb_variation));
		_cv2Duty = (_calib2VoltsPerOctave * (((float)(relative_note % 12)) + pb_variation));
	}
	else {
		_cv1Duty = 0;
		_cv2Duty = 0;
	}
}

void CMidiCV::sendGateCV (MidiType type)
{
	if (type == MidiType::NoteOn) {
		switch ((GateCVOutput)_gateCVOutput) {
			case (GateCVOutput::STrigger):
				SwingHal::setGPIO (gpioPin::gate0VPin);
				SwingHal::clearGPIO (gpioPin::gate12VPin);
				SwingHal::clearGPIO (gpioPin::gate5VPin);
				break;
			case (GateCVOutput::VTrigger5V):
				SwingHal::setGPIO (gpioPin::gate5VPin);
				SwingHal::clearGPIO (gpioPin::gate0VPin);
				SwingHal::clearGPIO (gpioPin::gate12VPin);
				break;
			case (GateCVOutput::VTrigger12V):
				SwingHal::setGPIO (gpioPin::gate5VPin);
				SwingHal::setGPIO (gpioPin::gate12VPin);
				SwingHal::clearGPIO (gpioPin::gate0VPin);
				break;
		}
	}
	else if (type == MidiType::NoteOff) {
		SwingHal::clearGPIO (gpioPin::gate5VPin);
		SwingHal::clearGPIO (gpioPin::gate0VPin);
		SwingHal::clearGPIO (gpioPin::gate12VPin);
	}
}

void CMidiCV::setCalibration (CalibrationParam param, float value)
{
	switch (param) {
		case CalibrationParam::calib1VPO:
			_calib1VoltsPerOctave = value;
			break;
		case CalibrationParam::calib2VPO:
			_calib2VoltsPerOctave = value;
			break;
		case CalibrationParam::calib1HPV:
			_calib1HertzPerVolts = value;
			break;
		default:
			break;
	}
}

void CMidiCV::outputPWMCV (PwmChannel channel)
{
	switch (channel) {
		case (PwmChannel::pitchCV1):
			SwingHal::setPWMDutyCycle (pwmCh::pitchCV1, _cv1Duty);
			break;
		case (PwmChannel::pitchCV2):
			SwingHal::setPWMDutyCycle (pwmCh::pitchCV2, _cv2Duty);
			break;
		case (PwmChannel::modCV):
			SwingHal::setPWMDutyCycle (pwmCh::modCV, _modDuty);
			break;
	}
}