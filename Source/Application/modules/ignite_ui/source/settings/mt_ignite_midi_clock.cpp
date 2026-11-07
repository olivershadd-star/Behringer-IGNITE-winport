/*
 * Copyright (c) - 2023 - MUSIC Tribe, MY.
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
	//   Class: IgniteMidiClkSetting
	////////////////////////////////////////////////
	IgniteMidiClkSetting::IgniteMidiClkSetting()
	{
		clockInbtn.makeVisibleAddListnerAndAddRadioGroup(this, 1355);
		clockOutbtn.makeVisibleAddListnerAndAddRadioGroup(this, 1355);
		clockInbtn.setToggleState(true, dontSendNotification);
		clockInbtn.setBounds(10, 66, 500, 50);
		clockOutbtn.setBounds(514, 66, 500, 50);
		clockInbtn.setToggleState(true, sendNotification);
		clockInbtn.sethoverImages("btn-clockin-settings-default-hover.png", "btn-clockin-settings-active-hover.png", "");
		clockOutbtn.sethoverImages("btn-clockout-settings-default-hover.png", "btn-clockout-settings-active-hover.png", "");
		clockOutbtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		clockInbtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());

		modeLable.setFont(juce::Font(font_15, juce::Font::plain).withTypefaceStyle("Regular"));
		modeLable.setJustificationType(juce::Justification::centred);
		modeLable.setEditable(false, false, false);
		modeLable.setColour(juce::Label::backgroundColourId, juce::Colour(ui::CommonColorID::neutralGrey4));
		modeLable.setColour(juce::Label::outlineColourId, Colours::white);
		modeLable.makeVisible(this);

		midiPortLable.setFont(juce::Font(font_15, juce::Font::plain).withTypefaceStyle("Regular"));
		midiPortLable.setJustificationType(juce::Justification::centred);
		midiPortLable.setEditable(false, false, false);
		midiPortLable.setColour(juce::Label::backgroundColourId, juce::Colour(ui::CommonColorID::neutralGrey4));
		midiPortLable.setColour(juce::Label::outlineColourId, Colours::white);
		midiPortLable.makeVisible(this);

		usbPortLable.setFont(juce::Font(font_15, juce::Font::plain).withTypefaceStyle("Regular"));
		usbPortLable.setJustificationType(juce::Justification::centred);
		usbPortLable.setEditable(false, false, false);
		usbPortLable.setColour(juce::Label::backgroundColourId, juce::Colour(ui::CommonColorID::neutralGrey4));
		usbPortLable.setColour(juce::Label::outlineColourId, Colours::white);
		usbPortLable.makeVisible(this);

		usbHPortLable.setFont(juce::Font(font_15, juce::Font::plain).withTypefaceStyle("Regular"));
		usbHPortLable.setJustificationType(juce::Justification::centred);
		usbHPortLable.setEditable(false, false, false);
		usbHPortLable.setColour(juce::Label::backgroundColourId, juce::Colour(ui::CommonColorID::neutralGrey4));
		usbHPortLable.setColour(juce::Label::outlineColourId, Colours::white);
		usbHPortLable.makeVisible(this);

		syncPortLable.setFont(juce::Font(font_15, juce::Font::plain).withTypefaceStyle("Regular"));
		syncPortLable.setJustificationType(juce::Justification::centred);
		syncPortLable.setEditable(false, false, false);
		syncPortLable.setColour(juce::Label::backgroundColourId, juce::Colour(ui::CommonColorID::neutralGrey4));
		syncPortLable.setColour(juce::Label::outlineColourId, Colours::white);
		syncPortLable.makeVisible(this);

		clkRateLable.setFont(juce::Font(font_15, juce::Font::plain).withTypefaceStyle("Regular"));
		clkRateLable.setJustificationType(juce::Justification::centred);
		clkRateLable.setEditable(false, false, false);
		clkRateLable.setColour(juce::Label::backgroundColourId, juce::Colour(ui::CommonColorID::neutralGrey4));
		clkRateLable.setColour(juce::Label::outlineColourId, Colours::white);
		clkRateLable.makeVisible(this);

		startLable.setFont(juce::Font(font_15, juce::Font::plain).withTypefaceStyle("Regular"));
		startLable.setJustificationType(juce::Justification::centred);
		startLable.setEditable(false, false, false);
		startLable.setColour(juce::Label::backgroundColourId, juce::Colour(ui::CommonColorID::neutralGrey4));
		startLable.setColour(juce::Label::outlineColourId, Colours::white);
		startLable.makeVisible(this);

		intModeBtn.makeVisibleAddListnerAndAddRadioGroup(this, 1356);
		extModeBtn.makeVisibleAddListnerAndAddRadioGroup(this, 1356);

		mport1Btn.makeVisibleAddListnerAndAddRadioGroup(this, CLKBTN_RADIO_GROUP_ID);
		mport2Btn.makeVisibleAddListnerAndAddRadioGroup(this, CLKBTN_RADIO_GROUP_ID);
		mport3Btn.makeVisibleAddListnerAndAddRadioGroup(this, CLKBTN_RADIO_GROUP_ID);
		mport4Btn.makeVisibleAddListnerAndAddRadioGroup(this, CLKBTN_RADIO_GROUP_ID);
		mport5Btn.makeVisibleAddListnerAndAddRadioGroup(this, CLKBTN_RADIO_GROUP_ID);
		uport1Btn.makeVisibleAddListnerAndAddRadioGroup(this, CLKBTN_RADIO_GROUP_ID);
		uport2Btn.makeVisibleAddListnerAndAddRadioGroup(this, CLKBTN_RADIO_GROUP_ID);
		uport3Btn.makeVisibleAddListnerAndAddRadioGroup(this, CLKBTN_RADIO_GROUP_ID);
		uport4Btn.makeVisibleAddListnerAndAddRadioGroup(this, CLKBTN_RADIO_GROUP_ID);
		uport5Btn.makeVisibleAddListnerAndAddRadioGroup(this, CLKBTN_RADIO_GROUP_ID);
		uport6Btn.makeVisibleAddListnerAndAddRadioGroup(this, CLKBTN_RADIO_GROUP_ID);
		uhport1Btn.makeVisibleAddListnerAndAddRadioGroup(this, CLKBTN_RADIO_GROUP_ID);
		uhport2Btn.makeVisibleAddListnerAndAddRadioGroup(this, CLKBTN_RADIO_GROUP_ID);
		uhport3Btn.makeVisibleAddListnerAndAddRadioGroup(this, CLKBTN_RADIO_GROUP_ID);
		uhport4Btn.makeVisibleAddListnerAndAddRadioGroup(this, CLKBTN_RADIO_GROUP_ID);
		uhport5Btn.makeVisibleAddListnerAndAddRadioGroup(this, CLKBTN_RADIO_GROUP_ID);
		sportBtn.makeVisibleAddListnerAndAddRadioGroup(this, CLKBTN_RADIO_GROUP_ID);
		sOutportBtn.makeVisibleAddListnerAndAddRadioGroup(this, CLKBTN_RADIO_GROUP_ID);
		sOutportBtn.setVisible(false);

		intModeBtn.sethoverImages("clockmode-internal-default-hover.png", "clockmode-internal-active-hover.png", "");
		extModeBtn.sethoverImages("clockmode-external-default-hover.png", "clockmode-external-active-hover.png", "");
		mport1Btn.sethoverImages("clocksetting-number-1-hover.png", "clocksetting-number-1-active-hover.png", "");
		mport2Btn.sethoverImages("clocksetting-number-2-hover.png", "clocksetting-number-2-active-hover.png", "");
		mport3Btn.sethoverImages("clocksetting-number-3-hover.png", "clocksetting-number-3-active-hover.png", "");
		mport4Btn.sethoverImages("clocksetting-number-4-hover.png", "clocksetting-number-4-active-hover.png", "");
		mport5Btn.sethoverImages("clocksetting-number-5-hover.png", "clocksetting-number-5-active-hover.png", "");
		uport1Btn.sethoverImages("clocksetting-number-1-hover.png", "clocksetting-number-1-active-hover.png", "");
		uport2Btn.sethoverImages("clocksetting-number-2-hover.png", "clocksetting-number-2-active-hover.png", "");
		uport3Btn.sethoverImages("clocksetting-number-3-hover.png", "clocksetting-number-3-active-hover.png", "");
		uport4Btn.sethoverImages("clocksetting-number-4-hover.png", "clocksetting-number-4-active-hover.png", "");
		uport5Btn.sethoverImages("clocksetting-number-5-hover.png", "clocksetting-number-5-active-hover.png", "");
		uport6Btn.sethoverImages("clocksetting-number-6-hover.png", "clocksetting-number-6-active-hover.png", "");
		//uhport1Btn.sethoverImages("usb-host-hover.png", "usb-host-active-hover.png", "");
		//uhport2Btn.sethoverImages("usb-host-hover.png", "usb-host-active-hover.png", "");
		/*uhport3Btn.sethoverImages("usb-host-hover.png", "usb-host-active-hover.png", "");
		uhport4Btn.sethoverImages("usb-host-hover.png", "usb-host-active-hover.png", "");
		uhport5Btn.sethoverImages("usb-host-hover.png", "usb-host-active-hover.png", "");*/
		sportBtn.sethoverImages("clock-in-hover.png", "clock-in-active-hover.png", "");
		sOutportBtn.sethoverImages("clock-out-hover.png", "clock-out-active-hover.png", "");

		intModeBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		extModeBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		mport1Btn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		mport2Btn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		mport3Btn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		mport4Btn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		mport5Btn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		uport1Btn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		uport2Btn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		uport3Btn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		uport4Btn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		uport5Btn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		uport6Btn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		uhport1Btn.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		uhport2Btn.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		uhport3Btn.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		uhport4Btn.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		uhport5Btn.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		sportBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());
		sOutportBtn.setLookAndFeel(ImageButtonLookandFeel::getLnf());

		addAndMakeVisible(syncClk);
		syncClk.setDisplayFormat(CommonListBox::BoxType::withoutTitleBar);
		syncClk.setValueColour(Theme::Instance().getColour(customOrange));

		addAndMakeVisible(syncOutClk);
		syncOutClk.setDisplayFormat(CommonListBox::BoxType::withoutTitleBar);
		syncOutClk.setValueColour(Theme::Instance().getColour(customOrange));
		syncOutClk.setVisible(false);

		addAndMakeVisible(syncTrigger);
		syncTrigger.setDisplayFormat(CommonListBox::BoxType::withoutTitleBar);
		syncTrigger.setValueColour(Theme::Instance().getColour(customOrange));

		midiClkOptCtl = IgniteControlOptions::GetAppOptInstance();
		addChildComponent(midiClkOptCtl);
		midiClkOptCtl->setBounds(xStartOptctl, yStartOptctl, widthOptctl, heightOptctlt);
		midiClkOptCtl->addOptCtlListener(this);

		ctlBox1.items.add(FlexItem(mport1Btn).withMargin({ 0,8,0,0 }).withFlex(1));
		ctlBox1.items.add(FlexItem(mport2Btn).withMargin({ 0,8,0,0 }).withFlex(1));
		ctlBox1.items.add(FlexItem(mport3Btn).withMargin({ 0,8,0,0 }).withFlex(1));
		ctlBox1.items.add(FlexItem(mport4Btn).withMargin({ 0,8,0,0 }).withFlex(1));
		ctlBox1.items.add(FlexItem(mport5Btn).withMargin({ 0,0,0,0 }).withFlex(1));
		ctlBox2.items.add(FlexItem(uport1Btn).withMargin({ 0,8,0,0 }).withFlex(1));
		ctlBox2.items.add(FlexItem(uport2Btn).withMargin({ 0,8,0,0 }).withFlex(1));
		ctlBox2.items.add(FlexItem(uport3Btn).withMargin({ 0,8,0,0 }).withFlex(1));
		ctlBox2.items.add(FlexItem(uport4Btn).withMargin({ 0,8,0,0 }).withFlex(1));
		ctlBox2.items.add(FlexItem(uport5Btn).withMargin({ 0,8,0,0 }).withFlex(1));
		ctlBox2.items.add(FlexItem(uport6Btn).withMargin({ 0,8,0,0 }).withFlex(1));
		ctlBox3.items.add(FlexItem(uhport1Btn).withMargin({ 0,0,0,0 }).withFlex(1));
		ctlBox3.items.add(FlexItem(uhport2Btn).withMargin({ 0,0,0,0 }).withFlex(1));
		ctlBox3.items.add(FlexItem(uhport3Btn).withMargin({ 0,0,0,0 }).withFlex(1));
		ctlBox3.items.add(FlexItem(uhport4Btn).withMargin({ 0,0,0,0 }).withFlex(1));
		ctlBox3.items.add(FlexItem(uhport5Btn).withMargin({ 0,0,0,0 }).withFlex(1));

		syncClk.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,370 });
		syncOutClk.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,370 });
		syncTrigger.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,370 });
		syncClk.setValueFontSize(20.0f);
		syncOutClk.setValueFontSize(20.0f);
		syncTrigger.setValueFontSize(20.0f);
		intModeBtn.setToggleState(false, dontSendNotification);
		extModeBtn.setToggleState(false, dontSendNotification);
		mport1Btn.setToggleState(false, dontSendNotification);
		mport2Btn.setToggleState(false, dontSendNotification);
		mport3Btn.setToggleState(false, dontSendNotification);
		mport4Btn.setToggleState(false, dontSendNotification);
		mport5Btn.setToggleState(false, dontSendNotification);
		uport1Btn.setToggleState(false, dontSendNotification);
		uport2Btn.setToggleState(false, dontSendNotification);
		uport3Btn.setToggleState(false, dontSendNotification);
		uport4Btn.setToggleState(false, dontSendNotification);
		uport5Btn.setToggleState(false, dontSendNotification);
		uport6Btn.setToggleState(false, dontSendNotification);
		uhport1Btn.setToggleState(false, dontSendNotification);
		uhport2Btn.setToggleState(false, dontSendNotification);
		uhport3Btn.setToggleState(false, dontSendNotification);
		uhport4Btn.setToggleState(false, dontSendNotification);
		uhport5Btn.setToggleState(false, dontSendNotification);
		sportBtn.setToggleState(false, dontSendNotification);
		sOutportBtn.setToggleState(false, dontSendNotification);

		popupPtr = CommonPopUp::getCommonPopupInstance();
		_pInfoWindow = CommonInfoWindow::GetInfoWindowInstance();
		getAssets();
		syncClk.onSelectionChanged = [this](int value, const juce::String& name)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			clkConfigDataUpdated = true;
			setEditIndication();
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsMidiClkCnfg, (paramId_t)SettingsMidiClkCnfgParam::inputPpqn, value);
		};

		syncOutClk.onSelectionChanged = [this](int value, const juce::String& name)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			clkConfigDataUpdated = true;
			setEditIndication();
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsMidiClkCnfg, (paramId_t)SettingsMidiClkCnfgParam::outputPpqn, value);
		};

		syncTrigger.onSelectionChanged = [this](int value, const juce::String& name)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;

			clkConfigDataUpdated = true;
			setEditIndication();
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsMidiClkCnfg, (paramId_t)SettingsMidiClkCnfgParam::triggerForIn, value);
		};

		syncClk.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		syncOutClk.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		syncTrigger.onFocusChanged = [this](bool a)
		{
			repaint();
		};
		setSize(getWidth(), getHeight());

	}

	IgniteMidiClkSetting::~IgniteMidiClkSetting()
	{
	}

	void IgniteMidiClkSetting::getAssets()
	{
		clkBgdefaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("clockgroup-bg-container.png"));
		clkRatedefaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("clockrate-bg-modallink-122x80-default.png"));
		clkRatehoverImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("clockrate-bg-modallink-122x80-default-hover.png"));
		husbDeafultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("husb-item-bg-default.png"));
		husbDeafultHoverImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("husb-item-bg-default-hover.png"));
		husbActiveImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("husb-item-bg-active.png"));
		husbActiveHoverImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("husb-item-bg-active-hover.png"));
	}
	void IgniteMidiClkSetting::paint(juce::Graphics& g)
	{
		Image Draw;

		if (clkConfigDataUpdated && !isAutosave)
			MenuMode::GetMenuModeInstance()->setHeader("Clock Configuration*");
		else
			MenuMode::GetMenuModeInstance()->setHeader("Clock Configuration");

		g.setColour(ui::Theme::Instance().getColour((neutralBlack)));
		g.fillAll();

		if (isClockInputMode)
		{
			if (!isIntClockMode)
			{
				g.drawImage(clkBgdefaultImage, ui::Rectangle<float>{10, 180, 1004, 60});
				g.drawImage(clkBgdefaultImage, ui::Rectangle<float>{10, 244, 1004, 60});
				g.drawImage(clkBgdefaultImage, ui::Rectangle<float>{10, 308, 1004, 60});
				g.drawImage(clkBgdefaultImage, ui::Rectangle<float>{10, 372, 1004, 60});
				g.drawImage(syncClk.getFocusState() ? Draw = clkRatehoverImage : Draw = clkRatedefaultImage, ui::Rectangle<float>{ 202, 317, 203, 44 });
				//g.drawImage(syncTrigger.getFocusState() ? Draw = clkRatehoverImage : Draw = clkRatedefaultImage, ui::Rectangle<float>{ 416, 361, 203, 44 });

				if(uhport1Btn.isVisible())
					g.drawImage(uhport1Btn.getToggleState() ? (uhport1Btn.isFocused ? Draw = husbActiveHoverImage : Draw = husbActiveImage) : (uhport1Btn.isFocused ? Draw = husbDeafultHoverImage : Draw = husbDeafultImage), ui::Rectangle<float>{97, 380, 168, 44});
				if (uhport2Btn.isVisible())
					g.drawImage(uhport2Btn.getToggleState() ? (uhport2Btn.isFocused ? Draw = husbActiveHoverImage : Draw = husbActiveImage) : (uhport2Btn.isFocused ? Draw = husbDeafultHoverImage : Draw = husbDeafultImage), ui::Rectangle<float>{269, 380, 168, 44});
				if (uhport3Btn.isVisible())
					g.drawImage(uhport3Btn.getToggleState() ? (uhport3Btn.isFocused ? Draw = husbActiveHoverImage : Draw = husbActiveImage) : (uhport3Btn.isFocused ? Draw = husbDeafultHoverImage : Draw = husbDeafultImage), ui::Rectangle<float>{441, 380, 168, 44});
				if (uhport4Btn.isVisible())
					g.drawImage(uhport4Btn.getToggleState() ? (uhport4Btn.isFocused ? Draw = husbActiveHoverImage : Draw = husbActiveImage) : (uhport4Btn.isFocused ? Draw = husbDeafultHoverImage : Draw = husbDeafultImage), ui::Rectangle<float>{613, 380, 168, 44});
				if (uhport5Btn.isVisible())
					g.drawImage(uhport5Btn.getToggleState() ? (uhport5Btn.isFocused ? Draw = husbActiveHoverImage : Draw = husbActiveImage) : (uhport5Btn.isFocused ? Draw = husbDeafultHoverImage : Draw = husbDeafultImage), ui::Rectangle<float>{785, 380, 168, 44});

			}
		}
		else
		{
			g.drawImage(clkBgdefaultImage, ui::Rectangle<float>{10, 126, 1004, 60});
			g.drawImage(clkBgdefaultImage, ui::Rectangle<float>{10, 190, 1004, 60});
			g.drawImage(clkBgdefaultImage, ui::Rectangle<float>{10, 254, 1004, 60});
			g.drawImage(clkBgdefaultImage, ui::Rectangle<float>{10, 318, 1004, 60});
			g.drawImage(syncOutClk.getFocusState() ? Draw = clkRatehoverImage : Draw = clkRatedefaultImage, ui::Rectangle<float>{ 202, 262, 203, 44 });
			if (uhport1Btn.isVisible())
				g.drawImage(uhport1Btn.getToggleState() ? (uhport1Btn.isFocused ? Draw = husbActiveHoverImage : Draw = husbActiveImage) : (uhport1Btn.isFocused ? Draw = husbDeafultHoverImage : Draw = husbDeafultImage), ui::Rectangle<float>{97, 326, 168, 44});
			if (uhport2Btn.isVisible())
				g.drawImage(uhport2Btn.getToggleState() ? (uhport2Btn.isFocused ? Draw = husbActiveHoverImage : Draw = husbActiveImage) : (uhport2Btn.isFocused ? Draw = husbDeafultHoverImage : Draw = husbDeafultImage), ui::Rectangle<float>{269, 326, 168, 44});
			if (uhport3Btn.isVisible())
				g.drawImage(uhport3Btn.getToggleState() ? (uhport3Btn.isFocused ? Draw = husbActiveHoverImage : Draw = husbActiveImage) : (uhport3Btn.isFocused ? Draw = husbDeafultHoverImage : Draw = husbDeafultImage), ui::Rectangle<float>{441, 326, 168, 44});
			if (uhport4Btn.isVisible())
				g.drawImage(uhport4Btn.getToggleState() ? (uhport4Btn.isFocused ? Draw = husbActiveHoverImage : Draw = husbActiveImage) : (uhport4Btn.isFocused ? Draw = husbDeafultHoverImage : Draw = husbDeafultImage), ui::Rectangle<float>{613, 326, 168, 44});
			if (uhport5Btn.isVisible())
				g.drawImage(uhport5Btn.getToggleState() ? (uhport5Btn.isFocused ? Draw = husbActiveHoverImage : Draw = husbActiveImage) : (uhport5Btn.isFocused ? Draw = husbDeafultHoverImage : Draw = husbDeafultImage), ui::Rectangle<float>{785, 326, 168, 44});

		}
	}

	void IgniteMidiClkSetting::setUsbHostVisibility()
	{
		auto numOfHost = mt::Ignite::midiPortList.size() - 11;
		CommonButton* buttons[] = { &uhport1Btn, &uhport2Btn, &uhport3Btn, &uhport4Btn, &uhport5Btn };

		for (int i = 0; i < 5; i++)
		{
			bool isVisible = numOfHost > i;
			buttons[i]->setVisible(isVisible);
			if (isVisible)
				buttons[i]->setButtonText(mt::Ignite::midiPortList[11 + i]);
		}
	}

	void IgniteMidiClkSetting::updateData()
	{
		std::vector<IgniteParamList> midiClkParams;
		IgniteParamList params;

		if (isClockInputMode)
		{
			params.param = (paramId_t)SettingsMidiClkCnfgParam::clkInPort;
			midiClkParams.push_back(params);
			params.param = (paramId_t)SettingsMidiClkCnfgParam::inputPpqn;
			midiClkParams.push_back(params);
			params.param = (paramId_t)SettingsMidiClkCnfgParam::triggerForIn;
			midiClkParams.push_back(params);
		}
		else
		{
			params.param = (paramId_t)SettingsMidiClkCnfgParam::clkOutPort;
			midiClkParams.push_back(params);
			params.param = (paramId_t)SettingsMidiClkCnfgParam::outputPpqn;
			midiClkParams.push_back(params);
			params.param = (paramId_t)SettingsMidiClkCnfgParam::triggerForOut;
			midiClkParams.push_back(params);
		}

		midiClkParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsMidiClkCnfg, midiClkParams);

		for (auto& param_id : midiClkParams)
		{
			switch (param_id.param)
			{
			case (paramId_t)SettingsMidiClkCnfgParam::clkInPort:
				if (param_id.MsgValue.get< int8_t >() == IGNITE_CLK_PORT_INTERNAL_CLK)
				{
					intModeBtn.setToggleState(true, dontSendNotification);
					isIntClockMode = true;
					resized();
				}
				else
				{
					extModeBtn.setToggleState(true, dontSendNotification);
					isIntClockMode = false;
					updatePortSelection(param_id.MsgValue.get< int8_t >(), true);
					resized();
				}
				break;
			case (paramId_t)SettingsMidiClkCnfgParam::inputPpqn:
				syncClk.setSelected(param_id.MsgValue.get< int8_t >());
				break;
			case (paramId_t)SettingsMidiClkCnfgParam::triggerForIn:
				syncTrigger.setSelected(param_id.MsgValue.get< int8_t >());
				break;
			case (paramId_t)SettingsMidiClkCnfgParam::clkOutPort:
			{
				uint32_t outPortEnableStateBitMap = param_id.MsgValue.get< uint32_t >();
				for (auto port = IGNITE_CLK_PORT_DIN_MIDI_PORT_1; port < IGNITE_CLK_PORT_MAX; ++port)
				{
					//port ids are sequential numbers starting from zero
					//So it can be used to access the bitmap, without additional variable
					updatePortSelection(port, (outPortEnableStateBitMap & (1 << port)) ? true : false);
				}
			}
				break;
			
			case (paramId_t)SettingsMidiClkCnfgParam::outputPpqn:
				syncOutClk.setSelected(param_id.MsgValue.get< int8_t >());
				break;
			}
		}
		setUsbHostVisibility();
	}

	void IgniteMidiClkSetting::updatePortSelection(int port, bool state)
	{
		switch (port)
		{
		case IGNITE_CLK_PORT_DIN_MIDI_PORT_1:
			mport1Btn.setToggleState(state, dontSendNotification);
			break;
		case IGNITE_CLK_PORT_DIN_MIDI_PORT_2:
			mport2Btn.setToggleState(state, dontSendNotification);
			break;
		case IGNITE_CLK_PORT_DIN_MIDI_PORT_3:
			mport3Btn.setToggleState(state, dontSendNotification);
			break;
		case IGNITE_CLK_PORT_DIN_MIDI_PORT_4:
			mport4Btn.setToggleState(state, dontSendNotification);
			break;
		case IGNITE_CLK_PORT_DIN_MIDI_PORT_5:
			mport5Btn.setToggleState(state, dontSendNotification);
			break;
		case IGNITE_CLK_PORT_USB_D_MIDI_PORT_1:
			uport1Btn.setToggleState(state, dontSendNotification);
			break;
		case IGNITE_CLK_PORT_USB_D_MIDI_PORT_2:
			uport2Btn.setToggleState(state, dontSendNotification);
			break;
		case IGNITE_CLK_PORT_USB_D_MIDI_PORT_3:
			uport3Btn.setToggleState(state, dontSendNotification);
			break;
		case IGNITE_CLK_PORT_USB_D_MIDI_PORT_4:
			uport4Btn.setToggleState(state, dontSendNotification);
			break;
		case IGNITE_CLK_PORT_USB_D_MIDI_PORT_5:
			uport5Btn.setToggleState(state, dontSendNotification);
			break;
		case IGNITE_CLK_PORT_USB_D_MIDI_PORT_6:
			uport6Btn.setToggleState(state, dontSendNotification);
			break;
		case IGNITE_CLK_PORT_USB_HOST_MIDI_PORT_1:
			uhport1Btn.setToggleState(state, dontSendNotification);
			break;
		case IGNITE_CLK_PORT_USB_HOST_MIDI_PORT_2:
			uhport2Btn.setToggleState(state, dontSendNotification);
			break;
		case IGNITE_CLK_PORT_USB_HOST_MIDI_PORT_3:
			uhport3Btn.setToggleState(state, dontSendNotification);
			break;
		case IGNITE_CLK_PORT_USB_HOST_MIDI_PORT_4:
			uhport4Btn.setToggleState(state, dontSendNotification);
			break;
		case IGNITE_CLK_PORT_USB_HOST_MIDI_PORT_5:
			uhport5Btn.setToggleState(state, dontSendNotification);
			break;
		case IGNITE_CLK_PORT_SYNC_PORT:
			isClockInputMode ? sportBtn.setToggleState(state, dontSendNotification) : sOutportBtn.setToggleState(state, dontSendNotification);
			break;
		}
	}

	void IgniteMidiClkSetting::autoSaveData()
	{
		_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsMidiClkCnfg, (paramId_t)SettingsMidiClkCnfgParam::saveCmd, 0);
		enableControlButton(IgniteControlOptions::SAVE, false);
		enableControlButton(IgniteControlOptions::UNDO, false);
		clkConfigDataUpdated = false;
	}

	void IgniteMidiClkSetting::setEditIndication()
	{
		if (clkConfigDataUpdated)
		{
			enableControlButton(IgniteControlOptions::SAVE, true);
			enableControlButton(IgniteControlOptions::UNDO, true);
		}
		else
		{
			enableControlButton(IgniteControlOptions::SAVE, false);
			enableControlButton(IgniteControlOptions::UNDO, false);
		}
		repaint();
	}

	void IgniteMidiClkSetting::resized()
	{
		ui::Rectangle zeroBound{ 0, 0, 0, 0 };

		if (isClockInputMode)
		{
			intModeBtn.setBounds(ui::Rectangle(95, 126, 245, 50));
			extModeBtn.setBounds(ui::Rectangle(348, 126, 245, 50));
			modeLable.setBounds(ui::Rectangle(20, 136, 55, 30));

			if (isIntClockMode)
			{
				midiPortLable.setBounds(zeroBound);
				usbPortLable.setBounds(zeroBound);
				usbHPortLable.setBounds(zeroBound);
				syncPortLable.setBounds(zeroBound);
				sportBtn.setBounds(zeroBound);
				sOutportBtn.setBounds(zeroBound);
				clkRateLable.setBounds(zeroBound);
				syncOutClk.setBounds(zeroBound);
				syncClk.setBounds(zeroBound);
				startLable.setBounds(zeroBound);
				syncTrigger.setBounds(zeroBound);
				ctlBox1.performLayout(zeroBound);
				ctlBox2.performLayout(zeroBound);
				ctlBox3.performLayout(zeroBound);
			}
			else
			{
				midiPortLable.setBounds(ui::Rectangle(20, 195, 55, 30));
				usbPortLable.setBounds(ui::Rectangle(20, 259, 44, 30));
				syncPortLable.setBounds(ui::Rectangle(20, 323, 55, 30));
				usbHPortLable.setBounds(ui::Rectangle(20, 387, 55, 30));

				sportBtn.setBounds(ui::Rectangle(97, 316, 94, 44));
				sOutportBtn.setBounds(ui::Rectangle(97, 316, 94, 44));

				clkRateLable.setBounds(ui::Rectangle(223, 322, 80, 30));
				syncOutClk.setBounds(ui::Rectangle(310, 328, 79, 20));
				syncClk.setBounds(ui::Rectangle(310, 328, 79, 20));

				startLable.setBounds(zeroBound);
				syncTrigger.setBounds(zeroBound);
				/*startLable.setBounds(ui::Rectangle(437, 368, 80, 30));
				syncTrigger.setBounds(ui::Rectangle(520, 373, 100, 20));*/

				ctlBox1.performLayout(ui::Rectangle(95, 186, 527, 48));
				ctlBox2.performLayout(ui::Rectangle(88, 250, 741, 48));
				ctlBox3.performLayout(ui::Rectangle(88, 378, 856, 48));
			}
		}
		else
		{
			intModeBtn.setBounds(zeroBound);
			extModeBtn.setBounds(zeroBound);
			modeLable.setBounds(zeroBound);
			startLable.setBounds(zeroBound);
			syncTrigger.setBounds(zeroBound);

			midiPortLable.setBounds(ui::Rectangle(20, 141, 55, 30));
			usbPortLable.setBounds(ui::Rectangle(20, 205, 44, 30));
			syncPortLable.setBounds(ui::Rectangle(20, 269, 55, 30));
			usbHPortLable.setBounds(ui::Rectangle(20, 333, 55, 30));

			sportBtn.setBounds(ui::Rectangle(97, 262, 94, 44));
			sOutportBtn.setBounds(ui::Rectangle(97, 262, 94, 44));

			clkRateLable.setBounds(ui::Rectangle(223, 269, 80, 30));
			syncOutClk.setBounds(ui::Rectangle(310, 274, 79, 20));
			syncClk.setBounds(ui::Rectangle(310, 274, 79, 20));

			ctlBox1.performLayout(ui::Rectangle(95, 132, 527, 48));
			ctlBox2.performLayout(ui::Rectangle(88, 196, 741, 48));
			ctlBox3.performLayout(ui::Rectangle(88, 324, 856, 48));
		}
		syncOutClk.setVisible(!isClockInputMode);
		syncClk.setVisible(isClockInputMode);
		sportBtn.setVisible(isClockInputMode);
		sOutportBtn.setVisible(!isClockInputMode);
		repaint();
	}

	void IgniteMidiClkSetting::changeVisibility()
	{
		mport1Btn.setRadioGroupId(isClockInputMode ? CLKBTN_RADIO_GROUP_ID : 0, dontSendNotification);
		mport2Btn.setRadioGroupId(isClockInputMode ? CLKBTN_RADIO_GROUP_ID : 0, dontSendNotification);
		mport3Btn.setRadioGroupId(isClockInputMode ? CLKBTN_RADIO_GROUP_ID : 0, dontSendNotification);
		mport4Btn.setRadioGroupId(isClockInputMode ? CLKBTN_RADIO_GROUP_ID : 0, dontSendNotification);
		mport5Btn.setRadioGroupId(isClockInputMode ? CLKBTN_RADIO_GROUP_ID : 0, dontSendNotification);
		uport1Btn.setRadioGroupId(isClockInputMode ? CLKBTN_RADIO_GROUP_ID : 0, dontSendNotification);
		uport2Btn.setRadioGroupId(isClockInputMode ? CLKBTN_RADIO_GROUP_ID : 0, dontSendNotification);
		uport3Btn.setRadioGroupId(isClockInputMode ? CLKBTN_RADIO_GROUP_ID : 0, dontSendNotification);
		uport4Btn.setRadioGroupId(isClockInputMode ? CLKBTN_RADIO_GROUP_ID : 0, dontSendNotification);
		uport5Btn.setRadioGroupId(isClockInputMode ? CLKBTN_RADIO_GROUP_ID : 0, dontSendNotification);
		uport6Btn.setRadioGroupId(isClockInputMode ? CLKBTN_RADIO_GROUP_ID : 0, dontSendNotification);
		uhport1Btn.setRadioGroupId(isClockInputMode ? CLKBTN_RADIO_GROUP_ID : 0, dontSendNotification);
		uhport2Btn.setRadioGroupId(isClockInputMode ? CLKBTN_RADIO_GROUP_ID : 0, dontSendNotification);
		uhport3Btn.setRadioGroupId(isClockInputMode ? CLKBTN_RADIO_GROUP_ID : 0, dontSendNotification);
		uhport4Btn.setRadioGroupId(isClockInputMode ? CLKBTN_RADIO_GROUP_ID : 0, dontSendNotification);
		uhport5Btn.setRadioGroupId(isClockInputMode ? CLKBTN_RADIO_GROUP_ID : 0, dontSendNotification);
		sportBtn.setRadioGroupId(isClockInputMode ? CLKBTN_RADIO_GROUP_ID : 0, dontSendNotification);
		sOutportBtn.setRadioGroupId(isClockInputMode ? CLKBTN_RADIO_GROUP_ID : 0, dontSendNotification);

		mport1Btn.setToggleState(false, dontSendNotification);
		mport2Btn.setToggleState(false, dontSendNotification);
		mport3Btn.setToggleState(false, dontSendNotification);
		mport4Btn.setToggleState(false, dontSendNotification);
		mport5Btn.setToggleState(false, dontSendNotification);
		uport1Btn.setToggleState(false, dontSendNotification);
		uport2Btn.setToggleState(false, dontSendNotification);
		uport3Btn.setToggleState(false, dontSendNotification);
		uport4Btn.setToggleState(false, dontSendNotification);
		uport5Btn.setToggleState(false, dontSendNotification);
		uport6Btn.setToggleState(false, dontSendNotification);
		uhport1Btn.setToggleState(false, dontSendNotification);
		uhport2Btn.setToggleState(false, dontSendNotification);
		uhport3Btn.setToggleState(false, dontSendNotification);
		uhport4Btn.setToggleState(false, dontSendNotification);
		uhport5Btn.setToggleState(false, dontSendNotification);
		sportBtn.setToggleState(false, dontSendNotification);
		sOutportBtn.setToggleState(false, dontSendNotification);
	}

	void IgniteMidiClkSetting::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		clkConfigDataUpdated = true;
		if (buttonThatWasClicked == &clockInbtn)
		{
			if (clockInbtn.getToggleState())
			{
				clkConfigDataUpdated = false;
				isClockInputMode = true;
				changeVisibility();
				updateData();
				resized();
				autoSaveData();
				_pInfoWindow->setTextandShow("Clock Out settings auto saved");
			}
		}
		else if (buttonThatWasClicked == &clockOutbtn)
		{
			if (clockOutbtn.getToggleState())
			{
				clkConfigDataUpdated = false;
				isClockInputMode = false;
				changeVisibility();
				updateData();
				resized();
				autoSaveData();
				_pInfoWindow->setTextandShow("Clock In settings auto saved");
			}
		}
		else if (buttonThatWasClicked == &intModeBtn)
		{
			if (intModeBtn.getToggleState())
			{
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsMidiClkCnfg,
					(paramId_t)SettingsMidiClkCnfgParam::clkInPort, IGNITE_CLK_PORT_INTERNAL_CLK);
				isIntClockMode = true;
				resized();
			}
		}
		else if (buttonThatWasClicked == &extModeBtn)
		{
			if (extModeBtn.getToggleState())
			{
				clkConfigDataUpdated = false;
				isIntClockMode = false;
				resized();
			}
		}
		//all port selection buttons
		else if (	(buttonThatWasClicked == &mport1Btn) || (buttonThatWasClicked == &mport2Btn) || (buttonThatWasClicked == &mport3Btn) || (buttonThatWasClicked == &mport4Btn) || (buttonThatWasClicked == &mport5Btn) ||
					(buttonThatWasClicked == &uport1Btn) || (buttonThatWasClicked == &uport2Btn) || (buttonThatWasClicked == &uport3Btn) || (buttonThatWasClicked == &uport4Btn) || (buttonThatWasClicked == &uport5Btn) || (buttonThatWasClicked == &uport6Btn) ||
					(buttonThatWasClicked == &uhport1Btn) || (buttonThatWasClicked == &uhport2Btn) || (buttonThatWasClicked == &uhport3Btn) || (buttonThatWasClicked == &uhport4Btn) || (buttonThatWasClicked == &uhport5Btn)
				)
		{
			if (isClockInputMode)
			{
				uhport1Btn.setToggleState(false, dontSendNotification);
				uhport2Btn.setToggleState(false, dontSendNotification);
				uhport3Btn.setToggleState(false, dontSendNotification);
				uhport4Btn.setToggleState(false, dontSendNotification);
				uhport5Btn.setToggleState(false, dontSendNotification);

			}
			int8_t portId = -1; 

			if (buttonThatWasClicked == &mport1Btn)
			{
				portId = IGNITE_CLK_PORT_DIN_MIDI_PORT_1;
			}
			else if (buttonThatWasClicked == &mport2Btn)
			{
				portId = IGNITE_CLK_PORT_DIN_MIDI_PORT_2;
			}
			else if (buttonThatWasClicked == &mport3Btn)
			{
				portId = IGNITE_CLK_PORT_DIN_MIDI_PORT_3;
			}
			else if (buttonThatWasClicked == &mport4Btn)
			{
				portId = IGNITE_CLK_PORT_DIN_MIDI_PORT_4;
			}
			else if (buttonThatWasClicked == &mport5Btn)
			{
				portId = IGNITE_CLK_PORT_DIN_MIDI_PORT_5;
			}
			else if (buttonThatWasClicked == &uport1Btn)
			{
				portId = IGNITE_CLK_PORT_USB_D_MIDI_PORT_1;
			}
			else if (buttonThatWasClicked == &uport2Btn)
			{
				portId = IGNITE_CLK_PORT_USB_D_MIDI_PORT_2;
			}
			else if (buttonThatWasClicked == &uport3Btn)
			{
				portId = IGNITE_CLK_PORT_USB_D_MIDI_PORT_3;
			}
			else if (buttonThatWasClicked == &uport4Btn)
			{
				portId = IGNITE_CLK_PORT_USB_D_MIDI_PORT_4;
			}
			else if (buttonThatWasClicked == &uport5Btn)
			{
				portId = IGNITE_CLK_PORT_USB_D_MIDI_PORT_5;
			}
			else if (buttonThatWasClicked == &uport6Btn)
			{
				portId = IGNITE_CLK_PORT_USB_D_MIDI_PORT_6;
			}
			else if (buttonThatWasClicked == &uhport1Btn)
			{
				uhport1Btn.setToggleState(!uhport1Btn.getToggleState(), dontSendNotification);
				portId = IGNITE_CLK_PORT_USB_HOST_MIDI_PORT_1;
			}
			else if (buttonThatWasClicked == &uhport2Btn)
			{
				uhport2Btn.setToggleState(!uhport2Btn.getToggleState(), dontSendNotification);
				portId = IGNITE_CLK_PORT_USB_HOST_MIDI_PORT_2;
			}
			else if (buttonThatWasClicked == &uhport3Btn)
			{
				uhport3Btn.setToggleState(!uhport3Btn.getToggleState(), dontSendNotification);
				portId = IGNITE_CLK_PORT_USB_HOST_MIDI_PORT_3;
			}
			else if (buttonThatWasClicked == &uhport4Btn)
			{
				uhport4Btn.setToggleState(!uhport4Btn.getToggleState(), dontSendNotification);
				portId = IGNITE_CLK_PORT_USB_HOST_MIDI_PORT_4;
			}
			else if (buttonThatWasClicked == &uhport5Btn)
			{
				uhport5Btn.setToggleState(!uhport5Btn.getToggleState(), dontSendNotification);
				portId = IGNITE_CLK_PORT_USB_HOST_MIDI_PORT_5;
			}
			if (isClockInputMode)
			{
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsMidiClkCnfg, (paramId_t)SettingsMidiClkCnfgParam::clkInPort, portId);
			}
			else
			{
				//Output clock can be enabled on multiple ports, at the same time
				//Read modify write 
				std::vector<IgniteParamList> midiClkParams;
				IgniteParamList params;
				params.param = (paramId_t)SettingsMidiClkCnfgParam::clkOutPort;
				midiClkParams.push_back(params);
				midiClkParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsMidiClkCnfg, midiClkParams);

				uint32_t outPortEnableStateBitMap = midiClkParams[0].MsgValue.get< uint32_t >();

				outPortEnableStateBitMap ^= (1 << portId);

				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsMidiClkCnfg, (paramId_t)SettingsMidiClkCnfgParam::clkOutPort, (uint32_t )outPortEnableStateBitMap);
			}
			
		}
		else if (buttonThatWasClicked == &sportBtn)
		{
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsMidiClkCnfg,
				(paramId_t)SettingsMidiClkCnfgParam::clkInPort, IGNITE_CLK_PORT_SYNC_PORT);
		}
		else if (buttonThatWasClicked == &sOutportBtn)
		{
			//Output clock can be enabled on multiple ports, at the same time
			//Read modify write 
			std::vector<IgniteParamList> midiClkParams;
			IgniteParamList params;
			params.param = (paramId_t)SettingsMidiClkCnfgParam::clkOutPort;
			midiClkParams.push_back(params);
			midiClkParams = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsMidiClkCnfg, midiClkParams);

			uint32_t outPortEnableStateBitMap = midiClkParams[0].MsgValue.get< uint32_t >();

			outPortEnableStateBitMap ^= (1 << IGNITE_CLK_PORT_SYNC_PORT);

			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsMidiClkCnfg, (paramId_t)SettingsMidiClkCnfgParam::clkOutPort, (uint32_t )outPortEnableStateBitMap);
		}
		setEditIndication();
	}

	void IgniteMidiClkSetting::onOptCtlButtonClicked(IgniteControlOptions::eKey option)
	{
		if (option == IgniteControlOptions::SAVEALLON)
		{
			clkConfigDataUpdated = false;
		}
		else if (option == IgniteControlOptions::AUTOSAVEON)
		{
			isAutosave = true;
		}
		else if (option == IgniteControlOptions::AUTOSAVEOFF)
		{
			isAutosave = false;
		}
		if (this->isVisible())
		{
			if (option == IgniteControlOptions::SAVE)
			{
				if (popupPtr->isDialogOpen.get() != true)
				{
					popupPtr->close();
					popupPtr->setPopUpPropories("Save ", 604, 290);
					popupPtr->setbtnsize(265, 44);
					popupPtr->setInfoText(String("Save Clock Configuration edits ? "));
					popupPtr->addImageButton("no", "btn-secondary-no-267x44-default.png", "btn-secondary-no-267x44-default-hover.png", 2);
					popupPtr->addImageButton("yes", "btn-yes-267x44-default.png", "btn-yes-267x44-default-hover.png", 1);
					popupPtr->popupType = POPUP_WITHOKCANCEL;
					popupPtr->isCloseButtonVisible(false);
					popupPtr->show();
					popupPtr->onSelectionChanged = [this](int r)
					{
						if (r == 1)
						{
							_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsMidiClkCnfg, (paramId_t)SettingsMidiClkCnfgParam::saveCmd, 0);
							enableControlButton(IgniteControlOptions::SAVE, false);
							enableControlButton(IgniteControlOptions::UNDO, false);
							clkConfigDataUpdated = false;
						}
						if (auto dw = getCurrentlyModalComponent())
							dw->exitModalState(0);
					};
				}
			}
			else if (option == IgniteControlOptions::UNDO)
			{
				if (clkConfigDataUpdated)
				{
					_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsMidiClkCnfg, (paramId_t)SettingsMidiClkCnfgParam::paramUndoCmd, 0);

					std::vector<IgniteParamList> midiClkParamList;
					IgniteParamList params;

					params.param = (paramId_t)SettingsMidiClkCnfgParam::paramUndoListCmd;
					midiClkParamList.push_back(params);
					midiClkParamList = _PUiVirtualEngine->getParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSettingsMidiClkCnfg, midiClkParamList);
					if (midiClkParamList.size() == 1)
					{
						clkConfigDataUpdated = false;
						enableControlButton(IgniteControlOptions::SAVE, false);
						enableControlButton(IgniteControlOptions::UNDO, false);
					}
					updateData();
				}
			}
		}
	}

	int IgniteMidiClkSetting::isEditing()
	{
		int index = 0;

		syncClk.IsEditing() ? index = 18 : 0;
		syncOutClk.IsEditing() ? index = 18 : 0;
		syncTrigger.IsEditing() ? index = 19 : 0;

		return index;
	}

	bool IgniteMidiClkSetting::PannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool setfocus = true;
		int editItem = MidiClkMenuViewItemID::NO_FOCUS;

		if (popupPtr != nullptr && popupPtr->IsEditing())
			return popupPtr->FPKeyHandler(true, param, KeyValue);

		if (KeyFocusedItem == MidiClkMenuViewItemID::NO_FOCUS)
		{
			/*1st key after Page visible */
			KeyFocusedItem = MidiClkMenuViewItemID::CLOCK_INPUT;

			if (FrontPannelParam::paramKey_RETURN_NAV == (FrontPannelParam)param)
			{
				AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SETTING_WINDOW);
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
					KeyFocusedItem = (KeyFocusedItem + 1 >= MidiClkMenuViewItemID::FOCUS_MAX ? (MidiClkMenuViewItemID::FOCUS_MAX) : KeyFocusedItem + 1);
					break;
				case FrontPannelParam::paramKey_RMOVERIGHT:
					KeyFocusedItem = (KeyFocusedItem - 1 <= MidiClkMenuViewItemID::NO_FOCUS ? (MidiClkMenuViewItemID::NO_FOCUS + 1) : KeyFocusedItem - 1);
					break;
				case FrontPannelParam::paramKey_RETURN_NAV:
					AppMenu::GetAppMenuInstance()->changeMenuOptionsVisibilty(AppMenu::MENU_WINDOWS::SETTING_WINDOW);
					break;
				}
			}
		}
		if (setfocus)
		{
			PannelSendKey(true, param, KeyValue);
		}
		return true;
	}

	void IgniteMidiClkSetting::PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		switch (BackupMenuView[KeyFocusedItem])
		{
		case CLOCK_INPUT:
			clockInbtn.FPKeyHandler(isFocuse, param, 0);
			break;
		case CLOCK_OUTPUT:
			clockOutbtn.FPKeyHandler(isFocuse, param, 0);
			break;
		case CLOCK_INTMODE:
			if (isClockInputMode)
				intModeBtn.FPKeyHandler(isFocuse, param, 0);
			else
			{
				KeyFocusedItem = MIDI_PORT1;
				mport1Btn.FPKeyHandler(true, param, 0);
			}
			break;
		case CLOCK_EXTMODE:
			if (isClockInputMode)
				extModeBtn.FPKeyHandler(isFocuse, param, 0);
			else
			{
				KeyFocusedItem = CLOCK_OUTPUT;
				clockOutbtn.FPKeyHandler(true, param, 0);
			}
			break;
		}
		if (!isClockInputMode || !isIntClockMode)
		{
			switch (BackupMenuView[KeyFocusedItem])
			{
			case MIDI_PORT1:
				mport1Btn.FPKeyHandler(isFocuse, param, 0);
				break;
			case MIDI_PORT2:
				mport2Btn.FPKeyHandler(isFocuse, param, 0);
				break;
			case MIDI_PORT3:
				mport3Btn.FPKeyHandler(isFocuse, param, 0);
				break;
			case MIDI_PORT4:
				mport4Btn.FPKeyHandler(isFocuse, param, 0);
				break;
			case MIDI_PORT5:
				mport5Btn.FPKeyHandler(isFocuse, param, 0);
				break;
			case MIDI_USBPORT1:
				uport1Btn.FPKeyHandler(isFocuse, param, 0);
				break;
			case MIDI_USBPORT2:
				uport2Btn.FPKeyHandler(isFocuse, param, 0);
				break;
			case MIDI_USBPORT3:
				uport3Btn.FPKeyHandler(isFocuse, param, 0);
				break;
			case MIDI_USBPORT4:
				uport4Btn.FPKeyHandler(isFocuse, param, 0);
				break;
			case MIDI_USBPORT5:
				uport5Btn.FPKeyHandler(isFocuse, param, 0);
				break;
			case MIDI_USBPORT6:
				uport6Btn.FPKeyHandler(isFocuse, param, 0);
				break;
			case MIDI_USB_HOSTPORT1:
				uhport1Btn.FPKeyHandler(isFocuse, param, 0);
				break;
			case MIDI_USB_HOSTPORT2:
				uhport2Btn.FPKeyHandler(isFocuse, param, 0);
				break;
			case MIDI_USB_HOSTPORT3:
				uhport3Btn.FPKeyHandler(isFocuse, param, 0);
				break;
			case MIDI_USB_HOSTPORT4:
				uhport4Btn.FPKeyHandler(isFocuse, param, 0);
				break;
			case MIDI_USB_HOSTPORT5:
				uhport5Btn.FPKeyHandler(isFocuse, param, 0);
				break;
			case MIDI_SYNCPORT:
				isClockInputMode ? sportBtn.FPKeyHandler(isFocuse, param, 0) : sOutportBtn.FPKeyHandler(isFocuse, param, 0);
				break;
			case MIDI_SYNCRATE:
				isClockInputMode ? syncClk.FPKeyHandler(isFocuse, param, KeyValue) : syncOutClk.FPKeyHandler(isFocuse, param, KeyValue);
				break;
			case MIDI_SYNC_START:
				if (isClockInputMode)
					syncTrigger.FPKeyHandler(isFocuse, param, KeyValue);
				else
				{
					KeyFocusedItem = MIDI_SYNCRATE;
					isClockInputMode ? syncClk.FPKeyHandler(true, param, KeyValue) : syncOutClk.FPKeyHandler(true, param, KeyValue);
				}
				break;
			default:
				break;
			}
		}
		else
		{
			if (KeyFocusedItem >= MIDI_PORT1)
			{
				KeyFocusedItem = CLOCK_EXTMODE;
				extModeBtn.FPKeyHandler(true, param, KeyValue);
			}
		}
		repaint();
	}
};