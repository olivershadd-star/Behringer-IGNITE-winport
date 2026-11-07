/*
 * Copyright (c) - 2022 - MUSIC Tribe, MY
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

#define POPUP_WITHOKCANCEL 1
#define POPUP_WITHOK 2
#define POPUP_BACKUP 3
#define POPUP_RESET 4
#define BACKUP_VIEW 5
#define WARNING_VIEW 5
#define POPUP_WIPEDATA 6
#define POPUP_CHANGEWARNING 7
#define POPUP_POWERCTL 8
#define POPUP_WITHCLOSE 9

/* To enable/disable close button in warning popups */
//#define ENABLE_CLOSEBUTTON

namespace ui
{
	class CommonPopUp : public juce::Component,
		public juce::Button::Listener, private Timer
	{
	public:
		enum backupItemID
		{
			NO_FOCUS = 0,
			SAVE_BACKUP,
			SAVE_BACKUP_USB,
			LOAD_BACKUP,
			LOAD_BACKUP_USB,
			FOCUS_MAX = LOAD_BACKUP_USB
		};

		enum warningItemID
		{
			WARNING_NO_FOCUS = 0,
			CANCEL,
			CONFIRM_SWITCH,
			SAVE_SWITCH,
			WARNING_FOCUS_MAX = SAVE_SWITCH
		};

		enum powerControlItemID
		{
			POWERCTL_WITH_NO_FOCUS = 0,
			PWRCTL_CANCEL,
			POWEROFF,
			REBOOT,
			POWERCTL_FOCUS_MAX = REBOOT
		};

		static CommonPopUp* getCommonPopupInstance()
		{
			static CommonPopUp* getAppObj;
			if (NULL == getAppObj)
			{
				getAppObj = new CommonPopUp();
			}

			return getAppObj;
		}


		uint8_t backupItem[BACKUP_VIEW] = { NO_FOCUS, SAVE_BACKUP, SAVE_BACKUP_USB, LOAD_BACKUP, LOAD_BACKUP_USB};
		uint8_t warningItem[WARNING_VIEW] = { NO_FOCUS, CANCEL, CONFIRM_SWITCH, SAVE_SWITCH };
		uint8_t powerCtlItem[POPUP_POWERCTL] = { NO_FOCUS, PWRCTL_CANCEL, POWEROFF, REBOOT };

		int KeyFocusedItem = backupItemID::NO_FOCUS;
		int WarningFocusedItem = warningItemID::WARNING_NO_FOCUS;
		int powerCtlFocusedItem = powerControlItemID::POWERCTL_FOCUS_MAX;

		std::function<void(int Selection)> onSelectionChanged;
		std::function<void(int Selection)> onActionReturnvalue;
		int popupType = 0;

		CommonPopUp(const juce::String& Title, int Width, int Height);
		CommonPopUp();
		~CommonPopUp();
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		CommonButton* addButton(const String BtnName, const int returnValue);
		CommonButton* addButtonWithBounds(const String BtnName, const int returnValue, ui::Rectangle<int>);
		CommonButton* addButtonNew(const String BtnName, const int returnValue);
		void exitAlert(Button* button);
		void show();
		void setInfoText(String a) { info = a; repaint(); };
		void addProgressBar(double & progress);
		void setProgressBar(double& progress);
		void removeProgressBar();
		CommonImageButton* addImageButton(String BtnName, String defaultImage, String activeImage, const int returnValue);
		CommonImageButton* addImageButtonwithBounds(String BtnName, String defaultImage, String activeImage, String hoverImage, const int returnValue, ui::Rectangle<int>);
		CommonImageButton* addDisabledImageButtonwithBounds(String BtnName, String defaultImage, String activeImage, String hoverImage, const int returnValue,ui::Rectangle<int>);
		void setbtnsize(int w, int h) { btnW = w; btnH = h; };
		void close();
		juce::Atomic<bool> isDialogOpen{ false };
		bool FPKeyHandler(bool isFocuse, paramId_t param, uint32_t KeyValue);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);
		void handleCommandMessage(int id);
		bool isEditing();
		bool IsEditing()
		{
			if ((isDialogOpen.get() == true))
				return true;
			return false;
		};
		void SetControlBtnLine(bool s) { Endline = s; };
		void timerCallback() override;
		void setAutohide(bool s, int timeinMs)
		{
			autohide = s;
			timeinms = timeinMs;
		}
		void setPopUpPropories(const juce::String& Title, int Width, int Height);
		void showPreloader(String Title, String Info);
		void requestforReturnValueCallback() { retValue = true; };
		bool isPreloaderRunning() { return ispreloader; };
		/* To enable/disable close button in popups */
		void isCloseButtonVisible(bool state) { closeBtn.setVisible(false); }

	private:
		juce::FlexBox ctlBox;
		juce::Viewport btnViewPort;
		Array<CommonButton*> listofBtns;
		Array<CommonImageButton*> listofImageBtns;
		juce::Component::SafePointer<juce::DialogWindow> dialogWindow;
		std::unique_ptr<Viewport> view;
		CommonLabel title{ "" };
		int width{ 0 }, height{ 0 };
		String info;
		int btnW{ 50 };
		int btnH{ 50 };
		CommonImageButton closeBtn{ "Close","ico-close.png","ico-close.png" };
		CommonProgressBar* progressBarComp;
		bool newButton = false;
		bool Endline = true;
		int timeinms = 5000;
		bool autohide = false;
		bool isTimerRunning = false;
		bool ispreloader = false;
		bool showCloseBtn = true;
		Image preloaderImage;
		uint8 preloaderCount = 0;
		bool retValue = 0;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CommonPopUp)
	};

	class CommonWarningPopUp : public juce::Component,
		public juce::Button::Listener
	{
	public:
		std::function<void(int Selection)> onSelectionChanged;
		CommonWarningPopUp();
		CommonWarningPopUp(String);
		~CommonWarningPopUp();
		void paint(juce::Graphics& g) override;
		void resized() override;
		void show();
		void close();
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		bool FPKeyHandler(bool isFocuse, paramId_t param, uint32_t KeyValue);
		void handleCommandMessage(int id);
		bool IsEditing()
		{
			if ((isDialogOpen.get() == true))
				return true;
			return false;
		};
		static CommonWarningPopUp* getCommonWarningPopupInstance()
		{
			static CommonWarningPopUp* getAppObj;
			if (NULL == getAppObj)
			{
				getAppObj = new CommonWarningPopUp();
			}

			return getAppObj;
		}

		void setWarningText(String inf);

	private:
		juce::FlexBox ctlBox;
		juce::Viewport btnViewPort;
		CommonLabel title{ "Warning " };
		CommonLabel info{ " " };
		juce::Component::SafePointer<juce::DialogWindow> dialogWindow;
		std::unique_ptr<Viewport> view;
#ifdef ENABLE_CLOSEBUTTON
		CommonImageButton closeBtn{ "Close","ico-close.png","ico-close.png" };
#endif
		CommonImageButton OkayBtn{ "Close","btn-okay-544x44-default.png","btn-okay-544x44-default-hover.png","btn-okay-544x44-default-hover.png" };
		juce::Atomic<bool> isDialogOpen{ false };

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CommonWarningPopUp)
	};

	class CommonInfoWindow : public juce::Component,
		 private Timer
	{
	public:
		CommonInfoWindow();
		~CommonInfoWindow() {};

		static CommonInfoWindow* GetInfoWindowInstance()
		{
			static CommonInfoWindow* GetInstance;
			if (NULL == GetInstance)
			{
				GetInstance = new CommonInfoWindow();
			}

			return GetInstance;
		}

		int minWidth = 180;
		int screenWidth = 1020;
		void setTextandShow(String Text);
		ui::Rectangle<float> InfoBounds;
		String text;
		int time = 3000;
		void paint(juce::Graphics& g) override;
		void timerCallback() override;
		void setInfoBounds(ui::Rectangle<float> b) { InfoBounds = b; };
		void setInfoTime(int t) { time = t; };
	};
};