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

namespace ui
{
	class I2CDevice
	{
	public:
		I2CDevice();
		~I2CDevice();

		bool isOpen() const;

		bool writeBytes(const uint8_t* data, int length);
		bool readBytes(uint8_t* buffer, int length);

	private:
		int         file_;
		std::string devicePath_;
		int         address_;
		bool        isDeviceOpen_;

		bool openDevice();
		void closeDevice();
	};
}
