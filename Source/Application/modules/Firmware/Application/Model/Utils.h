#pragma once
#include "EnumTypes.h"
#include "Configs.h"
#include "Constants.h"
#include <stdint.h>
namespace Ignite {
	class Utils {
	public:
		static constexpr uint8_t keyToPitchValue (uint8_t key, uint8_t octave, uint8_t offset = 5)
		{
			uint8_t pitch = ((octave - 1) * 12) + key + offset;
			pitch = pitch > 127 ? 127 : pitch;
			return pitch;
		}

		static uint8_t microsecondsToVelocity (uint32_t us_tm, VelocityCurve curve)
		{
			uint8_t velocity = 0;

			if (us_tm < Constants::keyStrokeMinTimeUs) {
				velocity = 0x7f;
			}
			else if (us_tm > Constants::keyStrokeMaxTimeUs) {
				velocity = 0;
			}
			else {
				//From 2,5 and 400 ms
				uint16_t x = (uint16_t)(us_tm / 1000);

				//LINEAR (0-4), LOG(5-9), ANTILOG(10-14)
				static uint16_t xpoints[15] = { 0, 25, 100, 130, 400, 0, 34, 115, 150, 400, 0,
					14, 48, 75, 400 };
				static uint16_t ypoints[15] = { 127, 40, 12, 10, 0, 127, 42, 16, 10, 0, 127,
					32, 18, 10, 0 };

				uint16_t x1, x2, y1, y2;
				uint8_t offset = 0;

				switch (curve) {
					case (VelocityCurve::Linear):
						offset = 0;
						break;
					case (VelocityCurve::Log):
						offset = 5;
						break;
					case (VelocityCurve::Antilog):
						offset = 10;
						break;
				}

				if (x <= xpoints[offset + 1]) {
					x1 = xpoints[offset];
					x2 = xpoints[offset + 1];
					y1 = ypoints[offset];
					y2 = ypoints[offset + 1];
				}
				else if (x <= xpoints[offset + 2]) {
					x1 = xpoints[offset + 1];
					x2 = xpoints[offset + 2];
					y1 = ypoints[offset + 1];
					y2 = ypoints[offset + 2];
				}
				else if (x <= xpoints[offset + 3]) {
					x1 = xpoints[offset + 2];
					x2 = xpoints[offset + 3];
					y1 = ypoints[offset + 2];
					y2 = ypoints[offset + 3];
				}
				else {
					x1 = xpoints[offset + 3];
					x2 = xpoints[offset + 4];
					y1 = ypoints[offset + 3];
					y2 = ypoints[offset + 4];
				}

				velocity =(uint8_t) (((((float)(x - x1)) / ((float)(x2 - x1)))
					* ((float)(y2 - y1)))
					+ y1);
			}
			return velocity;
		}

		static uint8_t getRealAftertouchValue (uint8_t linearValue, uint8_t calibration, AftertouchCurve curve)
		{
			float delta;
			float max_delta = 60.0;
			uint8_t aft_midi_value = linearValue;
			switch (curve) {
				case AftertouchCurve::Log: {
					if (linearValue < 64) {
						delta = (max_delta * ((float)aft_midi_value)) / 127;
					}
					else {
						delta = max_delta * (1 - (((float)aft_midi_value) / 127));
					}
					aft_midi_value -= (uint8_t)delta;
				} break;
				case AftertouchCurve::Antilog:
					if (linearValue < 64) {
						delta = (max_delta * ((float)aft_midi_value)) / 127;
					}
					else {
						delta = max_delta * (1 - (((float)aft_midi_value) / 127));
					}
					aft_midi_value += (uint8_t)delta;
					break;
				case AftertouchCurve::Soft:
					delta = (max_delta * ((float)aft_midi_value)) / 127;
					aft_midi_value -= (uint8_t)delta;
					break;
			}
			int16_t calibrated_aft_value = aft_midi_value
				+ (calibration - 0x3F);

			if (calibrated_aft_value < 0) {
				calibrated_aft_value = 0;
			}
			if (calibrated_aft_value > 127)
				calibrated_aft_value = 127;
			aft_midi_value = (uint8_t)calibrated_aft_value;
			return aft_midi_value;
		}
	};
}