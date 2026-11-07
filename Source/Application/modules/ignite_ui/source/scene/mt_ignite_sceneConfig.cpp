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

using namespace Ignite;

namespace ui
{

	////////////////////////////////////////////////
	//   Class: Ignite SceneConfig
	////////////////////////////////////////////////
	IgniteSceneConfig::IgniteSceneConfig()
	{
		addAndMakeVisible(autoSaveBtn);
		autoSaveBtn.addListener(this);
		autoSaveBtn.setToggleable(true);
		autoSaveBtn.setComponentID("autoSaveComp");
		autoSaveBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		autoSaveBtn.sethoverImages("toggle-autosave-hover.png", "toggle-autosave-active-hover.png", "toggle-autosave-disabled.png");

		addAndMakeVisible(wipeScenesBtn);
		wipeScenesBtn.addListener(this);
		wipeScenesBtn.setToggleable(true);
		wipeScenesBtn.setComponentID("wipeSceneComp");
		wipeScenesBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		wipeScenesBtn.setDisableImage("btn-wipe-scene-disabled.png");

		/*addAndMakeVisible(customFtsBtn);
		customFtsBtn.addListener(this);
		customFtsBtn.setToggleable(true);
		customFtsBtn.setComponentID("customFtsComp");*/

		sceneOptCtl = IgniteControlOptions::GetAppOptInstance();
		addChildComponent(sceneOptCtl);
		sceneOptCtl->setBounds(xStartOptctl, yStartOptctl, widthOptctl, heightOptctlt);
		sceneOptCtl->addOptCtlListener(this);

		addAndMakeVisible(tapConfig);
		tapConfig.setDisplayTitle(true);
		tapConfig.setJustificationType(juce::Justification::centred);
		tapConfig.setTextColour(Theme::Instance().getColour(customOrange));
		tapConfig.setcustombounds(true, ui::Rectangle<int>{144, 0, 50, 50}, ui::Rectangle<int>{90, 35, 150, 50});
		tapConfig.setComponentID("tapConfigComp");

		addAndMakeVisible(insertPosition);
		insertPosition.updateListOptions(mt::Ignite::sceneInsertPosition);
		insertPosition.setSelected(0);
		insertPosition.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		insertPosition.setValueColour(Theme::Instance().getColour(customOrange));
		insertPosition.setComponentID("insertPositionComp");
		insertPosition.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,370 });

		addAndMakeVisible(soloModeBtn);
		soloModeBtn.addListener(this);
		soloModeBtn.setToggleable(true);
		soloModeBtn.setComponentID("soloModeComp");
		soloModeBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		soloModeBtn.sethoverImages("toggle-solomode-hover.png", "toggle-solomode-active-hover.png", "toggle-solomode-disabled.png");

		addAndMakeVisible(fillModeBtn);
		fillModeBtn.addListener(this);
		fillModeBtn.setToggleable(true);
		fillModeBtn.setComponentID("fillConfigComp");
		fillModeBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		fillModeBtn.sethoverImages("toggle-fillmode-hover.png", "toggle-fillmode-active-hover.png", "toggle-solomode-disabled.png");

		/*fillConfigLable.makeVisible(this);
		fillConfigLable.setDisplayTitleAndBorder(false);
		fillConfigLable.setInterceptsMouseClicks(false, false);
		fillConfigLable.setVisible(false);

		addAndMakeVisible(fillMode);
		fillMode.updateListOptions(fillModeOptions);
		fillMode.setSelected(0);
		fillMode.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		fillMode.setValueColour(Theme::Instance().getColour(customOrange));
		fillMode.setComponentID("fillModeComp");

		addAndMakeVisible(fillRelease);
		fillRelease.updateListOptions(releaseOptions);
		fillRelease.setSelected(0);
		fillRelease.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		fillRelease.setValueColour(Theme::Instance().getColour(customOrange));
		fillMode.setAlpha((float)0.2);
		fillMode.setInterceptsMouseClicks(false, false);
		fillRelease.setAlpha((float)0.2);
		fillRelease.setInterceptsMouseClicks(false, false);
		fillRelease.setComponentID("fillReleaseComp");

		const juce::Rectangle<int> fillReleaseBounds{ (0),(0),widthfillRelease,heightfillRelease };
		fillRelease.setDailogViewType(mt::Ignite::DailogViewType::CustomView, false, fillReleaseBounds);
		fillRelease.setTextColour(Theme::Instance().getColour(customOrange));
		fillMode.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,360 });
		fillRelease.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,340 });*/

		_pCustomScaleComp = IgniteCustomScale::getAppCustomScaleInstance();
		addChildComponent(_pCustomScaleComp);
		_pCustomScaleComp->setBounds(0, 0, layout::middle.getWidth(), layout::middle.getHeight() + 15);
		_pCustomScaleComp->setVisible(false);

		_pPopUpPtr = CommonPopUp::getCommonPopupInstance();

		sceneMenuBox1.items.add(FlexItem(autoSaveBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		sceneMenuBox1.items.add(FlexItem(wipeScenesBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		sceneMenuBox1.items.add(FlexItem(tapConfig).withMargin({ 0,8,8,0 }).withFlex(1));

		sceneMenuBox2.items.add(FlexItem(fillModeBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		sceneMenuBox2.items.add(FlexItem(soloModeBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		sceneMenuBox2.items.add(FlexItem(insertPosition).withMargin({ 0,8,8,0 }).withFlex(1));
		//sceneMenuBox2.items.add(FlexItem(fillMode).withMargin({ 0,8,8,0 }).withFlex(1));
		//sceneMenuBox2.items.add(FlexItem(fillRelease).withMargin({ 0,8,8,0 }).withFlex(1));

		//sceneMenuBox3.items.add(FlexItem(soloModeBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		////sceneMenuBox3.items.add(FlexItem(customFtsBtn).withMargin({ 0,8,8,0 }).withFlex(1));
		//sceneMenuBox3.items.add(FlexItem(insertPosition).withMargin({ 0,8,8,0 }).withFlex(1));
		getAssets();
		insertPosition.onSelectionChanged = [this](int value, const juce::String&)
		{
			DBG("insertPosition.onSelectionChanged::" + String(__LINE__) + "::value: " + String(value));
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;
			if (!isInternal)
			{
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingSceneCnfg, (paramId_t)SettingsSceneCnfgParam::settingInsertPosition, value);
				sceneOptCtl->enableKey(IgniteControlOptions::SAVE, true);
				sceneOptCtl->enableKey(IgniteControlOptions::UNDO, true);
				sceneConfigDataUpdated = true;
			}
		};

		tapConfig.onValueChanged = [this](int value)
		{
			DBG("tapConfig.onValueChanged::" + String(__LINE__) + "::value: " + String(value));
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;
			if (!isInternal)
			{
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingSceneCnfg, (paramId_t)SettingsSceneCnfgParam::SettingSceneTapTempoParam, value);
				sceneOptCtl->enableKey(IgniteControlOptions::SAVE, true);
				sceneOptCtl->enableKey(IgniteControlOptions::UNDO, true);
				sceneConfigDataUpdated = true;
			}
			
		};

		/*fillMode.onSelectionChanged = [this](int value, const juce::String&)
			{
				DBG("fillMode.onSelectionChanged::" + String(__LINE__) + "::value: " + String(value));
				Component::BailOutChecker checker(this);

				if (checker.shouldBailOut())
					return;
				if (!isInternal)
				{
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingSceneCnfg, (paramId_t)SettingsSceneCnfgParam::SettingSceneFillActiveCnfgParam, value);
					sceneOptCtl->enableKey(IgniteControlOptions::SAVE, true);
					sceneOptCtl->enableKey(IgniteControlOptions::UNDO, true);
					sceneConfigDataUpdated = true;
				}
			};

		fillRelease.onSelectionChanged = [this](int value, const juce::String&)
		{
			DBG("fillRelease.onSelectionChanged ::" + String(__LINE__) + "::value: " + String(value));
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;
			if (!isInternal)
			{
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingSceneCnfg, (paramId_t)SettingsSceneCnfgParam::SettingSceneFillKeyCnfgParam, value);
				sceneOptCtl->enableKey(IgniteControlOptions::SAVE, true);
				sceneOptCtl->enableKey(IgniteControlOptions::UNDO, true);
				sceneConfigDataUpdated = true;
			}
		};

		fillMode.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		fillRelease.onFocusChanged = [this](bool a)
		{
			repaint();
		};*/

		tapConfig.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		insertPosition.onFocusChanged = [this](bool a)
		{
			repaint();
		};
	}

	IgniteSceneConfig::~IgniteSceneConfig()
	{
	}

	void IgniteSceneConfig::getAssets()
	{
		imageDefault = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("bg-modal-328x80-container-default.png"));
		imageDefaultHover = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("bg-modal-328x80-container-default-hover.png"));
		imageDisabled = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("bg-modal-328x80-container-disabled.png"));

	}

	void IgniteSceneConfig::paint(juce::Graphics& g)
	{
		if (!ftsWindowEnabled)
		{
			if (sceneConfigDataUpdated && !isAutosave)
				MenuMode::GetMenuModeInstance()->setHeader("Scene Configuration*");
			else
				MenuMode::GetMenuModeInstance()->setHeader("Scene Configuration");
		}
		if (!IgniteSong::getAppSongInstance()->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
			wipeScenesBtn.setEnabled(false);
		else
			wipeScenesBtn.setEnabled(true);

		Image Draw;

		Draw = tapConfig.isEnabled() ? (tapConfig.getFocusState() ? imageDefaultHover : imageDefault) : imageDisabled;
		g.drawImage(Draw, ui::Rectangle<float>{ 686, 70, 328, 80 });

		/*Draw = fillMode.isEnabled() ? (fillMode.getFocusState() ? imageDefaultHover : imageDefault) : imageDisabled;
		g.drawImage(Draw, ui::Rectangle<float>{ 348, 160, 328, 80 });

		Draw = fillRelease.isEnabled() ? (fillRelease.getFocusState() ? imageDefaultHover : imageDefault) : imageDisabled;
		g.drawImage(Draw, ui::Rectangle<float>{ 686, 160, 328, 80 });*/

		Draw = insertPosition.getFocusState() ? imageDefaultHover : imageDefault;
		g.drawImage(Draw, ui::Rectangle<float>{ 686, 160, 328, 80 });
	//	g.drawImage(Draw, ui::Rectangle<float>{ 348, 250, 328, 80 });

	}

	void IgniteSceneConfig::resized()
	{
		sceneMenuBox1.performLayout(ui::Rectangle(xStartSongMenuBox1, yStartSongMenuBox1, widthSongMenuBox1, heightSongMenuBox1));
		sceneMenuBox2.performLayout(ui::Rectangle(xStartSongMenuBox1, yStartSongMenuBox2, widthSongMenuBox1, heightSongMenuBox1));
		//sceneMenuBox3.performLayout(ui::Rectangle(xStartSongMenuBox1, yStartSongMenuBox2 + 90, 675, heightSongMenuBox1));
	}

	void IgniteSceneConfig::updateData(bool isinternal)
	{
		isInternal = isinternal;
		std::vector<IgniteParamList> sceneCnfgParams;
		IgniteParamList params;

		params.param = (paramId_t)SettingsSceneCnfgParam::SettingSceneAutoSaveParam;
		sceneCnfgParams.push_back(params);

		params.param = (paramId_t)SettingsSceneCnfgParam::SettingSceneTapTempoParam;
		sceneCnfgParams.push_back(params);

		params.param = (paramId_t)SettingsSceneCnfgParam::settingInsertPosition;
		sceneCnfgParams.push_back(params);

		params.param = (paramId_t)SettingsSceneCnfgParam::SettingSceneSoloModeParam;
		sceneCnfgParams.push_back(params);

		params.param = (paramId_t)SettingsSceneCnfgParam::SettingSceneFillModeParam;
		sceneCnfgParams.push_back(params);

		params.param = (paramId_t)SettingsSceneCnfgParam::SettingSceneFillActiveCnfgParam;
		sceneCnfgParams.push_back(params);

		params.param = (paramId_t)SettingsSceneCnfgParam::SettingSceneFillKeyCnfgParam;
		sceneCnfgParams.push_back(params);

		sceneCnfgParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingSceneCnfg, sceneCnfgParams);
		autoSaveScene = (bool)sceneCnfgParams[0].MsgValue.get<int8_t>();
		autoSaveBtn.setToggleState(autoSaveScene, dontSendNotification);
		autoSaveBtn.getToggleState() ? autoSaveBtn.setButtonText("Auto Save:on") : autoSaveBtn.setButtonText("Auto Save:off");
		tapConfig.setValue(sceneCnfgParams[1].MsgValue.get<int8_t>());
		insertPosition.setSelected((int)sceneCnfgParams[2].MsgValue.get<int8_t>());
		soloModeBtn.setToggleState((bool)sceneCnfgParams[3].MsgValue.get<int8_t>(), dontSendNotification);
		fillModeBtn.setToggleState((bool)sceneCnfgParams[4].MsgValue.get<int8_t>(), dontSendNotification);
		/*fillMode.setSelected(sceneCnfgParams[5].MsgValue.get<int8_t>());
		fillRelease.setSelected(sceneCnfgParams[6].MsgValue.get<int8_t>());*/

		soloModeBtn.getToggleState() ? soloModeBtn.setButtonText("Solo Mode:on") : soloModeBtn.setButtonText("Solo Mode:off");
		fillModeBtn.getToggleState() ? fillModeBtn.setButtonText("Fill Mode:on") : fillModeBtn.setButtonText("Fill Mode:off");

		/*if (fillModeBtn.getToggleState())
		{
			fillMode.setAlpha((float)1.0);
			fillMode.setInterceptsMouseClicks(true, true);
			fillRelease.setAlpha((float)1.0);
			fillRelease.setInterceptsMouseClicks(true, true);
		}
		else
		{
			fillMode.setAlpha((float)0.2);
			fillMode.setInterceptsMouseClicks(false, false);
			fillRelease.setAlpha((float)0.2);
			fillRelease.setInterceptsMouseClicks(false, false);
		}*/

		if (isInternal)
			isInternal = false;
	}

	void IgniteSceneConfig::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		auto scenePtr = IgniteScene::getAppSceneInstance();
		auto _pSongPtr = IgniteSong::getAppSongInstance();

		if (buttonThatWasClicked == &autoSaveBtn)
		{
			autoSaveScene = autoSaveBtn.getToggleState();
			if (_pSongPtr->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
			{
				if (autoSaveBtn.getToggleState())
				{
					if (!isInternal)
						_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleScene, (paramId_t)SceneParam::paramSaveSceneCmd, IgniteScene::getAppSceneInstance()->getSelected());
					scenePtr->updateLables();
				}
			}
			if (!isInternal)
			{
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingSceneCnfg, (paramId_t)SettingsSceneCnfgParam::SettingSceneAutoSaveParam, autoSaveScene);
				sceneOptCtl->enableKey(IgniteControlOptions::SAVE, true);
				sceneOptCtl->enableKey(IgniteControlOptions::UNDO, true);
				sceneConfigDataUpdated = true;
			}
			autoSaveBtn.getToggleState() ? autoSaveBtn.setButtonText("Auto Save:on") : autoSaveBtn.setButtonText("Auto Save:off");
		}
		else if (buttonThatWasClicked == &wipeScenesBtn)
		{
			if (_pSongPtr->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
			{
				scenePtr->deleteAllScenes();
				scenePtr->refreshSceneUI();
				wipeScenesBtn.setToggleState(false, dontSendNotification);
			}
		}
		/*else if (buttonThatWasClicked == &customFtsBtn)
		{
			ftsWindowEnabled = true;
			_pCustomScaleComp->setVisible(true);
			AppOptions::GetOptionsInstance()->taboptionChanges(mt::Ignite::tabs::MENU, (int)AppMenu::MENU_WINDOWS::UDS_WINDOWS);
		}*/
		else if (buttonThatWasClicked == &soloModeBtn)
		{
			if (!isInternal)
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingSceneCnfg, (paramId_t)SettingsSceneCnfgParam::SettingSceneSoloModeParam, soloModeBtn.getToggleState());
			if (_pSongPtr->isSongCreated() && _pSongPtr->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
				IgniteTrack::GetAppTrackInstance()->updateSelectionInfo();

			soloModeBtn.setButtonText(soloModeBtn.getToggleState() ? "Solo Mode:on" : "Solo Mode:off");
			_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_SOLO_SKIP, (soloModeBtn.getToggleState() ? fpLEDPattern::EN_LED_PATT_ON : fpLEDPattern::EN_LED_PATT_OFF));
		}
		else if (buttonThatWasClicked == &fillModeBtn)
		{
			if (_pSongPtr->isSongCreated())
				_pSongPtr->setSongData(mt::Ignite::songsDataIndex::FILLMODE, fillModeBtn.getToggleState(), false);

			if (fillModeBtn.getToggleState())
			{
				fillModeBtn.setButtonText("Fill Mode:on");
				/*fillMode.setAlpha((float)1.0);
				fillMode.setInterceptsMouseClicks(true, true);
				fillRelease.setAlpha((float)1.0);
				fillRelease.setInterceptsMouseClicks(true, true);*/
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_FILL_X, fpLEDPattern::EN_LED_PATT_ON);
			}
			else
			{
				fillModeBtn.setButtonText("Fill Mode:off");
				/*fillMode.setAlpha((float)0.2);
				fillMode.setInterceptsMouseClicks(false, false);
				fillRelease.setAlpha((float)0.2);
				fillRelease.setInterceptsMouseClicks(false, false);*/
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_FILL_X, fpLEDPattern::EN_LED_PATT_OFF);
			}
			if (!isInternal)
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingSceneCnfg, (paramId_t)SettingsSceneCnfgParam::SettingSceneFillModeParam, fillModeBtn.getToggleState());

			if (_pSongPtr->isSongCreated() && _pSongPtr->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
				IgniteTrack::GetAppTrackInstance()->updateSelectionInfo();
		}
	}

	void IgniteSceneConfig::onOptCtlButtonClicked(IgniteControlOptions::eKey option)
	{
		if (option == IgniteControlOptions::SAVEALLON)
		{
			sceneConfigDataUpdated = false;
		}
		else if (option == IgniteControlOptions::AUTOSAVEON)
		{
			isAutosave = true;
		}
		else if (option == IgniteControlOptions::AUTOSAVEOFF)
		{
			isAutosave = false;
		}
		if (this->isVisible() && !_pCustomScaleComp->isVisible())
		{
			if (option == IgniteControlOptions::SAVE)
			{
				if (_pPopUpPtr->isDialogOpen.get() != true)
				{
					_pPopUpPtr->close();
					_pPopUpPtr->setPopUpPropories("Save ", 604, 290);
					_pPopUpPtr->setbtnsize(265, 44);
					_pPopUpPtr->setInfoText(String(" Save Scene Configuration edits ? "));
					_pPopUpPtr->addImageButton("no", "btn-secondary-no-267x44-default.png", "btn-secondary-no-267x44-default-hover.png", 2);
					_pPopUpPtr->addImageButton("yes", "btn-yes-267x44-default.png", "btn-yes-267x44-default-hover.png", 1);
					_pPopUpPtr->popupType = POPUP_WITHOKCANCEL;
					_pPopUpPtr->isCloseButtonVisible(false);
					_pPopUpPtr->show();
					_pPopUpPtr->onSelectionChanged = [this](int r)
					{
						if (r == 1)
						{
							_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingSceneCnfg, (paramId_t)SettingsSceneCnfgParam::SettingSceneCnfgSave, 0);
							sceneOptCtl->enableKey(IgniteControlOptions::SAVE, false);
							sceneOptCtl->enableKey(IgniteControlOptions::UNDO, false);
							sceneConfigDataUpdated = false;
						}
						if (auto dw = getCurrentlyModalComponent())
							dw->exitModalState(0);
					};
				}
			}
			else if (option == IgniteControlOptions::SCENELIST)
			{
				IgniteScene::getAppSceneInstance()->changeSceneOptionsVisibility(false);
				AppMainmode::getMainModeInstance()->triggerTabChange(mt::Ignite::tabs::SCENE);
			}
			else if (option == IgniteControlOptions::UNDO)
			{
				if (sceneConfigDataUpdated)
				{
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingSceneCnfg, (paramId_t)SettingsSceneCnfgParam::paramUndoCmd, 0);

					std::vector<IgniteParamList> sceneCfgParamList;
					IgniteParamList params;

					params.param = (paramId_t)SettingsSceneCnfgParam::paramUndoListCmd;
					sceneCfgParamList.push_back(params);
					sceneCfgParamList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingSceneCnfg, sceneCfgParamList);
					if (sceneCfgParamList.size() == 1)
					{
						sceneConfigDataUpdated = false;
						sceneOptCtl->enableKey(IgniteControlOptions::SAVE, false);
						sceneOptCtl->enableKey(IgniteControlOptions::UNDO, false);
					}
					updateData(true);
				}
			}
		}
	}

	int IgniteSceneConfig::isEditing()
	{
		int index = 0;

		if (keyFocusedItem == WIPE_SCENES)
		{
			auto scenePtr = IgniteScene::getAppSceneInstance();

			if (scenePtr->_pPopUpPtr != nullptr && scenePtr->_pPopUpPtr->IsEditing())
			{
				return WIPE_SCENES;
			}
		}

		tapConfig.IsEditing() ? index = 3 : 0;
		/*fillMode.IsEditing() ? index = 5 : 0;
		fillRelease.IsEditing() ? index = 6 : 0;*/
		insertPosition.IsEditing() ? index = 6 : 0;
		return index;
	}

	bool IgniteSceneConfig::pannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		if (handleCustomScaleComp(param, KeyValue)) return true;
		if (handlePopUp(param, KeyValue)) return true;

		switch ((FrontPannelParam)param)
		{
		case FrontPannelParam::paramKey_SOLO_SKIP:
			return handleSoloSkip(KeyValue);
		case FrontPannelParam::paramKey_FILL_X:
			return handleFillX(KeyValue);
		case FrontPannelParam::paramKey_PAGESHIFT:
			return handlePageShift(param, KeyValue);
		default:
			return handleDefault(param, KeyValue);
		}
	}

	bool IgniteSceneConfig::handleCustomScaleComp(paramId_t param, uint32_t KeyValue)
	{
		if (_pCustomScaleComp->isVisible() && _pCustomScaleComp->_pPopupPtr != nullptr && _pCustomScaleComp->_pPopupPtr->IsEditing())
		{
			return _pCustomScaleComp->pannelKeyHandler(param, KeyValue);
		}
		return false;
	}

	bool IgniteSceneConfig::handlePopUp(paramId_t param, uint32_t KeyValue)
	{
		if (_pPopUpPtr != nullptr && _pPopUpPtr->IsEditing())
		{
			return _pPopUpPtr->FPKeyHandler(true, param, KeyValue);
		}
		return false;
	}

	bool IgniteSceneConfig::handleSoloSkip(uint32_t KeyValue)
	{
		_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_SOLO_SKIP, (!soloModeBtn.getToggleState() ? fpLEDPattern::EN_LED_PATT_ON : fpLEDPattern::EN_LED_PATT_OFF));
		postCommandMessage(1);
		return soloModeBtn.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, KeyValue);
	}

	bool IgniteSceneConfig::handleFillX(uint32_t KeyValue)
	{
		_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_FILL_X, (!fillModeBtn.getToggleState() ? fpLEDPattern::EN_LED_PATT_ON : fpLEDPattern::EN_LED_PATT_OFF));
		postCommandMessage(2);
		return fillModeBtn.FPKeyHandler(true, (paramId_t)FrontPannelParam::paramKey_RSELECT, KeyValue);
	}

	bool IgniteSceneConfig::handlePageShift(paramId_t param, uint32_t KeyValue)
	{
		pannelSendKey(false, param, KeyValue);
		if (optionHandlerFocus == SCENECONFIG_DETAIL)
		{
			if (_pCustomScaleComp->isVisible())
				return _pCustomScaleComp->pannelKeyHandler(param, KeyValue);
			else
				optionHandlerFocus = SCENECONFIG_OPTION;
		}
		else
		{
			optionHandlerFocus = SCENECONFIG_DETAIL;
		}
		pannelSendKey(true, param, KeyValue);
		return true;
	}

	bool IgniteSceneConfig::handleDefault(paramId_t param, uint32_t KeyValue)
	{
		if (optionHandlerFocus == SCENECONFIG_DETAIL)
		{
			return handleDetailFocus(param, KeyValue);
		}
		else
		{
			return handleOptionFocus(param, KeyValue);
		}
	}

	bool IgniteSceneConfig::handleDetailFocus(paramId_t param, uint32_t KeyValue)
	{
		if (_pCustomScaleComp->isVisible() && _pCustomScaleComp->pannelKeyHandler(param, KeyValue))
		{
			return true;
		}

		bool setfocus = true;
		int EditItem = sceneMenuViewItemID::NO_FOCUS;

		if (keyFocusedItem == sceneMenuViewItemID::NO_FOCUS)
		{
			keyFocusedItem = sceneMenuViewItemID::AUTO_SAVE;
			if ((FrontPannelParam)param == FrontPannelParam::paramKey_RETURN_NAV)
			{
				AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::MENU_WINDOW);
				return true;
			}
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
			}
			else
			{
				pannelSendKey(false, param, KeyValue);
				switch ((FrontPannelParam)param)
				{
				case FrontPannelParam::paramKey_RMOVELEFT:
					keyFocusedItem = std::min(keyFocusedItem + 1, (int)sceneMenuViewItemID::FOCUS_MAX);
					break;
				case FrontPannelParam::paramKey_RMOVERIGHT:
					keyFocusedItem = std::max(keyFocusedItem - 1, (int)sceneMenuViewItemID::NO_FOCUS + 1);
					break;
				case FrontPannelParam::paramKey_RETURN_NAV:
					AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::MENU_WINDOW);
					break;
				case FrontPannelParam::paramRot_ROW:
					handleRotaryKey(param, KeyValue);
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

	bool IgniteSceneConfig::handleOptionFocus(paramId_t param, uint32_t KeyValue)
	{
		pannelSendKey(false, param, KeyValue);
		switch ((FrontPannelParam)param)
		{
		case FrontPannelParam::paramKey_RMOVELEFT:
			optFocusedItem = std::min(optFocusedItem + 1, (int)sceneOptionsViewItemID::OP_FOCUS_MAX);
			break;
		case FrontPannelParam::paramKey_RMOVERIGHT:
			optFocusedItem = std::max(optFocusedItem - 1, (int)sceneOptionsViewItemID::OP_NO_FOCUS + 1);
			break;
		case FrontPannelParam::paramKey_RETURN_NAV:
			AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::MENU_WINDOW);
			break;
		}
		pannelSendKey(true, param, KeyValue);
		return true;
	}

	void IgniteSceneConfig::handleRotaryKey(paramId_t param, uint32_t KeyValue)
	{
		if (KeyValue == ROTARY_DIRECTION_RIGHT)
		{
			pannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
			keyFocusedItem = std::min(keyFocusedItem + SONG_NO_COM_ROW, (int)sceneMenuViewItemID::FOCUS_MAX);
			pannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
		}
		else
		{
			pannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVELEFT, 0x48);
			keyFocusedItem = std::max(keyFocusedItem - SONG_NO_COM_ROW, (int)sceneMenuViewItemID::NO_FOCUS);
			pannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RMOVELEFT, 0x48);
		}
		repaint();
	}

	void IgniteSceneConfig::pannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		auto scenePtr = IgniteScene::getAppSceneInstance();

		if (optionHandlerFocus == SCENECONFIG_DETAIL)
		{
			handleDetailFocus(isFocuse, param, KeyValue, scenePtr);
		}
		else
		{
			handleOptionFocus(isFocuse, param, KeyValue);
		}
	}

	void IgniteSceneConfig::handleDetailFocus(bool isFocuse, paramId_t param, uint32_t KeyValue, IgniteScene* scenePtr)
	{
		switch (sceneMenuView[keyFocusedItem])
		{
		case AUTO_SAVE:
			autoSaveBtn.FPKeyHandler(isFocuse, param, 0);
			break;
		case WIPE_SCENES:
			handleWipeScenes(isFocuse, param, KeyValue, scenePtr);
			break;
		case TAP_TEMPO:
			tapConfig.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case INSERT_POSITION:
			insertPosition.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case SOLO_MODE:
			handleSoloMode(isFocuse, param, 0);
			break;
		case FILL_CONFIG:
			handleFillConfig(isFocuse, param, 0);
			break;
		default:
			break;
		}
		repaint();
	}

	void IgniteSceneConfig::handleWipeScenes(bool isFocuse, paramId_t param, uint32_t KeyValue, IgniteScene* scenePtr)
	{
		if (wipeScenesBtn.isEnabled())
		{
			if (scenePtr->_pPopUpPtr != nullptr && scenePtr->_pPopUpPtr->IsEditing())
			{
				scenePtr->_pPopUpPtr->FPKeyHandler(isFocuse, param, KeyValue);
			}
			else
			{
				wipeScenesBtn.FPKeyHandler(isFocuse, param, KeyValue);
			}
		}
		else
		{
			adjustFocus(param);
			pannelSendKey(isFocuse, param, KeyValue);
		}
	}

	void IgniteSceneConfig::handleSoloMode(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		soloModeBtn.FPKeyHandler(isFocuse, param, KeyValue);
		if ((FrontPannelParam)param == FrontPannelParam::paramKey_RSELECT && isFocuse)
		{
			buttonClicked(&soloModeBtn);
		}
	}

	void IgniteSceneConfig::handleFillConfig(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		fillModeBtn.FPKeyHandler(isFocuse, param, KeyValue);
		if ((FrontPannelParam)param == FrontPannelParam::paramKey_RSELECT && isFocuse)
		{
			buttonClicked(&fillModeBtn);
		}
	}

	void IgniteSceneConfig::adjustFocus(paramId_t param)
	{
		if ((FrontPannelParam)param == FrontPannelParam::paramKey_RMOVELEFT)
		{
			keyFocusedItem++;
		}
		else
		{
			keyFocusedItem--;
		}
	}

	void IgniteSceneConfig::handleOptionFocus(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		bool state = false;
		switch (optionsView[optFocusedItem])
		{
		case OPT_UNDO:
			state = sceneOptCtl->PannelKeyHandler(IgniteControlOptions::eKey::UNDO, isFocuse, param, KeyValue);
			break;
		case OPT_SCENELIST:
			state = sceneOptCtl->PannelKeyHandler(IgniteControlOptions::eKey::SCENELIST, isFocuse, param, KeyValue);
			break;
		}

		if (!state)
		{
			optFocusedItem++;
			if (optFocusedItem > OP_FOCUS_MAX)
			{
				optFocusedItem = OPT_UNDO;
			}
			pannelSendKey(isFocuse, param, KeyValue);
		}
	}
	void IgniteSceneConfig::handleCommandMessage(int cmdId)
	{
		_pInfoWindow = CommonInfoWindow::GetInfoWindowInstance();
		if (cmdId == 1 || cmdId == 2)
		{
			if (cmdId == 1)
			{
				buttonClicked(&soloModeBtn);
				(!soloModeBtn.getToggleState()) ? _pInfoWindow->setTextandShow("Solo Mode: ON") : _pInfoWindow->setTextandShow("Solo Mode: OFF");
			}
			else if (cmdId == 2)
			{
				buttonClicked(&fillModeBtn);
				(!fillModeBtn.getToggleState()) ? _pInfoWindow->setTextandShow("Fill Mode : ON") : _pInfoWindow->setTextandShow("Fill Mode: OFF");
			}
		}
	}

	void IgniteSceneConfig::mouseUp(const MouseEvent& event)
	{
		auto a = event.eventComponent->getComponentID();
		int NewFocusedItem = sceneMenuViewItemID::NO_FOCUS;

		if (a == "autoSaveComp")					NewFocusedItem = sceneMenuViewItemID::AUTO_SAVE;
		else if (a == "wipeComp")				NewFocusedItem = sceneMenuViewItemID::WIPE_SCENES;
		//else if (a == "customFtsComp")				NewFocusedItem = sceneMenuViewItemID::UDS_CONFIG;
		else if (a == "tapConfigComp")			NewFocusedItem = sceneMenuViewItemID::TAP_TEMPO;

		if (NewFocusedItem != sceneMenuViewItemID::NO_FOCUS && NewFocusedItem != keyFocusedItem)
		{
			pannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_MouseClick, 0);
			keyFocusedItem = NewFocusedItem;
			pannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_MouseClick, 0);
		}
	}
};
