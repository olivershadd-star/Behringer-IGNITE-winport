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

#pragma once

#include <string>
#if defined( __linux__ ) || defined( __linux ) || defined( linux )
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define CV_IOCTL_MAGIC 'M'

#define CV_IOCTL_GET_CHANNELS _IOR(CV_IOCTL_MAGIC, 1, int)
#define CV_IOCTL_ENABLE_CHANNEL _IOW(CV_IOCTL_MAGIC, 2, int)
#define CV_IOCTL_DISABLE_CHANNEL _IOW(CV_IOCTL_MAGIC, 3, int)

#define DEVICE_PATH "/dev/cvctl_misc" // Path to the device file

#define MUX_S0	 1
#define MUX_S1   2
#define MUXA_EN  3
#define MUXB_EN  4
#endif

#define CV_CALIB_DEBUG 0
#define DAC_MAX_OUTPUT 2.5
#define DAC_RESOLUTION 16384
#define OPAMP_GAIN	4.8

#define DAC_OP_REG_VALUE(voltage)  (((voltage/OPAMP_GAIN)/DAC_MAX_OUTPUT)*DAC_RESOLUTION)


namespace ui
{
	class I2CDevice;
	class CVControl;
	class IgniteCalibration;

	class CVVoltageRefresh : public juce::Thread
	{
	public:
		CVVoltageRefresh() : juce::Thread("CVVoltageRefresh")
		{
#if defined( __linux__ ) || defined( __linux ) || defined( linux )

			cvGpioFd = open(DEVICE_PATH, O_WRONLY);

			if (cvGpioFd < 0) {
				perror("Failed to open the device file");
			}

			/* Disable DAC output*/
			auto tmp_port = MUXA_EN;
			ioctl(cvGpioFd, CV_IOCTL_ENABLE_CHANNEL, &tmp_port);
			tmp_port = MUXB_EN;
			ioctl(cvGpioFd, CV_IOCTL_ENABLE_CHANNEL, &tmp_port);
#endif
		}
		void run() override;
	private:
		int cvGpioFd = 0;
		int var1 = 0;
		int loop = 0;
		int cvIndex = 0;
		int gateIndex = 0;
		I2CDevice i2c;

		bool setDacVoltage(int channel, int reg);
		void setChannelState(int fd, int port, bool enable);
		void processVoltages(int var);
	};

	class CVControl
	{
	public:
		CVControl();
		~CVControl();

		void setCvVoltage(int cv_channel, float volt);
		void setGateVoltage(int gate_channel, float volt);
		void setArrayCvVoltage(float volt);
		void setArrayGateVoltage(float volt);
		void setVoltageforAllPorts(float volt);

		static CVControl* getCVInterface()
		{
			static CVControl* _cvInterface;
			if (NULL == _cvInterface)
			{
				_cvInterface = new CVControl();
			}

			return _cvInterface;
		}

	private:
		int cvGpioFd = 0;
		I2CDevice i2c;

		CVVoltageRefresh refreshThread;
		std::thread myThread;
		std::atomic<bool> threadShouldExit{ false };
		bool setupDac();
	};
}
