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

namespace ui
{
	AppOptCtl::AppOptCtl(bool BACK, bool SAVE, bool DEL, bool COPY, bool MOVE)
	{
		backButton = BACK;
		saveButton = SAVE;
		delButton = DEL;
		copyButton = COPY;
		moveButton = MOVE;

		optionBack.makeVisibleAndAddListner(this);
		optionSave.makeVisibleAndAddListner(this);
		optionCopy.makeVisibleAndAddListner(this);
		optionMove.makeVisibleAndAddListner(this);
		rowDelete.makeVisibleAndAddListner(this);

		optionBack.showTitleAndBorder(true);
		optionSave.showTitleAndBorder(true);
		optionCopy.showTitleAndBorder(true);
		optionMove.showTitleAndBorder(true);
		rowDelete.showTitleAndBorder(true);
		updateButtons();
	}

	AppOptCtl::~AppOptCtl()
	{

	}

	void AppOptCtl::updateButtons()
	{
		ctlBox.items.clear();
		if (backButton)
			ctlBox.items.add(FlexItem(optionBack).withMargin(5).withFlex(1));
		if (saveButton)
			ctlBox.items.add(FlexItem(optionSave).withMargin(5).withFlex(1));
		if (copyButton)
			ctlBox.items.add(FlexItem(optionCopy).withMargin(5).withFlex(1));
		if (moveButton)
			ctlBox.items.add(FlexItem(optionMove).withMargin(5).withFlex(1));
		if (delButton)
			ctlBox.items.add(FlexItem(rowDelete).withMargin(5).withFlex(1));
	}

	void AppOptCtl::setButtonName(pKey key, String new_name)
	{
		switch (key)
		{
		case  pKey::BACK:
			optionBack.setButtonText(new_name);
			break;
		case  pKey::SAVE:
			optionSave.setButtonText(new_name);
			break;
		case  pKey::DEL:
			rowDelete.setButtonText(new_name);
			break;
		case  pKey::COPY:
			optionCopy.setButtonText(new_name);
			break;
		case  pKey::MOVE:
			optionMove.setButtonText(new_name);
			break;
		}
	}

	void AppOptCtl::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		auto selectedKey = pKey::BACK;

		if (buttonThatWasClicked == &optionBack)
		{
			selectedKey = pKey::BACK;
		}
		else if (buttonThatWasClicked == &optionSave)
		{
			selectedKey = pKey::SAVE;
		}
		else if (buttonThatWasClicked == &optionCopy)
		{
			selectedKey = pKey::COPY;
		}
		else if (buttonThatWasClicked == &optionMove)
		{
			selectedKey = pKey::MOVE;
		}
		else if (buttonThatWasClicked == &rowDelete)
		{
			selectedKey = pKey::DEL;
		}
		if (onButtonPressed)
			onButtonPressed(selectedKey);
	}

	void AppOptCtl::paint(juce::Graphics& g)
	{
		g.setColour(Theme::Instance().getColour(neutralGrey1));
		g.fillAll();
	}

	void AppOptCtl::resized()
	{
		ctlBox.performLayout(getLocalBounds().reduced(5));
	}

	AppOptions::AppOptions()
	{

		optionCopy.makeVisibleAndAddListner(this);
		optionMove.makeVisibleAndAddListner(this);
		optionUndo.makeVisibleAndAddListner(this);
		optionloop.makeVisibleAndAddListner(this);
		optionConfig.makeVisibleAndAddListner(this);
		movetoTop.makeVisibleAndAddListner(this);
		movetoLast.makeVisibleAndAddListner(this);
		movetoDown.makeVisibleAndAddListner(this);
		movetoUp.makeVisibleAndAddListner(this);
		autoSave.makeVisibleAndAddListner(this);
		SongList.makeVisibleAndAddListner(this);
		SceneList.makeVisibleAndAddListner(this);
		TrackView.makeVisibleAndAddListner(this);
		PatternStep.makeVisibleAndAddListner(this);
		PatternBar.makeVisibleAndAddListner(this);
		PatternGrid.makeVisibleAndAddListner(this);
		midiGlobal.makeVisibleAndAddListner(this);
		midiSong.makeVisibleAndAddListner(this);
		songSettingActive.makeVisibleAndAddListner(this);
		songSettingGlobal.makeVisibleAndAddListner(this);
		cvioGlobal.makeVisibleAndAddListner(this);
		cvioSong.makeVisibleAndAddListner(this);
		songMidiConfig.makeVisibleAndAddListner(this);
		songCvioConfig.makeVisibleAndAddListner(this);
		btnInstrument.makeVisibleAndAddListner(this);
		btnPattern.makeVisibleAndAddListner(this);
		altFunBtn.makeVisibleAndAddListner(this);
		trackCtlBtn.makeVisibleAndAddListner(this);

		optionCopy.setDisableImage("btn-copy-disabled.png");
		optionUndo.setDisableImage("btn-undo-disabled.png");
		optionloop.setDisableImage("btn-loop-disabled.png");

		movetoUp.setDisableImage("btn-move1up-disabled.png");
		movetoUp.sethoverImages("btn-move1up-default-hover.png", "btn-move1up-active-hover.png", "btn-move1up-disabled-hover.png");
		movetoDown.setDisableImage("btn-move1down-disabled.png");
		movetoDown.sethoverImages("btn-move1down-default-hover.png", "btn-move1down-active-hover.png", "btn-move1down-disabled-hover.png");
		movetoLast.setDisableImage("btn-movetobottom-disabled.png");
		movetoLast.sethoverImages("btn-movetobottom-default-hover.png", "btn-movetobottom-active-hover.png", "btn-movetobottom-disabled-hover.png");
		movetoTop.setDisableImage("btn-movetotop-disabled.png");
		movetoTop.sethoverImages("btn-movetotop-default-hover.png", "btn-movetotop-active-hover.png", "btn-movetotop-disabled-hover.png");
		optionMove.setDisableImage("btn-move-disabled.png");
		optionMove.sethoverImages("btn-move-default-hover.png", "btn-move-active-hover.png", "btn-move-disabled-hover.png");
		optionloop.setDisableImage("btn-loop-disabled.png");
		optionloop.sethoverImages("btn-loop-default-hover.png", "btn-loop-active-hover.png", "btn-loop-disabled-hover.png");
		autoSave.setDisableImage("btn-autosave-disabled.png");
		autoSave.sethoverImages("btn-autosave-default-hover.png", "btn-autosave-active-hover.png", "btn-autosave-disabled-hover.png");
		songSettingGlobal.setDisableImage("btn-defaultsetting-disabled.png");
		songSettingGlobal.sethoverImages("btn-defaultsetting-default-hover.png", "btn-defaultsetting-active-hover.png", "btn-defaultsetting-disabled-hover.png");
		songSettingActive.setDisableImage("btn-activesong-disabled.png");
		songSettingActive.sethoverImages("btn-activesong-default-hover.png", "btn-activesong-active-hover.png", "btn-activesong-disabled-hover.png");
		midiGlobal.setDisableImage("btn-defaultsetting-disabled.png");
		midiGlobal.sethoverImages("btn-defaultsetting-default-hover.png", "btn-defaultsetting-active-hover.png", "btn-defaultsetting-disabled-hover.png");
		midiSong.setDisableImage("btn-activesong-disabled.png");
		midiSong.sethoverImages("btn-activesong-default-hover.png", "btn-activesong-active-hover.png", "btn-activesong-disabled-hover.png");
		cvioGlobal.setDisableImage("btn-defaultsetting-disabled.png");
		cvioGlobal.sethoverImages("btn-defaultsetting-default-hover.png", "btn-defaultsetting-active-hover.png", "btn-defaultsetting-disabled-hover.png");
		cvioSong.setDisableImage("btn-activesong-disabled.png");
		cvioSong.sethoverImages("btn-activesong-default-hover.png", "btn-activesong-active-hover.png", "btn-activesong-disabled-hover.png");
		altFunBtn.setDisableImage("btn-altfn-disabled.png");
		altFunBtn.sethoverImages("btn-altfn-default-hover.png", "btn-altfn-active-hover.png", "btn-altfn-disabled-hover.png");
		trackCtlBtn.setDisableImage("btn-extcc-default.png");
		trackCtlBtn.sethoverImages("btn-extcc-default-hover.png", "btn-altfn-active-hover.png", "btn-extcc-active-hover.png");

		optionMove.setClickingTogglesState(false);
		optionMove.setToggleable(true);
		optionMove.setToggleState(false, dontSendNotification);

		trackCtlBtn.setClickingTogglesState(false);
		trackCtlBtn.setToggleable(true);
		trackCtlBtn.setToggleState(false, dontSendNotification);

		altFunBtn.setClickingTogglesState(false);
		altFunBtn.setToggleable(true);
		altFunBtn.setToggleState(false, dontSendNotification);

		movetoTop.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		movetoLast.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		movetoDown.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		movetoUp.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		optionCopy.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		optionMove.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		optionUndo.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		optionloop.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		autoSave.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		//FillMode.setLookAndFeel(songSettingGlobal::getLnf());

		midiGlobal.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		midiSong.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		songSettingGlobal.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		songSettingActive.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		cvioGlobal.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		cvioSong.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		altFunBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		trackCtlBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());

		ctlBox.items.add(FlexItem(optionMove).withFlex(1));
		ctlBox.items.add(FlexItem(optionloop).withFlex(1));
		ctlBox.items.add(FlexItem(optionUndo).withFlex(1));
		ctlBox.items.add(FlexItem(optionCopy).withFlex(1));
		ctlBox.items.add(FlexItem(optionConfig).withFlex(1));
		enableKey(IgniteControlOptions::eKey::ALL, false);

		movetoTop.setVisible(false);
		movetoLast.setVisible(false);
		movetoUp.setVisible(false);
		movetoDown.setVisible(false);

		moveBox.items.add(FlexItem(movetoDown).withFlex(1));
		moveBox.items.add(FlexItem(movetoUp).withFlex(1));
		moveBox.items.add(FlexItem(movetoTop).withFlex(1));
		moveBox.items.add(FlexItem(movetoLast).withFlex(1));
		SongList.setVisible(false);
		SceneList.setVisible(false);
		PatternStep.setVisible(false);
		PatternBar.setVisible(false);
		PatternGrid.setVisible(false);
		midiGlobal.setVisible(false);
		midiSong.setVisible(false);
		songSettingGlobal.setVisible(false);
		songSettingActive.setVisible(false);
		cvioGlobal.setVisible(false);
		cvioSong.setVisible(false);
		songMidiConfig.setVisible(false);
		songCvioConfig.setVisible(false);
		midiGlobal.setToggleable(true);
		midiSong.setToggleable(true);
		songSettingGlobal.setToggleable(true);
		songSettingActive.setToggleable(true);
		cvioGlobal.setToggleable(true);
		cvioSong.setToggleable(true);
	}

	void AppOptions::paint(juce::Graphics& g)
	{
	}

	void AppOptions::resized()
	{
	}

	void AppOptions::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (optCntPtr == nullptr)
			optCntPtr = IgniteControlOptions::GetAppOptInstance();

		if (buttonThatWasClicked == &optionMove)
		{
			if (optionMove.getToggleState())
				optionMove.setToggleState(false, dontSendNotification);
			else
				optionMove.setToggleState(true, dontSendNotification);
			optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::MOVE);
		}
		else if (buttonThatWasClicked == &optionCopy)
		{
			if (optionCopy.getToggleState())
				optionCopy.setToggleState(false, dontSendNotification);
			optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::COPY);
		}
		else if (buttonThatWasClicked == &optionUndo)
		{
			if (optionUndo.getToggleState())
				optionUndo.setToggleState(false, dontSendNotification);
			optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::UNDO);
		}
		else if (buttonThatWasClicked == &optionloop)
		{
			if (optionloop.getToggleState())
				optionloop.setToggleState(false, dontSendNotification);
			optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::LOOP);
		}
		else if (buttonThatWasClicked == &optionConfig)
		{
			if (optionConfig.getToggleState())
				optionConfig.setToggleState(false, dontSendNotification);
			optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::CONFIG);
		}
		else if (buttonThatWasClicked == &movetoTop)
		{
			if (movetoTop.getToggleState())
				movetoTop.setToggleState(false, dontSendNotification);
			optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::MOVETOP);
		}
		else if (buttonThatWasClicked == &movetoLast)
		{
			if (movetoLast.getToggleState())
				movetoLast.setToggleState(false, dontSendNotification);
			optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::MOVEBTM);
		}
		else if (buttonThatWasClicked == &movetoDown)
		{
			if (movetoDown.getToggleState())
				movetoDown.setToggleState(false, dontSendNotification);
			optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::MOVEDOWN);
		}
		else if (buttonThatWasClicked == &movetoUp)
		{
			if (movetoUp.getToggleState())
				movetoUp.setToggleState(false, dontSendNotification);
			optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::MOVEUP);
		}
		else if (buttonThatWasClicked == &autoSave)
		{
			optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::AUTOSAVE);
		}
		else if (buttonThatWasClicked == &SongList)
		{
			optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::SONGLIST);
			if (SongList.getToggleState())
				SongList.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &SceneList)
		{
			optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::SCENELIST);
			if (SceneList.getToggleState())
				SceneList.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &TrackView)
		{
			optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::TRACKVIEW);
			if (TrackView.getToggleState())
				TrackView.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &PatternStep)
		{
			optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::PATSTEP);
			if (PatternStep.getToggleState())
				PatternStep.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &PatternBar)
		{
			optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::PATBAR);
			if (PatternBar.getToggleState())
				PatternBar.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &PatternGrid)
		{
			optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::PATGRID);
			if (PatternGrid.getToggleState())
				PatternGrid.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &midiGlobal)
		{
			if (midiGlobal.getToggleState())
				optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::MIDI_GLOBAL);
			else
				midiSong.setToggleState(true, sendNotification);
		}
		else if (buttonThatWasClicked == &midiSong)
		{
			if (midiSong.getToggleState())
				optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::MIDI_SONG);
			else
				midiGlobal.setToggleState(true, sendNotification);
		}
		else if (buttonThatWasClicked == &cvioGlobal)
		{
			if (cvioGlobal.getToggleState())
				optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::CV_GLOBAL);
			else
				cvioSong.setToggleState(true, sendNotification);
		}
		else if (buttonThatWasClicked == &cvioSong)
		{
			if (cvioSong.getToggleState())
				optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::CV_SONG);
			else
				cvioGlobal.setToggleState(true, sendNotification);
		}
		else if (buttonThatWasClicked == &songSettingGlobal)
		{
			if (songSettingGlobal.getToggleState())
			{
				optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::SONG_SETTING_GLOBAL);
				songSettingActive.setToggleState(false, dontSendNotification);
			}
			else
				songSettingActive.setToggleState(true, sendNotification);
		}
		else if (buttonThatWasClicked == &songSettingActive)
		{
			if (songSettingActive.getToggleState())
			{
				optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::SONG_SETTING_ACTIVE);
				songSettingGlobal.setToggleState(false, dontSendNotification);
			}
			else
				songSettingGlobal.setToggleState(true, sendNotification);
		}
		else if (buttonThatWasClicked == &songMidiConfig)
		{
			optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::MIDI_SONG_CONFIG);
			if (songMidiConfig.getToggleState())
				songMidiConfig.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &songCvioConfig)
		{
			optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::CVIO_SONG_CONFIG);
			if (songCvioConfig.getToggleState())
				songCvioConfig.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &btnPattern)
		{
			optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::PATTERN);
			if (btnPattern.getToggleState())
				btnPattern.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &btnInstrument)
		{
			optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::INST);
			if (btnInstrument.getToggleState())
				btnInstrument.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &altFunBtn)
		{
			altFunBtn.setToggleState(true, sendNotification);
			if (altFunBtn.getToggleState())
				altFunBtn.setToggleState(false, dontSendNotification);
			else
				altFunBtn.setToggleState(true, dontSendNotification);
			optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::ALT_FN);
		}
		else if (buttonThatWasClicked == &trackCtlBtn)
		{
			trackCtlBtn.setToggleState(true, sendNotification);
			if (trackCtlBtn.getToggleState())
				changebtnstate(ui::IgniteControlOptions::TRACK_CTL, false);
			else
				changebtnstate(ui::IgniteControlOptions::TRACK_CTL, true);
			optCntPtr->onCtrlOptnClick(IgniteControlOptions::eKey::TRACK_CTL);
		}
	}

	void AppOptions::showOptions(bool state)
	{
		setVisible(state);
		this->toFront(state);
	}

	void AppOptions::enableKey(IgniteControlOptions::eKey option, bool state)
	{
		switch (option)
		{
		case IgniteControlOptions::eKey::UNDO:
			optionUndo.setEnabled(state);
			break;
		case IgniteControlOptions::eKey::COPY:
			optionCopy.setEnabled(state);
			break;
		case IgniteControlOptions::eKey::MOVE:
			optionMove.setEnabled(state);
			break;
		case IgniteControlOptions::eKey::LOOP:
			optionloop.setEnabled(state);
			break;
		case IgniteControlOptions::eKey::CONFIG:
			optionConfig.setEnabled(state);
			break;
		case IgniteControlOptions::eKey::AUTOSAVE:
			autoSave.setEnabled(state);
			break;
		case IgniteControlOptions::eKey::ALL:
			optionloop.setEnabled(state);
			optionUndo.setEnabled(state);
			optionCopy.setEnabled(state);
			optionMove.setEnabled(state);
			break;
		}
	}

	void AppOptions::setView(bool loop, bool copy, bool move, bool undo, bool Config, bool autosave)
	{
		ctlBox.items.clear();
		ctlBox.flexDirection = FlexBox::Direction::row;

		if (move)
		{
			optionMove.setVisible(true);
			ctlBox.items.add(FlexItem(optionMove).withFlex(1));
		}
		else
			optionMove.setVisible(false);

		if (loop)
		{
			optionloop.setVisible(true);
			ctlBox.items.add(FlexItem(optionloop).withFlex(1));
		}
		else
			optionloop.setVisible(false);

		if (undo)
		{
			optionUndo.setVisible(true);
			ctlBox.items.add(FlexItem(optionUndo).withFlex(1));
		}
		else
			optionUndo.setVisible(false);


		if (copy)
		{
			optionCopy.setVisible(true);
			ctlBox.items.add(FlexItem(optionCopy).withFlex(1));
		}
		else
			optionCopy.setVisible(false);

		if (Config)
		{
			optionConfig.setVisible(true);
			ctlBox.items.add(FlexItem(optionConfig).withFlex(1).withWidth(60));
		}
		else
			optionConfig.setVisible(false);

		if (autosave)
		{
			autoSave.setVisible(true);
			ctlBox.items.add(FlexItem(autoSave).withFlex(1).withWidth(75));
		}
		else
			autoSave.setVisible(false);
		resized();
	}

	void AppOptions::taboptionChanges(mt::Ignite::tabs t, int subtab)
	{
		DBG(String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "Resetting option btns(move,copy,delete etc) components");
		if (appPatternComp == nullptr || appSongComp == nullptr || appSceneComp == nullptr || appTrackComp == nullptr || appInstrComp == nullptr)
		{
			appPatternComp = IgnitePattern::getAppPatternInstance();
			appSongComp = IgniteSong::getAppSongInstance();
			appSceneComp = IgniteScene::getAppSceneInstance();
			appTrackComp = IgniteTrack::GetAppTrackInstance();
			appInstrComp = IgniteInstruments::GetAppInstrumentsInstance();
		}
		SongList.setVisible(false);
		SceneList.setVisible(false);
		TrackView.setVisible(false);
		PatternStep.setVisible(false);
		PatternBar.setVisible(false);
		PatternGrid.setVisible(false);
		midiGlobal.setVisible(false);
		midiSong.setVisible(false);
		songSettingGlobal.setVisible(false);
		songSettingActive.setVisible(false);
		cvioGlobal.setVisible(false);
		cvioSong.setVisible(false);
		songMidiConfig.setVisible(false);
		songCvioConfig.setVisible(false);
		btnPattern.setVisible(false);
		movetoTop.setVisible(false);
		movetoLast.setVisible(false);
		movetoDown.setVisible(false);
		movetoUp.setVisible(false);
		btnInstrument.setVisible(false);
		optionMove.isFocused = false;
		trackCtlBtn.setVisible(false);
		trackCtlBtn.isFocused = false;
		altFunBtn.setVisible(false);
		altFunBtn.isFocused = false;

		switch (t)
		{
		case mt::Ignite::tabs::MENU:
			if (!subtab)
			{
				showOptions(false);
			}
			else if (subtab == 2)
			{
				showOptions(true);
				setView(false, true, true, true, false, true);
				optionMove.setBounds(xStartOptionccCmp + 317, (int)11.75, 38, 44);
				optionMove.setToggleState(false, dontSendNotification);
				appInstrComp->move_enable = false;
				ctlBox.performLayout(ui::Rectangle<float>{xStartOptionccCmp + 317, (int)11.75, 284, 44});
			}
			else if (subtab == 3)
			{
				showOptions(true);
				setView(false, false, false, true, false);
				SongList.setVisible(true);
				songSettingGlobal.setVisible(true);
				songSettingActive.setVisible(true);
				songSettingGlobal.setBounds(xStartOptionccCmp + 338, (int)11.75, 109, 44);
				songSettingActive.setBounds(xStartOptionccCmp + 455, (int)11.75, 145, 44);
				ctlBox.performLayout(ui::Rectangle<float>{xStartOptionccCmp + 156, (int)11.75, 50, 44});
				if (appSongComp->isSongCreated())
					songSettingActive.setToggleState(true, dontSendNotification);

				SongList.setBounds(xStartOptionccCmp + 206, (int)11.75, 128, 44);
			}
			else if (subtab == 4)
			{
				showOptions(true);
				setView(false, false, false, true, false);
				SceneList.setVisible(true);
				ctlBox.performLayout(ui::Rectangle<float>{xStartOptionccCmp + 418, (int)11.75, 50, 44});
				SceneList.setBounds(xStartOptionccCmp + 468, (int)11.75, 128, 44);
			}
			else if (subtab == 5)
			{
				showOptions(true);
				setView(false, false, false, true, false);
				PatternStep.setVisible(true);
				PatternBar.setVisible(true);
				PatternGrid.setVisible(true);
				ctlBox.performLayout(ui::Rectangle<float>{xStartOptionccCmp + 307, (int)11.75, 50, 44});
				PatternStep.setBounds(xStartOptionccCmp + 357, (int)11.75, 82, 44);
				PatternBar.setBounds(xStartOptionccCmp + 439, (int)11.75, 82, 44);
				PatternGrid.setBounds(xStartOptionccCmp + 521, (int)11.75, 82, 44);
			}
			else if (subtab == 6)
			{
				showOptions(true);
				setView(false, false, false, true, false);
				TrackView.setVisible(true);
				ctlBox.performLayout(ui::Rectangle<float>{xStartOptionccCmp + 414, (int)11.75, 50, 44});
				TrackView.setBounds(xStartOptionccCmp + 464, (int)11.75, 132, 44);
			}
			else if (subtab == 7)
			{
				showOptions(true);
				setView(false, false, false, true, false);
				midiGlobal.setVisible(true);
				midiSong.setVisible(true);
				midiGlobal.setBounds(xStartOptionccCmp + 338, (int)11.75, 109, 44);
				midiSong.setBounds(xStartOptionccCmp + 455, (int)11.75, 145, 44);
				ctlBox.performLayout(ui::Rectangle<float>{xStartOptionccCmp + 284, (int)11.75, 50, 44});
				if (appSongComp->isSongCreated())
					midiSong.setToggleState(true, dontSendNotification);
			}
			else if (subtab == 8)
			{
				showOptions(true);
				setView(false, false, false, true, false);
				cvioGlobal.setVisible(true);
				cvioSong.setVisible(true);
				cvioGlobal.setBounds(xStartOptionccCmp + 338, (int)11.75, 109, 44);
				cvioSong.setBounds(xStartOptionccCmp + 455, (int)11.75, 145, 44);
				ctlBox.performLayout(ui::Rectangle<float>{xStartOptionccCmp + 284, (int)11.75, 50, 44});
				changebtnstate(IgniteControlOptions::CV_SONG, appSongComp->isSongCreated());
			}
			else if (subtab == 13)
			{
				showOptions(true);
				setView(false, false, false, true, false);
				ctlBox.performLayout(ui::Rectangle<float>{xStartOptionccCmp + 376 + 174, (int)11.75, 50, 44});
			}
			else
			{
				showOptions(true);
				setView(false, false, false, true, false);
				ctlBox.performLayout(ui::Rectangle<float>{xStartOptionccCmp + 554, (int)11.75, 50, 44});
			}

			break;
		case mt::Ignite::tabs::SONG:
			if (appSongComp->isSongCreated())
			{
				if (subtab)
				{
					setView(false, true, false, true, true);
					optionMove.setToggleState(false, dontSendNotification);
					ctlBox.performLayout(ui::Rectangle<float>{xStartOptionccCmp + 188, 10, 215, 44});

				}
				else
				{
					setView(false, true, true, true, true);
					optionMove.setBounds(xStartOptionccCmp + 135, 10, 38, 44);
					optionMove.setToggleState(false, dontSendNotification);
					appSongComp->setSongMoveState(false);
					ctlBox.performLayout(ui::Rectangle<float>{xStartOptionccCmp + 135, 10, 270, 44});
				}
				if (appSongComp->isVisible())
				{
					if (!isVisible())
						showOptions(true);
				}
				songMidiConfig.setVisible(true);
				songCvioConfig.setVisible(true);
				songMidiConfig.setBounds(xStartOptionccCmp + 408, (int)11.75, 90, 44);
				songCvioConfig.setBounds(xStartOptionccCmp + 506, (int)11.75, 95, 44);
			}
			else
			{
				if (appSongComp->isVisible())
				{
					showOptions(false);
				}
			}
			break;
		case mt::Ignite::tabs::SCENE:
			if (appSongComp->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
			{
				if (subtab)
				{
					setView(false, false, false, true, true);
					optionMove.setToggleState(false, dontSendNotification);
					ctlBox.performLayout(ui::Rectangle<float>{xStartOptionccCmp + 440, 10, 160, 44});

				}
				else
				{
					setView(false, true, true, true, true);
					optionMove.setBounds(xStartOptionccCmp + 338, 10, 38, 44);
					optionMove.setToggleState(false, dontSendNotification);
					appSceneComp->setSceneMoveState(false);
					ctlBox.performLayout(ui::Rectangle<float>{xStartOptionccCmp + 338, 10, 265, 44});
				}
				if (appSceneComp->isVisible())
				{
					if (!isVisible())
						showOptions(true);
				}
			}
			else
			{
				if (appSceneComp->isVisible())
				{
					showOptions(false);
				}
			}
			break;
		case mt::Ignite::tabs::TRACK:
			if (appSongComp->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
			{
				if (!subtab)
				{
					showOptions(false);
				}
				else if (subtab == 3)
				{
					showOptions(true);
					setView(false, false, false, false, false);
					btnInstrument.setBounds(660, 12, 140, 44);
					btnInstrument.setVisible(true);
					trackCtlBtn.setBounds(542, 12, 110, 44);
					trackCtlBtn.setVisible(true);
					altFunBtn.setBounds(424, 12, 110, 44);
					altFunBtn.setVisible(trackCtlBtn.getToggleState());
				}

				else
				{
					showOptions(true);
					setView(false, false, false, true, false);
					btnPattern.setBounds(640, 12, 110, 44);
					btnPattern.setVisible(true);
					btnInstrument.setBounds(494, 12, 140, 44);
					btnInstrument.setVisible(true);
					ctlBox.performLayout(ui::Rectangle<float>{xStartOptionccCmp + 503, 12, 150, 44});
				}
			}
			break;
		case mt::Ignite::tabs::PATTERN:
			if (appPatternComp->isPatternCreated())
			{
				if (subtab == 0)
				{
					setView(false, true, true, true, true);
					optionMove.setBounds(xStartOptionccCmp + 338, 10, 38, 44);
					optionMove.setToggleState(false, dontSendNotification);
					appPatternComp->setPatternMoveState(false);
					ctlBox.performLayout(ui::Rectangle<float>{xStartOptionccCmp + 338, 10, 265, 44});
					if (!isVisible())
						showOptions(true);
				}
				else if (subtab == 1)
				{
					setView(false, false, false, true, true);
					ctlBox.performLayout(ui::Rectangle<float>{xStartOptionccCmp + 440, 10, 160, 44});
					if (!isVisible())
						showOptions(true);
				}
				else
				{
					if (appPatternComp->isVisible())
						showOptions(false);
				}
			}
			break;
		default:
			break;
		}
		if (!optionMove.getToggleState())
			enableMoveoptions(t, 0, false);
	}

	void AppOptions::enableMoveoptions(mt::Ignite::tabs a, int subtab, bool state)
	{
		movetoTop.setVisible(state);
		movetoLast.setVisible(state);
		movetoDown.setVisible(state);
		movetoUp.setVisible(state);
		if (state)
		{
			switch (a)
			{
			case mt::Ignite::tabs::MENU:
				if (subtab == 2)
					moveBox.performLayout(ui::Rectangle<float>{xStartOptionccCmp + 113, 11.75, 100 * 2, 44});
				break;
			case mt::Ignite::tabs::SONG:
				if (subtab)
				{
					moveBox.performLayout(ui::Rectangle<float>{xStartOptionccCmp + 86, 10, 100 * 2, 44});
				}
				else
				{
					moveBox.performLayout(ui::Rectangle<float>{132, 10, 100 * 2, 44});
				}

				break;
			case mt::Ignite::tabs::SCENE:
				moveBox.performLayout(ui::Rectangle<float>{xStartOptionccCmp + 134, 10, 200, 44});
				break;
			case mt::Ignite::tabs::TRACK:
				break;
			case mt::Ignite::tabs::PATTERN:
				moveBox.performLayout(ui::Rectangle<float>{xStartOptionccCmp + 134, 10, 200, 44});
				break;
			default:
				break;
			}
		}
	}

	bool AppOptions::getBtnState(IgniteControlOptions::eKey option)
	{
		switch (option)
		{
		case ui::IgniteControlOptions::PLAY:
			break;
		case ui::IgniteControlOptions::STOP:
			break;
		case ui::IgniteControlOptions::SAVE:
			break;
		case ui::IgniteControlOptions::COPY:
			break;
		case ui::IgniteControlOptions::UNDO:
			break;
		case ui::IgniteControlOptions::LOOP:
			break;
		case ui::IgniteControlOptions::MOVE:
			break;
		case ui::IgniteControlOptions::REC:
			break;
		case ui::IgniteControlOptions::DEL:
			break;
		case ui::IgniteControlOptions::FILLMODE:
			break;
		case ui::IgniteControlOptions::CONFIG:
			break;
		case ui::IgniteControlOptions::MOVEUP:
			return movetoUp.isVisible();
			break;
		case ui::IgniteControlOptions::MOVEDOWN:
			break;
		case ui::IgniteControlOptions::MOVETOP:
			break;
		case ui::IgniteControlOptions::MOVEBTM:
			break;
		case ui::IgniteControlOptions::AUTOSAVE:
			break;
		case ui::IgniteControlOptions::MIDI_GLOBAL:
			return midiGlobal.getToggleState();
			break;
		case ui::IgniteControlOptions::MIDI_SONG:
			return midiSong.getToggleState();
			break;
		case ui::IgniteControlOptions::SONG_SETTING_GLOBAL:
			return songSettingGlobal.getToggleState();
			break;
		case ui::IgniteControlOptions::SONG_SETTING_ACTIVE:
			return songSettingActive.getToggleState();
			break;
		case ui::IgniteControlOptions::MIDI_SONG_CONFIG:
			return songMidiConfig.getToggleState();
			break;
		case ui::IgniteControlOptions::CV_GLOBAL:
			return cvioGlobal.getToggleState();
			break;
		case ui::IgniteControlOptions::CV_SONG:
			return cvioSong.getToggleState();
			break;
		case ui::IgniteControlOptions::CVIO_SONG_CONFIG:
			return songCvioConfig.getToggleState();
			break;
		case ui::IgniteControlOptions::ALT_FN:
			return altFunBtn.getToggleState();
			break;
		case ui::IgniteControlOptions::TRACK_CTL:
			return trackCtlBtn.getToggleState();
			break;
		case ui::IgniteControlOptions::ALL:
			break;
		default:
			return false;
		}
		return false;
	}

	void AppOptions::changebtnstate(IgniteControlOptions::eKey option, bool state)
	{
		switch (option)
		{
		case ui::IgniteControlOptions::PLAY:
			break;
		case ui::IgniteControlOptions::STOP:
			break;
		case ui::IgniteControlOptions::SAVE:
			break;
		case ui::IgniteControlOptions::COPY:
			break;
		case ui::IgniteControlOptions::UNDO:
			break;
		case ui::IgniteControlOptions::LOOP:
			break;
		case ui::IgniteControlOptions::MOVE:
			break;
		case ui::IgniteControlOptions::REC:
			break;
		case ui::IgniteControlOptions::DEL:
			break;
		case ui::IgniteControlOptions::FILLMODE:
			break;
		case ui::IgniteControlOptions::CONFIG:
			break;
		case ui::IgniteControlOptions::MOVEUP:
			break;
		case ui::IgniteControlOptions::MOVEDOWN:
			break;
		case ui::IgniteControlOptions::MOVETOP:
			break;
		case ui::IgniteControlOptions::MOVEBTM:
			break;
		case ui::IgniteControlOptions::AUTOSAVE:
			autoSave.setToggleState(state, dontSendNotification);
			break;
		case ui::IgniteControlOptions::MIDI_GLOBAL:
			midiGlobal.setToggleState(state, dontSendNotification);
			midiSong.setToggleState(!state, dontSendNotification);
			break;
		case ui::IgniteControlOptions::MIDI_SONG:
			midiSong.setToggleState(state, dontSendNotification);
			midiGlobal.setToggleState(!state, dontSendNotification);
			break;
		case ui::IgniteControlOptions::SONG_SETTING_GLOBAL:
			songSettingGlobal.setToggleState(state, dontSendNotification);
			songSettingActive.setToggleState(!state, dontSendNotification);
			break;
		case ui::IgniteControlOptions::SONG_SETTING_ACTIVE:
			songSettingActive.setToggleState(state, dontSendNotification);
			songSettingGlobal.setToggleState(!state, dontSendNotification);
			break;
		case ui::IgniteControlOptions::MIDI_SONG_CONFIG:
			songMidiConfig.setToggleState(state, dontSendNotification);
			break;
		case ui::IgniteControlOptions::CV_GLOBAL:
			cvioGlobal.setToggleState(state, dontSendNotification);
			cvioSong.setToggleState(!state, dontSendNotification);
			break;
		case ui::IgniteControlOptions::CV_SONG:
			cvioSong.setToggleState(state, dontSendNotification);
			cvioGlobal.setToggleState(!state, dontSendNotification);
			break;
		case ui::IgniteControlOptions::CVIO_SONG_CONFIG:
			songCvioConfig.setToggleState(state, dontSendNotification);
			break;
		case ui::IgniteControlOptions::ALT_FN:
			altFunBtn.setVisible(state);
			break;
		case ui::IgniteControlOptions::TRACK_CTL:
			trackCtlBtn.setToggleState(state, dontSendNotification);
			if (state)
			{
				trackCtlBtn.setImage("btn-intfx-default.png", "btn-intfx-active.png", "btn-intfx-default-hover.png");
				trackCtlBtn.setDisableImage("btn-intfx-default.png");
				trackCtlBtn.sethoverImages("btn-intfx-default-hover.png", "btn-intfx-active-hover.png", "btn-intfx-default-hover.png");
			}
			else
			{
				trackCtlBtn.setImage("btn-extcc-default.png", "btn-extcc-active.png", "btn-extcc-default-hover.png");
				trackCtlBtn.setDisableImage("btn-extcc-default.png");
				trackCtlBtn.sethoverImages("btn-extcc-default-hover.png", "btn-altfn-active-hover.png", "btn-extcc-default-hover.png");
			}
			break;
		case ui::IgniteControlOptions::ALL:
			break;
		default:
			break;
		}
	}

	bool AppOptions::PannelKeyHandler(IgniteControlOptions::eKey option, bool state, paramId_t param, uint32_t KeyValue)
	{
		switch (option)
		{
		case ui::IgniteControlOptions::COPY:
			if (optionCopy.isEnabled())
			{
				if ((param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT || param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT)/* && param == (paramId_t)FrontPannelParam::paramKey_PAGESHIFT*/)
					optionCopy.setState((Button::ButtonState)state);
				else if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					optionCopy.setToggleState(state, sendNotification);
			}
			break;
		case ui::IgniteControlOptions::UNDO:
			if (optionUndo.isEnabled())
			{
				if ((param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT || param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT) || param == (paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
					optionUndo.setState((Button::ButtonState)state);
				else if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					optionUndo.setToggleState(state, sendNotification);
			}
			else
				return false;
			break;
		case ui::IgniteControlOptions::LOOP:
			if (optionloop.isEnabled())
			{
				if ((param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT || param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT) || param == (paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
					optionloop.setState((Button::ButtonState)state);
				else if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					optionloop.setToggleState(state, sendNotification);
				break;
			}
		case ui::IgniteControlOptions::MOVE:
			if (optionMove.isEnabled())
			{
				optionMove.isFocused = state;
				if ((param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT || param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT) || param == (paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
					optionMove.setState((Button::ButtonState)state);
				else if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
				{
					optionMove.setToggleState(state, sendNotification);
					optionMove.FPKeyHandler(state, param, KeyValue);
				}
				repaint();
			}
			else
				return false;
			break;
		case ui::IgniteControlOptions::CONFIG:
			if (optionConfig.isEnabled())
			{
				if (param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT || param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT || param == (paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
					optionConfig.setState((Button::ButtonState)state);
				else if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					optionConfig.setToggleState(state, sendNotification);
			}
			break;
		case ui::IgniteControlOptions::MOVEUP:
			if (movetoUp.isEnabled())
			{
				if (param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT || param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT || param == (paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
					movetoUp.setState((Button::ButtonState)state);
				else if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					movetoUp.setToggleState(state, sendNotification);
			}
			break;
		case ui::IgniteControlOptions::MOVEDOWN:
			if (movetoDown.isEnabled())
			{
				if (param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT || param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT || param == (paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
					movetoDown.setState((Button::ButtonState)state);
				else if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					movetoDown.setToggleState(state, sendNotification);
			}
			break;
		case ui::IgniteControlOptions::MOVETOP:
			if (movetoTop.isEnabled())
			{
				if (param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT || param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT || param == (paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
					movetoTop.setState((Button::ButtonState)state);
				else if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					movetoTop.setToggleState(state, sendNotification);
			}
			break;
		case ui::IgniteControlOptions::MOVEBTM:
			if (movetoLast.isEnabled())
			{
				if (param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT || param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT || param == (paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
					movetoLast.setState((Button::ButtonState)state);
				else if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					movetoLast.setToggleState(state, sendNotification);
			}
			break;
		case ui::IgniteControlOptions::AUTOSAVE:
			if (autoSave.isEnabled())
			{
				if (param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT || param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT || param == (paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
					autoSave.setState((Button::ButtonState)state);
				else if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					autoSave.setToggleState(state, sendNotification);
			}
			break;
		case ui::IgniteControlOptions::MIDI_GLOBAL:
			if (midiGlobal.isEnabled())
			{
				midiGlobal.isFocused = state;
				if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					midiGlobal.setToggleState(state, sendNotification);
				repaint();
			}
			else
				return false;
			break;
		case ui::IgniteControlOptions::MIDI_SONG:
			if (midiSong.isEnabled())
			{
				midiSong.isFocused = state;
				if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					midiSong.setToggleState(state, sendNotification);
				repaint();
			}
			else
				return false;
			break;
		case ui::IgniteControlOptions::MIDI_SONG_CONFIG:
			if (songMidiConfig.isEnabled())
			{
				if (param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT || param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT || param == (paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
					songMidiConfig.setState((Button::ButtonState)state);
				else if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					songMidiConfig.setToggleState(state, sendNotification);
			}
			break;
		case ui::IgniteControlOptions::CV_GLOBAL:
			if (cvioGlobal.isEnabled())
			{
				cvioGlobal.isFocused = state;
				if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					cvioGlobal.setToggleState(state, sendNotification);
				repaint();
			}
			else
				return false;
			break;
		case ui::IgniteControlOptions::CV_SONG:
			if (cvioSong.isEnabled())
			{
				cvioSong.isFocused = state;
				if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					cvioSong.setToggleState(state, sendNotification);
				repaint();
			}
			else
				return false;
			break;
		case ui::IgniteControlOptions::CVIO_SONG_CONFIG:
			if (songCvioConfig.isEnabled())
			{
				if (param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT || param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT || param == (paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
					songCvioConfig.setState((Button::ButtonState)state);
				else if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					songCvioConfig.setToggleState(state, sendNotification);
			}
			break;
		case ui::IgniteControlOptions::INST:
			if (btnInstrument.isEnabled())
			{
				if (param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT || param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT || param == (paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
					btnInstrument.setState((Button::ButtonState)state);
				else if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					btnInstrument.setToggleState(state, sendNotification);
			}
			break;
		case ui::IgniteControlOptions::ALT_FN:
			if (altFunBtn.isEnabled())
			{
				if (param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT || param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT || param == (paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
					altFunBtn.setState((Button::ButtonState)state);
				else if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					altFunBtn.setToggleState(state, sendNotification);
			}
			break;
		case ui::IgniteControlOptions::TRACK_CTL:
			if (trackCtlBtn.isEnabled())
			{
				if (param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT || param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT || param == (paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
					trackCtlBtn.setState((Button::ButtonState)state);
				else if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					changebtnstate(ui::IgniteControlOptions::TRACK_CTL, state);
			}
			break;
		case ui::IgniteControlOptions::PATTERN:
			if (btnPattern.isEnabled())
			{
				if (param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT || param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT || param == (paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
					btnPattern.setState((Button::ButtonState)state);
				else if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					btnPattern.setToggleState(state, sendNotification);
			}
			break;
		case ui::IgniteControlOptions::SONG_SETTING_GLOBAL:
			if (songSettingGlobal.isEnabled())
			{
				songSettingGlobal.isFocused = state;
				if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
				{
					songSettingGlobal.setToggleState(state, sendNotification);
					songSettingActive.setToggleState(!state, dontSendNotification);
				}
				repaint();
			}
			else
				return false;
			break;
		case ui::IgniteControlOptions::SONG_SETTING_ACTIVE:
			if (songSettingActive.isEnabled())
			{
				songSettingActive.isFocused = state;
				if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
				{
					songSettingActive.setToggleState(state, sendNotification);
					songSettingGlobal.setToggleState(!state, dontSendNotification);
				}
				repaint();
			}
			else
				return false;
			break;
		case ui::IgniteControlOptions::SONGLIST:
			if (SongList.isEnabled())
			{
				if ((param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT || param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT) || param == (paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
					SongList.setState((Button::ButtonState)state);
				else if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					SongList.setToggleState(state, sendNotification);
			}
			else
				return false;
			break;
		case ui::IgniteControlOptions::SCENELIST:
			if (SceneList.isEnabled())
			{
				if ((param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT || param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT) || param == (paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
					SceneList.setState((Button::ButtonState)state);
				else if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					SceneList.setToggleState(state, sendNotification);
			}
			else
				return false;
			break;
		case IgniteControlOptions::eKey::TRACKVIEW:
			if (TrackView.isEnabled())
			{
				if ((param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT || param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT) || param == (paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
					TrackView.setState((Button::ButtonState)state);
				else if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					TrackView.FPKeyHandler(state, param, KeyValue);
			}
			else
				return false;
			break;
		case IgniteControlOptions::eKey::PATSTEP:
			if (PatternStep.isEnabled())
			{
				if ((param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT || param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT) || param == (paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
					PatternStep.setState((Button::ButtonState)state);
				else if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					PatternStep.setToggleState(state, sendNotification);
			}
			else
				return false;
			break;
		case IgniteControlOptions::eKey::PATBAR:
			if (PatternBar.isEnabled())
			{
				if ((param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT || param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT) || param == (paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
					PatternBar.setState((Button::ButtonState)state);
				else if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					PatternBar.setToggleState(state, sendNotification);
			}
			else
				return false;
			break;
		case IgniteControlOptions::eKey::PATGRID:
			if (PatternGrid.isEnabled())
			{
				if ((param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT || param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT) || param == (paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
					PatternGrid.setState((Button::ButtonState)state);
				else if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT)
					PatternGrid.setToggleState(state, sendNotification);
			}
			else
				return false;
			break;

		default:
			break;
		}
		return true;
	}
};