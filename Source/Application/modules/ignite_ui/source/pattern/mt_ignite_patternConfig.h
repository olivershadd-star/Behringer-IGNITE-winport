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
	class IgniteSculptConfig;

	class IgnitePatternConfig :
		public juce::Component,
		public juce::Button::Listener,
		public IgniteControlOptions::Listener
	{
	public:
#define PATTERN_NO_COM_ROW 3

		IgnitePatternConfig();
		~IgnitePatternConfig() override;

		bool isAutoSaveEnabled() { return autoSavePattern; }
		bool getBarFollowState() { return barFollowBtn.getToggleState(); }
		void updateAccidentals(bool state);
		void updateData();
		bool pannelKeyHandler(paramId_t param, uint32_t keyValue);
		bool getpatternConfigDataUpdateState() { return patternConfigDataUpdated; }
		int getDefaultNote() { return defaultNote; }
		String getPatternInsertPosition() { return insertPosition.getSelectedValue(); }
		void getAssets();
		static IgnitePatternConfig* getAppPatternConfigInstance()
		{
			static IgnitePatternConfig* getAppPatternConfigObj;
			if (NULL == getAppPatternConfigObj)
			{
				getAppPatternConfigObj = new IgnitePatternConfig();
			}

			return getAppPatternConfigObj;
		}
		IgniteControlOptions* _pPatternOptCtl = nullptr;

	private:

#define PATTERN_MENU_VIEW 6
#define PATTERN_OPT_VIEW  6
		enum patternMenuViewItemID
		{
			NO_FOCUS = 0,
			AUTO_SAVE, //Row 1
			BAR_FOLLOW,
			WIPE_PATTERN,
			SCULPT_CONFIG,//Row 2
			INSERT_POSITION,
			FOCUS_MAX = INSERT_POSITION
		};
		enum PATTERNCONFIG_FOCUS
		{
			PATTERNCONFIG_DETAIL,
			PATTERNCONFIG_OPTION,
		};

		enum patternOptionsViewItemID
		{
			OP_NO_FOCUS = 0,
			OPT_UNDO,
			OPT_PATSTEP,
			OPT_PATBAR,
			OPT_PATGRID,
			OP_FOCUS_MAX = OPT_PATGRID
		};

		CommonPopUp* _pPopUpPtr = nullptr;
		IgniteSculptConfig* _pSculptComp = nullptr;

		CommonImageButton autoSaveBtn{ "Auto Save:off","toggle-autosave-default.png","toggle-autosave-active.png","toggle-autosave-hover.png" };
		CommonImageButton barFollowBtn{ "Bar Follow:off","toggle-barfollow-default.png","toggle-barfollow-active.png","toggle-barfollow-default-hover.png" };
		CommonImageButton wipePattern{ "Wipe Unassigned Patterns","btn-wipe-unassinged-default.png","btn-wipe-unassinged-default.png","btn-wipe-unassinged-hover.png" };
		CommonImageButton sculptBtn{ "Sculpt Configuration","btn-sculpt-config-default.png","btn-sculpt-config-default-hover.png","btn-sculpt-config-default-hover.png" };
		CommonListBox insertPosition{ "Insert Position", 1 };

		juce::FlexBox patternMenuBox1;
		juce::FlexBox patternMenuBox2;

		uint8_t optionHandlerFocus = PATTERNCONFIG_DETAIL;
		uint8_t optionsView[PATTERN_OPT_VIEW] = { OP_NO_FOCUS,OPT_UNDO,OPT_PATSTEP,OPT_PATBAR,OPT_PATGRID,INSERT_POSITION };
		uint8_t patternMenuView[PATTERN_MENU_VIEW] = { NO_FOCUS, AUTO_SAVE, BAR_FOLLOW, WIPE_PATTERN, SCULPT_CONFIG, INSERT_POSITION };

		int keyFocusedItem = patternMenuViewItemID::NO_FOCUS;
		int optFocusedItem = OPT_UNDO;
		int defaultNote = 48;
		bool patternConfigDataUpdated = false;
		bool autoSavePattern = false;
		bool barFollow = true;
		bool isAutosave = false;

		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void onOptCtlButtonClicked(IgniteControlOptions::eKey option);
		void pannelSendKey(bool isFocuse, paramId_t param, uint32_t keyValue);
		void mouseUp(const MouseEvent& event) override;
		int isEditing();
		Image imageDefault, imageDefaultHover, imagedisabledImage;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgnitePatternConfig)
	};
};
