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
#include <iostream>
#include <stdint.h>
#include <string>
#include <atomic>
#include "Common/Os/CrossPlatform/CThread.h"
#include <ModelParams.h>
#include "common_ui_controls/common_ui_controls.h"
#include "ignite_ui/source/settings/mt_ignite_playtribe_connection_status.h"

#define PLAYTIBE_THREAD_INIT_WAIT 1000

#define PC_OPERATION_START_REQUEST					"PC_OPERATION_START"
#define PC_OPERATION_END_REQUEST					"PC_OPERATION_END"

#define DEVICE_INFO_REQUEST							"Device Info"
#define DEVICE_SYSTEM_LOG_REQUEST					"System Logs"
#define DEVICE_SAVE_BACKUP							"Save Backup"
#define DEVICE_LOAD_BACKUP_START_REQUEST			"Load Backup Start"
#define DEVICE_LOAD_BACKUP_END_REQUEST			    "Load Backup End"
#define DEVICE_FAC_RESET_REQUEST					"Factory Reset"
#define DEVICE_FW_UPDATE_REQUEST					"Firmware Update"
#define DEVICE_FW_UPDATE_STATUS_REQUEST				"Fw Status"
#define DEVICE_FAC_RESET_STATUS_REQUEST				"Factory Status"

namespace Ignite
{
	class FrontPannelManager;
	class PlayTribeConnectionManager : juce::Component
	{
	public:
		PlayTribeConnectionManager(FrontPannelManager* _frontpannelmangr);
		~PlayTribeConnectionManager();

		void setFirmwareUpdateStatus(DEV_STATUS state);
		void PlayTribeConnectionManagerStartThreads(void);
		void stopPlayTribeConnectionManagerThreads();
		void handleCommandMessage(int commandId) override;

		void disconnectClient();

	private:
		FrontPannelManager* frontPannelManager = nullptr;
		PlaytribeConnectionStatus* playtribeConnStatus = nullptr;

		std::atomic<int> clientSocket{ -1 };
		bool app_connected = false;
		DEV_STATUS          fw_update_status = INVALID_STATE;

		std::string encrypted_password;

		CThread PlayTribeEthernetWatchThread;
		CThread PlayTribeExternalReadThread;

		ThreadFunction PlayTribeExternalReadThreadFunctionCB;
		ThreadFunction PlayTribeEthernetWatchThreadFunctionCB;

		std::atomic<bool> shouldExitWatchThread{ false };
		std::atomic<bool> shouldExitReadThread{ false };

		void PlayTribeEthernetWatchThreadFunction(void);
		void PlayTribeExternalReadThreadFunction(void);

		void processCommandReceivedOverEthernet(const char* cmd);
		void sendResponseOverEthernet(const char* response, size_t len);

		void sendDeviceInfoRequestResponse();
		std::string fwstatusToString(FwStatus_t status);

		std::string getIPAddress();
		std::string generate_random_password(int length);
		std::string encrypt_password(const std::string& password, const std::string& key);
		bool set_ftp_user_password(const std::string& username, const std::string& password);
		std::string decrypt_password(const std::string& data, const std::string& key);
	};
}