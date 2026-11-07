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
	IgniteLoopControl::IgniteLoopControl(std::vector<juce::String>* itemList)
	{
		loopList = itemList;
		addAndMakeVisible(loopStart);
		loopStart.setButtonText(TRANS("Select Loop Start"));
		loopStart.addListener(this);
		loopStart.setColour(juce::TextButton::buttonColourId, juce::Colours::black);
		loopStart.setInterceptsMouseClicks(false, false);

		addAndMakeVisible(loopEnd);
		loopEnd.setButtonText(TRANS("Select Loop End"));
		loopEnd.addListener(this);
		loopEnd.setColour(juce::TextButton::buttonColourId, juce::Colours::black);
		loopEnd.setInterceptsMouseClicks(false, false);

		addAndMakeVisible(loopStartSceneBox);
		loopStartSceneBox.updateListOptions(*itemList);
		loopStartSceneBox.setDisplayFormat(CommonListBox::BoxType::withTitleBar);
		loopStartSceneBox.setSelected(1);
		loopStartSceneBox.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,450 });
		loopStartSceneBox.setValueColour(Theme::Instance().getColour(customOrange));

		addAndMakeVisible(loopEndSceneBox);
		loopEndSceneBox.updateListOptions(*itemList);
		loopEndSceneBox.setDisplayFormat(CommonListBox::BoxType::withTitleBar);
		loopEndSceneBox.setSelected(1);
		loopEndSceneBox.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, juce::Rectangle{ 0,0,604,450 });
		loopEndSceneBox.setValueColour(Theme::Instance().getColour(customOrange));

		addAndMakeVisible(ctlApply);
		ctlApply.setButtonText(TRANS("Apply"));
		ctlApply.addListener(this);
		ctlApply.setColour(juce::TextButton::buttonColourId, juce::Colours::black);

		addAndMakeVisible(ctlCancel);
		ctlCancel.setButtonText(TRANS("Cancel"));
		ctlCancel.addListener(this);
		ctlCancel.setColour(juce::TextButton::buttonColourId, juce::Colours::black);

		addAndMakeVisible(ctlclear);
		ctlclear.setButtonText(TRANS("Clear Loop"));
		ctlclear.addListener(this);
		ctlclear.setColour(juce::TextButton::buttonColourId, juce::Colours::black);

		//loopBox1.items.add(FlexItem(loopStart).withMargin(3).withFlex(1));
		loopBox1.items.add(FlexItem(loopStartSceneBox).withFlex(1));

		//loopBox2.items.add(FlexItem(loopEnd).withMargin(3).withFlex(1));
		loopBox2.items.add(FlexItem(loopEndSceneBox).withFlex(1));

		addAndMakeVisible(Title);
		Title.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
		Title.setJustificationType(juce::Justification::centred);

		//loopBox.flexDirection = FlexBox::Direction::column;
		//loopBox.items.add(FlexItem(loopBox1).withMargin(3).withFlex(1));
		//loopBox.items.add(FlexItem(loopBox2).withMargin(3).withFlex(1));

		ctlBox.items.add(FlexItem(ctlApply).withMargin(3).withFlex(1));
		ctlBox.items.add(FlexItem(ctlCancel).withMargin(3).withFlex(1));
		ctlBox.items.add(FlexItem(ctlclear).withMargin(3).withFlex(1));

		loopStartSceneBox.onSelectionChanged = [this](int value, const juce::String& name)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;
			loopStartIndex = value;
		};

		loopEndSceneBox.onSelectionChanged = [this](int value, const juce::String& name)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;
			loopEndIndex = value;
		};

		loopStartSceneBox.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		loopEndSceneBox.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		setSize(getWidth(), getHeight());
	}

	IgniteLoopControl::~IgniteLoopControl()
	{
	}

	void IgniteLoopControl::paint(juce::Graphics& g)
	{
		auto b = getLocalBounds();
		Image Draw;
		loopStartSceneBox.updateListOptions(*loopList, loopStartIndex);
		loopEndSceneBox.updateListOptions(*loopList, loopEndIndex);
		loopStartSceneBox.setSelected(loopStartIndex);
		loopEndSceneBox.setSelected(loopEndIndex);

		g.setColour(Colour(0xFF48507A));
		g.fillAll();
		g.setColour(Colour(0xFF101226));
		g.fillRect(ui::Rectangle{ b.getX() + 2,b.getY() + 2,b.getWidth() - 4,b.getHeight() - 4 });

		Image dropImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("sceneloop-bg-container-long-default.png"));
		Image hoverImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("sceneloop-bg-container-long-hover.png"));

		(loopStartSceneBox.getFocusState() || loopStartSceneBox.isMouseOver()) ? Draw = hoverImage : Draw = dropImage;
		g.drawImage(Draw, ui::Rectangle<float>{ 30, 68, 667, 86  }, RectanglePlacement::centred);
		(loopEndSceneBox.getFocusState() || loopEndSceneBox.isMouseOver()) ? Draw = hoverImage : Draw = dropImage;
		g.drawImage(Draw, ui::Rectangle<float>{30, 174, 667, 86 }, RectanglePlacement::centred);

		Font a((float)(32));
		auto l = a.getStringWidth(loopStartSceneBox.getSelected());
		g.setColour(Theme::Instance().getColour(customBlue19));
		g.fillRect(45 + l, 113, 2, 25);

		g.setColour(Theme::Instance().getColour(customOrange));
		g.setFont(26.0f);
		g.drawText("Choose Start Loop", ui::Rectangle{ 55 + l,108,300,32 }, Justification::left, true);

		l = a.getStringWidth(loopEndSceneBox.getSelected());
		g.setColour(Theme::Instance().getColour(customBlue19));
		g.fillRect(45 + l, 218, 2, 25);

		g.setColour(Theme::Instance().getColour(customOrange));
		g.setFont(26.0f);
		g.drawText("Choose End Loop", ui::Rectangle{ 55 + l,213,300,32 }, Justification::left, true);
	}

	void IgniteLoopControl::resized()
	{
		Title.setBounds(0, 5, getWidth(), 60);
		loopBox1.performLayout(ui::Rectangle{ 30, 68,667,86 });
		loopBox2.performLayout(ui::Rectangle{ 30,174,667,86 });
		ctlBox.performLayout(Rectangle(30, 268, 540, heightCtlBox));
	}

	void IgniteLoopControl::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		loopKey selectedKey = loopKey::CANCEL;

		if (buttonThatWasClicked == &ctlApply)
		{
			selectedKey = loopKey::APPLY;
			if (onButtonPressed)
				onButtonPressed(selectedKey, loopStartIndex, loopEndIndex);
		}
		else if (buttonThatWasClicked == &ctlCancel)
		{
			selectedKey = loopKey::CANCEL;
			if (onButtonPressed)
				onButtonPressed(selectedKey, loopStartIndex, loopEndIndex);
		}
		else if (buttonThatWasClicked == &ctlclear)
		{
			selectedKey = loopKey::CLEAR;
			loopStartSceneBox.setSelected(0);
			loopEndSceneBox.setSelected(0);
			if (onButtonPressed)
				onButtonPressed(selectedKey, 0, 0);
		}
	}
	int IgniteLoopControl::IsEditing()
	{
		int index = 0;
		loopStartSceneBox.IsEditing() ? index = 1 : 0;
		loopEndSceneBox.IsEditing() ? index = 2 : 0;
		return index;
	}
	bool IgniteLoopControl::PannelKeyHandler(paramId_t param, uint32_t KeyValue)
	{
		bool setfocus = true;
		int EditItem = (int)IgniteLoopControl::loopKey::NONE;

		if (FocusIndex == (int)IgniteLoopControl::loopKey::NONE)
		{
			/*1st key after Page visible */
			FocusIndex = (int)IgniteLoopControl::loopKey::START;
		}
		else
		{
			EditItem = IsEditing();
			if (EditItem)
			{
				if (FocusIndex != EditItem)
				{
					PannelSendKey(false, param, KeyValue);
					FocusIndex = EditItem;
				}
				setfocus = true;
			}
			else
			{
				PannelSendKey(false, param, KeyValue);

				if (!IsEditing())
				{
					switch ((FrontPannelParam)param)
					{
					case FrontPannelParam::paramKey_RMOVELEFT:
						FocusIndex = (FocusIndex + 1 >= (int)IgniteLoopControl::loopKey::INVALID ? ((int)IgniteLoopControl::loopKey::INVALID) : FocusIndex + 1);
						break;
					case FrontPannelParam::paramKey_RMOVERIGHT:
						FocusIndex = (FocusIndex - 1 <= (int)IgniteLoopControl::loopKey::NONE ? ((int)IgniteLoopControl::loopKey::NONE + 1) : FocusIndex - 1);
						break;
					case FrontPannelParam::paramKey_RSELECT:
						break;
					case FrontPannelParam::paramKey_RETURN_NAV:
						onButtonPressed(loopKey::CANCEL, loopStartIndex, loopEndIndex);
						break;
					}
				}
			}
		}
		if (setfocus)
			PannelSendKey(true, param, KeyValue);

		return true;
	}

	void IgniteLoopControl::PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		switch ((IgniteLoopControl::loopKey)FocusIndex)
		{
		case IgniteLoopControl::loopKey::START:
			loopStartSceneBox.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case IgniteLoopControl::loopKey::END:
			loopEndSceneBox.FPKeyHandler(isFocuse, param, KeyValue);
			break;
		case IgniteLoopControl::loopKey::APPLY:
			ctlApply.setState((Button::ButtonState)isFocuse);
			if ((paramId_t)param == (paramId_t)FrontPannelParam::paramKey_RSELECT && isFocuse)
				buttonClicked(&ctlApply);
			break;
		case IgniteLoopControl::loopKey::CANCEL:
			ctlCancel.setState((Button::ButtonState)isFocuse);
			if ((paramId_t)param == (paramId_t)FrontPannelParam::paramKey_RSELECT && isFocuse)
				buttonClicked(&ctlCancel);
			break;
		case IgniteLoopControl::loopKey::CLEAR:
			ctlclear.setState((Button::ButtonState)isFocuse);
			if ((paramId_t)param == (paramId_t)FrontPannelParam::paramKey_RSELECT && isFocuse)
				buttonClicked(&ctlclear);
			break;
		default:
			break;
		}
		repaint();
	}
}
