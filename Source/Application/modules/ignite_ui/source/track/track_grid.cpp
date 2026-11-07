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

	IgniteTrackGrid::IgniteTrackGrid(IgniteTrack* tPtr)
	{
		pTrack = tPtr;

		addAndMakeVisible(trackBtn1);
		trackBtn1.setTitle(TRANS("TRACK 1"));
		trackBtn1.addListener(this);

		addAndMakeVisible(trackBtn2);
		trackBtn2.setTitle(TRANS("TRACK 2"));
		trackBtn2.addListener(this);

		addAndMakeVisible(trackBtn3);
		trackBtn3.setTitle(TRANS("TRACK 3"));
		trackBtn3.addListener(this);

		addAndMakeVisible(trackBtn4);
		trackBtn4.setTitle(TRANS("TRACK 4"));
		trackBtn4.addListener(this);

		addAndMakeVisible(trackBtn5);
		trackBtn5.setTitle(TRANS("TRACK 5"));
		trackBtn5.addListener(this);

		addAndMakeVisible(trackBtn6);
		trackBtn6.setTitle(TRANS("TRACK 6"));
		trackBtn6.addListener(this);

		addAndMakeVisible(trackBtn7);
		trackBtn7.setTitle(TRANS("TRACK 7"));
		trackBtn7.addListener(this);

		addAndMakeVisible(trackBtn8);
		trackBtn8.setTitle(TRANS("TRACK 8"));
		trackBtn8.addListener(this);

		addAndMakeVisible(trackBtn9);
		trackBtn9.setTitle(TRANS("TRACK 9"));
		trackBtn9.addListener(this);

		addAndMakeVisible(trackBtn10);
		trackBtn10.setTitle(TRANS("TRACK 10"));
		trackBtn10.addListener(this);

		addAndMakeVisible(trackBtn11);
		trackBtn11.setTitle(TRANS("TRACK 11"));
		trackBtn11.addListener(this);

		addAndMakeVisible(trackBtn12);
		trackBtn12.setTitle(TRANS("TRACK 12"));
		trackBtn12.addListener(this);

		addAndMakeVisible(trackBtn13);
		trackBtn13.setTitle(TRANS("TRACK 13"));
		trackBtn13.addListener(this);

		addAndMakeVisible(trackBtn14);
		trackBtn14.setTitle(TRANS("TRACK 14"));
		trackBtn14.addListener(this);

		addAndMakeVisible(trackBtn15);
		trackBtn15.setTitle(TRANS("TRACK 15"));
		trackBtn15.addListener(this);

		addAndMakeVisible(trackBtn16);
		trackBtn16.setTitle(TRANS("TRACK 16"));
		trackBtn16.addListener(this);

		_pInfoWindow = CommonInfoWindow::GetInfoWindowInstance();

		page1.makeVisibleAndAddListner(this);
		page2.makeVisibleAndAddListner(this);
		page3.makeVisibleAndAddListner(this);
		page4.makeVisibleAndAddListner(this);

		page1.setInterceptsMouseClicks(false, false);
		page2.setInterceptsMouseClicks(false, false);
		page3.setInterceptsMouseClicks(false, false);
		page4.setInterceptsMouseClicks(false, false);

		pageflex.items.add(FlexItem(page1).withFlex(1));
		pageflex.items.add(FlexItem(page2).withFlex(1));
		pageflex.items.add(FlexItem(page3).withFlex(1));
		pageflex.items.add(FlexItem(page4).withFlex(1));

		trackBox_colume1.items.add(FlexItem(trackBtn1).withFlex(1).withMargin({ 0,4,4,0 }));
		trackBox_colume1.items.add(FlexItem(trackBtn2).withFlex(1).withMargin({ 0,4,4,4 }));
		trackBox_colume1.items.add(FlexItem(trackBtn3).withFlex(1).withMargin({ 0,4,4,4 }));
		trackBox_colume1.items.add(FlexItem(trackBtn4).withFlex(1).withMargin({ 0,0,4,4 }));
		trackBox_colume2.items.add(FlexItem(trackBtn5).withFlex(1).withMargin({ 0,4,4,0 }));
		trackBox_colume2.items.add(FlexItem(trackBtn6).withFlex(1).withMargin({ 0,4,4,4 }));
		trackBox_colume2.items.add(FlexItem(trackBtn7).withFlex(1).withMargin({ 0,4,4,4 }));
		trackBox_colume2.items.add(FlexItem(trackBtn8).withFlex(1).withMargin({ 0,0,4,4 }));
		trackBox_colume3.items.add(FlexItem(trackBtn9).withFlex(1).withMargin({ 0,4,4,0 }));
		trackBox_colume3.items.add(FlexItem(trackBtn10).withFlex(1).withMargin({ 0,4,4,4 }));;
		trackBox_colume3.items.add(FlexItem(trackBtn11).withFlex(1).withMargin({ 0,4,4,4 }));;
		trackBox_colume3.items.add(FlexItem(trackBtn12).withFlex(1).withMargin({ 0,0,4,4 }));;
		trackBox_colume4.items.add(FlexItem(trackBtn13).withFlex(1).withMargin({ 0,4,4,0 }));
		trackBox_colume4.items.add(FlexItem(trackBtn14).withFlex(1).withMargin({ 0,4,4,4 }));
		trackBox_colume4.items.add(FlexItem(trackBtn15).withFlex(1).withMargin({ 0,4,4,4 }));
		trackBox_colume4.items.add(FlexItem(trackBtn16).withFlex(1).withMargin({ 0,0,4,4 }));

		trackBox.flexDirection = FlexBox::Direction::column;
		trackBox.items.add(FlexItem(trackBox_colume1).withFlex(1));
		trackBox.items.add(FlexItem(trackBox_colume2).withFlex(1));
		trackBox.items.add(FlexItem(trackBox_colume3).withFlex(1));
		trackBox.items.add(FlexItem(trackBox_colume4).withFlex(1));
	}

	IgniteTrackGrid::~IgniteTrackGrid()
	{
	}

	void IgniteTrackGrid::paint(juce::Graphics& g)
	{
	}

	void IgniteTrackGrid::resized()
	{
		trackBox.performLayout(ui::Rectangle(10, 64, 1004, 386));
		pageflex.performLayout(ui::Rectangle(445, 460, 134, 12));
	}

	void IgniteTrackGrid::buttonClicked(juce::Button* buttonThatWasClicked)
	{
	}

	CommonTrackButton* IgniteTrackGrid::getButton(int index)
	{
		switch (index)
		{
		case 0:
			return &trackBtn1;
		case 1:
			return &trackBtn2;
		case 2:
			return &trackBtn3;
		case 3:
			return &trackBtn4;
		case 4:
			return &trackBtn5;
		case 5:
			return &trackBtn6;
		case 6:
			return &trackBtn7;
		case 7:
			return &trackBtn8;
		case 8:
			return &trackBtn9;
		case 9:
			return &trackBtn10;
		case 10:
			return &trackBtn11;
		case 11:
			return &trackBtn12;
		case 12:
			return &trackBtn13;
		case 13:
			return &trackBtn14;
		case 14:
			return &trackBtn15;
		case 15:
			return &trackBtn16;
		default:
			return &trackBtn1;
		}
	}

	void IgniteTrackGrid::updateTrackButtonState()
	{
		auto scnPtr = IgniteScene::getAppSceneInstance();
		int current_track = (int)scnPtr->getSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK);
		int currentTrackBank = (int)scnPtr->getSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK_BANK) * 16;

		for (auto trackIndex = 0; trackIndex < 16; trackIndex++)
		{
			scnPtr->setSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK, currentTrackBank + trackIndex, true);
			auto gTrackRef = scnPtr->getTrackDataRef();

			if (!gTrackRef->trackState)
				getButton(trackIndex)->setToggleState(true);
			else
				getButton(trackIndex)->setToggleState(false);
		}
		updatePagerBullet(currentTrackBank / 16);
		scnPtr->setSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK, current_track, true);
	}

	void IgniteTrackGrid::updateTrackData(int trackIndex)
	{
		String mode;
		auto gTrackRef = IgniteScene::getAppSceneInstance()->getTrackDataRef();

		(gTrackRef->soloMode) ? (mode = "") : (mode = "");
		getButton(trackIndex)->setlabels(gTrackRef->outputInstrument, gTrackRef->pattern, mode);
		getButton(trackIndex)->setTitle(gTrackRef->name);
		getButton(trackIndex)->setTextColour(CommonTrackButton::Contains::LeftLabel, Theme::Instance().getColour(neutralBlack));
		getButton(trackIndex)->setTextColour(CommonTrackButton::Contains::RightLabel, Theme::Instance().getColour(neutralBlack));
		(!gTrackRef->trackState) ? getButton(trackIndex)->setButtonOnColour(juce::Colours::limegreen) : getButton(trackIndex)->setColour(Theme::Instance().getColour(systemBlue));
	}

	void IgniteTrackGrid::updateTrackGridData()
	{
		auto current_track_index = 0;
		auto scnPtr = IgniteScene::getAppSceneInstance();
		int current_track = static_cast<int>(scnPtr->getSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK));
		int currentTrackBank = static_cast<int>(scnPtr->getSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK_BANK)) * 16;

		current_track = (current_track == -1) ? 0 : current_track;
		current_track_index = (current_track >= 16) ? (current_track - currentTrackBank) : current_track;

		for (int trackIndex = 0; trackIndex < 16; ++trackIndex)
		{
			auto trackBtn = getButton(trackIndex);
			int trackDataIndex = currentTrackBank + trackIndex;

			scnPtr->setSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK, trackDataIndex, true);
			mt::Ignite::trackData* gTrackRef = scnPtr->getTrackDataRef();

			trackBtn->setlabels(gTrackRef->outputInstrument, gTrackRef->pattern, "");
			trackBtn->setTitle(gTrackRef->name);
			trackBtn->setSoloState(gTrackRef->soloMode);

			if (trackIndex == current_track_index)
			{
				trackBtn->setToggleState(!gTrackRef->trackState);
				trackBtn->setEditState(true);
			}
			else
			{
				trackBtn->setEditState(false);
			}
		}

		scnPtr->setSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK, current_track, true);
		auto currentButton = getButton(current_track);
		currentButton->setButtonOnColour(juce::Colours::limegreen.withAlpha(static_cast<uint8>(0x50)));
		enablePagerBullet();
	}


	void IgniteTrackGrid::onMouseClicked(CommonTrackButton* buttonThatWasClicked)
	{
		bool isStateChanged = false;
		auto songPtr = IgniteSong::getAppSongInstance();
		auto scnPtr = IgniteScene::getAppSceneInstance();
		int currentTrackBank = (int)scnPtr->getSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK_BANK) * 16;
		bool* trackMutePtr = AppMainmode::getMainModeInstance()->getTrackMuteStatus();

		for (auto trackIndex = 0; trackIndex < 16; trackIndex++)
		{
			getButton(trackIndex)->setButtonOnColour((juce::Colours::limegreen).withAlpha((uint8)0x50));
			_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((uint8_t)FrontPannelParam::paramKey_TRACKROTARY1 + trackIndex), fpLEDPattern::EN_LED_PATT_OFF);
		}

		if (buttonThatWasClicked == &trackBtn1)
		{
			scnPtr->currentTrack = currentTrackBank + 0;
			if (songPtr->isTrackConfigured(currentTrackBank + 0))
			{
				pTrack->setTrackData(mt::Ignite::trackDataIndex::TRACK_STATE, trackBtn1.getToggleState(), false, scnPtr->currentTrack);
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::param_RGB_DISP1, (uint8_t)(trackBtn1.getToggleState() ? fpLEDPattern::EN_RGB_LED_BLUE : fpLEDPattern::EN_LED_PATT_OFF));
				isStateChanged = true;
				trackMutePtr[scnPtr->currentTrack] = trackBtn1.getToggleState();
			}
			else
				trackBtn1.setToggleState(false);
		}
		if (buttonThatWasClicked == &trackBtn2)
		{
			scnPtr->currentTrack = currentTrackBank + 1;
			if (songPtr->isTrackConfigured(currentTrackBank + 1))
			{
				pTrack->setTrackData(mt::Ignite::trackDataIndex::TRACK_STATE, trackBtn2.getToggleState(), false, scnPtr->currentTrack);
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::param_RGB_DISP2, (uint8_t)(trackBtn2.getToggleState() ? fpLEDPattern::EN_RGB_LED_BLUE : fpLEDPattern::EN_LED_PATT_OFF));
				isStateChanged = true;
				trackMutePtr[scnPtr->currentTrack] = trackBtn2.getToggleState();
			}
			else
				trackBtn2.setToggleState(false);
		}
		if (buttonThatWasClicked == &trackBtn3)
		{
			scnPtr->currentTrack = currentTrackBank + 2;
			if (songPtr->isTrackConfigured(currentTrackBank + 2))
			{
				pTrack->setTrackData(mt::Ignite::trackDataIndex::TRACK_STATE, trackBtn3.getToggleState(), false, scnPtr->currentTrack);
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::param_RGB_DISP3, (uint8_t)(trackBtn3.getToggleState() ? fpLEDPattern::EN_RGB_LED_BLUE : fpLEDPattern::EN_LED_PATT_OFF));
				isStateChanged = true;
				trackMutePtr[scnPtr->currentTrack] = trackBtn3.getToggleState();
			}
			else
				trackBtn3.setToggleState(false);
		}
		if (buttonThatWasClicked == &trackBtn4)
		{
			scnPtr->currentTrack = currentTrackBank + 3;
			if (songPtr->isTrackConfigured(currentTrackBank + 3))
			{
				pTrack->setTrackData(mt::Ignite::trackDataIndex::TRACK_STATE, trackBtn4.getToggleState(), false, scnPtr->currentTrack);
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::param_RGB_DISP4, (uint8_t)(trackBtn4.getToggleState() ? fpLEDPattern::EN_RGB_LED_BLUE : fpLEDPattern::EN_LED_PATT_OFF));
				isStateChanged = true;
				trackMutePtr[scnPtr->currentTrack] = trackBtn4.getToggleState();
			}
			else
				trackBtn4.setToggleState(false);
		}
		if (buttonThatWasClicked == &trackBtn5)
		{
			scnPtr->currentTrack = currentTrackBank + 4;
			if (songPtr->isTrackConfigured(currentTrackBank + 4))
			{
				pTrack->setTrackData(mt::Ignite::trackDataIndex::TRACK_STATE, trackBtn5.getToggleState(), false, scnPtr->currentTrack);
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::param_RGB_DISP5, (uint8_t)(trackBtn5.getToggleState() ? fpLEDPattern::EN_RGB_LED_BLUE : fpLEDPattern::EN_LED_PATT_OFF));
				isStateChanged = true;
				trackMutePtr[scnPtr->currentTrack] = trackBtn5.getToggleState();
			}
			else
				trackBtn5.setToggleState(false);
		}
		if (buttonThatWasClicked == &trackBtn6)
		{
			scnPtr->currentTrack = currentTrackBank + 5;
			if (songPtr->isTrackConfigured(currentTrackBank + 5))
			{
				pTrack->setTrackData(mt::Ignite::trackDataIndex::TRACK_STATE, trackBtn6.getToggleState(), false, scnPtr->currentTrack);
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::param_RGB_DISP6, (uint8_t)(trackBtn6.getToggleState() ? fpLEDPattern::EN_RGB_LED_BLUE : fpLEDPattern::EN_LED_PATT_OFF));
				isStateChanged = true;
				trackMutePtr[scnPtr->currentTrack] = trackBtn6.getToggleState();
			}
			else
				trackBtn6.setToggleState(false);
		}
		if (buttonThatWasClicked == &trackBtn7)
		{
			scnPtr->currentTrack = currentTrackBank + 6;
			if (songPtr->isTrackConfigured(currentTrackBank + 6))
			{
				pTrack->setTrackData(mt::Ignite::trackDataIndex::TRACK_STATE, trackBtn7.getToggleState(), false, scnPtr->currentTrack);
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::param_RGB_DISP7, (uint8_t)(trackBtn7.getToggleState() ? fpLEDPattern::EN_RGB_LED_BLUE : fpLEDPattern::EN_LED_PATT_OFF));
				isStateChanged = true;
				trackMutePtr[scnPtr->currentTrack] = trackBtn7.getToggleState();
			}
			else
				trackBtn7.setToggleState(false);
		}
		if (buttonThatWasClicked == &trackBtn8)
		{
			scnPtr->currentTrack = currentTrackBank + 7;
			if (songPtr->isTrackConfigured(currentTrackBank + 7))
			{
				pTrack->setTrackData(mt::Ignite::trackDataIndex::TRACK_STATE, trackBtn8.getToggleState(), false, scnPtr->currentTrack);
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::param_RGB_DISP8, (uint8_t)(trackBtn8.getToggleState() ? fpLEDPattern::EN_RGB_LED_BLUE : fpLEDPattern::EN_LED_PATT_OFF));
				isStateChanged = true;
				trackMutePtr[scnPtr->currentTrack] = trackBtn8.getToggleState();
			}
			else
				trackBtn8.setToggleState(false);
		}
		if (buttonThatWasClicked == &trackBtn9)
		{
			scnPtr->currentTrack = currentTrackBank + 8;
			if (songPtr->isTrackConfigured(currentTrackBank + 8))
			{
				pTrack->setTrackData(mt::Ignite::trackDataIndex::TRACK_STATE, trackBtn9.getToggleState(), false, scnPtr->currentTrack);
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::param_RGB_DISP9, (uint8_t)(trackBtn9.getToggleState() ? fpLEDPattern::EN_RGB_LED_BLUE : fpLEDPattern::EN_LED_PATT_OFF));
				isStateChanged = true;
				trackMutePtr[scnPtr->currentTrack] = trackBtn9.getToggleState();
			}
			else
				trackBtn9.setToggleState(false);
		}
		if (buttonThatWasClicked == &trackBtn10)
		{
			scnPtr->currentTrack = currentTrackBank + 9;
			if (songPtr->isTrackConfigured(currentTrackBank + 9))
			{
				pTrack->setTrackData(mt::Ignite::trackDataIndex::TRACK_STATE, trackBtn10.getToggleState(), false, scnPtr->currentTrack);
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::param_RGB_DISP10, (uint8_t)(trackBtn10.getToggleState() ? fpLEDPattern::EN_RGB_LED_BLUE : fpLEDPattern::EN_LED_PATT_OFF));
				isStateChanged = true;
				trackMutePtr[scnPtr->currentTrack] = trackBtn10.getToggleState();
			}
			else
				trackBtn10.setToggleState(false);
		}
		if (buttonThatWasClicked == &trackBtn11)
		{
			scnPtr->currentTrack = currentTrackBank + 10;
			if (songPtr->isTrackConfigured(currentTrackBank + 10))
			{
				pTrack->setTrackData(mt::Ignite::trackDataIndex::TRACK_STATE, trackBtn11.getToggleState(), false, scnPtr->currentTrack);
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::param_RGB_DISP11, (uint8_t)(trackBtn11.getToggleState() ? fpLEDPattern::EN_RGB_LED_BLUE : fpLEDPattern::EN_LED_PATT_OFF));
				isStateChanged = true;
				trackMutePtr[scnPtr->currentTrack] = trackBtn11.getToggleState();
			}
			else
				trackBtn11.setToggleState(false);
		}
		if (buttonThatWasClicked == &trackBtn12)
		{
			scnPtr->currentTrack = currentTrackBank + 11;
			if (songPtr->isTrackConfigured(currentTrackBank + 11))
			{
				pTrack->setTrackData(mt::Ignite::trackDataIndex::TRACK_STATE, trackBtn12.getToggleState(), false, scnPtr->currentTrack);
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::param_RGB_DISP12, (uint8_t)(trackBtn12.getToggleState() ? fpLEDPattern::EN_RGB_LED_BLUE : fpLEDPattern::EN_LED_PATT_OFF));
				isStateChanged = true;
				trackMutePtr[scnPtr->currentTrack] = trackBtn12.getToggleState();
			}
			else
				trackBtn12.setToggleState(false);
		}
		if (buttonThatWasClicked == &trackBtn13)
		{
			scnPtr->currentTrack = currentTrackBank + 12;
			if (songPtr->isTrackConfigured(currentTrackBank + 12))
			{
				pTrack->setTrackData(mt::Ignite::trackDataIndex::TRACK_STATE, trackBtn13.getToggleState(), false, scnPtr->currentTrack);
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::param_RGB_DISP13, (uint8_t)(trackBtn13.getToggleState() ? fpLEDPattern::EN_RGB_LED_BLUE : fpLEDPattern::EN_LED_PATT_OFF));
				isStateChanged = true;
				trackMutePtr[scnPtr->currentTrack] = trackBtn13.getToggleState();
			}
			else
				trackBtn13.setToggleState(false);
		}
		if (buttonThatWasClicked == &trackBtn14)
		{
			scnPtr->currentTrack = currentTrackBank + 13;
			if (songPtr->isTrackConfigured(currentTrackBank + 13))
			{
				pTrack->setTrackData(mt::Ignite::trackDataIndex::TRACK_STATE, trackBtn14.getToggleState(), false, scnPtr->currentTrack);
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::param_RGB_DISP14, (uint8_t)(trackBtn14.getToggleState() ? fpLEDPattern::EN_RGB_LED_BLUE : fpLEDPattern::EN_LED_PATT_OFF));
				isStateChanged = true;
				trackMutePtr[scnPtr->currentTrack] = trackBtn14.getToggleState();
			}
			else
				trackBtn14.setToggleState(false);
		}
		if (buttonThatWasClicked == &trackBtn15)
		{
			scnPtr->currentTrack = currentTrackBank + 14;
			if (songPtr->isTrackConfigured(currentTrackBank + 14))
			{
				pTrack->setTrackData(mt::Ignite::trackDataIndex::TRACK_STATE, trackBtn15.getToggleState(), false, scnPtr->currentTrack);
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::param_RGB_DISP15, (uint8_t)(trackBtn15.getToggleState() ? fpLEDPattern::EN_RGB_LED_BLUE : fpLEDPattern::EN_LED_PATT_OFF));
				isStateChanged = true;
				trackMutePtr[scnPtr->currentTrack] = trackBtn15.getToggleState();
			}
			else
				trackBtn15.setToggleState(false);
		}
		if (buttonThatWasClicked == &trackBtn16)
		{
			scnPtr->currentTrack = currentTrackBank + 15;
			if (songPtr->isTrackConfigured(currentTrackBank + 15))
			{
				pTrack->setTrackData(mt::Ignite::trackDataIndex::TRACK_STATE, trackBtn16.getToggleState(), false, scnPtr->currentTrack);
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::param_RGB_DISP16, (uint8_t)(trackBtn16.getToggleState() ? fpLEDPattern::EN_RGB_LED_BLUE : fpLEDPattern::EN_LED_PATT_OFF));
				isStateChanged = true;
				trackMutePtr[scnPtr->currentTrack] = trackBtn16.getToggleState();
			}
			else
				trackBtn16.setToggleState(false);
		}

		updateTrackGridData();

		if (isStateChanged)
		{
			if (!IgniteTrackConfig::GetAppTrackConfigInstance()->isAutoSaveEnabled())
			{
				pTrack->trackDataUpdated = true;
				pTrack->enableControlButton(IgniteControlOptions::SAVE, true);
				pTrack->enableControlButton(IgniteControlOptions::UNDO, true);
			}
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleTrack, (paramId_t)TrackParam::paramClearUndoList, 1);
		}
		else
			_pInfoWindow->setTextandShow("Pattern and Output Instrument not assigned");

		/*else if (!isDoubleClick)
		{
			auto popupPtr = new CommonPopUp("Track not configured !!!", 604, 290);
			popupPtr->setbtnsize(267, 44);
			popupPtr->setInfoText("Please assign pattern and instrument to this track");
			popupPtr->addImageButton("OK", "btn-okay-544x44-default.png", "btn-okay-544x44-default-hover.png", 1);
			popupPtr->popupType = POPUP_WITHOK;
			popupPtr->setAutohide(true, 1500);
			popupPtr->show();
			popupPtr->onSelectionChanged = [this](int r)
			{
				if (r == 1)
					if (auto dw = getCurrentlyModalComponent())
						dw->exitModalState(0);
			};
		}*/
	}

	bool IgniteTrackGrid::changeEditTrack(int trackIndex)
	{
		auto scnPtr = IgniteScene::getAppSceneInstance();
		int currentTrackBank = (int)scnPtr->getSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK_BANK) * 16;

		for (auto _trackIndex = 0; _trackIndex < 16; _trackIndex++)
			_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((uint8_t)FrontPannelParam::paramKey_TRACKROTARY1 + _trackIndex), fpLEDPattern::EN_LED_PATT_OFF);

		for (int index = 0; index < 16; index++)
		{
			if (trackIndex == index)
			{
				scnPtr->setSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK, currentTrackBank + trackIndex, false);
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((uint8_t)FrontPannelParam::paramKey_TRACKROTARY1 + index), fpLEDPattern::EN_LED_PATT_ON);
				break;
			}
		}

		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleTrack, (paramId_t)TrackParam::paramClearUndoList, 1);
		AppTrackOpt::GetAppTrackOptionsInstance(pTrack)->refreshData();
		pTrack->setCurrentTrackData();
		pTrack->updateSelectionInfo();
		pTrack->trackDataUpdated = false;
		pTrack->enableControlButton(IgniteControlOptions::SAVE, false);
		pTrack->enableControlButton(IgniteControlOptions::UNDO, false);

		return true;
	}

	void IgniteTrackGrid::onMouseDoubleClicked(CommonTrackButton* evt)
	{

		auto scnPtr = IgniteScene::getAppSceneInstance();
		int currentTrackBank = (int)scnPtr->getSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK_BANK) * 16;

		for (auto trackIndex = 0; trackIndex < 16; trackIndex++)
			_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((uint8_t)FrontPannelParam::paramKey_TRACKROTARY1 + trackIndex), fpLEDPattern::EN_LED_PATT_OFF);

		for (int index = 0; index < 16; index++)
		{
			auto trackBtn = getButton(index);
			if (evt == trackBtn)
			{
				scnPtr->setSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK, currentTrackBank + index, false);
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)((uint8_t)FrontPannelParam::paramKey_TRACKROTARY1 + index), fpLEDPattern::EN_LED_PATT_ON);
				break;
			}
		}

		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleTrack, (paramId_t)TrackParam::paramClearUndoList, 1);
		pTrack->changeTrackOptionsVisibility(IgniteTrack::trackScreenIndex::OPTION_WINDOW);
		AppTrackOpt::GetAppTrackOptionsInstance(pTrack)->refreshData();
		pTrack->setCurrentTrackData();
		pTrack->updateSelectionInfo();
		pTrack->trackDataUpdated = false;
		pTrack->enableControlButton(IgniteControlOptions::SAVE, false);
		pTrack->enableControlButton(IgniteControlOptions::UNDO, false);
	}

	bool IgniteTrackGrid::PannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool handled = true;
		int id = 0;
		if ((FrontPannelParam)param == FrontPannelParam::paramKey_RMOVELEFT || (FrontPannelParam)param == FrontPannelParam::paramKey_RMOVERIGHT || (FrontPannelParam)param == FrontPannelParam::paramRot_ROW)
		{
			getButton(keyFocusedItem - 1)->setFocusState(false);
			if (keyFocusedItem == TrackViewItemID::EN_TRACK16 && FrontPannelParam::paramKey_RMOVELEFT == (FrontPannelParam)param && pTrack->getTotalTrackBank() > 1)
			{
				auto scnPtr = IgniteScene::getAppSceneInstance();
				int currentTrackBank = (int)scnPtr->getSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK_BANK);
				if (currentTrackBank < 4 && currentTrackBank >=0 && currentTrackBank +1 < pTrack->getTotalTrackBank())
				{
					pTrack->getTrackBankAndUpdate(currentTrackBank + 1);
					keyFocusedItem = TrackViewItemID::EN_TRACK1;
				}
					getButton(keyFocusedItem - 1)->setFocusState(true);
			}
			else if (keyFocusedItem == TrackViewItemID::EN_TRACK1 && FrontPannelParam::paramKey_RMOVERIGHT == (FrontPannelParam)param && pTrack->getTotalTrackBank() > 1)
			{
				auto scnPtr = IgniteScene::getAppSceneInstance();
				int currentTrackBank = (int)scnPtr->getSceneData(mt::Ignite::sceneDataIndex::CURRENT_TRACK_BANK);
				if (currentTrackBank < 4 && currentTrackBank > 0)
				{
					pTrack->getTrackBankAndUpdate(currentTrackBank - 1);
					keyFocusedItem = TrackViewItemID::FOCUS_MAX;
				}
					getButton(keyFocusedItem - 1)->setFocusState(true);
			}
			else
			{
				switch ((FrontPannelParam)param)
				{
				case FrontPannelParam::paramKey_RMOVELEFT:
					keyFocusedItem = (keyFocusedItem + 1 >= TrackViewItemID::FOCUS_MAX ? (TrackViewItemID::FOCUS_MAX) : keyFocusedItem + 1);
					break;
				case FrontPannelParam::paramKey_RMOVERIGHT:
					keyFocusedItem = (keyFocusedItem - 1 <= TrackViewItemID::NO_FOCUS ? (TrackViewItemID::EN_TRACK1) : keyFocusedItem - 1);
					break;
				case FrontPannelParam::paramRot_ROW:
					if ((KeyValue == ROTARY_RIGHT || KeyValue == ROTARY_FASTRIGHT || KeyValue == ROTARY_SUPERFASTRIGHT))
					{
						keyFocusedItem = (keyFocusedItem + TRACK_ROW_ITEMS >= TrackViewItemID::FOCUS_MAX ? ((keyFocusedItem + TRACK_ROW_ITEMS) == (TrackViewItemID::FOCUS_MAX) ? (TrackViewItemID::FOCUS_MAX) : keyFocusedItem) : keyFocusedItem + TRACK_ROW_ITEMS);
					}
					else if ((KeyValue == ROTARY_LEFT || KeyValue == ROTARY_FASTLEFT || KeyValue == ROTARY_SUPERFASTLEFT))
					{
						keyFocusedItem = (keyFocusedItem - TRACK_ROW_ITEMS <= TrackViewItemID::NO_FOCUS ? (keyFocusedItem) : keyFocusedItem - TRACK_ROW_ITEMS);
					}
					break;
				}
				getButton(keyFocusedItem - 1)->setFocusState(true);
			}
		}
		else if (FrontPannelParam::paramKey_RSELECT == (FrontPannelParam)param)
		{
				isDoubleClick = true;
				this->postCommandMessage(16 + keyFocusedItem);
		}
		else if (KeyValue == (uint32_t)FrontPannelKeyStatus::paramKeyStatusPressed)
		{
			switch ((FrontPannelParam)param)
			{
			case FrontPannelParam::paramKey_TRACKSEL1:   id = 1; break;
			case FrontPannelParam::paramKey_TRACKSEL2:   id = 2; break;
			case FrontPannelParam::paramKey_TRACKSEL3:   id = 3; break;
			case FrontPannelParam::paramKey_TRACKSEL4:   id = 4; break;
			case FrontPannelParam::paramKey_TRACKSEL5:   id = 5; break;
			case FrontPannelParam::paramKey_TRACKSEL6:   id = 6; break;
			case FrontPannelParam::paramKey_TRACKSEL7:   id = 7; break;
			case FrontPannelParam::paramKey_TRACKSEL8:   id = 8; break;
			case FrontPannelParam::paramKey_TRACKSEL9:   id = 9; break;
			case FrontPannelParam::paramKey_TRACKSEL10:  id = 10; break;
			case FrontPannelParam::paramKey_TRACKSEL11:  id = 11; break;
			case FrontPannelParam::paramKey_TRACKSEL12:  id = 12; break;
			case FrontPannelParam::paramKey_TRACKSEL13:  id = 13; break;
			case FrontPannelParam::paramKey_TRACKSEL14:  id = 14; break;
			case FrontPannelParam::paramKey_TRACKSEL15:  id = 15; break;
			case FrontPannelParam::paramKey_TRACKSEL16:  id = 16; break;
			case FrontPannelParam::paramKey_TRACKROTARY1:   id = 17; break;
			case FrontPannelParam::paramKey_TRACKROTARY2:   id = 18; break;
			case FrontPannelParam::paramKey_TRACKROTARY3:   id = 19; break;
			case FrontPannelParam::paramKey_TRACKROTARY4:   id = 20; break;
			case FrontPannelParam::paramKey_TRACKROTARY5:   id = 21; break;
			case FrontPannelParam::paramKey_TRACKROTARY6:   id = 22; break;
			case FrontPannelParam::paramKey_TRACKROTARY7:   id = 23; break;
			case FrontPannelParam::paramKey_TRACKROTARY8:   id = 24; break;
			case FrontPannelParam::paramKey_TRACKROTARY9:   id = 25; break;
			case FrontPannelParam::paramKey_TRACKROTARY10:  id = 26; break;
			case FrontPannelParam::paramKey_TRACKROTARY11:  id = 27; break;
			case FrontPannelParam::paramKey_TRACKROTARY12:  id = 28; break;
			case FrontPannelParam::paramKey_TRACKROTARY13:  id = 29; break;
			case FrontPannelParam::paramKey_TRACKROTARY14:  id = 30; break;
			case FrontPannelParam::paramKey_TRACKROTARY15:  id = 31; break;
			case FrontPannelParam::paramKey_TRACKROTARY16:  id = 32; break;
			default:
				handled = false;
			}
			if ((id >= 1 && id <= 16 && !AppMainmode::getMainModeInstance()->getFillKeyStatus()) || (id > 16 && id <= 32))
				this->postCommandMessage(id);
		}

		return handled;
	}
	void IgniteTrackGrid::handleCommandMessage(int id)
	{
		CommonTrackButton* buttonThatWasClicked = getButton(((id > 16) ? (id - 16) : id) - 1);
		if (buttonThatWasClicked != nullptr)
		{
			if (id > 16 && id <= 32)
			{
				isDoubleClick = true;
				buttonThatWasClicked->handleMouseDoubleClick();
				onMouseDoubleClicked(buttonThatWasClicked);
			}
			else if(id >=1 && id <=16)
			{
				isDoubleClick = false;
				buttonThatWasClicked->handleMouseSingleClick();
				onMouseClicked(buttonThatWasClicked);
			}
		}

	}
	void IgniteTrackGrid::updatePagerBullet(int index)
	{
		page1.setToggleState(false, dontSendNotification);
		page2.setToggleState(false, dontSendNotification);
		page3.setToggleState(false, dontSendNotification);
		page4.setToggleState(false, dontSendNotification);
		switch (index + 1)
		{
		case 1:
			page1.setToggleState(true, dontSendNotification);
			break;
		case 2:
			page2.setToggleState(true, dontSendNotification);
			break;
		case 3:
			page3.setToggleState(true, dontSendNotification);
			break;
		case 4:
			page4.setToggleState(true, dontSendNotification);
			break;
		default:
			break;
		}

	}

	void IgniteTrackGrid::enablePagerBullet()
	{
		auto scnPtr = IgniteScene::getAppSceneInstance();
		int count = (int)scnPtr->getSceneData(mt::Ignite::sceneDataIndex::NUM_TRACK_BANK_INDEX);
		switch (count)
		{
		case 1:
			page1.setEnabled(true);
			page2.setEnabled(false);
			page3.setEnabled(false);
			page4.setEnabled(false);
			break;
		case 2:
			page1.setEnabled(true);
			page2.setEnabled(true);
			page3.setEnabled(false);
			page4.setEnabled(false);
			break;
		case 3:
			page1.setEnabled(true);
			page2.setEnabled(true);
			page3.setEnabled(true);
			page4.setEnabled(false);
			break;
		case 4:
			page1.setEnabled(true);
			page2.setEnabled(true);
			page3.setEnabled(true);
			page4.setEnabled(true);
			break;
		default:
			break;
		}
	}
};
