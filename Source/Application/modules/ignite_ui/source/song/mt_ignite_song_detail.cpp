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
	AppSongView::AppSongView(IgniteSong* songPtr)
	{
		_pSong = songPtr;

		swingComp.makeVisible(this);
		tempoComp.makeVisible(this);
		tracksComp.makeVisible(this);
		swingComp.setDisplayTitle(true);
		tempoComp.setDisplayTitle(true);
		tempoComp.setNumDecimalPlacesToDisplay(1);

		sceneInSong.makeVisible(this);
		sceneInSong.setDisplayTitle(true);
		sceneInSong.setEditable(false);

		showSceneList.makeVisibleAndAddListner(this);
		nameLabel.makeVisibleAndAddListner(this);
		nameLabel.setDisplayTitle(false);
		nameLabel.setEditable(false, true, false);
		nameLabel.setJustificationType(Justification::centred);
		nameLabel.setBounds(xStartSongRow, yStartSongRow, widthSongRow, heightSongRow);

		swingComp.setJustificationType(juce::Justification::centred);
		tempoComp.setJustificationType(juce::Justification::centred);
		sceneInSong.setJustificationType(juce::Justification::centred);
		sceneInSong.setTextColour(Theme::Instance().getColour(customOrange));

		addAndMakeVisible(tracksComp);
		tracksComp.updateListOptions(numOfTracks);
		tracksComp.setSelected(1);
		tracksComp.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		tracksComp.setValueColour(Theme::Instance().getColour(customOrange));

		const juce::Rectangle<int> currentSceneBound{ (0),(0),widthCurrentScene,heightCurrentScene };
		addAndMakeVisible(sceneCBox);
		sceneCBox.updateListOptions(sceneList);
		sceneCBox.setDisplayFormat(CommonListBox::BoxType::withTitleBar);
		sceneCBox.setValueColour(Theme::Instance().getColour(customOrange));
		sceneCBox.setSelected(1);
		sceneCBox.setDailogViewType(mt::Ignite::DailogViewType::CustomView, false, currentSceneBound);
		sceneCBox.setBackgroundColour(Theme::Instance().getColour(customEerieBlack));
		sceneCBox.setTextColour(Theme::Instance().getColour(customOrange));

		cScene.makeVisibleAndAddListner(this);
		cScene.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());

		nScene.makeVisibleAndAddListner(this);
		nScene.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());

		swingHover.makeVisibleAndAddListner(this);
		swingHover.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());

		tempoHover.makeVisibleAndAddListner(this);
		tempoHover.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());

		const juce::Rectangle<int> nextSceneBound{ (0),(0),widthCurrentScene,heightCurrentScene };
		addAndMakeVisible(nextCSceneBox);
		nextCSceneBox.updateListOptions(nextSceneList);
		nextCSceneBox.setDisplayFormat(CommonListBox::BoxType::withTitleBar);
		nextCSceneBox.setValueColour(Theme::Instance().getColour(customOrange));
		nextCSceneBox.setSelected(1);
		nextCSceneBox.setDailogViewType(mt::Ignite::DailogViewType::CustomView, false, nextSceneBound);
		nextCSceneBox.setBackgroundColour(Theme::Instance().getColour(customEerieBlack));
		nextCSceneBox.setTextColour(Theme::Instance().getColour(customOrange));

		tracklist.makeVisibleAndAddListner(this);

		_isFillMode = false;

		sceneBox.items.add(FlexItem(swingComp).withFlex(1).withMargin({ 0,8,60,0 }));
		sceneBox.items.add(FlexItem(tracksComp).withMargin({ 0, 8, 60, 0 }).withFlex(1));
		sceneBox.items.add(FlexItem(tempoComp).withMargin({ 0, 8, 60, 0 }).withFlex(1));

		tempoComp.setTextColour(Theme::Instance().getColour(customOrange));
		swingComp.setTextColour(Theme::Instance().getColour(customOrange));

		const juce::Rectangle<int> bonds{ (0),(0),604,235 };
		tracksComp.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, bonds);
		sceneCBox.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, ui::Rectangle{ 0,0,604,480 });
		nextCSceneBox.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, ui::Rectangle{ 0,0,604,480 });

		activeTrackC.makeVisible(this);
		activeTrackN.makeVisible(this);

		swingAppliedtoScene.makeVisibleAndAddListner(this);
		swingAppliedtoScene.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		tempoAppliedtoScene.makeVisibleAndAddListner(this);
		tempoAppliedtoScene.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		tempoToScene.makeVisible(this);
		swingToScene.makeVisible(this);
		this->addMouseListener(this, true);

		btnSwingAppliedtoScene.makeVisibleAndAddListner(this);
		btnSwingAppliedtoScene.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		btnSwingAppliedtoScene.addMouseListener(this, false);
		btnTempoAppliedtoScene.makeVisibleAndAddListner(this);
		btnTempoAppliedtoScene.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		btnTempoAppliedtoScene.addMouseListener(this, false);
		addAndMakeVisible(tapTempo);
		getAssets();
		_pSongConfigComp = IgniteSongConfig::getAppSongConfigInstance();
		optPtr = IgniteControlOptions::GetAppOptInstance();


		swingAppliedtoScene.sethoverImages("sml-btn-toggle-no-default-hover.png","sml-btn-toggle-yes-default-hover.png","null");
		tempoAppliedtoScene.sethoverImages("sml-btn-toggle-no-default-hover.png", "sml-btn-toggle-yes-default-hover.png", "null");

		swingComp.setComponentID((String)SWING);
		btnSwingAppliedtoScene.setComponentID((String)SWING_TO_SCENE);
		swingAppliedtoScene.setComponentID((String)SWING_TO_SCENE);
		tracksComp.setComponentID((String)NUM_TRACKS);
		tracklist.setComponentID((String)VIEW_TRACKS);
		tempoComp.setComponentID((String)TEMPO);
		btnTempoAppliedtoScene.setComponentID((String)TEMPO_TO_SCENE);
		tempoAppliedtoScene.setComponentID((String)TEMPO_TO_SCENE);
		sceneInSong.setComponentID((String)(SHOW_SCENE_LIST));
		showSceneList.setComponentID((String)SHOW_SCENE_LIST);
		sceneCBox.setComponentID(juce::String(CURRENT_SCENE));
		cScene.setComponentID(juce::String(CURRENT_SCENE));
		nextCSceneBox.setComponentID(juce::String(NEXT_SCENE));
		nScene.setComponentID(juce::String(NEXT_SCENE));
		tapTempo.setComponentID((String)TAP_TEMPO);	  
		
		tapTempo.getTapConfigValue = [this]()
		{
			return (int)_pSongConfigComp->getTapConfigValue();
		};

#if defined SEND_TEMPO_AS_PLAY_MODE_TIMER
		tapTempo.onValueChanged = [this](float value, bool sendTempoAsPlayModeData)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			setTapTempo(value, sendTempoAsPlayModeData, false);
		};
#elif defined SEND_TEMPO_AS_EDIT_MODE_UNDO
		tapTempo.onValueChanged = [this](float value, bool sendUndoForTapTempo)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			if (sendUndoForTapTempo)
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::paramUndoCmd, 0, false);

			_pSong->setSongData(mt::Ignite::songsDataIndex::TEMPO, (float)value, false);

			if (_pSong->getSongData(mt::Ignite::songsDataIndex::NUM_SCENES))
				IgniteTrack::GetAppTrackInstance()->updateSelectionInfo();

			if (!IgniteSongConfig::getAppSongConfigInstance()->isAutoSaveEnabled())
			{
				_pSong->setSongDataUpdateStatus(true);
				updateSongEditIndication();
				_pSong->enableControlButton(IgniteControlOptions::SAVE, true);
				_pSong->enableControlButton(IgniteControlOptions::UNDO, true);
			}
			else if (_pSong->getSongData(mt::Ignite::songsDataIndex::NUM_SCENES) && (_pSong->getGlobalSwingState() || _pSong->getGlobalTempoState()))
				_pSong->saveGlobalSongDataOfScenes();
		};
#endif

		nameLabel.onValueChanged = [this](String value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;


			_pSong->setSongData(mt::Ignite::songsDataIndex::SONG_NAME, value, false);
			if (_pSong->getSongData(mt::Ignite::songsDataIndex::NUM_SCENES))
				IgniteTrack::GetAppTrackInstance()->updateSelectionInfo();
			if (!IgniteSongConfig::getAppSongConfigInstance()->isAutoSaveEnabled())
			{
				_pSong->setSongDataUpdateStatus(true);
				updateSongEditIndication();
				_pSong->enableControlButton(IgniteControlOptions::SAVE, true);
				_pSong->enableControlButton(IgniteControlOptions::UNDO, true);
			}
		};

		tempoComp.onFocusChanged = [this](bool state)
		{

			repaint();
		};

		tempoComp.onFloatValueChanged = [this](float value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			_pSong->setSongData(mt::Ignite::songsDataIndex::TEMPO, value, false);

			if (_pSong->getSongData(mt::Ignite::songsDataIndex::NUM_SCENES))
				IgniteTrack::GetAppTrackInstance()->updateSelectionInfo();

			if (!IgniteSongConfig::getAppSongConfigInstance()->isAutoSaveEnabled())
			{
				_pSong->setSongDataUpdateStatus(true);
				//tempoComp.setName("Tempo*");
				updateSongEditIndication();
				_pSong->enableControlButton(IgniteControlOptions::SAVE, true);
				_pSong->enableControlButton(IgniteControlOptions::UNDO, true);
			}
			else if (_pSong->getSongData(mt::Ignite::songsDataIndex::NUM_SCENES) && (_pSong->getGlobalSwingState() || _pSong->getGlobalTempoState()))
				_pSong->saveGlobalSongDataOfScenes();
		};

		swingComp.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			_pSong->setSongData(mt::Ignite::songsDataIndex::SWING, (uint8_t)value, false);
			if (_pSong->getSongData(mt::Ignite::songsDataIndex::NUM_SCENES))
				IgniteTrack::GetAppTrackInstance()->updateSelectionInfo();
			if (!IgniteSongConfig::getAppSongConfigInstance()->isAutoSaveEnabled())
			{
				_pSong->setSongDataUpdateStatus(true);
				updateSongEditIndication();
				//swingComp.setName("Swing*");
				_pSong->enableControlButton(IgniteControlOptions::SAVE, true);
				_pSong->enableControlButton(IgniteControlOptions::UNDO, true);
			}
			else if (_pSong->getSongData(mt::Ignite::songsDataIndex::NUM_SCENES) && (_pSong->getGlobalSwingState() || _pSong->getGlobalTempoState()))
				_pSong->saveGlobalSongDataOfScenes();
		};

		tempoComp.onPlayTimeFloatValueChanged = [this](float value)
		{
			auto opMode = optPtr->getOperationMode();
			if ((opMode == mt::Ignite::operatioMode::PLAY_MODE) || (opMode == mt::Ignite::operatioMode::PLAY_REC_MODE))
			{
				Component::BailOutChecker checker(this);

				if (checker.shouldBailOut())
					return;

				_pSong->setSongData(mt::Ignite::songsDataIndex::TEMPO, value, false);

				if (_pSong->getSongData(mt::Ignite::songsDataIndex::NUM_SCENES))
					IgniteTrack::GetAppTrackInstance()->updateSelectionInfo();

				if (!IgniteSongConfig::getAppSongConfigInstance()->isAutoSaveEnabled())
				{
					_pSong->setSongDataUpdateStatus(true);
					updateSongEditIndication();
					//tempoComp.setName("Tempo*");
					_pSong->enableControlButton(IgniteControlOptions::SAVE, true);
					_pSong->enableControlButton(IgniteControlOptions::UNDO, true);
				}
				else if (_pSong->getSongData(mt::Ignite::songsDataIndex::NUM_SCENES) && (_pSong->getGlobalSwingState() || _pSong->getGlobalTempoState()))
					_pSong->saveGlobalSongDataOfScenes();
			}
		};

		swingComp.onPlayTimeValueChanged = [this](int value)
		{
			auto opMode = optPtr->getOperationMode();
			if ((opMode == mt::Ignite::operatioMode::PLAY_MODE) || (opMode == mt::Ignite::operatioMode::PLAY_REC_MODE))
			{
				Component::BailOutChecker checker(this);

				if (checker.shouldBailOut())
					return;

				_pSong->setSongData(mt::Ignite::songsDataIndex::SWING, (uint8_t)value, false);
				if (_pSong->getSongData(mt::Ignite::songsDataIndex::NUM_SCENES))
					IgniteTrack::GetAppTrackInstance()->updateSelectionInfo();
				if (!IgniteSongConfig::getAppSongConfigInstance()->isAutoSaveEnabled())
				{
					_pSong->setSongDataUpdateStatus(true);
					updateSongEditIndication();
					//swingComp.setName("Swing*");
					_pSong->enableControlButton(IgniteControlOptions::SAVE, true);
					_pSong->enableControlButton(IgniteControlOptions::UNDO, true);
				}
				else if (_pSong->getSongData(mt::Ignite::songsDataIndex::NUM_SCENES) && (_pSong->getGlobalSwingState() || _pSong->getGlobalTempoState()))
					_pSong->saveGlobalSongDataOfScenes();
			}
		};

		swingComp.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		tracksComp.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		tracksComp.onApplyValueChanged = [this](int value, const juce::String& name)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			value++;
			if ((int)_pSong->getSongData(mt::Ignite::songsDataIndex::NUM_TRACKS_INDEX) != value)
				_pSong->setSongData(mt::Ignite::songsDataIndex::NUM_TRACKS_INDEX, value, false);
			if (!IgniteSongConfig::getAppSongConfigInstance()->isAutoSaveEnabled())
			{
				_pSong->setSongDataUpdateStatus(true);
				updateSongEditIndication();
				IgniteTrack::GetAppTrackInstance()->noOfTrackChaged(true);
				//tracksComp.setTitleText("Number of Tracks*");
				_pSong->enableControlButton(IgniteControlOptions::SAVE, true);
				_pSong->enableControlButton(IgniteControlOptions::UNDO, true);
			}
		};

		sceneCBox.onSelectionChanged = [this](int value, const juce::String&)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			//if ((int)_pSong->getSongData(mt::Ignite::songsDataIndex::CURRENT_SCENE) != value)
			//	sceneCBox.setTitleText("Current Scene*");
			if (*sceneList.begin() != "No Scene")
				_pSong->setSongData(mt::Ignite::songsDataIndex::CURRENT_SCENE, value, false);

			if (!IgniteSongConfig::getAppSongConfigInstance()->isAutoSaveEnabled())
			{
				_pSong->setSongDataUpdateStatus(true);
				updateSongEditIndication();
				_pSong->enableControlButton(IgniteControlOptions::SAVE, true);
			}
			//_pSong->enableControlButton(IgniteControlOptions::UNDO, true);
			sceneCBox.setBackgroundColour(Theme::Instance().getColour(customEerieBlack));
			resized();
		};

		nextCSceneBox.onSelectionChanged = [this](int value, const juce::String&)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			//if ((int)_pSong->getSongData(mt::Ignite::songsDataIndex::NEXT_SCENE) != value)
				//nextCSceneBox.setTitleText("Next Scene*");
			if (*nextSceneList.begin() != "No Scene")
				_pSong->setSongData(mt::Ignite::songsDataIndex::NEXT_SCENE, value, false);
			if (!IgniteSongConfig::getAppSongConfigInstance()->isAutoSaveEnabled())
			{
				_pSong->setSongDataUpdateStatus(true);
				updateSongEditIndication();
				_pSong->enableControlButton(IgniteControlOptions::SAVE, true);
				//_pSong->enableControlButton(IgniteControlOptions::UNDO, true);
			}
			nextCSceneBox.setBackgroundColour(Theme::Instance().getColour(customEerieBlack));
			resized();
		};

		sceneInSong.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		nextCSceneBox.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		sceneCBox.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		tapTempo.onFocusChanged = [this](bool a)
		{
			repaint();
		};

	}

	AppSongView::~AppSongView()
	{
	}

	void AppSongView::labelTextChanged(Label* labelThatHasChanged)
	{
		if (labelThatHasChanged == &nameLabel)
		{
			if (!IgniteSongConfig::getAppSongConfigInstance()->isAutoSaveEnabled())
			{
				_pSong->setSongDataUpdateStatus(true);
				updateSongEditIndication();
			}
			_pSong->setSongData(mt::Ignite::songsDataIndex::SONG_NAME, nameLabel.getText(), false);
		}
	}
	void AppSongView::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &showSceneList)
		{
			AppMainmode::getMainModeInstance()->changeTabVisibility(mt::Ignite::tabs::SCENE, true);
			AppMainmode::getMainModeInstance()->setActiveTab(mt::Ignite::tabs::SCENE);
			if (showSceneList.getToggleState())
				showSceneList.setToggleState(false, dontSendNotification);
		}
		else if (buttonThatWasClicked == &tracklist)
		{
			if (_pSong->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
			{
				AppMainmode::getMainModeInstance()->triggerTabChange(mt::Ignite::tabs::TRACK);
				IgniteTrack::GetAppTrackInstance()->changeTrackOptionsVisibility(IgniteTrack::trackScreenIndex::TRACK_WINDOW);
				tracklist.setToggleState(false, dontSendNotification);
			}
		}
		else if (&swingAppliedtoScene == buttonThatWasClicked)
		{
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::paramApplySongSwingToScenes, swingAppliedtoScene.getToggleState());
			_pSong->setGlobalSwingState(swingAppliedtoScene.getToggleState());
			if (_pSong->getSongData(mt::Ignite::songsDataIndex::NUM_SCENES))
				IgniteTrack::GetAppTrackInstance()->updateSelectionInfo();
			_pSong->setEditIndication(true);
		}
		else if (&tempoAppliedtoScene == buttonThatWasClicked)
		{
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::paramApplySongTempoToScenes, tempoAppliedtoScene.getToggleState());
			_pSong->setGlobalTempoState(tempoAppliedtoScene.getToggleState());
			if (_pSong->getSongData(mt::Ignite::songsDataIndex::NUM_SCENES))
				IgniteTrack::GetAppTrackInstance()->updateSelectionInfo();
			_pSong->setEditIndication(true);
		}
		else if (&cScene == buttonThatWasClicked)
		{
			sceneCBox.showList();
		}
		else if (&nScene == buttonThatWasClicked)
		{
			nextCSceneBox.showList();
		}	
	}

	void AppSongView::updateSceneLists(mt::Ignite::songData* songdata)
	{
		std::vector<mt::Ignite::sceneData> scene_data = songdata->scene_data;
		sceneList.erase(sceneList.begin(), sceneList.end());
		nextSceneList.erase(nextSceneList.begin(), nextSceneList.end());
		DBG(String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "Updating current and next scene in song detail page ");
		if (!songdata->num_scenes)
		{
			sceneList.push_back("No Scene");
			nextSceneList.push_back("No Scene");
			sceneCBox.updateListOptions(sceneList, 0);
			nextCSceneBox.updateListOptions(nextSceneList, 0);
		}

		for (auto i = 0; i < songdata->num_scenes; i++)
		{
			sceneList.push_back(scene_data[i].name);
			sceneCBox.updateListOptions(sceneList, i);
			nextSceneList.push_back(scene_data[i].name);
			nextCSceneBox.updateListOptions(nextSceneList, i);
		}
		sceneCBox.setSelected(songdata->current_scene);
		nextCSceneBox.setSelected(songdata->next);
		sceneCBox.setBackgroundColour(Theme::Instance().getColour(customEerieBlack));
		nextCSceneBox.setBackgroundColour(Theme::Instance().getColour(customEerieBlack));
		resized();
	}

	void AppSongView::updateSongEditIndication()
	{
		String songNameString = _pSong->getSongData(mt::Ignite::songsDataIndex::SONG_NAME);

		if (_pSong->getSongDataUpdateStatus() && !_pSong->isGlobalAutosaveEnabled())
			songNameString = songNameString + "*";

		nameLabel.setText(songNameString, dontSendNotification);
	}

	void AppSongView::updateActiveTracks()
	{
		auto opMode = optPtr->getOperationMode();
		if ((opMode != mt::Ignite::operatioMode::PLAY_MODE) || (opMode != mt::Ignite::operatioMode::PLAY_REC_MODE))
		{
			sceneCBox.setSelected((int)_pSong->getSongData(mt::Ignite::songsDataIndex::CURRENT_SCENE));
			nextCSceneBox.setSelected((int)_pSong->getSongData(mt::Ignite::songsDataIndex::NEXT_SCENE));
			if (gSongs.getReference(_pSong->getSelected()).sceneCreated)
			{
				auto t = _pSong->getActiveTracks();
				activeTrackC.setText((t ? String(t) : "No") + " Active Tracks", dontSendNotification);
				t = _pSong->getActiveTracksNext();
				activeTrackN.setText((t ? String(t) : "No") + " Active Tracks", dontSendNotification);
				repaint();
			}
		}
	}

	void AppSongView::refreshData(int SerialNumber, mt::Ignite::songData* songdata)
	{
		if (_pSong->isVisible())
		{
			updateSongEditIndication();
			sceneInSong.setValue(_pSong->getSongData(mt::Ignite::songsDataIndex::NUM_SCENES));
			tempoComp.setText(String((float)_pSong->getSongData(mt::Ignite::songsDataIndex::TEMPO), 1), dontSendNotification);
			swingComp.setText(String(_pSong->getSongData(mt::Ignite::songsDataIndex::SWING).toString()), dontSendNotification);
			tracksComp.setSelected((int)_pSong->getSongData(mt::Ignite::songsDataIndex::NUM_TRACKS_INDEX) - 1);
			swingAppliedtoScene.setToggleState(_pSong->getGlobalSwingState(), dontSendNotification);
			tempoAppliedtoScene.setToggleState(_pSong->getGlobalTempoState(), dontSendNotification);
			updateActiveTracks();
		}
	}

	void AppSongView::updateScene(mt::Ignite::songData* songdata, int sceneActiveTracks, int nextSceneActiveTracks)
	{
		//if (_pSong->isVisible())
		{
			sceneCBox.setSelected((int)_pSong->getSongData(mt::Ignite::songsDataIndex::CURRENT_SCENE));
			nextCSceneBox.setSelected((int)_pSong->getSongData(mt::Ignite::songsDataIndex::NEXT_SCENE));
			auto t = _pSong->getActiveTracks();
			activeTrackC.setText((t ? String(t) : "No") + " Active Tracks", dontSendNotification);
			t = _pSong->getActiveTracksNext();
			activeTrackN.setText((t ? String(t) : "No") + " Active Tracks", dontSendNotification);
		}
	}


	void AppSongView::updateLableText(mt::Ignite::songsDataIndex item_id, bool state)
	{
		//switch (item_id)
		//{
		//case mt::Ignite::songsDataIndex::TEMPO:
		//	state ? tempoComp.setName("Tempo*") : tempoComp.setName("Tempo");
		//	break;
		//case mt::Ignite::songsDataIndex::SWING:
		//	state ? swingComp.setName("Swing*") : swingComp.setName("Swing");
		//	break;
		//case mt::Ignite::songsDataIndex::NUM_TRACKS_INDEX:
		//	state ? tracksComp.setTitleText("Number of Tracks*") : tracksComp.setTitleText("Number of Tracks");
		//	break;
		//case mt::Ignite::songsDataIndex::CURRENT_SCENE:
		//	//state ? sceneCBox.setTitleText("Current Scene*") : sceneCBox.setTitleText("Current Scene");
		//	break;
		//case mt::Ignite::songsDataIndex::NEXT_SCENE:
		//	//state ? nextCSceneBox.setTitleText("Next Scene*") : nextCSceneBox.setTitleText("Next Scene");
		//	break;
		//}
	}

	void AppSongView::getAssets()
	{

		imageAllSceneDefault= juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-allscene-default.png"));
		imageAllSceneActive = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-allscene-active.png"));
		imageAllSceneDisable = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-allscene-default-hover.png"));

		imageSwingApptoSceneDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("sml-btn-toggle-no-default.png"));
		imageSwingApptoSceneActive = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("sml-btn-toggle-yes-default.png"));

		imageTempoApptoSceneDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("sml-btn-toggle-no-default.png"));
		imageTempoApptoSceneActive = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("sml-btn-toggle-yes-default.png"));

		imageSongHeader= juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("song-bg-activesong.png"));

		imageBgContainerSmallDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("song-bg-container-short1-default.png"));
		imageBgContainerSmallActive = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("song-bg-container-short1-hover.png"));

		imageBgContainerLowerHover= juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("song-bg-container-lower-hover.png"));
		imageBgContainerLowerDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("song-bg-container-lower-default.png"));
		imageBgContainerLongDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("song-bg-container-long-default.png"));
		imageBgContainerLongHover	 = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("song-bg-container-long-hover.png"));
		imageBgContainer2ShortDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("song-bg-container-short2-default.png"));
		imageBgContainer2ShortHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("song-bg-container-short2-hover.png"));
		imageDividerHorz= juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("divider-horizontal.png"));

		imageSongTempoDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("song-taptempo-default.png"));
		imageSongTempoHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("song-taptempo-hover.png"));
		imageSongTempoClick = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("song-taptempo-clicked.png"));

		showSceneList.setImage(imageAllSceneDefault, imageAllSceneActive, imageAllSceneDisable);
		swingAppliedtoScene.setImage(imageSwingApptoSceneDefault, imageSwingApptoSceneActive);
		tempoAppliedtoScene.setImage(imageSwingApptoSceneDefault, imageSwingApptoSceneActive);
	}

	void AppSongView::paint(juce::Graphics& g)
	{
		g.drawImage(imageSongHeader, ui::Rectangle<float>{ xStartSongRow, yStartSongRow, widthSongRow, heightSongRow }, RectanglePlacement::centred);

		g.drawImage(tracksComp.getFocusState() ? imageBgContainerSmallActive : imageBgContainerSmallDefault, ui::Rectangle<float>{ 337, yStartBox1, 330, 164 }, RectanglePlacement::centred);

		g.drawImage(swingComp.getFocusState() ? imageBgContainerSmallActive : imageBgContainerSmallDefault, ui::Rectangle<float>{ 0, yStartBox1, 330, 104 }, RectanglePlacement::stretchToFit);
		g.drawImage(tempoComp.getFocusState() ? imageBgContainerSmallActive : imageBgContainerSmallDefault, ui::Rectangle<float>{ 674, yStartBox1, 330, 104 }, RectanglePlacement::stretchToFit);

		g.drawImage( btnSwingAppliedtoScene.isFocused  ? imageBgContainerLowerHover : imageBgContainerLowerDefault, ui::Rectangle<float>{ 0, 158, 330, 60 }, RectanglePlacement::centred);

		g.drawImage(btnTempoAppliedtoScene.isFocused ? imageBgContainerLowerHover : imageBgContainerLowerDefault, ui::Rectangle<float>{ 674, 158, 330, 60 }, RectanglePlacement::centred);

		g.drawImage(sceneInSong.getFocusState() ? imageBgContainer2ShortHover : imageBgContainer2ShortDefault, ui::Rectangle<float>{ 0,226, 330, 180 }, RectanglePlacement::centred);

		g.drawImage((sceneCBox.getFocusState()) ? imageBgContainerLongHover : imageBgContainerLongDefault, ui::Rectangle<float>{ 337, 226, 330, 86 }, RectanglePlacement::centred);
		g.drawImage((nextCSceneBox.getFocusState()) ? imageBgContainerLongHover : imageBgContainerLongDefault, ui::Rectangle<float>{ 337, 320, 330, 86 }, RectanglePlacement::centred);

		Font a((float)(32));

		auto l = a.getStringWidth(sceneCBox.getSelected());
		g.setColour(Theme::Instance().getColour(customBlue19));
		if (l < 180)
			g.fillRect(352 + l, 274, 2, 25);
		else
			g.fillRect(505, 274, 2, 25);

		l = a.getStringWidth(nextCSceneBox.getSelected());
		g.setColour(Theme::Instance().getColour(customBlue19));
		if (l < 180)
			g.fillRect(352 + l, 368, 2, 25);
		else
			g.fillRect(505, 368, 2, 25);

		//	g.setColour(Colour(0xFF2697D2).withAlpha(0.25f));
		//	g.fillRect(0, yStartBox1 + 104, 330, 1);
		//	g.fillRect(676, yStartBox1 + 104, 330, 1);

		g.setColour(Theme::Instance().getColour(customOrange));
		g.setFont(20.0f);
		l = a.getStringWidth(sceneCBox.getSelected());
		if (l < 180)
			g.drawText(activeTrackC.getText(), ui::Rectangle{ 362 + l, 276, 222, 25 }, Justification::left, true);
		else
			g.drawText(activeTrackC.getText(), ui::Rectangle{ 514 , 276, 222, 25 }, Justification::left, true);

		g.setColour(Theme::Instance().getColour(customOrange));
		g.setFont(20.0f);
		l = a.getStringWidth(nextCSceneBox.getSelected());
		if (l < 180)
			g.drawText(activeTrackN.getText(), ui::Rectangle{ 362 + l, 370, 222, 25 }, Justification::left, true);
		else
			g.drawText(activeTrackN.getText(), ui::Rectangle{ 514, 370, 222, 25 }, Justification::left, true);

		g.drawImage(tapTempo.getClickState() ? imageSongTempoClick : (tapTempo.getFocusState() ? imageSongTempoHover : imageSongTempoDefault), ui::Rectangle<float>{ 674, 218, 330, 188 }, RectanglePlacement::centred);

	}

	void AppSongView::resized()
	{
		Font a((float)(32));
		auto l = a.getStringWidth(sceneCBox.getSelected());
		sceneBox.performLayout(ui::Rectangle(xStartBox1, yStartBox1, widthBox1, heightBox));
		showSceneList.setBounds(64, 339, 202, 44);
		sceneInSong.setBounds(0, 226, 330, 125);
		sceneCBox.setBounds(338, 232, 180, 86);
		cScene.setBounds(338, 226, 330, 86);
		cScene.toFront(true);
		nextCSceneBox.setBounds(338, 326, 180, 86);
		nScene.setBounds(338, 319, 330, 86);
		nScene.toFront(true);

		//activeTrackC.setBounds(390 + l, 269, 222, 25);
		l = a.getStringWidth(nextCSceneBox.getSelected());
		//activeTrackN.setBounds(390 + l, 363, 222, 25);
		swingAppliedtoScene.setBounds(50, yStartBox1 + 118, 74, 32);

		btnSwingAppliedtoScene.setBounds(0, 158, 330, 60);
		btnTempoAppliedtoScene.setBounds(674, 158, 330, 60);
		tempoToScene.setBounds(129, yStartBox1 + 118, 206, 32);
		tempoAppliedtoScene.setBounds(726, yStartBox1 + 118, 74, 32);
		swingToScene.setBounds(804, yStartBox1 + 118, 206, 32);
		tracklist.setBounds(400, 158, 202, 44);
		tapTempo.setBounds(674, 218, 330, 188);
		sceneCBox.toFront(true);
		swingHover.setBounds(0, 158, 330, 60);
		tempoHover.setBounds(674, 158, 330, 60);
		showSceneList.toFront(true);

		swingHover.toFront(true);
		btnSwingAppliedtoScene.toFront(true);
		swingAppliedtoScene.toFront(true);
		tempoHover.toFront(true);
		btnTempoAppliedtoScene.toFront(true);

		tempoAppliedtoScene.toFront(true);
	}

	int AppSongView::isEditing()
	{
		int index = 0;
		swingComp.IsEditing() ? index = 1 : 0;
		tracksComp.IsEditing() ? index = 3 : 0;
		tempoComp.IsEditing() ? index = 5 : 0;
		sceneCBox.IsEditing() ? index = 8 : 0;
		nextCSceneBox.IsEditing() ? index = 9 : 0;

		return index;
	}

	bool AppSongView::pannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool setfocus = true;
		int EditItem = songDetailsViewItemID::NO_FOCUS;

		if (keyFocusedItem == songDetailsViewItemID::NO_FOCUS)
		{
			/*1st key after Page visible */
			keyFocusedItem = songDetailsViewItemID::SWING;
		}
		else
		{
			EditItem = isEditing();
			if (EditItem)
			{
				if (keyFocusedItem != EditItem)
				{
					pannelSendKey(false, param, KeyValue);
					keyFocusedItem = EditItem;
				}
				setfocus = true;
			}
			else
			{
				
				pannelSendKey(false, param, KeyValue); // clear last Focus
				switch ((FrontPannelParam)param)
				{
				case FrontPannelParam::paramKey_RMOVELEFT:
					keyFocusedItem = (keyFocusedItem + 1 >= songDetailsViewItemID::FOCUS_MAX ? (songDetailsViewItemID::FOCUS_MAX) : keyFocusedItem + 1);
					break;
				case FrontPannelParam::paramKey_RMOVERIGHT:
					keyFocusedItem = (keyFocusedItem - 1 <= songDetailsViewItemID::NO_FOCUS ? (songDetailsViewItemID::NO_FOCUS + 1) : keyFocusedItem - 1);
					break;
				case FrontPannelParam::paramRot_ROW:

					if ((keyFocusedItem == NUM_TRACKS || keyFocusedItem == CURRENT_SCENE || keyFocusedItem == SWING || keyFocusedItem == TEMPO) && KeyValue == ROTARY_DIRECTION_RIGHT || ((keyFocusedItem == SWING_TO_SCENE || keyFocusedItem == NEXT_SCENE || keyFocusedItem == TEMPO_TO_SCENE || keyFocusedItem == VIEW_TRACKS) && KeyValue == ROTARY_DIRECTION_LEFT))
						numItemsInRow = 1;
					else if (((keyFocusedItem == VIEW_TRACKS || keyFocusedItem == TEMPO_TO_SCENE) && KeyValue == ROTARY_DIRECTION_RIGHT) || ((keyFocusedItem == CURRENT_SCENE || keyFocusedItem == TAP_TEMPO) && KeyValue == ROTARY_DIRECTION_LEFT))
						numItemsInRow = 4;
					else if (keyFocusedItem == SHOW_SCENE_LIST || ((keyFocusedItem == SWING_TO_SCENE) && KeyValue == ROTARY_DIRECTION_RIGHT) || (keyFocusedItem == TEMPO && KeyValue == ROTARY_DIRECTION_LEFT))
						numItemsInRow = 5;
					else
						numItemsInRow = 3;

					if (KeyValue == ROTARY_DIRECTION_RIGHT)
					{
						pannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
						keyFocusedItem = (keyFocusedItem + numItemsInRow >= songDetailsViewItemID::FOCUS_MAX ? ((keyFocusedItem + numItemsInRow) == (songDetailsViewItemID::FOCUS_MAX) ? (songDetailsViewItemID::FOCUS_MAX) : keyFocusedItem) : keyFocusedItem + numItemsInRow);
						pannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
					}
					else
					{
						pannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVELEFT, 0x48);
						keyFocusedItem = (keyFocusedItem - numItemsInRow <= songDetailsViewItemID::NO_FOCUS ? (keyFocusedItem) : keyFocusedItem - numItemsInRow);
						pannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RMOVELEFT, 0x48);
					}
					repaint();
					setfocus = false;
					break;
				}
			}
		}
		if (setfocus)
		{
			pannelSendKey(true, param, KeyValue);
		}
		return true;
	}

	void AppSongView::pannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		switch (songDetailsView[keyFocusedItem])
		{
		case SWING:
			swingComp.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case SWING_TO_SCENE:
			swingAppliedtoScene.FPKeyHandler(isFocuse, param, 0);
			btnSwingAppliedtoScene.FPKeyHandler(isFocuse, param, 0);
			break;
		case TEMPO:
			tempoComp.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case TEMPO_TO_SCENE:
			tempoAppliedtoScene.FPKeyHandler(isFocuse, param, 0);
			btnTempoAppliedtoScene.FPKeyHandler(isFocuse, param, 0);
			break;
		case NUM_TRACKS:
			tracksComp.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case CURRENT_SCENE:
			sceneCBox.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case NEXT_SCENE:
			nextCSceneBox.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case SHOW_SCENE_LIST:
			if (param != (paramId_t)FrontPannelParam::paramKey_RSELECT)
				sceneInSong.FPKeyHandler(isFocuse, param, KeyValue);
			else
				showSceneList.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case VIEW_TRACKS:
			tracklist.setState((Button::ButtonState)isFocuse);
			tracklist.FPKeyHandler(isFocuse, param, 0);
			break;
		case TAP_TEMPO:
			tapTempo.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		default:
			break;
		}
	}

	void AppSongView::resetSongFocuse(String a)
	{
		int NewFocusedItem = songDetailsViewItemID::NO_FOCUS;
		//auto a = event.eventComponent->getComponentID();

		if (a == "swingComp")					NewFocusedItem = songDetailsViewItemID::SWING;
		else if (a == "swingAppliedtoScene" || a == "btnSwingAppliedtoScene")	NewFocusedItem = songDetailsViewItemID::SWING_TO_SCENE;
		else if (a == "tempoComp")				NewFocusedItem = songDetailsViewItemID::TEMPO;
		else if (a == "tempoAppliedtoScene" || a == "btnTempoAppliedtoScene")	NewFocusedItem = songDetailsViewItemID::TEMPO_TO_SCENE;
		else if (a == "tracksComp")				NewFocusedItem = songDetailsViewItemID::NUM_TRACKS;
		else if (a == "showSceneList")			NewFocusedItem = songDetailsViewItemID::SHOW_SCENE_LIST;
		else if (a == "sceneCBox")				NewFocusedItem = songDetailsViewItemID::CURRENT_SCENE;
		else if (a == "nextCSceneBox")			NewFocusedItem = songDetailsViewItemID::NEXT_SCENE;

		if (NewFocusedItem != songDetailsViewItemID::NO_FOCUS && NewFocusedItem != keyFocusedItem)
		{
			pannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_MouseClick, 0);
			keyFocusedItem = NewFocusedItem;
			pannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_MouseClick, 0);
		}
	}

	void AppSongView::timerCallback()
	{
		setTapTempo(FrountPannel::GetFrountPannelInstance()->getTapTempoValue(), false, false);
		stopTimer();
	}
	void AppSongView::mouseDown(const MouseEvent& event)
	{
		auto comp_id = event.eventComponent->getComponentID();
		if ((comp_id != ""))
		{
			int a = std::stoi((comp_id.toStdString()));
			pannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_MouseClick, 1);
			keyFocusedItem = a;
			pannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_MouseClick, 1);
		}

		if (comp_id != String(TAP_TEMPO))
		{
			tapTempo.resetTapTempoData();
		}
	}

	void AppSongView::setTapTempo(float value, bool sendTempoAsPlayModeData, bool timerStart)
	{
		if (timerStart)
			startTimer(TIMER_TIMEOUT_UPDATE_TEMPO_MILLISECOND);

		_pSong->setSongData(mt::Ignite::songsDataIndex::TEMPO, value, false);

		if (_pSong->getSongData(mt::Ignite::songsDataIndex::NUM_SCENES))
			IgniteTrack::GetAppTrackInstance()->updateSelectionInfo();

		if (!IgniteSongConfig::getAppSongConfigInstance()->isAutoSaveEnabled())
		{
			_pSong->setSongDataUpdateStatus(true);
			updateSongEditIndication();
			_pSong->enableControlButton(IgniteControlOptions::SAVE, true);
			_pSong->enableControlButton(IgniteControlOptions::UNDO, true);
		}
		else if (_pSong->getSongData(mt::Ignite::songsDataIndex::NUM_SCENES) && (_pSong->getGlobalSwingState() || _pSong->getGlobalTempoState()))
			_pSong->saveGlobalSongDataOfScenes();
	}
};
