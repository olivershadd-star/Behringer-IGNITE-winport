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
	IgniteCustomScaleOpt::IgniteCustomScaleOpt(IgniteCustomScale* iPtr)
	{
		scalePtr = iPtr;

		auto onFocusChangedCb = [this](bool a)
		{
			repaint();
		};

		udsApplyBtn.makeVisibleAndAddListner(this);
		udsApplyBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());

		for (auto i = 1; i <= 11; i++)
		{
			ui::CommonListBox* notePtr = new ui::CommonListBox("Note" + String(i), 4);
			notePtr->updateListOptions(scaleNoteValueList);
			notePtr->setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
			addAndMakeVisible(notePtr);
			listofListBox.add(notePtr);
			notePtr->setValueColour(Theme::Instance().getColour(customOrange));
			notePtr->onFocusChanged = onFocusChangedCb;
			notePtr->updateListOptions(scaleNoteValueList);
		}

		InstrBox_colume1.items.add(FlexItem(*listofListBox[0]).withMargin({ 0,8,0,0 }).withFlex(1));
		InstrBox_colume1.items.add(FlexItem(*listofListBox[1]).withMargin({ 0,8,0,0 }).withFlex(1));
		InstrBox_colume1.items.add(FlexItem(*listofListBox[2]).withMargin({ 0,0,0,0 }).withFlex(1));

		InstrBox_colume2.items.add(FlexItem(*listofListBox[3]).withMargin({ 0,8,0,0 }).withFlex(1));
		InstrBox_colume2.items.add(FlexItem(*listofListBox[4]).withMargin({ 0,8,0,0 }).withFlex(1));
		InstrBox_colume2.items.add(FlexItem(*listofListBox[5]).withMargin({ 0,0,0,0 }).withFlex(1));

		InstrBox_colume3.items.add(FlexItem(*listofListBox[6]).withMargin({ 0,8,0,0 }).withFlex(1));
		InstrBox_colume3.items.add(FlexItem(*listofListBox[7]).withMargin({ 0,8,0,0 }).withFlex(1));
		InstrBox_colume3.items.add(FlexItem(*listofListBox[8]).withMargin({ 0,0,0,0 }).withFlex(1));

		InstrBox_colume4.items.add(FlexItem(*listofListBox[9]).withMargin({ 0,8,0,0 }).withFlex(1));
		InstrBox_colume4.items.add(FlexItem(*listofListBox[10]).withMargin({ 0,8,0,0 }).withFlex(1));


		listofListBox[0]->setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,360 });
		listofListBox[1]->setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,360 });
		listofListBox[2]->setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,360 });
		listofListBox[3]->setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,360 });
		listofListBox[4]->setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,360 });
		listofListBox[5]->setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,360 });

		listofListBox[6]->setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,360 });
		listofListBox[7]->setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,360 });
		listofListBox[8]->setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,360 });

		listofListBox[9]->setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,360 });
		listofListBox[10]->setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,360 });

		ptr = CommonPopUp::getCommonPopupInstance();

		for (int i = 0; i < listofListBox.size(); i++)
		{
			listofListBox[i]->setcustombounds(true, ui::Rectangle<int>{90, 4, 85, 60}, ui::Rectangle<int>{83, 48, 90, 20});
		}

		listofListBox[0]->onSelectionChanged = [this](int value, const juce::String& name)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			updateListBoxOptions(value, name);
			scalePtr->setCustomScaleData(mt::Ignite::customScaleDataIndex::FTS1_VALUE, (int8)value - 1, false);
		};

		listofListBox[1]->onSelectionChanged = [this](int value, const juce::String& name)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			updateListBoxOptions(value, name);
			scalePtr->setCustomScaleData(mt::Ignite::customScaleDataIndex::FTS2_VALUE, (int8)value - 1, false);
		};

		listofListBox[2]->onSelectionChanged = [this](int value, const juce::String& name)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			updateListBoxOptions(value, name);
			scalePtr->setCustomScaleData(mt::Ignite::customScaleDataIndex::FTS3_VALUE, (int8)value - 1, false);
		};

		listofListBox[3]->onSelectionChanged = [this](int value, const juce::String& name)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			updateListBoxOptions(value, name);
			scalePtr->setCustomScaleData(mt::Ignite::customScaleDataIndex::FTS4_VALUE, (int8)value - 1, false);
		};

		listofListBox[4]->onSelectionChanged = [this](int value, const juce::String& name)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			updateListBoxOptions(value, name);
			scalePtr->setCustomScaleData(mt::Ignite::customScaleDataIndex::FTS5_VALUE, (int8)value - 1, false);
		};

		listofListBox[5]->onSelectionChanged = [this](int value, const juce::String& name)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			updateListBoxOptions(value, name);
			scalePtr->setCustomScaleData(mt::Ignite::customScaleDataIndex::FTS6_VALUE, (int8)value - 1, false);
		};

		listofListBox[6]->onSelectionChanged = [this](int value, const juce::String& name)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			updateListBoxOptions(value, name);
			scalePtr->setCustomScaleData(mt::Ignite::customScaleDataIndex::FTS7_VALUE, (int8)value - 1, false);
		};

		listofListBox[7]->onSelectionChanged = [this](int value, const juce::String& name)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			updateListBoxOptions(value, name);
			scalePtr->setCustomScaleData(mt::Ignite::customScaleDataIndex::FTS8_VALUE, (int8)value - 1, false);
		};

		listofListBox[8]->onSelectionChanged = [this](int value, const juce::String& name)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			updateListBoxOptions(value, name);
			scalePtr->setCustomScaleData(mt::Ignite::customScaleDataIndex::FTS9_VALUE, (int8)value - 1, false);
		};

		listofListBox[9]->onSelectionChanged = [this](int value, const juce::String& name)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			updateListBoxOptions(value, name);
			scalePtr->setCustomScaleData(mt::Ignite::customScaleDataIndex::FTS10_VALUE, (int8)value - 1, false);
		};

		listofListBox[10]->onSelectionChanged = [this](int value, const juce::String& name)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			updateListBoxOptions(value, name);
			scalePtr->setCustomScaleData(mt::Ignite::customScaleDataIndex::FTS11_VALUE, (int8)value - 1, false);
		};
	}

	IgniteCustomScaleOpt::~IgniteCustomScaleOpt()
	{
	}

	void IgniteCustomScaleOpt::updateNoteList()
	{
		for (auto i = 0; i < 11; i++)
		{
			listofListBox[i]->updateListOptions(scaleNoteValueList);
		}
	}

	void IgniteCustomScaleOpt::updateListBoxOptions(int value, const juce::String& sValue)
	{
		if (std::find(scaleNoteValueList.begin(), scaleNoteValueList.end(), sValue) != scaleNoteValueList.end())
		{
			scalePtr->setCustomScaleDataUpdateStatus(true);

			if (!scalePtr->getAutoSaveStatus())
			{
				scalePtr->updateScaleEditIndication();
				scalePtr->enableControlButton(IgniteControlOptions::SAVE, true);
				scalePtr->enableControlButton(IgniteControlOptions::UNDO, true);
			}
		}
	}

	void IgniteCustomScaleOpt::selectNoteValue(int index)
	{
		if (firstIndex)
		{
			scaleNoteValueList.erase(scaleNoteValueList.begin() + index);
			std::rotate(scaleNoteValueList.begin(), scaleNoteValueList.begin() + index, scaleNoteValueList.end());
			firstIndex = false;
		}
		else
		{
			if (0 == index)
				scaleNoteValueList.erase(scaleNoteValueList.begin() + index);
			else
				scaleNoteValueList.erase(scaleNoteValueList.begin(), scaleNoteValueList.begin() + index);
		}
		updateNoteList();
	}

	void IgniteCustomScaleOpt::paint(juce::Graphics& g)
	{

		Image defaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("bg-modal-container-default.png"));
		Image activeImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("bg-modal-container-default-hover.png"));
		Image btnActiveImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("inst-bg-container-Active.png"));
		g.drawImage(listofListBox[0]->getFocusState() ? activeImage : defaultImage, ui::Rectangle<float>{ 0, 10, 250, 95 }, RectanglePlacement::centred);
		g.drawImage(listofListBox[1]->getFocusState() ? activeImage : defaultImage, ui::Rectangle<float>{ 258, 10, 250, 95 }, RectanglePlacement::centred);
		g.drawImage(listofListBox[2]->getFocusState() ? activeImage : defaultImage, ui::Rectangle<float>{ 516, 10, 250, 95 }, RectanglePlacement::centred);
		g.drawImage(listofListBox[3]->getFocusState() ? activeImage : defaultImage, ui::Rectangle<float>{ 0, 113, 250, 95 }, RectanglePlacement::centred);
		g.drawImage(listofListBox[4]->getFocusState() ? activeImage : defaultImage, ui::Rectangle<float>{ 258, 113, 250, 95 }, RectanglePlacement::centred);
		g.drawImage(listofListBox[5]->getFocusState() ? activeImage : defaultImage, ui::Rectangle<float>{ 516, 113, 250, 95 }, RectanglePlacement::centred);
		g.drawImage(listofListBox[6]->getFocusState() ? activeImage : defaultImage, ui::Rectangle<float>{ 0, 216, 250, 95 }, RectanglePlacement::centred);
		g.drawImage(listofListBox[7]->getFocusState() ? activeImage : defaultImage, ui::Rectangle<float>{ 258, 216, 250, 95 }, RectanglePlacement::centred);
		g.drawImage(listofListBox[8]->getFocusState() ? activeImage : defaultImage, ui::Rectangle<float>{ 516, 216, 250, 95 }, RectanglePlacement::centred);
		g.drawImage(listofListBox[9]->getFocusState() ? activeImage : defaultImage, ui::Rectangle<float>{ 0, 319, 250, 95 }, RectanglePlacement::centred);
		g.drawImage(listofListBox[10]->getFocusState() ? activeImage : defaultImage, ui::Rectangle<float>{ 258, 319, 250, 95 }, RectanglePlacement::centred);
	}

	void IgniteCustomScaleOpt::resized()
	{
		InstrBox_colume1.performLayout(ui::Rectangle(0, 10, 770, 95));
		InstrBox_colume2.performLayout(ui::Rectangle(0, 113, 770, 95));
		InstrBox_colume3.performLayout(ui::Rectangle(0, 216, 770, 95));
		InstrBox_colume4.performLayout(ui::Rectangle(0, 319, 513, 95));
		udsApplyBtn.setBounds(516, 319, 250, 95);
	}

	void IgniteCustomScaleOpt::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		

		if (buttonThatWasClicked == &udsApplyBtn)
		{
			udsApplyBtn.setToggleState(false, dontSendNotification);
			if (scalePtr->checkValidScaleSequence())
			{
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramActiveUds, scalePtr->getSelected());
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramUdsConfigDone, scalePtr->getSelected());
				if (IgniteSong::getAppSongInstance()->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
					AppSceneView::getAppSceneViewInstance(IgniteScene::getAppSceneInstance())->setFTSListUpdateState(true);
			}
			else
			{
				if (ptr->isDialogOpen.get() != true)
				{
					ptr->close();
					ptr->setPopUpPropories("Invalid " + gCustomScale[scalePtr->getSelected()].name + " NOTE Configuration !!!", 604, 290);
					ptr->setbtnsize(265, 44);
					ptr->setInfoText("Please configure correctly, NOTES value shall in be sequential order \n  For ex: NOTE:VALUE 1:C 2:C# 3:D 4:D# 5:E 6:F 7:F# 8:G 9:G# 10:A");
					ptr->addImageButton("OK", "btn-deleteyes-default.png", "btn-deleteyes-active.png", 1);
					ptr->popupType = POPUP_WITHOK;
					ptr->isCloseButtonVisible(false);
					ptr->show();
					ptr->onSelectionChanged = [this](int r)
					{
						if (auto dw = getCurrentlyModalComponent())
							dw->exitModalState(0);
					};
				}
			}
		}
	}

	void IgniteCustomScaleOpt::refreshData()
	{
		if ((int)scalePtr->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS1_VALUE) != -1)
			listofListBox[0]->setSelected((int)scalePtr->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS1_VALUE) + 1);
		else
			listofListBox[0]->setSelected(0);
		if ((int)scalePtr->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS2_VALUE) != -1)
			listofListBox[1]->setSelected((int)scalePtr->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS2_VALUE) + 1);
		else
			listofListBox[1]->setSelected(0);
		if ((int)scalePtr->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS3_VALUE) != -1)
			listofListBox[2]->setSelected((int)scalePtr->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS3_VALUE) + 1);
		else
			listofListBox[2]->setSelected(0);
		if ((int)scalePtr->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS4_VALUE) != -1)
			listofListBox[3]->setSelected((int)scalePtr->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS4_VALUE) + 1);
		else
			listofListBox[3]->setSelected(0);
		if ((int)scalePtr->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS5_VALUE) != -1)
			listofListBox[4]->setSelected((int)scalePtr->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS5_VALUE) + 1);
		else
			listofListBox[4]->setSelected(0);
		if ((int)scalePtr->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS6_VALUE) != -1)
			listofListBox[5]->setSelected((int)scalePtr->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS6_VALUE) + 1);
		else
			listofListBox[5]->setSelected(0);
		if ((int)scalePtr->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS7_VALUE) != -1)
			listofListBox[6]->setSelected((int)scalePtr->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS7_VALUE) + 1);
		else
			listofListBox[6]->setSelected(0);
		if ((int)scalePtr->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS8_VALUE) != -1)
			listofListBox[7]->setSelected((int)scalePtr->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS8_VALUE) + 1);
		else
			listofListBox[7]->setSelected(0);
		if ((int)scalePtr->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS9_VALUE) != -1)
			listofListBox[8]->setSelected((int)scalePtr->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS9_VALUE) + 1);
		else
			listofListBox[8]->setSelected(0);
		if ((int)scalePtr->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS10_VALUE) != -1)
			listofListBox[9]->setSelected((int)scalePtr->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS10_VALUE) + 1);
		else
			listofListBox[9]->setSelected(0);
		if ((int)scalePtr->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS11_VALUE) != -1)
			listofListBox[10]->setSelected((int)scalePtr->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS11_VALUE) + 1);
		else
			listofListBox[10]->setSelected(0);
		repaint();
	}

	int IgniteCustomScaleOpt::isEditing()
	{
		int index = 0;

		if (listofListBox[0]->IsEditing())
			index = NOTE1;
		else if (listofListBox[1]->IsEditing())
			index = NOTE2;
		else if (listofListBox[2]->IsEditing())
			index = NOTE3;
		else if (listofListBox[3]->IsEditing())
			index = NOTE4;
		else if (listofListBox[4]->IsEditing())
			index = NOTE5;
		else if (listofListBox[5]->IsEditing())
			index = NOTE6;
		else if (listofListBox[6]->IsEditing())
			index = NOTE7;
		else if (listofListBox[7]->IsEditing())
			index = NOTE8;
		else if (listofListBox[8]->IsEditing())
			index = NOTE9;
		else if (listofListBox[9]->IsEditing())
			index = NOTE10;
		else if (listofListBox[10]->IsEditing())
			index = NOTE11;

		return index;
	}
	bool IgniteCustomScaleOpt::pannelKeyHandler(paramId_t param, uint32_t keyValue)
	{
		bool setfocus = true;
		int editItem = udsViewItemID::NO_FOCUS;

		if (ptr != nullptr && ptr->IsEditing())
			return ptr->FPKeyHandler(true, param, keyValue);

		if (keyFocusedItem == udsViewItemID::NO_FOCUS)
		{
			keyFocusedItem = udsViewItemID::NOTE1;
		}
		else
		{
			editItem = isEditing();
			if (editItem)
			{
				if (keyFocusedItem != editItem)
				{
					pannelSendKey(false, param, keyValue);
					keyFocusedItem = editItem;
				}
				setfocus = true;
			}
			else
			{
				pannelSendKey(false, param, keyValue);

				if (scalePtr->getOptionHandlerState() != scalePtr->UDS_DETAIL)
					return true;

				switch ((FrontPannelParam)param)
				{
				case FrontPannelParam::paramKey_RMOVELEFT:
					keyFocusedItem = (keyFocusedItem + 1 >= udsViewItemID::FOCUS_MAX ? udsViewItemID::FOCUS_MAX : keyFocusedItem + 1);
					break;
				case FrontPannelParam::paramKey_RMOVERIGHT:
					keyFocusedItem = (keyFocusedItem - 1 <= udsViewItemID::NO_FOCUS ? udsViewItemID::NO_FOCUS + 1 : keyFocusedItem - 1);
					break;
				case FrontPannelParam::paramKey_RETURN_NAV:
					AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SCENE_WINDOW);
					break;
				case FrontPannelParam::paramRot_ROW:

					if (keyValue == ROTARY_DIRECTION_RIGHT)
					{
						pannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
						keyFocusedItem = (keyFocusedItem + SCENE_UDS_NO_COM_ROW >= udsViewItemID::FOCUS_MAX ? ((keyFocusedItem + SCENE_UDS_NO_COM_ROW) == (udsViewItemID::FOCUS_MAX) ? (udsViewItemID::FOCUS_MAX) : keyFocusedItem) : keyFocusedItem + SCENE_UDS_NO_COM_ROW);
						pannelSendKey(true, (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT, 0x47);
					}
					else
					{
						pannelSendKey(false, (paramId_t)FrontPannelParam::paramKey_RMOVELEFT, 0x48);
						keyFocusedItem = (keyFocusedItem - SCENE_UDS_NO_COM_ROW <= udsViewItemID::NO_FOCUS ? (keyFocusedItem) : keyFocusedItem - SCENE_UDS_NO_COM_ROW);
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
			pannelSendKey(true, param, keyValue);
		}
		return true;
	}

	void IgniteCustomScaleOpt::pannelSendKey(bool isFocuse, paramId_t param, uint32_t keyValue)
	{
		switch (udsViewItems[keyFocusedItem])
		{
		case NOTE1:
			listofListBox[0]->FPKeyHandler(isFocuse, param, keyValue);
			break;
		case NOTE2:
			listofListBox[1]->FPKeyHandler(isFocuse, param, keyValue);
			break;
		case NOTE3:
			listofListBox[2]->FPKeyHandler(isFocuse, param, keyValue);
			break;
		case NOTE4:
			listofListBox[3]->FPKeyHandler(isFocuse, param, keyValue);
			break;
		case NOTE5:
			listofListBox[4]->FPKeyHandler(isFocuse, param, keyValue);
			break;
		case NOTE6:
			listofListBox[5]->FPKeyHandler(isFocuse, param, keyValue);
			break;
		case NOTE7:
			listofListBox[6]->FPKeyHandler(isFocuse, param, keyValue);
			break;
		case NOTE8:
			listofListBox[7]->FPKeyHandler(isFocuse, param, keyValue);
			break;
		case NOTE9:
			listofListBox[8]->FPKeyHandler(isFocuse, param, keyValue);
			break;
		case NOTE10:
			listofListBox[9]->FPKeyHandler(isFocuse, param, keyValue);
			break;
		case NOTE11:
			listofListBox[10]->FPKeyHandler(isFocuse, param, keyValue);
			break;
		case APPLY_NOTE_VALUES:
			udsApplyBtn.FPKeyHandler(isFocuse, param, keyValue);
			break;
		}
	}
};