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
	//   Class: IgniteSculptConfig
	////////////////////////////////////////////////
	IgniteSculptConfig::IgniteSculptConfig()
	{
		addAndMakeVisible(modeLable);
		modeLable.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
		modeLable.setJustificationType(juce::Justification::centred);

		addAndMakeVisible(valueLable);
		valueLable.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
		valueLable.setJustificationType(juce::Justification::centred);

		addAndMakeVisible(paramLable);
		paramLable.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
		paramLable.setJustificationType(juce::Justification::left);

		addAndMakeVisible(sculptRelBtn);
		sculptRelBtn.addListener(this);
		sculptRelBtn.setToggleable(true);
		sculptRelBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		sculptRelBtn.sethoverImages("btn-relative-245x50-default-hover.png", "btn-relative-245x50-active-hover.png", "");

		addAndMakeVisible(sculptAbsBtn);
		sculptAbsBtn.addListener(this);
		sculptAbsBtn.setToggleable(true);
		sculptAbsBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		sculptAbsBtn.sethoverImages("btn-absolute-245x50-default-hover.png", "btn-absolute-245x50-active-hover.png", "");

		addAndMakeVisible(randomRelBtn);
		randomRelBtn.addListener(this);
		randomRelBtn.setToggleable(true);
		randomRelBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		randomRelBtn.sethoverImages("btn-random-relative-245x50-default-hover.png", "btn-random-relative-245x50-active-hover.png", "");

		addAndMakeVisible(randomAbsBtn);
		randomAbsBtn.addListener(this);
		randomAbsBtn.setToggleable(true);
		randomAbsBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		randomAbsBtn.sethoverImages("btn-random-absolute-245x50-default-hover.png", "btn-random-absolute-245x50-active-hover.png", "");

		addAndMakeVisible(paramAllBtn);
		paramAllBtn.addListener(this);
		paramAllBtn.setToggleState(true, dontSendNotification);
		paramAllBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		paramAllBtn.sethoverImages("toggle-all-160x44-default-hover.png", "toggle-all-160x44-active-hover.png", "toggle-all-160x44-disabled.png");

		addAndMakeVisible(paramVeloBtn);
		paramVeloBtn.addListener(this);
		paramVeloBtn.setToggleable(true);
		paramVeloBtn.setToggleState(true, dontSendNotification);
		paramVeloBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		paramVeloBtn.sethoverImages("toggle-velocity-160x44-default-hover.png", "toggle-velocity-160x44-active-hover.png", "toggle-velocity-160x44-disabled.png");

		/*addAndMakeVisible(paramLenStepBtn);
		paramLenStepBtn.addListener(this);
		paramLenStepBtn.setToggleable(true);
		paramLenStepBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		paramLenStepBtn.sethoverImages("toggle-lenstep-160x44-default-hover.png", "toggle-lenstep-160x44-active-hover.png", "toggle-lenstep-160x44-disabled.png");

		addAndMakeVisible(paramLenTickBtn);
		paramLenTickBtn.addListener(this);
		paramLenTickBtn.setToggleable(true);
		paramLenTickBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		paramLenTickBtn.sethoverImages("toggle-lentick-160x44-default-hover.png", "toggle-lentick-160x44-active-hover.png", "toggle-lentick-160x44-disabled.png");*/

		addAndMakeVisible(paramNoteBtn);
		paramNoteBtn.addListener(this);
		paramNoteBtn.setToggleable(true);
		paramNoteBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		paramNoteBtn.sethoverImages("toggle-note-160x44-default-hover.png", "toggle-note-160x44-active-hover.png", "toggle-note-160x44-disabled.png");

		veloStartValue.makeVisible(this);
		veloStartValue.setComponentID("veloStartValue");
		veloStartValue.setDisplayTitle(true);
		veloStartValue.setJustificationType(juce::Justification::centred);
		veloStartValue.setTextColour(Theme::Instance().getColour(customOrange));

		/*lenStepStartValue.makeVisible(this);
		lenStepStartValue.setComponentID("lenStepStartValue");
		lenStepStartValue.setDisplayTitle(true);
		lenStepStartValue.setJustificationType(juce::Justification::centred);
		lenStepStartValue.setTextColour(Theme::Instance().getColour(customOrange));

		lenTickStartValue.makeVisible(this);
		lenTickStartValue.setComponentID("lenTickStartValue");
		lenTickStartValue.setDisplayTitle(true);
		lenTickStartValue.setJustificationType(juce::Justification::centred);
		lenTickStartValue.setTextColour(Theme::Instance().getColour(customOrange));*/

		noteStartValue.makeVisible(this);
		noteStartValue.setComponentID("noteStartValue");
		noteStartValue.setDisplayTitle(true);
		noteStartValue.setJustificationType(juce::Justification::centred);
		noteStartValue.setTextColour(Theme::Instance().getColour(customOrange));

		veloEndValue.makeVisible(this);
		veloEndValue.setComponentID("veloEndValue");
		veloEndValue.setDisplayTitle(true);
		veloEndValue.setJustificationType(juce::Justification::centred);
		veloEndValue.setTextColour(Theme::Instance().getColour(customOrange));

		/*lenStepEndValue.makeVisible(this);
		lenStepEndValue.setComponentID("lenStepEndValue");
		lenStepEndValue.setDisplayTitle(true);
		lenStepEndValue.setJustificationType(juce::Justification::centred);
		lenStepEndValue.setTextColour(Theme::Instance().getColour(customOrange));

		lenTickEndValue.makeVisible(this);
		lenTickEndValue.setComponentID("lenTickEndValue");
		lenTickEndValue.setDisplayTitle(true);
		lenTickEndValue.setJustificationType(juce::Justification::centred);
		lenTickEndValue.setTextColour(Theme::Instance().getColour(customOrange));*/

		noteEndValue.makeVisible(this);
		noteEndValue.setComponentID("noteEndValue");
		noteEndValue.setDisplayTitle(true);
		noteEndValue.setJustificationType(juce::Justification::centred);
		noteEndValue.setTextColour(Theme::Instance().getColour(customOrange));

		modeLable.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		paramLable.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());


		sculptOptCtl = IgniteControlOptions::GetAppOptInstance();
		addChildComponent(sculptOptCtl);
		sculptOptCtl->setBounds(xStartOptctl, yStartOptctl, widthOptctl, heightOptctlt);
		sculptOptCtl->addOptCtlListener(this);

		veloStartValue.setcustombounds(true, ui::Rectangle(0, 15, 245, 34), ui::Rectangle(0, 49, 245, 20));
		/*lenStepStartValue.setcustombounds(true, ui::Rectangle(0, 15, 245, 34), ui::Rectangle(0, 49, 245, 20));
		lenTickStartValue.setcustombounds(true, ui::Rectangle(0, 15, 245, 34), ui::Rectangle(0, 49, 245, 20));*/
		noteStartValue.setcustombounds(true, ui::Rectangle(0, 15, 245, 34), ui::Rectangle(0, 49, 245, 20));

		veloEndValue.setcustombounds(true, ui::Rectangle(0, 15, 245, 34), ui::Rectangle(0, 49, 245, 20));
		/*lenStepEndValue.setcustombounds(true, ui::Rectangle(0, 15, 245, 34), ui::Rectangle(0, 49, 245, 20));
		lenTickEndValue.setcustombounds(true, ui::Rectangle(0, 15, 245, 34), ui::Rectangle(0, 49, 245, 20));*/
		noteEndValue.setcustombounds(true, ui::Rectangle(0, 15, 245, 34), ui::Rectangle(0, 49, 245, 20));

		ctlBox2.items.add(FlexItem(sculptRelBtn).withMargin(0).withFlex(1));
		ctlBox2.items.add(FlexItem(sculptAbsBtn).withMargin(0).withFlex(1));
		ctlBox2.items.add(FlexItem(randomRelBtn).withMargin(0).withFlex(1));
		ctlBox2.items.add(FlexItem(randomAbsBtn).withMargin(0).withFlex(1));

		paramBox.items.add(FlexItem(paramAllBtn).withMargin(0).withFlex(1));
		paramBox.items.add(FlexItem(paramVeloBtn).withMargin(0).withFlex(1));
		/*paramBox.items.add(FlexItem(paramLenStepBtn).withMargin(0).withFlex(1));
		paramBox.items.add(FlexItem(paramLenTickBtn).withMargin(0).withFlex(1));*/
		paramBox.items.add(FlexItem(paramNoteBtn).withMargin(0).withFlex(1));

		setSize(getWidth(), getHeight());

		popupPtr = CommonPopUp::getCommonPopupInstance();

		veloStartValue.onValueChanged = [this](int value)
			{
				Component::BailOutChecker checker(this);

				if (checker.shouldBailOut())
					return;

				if (sculptRelBtn.getToggleState())
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptRelativeVelocity, value);
				else if (sculptAbsBtn.getToggleState())
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptAbsoluteVelocity, value);
				else if (randomRelBtn.getToggleState())
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptRandomRelativeVelocityStart, value);
				else if (randomAbsBtn.getToggleState())
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptRandomAbsoluteVelocityStart, value);

				enableControlButton(IgniteControlOptions::SAVE, true);
				enableControlButton(IgniteControlOptions::UNDO, true);
				sculptConfigDataUpdated = true;
			};

		/*lenStepStartValue.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			if (sculptRelBtn.getToggleState())
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptRelativeLengthSteps, value);
			else if (sculptAbsBtn.getToggleState())
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptAbsoluteLengthSteps, value);
			else if (randomRelBtn.getToggleState())
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptRandomRelativeLengthStepStart, value);
			else if (randomAbsBtn.getToggleState())
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptRandomAbsoluteLengthStepStart, value);

			enableControlButton(IgniteControlOptions::SAVE, true);
			enableControlButton(IgniteControlOptions::UNDO, true);
			sculptConfigDataUpdated = true;
		};

		lenTickStartValue.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			if (sculptRelBtn.getToggleState())
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptRelativeLengthTicks, value);
			else if (sculptAbsBtn.getToggleState())
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptAbsoluteLengthTicks, value);
			else if (randomRelBtn.getToggleState())
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptRandomRelativeLengthTickStart, value);
			else if (randomAbsBtn.getToggleState())
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptRandomAbsoluteLengthTickStart, value);

			enableControlButton(IgniteControlOptions::SAVE, true);
			enableControlButton(IgniteControlOptions::UNDO, true);
			sculptConfigDataUpdated = true;
		};*/

		noteStartValue.onValueChanged = [this](int value)
			{
				Component::BailOutChecker checker(this);

				if (checker.shouldBailOut())
					return;

				if (sculptRelBtn.getToggleState())
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptRelativeNote, value);
				else if (sculptAbsBtn.getToggleState())
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptAbsoluteNote, value);
				else if (randomRelBtn.getToggleState())
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptRandomRelativeNoteStart, value);
				else if (randomAbsBtn.getToggleState())
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptRandomAbsoluteNoteStart, value);

				enableControlButton(IgniteControlOptions::SAVE, true);
				enableControlButton(IgniteControlOptions::UNDO, true);
				sculptConfigDataUpdated = true;
			};

		veloEndValue.onValueChanged = [this](int value)
			{
				Component::BailOutChecker checker(this);

				if (checker.shouldBailOut())
					return;

				if (randomAbsBtn.getToggleState())
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptRandomAbsoluteVelocityEnd, value);
				else if (randomRelBtn.getToggleState())
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptRandomRelativeVelocityEnd, value);

				enableControlButton(IgniteControlOptions::SAVE, true);
				enableControlButton(IgniteControlOptions::UNDO, true);
				sculptConfigDataUpdated = true;
			};

		/*lenStepEndValue.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			if (randomAbsBtn.getToggleState())
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptRandomAbsoluteLengthStepEnd, value);
			else if (randomRelBtn.getToggleState())
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptRandomRelativeLengthStepEnd, value);

			enableControlButton(IgniteControlOptions::SAVE, true);
			enableControlButton(IgniteControlOptions::UNDO, true);
			sculptConfigDataUpdated = true;
		};

		lenTickEndValue.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			if (randomAbsBtn.getToggleState())
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptRandomAbsoluteLengthTickEnd, value);
			else if (randomRelBtn.getToggleState())
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptRandomRelativeLengthTickEnd, value);

			enableControlButton(IgniteControlOptions::SAVE, true);
			enableControlButton(IgniteControlOptions::UNDO, true);
			sculptConfigDataUpdated = true;
		};*/

		noteEndValue.onValueChanged = [this](int value)
			{
				Component::BailOutChecker checker(this);

				if (checker.shouldBailOut())
					return;

				if (randomAbsBtn.getToggleState())
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptRandomAbsoluteNoteEnd, value);
				else if (randomRelBtn.getToggleState())
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptRandomRelativeNoteEnd, value);

				enableControlButton(IgniteControlOptions::SAVE, true);
				enableControlButton(IgniteControlOptions::UNDO, true);
				sculptConfigDataUpdated = true;
			};

		veloStartValue.onFocusChanged = [this](bool state)
			{
				repaint();
			};

		/*lenStepStartValue.onFocusChanged = [this](bool state)
		{
			repaint();
		};

		lenTickStartValue.onFocusChanged = [this](bool state)
		{
			repaint();
		};*/

		noteStartValue.onFocusChanged = [this](bool state)
			{
				repaint();
			};

		veloEndValue.onFocusChanged = [this](bool state)
			{
				repaint();
			};

		/*lenStepEndValue.onFocusChanged = [this](bool state)
		{
			repaint();
		};

		lenTickEndValue.onFocusChanged = [this](bool state)
		{
			repaint();
		};*/

		noteEndValue.onFocusChanged = [this](bool state)
			{
				repaint();
			};
	}

	IgniteSculptConfig::~IgniteSculptConfig()
	{
	}

	void IgniteSculptConfig::setParamValueTitle(bool isValueRange)
	{
		if (isValueRange)
		{
			veloStartValue.setTitleText("Velocity Range: Start");
			veloStartValue.setName("Velocity Range: Start");
			/*lenStepStartValue.setTitleText("Length(Step) Range: Start");
			lenStepStartValue.setName("Length(Step) Range: Start");
			lenTickStartValue.setTitleText("Length(Tick) Range: Start");
			lenTickStartValue.setName("Length(Tick) Range: Start");*/
			noteStartValue.setTitleText("Note Range: Start");
			noteStartValue.setName("Note Range: Start");
		}
		else
		{
			veloStartValue.setTitleText("Velocity");
			veloStartValue.setName("Velocity");
			/*lenStepStartValue.setTitleText("Length(Step)");
			lenStepStartValue.setName("Length(Step)");
			lenTickStartValue.setTitleText("Length(Tick)");
			lenTickStartValue.setName("Length(Tick)");*/
			noteStartValue.setTitleText("Note");
			noteStartValue.setName("Note");
		}
	}

	void IgniteSculptConfig::setSculptParams(SculptParameterSelect param, bool state)
	{
		if (state)
			sculpt_params = sculpt_params | (uint8_t)param;

		paramAllBtn.setToggleState(false, dontSendNotification);

		switch (param)
		{
		case SculptParameterSelect::allParams:
			paramAllBtn.setToggleState(state, dontSendNotification);
			paramVeloBtn.setToggleState(false, dontSendNotification);
			/*paramLenStepBtn.setToggleState(false, dontSendNotification);
			paramLenTickBtn.setToggleState(false, dontSendNotification);*/
			paramNoteBtn.setToggleState(false, dontSendNotification);
			state ? (sculpt_params = (uint8_t)SculptParameterSelect::allParams) : (sculpt_params = (uint8_t)SculptParameterSelect::none);
			break;
		case SculptParameterSelect::velocity:
			paramVeloBtn.setToggleState(state, dontSendNotification);
			paramAllBtn.setToggleState(false, dontSendNotification);
			paramNoteBtn.setToggleState(false, dontSendNotification);
			if (!state)
				sculpt_params = sculpt_params & ~(1 << 0);
			break;
			/*case SculptParameterSelect::lengthInSteps:
				paramLenStepBtn.setToggleState(state, dontSendNotification);
				if (!state)
					sculpt_params = sculpt_params & ~(1 << 1);	break;
			case SculptParameterSelect::lengthInTicks:
				paramLenTickBtn.setToggleState(state, dontSendNotification);
				if (!state)
					sculpt_params = sculpt_params & ~(1 << 2);	break;*/
		case SculptParameterSelect::note:
			paramNoteBtn.setToggleState(state, dontSendNotification);
			paramAllBtn.setToggleState(false, dontSendNotification);
			paramVeloBtn.setToggleState(false, dontSendNotification);
			if (!state)
				sculpt_params = sculpt_params & ~(1 << 3); break;
		}
		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptParameterSelection, sculpt_params);
	}

	void IgniteSculptConfig::setSculptMode(sculptMode mode)
	{
		switch (mode)
		{
		case sculptMode::SCULPT_REL:
			valueLable.setText("Parameter Values For Sculpt Relative Mode", dontSendNotification);
			setParamValueTitle(false);
			break;
		case sculptMode::SCULPT_ABS:
			valueLable.setText("Parameter Values For Sculpt Absolute Mode", dontSendNotification);
			setParamValueTitle(false);
			break;
		case sculptMode::RANDOM_REL:
			valueLable.setText("Parameter Values For Random Relative Mode", dontSendNotification);
			setParamValueTitle(true);
			break;
		case sculptMode::RANDOM_ABS:
			valueLable.setText("Parameter Values For Random Absolute Mode", dontSendNotification);
			setParamValueTitle(true);
			break;
		case sculptMode::INVALID:
			valueLable.setText("Parameter Values For Sculpt Mode", dontSendNotification);
			setParamValueTitle(false);
		}
		if (mode == sculptMode::INVALID)
		{
			valueLable.setAlpha(0.3f);
			veloStartValue.setAlpha(0.3f);
			/*lenStepStartValue.setAlpha(0.3f);
			lenTickStartValue.setAlpha(0.3f);*/
			noteStartValue.setAlpha(0.3f);
			veloEndValue.setAlpha(0.3f);
			/*lenStepEndValue.setAlpha(0.3f);*/
			/*lenTickEndValue.setAlpha(0.3f);*/
			noteEndValue.setAlpha(0.3f);
			veloStartValue.setInterceptsMouseClicks(false, false);
			/*lenStepStartValue.setInterceptsMouseClicks(false, false);
			lenTickStartValue.setInterceptsMouseClicks(false, false);*/
			noteStartValue.setInterceptsMouseClicks(false, false);
			veloEndValue.setInterceptsMouseClicks(false, false);
			/*lenStepEndValue.setInterceptsMouseClicks(false, false);
			lenTickEndValue.setInterceptsMouseClicks(false, false);*/
			noteEndValue.setInterceptsMouseClicks(false, false);
		}
		else
		{
			valueLable.setAlpha(1.0f);
			veloStartValue.setAlpha(1.0f);
			/*lenStepStartValue.setAlpha(1.0f);
			lenTickStartValue.setAlpha(1.0f);*/
			noteStartValue.setAlpha(1.0f);
			veloEndValue.setAlpha(1.0f);
			/*lenStepEndValue.setAlpha(1.0f);
			lenTickEndValue.setAlpha(1.0f);*/
			noteEndValue.setAlpha(1.0f);
			veloStartValue.setInterceptsMouseClicks(true, true);
			/*lenStepStartValue.setInterceptsMouseClicks(true, true);
			lenTickStartValue.setInterceptsMouseClicks(true, true);*/
			noteStartValue.setInterceptsMouseClicks(true, true);
			veloEndValue.setInterceptsMouseClicks(true, true);
			/*lenStepEndValue.setInterceptsMouseClicks(true, true);
			lenTickEndValue.setInterceptsMouseClicks(true, true);*/
			noteEndValue.setInterceptsMouseClicks(true, true);

		}
	}

	void IgniteSculptConfig::paint(juce::Graphics& g)
	{
		Image Draw = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("bg-sculpt-mode.png"));

		g.setColour(Theme::Instance().getColour(neutralBlack));
		g.fillAll();

		MenuMode::GetMenuModeInstance()->setHeader("Pattern Sculpt Configuration");

		Image defImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("item-bg-midi-245x80-default.png"));
		Image defOver = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("item-bg-midi-245x80-default-hover.png"));

		Draw = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("bg-params-toggle.png"));
		g.drawImage(Draw, ui::Rectangle<float>{ 10, 171, 1004, 74 });

		if (randomRelBtn.getToggleState() || randomAbsBtn.getToggleState())
		{
			Draw = veloStartValue.getFocusState() ? defOver : defImage;
			g.drawImage(Draw, ui::Rectangle<float>{10, 296, 245, 80});

			Draw = veloEndValue.getFocusState() ? defOver : defImage;
			g.drawImage(Draw, ui::Rectangle<float>{263.5, 296, 245, 80});

			Draw = noteStartValue.getFocusState() ? defOver : defImage;
			g.drawImage(Draw, ui::Rectangle<float>{517, 296, 245, 80});

			Draw = noteEndValue.getFocusState() ? defOver : defImage;
			g.drawImage(Draw, ui::Rectangle<float>{770.5, 296, 245, 80});
		}
		else
		{
			Draw = veloStartValue.getFocusState() ? defOver : defImage;
			g.drawImage(Draw, ui::Rectangle<float>{10, 296, 245, 80});

			Draw = noteStartValue.getFocusState() ? defOver : defImage;
			g.drawImage(Draw, ui::Rectangle<float>{263.5, 296, 245, 80});
		}
	}

	uint8_t IgniteSculptConfig::getSculptParamConfig()
	{
		std::vector<IgniteParamList> sculptParams;
		IgniteParamList params;

		params.param = (paramId_t)SettingsSculptModeCnfgParam::sculptParameterSelection;
		sculptParams.push_back(params);

		sculptParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, sculptParams);
		return sculptParams[0].MsgValue.get< int8>();
	}

	void IgniteSculptConfig::loadSculptParams()
	{
		std::vector<IgniteParamList> sculptParams;
		IgniteParamList params;

		params.param = (paramId_t)SettingsSculptModeCnfgParam::sculptParameterSelection;
		sculptParams.push_back(params);

		sculptParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, sculptParams);
		sculpt_params = sculptParams[0].MsgValue.get< int8>();

		paramAllBtn.setToggleState(false, dontSendNotification);
		paramVeloBtn.setToggleState(false, dontSendNotification);
		/*paramLenStepBtn.setToggleState(false, dontSendNotification);
		paramLenTickBtn.setToggleState(false, dontSendNotification);*/
		paramNoteBtn.setToggleState(false, dontSendNotification);

		if (sculpt_params == (uint8_t)SculptParameterSelect::allParams)
			paramAllBtn.setToggleState(true, dontSendNotification);
		else {
			if (sculpt_params & (uint8_t)SculptParameterSelect::velocity)
				paramVeloBtn.setToggleState(true, dontSendNotification);
			/*if (sculpt_params & (uint8_t)SculptParameterSelect::lengthInSteps)
				paramLenStepBtn.setToggleState(true, dontSendNotification);
			if (sculpt_params & (uint8_t)SculptParameterSelect::lengthInTicks)
				paramLenTickBtn.setToggleState(true, dontSendNotification);*/
			if (sculpt_params & (uint8_t)SculptParameterSelect::note)
				paramNoteBtn.setToggleState(true, dontSendNotification);
		}
	}

	IgniteSculptConfig::sculptMode IgniteSculptConfig::getSculptMode()
	{
		std::vector<IgniteParamList> sculptParams;
		IgniteParamList params;

		sculptRelBtn.setToggleState(false, dontSendNotification);
		sculptAbsBtn.setToggleState(false, dontSendNotification);
		randomAbsBtn.setToggleState(false, dontSendNotification);
		randomRelBtn.setToggleState(false, dontSendNotification);

		params.param = (paramId_t)SettingsSculptModeCnfgParam::sculptMode;
		sculptParams.push_back(params);

		sculptParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, sculptParams);
		auto mode = sculptParams[0].MsgValue.get< int8>();

		switch (mode)
		{
		case static_cast<int8> (SculptMode::relative):
			sculptRelBtn.setToggleState(true, dontSendNotification);
			setSculptMode(sculptMode::SCULPT_REL);
			return sculptMode::SCULPT_REL;
			break;

		case  static_cast<int8> (SculptMode::absolute):
			sculptAbsBtn.setToggleState(true, dontSendNotification);
			setSculptMode(sculptMode::SCULPT_ABS);
			return sculptMode::SCULPT_ABS;
			break;

		case  static_cast<int8> (SculptMode::randomRelative):
			randomRelBtn.setToggleState(true, dontSendNotification);
			setSculptMode(sculptMode::RANDOM_REL);
			return sculptMode::RANDOM_REL;
			break;

		case  static_cast<int8> (SculptMode::randomAbsolute):
			randomAbsBtn.setToggleState(true, dontSendNotification);
			setSculptMode(sculptMode::RANDOM_ABS);
			return sculptMode::RANDOM_ABS;
			break;
		}

		setSculptMode(sculptMode::INVALID);
		return sculptMode::INVALID;
	}

	void IgniteSculptConfig::updateData(sculptMode mode)
	{
		std::vector<IgniteParamList> sculptValueParams;
		IgniteParamList valueParams;

		switch (mode)
		{
		case sculptMode::SCULPT_REL:
			sculptValueParams.clear();
			valueParams.param = (paramId_t)SettingsSculptModeCnfgParam::sculptRelativeVelocity;
			sculptValueParams.push_back(valueParams);

			/*valueParams.param = (paramId_t)SettingsSculptModeCnfgParam::sculptRelativeLengthSteps;
			sculptValueParams.push_back(valueParams);

			valueParams.param = (paramId_t)SettingsSculptModeCnfgParam::sculptRelativeLengthTicks;
			sculptValueParams.push_back(valueParams);*/

			valueParams.param = (paramId_t)SettingsSculptModeCnfgParam::sculptRelativeNote;
			sculptValueParams.push_back(valueParams);

			sculptValueParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, sculptValueParams);

			for (auto& sculpt_rel_param_id : sculptValueParams)
			{
				switch (sculpt_rel_param_id.param)
				{
				case (paramId_t)SettingsSculptModeCnfgParam::sculptRelativeVelocity:
					veloStartValue.setText(String(sculpt_rel_param_id.MsgValue.get< int8_t >()), dontSendNotification);
					veloStartValue.setValue(sculpt_rel_param_id.MsgValue.get< int8_t >());
					break;

					/*case (paramId_t)SettingsSculptModeCnfgParam::sculptRelativeLengthSteps:
						lenStepStartValue.setText(String(sculpt_rel_param_id.MsgValue.get< int8_t >()), dontSendNotification);
						lenStepStartValue.setValue(sculpt_rel_param_id.MsgValue.get< int8_t >());
						break;

					case (paramId_t)SettingsSculptModeCnfgParam::sculptRelativeLengthTicks:
						lenTickStartValue.setText(String(sculpt_rel_param_id.MsgValue.get< int8_t >()), dontSendNotification);
						lenTickStartValue.setValue(sculpt_rel_param_id.MsgValue.get< int8_t >());
						break;*/

				case (paramId_t)SettingsSculptModeCnfgParam::sculptRelativeNote:
					noteStartValue.setText(String(sculpt_rel_param_id.MsgValue.get< int8_t >()), dontSendNotification);
					noteStartValue.setValue(sculpt_rel_param_id.MsgValue.get< int8_t >());
					break;
				}
			}
			break;

		case sculptMode::SCULPT_ABS:
			sculptValueParams.clear();
			valueParams.param = (paramId_t)SettingsSculptModeCnfgParam::sculptAbsoluteVelocity;
			sculptValueParams.push_back(valueParams);
			/*valueParams.param = (paramId_t)SettingsSculptModeCnfgParam::sculptAbsoluteLengthSteps;
			sculptValueParams.push_back(valueParams);
			valueParams.param = (paramId_t)SettingsSculptModeCnfgParam::sculptAbsoluteLengthTicks;
			sculptValueParams.push_back(valueParams);*/
			valueParams.param = (paramId_t)SettingsSculptModeCnfgParam::sculptAbsoluteNote;
			sculptValueParams.push_back(valueParams);

			sculptValueParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, sculptValueParams);
			for (auto& sculpt_rel_param_id : sculptValueParams)
			{
				switch (sculpt_rel_param_id.param)
				{
				case (paramId_t)SettingsSculptModeCnfgParam::sculptAbsoluteVelocity:
					veloStartValue.setText(String(sculpt_rel_param_id.MsgValue.get< int8_t >()), dontSendNotification);
					veloStartValue.setValue(sculpt_rel_param_id.MsgValue.get< int8_t >());
					break;
					/*case (paramId_t)SettingsSculptModeCnfgParam::sculptAbsoluteLengthSteps:
						lenStepStartValue.setText(String(sculpt_rel_param_id.MsgValue.get< int8_t >()), dontSendNotification);
						break;
					case (paramId_t)SettingsSculptModeCnfgParam::sculptAbsoluteLengthTicks:
						lenTickStartValue.setText(String(sculpt_rel_param_id.MsgValue.get< int8_t >()), dontSendNotification);
						break;*/
				case (paramId_t)SettingsSculptModeCnfgParam::sculptAbsoluteNote:
					noteStartValue.setText(String(sculpt_rel_param_id.MsgValue.get< int8_t >()), dontSendNotification);
					break;
				}
			}
			break;

		case sculptMode::RANDOM_REL:
			sculptValueParams.clear();
			valueParams.param = (paramId_t)SettingsSculptModeCnfgParam::sculptRandomRelativeVelocityStart;
			sculptValueParams.push_back(valueParams);
			valueParams.param = (paramId_t)SettingsSculptModeCnfgParam::sculptRandomRelativeVelocityEnd;
			sculptValueParams.push_back(valueParams);
			/*valueParams.param = (paramId_t)SettingsSculptModeCnfgParam::sculptRandomRelativeLengthStepStart;
			sculptValueParams.push_back(valueParams);
			valueParams.param = (paramId_t)SettingsSculptModeCnfgParam::sculptRandomRelativeLengthStepEnd;
			sculptValueParams.push_back(valueParams);
			valueParams.param = (paramId_t)SettingsSculptModeCnfgParam::sculptRandomRelativeLengthTickStart;
			sculptValueParams.push_back(valueParams);
			valueParams.param = (paramId_t)SettingsSculptModeCnfgParam::sculptRandomRelativeLengthTickEnd;*/
			sculptValueParams.push_back(valueParams);
			valueParams.param = (paramId_t)SettingsSculptModeCnfgParam::sculptRandomRelativeNoteStart;
			sculptValueParams.push_back(valueParams);
			valueParams.param = (paramId_t)SettingsSculptModeCnfgParam::sculptRandomRelativeNoteEnd;
			sculptValueParams.push_back(valueParams);
			sculptValueParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, sculptValueParams);
			for (auto& sculpt_rel_param_id : sculptValueParams)
			{
				switch (sculpt_rel_param_id.param)
				{
				case (paramId_t)SettingsSculptModeCnfgParam::sculptRandomRelativeVelocityStart:
					veloStartValue.setText(String(sculpt_rel_param_id.MsgValue.get< int8_t >()), dontSendNotification);
					break;
				case (paramId_t)SettingsSculptModeCnfgParam::sculptRandomRelativeVelocityEnd:
					veloEndValue.setText(String(sculpt_rel_param_id.MsgValue.get< int8_t >()), dontSendNotification);
					break;
					/*case (paramId_t)SettingsSculptModeCnfgParam::sculptRandomRelativeLengthStepStart:
						lenStepStartValue.setText(String(sculpt_rel_param_id.MsgValue.get< int8_t >()), dontSendNotification);
						break;
					case (paramId_t)SettingsSculptModeCnfgParam::sculptRandomRelativeLengthStepEnd:
						lenStepEndValue.setText(String(sculpt_rel_param_id.MsgValue.get< int8_t >()), dontSendNotification);
						break;
					case (paramId_t)SettingsSculptModeCnfgParam::sculptRandomRelativeLengthTickStart:
						lenTickStartValue.setText(String(sculpt_rel_param_id.MsgValue.get< int8_t >()), dontSendNotification);
						break;
					case (paramId_t)SettingsSculptModeCnfgParam::sculptRandomRelativeLengthTickEnd:
						lenTickEndValue.setText(String(sculpt_rel_param_id.MsgValue.get< int8_t >()), dontSendNotification);
						break;*/
				case (paramId_t)SettingsSculptModeCnfgParam::sculptRandomRelativeNoteStart:
					noteStartValue.setText(String(sculpt_rel_param_id.MsgValue.get< int8_t >()), dontSendNotification);
					break;
				case (paramId_t)SettingsSculptModeCnfgParam::sculptRandomRelativeNoteEnd:
					noteEndValue.setText(String(sculpt_rel_param_id.MsgValue.get< int8_t >()), dontSendNotification);
					break;
				}
			}
			break;
		case sculptMode::RANDOM_ABS:
			sculptValueParams.clear();

			valueParams.param = (paramId_t)SettingsSculptModeCnfgParam::sculptRandomAbsoluteVelocityStart;
			sculptValueParams.push_back(valueParams);

			valueParams.param = (paramId_t)SettingsSculptModeCnfgParam::sculptRandomAbsoluteVelocityEnd;
			sculptValueParams.push_back(valueParams);

			/*valueParams.param = (paramId_t)SettingsSculptModeCnfgParam::sculptRandomAbsoluteLengthStepStart;
			sculptValueParams.push_back(valueParams);

			valueParams.param = (paramId_t)SettingsSculptModeCnfgParam::sculptRandomAbsoluteLengthStepEnd;
			sculptValueParams.push_back(valueParams);

			valueParams.param = (paramId_t)SettingsSculptModeCnfgParam::sculptRandomAbsoluteLengthTickStart;
			sculptValueParams.push_back(valueParams);

			valueParams.param = (paramId_t)SettingsSculptModeCnfgParam::sculptRandomAbsoluteLengthTickEnd;*/
			sculptValueParams.push_back(valueParams);

			valueParams.param = (paramId_t)SettingsSculptModeCnfgParam::sculptRandomAbsoluteNoteStart;
			sculptValueParams.push_back(valueParams);

			valueParams.param = (paramId_t)SettingsSculptModeCnfgParam::sculptRandomAbsoluteNoteEnd;
			sculptValueParams.push_back(valueParams);

			sculptValueParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, sculptValueParams);

			for (auto& sculpt_rel_param_id : sculptValueParams)
			{
				switch (sculpt_rel_param_id.param)
				{
				case (paramId_t)SettingsSculptModeCnfgParam::sculptRandomAbsoluteVelocityStart:
					veloStartValue.setText(String(sculpt_rel_param_id.MsgValue.get< int8_t >()), dontSendNotification);
					break;

				case (paramId_t)SettingsSculptModeCnfgParam::sculptRandomAbsoluteVelocityEnd:
					veloEndValue.setText(String(sculpt_rel_param_id.MsgValue.get< int8_t >()), dontSendNotification);
					break;

					/*case (paramId_t)SettingsSculptModeCnfgParam::sculptRandomAbsoluteLengthStepStart:
						lenStepStartValue.setText(String(sculpt_rel_param_id.MsgValue.get< int8_t >()), dontSendNotification);
						break;

					case (paramId_t)SettingsSculptModeCnfgParam::sculptRandomAbsoluteLengthStepEnd:
						lenStepEndValue.setText(String(sculpt_rel_param_id.MsgValue.get< int8_t >()), dontSendNotification);
						break;

					case (paramId_t)SettingsSculptModeCnfgParam::sculptRandomAbsoluteLengthTickStart:
						lenTickStartValue.setText(String(sculpt_rel_param_id.MsgValue.get< int8_t >()), dontSendNotification);
						break;

					case (paramId_t)SettingsSculptModeCnfgParam::sculptRandomAbsoluteLengthTickEnd:
						lenTickEndValue.setText(String(sculpt_rel_param_id.MsgValue.get< int8_t >()), dontSendNotification);
						break;*/

				case (paramId_t)SettingsSculptModeCnfgParam::sculptRandomAbsoluteNoteStart:
					noteStartValue.setText(String(sculpt_rel_param_id.MsgValue.get< int8_t >()), dontSendNotification);
					break;

				case (paramId_t)SettingsSculptModeCnfgParam::sculptRandomAbsoluteNoteEnd:
					noteEndValue.setText(String(sculpt_rel_param_id.MsgValue.get< int8_t >()), dontSendNotification);
					break;
				}
			}
			break;
		}
		resized();
	}

	void IgniteSculptConfig::loadDataFromEngine()
	{
		updateData(getSculptMode());
		loadSculptParams();
	}

	void IgniteSculptConfig::resized()
	{
		modeLable.setBounds(20, 66, 984, 30);
		paramLable.setBounds(20, 195, 190, 30);
		ctlBox1.performLayout(ui::Rectangle{ 10, 60, 1000,40 });
		ctlBox2.performLayout(ui::Rectangle{ 10, 111, 1004, 50 });
		valueBoxTitle.performLayout(Rectangle(10, 260, 1000, 40));
		veloStartValue.setVisible(false);
		veloEndValue.setVisible(false);
		noteStartValue.setVisible(false);
		noteEndValue.setVisible(false);

		if (randomRelBtn.getToggleState() || randomAbsBtn.getToggleState())
		{
			veloStartValue.setVisible(true);
			veloEndValue.setVisible(true);
			noteStartValue.setVisible(true);
			noteEndValue.setVisible(true);
			veloStartValue.setBounds(10, 296, 245, 80);
			veloEndValue.setBounds(263, 296, 245, 80);
			noteStartValue.setBounds(517, 296, 245, 80);
			noteEndValue.setBounds(770, 296, 245, 80);
		}
		else
		{
			veloStartValue.setVisible(true);
			noteStartValue.setVisible(true);
			veloStartValue.setBounds(10, 296, 245, 80);
			noteStartValue.setBounds(263, 296, 245, 80);
		}
		valueLable.setBounds(20, 250, 984, 30);
		paramBox.performLayout(Rectangle(178, 189, 826, 44));
	}

	void IgniteSculptConfig::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		int8 mode = static_cast <int8_t> (SculptMode::none);

		if (buttonThatWasClicked == &sculptRelBtn)
		{
			KeyFocusedItem = SculptMenuViewItemID::SCULPT_REL;
			if (sculptRelBtn.getToggleState())
			{
				setSculptMode(sculptMode::SCULPT_REL);
				sculptAbsBtn.setToggleState(false, dontSendNotification);
				randomRelBtn.setToggleState(false, dontSendNotification);
				randomAbsBtn.setToggleState(false, dontSendNotification);
				updateData(sculptMode::SCULPT_REL);
				mode = static_cast <int8_t> (SculptMode::relative);
			}
			else
				setSculptMode(sculptMode::INVALID);
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptMode, mode);
		}
		else if (buttonThatWasClicked == &sculptAbsBtn)
		{
			KeyFocusedItem = SculptMenuViewItemID::SCULPT_ABS;
			if (sculptAbsBtn.getToggleState())
			{
				setSculptMode(sculptMode::SCULPT_ABS);
				sculptRelBtn.setToggleState(false, dontSendNotification);
				randomRelBtn.setToggleState(false, dontSendNotification);
				randomAbsBtn.setToggleState(false, dontSendNotification);
				updateData(sculptMode::SCULPT_ABS);
				mode = static_cast <int8_t> (SculptMode::absolute);
			}
			else
				setSculptMode(sculptMode::INVALID);

			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptMode, mode);
		}
		else if (buttonThatWasClicked == &randomRelBtn)
		{
			KeyFocusedItem = SculptMenuViewItemID::RANDOM_REL;
			if (randomRelBtn.getToggleState())
			{
				setSculptMode(sculptMode::RANDOM_REL);
				sculptRelBtn.setToggleState(false, dontSendNotification);
				sculptAbsBtn.setToggleState(false, dontSendNotification);
				randomAbsBtn.setToggleState(false, dontSendNotification);
				updateData(sculptMode::RANDOM_REL);
				mode = static_cast <int8_t> (SculptMode::randomRelative);
			}
			else
				setSculptMode(sculptMode::INVALID);

			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptMode, mode);
		}
		else if (buttonThatWasClicked == &randomAbsBtn)
		{
			KeyFocusedItem = SculptMenuViewItemID::RANDOM_ABS;
			if (randomAbsBtn.getToggleState())
			{
				setSculptMode(sculptMode::RANDOM_ABS);
				sculptRelBtn.setToggleState(false, dontSendNotification);
				sculptAbsBtn.setToggleState(false, dontSendNotification);
				randomRelBtn.setToggleState(false, dontSendNotification);
				updateData(sculptMode::RANDOM_ABS);
				mode = static_cast <int8_t> (SculptMode::randomAbsolute);
			}
			else
				setSculptMode(sculptMode::INVALID);

			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::sculptMode, mode);
		}
		else if (buttonThatWasClicked == &paramAllBtn)
		{
			KeyFocusedItem = SculptMenuViewItemID::SCULPT_ALL_PARAM;
			setSculptParams(SculptParameterSelect::allParams, paramAllBtn.getToggleState());
		}
		else if (buttonThatWasClicked == &paramVeloBtn)
		{
			KeyFocusedItem = SculptMenuViewItemID::SCULPT_VELO_PARAM;
			setSculptParams(SculptParameterSelect::velocity, paramVeloBtn.getToggleState());
		}
		/*else if (buttonThatWasClicked == &paramLenStepBtn)
		{
			KeyFocusedItem = SculptMenuViewItemID::SCULPT_LEN_ST_PARAM;
			setSculptParams(SculptParameterSelect::lengthInSteps, paramLenStepBtn.getToggleState());
		}
		else if (buttonThatWasClicked == &paramLenTickBtn)
		{
			KeyFocusedItem = SculptMenuViewItemID::SCULPT_LEN_TK_PARAM;
			setSculptParams(SculptParameterSelect::lengthInTicks, paramLenTickBtn.getToggleState());
		}*/
		else if (buttonThatWasClicked == &paramNoteBtn)
		{
			KeyFocusedItem = SculptMenuViewItemID::SCULPT_NOTE_PARAM;
			setSculptParams(SculptParameterSelect::note, paramNoteBtn.getToggleState());
		}

		enableControlButton(IgniteControlOptions::SAVE, true);
		enableControlButton(IgniteControlOptions::UNDO, true);
		sculptConfigDataUpdated = true;
	}

	void IgniteSculptConfig::onOptCtlButtonClicked(IgniteControlOptions::eKey option)
	{
		if (this->isVisible())
		{
			if (option == IgniteControlOptions::SAVE)
			{
				if (popupPtr->isDialogOpen.get() != true)
				{
					popupPtr->close();
					popupPtr->setPopUpPropories("Save ", 604, 290);
					popupPtr->setbtnsize(265, 44);
					popupPtr->setInfoText(String("Save Sculpt Configuration edits ? "));
					popupPtr->addImageButton("no", "btn-secondary-no-267x44-default.png", "btn-secondary-no-267x44-default-hover.png", 2);
					popupPtr->addImageButton("yes", "btn-yes-267x44-default.png", "btn-yes-267x44-default-hover.png", 1);
					popupPtr->popupType = POPUP_WITHOKCANCEL;
					popupPtr->isCloseButtonVisible(false);
					popupPtr->show();
					popupPtr->onSelectionChanged = [this](int r)
						{
							if (r == 1)
							{
								_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::settingSculptConfigSave, 0);
								enableControlButton(IgniteControlOptions::SAVE, false);
								enableControlButton(IgniteControlOptions::UNDO, false);
								sculptConfigDataUpdated = false;
							}
							if (auto dw = getCurrentlyModalComponent())
								dw->exitModalState(0);
						};
				}
			}
			else if (option == IgniteControlOptions::UNDO)
			{
				if (sculptConfigDataUpdated)
				{
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, (paramId_t)SettingsSculptModeCnfgParam::paramUndoCmd, 0);

					std::vector<IgniteParamList> sculptParamList;
					IgniteParamList params;

					params.param = (paramId_t)SettingsSculptModeCnfgParam::paramUndoListCmd;
					sculptParamList.push_back(params);
					sculptParamList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsSculptModeCnfg, sculptParamList);
					if (sculptParamList.size() == 1)
					{
						sculptConfigDataUpdated = false;
						enableControlButton(IgniteControlOptions::SAVE, false);
						enableControlButton(IgniteControlOptions::UNDO, false);
					}
					loadDataFromEngine();
				}
			}
		}
	}

	int IgniteSculptConfig::isEditing()
	{
		int index = 0;

		veloStartValue.IsEditing() ? index = 8 : 0;
		/*lenStepStartValue.IsEditing() ? index = 11 : 0;
		lenTickStartValue.IsEditing() ? index = 12 : 0;*/
		if (sculptRelBtn.getToggleState() || sculptAbsBtn.getToggleState())
		{
			noteStartValue.IsEditing() ? index = 9 : 0;
		}
		else if (randomRelBtn.getToggleState() || randomAbsBtn.getToggleState())
		{
			veloEndValue.IsEditing() ? index = 9 : 0;
			noteStartValue.IsEditing() ? index = 10 : 0;
		}
		/*lenStepEndValue.IsEditing() ? index = 15 : 0;
		lenTickEndValue.IsEditing() ? index = 16 : 0;*/
		noteEndValue.IsEditing() ? index = 11 : 0;

		return index;
	}

	bool IgniteSculptConfig::PannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool setfocus = true;
		int editItem = SculptMenuViewItemID::NO_FOCUS;

		if (popupPtr != nullptr && popupPtr->IsEditing())
			return popupPtr->FPKeyHandler(true, param, KeyValue);

		if ((FrontPannelParam)param == FrontPannelParam::paramKey_PAGESHIFT)
		{
			PannelSendKey(false, param, KeyValue);
			if (optionHandlerFocus == SCULPTCONFIG_DETAIL)
			{
				optionHandlerFocus = SCULPTCONFIG_OPTION;
			}
			else
			{
				optionHandlerFocus = SCULPTCONFIG_DETAIL;
			}
			PannelSendKey(true, param, KeyValue);
			return true;
		}

		if (optionHandlerFocus == SCULPTCONFIG_DETAIL)
		{

			if (KeyFocusedItem == SculptMenuViewItemID::NO_FOCUS)
			{
				/*1st key after Page visible */
				KeyFocusedItem = SculptMenuViewItemID::SCULPT_REL;

				if (FrontPannelParam::paramKey_RETURN_NAV == (FrontPannelParam)param)
				{
					AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::PATTERN_WINDOW);
					return true;
				}
			}
			else
			{
				editItem = isEditing();
				if (editItem)
				{
					if (KeyFocusedItem != editItem)
					{
						PannelSendKey(false, param, KeyValue);
						KeyFocusedItem = editItem;
					}
					setfocus = true;
				}
				else
				{
					PannelSendKey(false, param, KeyValue); // clear last Focus
					switch ((FrontPannelParam)param)
					{
					case FrontPannelParam::paramKey_RMOVELEFT:
						KeyFocusedItem = (KeyFocusedItem + 1 >= SculptMenuViewItemID::FOCUS_MAX ? (SculptMenuViewItemID::FOCUS_MAX) : KeyFocusedItem + 1);
						break;
					case FrontPannelParam::paramKey_RMOVERIGHT:
						KeyFocusedItem = (KeyFocusedItem - 1 <= SculptMenuViewItemID::NO_FOCUS ? (SculptMenuViewItemID::NO_FOCUS + 1) : KeyFocusedItem - 1);
						break;
					case FrontPannelParam::paramKey_RETURN_NAV:
						AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::PATTERN_WINDOW);
						break;
					}
				}
			}
		}
		else
		{
			PannelSendKey(false, param, KeyValue); // clear last Focus
			switch ((FrontPannelParam)param)
			{
			case FrontPannelParam::paramKey_RMOVELEFT:
				optFocusedItem = (optFocusedItem + 1 >= sculptOptionsViewItemID::OP_FOCUS_MAX ? (sculptOptionsViewItemID::OP_FOCUS_MAX) : optFocusedItem + 1);
				break;
			case FrontPannelParam::paramKey_RMOVERIGHT:
				optFocusedItem = (optFocusedItem - 1 <= sculptOptionsViewItemID::OP_NO_FOCUS ? (sculptOptionsViewItemID::OP_NO_FOCUS + 1) : optFocusedItem - 1);
				break;
			case FrontPannelParam::paramKey_RETURN_NAV:
				AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::PATTERN_WINDOW);
				break;
			}
		}
		if (setfocus)
		{
			PannelSendKey(true, param, KeyValue);
		}
		return true;
	}

	void IgniteSculptConfig::PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		bool state = false;

		if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT && (KeyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusReleased))
			return;

		if (optionHandlerFocus == SCULPTCONFIG_DETAIL)
		{
			switch (SculptMenuView[KeyFocusedItem])
			{
			case SCULPT_REL:
				sculptRelBtn.FPKeyHandler(isFocuse, param, 0);
				break;
			case SCULPT_ABS:
				sculptAbsBtn.FPKeyHandler(isFocuse, param, 0);
				break;
			case RANDOM_REL:
				randomRelBtn.FPKeyHandler(isFocuse, param, 0);
				break;
			case RANDOM_ABS:
				randomAbsBtn.FPKeyHandler(isFocuse, param, 0);
				break;
			case SCULPT_ALL_PARAM:
				paramAllBtn.FPKeyHandler(isFocuse, param, 0);
				break;
			case SCULPT_VELO_PARAM:
				paramVeloBtn.FPKeyHandler(isFocuse, param, 0);
				break;
				/*case SCULPT_LEN_ST_PARAM:
					paramLenStepBtn.FPKeyHandler(isFocuse, param, KeyValue);
					if ((paramId_t)param == (paramId_t)FrontPannelParam::paramKey_RSELECT && isFocuse)
					{
						buttonClicked(&paramLenStepBtn);
					}
					break;
				case SCULPT_LEN_TK_PARAM:
					paramLenTickBtn.FPKeyHandler(isFocuse, param, KeyValue);
					if ((paramId_t)param == (paramId_t)FrontPannelParam::paramKey_RSELECT && isFocuse)
					{
						buttonClicked(&paramLenTickBtn);
					}
					break;*/
			case SCULPT_NOTE_PARAM:
				paramNoteBtn.FPKeyHandler(isFocuse, param, 0);
				break;
			case SCULPT_VELO:
				if (veloStartValue.getAlpha() == 1.0f)
					veloStartValue.FPKeyHandler(isFocuse, param, KeyValue);
				break;
				/*case SCULPT_LEN_ST:
					if (lenStepStartValue.getAlpha() == 1.0f)
						lenStepStartValue.FPKeyHandler(isFocuse, param, KeyValue);
					break;
				case SCULPT_LEN_TK:
					if (lenTickStartValue.getAlpha() == 1.0f)
						lenTickStartValue.FPKeyHandler(isFocuse, param, KeyValue);
					break;*/
			case SCULPT_DELAY:
				if (sculptRelBtn.getToggleState() || sculptAbsBtn.getToggleState())
				{
					if (noteStartValue.getAlpha() == 1.0f)
						noteStartValue.FPKeyHandler(isFocuse, param, KeyValue);
				}
				else if (randomRelBtn.getToggleState() || randomAbsBtn.getToggleState())
				{
					if (veloEndValue.getAlpha() == 1.0f)
						veloEndValue.FPKeyHandler(isFocuse, param, KeyValue);
				}
				break;
			case RANDOM_VELO:
				if (randomRelBtn.getToggleState() || randomAbsBtn.getToggleState())
				{
					if (noteStartValue.getAlpha() == 1.0f)
						noteStartValue.FPKeyHandler(isFocuse, param, KeyValue);
				}
				break;
				/*case RANDOM_LEN_ST:
					if (lenStepEndValue.getAlpha() == 1.0f)
						lenStepEndValue.FPKeyHandler(isFocuse, param, KeyValue);
					break;
				case RANDOM_LEN_TK:
					if (lenTickEndValue.getAlpha() == 1.0f)
						lenTickEndValue.FPKeyHandler(isFocuse, param, KeyValue);
					break;*/
			case RANDOM_DELAY:
				if (randomRelBtn.getToggleState() || randomAbsBtn.getToggleState())
				{
					if (noteEndValue.getAlpha() == 1.0f)
						noteEndValue.FPKeyHandler(isFocuse, param, KeyValue);
				}
				break;
			default:
				break;
			}
		}
		else
		{
			auto sculptCompPtr = IgnitePatternConfig::getAppPatternConfigInstance();

			switch (sculptOptionsMenuView[optFocusedItem])
			{
			case OPT_UNDO:
				state = sculptCompPtr->_pPatternOptCtl->PannelKeyHandler(IgniteControlOptions::eKey::UNDO, isFocuse, param, KeyValue);
				break;
			case OPT_PATSTEP:
				state = sculptCompPtr->_pPatternOptCtl->PannelKeyHandler(IgniteControlOptions::eKey::PATSTEP, isFocuse, param, KeyValue);
				break;
			case OPT_PATBAR:
				state = sculptCompPtr->_pPatternOptCtl->PannelKeyHandler(IgniteControlOptions::eKey::PATBAR, isFocuse, param, KeyValue);
				break;
			case OPT_PATGRID:
				state = sculptCompPtr->_pPatternOptCtl->PannelKeyHandler(IgniteControlOptions::eKey::PATGRID, isFocuse, param, KeyValue);
				break;

			}

			if (state == false)
			{
				optFocusedItem++;
				if (optFocusedItem > OP_FOCUS_MAX)
					optFocusedItem = OPT_UNDO;
				PannelSendKey(isFocuse, param, KeyValue);
			}
		}
		repaint();
	}
};
