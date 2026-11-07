/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.8

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once
namespace ui
{
	class IgniteInstruments;
	class IgniteRecord;
	class IgniteSettings;
	class IgniteSongConfig;
	class IgniteSceneConfig;
	class IgniteTrackConfig;
	class IgnitePatternConfig;
	class IgniteCvio;
	class IgniteMidiConfig;
	class IgniteCalibration;
	class AppMenu;
	class AppOptions;
	class IgniteControlOptions;

	class MenuMode : public juce::Component,
		public CommonLabel::Listener,
		public juce::Button::Listener
	{
	public:
		MenuMode();
		~MenuMode();
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void labelTextChanged(Label* labelThatHasChanged) override;
		void setHeader(const String& name);
		void setJustification(Justification type);
		std::function<void(int btn)> onBackbtnpress;
		static MenuMode* GetMenuModeInstance()
		{
			static MenuMode* GetMenuMode;
			if (NULL == GetMenuMode)
			{
				GetMenuMode = new MenuMode();
			}

			return GetMenuMode;
		}
	private:
		juce::FlexBox box;
		CommonImageButton back{ " Back ", "back-default.png","back-active.png","back-default-hover.png" };
		CommonLabel header{ "" };
		CommonInfoWindow* _pInfoWindow = nullptr;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MenuMode)
	};

	class AppMenuOptions : public juce::Component,
		public juce::Button::Listener
	{
	public:
#define MENU_VIEW 10
#define MENU_ROW_ITEMS 3
		enum menusViewItemID
		{
			NO_FOCUS = 0,
			INSTRUMENT, //Row 1
			MIDI_CONFIG,
			CVIO_CONFIG,
			SONG,
			SCENE,
			TRACK,
			PATTERN, //Row 2
			RECORD, // Row 3
			SETTINGS,
			FOCUS_MAX = SETTINGS
		};
		uint8_t menusView[MENU_VIEW] = { NO_FOCUS, INSTRUMENT, MIDI_CONFIG, CVIO_CONFIG, SONG, SCENE, TRACK, PATTERN, RECORD, SETTINGS };
		int KeyFocusedItem = menusViewItemID::NO_FOCUS;

		AppMenuOptions(AppMenu* parentPtr);
		~AppMenuOptions() override;

		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void changeMenuWindowState(juce::Button* btn, bool state);
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue);

	private:
		AppMenu* menuPtr;
		MenuMode* menuModeptr;
		CommonImageButton browser{ "Browse","browse-default.png","browse-active.png" };
		CommonImageButton instrumentButton{ "Instruments","link-instrument-default.png","link-instrument-active.png","link-instrument-active.png" };
		CommonImageButton songButton{ "Song","link-song-default.png","link-song-active.png","link-song-active.png"};
		CommonImageButton sceneButton{ "Scene","link-scene-default.png","link-scene-active.png","link-scene-active.png"};

		CommonImageButton patternButton{ "Pattern","link-pattern-default.png","link-pattern-active.png","link-pattern-active.png"};
		CommonImageButton trackButton{ "Track","link-track-default.png","link-track-active.png","link-track-active.png" };
		CommonImageButton midiConfigButton{ "MIDI Config","link-midiconfig-default.png","link-midiconfig-active.png","link-midiconfig-active.png" };
		CommonImageButton cvioButton{ "CVIO Config","link-cvioconfig-default.png","link-cvioconfig-active.png","link-cvioconfig-active.png" };

		CommonImageButton drumButton{ "DRUM Config","drumconfig-default.png","drumconfig-active.png" };
		CommonImageButton calibrationButton{ "Calibration","calibration-default.png","calibration-active.png" };
		CommonImageButton recordButton{ "Record","link-record-default.png","link-record-active.png","link-record-active.png"};
		CommonImageButton settingsButton{ "Settings","link-settings-default.png","link-settings-active.png","link-settings-active.png"};

		juce::FlexBox box, r1, r2, r3, r4;
		AppOptions* optionptr = nullptr;
		Button* activeBtnptr;
		void mouseDown(const MouseEvent& event) override ;
		//==============================================================================
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AppMenuOptions)
	};

	class AppMenu : public juce::Component
	{
	public:

		enum class MENU_WINDOWS
		{
			MENU_WINDOW,
			BROWSE_WINDOW,
			INSTR_WINDOW,
			SONG_WINDOW,
			SCENE_WINDOW,
			PATTERN_WINDOW,
			TRACK_WINDOW,
			MIDI_WINDOW,
			CVIO_WINDOW,
			DRUM_WINDOW,
			CALIB_WINDOW,
			RECORD_WINDOW,
			SETTING_WINDOW,
			MISC_SETTING_WINDOW,
			UDS_WINDOWS,
			DISABLE_ALL_WINDOW,
		};

		AppMenu();
		~AppMenu();
		void resized() override;
		void setAllMenuCompInVisible();
		void changeMenuOptionsVisibilty(MENU_WINDOWS index);
		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		MENU_WINDOWS currentIndex = MENU_WINDOWS::DISABLE_ALL_WINDOW;

		static AppMenu* GetAppMenuInstance()
		{
			static AppMenu* GetMenuInstance;
			if (NULL == GetMenuInstance)
			{
				GetMenuInstance = new AppMenu();
			}

			return GetMenuInstance;
		}

	private:
		IgniteInstruments* instrInstance = nullptr;
		IgniteSongConfig* songInstance = nullptr;
		IgniteSceneConfig* sceneInstance = nullptr;
		IgniteTrackConfig* trackInstance = nullptr;
		IgnitePatternConfig* patternInstance = nullptr;
		IgniteRecord* recordInstance = nullptr;
		IgniteCvio* cvioInstance = nullptr;
		IgniteMidiConfig* midiConfigInstance = nullptr;
		IgniteSettings* settingsInstance = nullptr;
		IgniteCalibration* calibInstance = nullptr;
		MenuMode* menuModeInstance;
		AppMenuOptions* menuOptions;
		AppOptions* optionptr = nullptr;
		IgniteControlOptions* menuOptCtl = nullptr;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AppMenu)
	};
};