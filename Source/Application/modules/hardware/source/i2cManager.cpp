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

#if( JUCE_LINUX || __linux__ )
#include <iostream>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#endif

namespace ui
{
	I2CDevice::I2CDevice()
		: devicePath_("/dev/i2c-1"), address_(0xc), file_(-1), isDeviceOpen_(false)
	{
		if (openDevice())
		{
			isDeviceOpen_ = true;
		}
	}

	I2CDevice::~I2CDevice()
	{
	}

	bool I2CDevice::isOpen() const
	{
		return isDeviceOpen_;
	}

	bool I2CDevice::openDevice()
	{
#if( JUCE_LINUX || __linux__ )
		file_ = open(devicePath_.c_str(), O_RDWR);
		if (file_ < 0)
		{
			DBG("DAC Failed to open the I2C device");
			return false;
		}
		else
			DBG("DAC SUCCCESS to open the I2C device");

		if (ioctl(file_, I2C_SLAVE, address_) < 0)
		{
			DBG("DAC Failed to select I2C device");
			closeDevice();
			return false;
		}
		else
			DBG("DAC SUCCCESS to SET Slave Address");
#endif
		return true;
	}

	void I2CDevice::closeDevice()
	{
#if( JUCE_LINUX || __linux__ )
		if (file_ >= 0)
		{
			close(file_);
			file_ = -1;
		}
#endif
		isDeviceOpen_ = false;
	}

	bool I2CDevice::writeBytes(const uint8_t* data, int length)
	{
#if( JUCE_LINUX || __linux__ )
		if (!isOpen())
		{
			DBG("DAC I2C device is not open");
			return false;
		}

		//DBG("data[0]=" << juce::String::toHexString(data[0]));
		//DBG("data[1]=" << juce::String::toHexString(data[1]));
		//DBG("data[2]=" << juce::String::toHexString(data[2]));
		ssize_t bytesWritten = write(file_, data, length);
		if (bytesWritten != length)
		{
			DBG("DAC Failed to write to the I2C device");
			return false;
		}
#endif
		return true;
	}

	bool I2CDevice::readBytes(uint8_t* buffer, int length)
	{
#if( JUCE_LINUX || __linux__ )
		if (!isOpen())
		{
			DBG("DAC I2C device is not open");
			return false;
		}

		ssize_t bytesRead = read(file_, buffer, length);
		if (bytesRead != length)
		{
			DBG("DAC Failed to read from the I2C device");
			return false;
		}
#endif
		return true;
	}
}
