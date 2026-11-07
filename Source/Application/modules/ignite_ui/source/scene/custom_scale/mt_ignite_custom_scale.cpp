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
	juce::Array<mt::Ignite::customScaleData> gCustomScale;

	////////////////////////////////////////////////
	//   Class: Ignite CustomScale
	////////////////////////////////////////////////
	IgniteCustomScale::IgniteCustomScale()
	{
		addNewInList.makeVisibleAndAddListner(this);
		addNewInList.setColour(juce::TextButton::buttonColourId, Theme::Instance().getColour(neutralGrey1));
		addAndMakeVisible(view);
		addAndMakeVisible(container);
		view.setViewedComponent(&container, true);
		view.setBounds(10, 68, 230, 400);
		view.setScrollBarsShown(true, false, true, true);
		view.setScrollBarThickness(5);
		view.setScrollOnDragMode(juce::Viewport::ScrollOnDragMode::all);

		setBufferedToImage(true);
		customScaleCreated = false;
		curretCustomScaleRow = -1;
		refreshCustomScaleUI();

		_pScaleOptInstance = IgniteCustomScaleOpt::getcustomScaleInstanceOpt(this);
		addChildComponent(_pScaleOptInstance);
		_pScaleOptInstance->setBounds(250, yStartInstrView, 784, 430);

		_pEmptyScaleComp = new class AppDnp();
		addChildComponent(_pEmptyScaleComp);
		_pEmptyScaleComp->setBounds(10, 118, 1004, 352);
		_pEmptyScaleComp->setDisplayMessage(String(" "));
		_pEmptyScaleComp->setBackgrounImage(juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("img-empty-state-uds.png")));

		_pScaleOptCtr = IgniteControlOptions::GetAppOptInstance();
		_pScaleOptCtr->setBounds(xStartOptctl, yStartOptctl, widthOptctl, heightOptctlt);
		_pScaleOptCtr->addOptCtlListener(this);

		addNew.makeVisibleAndAddListner(this);
		addNew.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		addNew.setColour(juce::TextEditor::outlineColourId, Theme::Instance().getColour(customBlue13));
		addNew.setColour(TextButton::ColourIds::textColourOffId, Theme::Instance().getColour(customBlue13));
		addNew.setColour(TextButton::ColourIds::buttonColourId, Theme::Instance().getColour(customdblue));
		addNewInList.setVisible(false);
		addNew.setBounds(Rectangle(xStartAddNewBtn, 63, widthAddNewBtn, heightAddNewBtn));
		bootup = true;

		_pPopupPtr = CommonPopUp::getCommonPopupInstance();
	}

	IgniteCustomScale::~IgniteCustomScale()
	{
		cleanup();
	}

	int IgniteCustomScale::getSelected(void)
	{
		return selected;
	}

	void IgniteCustomScale::setSelected(int index)
	{
		if (selected != index)
			enableControlButton(IgniteControlOptions::ALL, false);

		if (isPositiveAndBelow(index, list.size()))
			selected = index;

		// Highlist selected row.
		for (auto& i : list)
			i->highlight(false);
		list[selected]->highlight(true);

		requestDataFromEngine(selected);

		_pScaleOptInstance->setVisible(true);
		_pScaleOptInstance->refreshData();
		if (this->isVisible())
		{
			if (customScaleCreated)
			{
				enableControlButton(IgniteControlOptions::DEL, true);
			}

			if (customScaleDataUpdated)
			{
				enableControlButton(IgniteControlOptions::SAVE, true);
				enableControlButton(IgniteControlOptions::UNDO, true);
			}
		}
	}

	void IgniteCustomScale::updateDataFromEngine()
	{
		std::vector<IgniteParamList> scaleParams;
		IgniteParamList params;

		list.clear();
		gCustomScale.clear();

		params.param = (paramId_t)SettingsUdsCnfgParam::paramUdsNameList;
		scaleParams.push_back(params);
		scaleParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, scaleParams);
		selected = 0;

		if (scaleParams.size() != 0)
		{
			customScaleCreated = true;
			for (auto& i : scaleParams)
			{
				addCustomScale(false);
				setCustomScaleData(mt::Ignite::customScaleDataIndex::FTS_NAME, i.MsgValue.get<std::string>(), true);
				selected++;
			}
			selected = 0;
			setSelected(selected);
			_pEmptyScaleComp->setVisible(false);
			addNew.setVisible(false);
			addNewInList.setVisible(true);
		}
		else
		{
			customScaleCreated = false;
			_pEmptyScaleComp->setVisible(true);
			addNew.setVisible(true);
			addNewInList.setVisible(false);
		}
	}

	void IgniteCustomScale::requestDataFromEngine(int index)
	{
		std::vector<IgniteParamList> scaleParams;
		IgniteParamList params;

		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramActiveUds, index);

		for (auto i = (int)SettingsUdsCnfgParam::paramUdsNote1; i <= (int)SettingsUdsCnfgParam::paramUdsNote12; i++)
		{
			params.param = (paramId_t)SettingsUdsCnfgParam(i);
			scaleParams.push_back(params);
		}

		auto data = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, scaleParams);

		for (auto i = (int)mt::Ignite::customScaleDataIndex::FTS1_VALUE; i <= (int)mt::Ignite::customScaleDataIndex::FTS12_VALUE; i++)
			setCustomScaleData((mt::Ignite::customScaleDataIndex)i, data[i - (int)mt::Ignite::customScaleDataIndex::FTS1_VALUE].MsgValue.get<int8_t>(), true);
	}

	void IgniteCustomScale::updateLables()
	{
		std::vector<IgniteParamList> scaleParams;
		IgniteParamList params;

		params.param = (paramId_t)SettingsUdsCnfgParam::paramUndoListCmd;
		scaleParams.push_back(params);
		scaleParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, scaleParams);

		if (scaleParams.size() == 1)
		{
			enableControlButton(IgniteControlOptions::SAVE, false);
			enableControlButton(IgniteControlOptions::UNDO, false);
			customScaleDataUpdated = false;
			updateScaleEditIndication();
		}
		_pScaleOptInstance->repaint();
	}

	void IgniteCustomScale::cleanup()
	{
		container.removeAllChildren();
		list.clear();
	}

	String IgniteCustomScale::getScaleName()
	{
		std::vector<IgniteParamList> scaleNameList;
		IgniteParamList params;

		scaleNameList.clear();
		params.param = (paramId_t)SettingsUdsCnfgParam::paramUdsNameList;
		params.startPos = 0;
		params.Count = 100;
		scaleNameList.push_back(params);
		scaleNameList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, scaleNameList);

		if (scaleNameList.size())
			return scaleNameList[scaleNameList.size() - 1].MsgValue.get<std::string>();
		else
			return "";
	}

	void IgniteCustomScale::populate()
	{
		mt::Ignite::customScaleData CustomScaledata;
		IgniteCustomScaleRow* row;
		String name = getScaleName();

		curretCustomScaleRow++;
		CustomScaledata = gCustomScale[list.size()];

		if (name != "")
			CustomScaledata.name = getScaleName();

		row = new IgniteCustomScaleRow(list.size(), CustomScaledata, this);
		list.add(row);
		container.addAndMakeVisible(row);
		customScaleCreated = true;
		refreshCustomScaleUI();
	}

	void IgniteCustomScale::refreshCustomScaleUI()
	{
		int index = 0;
		for (auto& i : list)
		{
			i->setBounds(0, ((52 * index++)), 220, 44);
			i->onMouseDown = [this](IgniteCustomScaleRow* Row)
			{
				showPopup((Row->getSerialNumber()));
			};
		}

		addNewInList.setBounds(0, (52 * index), 220, 44);

		// Set overall view container size....
		container.setSize(220, ((index + 1) * 52));
		if (customScaleCreated)
		{
			setSelected(selected);
			container.addAndMakeVisible(addNewInList);
		}
		if (addNewInList.isVisible())
			addNew.setVisible(false);
	}

	void IgniteCustomScale::addCustomScale(bool isScaleUpdateneeded)
	{
		String CustomScale_name = String("UDS" + String(list.size() + 1));
		gCustomScale.add({ list.size() , CustomScale_name, list.size(), -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 });
		if (isScaleUpdateneeded)
		{
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramAddUds, 0);
		}
		populate();
		_pEmptyScaleComp->setVisible(false);
		addNewInList.setVisible(true);
	}

	void IgniteCustomScale::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &addNewInList || buttonThatWasClicked == &addNew)
		{
			addNew.setVisible(false);
			addCustomScale(true);
			repaint();
			if (addNewInList.getToggleState())
				addNewInList.setToggleState(false, dontSendNotification);
		}
	}

	void IgniteCustomScale::paint(juce::Graphics& g)
	{
		MenuMode::GetMenuModeInstance()->setHeader("User Defined Scales");
		g.setColour(ui::Theme::Instance().getColour((neutralBlack)));
		g.fillAll();

		if (bootup)
		{
			bootup = false;
			updateDataFromEngine();
		}
		if (customScaleCreated && this->isVisible())
			enableControlButton(IgniteControlOptions::DEL, true);

		if (addNew.isVisible())
		{
			String name = addNew.getToggleState() ? "btn-add-newscale-active.png" : addNew.isMouseOver() ? "btn-add-newscale-hover.png" : "btn-add-newscale-default.png";
			Image Draw = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile(name));
			g.drawImage(Draw, ui::Rectangle<float>{xStartAddNewBtn, 63, widthAddNewBtn, heightAddNewBtn}, RectanglePlacement::centred);
		}
	}

	void IgniteCustomScale::resized()
	{
	}

	void IgniteCustomScale::updateData()
	{
	}

	void IgniteCustomScale::updateScaleEditIndication()
	{
		list[selected]->updateEditIndication();
	}

	void IgniteCustomScale::showPopup(int index)
	{
		if (_pPopupPtr->isDialogOpen.get() != true)
		{
			_pPopupPtr->close();
			_pPopupPtr->setPopUpPropories("Switch Selected Scale", 604, 290);
			_pPopupPtr->setbtnsize(184, 44);
			_pPopupPtr->addImageButton("Cancel", "btn-cancel-174x44-default-hover.png", "btn-cancel-174x44-default.png", 2);
			_pPopupPtr->addImageButton("Confirm Switch", "btn-confirmswitch-174x44-default.png", "btn-confirmswitch-174x44-default-hover.png", 1);
			_pPopupPtr->addImageButton("Save and Switch", "btn-saveswitch-174x44-default.png", "btn-saveswitch-174x44-default-hover.png", 3);
			_pPopupPtr->setInfoText(String(gCustomScale[selected].name) + " unsaved data will be lost");

			if ((index == selected) || (!customScaleDataUpdated))
			{
				setSelected(index);
				return;
			}
			prevSelected = index;
			_pPopupPtr->popupType = POPUP_CHANGEWARNING;
			_pPopupPtr->isCloseButtonVisible(false);
			_pPopupPtr->show();
			_pPopupPtr->onSelectionChanged = [this](int r)
			{
				if (r == 1)
				{
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramClearUndoList, selected);
					customScaleDataUpdated = false;
					updateLables();
					setSelected(prevSelected);
				}
				if (r == 3)
				{
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramActiveUds, selected);
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::SettingsUdsCnfgSaveParam, selected);
					customScaleDataUpdated = false;
					updateLables();
					setSelected(prevSelected);
				}

				if (r == 2)
					UdsRowHighLightIndex = prevSelected - 1;

				if (auto dw = getCurrentlyModalComponent())
					dw->exitModalState(0);

			};
		}
	}

	void IgniteCustomScale::changeCustomScaleOptionsVisibility(bool bShouldShow)
	{
		_pScaleOptInstance->setVisible(bShouldShow);
		for (auto eachRow : list)
		{
			eachRow->setVisible(!bShouldShow);
		}
		resized();
	}

	void IgniteCustomScale::updateCustomScaleData(uint8_t param, const uint32_t value)
	{
	}

	void IgniteCustomScale::updateCustomScaleData(uint8_t param, const std::string& value)
	{
	}

	void IgniteCustomScale::setCustomScaleData(mt::Ignite::customScaleDataIndex item_id, int8 data, bool is_internal)
	{
		auto& gCustomScaleRef = gCustomScale.getReference(selected);

		if (!is_internal)
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramActiveUds, selected);

		switch (item_id)
		{
		case mt::Ignite::customScaleDataIndex::FTS1_VALUE:
			gCustomScaleRef.note1_value = data;
			if (!is_internal)
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramUdsNote1, (uint8_t)data);
			break;
		case mt::Ignite::customScaleDataIndex::FTS2_VALUE:
			gCustomScaleRef.note2_value = data;
			if (!is_internal)
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramUdsNote2, (uint8_t)data);
			break;
		case mt::Ignite::customScaleDataIndex::FTS3_VALUE:
			gCustomScaleRef.note3_value = data;
			if (!is_internal)
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramUdsNote3, (uint8_t)data);
			break;
		case mt::Ignite::customScaleDataIndex::FTS4_VALUE:
			gCustomScaleRef.note4_value = data;
			if (!is_internal)
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramUdsNote4, (uint8_t)data);
			break;
		case mt::Ignite::customScaleDataIndex::FTS5_VALUE:
			gCustomScaleRef.note5_value = data;
			if (!is_internal)
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramUdsNote5, (uint8_t)data);
			break;
		case mt::Ignite::customScaleDataIndex::FTS6_VALUE:
			gCustomScaleRef.note6_value = data;
			if (!is_internal)
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramUdsNote6, (uint8_t)data);
			break;
		case mt::Ignite::customScaleDataIndex::FTS7_VALUE:
			gCustomScaleRef.note7_value = data;
			if (!is_internal)
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramUdsNote7, (uint8_t)data);
			break;
		case mt::Ignite::customScaleDataIndex::FTS8_VALUE:
			gCustomScaleRef.note8_value = data;
			if (!is_internal)
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramUdsNote8, (uint8_t)data);
			break;
		case mt::Ignite::customScaleDataIndex::FTS9_VALUE:
			gCustomScaleRef.note9_value = data;
			if (!is_internal)
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramUdsNote9, (uint8_t)data);
			break;
		case mt::Ignite::customScaleDataIndex::FTS10_VALUE:
			gCustomScaleRef.note10_value = data;
			if (!is_internal)
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramUdsNote10, (uint8_t)data);
			break;
		case mt::Ignite::customScaleDataIndex::FTS11_VALUE:
			gCustomScaleRef.note11_value = data;
			if (!is_internal)
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramUdsNote11, (uint8_t)data);
			break;
		case mt::Ignite::customScaleDataIndex::FTS12_VALUE:
			gCustomScaleRef.note12_value = data;
			if (!is_internal)
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramUdsNote12, (uint8_t)data);
			break;
		}
	}

	void IgniteCustomScale::setCustomScaleData(mt::Ignite::customScaleDataIndex item_id, String data, bool is_internal)
	{
		auto& gCustomScaleRef = gCustomScale.getReference(selected);

		if (!is_internal)
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramActiveUds, selected);

		switch (item_id)
		{
		case mt::Ignite::customScaleDataIndex::FTS_NAME:
			gCustomScaleRef.name = data;
			if (!is_internal)
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramUdsName, data.toStdString());
			break;
		}
		list[selected]->refreshCustomScaleRowUI();
	}

	var IgniteCustomScale::getCustomScaleData(mt::Ignite::customScaleDataIndex item_id)
	{
		switch (item_id)
		{
		case mt::Ignite::customScaleDataIndex::FTS_NAME:
			return gCustomScale[selected].name;
		case mt::Ignite::customScaleDataIndex::FTS1_VALUE:
			return gCustomScale[selected].note1_value;
		case mt::Ignite::customScaleDataIndex::FTS2_VALUE:
			return gCustomScale[selected].note2_value;
		case mt::Ignite::customScaleDataIndex::FTS3_VALUE:
			return gCustomScale[selected].note3_value;
		case mt::Ignite::customScaleDataIndex::FTS4_VALUE:
			return gCustomScale[selected].note4_value;
		case mt::Ignite::customScaleDataIndex::FTS5_VALUE:
			return gCustomScale[selected].note5_value;
		case mt::Ignite::customScaleDataIndex::FTS6_VALUE:
			return gCustomScale[selected].note6_value;
		case mt::Ignite::customScaleDataIndex::FTS7_VALUE:
			return gCustomScale[selected].note7_value;
		case mt::Ignite::customScaleDataIndex::FTS8_VALUE:
			return gCustomScale[selected].note8_value;
		case mt::Ignite::customScaleDataIndex::FTS9_VALUE:
			return gCustomScale[selected].note9_value;
		case mt::Ignite::customScaleDataIndex::FTS10_VALUE:
			return gCustomScale[selected].note10_value;
		case mt::Ignite::customScaleDataIndex::FTS11_VALUE:
			return gCustomScale[selected].note11_value;
		case mt::Ignite::customScaleDataIndex::FTS12_VALUE:
			return gCustomScale[selected].note12_value;
		default:
			return -1;
		}
	}

	void IgniteCustomScale::deleteCurrentCustomScale()
	{
		//Send request to Engine for deleting CustomScale
		container.removeChildComponent(selected);
		list.remove(selected);
		container.setSize(220, (list.size() * layout::row.getHeight()));
	}

	bool IgniteCustomScale::checkValidScaleSequence()
	{
		bool firstNoteFlag = true;
		bool boundaryCrossedFlag = false;
		int startNote = -1;
		int prevNote = -1;
		uint16_t noteMarker = 0x0000;
		bool validStatus = true;
		std::vector<int>noteList;

		for (auto i = (int)mt::Ignite::customScaleDataIndex::FTS1_VALUE; i <= (int)mt::Ignite::customScaleDataIndex::FTS12_VALUE; i++)
		{
			int note_value = (int)getCustomScaleData((mt::Ignite::customScaleDataIndex)i);
			if (note_value != -1)
				noteList.push_back(note_value);
		}

		for (auto note : noteList)
		{
			if ((noteMarker & (1 << note)) == 0)//check for duplicate
			{
				// Very first note is marked to check that the sequence does not go above 1 octave
				if (firstNoteFlag == true)
				{
					firstNoteFlag = false;
					startNote = note;
					prevNote = note;
					noteMarker |= (1 << note);
				}
				else
				{
					// assume notes arranged in order from c, c# . . . a# & b. Checks if it crossed over b and started from begining
					if (boundaryCrossedFlag == true)
					{
						if ((note > prevNote) && (note < startNote))
						{
							prevNote = note;
							noteMarker |= (1 << note);
						}
						else
						{
							validStatus = false;
							break;
						}
					}
					else
					{
						if (note > prevNote)
						{
							prevNote = note;
							noteMarker |= (1 << note);
						}
						else
						{
							if (note < startNote)
							{
								boundaryCrossedFlag = true;
								prevNote = note;
								noteMarker |= (1 << note);
							}
							else
							{
								validStatus = false;
								break;
							}
						}
					}//boundary not crossed
				}// first note = false (subsequent notes)
			}
			else//it is duplicate
			{
				validStatus = false;
				break;
			}
		}
		return validStatus;
	}

	bool IgniteCustomScale::pannelKeyOptionsHandler(paramId_t param, uint32_t KeyValue)
	{
		bool setfocus = true;

		if (keyFocusedItem == OptionsViewItemID::NO_FOCUS)
		{
			/*1st key after Page visible */
			keyFocusedItem = OptionsViewItemID::UDS_UNDO;
		}
		else
		{
			pannelSendKey(false, param, KeyValue); // clear last Focus
			if (optionHandlerEnabled != UDS_OPTION)
				return true;
			switch ((FrontPannelParam)param)
			{
			case FrontPannelParam::paramKey_RMOVELEFT:
				keyFocusedItem = (keyFocusedItem + 1 >= OptionsViewItemID::FOCUS_MAX ? (OptionsViewItemID::FOCUS_MAX) : keyFocusedItem + 1);
				break;
			case FrontPannelParam::paramKey_RMOVERIGHT:
				keyFocusedItem = (keyFocusedItem - 1 <= OptionsViewItemID::NO_FOCUS ? (OptionsViewItemID::NO_FOCUS + 1) : keyFocusedItem - 1);
				break;
			}
		}
		if (setfocus)
		{
			pannelSendKey(true, param, KeyValue);
		}
		return true;
	}

	void IgniteCustomScale::pannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		switch (OptionsView[keyFocusedItem])
		{
		case UDS_UNDO:
			_pScaleOptCtr->PannelKeyHandler(IgniteControlOptions::eKey::UNDO, isFocuse, param, KeyValue);
			break;
		default:
			break;
		}
	}

	bool IgniteCustomScale::pannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool keyHandled = false;
		itemParam = param;
		itemKeyValue = KeyValue;

		if (_pPopupPtr != nullptr && _pPopupPtr->IsEditing())
		{
			if ((param != (paramId_t)FrontPannelParam::paramRot_ROW) && (param != (paramId_t)FrontPannelParam::paramKey_ROTARYROW))
			{
				return _pPopupPtr->FPKeyHandler(true, param, KeyValue);
			}
			else
			{
				if (param == (paramId_t)FrontPannelParam::paramRot_ROW)
				{
					if ((KeyValue == ROTARY_RIGHT || KeyValue == ROTARY_FASTRIGHT || KeyValue == ROTARY_SUPERFASTRIGHT))
						param = (paramId_t)FrontPannelParam::paramKey_RMOVELEFT;
					else if ((KeyValue == ROTARY_LEFT || KeyValue == ROTARY_FASTLEFT || KeyValue == ROTARY_SUPERFASTLEFT))
						param = (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT;
				}
				else if (param == (paramId_t)FrontPannelParam::paramKey_ROTARYROW)
				{
					param = (paramId_t)FrontPannelParam::paramKey_RSELECT;
				}

				return _pPopupPtr->FPKeyHandler(true, param, 1);
			}
		}

		if (param == (paramId_t)FrontPannelParam::paramKey_NEXT_TIE && _pScaleOptCtr->getOperationMode() == mt::Ignite::operatioMode::IDLE_MODE)
		{
			if (!list.isEmpty())
			{
				list[UdsRowHighLightIndex]->SetFocus(false, false);
				this->postCommandMessage(4);

				if (UdsRowHighLightIndex + 1 >= list.size())
					UdsRowHighLightIndex = 0;
				else
					UdsRowHighLightIndex = jmin<int>(jmax<int>((UdsRowHighLightIndex + 1), 0), (list.size() - 1));

				if ((UdsRowHighLightIndex) * 52 > (view.getViewArea().getHeight() - 52))
					view.setViewPosition(view.getViewPositionX(), view.getViewPositionY() + 52);

				list[UdsRowHighLightIndex]->SetFocus(true, false);
				repaint();
			}
			return true;
		}

		if (list.isEmpty())
		{
			if (addNew.isVisible() == true)
			{
				if (((FrontPannelParam)param == FrontPannelParam::paramKey_RSELECT) || ((FrontPannelParam)param == FrontPannelParam::paramKey_INSERT))
					this->postCommandMessage(2); //Add new Button
			}
		}
		else
		{
			if (!list.isEmpty() && ((FrontPannelParam)param == FrontPannelParam::paramRot_ROW || (FrontPannelParam)param == FrontPannelParam::paramKey_ROTARYROW ||
				(FrontPannelParam)param == FrontPannelParam::paramKey_INSERT))
			{
				(list)[UdsRowHighLightIndex]->SetFocus(false, false);
				addNewInList.setState(Button::ButtonState::buttonNormal);
				switch ((FrontPannelParam)param)
				{
				case FrontPannelParam::paramRot_ROW:
					if ((KeyValue == ROTARY_RIGHT || KeyValue == ROTARY_FASTRIGHT || KeyValue == ROTARY_SUPERFASTRIGHT))
					{
						if (UdsRowHighLightIndex + 1 >= list.size() && addNewInList.isVisible())
						{
							addNewInList.setState(Button::ButtonState::buttonOver);
							UdsRowHighLightIndex = (list.size() - 1);
							addNewInListHiglited = true;
						}
						else
						{
							UdsRowHighLightIndex = jmin<int>(jmax<int>((UdsRowHighLightIndex + 1), 0), (list.size() - 1));
						}

						if ((UdsRowHighLightIndex) * 52 > (view.getViewArea().getHeight() - 52))
							view.setViewPosition(view.getViewPositionX(), view.getViewPositionY() + 52);
					}
					else if ((KeyValue == ROTARY_LEFT || KeyValue == ROTARY_FASTLEFT || KeyValue == ROTARY_SUPERFASTLEFT))
					{
						if (addNewInListHiglited)
						{
							addNewInList.setState(Button::ButtonState::buttonNormal);
							addNewInListHiglited = false;
							UdsRowHighLightIndex = (list.size() - 1);
						}
						else
							UdsRowHighLightIndex = jmin<int>(jmax<int>((UdsRowHighLightIndex - 1), 0), (list.size() - 1));

						if ((UdsRowHighLightIndex - 1) * 52 <= (view.getViewArea().getHeight()))
							view.setViewPosition(view.getViewPositionX(), view.getViewPositionY() - 52);
					}
					break;
				case FrontPannelParam::paramKey_ROTARYROW:
					if (addNewInListHiglited)
						this->postCommandMessage(2); //Add new in list Button
					else if (UdsRowHighLightIndex == list.size())
						(list)[UdsRowHighLightIndex]->postCommandMessage(1);
					else
						this->postCommandMessage(4);
					break;
				case FrontPannelParam::paramKey_INSERT:
					this->postCommandMessage(2); //Add new in list Button
					break;
				}

				if (!addNewInListHiglited)
					(list)[UdsRowHighLightIndex]->SetFocus(true, false);
				repaint();
			}
			else if ((optionHandlerEnabled == UDS_OPTION) && !addNew.isVisible() && param != (paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
			{
				keyHandled = pannelKeyOptionsHandler(param, KeyValue);
			}

			else if ((optionHandlerEnabled == UDS_DETAIL) && !addNew.isVisible() && param != (paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
			{
				keyHandled = _pScaleOptInstance->pannelKeyHandler(param, KeyValue);
			}
			else if (!list.isEmpty() && (optionHandlerEnabled == UDS_OPTION))
			{
				if (param == (paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
				{
					if (optionHandlerEnabled == UDS_OPTION)
					{
						optionHandlerEnabled = UDS_DETAIL;
						addNew.setBackgroundColour(juce::Colour(0x0E3252));
						param = (paramId_t)FrontPannelParam::paramKey_RMOVERIGHT;
						pannelKeyOptionsHandler(param, KeyValue);
						keyHandled = pannelKeyHandler(param, KeyValue);
					}
					else
						keyHandled = pannelKeyOptionsHandler(param, KeyValue);
				}
			}
			else if (!list.isEmpty() && (optionHandlerEnabled == UDS_DETAIL))
			{
				if (param == (paramId_t)FrontPannelParam::paramKey_PAGESHIFT)
				{
					if (optionHandlerEnabled == UDS_DETAIL)
					{
						optionHandlerEnabled = UDS_OPTION;
						addNew.setBackgroundColour(juce::Colour(0x0E3252));
						_pScaleOptInstance->pannelKeyHandler(param, KeyValue);
						keyHandled = pannelKeyOptionsHandler(param, KeyValue);
					}
					else
						keyHandled = _pScaleOptInstance->pannelKeyHandler(param, KeyValue);
				}
			}
			else
			{
				if ((FrontPannelParam)param == FrontPannelParam::paramKey_RSELECT)
					this->postCommandMessage(1); //Add new Button
				keyHandled = true;
			}
		}

		return keyHandled;
	}
	void IgniteCustomScale::handleCommandMessage(int id)
	{
		if (id == 1)
			buttonClicked(&addNew);
		else if (id == 2)
			buttonClicked(&addNewInList);
		else if (id == 4)
			(list)[UdsRowHighLightIndex]->PannelKeyHandler(itemParam, itemKeyValue);
	}

	////////////////////////////////////////////////
	//   Class: Ignite CustomScale row
	////////////////////////////////////////////////
	IgniteCustomScaleRow::IgniteCustomScaleRow(int SerialNumber, mt::Ignite::customScaleData& Data, IgniteCustomScale* CustomScalePtr) : customScaledata(Data)
	{
		_pCustomScale = CustomScalePtr;
		srNo.makeVisible(this);
		name.makeVisibleAndAddListner(this);

		name.setDisplayTitle(true);
		name.setEditable(false, true, false);
		name.setDisplayTitle(false);
		name.addMouseListener(this, false);

		srNo.setText(String(SerialNumber), juce::dontSendNotification);
		name.setText(customScaledata.name, juce::dontSendNotification);
		name.setJustificationType(Justification::centred);
		name.setLableFont(font_10);

		box.items.add(FlexItem(name).withMargin(3).withFlex(3));

		normalImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-inst-list-default-normal.png"));
		activeImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-inst-list-active-normal.png"));

		name.onValueChanged = [this](String value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			if (_pCustomScale->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS_NAME) != value)
			{
				if (IgniteSong::getAppSongInstance()->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
					AppSceneView::getAppSceneViewInstance(IgniteScene::getAppSceneInstance())->setFTSListUpdateState(true);
				_pCustomScale->setCustomScaleDataUpdateStatus(true);
				_pCustomScale->setCustomScaleData(mt::Ignite::customScaleDataIndex::FTS_NAME, value, false);
				if (!_pCustomScale->getAutoSaveStatus())
				{
					_pCustomScale->enableControlButton(IgniteControlOptions::SAVE, true);
					_pCustomScale->enableControlButton(IgniteControlOptions::UNDO, true);
				}
			}
		};

		name.ValidateDataOnChange = [this](String value)
		{
			Component::BailOutChecker checker(this);
			if (checker.shouldBailOut())
				return KEY_PAD_DATA_VALIDATE_OK;

			if (_pCustomScale->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS_NAME) != value)
			{
				//check for duplicate
				for (auto& i : gCustomScale)
				{
					if (i.name == value)
						return KEY_PAD_DATA_DUPLICATE_ERROR; // Name already present
				}
			}
			return KEY_PAD_DATA_VALIDATE_OK;
		};
	}

	IgniteCustomScaleRow::~IgniteCustomScaleRow()
	{}

	void IgniteCustomScaleRow::mouseUp(const MouseEvent& event)
	{
		if (onMouseDown)
			onMouseDown(this);
	}

	void IgniteCustomScaleRow::mouseDrag(const MouseEvent& event)
	{
		juce::DragAndDropContainer* dragC = juce::DragAndDropContainer::findParentDragContainerFor(this);
		if (dragC)
		{
			if (!dragC->isDragAndDropActive())
			{
				if (_pCustomScale->getMoveEnableStatus())
					dragC->startDragging("TargetSource", this);
				rowIsBeingDraggedOver = true;
			}
		}
	}

	void IgniteCustomScaleRow::highlight(bool State)
	{
		isHighlighted = State;
		repaint();
	}

	int IgniteCustomScaleRow::getSerialNumber()
	{
		return srNo.getText().getIntValue();
	}

	void IgniteCustomScaleRow::mouseDown(const MouseEvent& event)
	{
	}

	void IgniteCustomScaleRow::showCustomScaleView()
	{
		auto pChild = IgniteCustomScaleOpt::getcustomScaleInstanceOpt(_pCustomScale);
		serialNo = getSerialNumber();
		_pCustomScale->setCurrentCustomScaleRow(serialNo);
		mt::Ignite::customScaleData idata = gCustomScale[serialNo];
		pChild->refreshData();
		_pCustomScale->changeCustomScaleOptionsVisibility(true);
	}

	void IgniteCustomScaleRow::setColor(int colourID, Colour colour)
	{
		if (colourID == ui::Label::backgroundColourId)
		{
			name.setBackgroundColour(colour);
		}
		else if (colourID == ui::Label::textColourId)
		{
			name.setTextColour(colour);
		}
		else if (colourID == ui::Label::outlineColourId)
		{
			name.setColour(ui::Label::outlineColourId, colour);
		}
	}

	void IgniteCustomScaleRow::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &options)
		{
			showCustomScaleView();
		}
	}

	void IgniteCustomScaleRow::updateEditIndication()
	{
		String scaleNameString = _pCustomScale->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS_NAME);

		if (_pCustomScale->getCustomScaleDataUpdateStatus())
			scaleNameString = scaleNameString + "*";

		name.setText(scaleNameString, juce::dontSendNotification);
	}

	void IgniteCustomScaleRow::refreshCustomScaleRowUI()
	{
		name.setText(_pCustomScale->getCustomScaleData(mt::Ignite::customScaleDataIndex::FTS_NAME), juce::dontSendNotification);
	}

	void IgniteCustomScaleRow::labelTextChanged(Label* labelThatHasChanged)
	{
		if (labelThatHasChanged == &name)
		{
			_pCustomScale->setCustomScaleData(mt::Ignite::customScaleDataIndex::FTS_NAME, name.getText(), false);
			_pCustomScale->setCustomScaleDataUpdateStatus(true);
			updateEditIndication();
		}
	}

	void IgniteCustomScaleRow::paint(juce::Graphics& g)
	{
		Image Draw;
		String rowName;

		rowName = isHighlighted ? isMouseOver ? "list-item-active-hover.png" : "list-item-active.png" : isMouseOver ? "list-item-default-hover.png" : "list-item-default.png";
		Draw = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile(rowName));
		g.drawImage(Draw, getLocalBounds().toFloat(), RectanglePlacement::centred);
	}

	void IgniteCustomScaleRow::resized()
	{
		box.performLayout(getLocalBounds());
	}

	bool IgniteCustomScaleRow::PannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT || param == (paramId_t)FrontPannelParam::paramKey_NEXT_TIE || param == (paramId_t)FrontPannelParam::paramKey_ROTARYROW)
		{
			onMouseDown(this);
		}
		else if (param == (paramId_t)FrontPannelParam::paramKey_RDBLSELECT)
		{
			name.editLable();
			name.PannelKeyHandler(param, KeyValue);
		}

		return true;
	}


	void IgniteCustomScale::onOptCtlButtonClicked(IgniteControlOptions::eKey option)
	{
		int selected_CustomScale_index;

		if (this->isVisible())
		{
			switch (option)
			{
			case IgniteControlOptions::SAVE:
				if (globalSettingUpdated)
				{
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsGeneralCnfgParam::SettingDeviceCnfgSave, 0);
					globalSettingUpdated = false;
				}
				if (_pPopupPtr->isDialogOpen.get() != true)
				{
					_pPopupPtr->close();
					_pPopupPtr->setPopUpPropories("Save ", 604, 290);
					_pPopupPtr->setbtnsize(265, 44);
					_pPopupPtr->setInfoText(String(" Save " + gCustomScale[selected].name + " edits? "));
					_pPopupPtr->addImageButton("no", "btn-secondary-no-267x44-default.png", "btn-secondary-no-267x44-default-hover.png", 2);
					_pPopupPtr->addImageButton("yes", "btn-yes-267x44-default.png", "btn-yes-267x44-default-hover.png", 1);
					_pPopupPtr->popupType = POPUP_WITHOKCANCEL;
					_pPopupPtr->isCloseButtonVisible(false);
					_pPopupPtr->show();
					_pPopupPtr->onSelectionChanged = [this](int r)
					{
						if (r == 1)
						{
							_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramActiveUds, selected);
							_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::SettingsUdsCnfgSaveParam, 0);
							if (IgniteSong::getAppSongInstance()->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
								AppSceneView::getAppSceneViewInstance(IgniteScene::getAppSceneInstance())->setFTSListUpdateState(true);
							customScaleDataUpdated = false;
							updateLables();
						}
						if (auto dw = getCurrentlyModalComponent())
							dw->exitModalState(0);
					};
				}
				break;
			case IgniteControlOptions::DEL:
			{
				if (gCustomScale.size() > 0)
				{
					selected_CustomScale_index = getSelected();
					if (_pPopupPtr->isDialogOpen.get() != true)
					{
						_pPopupPtr->close();
						_pPopupPtr->setPopUpPropories("Delete " + gCustomScale[selected].name, 604, 290);
						_pPopupPtr->setbtnsize(265, 44);
						_pPopupPtr->setInfoText("Are you sure you want to delete " + gCustomScale[selected].name);
						_pPopupPtr->addImageButton("no", "btn-secondary-no-267x44-default.png", "btn-secondary-no-267x44-default-hover.png", 2);
						_pPopupPtr->addImageButton("yes", "btn-yes-267x44-default.png", "btn-yes-267x44-default-hover.png", 1);
						_pPopupPtr->popupType = POPUP_WITHOKCANCEL;
						_pPopupPtr->isCloseButtonVisible(false);
						_pPopupPtr->show();
						_pPopupPtr->onSelectionChanged = [this, selected_CustomScale_index](int r)
						{
							if (r == 1)
							{
								auto selected_scale_index = getSelected();
								_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramActiveUds, selected);
								_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramRemoveUds, selected);

								if (auto dw = getCurrentlyModalComponent())
									dw->exitModalState(0);

								updateDataFromEngine();
								if (gCustomScale.size() > 0)
								{
									if (selected_scale_index == 0)
										setSelected(selected_scale_index);
									else
										setSelected(selected_CustomScale_index - 1);
								}
								else
								{
									customScaleCreated = false;
									_pEmptyScaleComp->setVisible(true);
									addNew.setVisible(true);
									addNewInList.setVisible(false);
									refreshCustomScaleUI();
									_pScaleOptInstance->setVisible(false);
									enableControlButton(IgniteControlOptions::DEL, false);
								}
							}
							else
							{
								if (auto dw = getCurrentlyModalComponent())
									dw->exitModalState(0);
							}
						};
					}
					if (IgniteSong::getAppSongInstance()->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED))
						AppSceneView::getAppSceneViewInstance(IgniteScene::getAppSceneInstance())->setFTSListUpdateState(true);
				}
				break;
			}
			case IgniteControlOptions::UNDO:
				if (customScaleDataUpdated)
				{
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramActiveUds, selected);
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsUdsCnfg, (paramId_t)SettingsUdsCnfgParam::paramUndoCmd, selected);
					Time::waitForMillisecondCounter(Time::getMillisecondCounter() + 50);
					updateLables();
					setSelected(selected);
				}
				break;
			}
		}
	}

	void IgniteCustomScaleRow::mouseMove(const MouseEvent& event)
	{
		isMouseOver = true;
		repaint();
	}

	void IgniteCustomScaleRow::mouseExit(const MouseEvent& event)
	{
		isMouseOver = false;
		repaint();
	}

	void IgniteCustomScaleRow::SetFocus(bool hasFocus, bool activeHasFocus)
	{
		if (hasFocus)
			isMouseOver = true;
		else
			isMouseOver = false;

		if (activeHasFocus)
			name.setBackgroundColour(juce::Colour(0x2086BF));
		repaint();
	};

};