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
#pragma warning(disable : 4201)
#include <cstdint>
#include <JuceHeader.h>
#include "ignite_ui/source/settings/mt_ignite_device_status.h"
#include<fstream>
#include<filesystem>

#define READ 0
#define WRITE 1

#define INFO                ( ( 'I' ) | ( 'N' << 8 ) | ( 'F' << 16 ) | ( 'O' << 24 ) )
#define FAIL                ( ( 'F' ) | ( 'A' << 8 ) | ( 'I' << 16 ) | ( 'L' << 24 ) )
#define OKAY                ( ( 'O' ) | ( 'K' << 8 ) | ( 'A' << 16 ) | ( 'Y' << 24 ) )
#define DATA                ( ( 'D' ) | ( 'A' << 8 ) | ( 'T' << 16 ) | ( 'A' << 24 ) )
#define CONN                ( ( 'C' ) | ( 'O' << 8 ) | ( 'N' << 16 ) | ( 'N' << 24 ) )

#define MAX_FRAME_SIZE      64
#define MAX_FRAME_DATA_SIZE 60
namespace filesystem = std::filesystem;
namespace Ignite
{
	class FrontPannelManager;

	class USBFunctionFS : public juce::Thread
		, juce::Timer
	{
	public:
		//USBFunctionFS();
		USBFunctionFS(FrontPannelManager* frontpannelmangr, IgniteEngine& model);
		~USBFunctionFS() override;

		void start();
		void stop();
		void run() override;
		void init();
		bool getStatus() { return isConnected.load(); }
		void setFirmwareUpdateStatus(DEV_STATUS state);

		virtual void timerCallback();

		/*static USBFunctionFS* getUSBInstance()
		{
			static USBFunctionFS* _usbFunctionfs;
			if (NULL == _usbFunctionfs)
			{
				_usbFunctionfs = new USBFunctionFS();
			}
			return _usbFunctionfs;
		}*/

		void setUsbcallback(UsbStatus func)
		{
			usbCallback = func;
		}

	private:
		UsbStatus           usbCallback;
		bool                timerRunning = false; // Define timerRunning as a member variable
		bool                responseReceived = false;
		int                 g_ep_write = -1;
		int                 g_ep_read = -1;
		int                 write_filefd = -1; //linux will be writing to this file
		int                 read_filefd = -1; //linux will be writing to this file
		int                 stdoutfd = -1;
		DEV_STATUS          fw_update_status = INVALID_STATE;
		std::atomic<bool>   isConnected = false;
		juce::String usbFilePath;

		std::string rFilePath;

		FrontPannelManager* frontPannelManager = nullptr;
		IgniteDeviceStatus* deviceStatus = nullptr;
		IgniteEngine& engine;

		int                 openFileDescriptor(const juce::String& filePath);
		void                closeFileDescriptor(int fd);
		void                handleOpenFileError(const juce::String& filePath);
		void                readCommandFromUSB(juce::String& command);
		int                 handleCommand(const juce::String& command);
		int                 writeData(void* p, size_t size);
		int                 writeFile(int fp, void* p, size_t size);

		int handleAckCommand();
		int handleWFileCommand(juce::String& filename, int size);
		int handleWDataCommand(const juce::StringArray& parts, int size);
		int handleReadFileCommand(const juce::String& cmdType);
		int handleUploadCommand(const juce::StringArray& parts);
		int handleCloseFileCommand();
		int handleFirmwareCompleteCommand();
		int handleUCmdCommand(const char* cmd);
		int handleDeviceInfoCommand();
		int handleFactoryResetCommand();
		
		size_t calculateSizeofFile(std::ifstream* file);
		std::string fwstatusToString(FwStatus_t status);

#if defined( JUCE_LINUX ) || defined( __linux__ )
		pid_t popen2(const char* command, int* infp, int* outfp);
#endif
		union FSdata
		{
			uint8_t raw[MAX_FRAME_SIZE];
			struct
			{
				uint32_t key;
				uint8_t  data[MAX_FRAME_SIZE - sizeof(uint32_t)];
			};
		};

		int handleCreateDirectoryCommand(const char* buff, FSdata fs, int tfilesize, usbmsg_t data);

	};
}
