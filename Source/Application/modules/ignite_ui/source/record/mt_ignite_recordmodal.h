/*
 * Copyright (c) - 2022 - MUSIC Tribe, MY.
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

namespace ui
{
	class IgniteControlOptions;
	class IgniteRecordModale :
		public juce::Component, public juce::Button::Listener
	{
	public:
#define RECORD_LIST 5
		enum RecordModalViewItemID
		{
			NO_FOCUS = 0,
			CREATE_NEW,
			OVERRIDE,
			AUDITION,
			CANCEL,
			FOCUS_MAX = CANCEL
		};
		int KeyFocusedItem = RecordModalViewItemID::NO_FOCUS;
		uint8_t RecordModalView[RECORD_LIST] = { NO_FOCUS, CREATE_NEW, OVERRIDE, AUDITION, CANCEL };
		IgniteRecordModale();
		~IgniteRecordModale() override;
		std::function<void(int Selection)> onSelectionChanged;
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);

		static IgniteRecordModale* GetAppRecordInstance()
		{
			static IgniteRecordModale* GetAppRecordObj;
			if (NULL == GetAppRecordObj)
			{
				GetAppRecordObj = new IgniteRecordModale();
			}

			return GetAppRecordObj;
		}
		void show(bool newrecord, bool overriderecord);

	private:
		CommonImageButton CreateNew{ "Create New Pattern and Start Recording","btn-create_and_start-default.png","btn-create_and_start-default-hover.png","btn-create_and_start-default-hover.png"};
		CommonImageButton OverRide{ "Overwrite Current Pattern and Start Recording","btn-overwrite_and_start-default.png","btn-overwrite_and_start-default-hover.png","btn-overwrite_and_start-default-hover.png" };
		CommonImageButton Audition{ "Start Audition","btn-start_auditioning-544x50-default.png","btn-start_auditioning-544x50-default-hover.png","btn-start_auditioning-544x50-default-hover.png"};
		CommonImageButton Cancel{ "Cancel","btn-cancel-record-default.png","btn-cancel-record-default-hover.png","btn-cancel-record-default-hover.png"};
		CommonLabel Title{"Options"};
		CommonImageButton close{ "Close","ico-close.png","ico-close.png" };
		IgniteControlOptions* CtrlPtr=nullptr;
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		bool overRide { false };
		void handleCommandMessage(int id);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteRecordModale)
	};
};

