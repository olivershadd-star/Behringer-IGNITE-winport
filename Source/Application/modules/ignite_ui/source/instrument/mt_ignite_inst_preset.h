/*
* Copyright (c) - 2024 - MUSIC Tribe, MY.
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
	class IgniteInstruments;
	class InstrumentPreset : public juce::Component,
		public CommonButton::Listener
	{
	public:
		InstrumentPreset(IgniteInstruments* iPtr);
		~InstrumentPreset() override;
		void setPresetGroup(int groupIndex = 0);
		bool pannelKeyHandler(paramId_t param, uint32_t keyValue);
		void refreshData();
		void getAssets();

	private:
#define INSTR_PRESET_VIEW 9
		enum stepLengthViewItemID
		{
			NO_FOCUS = 0,
			KEY_HOLD,
			KEY_STEP,
			KEY_STEP_DEC,
			KEY_STEP_INC,
			KEY_TICK_DEC,
			KEY_TIC_INC,
			KEY_CANCEL,
			KEY_APPLY,
			FOCUS_MAX = KEY_APPLY
		};

		uint8_t stepLengthView[INSTR_PRESET_VIEW] = { NO_FOCUS, KEY_HOLD, KEY_STEP, KEY_STEP_DEC, KEY_STEP_INC, KEY_TICK_DEC, KEY_TIC_INC, KEY_CANCEL, KEY_APPLY };
		int keyFocusedItem = stepLengthViewItemID::NO_FOCUS;
		int currentPresetGroup = 0;

		FrountPannel* FrountPannelRef = nullptr;

		CommonToggleButton presetGroupLable{ "Piano" };
		Array<String> presetGroupName;
		CommonToggleButton preset1{ " " };
		CommonToggleButton preset2{ "" };
		CommonToggleButton preset3{ "" };
		CommonToggleButton preset4{ "" };
		CommonToggleButton preset5{ "" };
		CommonToggleButton preset6{ "" };
		CommonToggleButton preset7{ "" };
		CommonToggleButton preset8{ "" };
		CommonToggleButton preset9{ "" };
		CommonToggleButton preset10{ "" };
		CommonToggleButton preset11{ "" };
		CommonToggleButton preset12{ "" };
		CommonToggleButton preset13{ "" };
		CommonToggleButton preset14{ "" };
		CommonToggleButton preset15{ "" };
		CommonToggleButton preset16{ "" };
		CommonButton prevPresetGroupButton;
		CommonButton presetGroupButton{ "Piano" };
		CommonButton nextPresetGroupButton;

		CommonLabel	presetTitle{ "Presets" };

		CommonImageButton closeBtn{ "Close","ico-close.png","ico-close.png" };
		Image modelContainer, presetBgd, presetItemDefault, presetItemActive, presetItemDefaultHover, presetItemActiveHover,
			presetItemDisabled, presetLeftCaretDefault, presetLeftCaretHover, presetLeftCaretDisabled,
			presetRightCaretDefault, presetRightCaretHover, presetRightCaretDisabled, devider;

		IgniteInstruments* instrPtr = nullptr;
		bool dontLoadAtBootup = false;
		void resized() override;
		void paint(juce::Graphics& g) override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void pannelSendKey(bool isFocuse, paramId_t param, uint32_t keyValue);
		void sendPreset(int presetIndex, bool sendToEngine = true);
		void loadPresets(int presetGroup);
		void setPresetButton(int index);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InstrumentPreset)
	};
}