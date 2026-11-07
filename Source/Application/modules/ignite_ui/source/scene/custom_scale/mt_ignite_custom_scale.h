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
	class AppDnp;
	class IgniteCustomScaleRow;
	class IgniteCustomScaleOpt;

	class IgniteCustomScale :
		public juce::Component,
		public juce::Button::Listener,
		public IgniteControlOptions::Listener,
		public juce::DragAndDropContainer
	{
	public:
		enum UDS_FOCUS
		{
			UDS_DETAIL,
			UDS_LIST,
			UDS_OPTION,
		};

		CommonPopUp* _pPopupPtr = nullptr;

		IgniteCustomScale();
		~IgniteCustomScale() override;

		var getCustomScaleData(mt::Ignite::customScaleDataIndex itemId);
		int8_t getOptionHandlerState() { return optionHandlerEnabled; }
		bool getCustomScaleDataUpdateStatus() { return customScaleDataUpdated; }
		bool getAutoSaveStatus() { return autoSaveState; }
		bool getMoveEnableStatus() { return moveEnabled; }
		int getCurrentCustomScaleRow() { return curretCustomScaleRow; }

		void setCustomScaleData(mt::Ignite::customScaleDataIndex itemId, int8 data, bool isInternal);
		void setCustomScaleData(mt::Ignite::customScaleDataIndex itemId, String data, bool isInternal);
		void setCustomScaleDataUpdateStatus(bool state) { customScaleDataUpdated = state; }
		void setCurrentCustomScaleRow(int value) { curretCustomScaleRow = value; }

		void updateScaleEditIndication();
		void enableControlButton(IgniteControlOptions::eKey key, bool state) { _pScaleOptCtr->enableKey(key, state); };
		void changeCustomScaleOptionsVisibility(bool bShouldShow);
		bool pannelKeyHandler(paramId_t param, uint32_t keyValue);
		bool checkValidScaleSequence();
		int getSelected(void);

		static IgniteCustomScale* getAppCustomScaleInstance()
		{
			static IgniteCustomScale* customScaleInstance;
			if (NULL == customScaleInstance)
			{
				customScaleInstance = new IgniteCustomScale();
			}

			return customScaleInstance;
		}

	private:
#define UDS_OPTIONS_VIEW 2

		bool customScaleCreated = false;
		bool customScaleDataUpdated = false;
		bool moveEnabled = false;
		bool autoSaveState = false;
		bool bootup = true;
		int curretCustomScaleRow = 0;
		uint8_t optionHandlerEnabled = UDS_DETAIL;

		enum OptionsViewItemID
		{
			NO_FOCUS = 0,
			UDS_UNDO,
			FOCUS_MAX = UDS_UNDO
		};

		uint8_t OptionsView[UDS_OPTIONS_VIEW] = { NO_FOCUS, UDS_UNDO };
		int keyFocusedItem = OptionsViewItemID::NO_FOCUS;
		bool itemFocus = false;
		paramId_t itemParam;
		uint32_t itemKeyValue;

		IgniteCustomScaleOpt* _pScaleOptInstance = nullptr;
		AppDnp* _pEmptyScaleComp = nullptr;
		IgniteBottomBar* _pBottomBarComp = nullptr;
		IgniteControlOptions* _pScaleOptCtr = nullptr;

		mt::Ignite::customScaleData prevCustomScaleData{ 0 };
		juce::Viewport view;
		juce::Component container;
		juce::OwnedArray<IgniteCustomScaleRow> list;
		CommonImageButton addNewInList{ " Add New ","btn-uds-add-default.png","btn-uds-add-active.png","btn-uds-add-default-hover.png" };
		CommonButton addNew{ "" };
		CommonButton addNewSeqButton;
		bool globalSettingUpdated = false;
		int UdsRowHighLightIndex = 0;
		bool addNewInListHiglited = false;
		bool KeyFocusOnRow = false;
		paramId_t paramt;
		uint32_t KeyValuet;

		void cleanup();
		void populate();
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void paint(juce::Graphics& g) override;
		void resized() override;
		void showPopup(int index);
		int selected{ 0 };
		int prevSelected{ 0 };
		void updateLables();
		String getScaleName();
		void onOptCtlButtonClicked(IgniteControlOptions::eKey option) override;
		void requestDataFromEngine(int index);
		void addCustomScale(bool isScaleUpdateneeded);
		bool isCustomScaleCreated(void) { return(customScaleCreated); }
		void deleteCurrentCustomScale();
		void refreshCustomScaleUI();
		void onOptCtlButtonClicked(AppOptCtl::pKey option);
		void handleCommandMessage(int id);
		bool pannelKeyOptionsHandler(paramId_t param, uint32_t KeyValue);
		void pannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);

		void updateDataFromEngine();
		void updateCustomScaleData(uint8_t param, const uint32_t value);
		void updateCustomScaleData(uint8_t param, const std::string& value);
		void updateData();
		void setSelected(int index);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteCustomScale)
	};


	class IgniteCustomScaleRow :
		public juce::Component,
		public CommonLabel::Listener,
		public CommonButton::Listener
	{
	public:
		IgniteCustomScaleRow(int SerialNumber, mt::Ignite::customScaleData& Data, IgniteCustomScale* ownerptr);
		~IgniteCustomScaleRow();
		std::function<void(IgniteCustomScaleRow*)> onMouseDown;

		void highlight(bool state);
		int getSerialNumber();
		void refreshCustomScaleRowUI();
		void showCustomScaleView();
		void updateEditIndication();
		void setColor(int colourID, Colour colour);
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		bool isEditing() { return name.isEditing; }
		void SetFocus(bool hasFocus, bool activeHasFocus);

	private:
		IgniteCustomScale* _pCustomScale = nullptr;
		mt::Ignite::customScaleData& customScaledata;
		juce::FlexBox box;
		int serialNo;
		bool rowIsBeingDraggedOver = false;

		CommonSerialNumber srNo{ "1" };
		CommonKey name{ "" };
		CommonLabel port{ "PORT", "1" }, channel{ "CHANNEL", "1" };
		CommonImageButton options{ "Options", "Edit.png" };
		Image normalImage;
		Image activeImage;
		void paint(juce::Graphics& g) override;
		void resized() override;
		void mouseDown(const MouseEvent& event) override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void labelTextChanged(Label* labelThatHasChanged) override;
		void mouseUp(const MouseEvent& event) override;
		void mouseDrag(const MouseEvent& event) override;
		void mouseMove(const MouseEvent& event) override;
		void mouseExit(const MouseEvent& event) override;
		bool isHighlighted{ false };
		bool isMouseOver{ false };

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteCustomScaleRow)
	};
};
