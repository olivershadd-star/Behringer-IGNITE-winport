/*
 * Copyright (c) - 2021 - MUSIC Tribe, MY.
 * This file is part of IGNITE.
 *
 * IGNITE is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Affero General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * IGNITE is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with IGNITE. If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#include <juce_core/system/juce_PlatformDefs.h>
int cvVoltageArray[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int gateVoltageArray[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

namespace ui
{
	CVControl::CVControl()
	{
#if defined( __linux__ ) || defined( __linux ) || defined( linux )
		setupDac();
#endif
		IgniteCalibration::GetAppCalibrationInstance()->dacVoltageChanged.connect([this](int port, float voltage)
			{
				setCvVoltage(port, voltage);
			});
		IgniteCalibration::GetAppCalibrationInstance()->dacVoltageChangedForAll.connect([this](float voltage)
			{
				setArrayCvVoltage(voltage);
			});
	}
	CVControl::~CVControl()
	{
#if defined( __linux__ ) || defined( __linux ) || defined( linux )
		// Close the device file
		close(cvGpioFd);
#endif
	}

	/*
	*	Port	     MUXA_EN	     MUXB_EN	      MUXS1	      MUXS0	         Value to cvgpio driver  DAC1	DAC2  Value
													in decimal
		CV0				0		1		0				0			4									  ON	OFF		2
		GATE0			0		1		0				0			4									  OFF	ON		1
		CV1				0		1		0				1			5									  ON	OFF		2
		GATE1			0		1		0				1			5									  OFF	ON		1
		CV2				0		1		1				0			6									  ON	OFF		2
		GATE2			0		1		1				0			6									  OFF	ON		1
		CV3				0		1		1				1			7									  ON	OFF		2
		GATE3			0		1		1				1			7								      OFF	ON		1
		CV4				1		0		0				0			8									  ON	OFF		2
		GATE4			1		0		0				0			8									  OFF	ON		1
		CV5				1		0		0				1			9									  ON	OFF		2
		GATE5			1		0		0				1			9									  OFF	ON		1
		CV6				1		0		1				0			10									  ON	OFF		2
		GATE6			1		0		1				0			10									  OFF	ON		1
		CV7				1		0		1				1			11									  ON	OFF		2
		GATE7			1		0		1				1			11									  OFF	ON		1
		Disable all		1		1		x				x			12									  OFF   OFF		0

	*/

	bool CVControl::setupDac()
	{
		uint8_t buffer[3] = { 0 };
		buffer[0] = 0x3f; //Internal reference setup (1- on/0 - off )
		buffer[1] = 0x00;
		buffer[2] = 0x01;

		if (!i2c.writeBytes(buffer, sizeof(buffer)))
		{
			DBG("Failed to setup internal refernece register");
			return false;
		}

		buffer[0] = 0x37; //LDAC register setup (1- The DAC registers are updated after new data is read in)
		buffer[1] = 0x00;
		buffer[2] = 0x03;

		if (!i2c.writeBytes(buffer, sizeof(buffer)))
		{
			DBG("Failed to setup LDAC register");
			return false;
		}
		refreshThread.startThread();

		return true;
	}

	void CVControl::setVoltageforAllPorts(float volt)
	{
		for (auto i = 0; i < 8; i++)
			cvVoltageArray[i] = gateVoltageArray[i] = (int)DAC_OP_REG_VALUE(volt);
	}

	void CVControl::setArrayCvVoltage(float volt)
	{
		DBG("Set all cv port voltage: " + juce::String(volt));
		for (auto i = 0; i < 8; i++)
			cvVoltageArray[i] = (int)DAC_OP_REG_VALUE(volt);
	}

	void CVControl::setArrayGateVoltage(float volt)
	{
		DBG("Set all gate voltage: " + juce::String(volt));
		for (auto i = 0; i < 8; i++)
			gateVoltageArray[i] = (int)DAC_OP_REG_VALUE(volt);
	}

	void CVControl::setCvVoltage(int cv_channel, float volt)
	{
		//DBG("Set CV voltage: " + juce::String(volt) + "For channel: " + String(cv_channel));play time print
		cvVoltageArray[cv_channel] = int(DAC_OP_REG_VALUE(volt));
	}

	void CVControl::setGateVoltage(int gate_channel, float volt)
	{
		//DBG("Set Gate voltage: " + juce::String(volt) + "For channel: " + String(gate_channel)); play time print
		gateVoltageArray[gate_channel] = (int)(DAC_OP_REG_VALUE(volt));
	}

	bool CVVoltageRefresh::setDacVoltage(int channel, int reg)
	{
		if (channel >= 0 && channel < 2)
		{
			uint8_t buffer[3] = { 0 };
			int dacOutputReg = reg;

			buffer[0] = (uint8_t)(0x10 | channel);
			buffer[1] = (dacOutputReg >> 6) & 0xFF;
			buffer[2] = dacOutputReg & 0xFF;
#if CV_CALIB_DEBUG
			DBG("buffer 1 : " + juce::String(buffer[1]));
			DBG("buffer 2 : " + juce::String(buffer[2]));
			//		DBG("Calibration CV DAC REG value: " + juce::String(dacOutputReg));
			//		DBG("Calibration CV value for note : " + juce::String(outputVoltage));
#endif
			if (!i2c.writeBytes(buffer, sizeof(buffer)))
			{
				DBG("setVoltage Failed to set Voltage Channel->" << channel);
				return false;
			}
			return true;
		}
		return true;
	}

	void CVVoltageRefresh::setChannelState(int fd, int port, bool enable)
	{
#ifdef _WIN32
		DBG("CVVoltageRefresh::setChannelState fd = " << fd << " port = " << port << " enable = " << (int)enable);
#elif defined __linux__
		ioctl(fd, enable ? CV_IOCTL_ENABLE_CHANNEL : CV_IOCTL_DISABLE_CHANNEL, &port);
#endif
	}

	void CVVoltageRefresh::processVoltages(int var)
	{
		setDacVoltage(0, cvVoltageArray[cvIndex]);
		setDacVoltage(1, gateVoltageArray[gateIndex]);
		setChannelState(cvGpioFd, 2, var == 2 || var == 3);
		setChannelState(cvGpioFd, 1, var == 1 || var == 3);
	}

	void CVVoltageRefresh::run()
	{
#if defined( __linux__ ) || defined( __linux ) || defined( linux )
		int var = 0;
		bool loop = false;

		DBG("CV Voltage Refresh Thread Started");
		while (!threadShouldExit())
		{
			this->setChannelState(cvGpioFd, 3, true);
			this->setChannelState(cvGpioFd, 4, true);
			processVoltages(var);

			var = (var + 1) % 4;

			if (loop == 0)
				setChannelState(cvGpioFd, 3, false);
			else
				setChannelState(cvGpioFd, 4, false);

			if (var == 0)
				loop = !loop;

			cvIndex = (cvIndex + 1) % 8;
			gateIndex = (gateIndex + 1) % 8;

			usleep(200);
		}
#endif
		DBG("Thread has exited.");
	}
}
