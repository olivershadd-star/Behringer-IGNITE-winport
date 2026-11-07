#pragma once

namespace Ignite
{
	namespace Sysex
	{
		class utils
		{
		public:
			static uint16_t sysexToData (uint8_t* sysex, uint8_t* output, uint16_t len)
			{
				uint16_t cnt;
				uint16_t cnt2 = 0;
				uint16_t bits = 0;
				for (cnt = 0; cnt < len; cnt++)
				{
					if ((cnt % 8) == 0)
					{
						bits = sysex[cnt];
					}
					else
					{
						output[cnt2++] = sysex[cnt] | ((bits & 1) << 7);
						bits >>= 1;
					}
				}
				return cnt2;
			}

			static uint8_t dataToSysex (uint8_t* data, uint8_t* sysex, uint8_t len)
			{
				uint8_t retLen = 0;
				uint8_t cnt;
				uint8_t cnt7 = 0;

				sysex[0] = 0;

				for (cnt = 0; cnt < len; cnt++)
				{
					uint8_t c = data[cnt] & 0x7F;
					uint8_t msb = data[cnt] >> 7;
					sysex[0] |= msb << cnt7;
					sysex[1 + cnt7] = c;

					if (cnt7++ == 6)
					{
						sysex += 8;
						retLen += 8;
						sysex[0] = 0;
						cnt7 = 0;
					}
				}
				return retLen + cnt7 + (cnt7 != 0 ? 1 : 0);
			}
		};
	}
}