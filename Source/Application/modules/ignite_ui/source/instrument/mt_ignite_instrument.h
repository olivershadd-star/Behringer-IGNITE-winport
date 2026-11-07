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
	class AppHome;
	class AppDnp;
	class IgniteInstrumentsRow;
	class IgniteInstrumentOpt;

	class IgniteInstruments :
		public juce::Component,
		public juce::Button::Listener,
		public IgniteControlOptions::Listener,
		public juce::DragAndDropContainer
	{
	public:
		enum INST_FOCUS
		{
			INST_DETAIL,
			INST_LIST,
			INST_OPTION,
		};

		bool instrumentsCreated = false;
		bool instrumentsDataUpdated = false;
		bool move_enable = false;
		bool autoSaveState = false;
		uint8_t option_handler_focus = INST_DETAIL;

		IgniteInstruments();
		~IgniteInstruments() override;
		int getSelected(void);
		void setSelected(int index);
		void changeInstrumentsOptionsVisibility(bool bShouldShow);
		bool isInstrumentsCreated(void) { return(instrumentsCreated); }
		void addInstrument(bool isPatternUpdateneeded);
		void deleteCurrentInstruments();
		void refreshInstrumentsUI();
		void setInstrumentData(mt::Ignite::instrumentsDataIndex item_id, int data, bool is_internal);
		void setInstrumentData(mt::Ignite::instrumentsDataIndex item_id, String data, bool is_internal);
		var getInstrumentData(mt::Ignite::instrumentsDataIndex item_id);
		void onOptCtlButtonClicked(AppOptCtl::pKey option);
		void updateInstrumentsData(uint8_t param, const uint32_t value);
		void updateInstrumentsData(uint8_t param, const std::string& value);
		void setCurrentInstrumentsRow(int value) { curretInstrumentsRow = value; }
		int getCurrentInstrumentsRow() { return curretInstrumentsRow; }
		String getCurrentPort();
		void updateDataFromEngine();
		void requestDataFromEngine(int index);
		void enableControlButton(IgniteControlOptions::eKey key, bool state) { instOptCtr->enableKey(key, state); };
		void moveInstrument(juce::Point<float> position);
		void moveInstrument(int destIndex);
		void updateData();
		void updateInstrEditIndication();
		bool isInstrumentUsed(String instr_name);
		void markAsCvInUse(const String& cvPort);
		void markAsCvFree(const String& cvPort);
		bool isCvUsed(const String& cvPort);
		void markAsChannelInUse(const String& midiport, int channel);
		void markAsChannelFree(const String& midiport, int channel);
		bool isChannelUsed(const String& midiport, int channel);
		void markAsMidiInUse(const String& midiPort);
		void markAsMidiFree(const String& midiPort);
		bool isMidiUsed(const String& midiPort);
		void updateMidiDeviceList();
		void deleteUnassignedInstruments();

		static IgniteInstruments* GetAppInstrumentsInstance()
		{
			static IgniteInstruments* GetAppInstrumentsInstance;
			if (NULL == GetAppInstrumentsInstance)
			{
				GetAppInstrumentsInstance = new IgniteInstruments();
			}

			return GetAppInstrumentsInstance;
		}
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void handleCommandMessage(int id);
		bool PannelKeyOptionsHandler(paramId_t param, uint32_t KeyValue);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		void getAssets();
		int curretInstrumentsRow = 0;
		bool isGlobalAutosaveEnabled() { return isAutosave; };

	private:
#define INST_OPTIONS_VIEW 9
		enum InstOptionsViewItemID
		{
			NO_FOCUS = 0,
			INST_MOVE_DOWN,
			INST_MOVE_UP,
			INST_MOVE_TOP,
			INST_MOVE_LAST,
			INST_MOVE,
			INST_UNDO,
			INST_COPY,
			INST_AUTO_SAVE,
			FOCUS_MAX = INST_AUTO_SAVE
		};

		uint8_t OptionsView[INST_OPTIONS_VIEW] = { NO_FOCUS, INST_MOVE_DOWN, INST_MOVE_UP, INST_MOVE_TOP, INST_MOVE_LAST, INST_MOVE, INST_UNDO, INST_COPY, INST_AUTO_SAVE };
		int KeyFocusedItem = InstOptionsViewItemID::NO_FOCUS;

		IgniteInstrumentOpt* instrOptInstance = nullptr;
		AppDnp* emptyInstrComp = nullptr;
		CommonInfoWindow* _pInfoWindow = nullptr;
		mt::Ignite::instrumentsData prevInstrumentsData{ 0 };
		juce::Viewport view;
		juce::Component container;
		juce::OwnedArray<IgniteInstrumentsRow> list;
		IgniteBottomBar* bottomBarComp = nullptr;
		CommonImageButton addNewInList{ " Add New ","btn-inst-add-default.png","btn-inst-add-active.png","btn-inst-add-default-hover.png"};
		CommonButton addNew{ "" };
		CommonButton addNewSeqButton;
		IgniteControlOptions* instOptCtr = nullptr;
		IgniteCopy* instrumentCopyComp = nullptr;
		IgniteSettings* settingsInstance = nullptr;
		bool globalSettingUpdated = false;
		bool addNewInListHiglited = false;
		int instRowHighLightIndex = 0;
		paramId_t itemParam;
		uint32_t itemKeyValue;
		bool itemFocus = false;
		AppOptions* appOptPtr = nullptr;
		CommonPopUp* popupPtr = nullptr;
		CommonWarningPopUp* warnPopupPtr = nullptr;
		std::unordered_map<String, bool> cvUseList;
		std::unordered_map<String, bool> midiUseList;
		std::unordered_map<String, bool[16]> channelUseList;
		Image imageAddInstActive, imageAddInstDefault, imageAddInstHover;
		bool isAutosave = false;

		void cleanup();
		void populate();
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void paint(juce::Graphics& g) override;
		void resized() override;
		void showPopup(int index);
		int selected{ 0 };
		int prevSelected{ 0 };
		void updateLables();
		String getInstrName();
		void onOptCtlButtonClicked(IgniteControlOptions::eKey option) override;
		void copyInstrument(IgniteCopy::copyCtlKey key, String copyName);
		void addCvToUseList(const String& cvPort);
		void addChannelToUseList(const String& midiport, int channel);
		void addMidiToUseList(const String& midiPort);
		void removeCvFromUseList(const String& cvPort);


		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteInstruments)
	};


	class IgniteInstrumentsRow :
		public juce::Component,
		public CommonLabel::Listener,
		public CommonButton::Listener
	{
	public:
		IgniteInstrumentsRow(int SerialNumber, mt::Ignite::instrumentsData& Data, IgniteInstruments* ownerptr);
		~IgniteInstrumentsRow();
		std::function<void(IgniteInstrumentsRow*)> onMouseDown;

		void highlight(bool state);
		int getSerialNumber();
		void refreshInstrumentsRowUI();
		void showInstrumentsView();
		void updateEditIndication();
		void SetFocus(bool hasFocus, bool activeHasFocus);
		void setColor(int colourID, Colour colour);
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		bool isEditing() { return name.isEditing; }
		void getAssets();
	private:
		IgniteInstruments* _pInstruments = nullptr;
		mt::Ignite::instrumentsData& instrumentsdata;
		juce::FlexBox box;
		int serialNo;
		bool rowIsBeingDraggedOver = false;
		String serialNumber = "1";

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
		Image imageActive, imageDefault, imageActiveHover, imageDefaultHover;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteInstrumentsRow)
	};
};
