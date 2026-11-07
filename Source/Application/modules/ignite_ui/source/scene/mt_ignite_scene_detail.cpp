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
	AppSceneView::AppSceneView(IgniteScene* scenePtr)
	{
		_pScene = scenePtr;
		addAndMakeVisible(ftsRootNote);
		ftsRootNote.updateListOptions(rootNotes);
		ftsRootNote.setSelected(0);
		ftsRootNote.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		ftsRootNote.setValueColour(Theme::Instance().getColour(customOrange));

		addAndMakeVisible(ftsScale);
		ftsScale.updateListOptions(scaleList);
		ftsScale.setSelected(0);
		ftsScale.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		ftsScale.setValueColour(Theme::Instance().getColour(customOrange));

		gbarComp.makeVisible(this);
		lenComp.makeVisible(this);
		xposeComp.makeVisible(this);
		swingComp.makeVisible(this);
		tempoComp.makeVisible(this);
		tempoComp.setNumDecimalPlacesToDisplay(1);

		addAndMakeVisible(songAdv);
		songAdv.updateListOptions(songAdvOptions);
		songAdv.setSelected(0);
		songAdv.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		songAdv.setValueColour(Theme::Instance().getColour(customOrange));

		addAndMakeVisible(muteHold);
		muteHold.updateListOptions(muteHolfOptions);
		muteHold.setSelected(0);
		muteHold.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		muteHold.setValueColour(Theme::Instance().getColour(customOrange));

		xfts.makeVisibleAndAddListner(this);
		xfts.setLookAndFeel(EmptyTextBackgroundLooknFeel::getLnf());
		xfts.setClickingTogglesState(false);
		xfts.setToggleable(true);

		gbarComp.setDisplayTitle(true);
		lenComp.setDisplayTitle(true);
		xposeComp.setDisplayTitle(true);
		swingComp.setDisplayTitle(true);
		tempoComp.setDisplayTitle(true);

		swingComp.setJustificationType(juce::Justification::centred);
		tempoComp.setJustificationType(juce::Justification::centred);

		swingComp.setcustombounds(true, ui::Rectangle<int>{98, 3, 135, 60}, ui::Rectangle<int>{90, 35, 150, 50});
		gbarComp.setcustombounds(true, ui::Rectangle<int>{98, 3, 135, 60}, ui::Rectangle<int>{90, 35, 150, 50});
		lenComp.setcustombounds(true, ui::Rectangle<int>{98, 3, 135, 60}, ui::Rectangle<int>{90, 35, 150, 50});
		tempoComp.setcustombounds(true, ui::Rectangle<int>{98, 3, 135, 60}, ui::Rectangle<int>{90, 35, 150, 50});
		xposeComp.setcustombounds(true, ui::Rectangle<int>{98, 3, 135, 60}, ui::Rectangle<int>{90, 35, 150, 50});

		gbarComp.setJustificationType(juce::Justification::centred);
		lenComp.setJustificationType(juce::Justification::centred);
		xposeComp.setJustificationType(juce::Justification::centred);

		addAndMakeVisible(tapTempo);

		nameLabel.makeVisibleAndAddListner(this);
		nameLabel.setDisplayTitle(false);
		nameLabel.setEditable(false, true, false);
		nameLabel.setJustificationType(Justification::centred);
		nameLabel.setBounds(xStartSongRow, yStartSongRow, widthSongRow, heightSongRow);

		sceneBox1.items.add(FlexItem(swingComp).withMargin(0).withFlex(1));
		sceneBox1.items.add(FlexItem(gbarComp).withMargin(0).withFlex(1));
		sceneBox1.items.add(FlexItem(muteHold).withMargin(0).withFlex(1));

		sceneBox2.items.add(FlexItem(lenComp).withMargin(0).withFlex(1));
		sceneBox2.items.add(FlexItem(songAdv).withMargin(0).withFlex(1));
		sceneBox2.items.add(FlexItem(tempoComp).withMargin(0).withFlex(1));

		sceneBox3.items.add(FlexItem(ftsRootNote).withMargin(0).withFlex(1));
		sceneBox3.items.add(FlexItem(ftsScale).withMargin(0).withFlex(1));

		sceneBox4.items.add(FlexItem(xfts).withMargin(0).withFlex(1));
		sceneBox4.items.add(FlexItem(xposeComp).withMargin(0).withFlex(1));

		tempoComp.setTextColour(Theme::Instance().getColour(customOrange));
		swingComp.setTextColour(Theme::Instance().getColour(customOrange));
		gbarComp.setTextColour(Theme::Instance().getColour(customOrange));
		lenComp.setTextColour(Theme::Instance().getColour(customOrange));
		xposeComp.setTextColour(Theme::Instance().getColour(customOrange));
		const juce::Rectangle<int> bonds{ (0),(0),604,235 };
		muteHold.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, bonds);
		muteHold.setBackgroundColour(Theme::Instance().getColour(customEerieBlack));
		muteHold.setTextColour(Theme::Instance().getColour(customBlue4));

		const juce::Rectangle<int> bonds1{ (0),(0),604,235 };
		songAdv.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, bonds1);
		songAdv.setBackgroundColour(Theme::Instance().getColour(customEerieBlack));
		songAdv.setTextColour(Theme::Instance().getColour(customBlue4));

		ftsScale.setDailogViewType(mt::Ignite::DailogViewType::CustomView, false);
		ftsScale.setBackgroundColour(Theme::Instance().getColour(customEerieBlack));
		ftsScale.setTextColour(Theme::Instance().getColour(customBlue4));
		ftsScale.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, ui::Rectangle{ 0,0,604,450 });
		songAdv.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, ui::Rectangle{ 0,0,604,450 });

		ftsRootNote.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, ui::Rectangle{ 0,0,604,450 });
		_pSceneConfigComp = IgniteSceneConfig::getAppSceneConfigInstance();
		optPtr = IgniteControlOptions::GetAppOptInstance();
		_pSong = IgniteSong::getAppSongInstance();
		getAssets();

		tapTempo.getTapConfigValue = [this]()
		{
			return (int)_pSceneConfigComp->tapConfig.getValue();
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
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleScene, (paramId_t)SceneParam::paramUndoCmd, 0, false);

			_pScene->setSceneData(mt::Ignite::sceneDataIndex::SCENE_TEMPO, (float)value, false);

			if (!IgniteSceneConfig::getAppSceneConfigInstance()->isAutoSaveEnabled())
				_pScene->updateSceneEditIndication(true);
			IgniteTrack::GetAppTrackInstance()->updateSelectionInfo();
		};
#endif

		swingComp.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			_pScene->setSceneData(mt::Ignite::sceneDataIndex::SCENE_SWING, uint8_t(value), false);

			if (!IgniteSceneConfig::getAppSceneConfigInstance()->isAutoSaveEnabled())
				_pScene->updateSceneEditIndication(true);

			IgniteTrack::GetAppTrackInstance()->updateSelectionInfo();
		};

		swingComp.onPlayTimeValueChanged = [this](int value)
		{
			auto opMode = optPtr->getOperationMode();
			if ((opMode == mt::Ignite::operatioMode::PLAY_MODE) || (opMode == mt::Ignite::operatioMode::PLAY_REC_MODE))
			{
				Component::BailOutChecker checker(this);

				if (checker.shouldBailOut())
					return;

				_pScene->setSceneData(mt::Ignite::sceneDataIndex::SCENE_SWING, uint8_t(value), false);

				if (!IgniteSceneConfig::getAppSceneConfigInstance()->isAutoSaveEnabled())
					_pScene->updateSceneEditIndication(true);

				IgniteTrack::GetAppTrackInstance()->updateSelectionInfo();
			}
		};

		tempoComp.onFloatValueChanged = [this](float value)
		{
			if ((int)_pScene->getSceneData(mt::Ignite::sceneDataIndex::SCENE_TEMPO) != value)
			{
				Component::BailOutChecker checker(this);

				if (checker.shouldBailOut())
					return;

				if (!IgniteSceneConfig::getAppSceneConfigInstance()->isAutoSaveEnabled())
					_pScene->updateSceneEditIndication(true);

				_pScene->setSceneData(mt::Ignite::sceneDataIndex::SCENE_TEMPO, (float)value, false);
				IgniteTrack::GetAppTrackInstance()->updateSelectionInfo();
			}
		};

		tempoComp.onPlayTimeFloatValueChanged = [this](float value)
		{
			auto opMode = optPtr->getOperationMode();
			if ((opMode == mt::Ignite::operatioMode::PLAY_MODE) || (opMode == mt::Ignite::operatioMode::PLAY_REC_MODE))
			{
				Component::BailOutChecker checker(this);

				if (checker.shouldBailOut())
					return;

				if (!IgniteSceneConfig::getAppSceneConfigInstance()->isAutoSaveEnabled())
					_pScene->updateSceneEditIndication(true);

				_pScene->setSceneData(mt::Ignite::sceneDataIndex::SCENE_TEMPO, (float)value, false);
				IgniteTrack::GetAppTrackInstance()->updateSelectionInfo();
			}
		};

		gbarComp.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			if (!IgniteSceneConfig::getAppSceneConfigInstance()->isAutoSaveEnabled())
				_pScene->updateSceneEditIndication(true);

			_pScene->setSceneData(mt::Ignite::sceneDataIndex::GBAR, (uint8_t)value, false);
		};

		lenComp.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			if (!IgniteSceneConfig::getAppSceneConfigInstance()->isAutoSaveEnabled())
				_pScene->updateSceneEditIndication(true);

			SceneStatusBar::GetSceneBarInstance()->onNumofBarchangedinScene(value);
			_pScene->setSceneData(mt::Ignite::sceneDataIndex::LENGHT, value, false);
		};

		xposeComp.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			if (!IgniteSceneConfig::getAppSceneConfigInstance()->isAutoSaveEnabled())
				_pScene->updateSceneEditIndication(true);

			_pScene->setSceneData(mt::Ignite::sceneDataIndex::XPOSE, (int8_t)value, false);
			IgniteTrack::GetAppTrackInstance()->updateSelectionInfo();

		};

		gbarComp.onPlayTimeValueChanged = [this](int value)
		{
			auto opMode = optPtr->getOperationMode();
			if ((opMode == mt::Ignite::operatioMode::PLAY_MODE) || (opMode == mt::Ignite::operatioMode::PLAY_REC_MODE))
			{
				Component::BailOutChecker checker(this);

				if (checker.shouldBailOut())
					return;

				if (!IgniteSceneConfig::getAppSceneConfigInstance()->isAutoSaveEnabled())
					_pScene->updateSceneEditIndication(true);

				_pScene->setSceneData(mt::Ignite::sceneDataIndex::GBAR, (uint8_t)value, false);
			}
		};

		lenComp.onPlayTimeValueChanged = [this](int value)
		{
		auto opMode = optPtr->getOperationMode();
			if ((opMode == mt::Ignite::operatioMode::PLAY_MODE) || (opMode == mt::Ignite::operatioMode::PLAY_REC_MODE))
			{
				Component::BailOutChecker checker(this);

				if (checker.shouldBailOut())
					return;

				if (!IgniteSceneConfig::getAppSceneConfigInstance()->isAutoSaveEnabled())
					_pScene->updateSceneEditIndication(true);

				SceneStatusBar::GetSceneBarInstance()->onNumofBarchangedinScene(value);
				_pScene->setSceneData(mt::Ignite::sceneDataIndex::LENGHT, value, false);
			}
		};

		xposeComp.onPlayTimeValueChanged = [this](int value)
		{
			auto opMode = optPtr->getOperationMode();
			if ((opMode == mt::Ignite::operatioMode::PLAY_MODE) || (opMode == mt::Ignite::operatioMode::PLAY_REC_MODE))
			{
				Component::BailOutChecker checker(this);

				if (checker.shouldBailOut())
					return;

				if (!IgniteSceneConfig::getAppSceneConfigInstance()->isAutoSaveEnabled())
					_pScene->updateSceneEditIndication(true);

				_pScene->setSceneData(mt::Ignite::sceneDataIndex::XPOSE, (int8_t)value, false);
				IgniteTrack::GetAppTrackInstance()->updateSelectionInfo();
			}
		};

		songAdv.onSelectionChanged = [this](int value, const juce::String&)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			if (!IgniteSceneConfig::getAppSceneConfigInstance()->isAutoSaveEnabled())
				_pScene->updateSceneEditIndication(true);

			_pScene->setSceneData(mt::Ignite::sceneDataIndex::SONGADV, (uint8_t)value, false);
		};

		ftsRootNote.onSelectionChanged = [this](int value, const juce::String&)
		{
			Component::BailOutChecker checker(this);
			if (checker.shouldBailOut())
				return;

			if (!IgniteSceneConfig::getAppSceneConfigInstance()->isAutoSaveEnabled())
				_pScene->updateSceneEditIndication(true);

			_pScene->setSceneData(mt::Ignite::sceneDataIndex::FTSROOTNOTE, (uint8_t)value, false);
			IgniteTrack::GetAppTrackInstance()->updateSelectionInfo();
		};

		ftsScale.onSelectionChanged = [this](int value, const juce::String&)
		{
			Component::BailOutChecker checker(this);
			if (checker.shouldBailOut())
				return;

			value++;

			if (!IgniteSceneConfig::getAppSceneConfigInstance()->isAutoSaveEnabled())
				_pScene->updateSceneEditIndication(true);

			if (value == 1)
			{
				ftsRootNote.setAlpha((float)0.2);
				ftsRootNote.setInterceptsMouseClicks(false, false);
			}
			else
			{
				ftsRootNote.setAlpha((float)1.0);
				ftsRootNote.setInterceptsMouseClicks(true, true);
			}
			_pScene->setSceneData(mt::Ignite::sceneDataIndex::FTSSCALE, (uint8_t)value, false);
			IgniteTrack::GetAppTrackInstance()->updateSelectionInfo();
		};

		muteHold.onSelectionChanged = [this](int value, const juce::String&)
		{
			Component::BailOutChecker checker(this);
			if (checker.shouldBailOut())
				return;

			if (!IgniteSceneConfig::getAppSceneConfigInstance()->isAutoSaveEnabled())
				_pScene->updateSceneEditIndication(true);

			_pScene->setSceneData(mt::Ignite::sceneDataIndex::MUTEHOLD, (uint8_t)value, false);
		};

		nameLabel.onValueChanged = [this](String value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;


			_pScene->setSceneData(mt::Ignite::sceneDataIndex::SCENE_NAME, value, false);
			IgniteTrack::GetAppTrackInstance()->updateSelectionInfo();
			if (!IgniteSceneConfig::getAppSceneConfigInstance()->isAutoSaveEnabled())
				_pScene->updateSceneEditIndication(true);
		};

		swingComp.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		tempoComp.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		gbarComp.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		lenComp.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		songAdv.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		muteHold.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		ftsRootNote.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		ftsScale.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		xposeComp.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		tapTempo.onFocusChanged = [this](bool a)
		{
			repaint();
		};

	}

	AppSceneView::~AppSceneView()
	{
	}

	void AppSceneView::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &xfts)
		{
			if (xfts.getToggleState())
				xfts.setToggleState(false, dontSendNotification);
			else
				xfts.setToggleState(true, dontSendNotification);

			_pScene->setSceneData(mt::Ignite::sceneDataIndex::XFTS, (uint8_t)xfts.getToggleState(), false);

			if (!IgniteSceneConfig::getAppSceneConfigInstance()->isAutoSaveEnabled())
				_pScene->updateSceneEditIndication(true);

		}
	}

	void AppSceneView::updateScaleList()
	{
		std::vector<IgniteParamList> udsParamList;
		IgniteParamList params;

		scaleList.clear();
		params.param = (paramId_t)SongParam::paramFtsNameList;
		udsParamList.push_back(params);
		udsParamList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, udsParamList);

		for (auto& i : udsParamList)
			scaleList.push_back(i.MsgValue.get<std::string>());

		ftsScale.updateListOptions(scaleList);
	}

	void AppSceneView::labelTextChanged(Label* labelThatHasChanged)
	{
		if (!IgniteSceneConfig::getAppSceneConfigInstance()->isAutoSaveEnabled())
			_pScene->updateSceneEditIndication(true);

		if (labelThatHasChanged == &optionsSceneName)
		{
			_pScene->setSceneData(mt::Ignite::sceneDataIndex::SCENE_NAME, optionsSceneName.getText(), false);
		}
		if (labelThatHasChanged == &nameLabel)
		{
			_pScene->setSceneData(mt::Ignite::sceneDataIndex::SCENE_NAME, nameLabel.getText(), false);
		}

		nameLabel.setText(nameLabel.getText(), dontSendNotification);
	}

	String AppSceneView::getListData(mt::Ignite::sceneDataIndex index)
	{
		switch (index)
		{
		case mt::Ignite::sceneDataIndex::MUTEHOLD:
			return muteHold.getSelected();
		case mt::Ignite::sceneDataIndex::SONGADV:
			return songAdv.getSelected();
		case mt::Ignite::sceneDataIndex::FTSROOTNOTE:
			return ftsRootNote.getSelected();
		case mt::Ignite::sceneDataIndex::FTSSCALE:
			return ftsScale.getSelected();
		}
		return String(-1);
	}
	void AppSceneView::refreshData(int SerialNumber, mt::Ignite::sceneData* scenedata)
	{
		if (_pScene->isVisible())
		{
			if (isFTSListUpdateNeeded)
			{
				updateScaleList();
				isFTSListUpdateNeeded = false;
			}
			nameLabel.setText(_pScene->getSceneData(mt::Ignite::sceneDataIndex::SCENE_NAME), dontSendNotification);
			optionsSceneName.setText(_pScene->getSceneData(mt::Ignite::sceneDataIndex::SCENE_NAME), dontSendNotification);
			serialNumLabel.setText(String(SerialNumber), dontSendNotification);
			gbarComp.setText(String(_pScene->getSceneData(mt::Ignite::sceneDataIndex::GBAR).toString()), dontSendNotification);
			xposeComp.setText(String((int8_t)(_pScene->getSceneData(mt::Ignite::sceneDataIndex::XPOSE).toString()).getIntValue()), dontSendNotification);
			lenComp.setText(String(_pScene->getSceneData(mt::Ignite::sceneDataIndex::LENGHT).toString()), dontSendNotification);
			swingComp.setText(String(_pScene->getSceneData(mt::Ignite::sceneDataIndex::SCENE_SWING).toString()), dontSendNotification);
			tempoComp.setText(String((float)_pScene->getSceneData(mt::Ignite::sceneDataIndex::SCENE_TEMPO), 1), dontSendNotification);
			muteHold.setSelected((int)_pScene->getSceneData(mt::Ignite::sceneDataIndex::MUTEHOLD));
			songAdv.setSelected((int)_pScene->getSceneData(mt::Ignite::sceneDataIndex::SONGADV));
			ftsRootNote.setSelected((int)_pScene->getSceneData(mt::Ignite::sceneDataIndex::FTSROOTNOTE));
			ftsScale.setSelected((int)_pScene->getSceneData(mt::Ignite::sceneDataIndex::FTSSCALE) - 1);
			if (!((int)_pScene->getSceneData(mt::Ignite::sceneDataIndex::FTSSCALE) - 1))
			{
				ftsRootNote.setAlpha((float)0.2);
				ftsRootNote.setInterceptsMouseClicks(false, false);
			}
			else
			{
				ftsRootNote.setAlpha((float)1.0);
				ftsRootNote.setInterceptsMouseClicks(true, true);
			}
			xfts.setToggleState((bool)_pScene->getSceneData(mt::Ignite::sceneDataIndex::XFTS), dontSendNotification);
		}
	}

	void AppSceneView::updateLableText(mt::Ignite::sceneDataIndex item_id, bool state)
	{
		switch (item_id)
		{
		case mt::Ignite::sceneDataIndex::SCENE_TEMPO:
			state ? tempoComp.setName("Tempo*") : tempoComp.setName("Tempo");
			break;
		case mt::Ignite::sceneDataIndex::SCENE_SWING:
			state ? swingComp.setName("Swing*") : swingComp.setName("Swing");
			break;
		case mt::Ignite::sceneDataIndex::GBAR:
			state ? gbarComp.setName("GBAR*") : gbarComp.setName("GBAR");
			break;
		case mt::Ignite::sceneDataIndex::LENGHT:
			state ? lenComp.setName("Length*") : lenComp.setName("Length");
			break;
		case mt::Ignite::sceneDataIndex::XPOSE:
			state ? xposeComp.setName("Xpose*") : xposeComp.setName("Xpose");
			break;
		case mt::Ignite::sceneDataIndex::MUTEHOLD:
			state ? muteHold.setTitleText("Mute Hold*") : muteHold.setTitleText("Mute Hold");
			break;
		case mt::Ignite::sceneDataIndex::SONGADV:
			state ? songAdv.setTitleText("Scene Advance*") : songAdv.setTitleText("Scene Advance");
			break;
		case mt::Ignite::sceneDataIndex::FTSROOTNOTE:
			state ? ftsRootNote.setTitleText("FTS: Root Note*") : ftsRootNote.setTitleText("FTS: Root Note");
			break;
		case mt::Ignite::sceneDataIndex::FTSSCALE:
			state ? ftsScale.setTitleText("FTS: Scale*") : ftsScale.setTitleText("FTS: Scale");
			break;
		case mt::Ignite::sceneDataIndex::XFTS:
			state ? xfts.setButtonText("Xpose: Post FTS") : xfts.setButtonText("Xpose: Pre FTS");
			break;
		}
	}
	void AppSceneView::getAssets()
	{
		imageSceneHeader = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("song-bg-activesong.png"));
		imageSceneBgContainerDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("bg-container-scene-default.png"));
		imageSceneBgContainerSelected = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("bg-container-scene-selected.png"));

		imageXposePostDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-xpose-post-default.png"));
		imageXposePostHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-xpose-post-hover.png"));
		imageXposePreDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-xpose-pre-default.png"));
		imageXposePreHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-xpose-pre-hover.png"));

		imageSongTempoDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("bg-taptempo-scene-default.png"));
		imageSongTempoHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("bg-taptempo-scene-selected.png"));
		imageSongTempoClick = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("bg-taptempo-scene-clicked.png"));
	}

	void AppSceneView::updateComponentState(Component& comp, bool state)
	{
		float inactiveAlpha = 0.2f;
		float activeAlpha = 1.0f;

		comp.setAlpha(state ? inactiveAlpha : activeAlpha);
		comp.setInterceptsMouseClicks(!state, !state);
	}

	void AppSceneView::paint(juce::Graphics& g)
	{
		g.drawImage(imageSceneHeader, ui::Rectangle<float>{ xStartSongRow, yStartSongRow, widthSongRow, heightSongRow }, RectanglePlacement::centred);

		g.drawImage(swingComp.getFocusState() ? imageSceneBgContainerSelected : imageSceneBgContainerDefault, ui::Rectangle<float>{ 0, 54, 328, 80 }, RectanglePlacement::centred);
		g.drawImage(gbarComp.getFocusState() ? imageSceneBgContainerSelected : imageSceneBgContainerDefault, ui::Rectangle<float>{ 338, 54, 328, 80 }, RectanglePlacement::centred);
		g.drawImage(muteHold.getFocusState() ? imageSceneBgContainerSelected : imageSceneBgContainerDefault, ui::Rectangle<float>{ 676, 54, 328, 80 }, RectanglePlacement::centred);

		g.drawImage(lenComp.getFocusState() ? imageSceneBgContainerSelected : imageSceneBgContainerDefault, ui::Rectangle<float>{ 0, 142, 328, 80 }, RectanglePlacement::centred);
		g.drawImage(songAdv.getFocusState() ? imageSceneBgContainerSelected : imageSceneBgContainerDefault, ui::Rectangle<float>{ 338, 142, 328, 80 }, RectanglePlacement::centred);
		g.drawImage(tempoComp.getFocusState() ? imageSceneBgContainerSelected : imageSceneBgContainerDefault, ui::Rectangle<float>{ 676, 142, 328, 80 }, RectanglePlacement::centred);

		g.drawImage(ftsRootNote.getFocusState() ? imageSceneBgContainerSelected : imageSceneBgContainerDefault, ui::Rectangle<float>{ 0, 230, 328, 80 }, RectanglePlacement::centred);
		g.drawImage(ftsScale.getFocusState() ? imageSceneBgContainerSelected : imageSceneBgContainerDefault, ui::Rectangle<float>{ 338, 230, 328, 80 }, RectanglePlacement::centred);
		g.drawImage(xfts.getToggleState() ? (xfts.isMouseOver() || xfts.isFocused) ? imageXposePostHover: imageXposePostDefault: (xfts.isMouseOver() || xfts.isFocused) ? imageXposePreHover: imageXposePreDefault, ui::Rectangle<float>{ 0, 318, 328, 80 }, RectanglePlacement::centred);
		g.drawImage(xposeComp.getFocusState() ? imageSceneBgContainerSelected : imageSceneBgContainerDefault, ui::Rectangle<float>{ 338, 318, 328, 80 }, RectanglePlacement::centred);
		g.drawImage(tapTempo.getClickState() ? imageSongTempoClick : (tapTempo.getFocusState() ? imageSongTempoHover : imageSongTempoDefault), ui::Rectangle<float>{ 676, 222, 328, 176 }, RectanglePlacement::centred);

		updateComponentState(swingComp, _pSong->getGlobalSwingState());
		updateComponentState(tempoComp, _pSong->getGlobalTempoState());
	}

	void AppSceneView::resized()
	{
		sceneBox1.performLayout(ui::Rectangle(10, 54, 1004, 80));
		sceneBox2.performLayout(ui::Rectangle(10, 142, 1004, 80));
		sceneBox3.performLayout(ui::Rectangle(10, 230, 666, 80));
		sceneBox4.performLayout(ui::Rectangle(10, 318, 666, 80));
		tapTempo.setBounds((int)676, 222, (int)328, 176);
	}
	int AppSceneView::isEditing()
	{
		int index = 0;
		swingComp.IsEditing() ? index = 1 : 0;
		gbarComp.IsEditing() ? index = 2 : 0;
		muteHold.IsEditing() ? index = 3 : 0;
		lenComp.IsEditing() ? index = 4 : 0;
		songAdv.IsEditing() ? index = 5 : 0;
		tempoComp.IsEditing() ? index = 6 : 0;
		ftsRootNote.IsEditing() ? index = 7 : 0;
		ftsScale.IsEditing() ? index = 8 : 0;
		xposeComp.IsEditing() ? index = 10 : 0;

		return index;
	}

	bool AppSceneView::pannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool setfocus = true;
		int EditItem = sceneDetailsViewItemID::NO_FOCUS;

		if (keyFocusedItem == sceneDetailsViewItemID::NO_FOCUS)
		{
			keyFocusedItem = sceneDetailsViewItemID::SWINGCOMP;
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
				pannelSendKey(false, param, KeyValue);
				if (_pScene->getOptionHandlerState() != _pScene->SCENE_DETAIL)
					return true;
				switch ((FrontPannelParam)param)
				{
				case FrontPannelParam::paramKey_RMOVELEFT:
					keyFocusedItem = (keyFocusedItem + 1 >= sceneDetailsViewItemID::FOCUS_MAX ? sceneDetailsViewItemID::FOCUS_MAX : keyFocusedItem + 1);
					if (keyFocusedItem == FTSROOTNOTE)
					{
						bool allowsComp, allowsChild;
						ftsRootNote.getInterceptsMouseClicks(allowsComp, allowsChild);
						if (!allowsChild)
							keyFocusedItem++;
					}
					break;
				case FrontPannelParam::paramKey_RMOVERIGHT:
					keyFocusedItem = (keyFocusedItem - 1 <= sceneDetailsViewItemID::NO_FOCUS ? sceneDetailsViewItemID::NO_FOCUS + 1 : keyFocusedItem - 1);
					if (keyFocusedItem == FTSROOTNOTE)
					{
						bool allowsComp, allowsChild;
						ftsRootNote.getInterceptsMouseClicks(allowsComp, allowsChild);
						if (!allowsChild)
							keyFocusedItem--;
					}
					break;
				case FrontPannelParam::paramRot_ROW:
					if ((KeyValue == ROTARY_DIRECTION_RIGHT && (keyFocusedItem == FTSROOTNOTE || keyFocusedItem == FTSSCALE)) || (KeyValue == ROTARY_DIRECTION_LEFT && (keyFocusedItem == XFTS || keyFocusedItem == XPOSECOMP)))
					{
						numItemsInRow = 2;
					}
					else if ((KeyValue == ROTARY_DIRECTION_LEFT && keyFocusedItem == TAP_TEMPO) || (keyFocusedItem == TEMPOCOMP && KeyValue == ROTARY_DIRECTION_RIGHT))
					{
						numItemsInRow = 5;
					}
					else
					{
						numItemsInRow = 3;
					}

					if (KeyValue == ROTARY_DIRECTION_RIGHT)
					{
						pannelSendKey(false, (paramId_t)FrontPannelParam::paramRot_ROW, ROTARY_DIRECTION_RIGHT);
						keyFocusedItem = (keyFocusedItem + numItemsInRow >= sceneDetailsViewItemID::FOCUS_MAX ? ((keyFocusedItem + numItemsInRow) == (sceneDetailsViewItemID::FOCUS_MAX) ? (sceneDetailsViewItemID::FOCUS_MAX) : keyFocusedItem) : keyFocusedItem + numItemsInRow);
						pannelSendKey(true, (paramId_t)FrontPannelParam::paramRot_ROW, ROTARY_DIRECTION_RIGHT);
					}
					else
					{
						pannelSendKey(false, (paramId_t)FrontPannelParam::paramRot_ROW, ROTARY_DIRECTION_LEFT);
						keyFocusedItem = (keyFocusedItem - numItemsInRow <= sceneDetailsViewItemID::NO_FOCUS ? (keyFocusedItem) : keyFocusedItem - numItemsInRow);
						pannelSendKey(true, (paramId_t)FrontPannelParam::paramRot_ROW, ROTARY_DIRECTION_LEFT);
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

	void AppSceneView::pannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		Colour Colour;
		if (isFocuse)
			Colour = Theme::Instance().getColour(systemOrange);
		else
			Colour = Theme::Instance().getColour(systemBlue);


		tapTempo.setFocusState(false);
		switch (detailsViewItems[keyFocusedItem])
		{
		case SWINGCOMP:
			if (swingComp.getAlpha() == 1.0)
				swingComp.FPKeyHandler(isFocuse, param, KeyValue);
			else
				if (!(KeyValue == ROTARY_DIRECTION_LEFT))
					skipItemFromFocus(isFocuse, param, KeyValue);
				else
				{
					keyFocusedItem = LENCOMP;
					pannelSendKey(isFocuse, param, KeyValue);
				}
			break;
		case TEMPOCOMP:
			if (tempoComp.getAlpha() == 1.0)
				tempoComp.FPKeyHandler(isFocuse, param, KeyValue);
			else
				skipItemFromFocus(isFocuse, param, KeyValue);
			break;
		case GBARCOMP:
			gbarComp.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case LENCOMP:
			lenComp.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case SONGADV:
			songAdv.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case MUTEHOLD:
			muteHold.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case FTSROOTNOTE:
			if (ftsRootNote.getAlpha() == 1.0)
				ftsRootNote.FPKeyHandler(isFocuse, param, KeyValue);
			else
				skipItemFromFocus(isFocuse,param, KeyValue);
			break;
		case FTSSCALE:
			ftsScale.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case XPOSECOMP:
			xposeComp.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case TAP_TEMPO:
			tapTempo.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case XFTS:
			xfts.FPKeyHandler(isFocuse, param, 0);
			repaint();
			break;
		}
	}
	void AppSceneView::skipItemFromFocus(bool isFocuse,paramId_t param, uint32_t keyValue)
	{
		if (param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT)
		{
			keyFocusedItem++;
		}
		else if (param == (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT)
		{
			keyFocusedItem--;
		}
		else
		{
			if ((keyValue == ROTARY_DIRECTION_RIGHT && (keyFocusedItem == FTSROOTNOTE || keyFocusedItem == FTSSCALE)) || (keyValue == ROTARY_DIRECTION_LEFT && (keyFocusedItem == XFTS || keyFocusedItem == XPOSECOMP)))
			{
				numItemsInRow = 2;
			}
			else if( keyFocusedItem == TEMPOCOMP && keyValue == ROTARY_DIRECTION_RIGHT)
			{
				numItemsInRow = 5;
			}
			else
			{
				numItemsInRow = 3;
			}

			if (keyValue == ROTARY_DIRECTION_RIGHT)
				keyFocusedItem = (keyFocusedItem + numItemsInRow >= sceneDetailsViewItemID::FOCUS_MAX ? ((keyFocusedItem + numItemsInRow) == (sceneDetailsViewItemID::FOCUS_MAX) ? (sceneDetailsViewItemID::FOCUS_MAX) : keyFocusedItem) : keyFocusedItem + numItemsInRow);
			else
				keyFocusedItem = (keyFocusedItem - numItemsInRow <= sceneDetailsViewItemID::NO_FOCUS ? (keyFocusedItem) : keyFocusedItem - numItemsInRow);
		}
		pannelSendKey(isFocuse, param, keyValue);

	}

	void AppSceneView::mouseUp(const MouseEvent& event)
	{
		auto a = event.eventComponent->getComponentID();
		if (a != "TapTempo")
		{
			// If user click on any other component reset tap tempo data
			tapTempo.resetTapTempoData();
		}
	}

	void AppSceneView::timerCallback()
	{
		setTapTempo(FrountPannel::GetFrountPannelInstance()->getTapTempoValue(), false, false);
		stopTimer();
	}

	void AppSceneView::setTapTempo(float value, bool sendTempoAsPlayModeData, bool timerStart)
	{
		if (timerStart)
			startTimer(TIMER_TIMEOUT_UPDATE_TEMPO_MILLISECOND);

		_pScene->setSceneData(mt::Ignite::sceneDataIndex::SCENE_TEMPO, (float)value, false, sendTempoAsPlayModeData);

		if (!IgniteSceneConfig::getAppSceneConfigInstance()->isAutoSaveEnabled())
			_pScene->updateSceneEditIndication(true);
		IgniteTrack::GetAppTrackInstance()->updateSelectionInfo();
	}
};
