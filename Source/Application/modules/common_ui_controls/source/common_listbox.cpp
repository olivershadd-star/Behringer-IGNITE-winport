/*
 * Copyright (c) - 2021 - MUSIC Tribe, MY.
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
	//////////////////////
	/// COMMON Button
	//////////////////////
	CommonList::CommonList(const String& Title, int NumColumns) : CommonList(Title, {}, 0, NumColumns)
	{}

	CommonList::CommonList(const String& title, const std::vector<juce::String>& Options, int Selected, int NumColumns, bool showRstBtn)
		: title(title), noOfColumns(NumColumns), showResetBtn(showRstBtn)
	{
		setLookAndFeel(CommonLooknFeel::getLnf());
		setOpaque(true);
		listTitle.makeVisible(this);
		listTitle.setText(title, dontSendNotification);
		listTitle.setJustificationType(Justification::centred);
		if (Options.size())
			setContent(Options, Selected);
		closeBtn.makeVisible(this);
		closeBtn.addListener(this);
		closeBtn.toFront(true);
	}


	CommonList::~CommonList()
	{
		deleteAndFree();
	}

	void CommonList::setContent(const std::vector<juce::String>& Data, int Selected)
	{
		// Delete earlier allocations.
		deleteAndFree();

		for (auto opt : Data)
		{
			auto option = new CommonToggleButton(opt);
			options.add(option);
			option->setRadioGroupId(55, NotificationType::dontSendNotification);
			option->makeVisibleAndAddListner(this);
			option->setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
		}
		setSelected(Selected);
		resized();
		repaint();
	}
	const String& CommonList::getTitle()
	{
		return title;
	}

	const int CommonList::getColumns()
	{
		return noOfColumns;
	}

	const int CommonList::getSelectedIndex()
	{
		return selection;
	}

	const String& CommonList::getSelected()
	{
		static String empty{ "" };
		if (isPositiveAndBelow(selection, options.size()))
			return options[selection]->getButtonText();
		return empty;
	}

	void CommonList::setTitle(const String& list_title)
	{
		title = list_title;
	}

	void CommonList::setColumns(int Cols)
	{
		noOfColumns = jmax<int>(1, Cols);
	}

	void CommonList::setSelected(int O)
	{
		if (options.size())
		{
			selection = jmin<int>(O, (options.size() - 1));
			selection = jmax<int>(selection, 0);
			options[selection]->setToggleState(true, NotificationType::dontSendNotification);
		}
	}

	void CommonList::clearSelected(int O)
	{
		if (options.size())
		{
			selection = jmin<int>(O, (options.size() - 1));
			selection = jmax<int>(selection, 0);
			options[selection]->setToggleState(false, NotificationType::dontSendNotification);
		}
	}
	void CommonList::setSelected(const String& O)
	{
		for (auto i = 0; i < options.size(); i++)
			if (!O.compare(options[i]->getButtonText()))
			{
				setSelected(i); break;
			}
	}

	void CommonList::makeVisible(Component* Parent)
	{
		Parent->addAndMakeVisible(dynamic_cast<Component&>(*this));
	}

	const int CommonList::getRequiredHeight()
	{
		auto b = getLocalBounds().reduced(10);

		const auto spaceW{ 5 }, spaceH{ 5 };
		auto w = (b.getWidth() - (spaceW * (noOfColumns - 1)) - 10) / (noOfColumns);
		auto noOfRows = (int)(options.size() / noOfColumns) + 1;
		auto h = juce::jlimit(40, 40, (b.getHeight() - (spaceW * (noOfRows - 1))) / (noOfRows));

		int column = 0, x = b.getX() + 3, y = b.getY() + 98;
		//for (auto opt : options)
		for (auto opt = 0; opt < options.size(); opt++)
		{
			//opt->setBounds(x, y, w, h);
			x += (w + spaceW);
			if (++column >= noOfColumns)
			{
				x = b.getX() + 3;
				y += (h + spaceH);
				column = 0;
			}
		}
		reqHeight = y + (h + spaceH) + 35 + 68 + 10;
		return reqHeight;
	}
	void CommonList::changeListLnF(LookAndFeel* newLookAndFeel)
	{
		for (int i = 0; i < options.size(); i++)
			options[i]->setLookAndFeel(newLookAndFeel);
	}
	void CommonList::paint(juce::Graphics& g)
	{
		if (viewType == mt::Ignite::DailogViewType::CustomView)
		{
			g.setColour(juce::Colour(ui::Theme::Instance().getColour(customBlue15)));
			if (ctrOpt)
			{
				g.fillRoundedRectangle(0, 0, (float)getWidth(), (float)(getHeight()), 3.0f);
				g.setColour(ui::Theme::Instance().getColour(customBlue14));
				g.fillRoundedRectangle(1.0f, 1.0f, (float)getWidth() - 2, (float)getHeight(), 3.0f);
				g.setColour(juce::Colour(ui::Theme::Instance().getColour(customBlue14)).withAlpha(0.5f));
				g.fillRect(0, 70, (int)getWidth(), 1);
				g.setColour(juce::Colour(ui::Theme::Instance().getColour(customBlue15)));
				g.fillRect(0, 70, (int)getWidth(), 1);

			}
			else
			{
				g.fillRect(0, 0, (int)getWidth(), (int)getRequiredHeight() - 140);
				g.setColour(ui::Theme::Instance().getColour(customBlue14));
				g.fillRect(2, 2, getWidth() - 4, getRequiredHeight() - 145);
			}
		}
		else
		{
			g.fillAll(ui::Theme::Instance().getColour(neutralGrey4));
		}
	};

	void CommonList::resized()
	{
		if (getLocalBounds().isEmpty())
			return;

		auto b = getLocalBounds().reduced(10);

		const auto spaceW{ 5 }, spaceH{ 5 };
		auto w = (b.getWidth() - (spaceW * (noOfColumns - 1)) - 10) / (noOfColumns);
		auto noOfRows = (int)(options.size() / noOfColumns) + 1;
		auto h = juce::jlimit(40, 40, (b.getHeight() - (spaceW * (noOfRows - 1))) / (noOfRows));

		int column = 0, x = b.getX() + 3, y = b.getY();
		if (viewType == mt::Ignite::DailogViewType::CustomView)
		{
			listTitle.setBounds(0, 5, b.getWidth(), 58);
			closeBtn.setBounds(getWidth() - 50, 20, 30, 20);
			y = +88;
		}
		for (auto opt : options)
		{
			opt->setBounds(x, y, w, h);
			x += (w + spaceW);
			if (++column >= noOfColumns)
			{
				x = b.getX() + 3;
				y += (h + spaceH);
				column = 0;
			}
		}
	}


	void CommonList::deleteAndFree()
	{
		for (auto opt : options)
		{
			opt->setBounds(0, 0, 0, 0);
		}
		options.clearQuick();
	}

	void CommonList::buttonClicked(juce::Button* button)
	{
		selection = options.indexOf(dynamic_cast<CommonToggleButton*>(button));
		if (button->getToggleState() && onSelectionChanged)
			onSelectionChanged(selection);
		if (!ctrOpt)
			if (auto dw = getCurrentlyModalComponent())
				dw->exitModalState(selection);
		if (button == &closeBtn)
		{
			isDialogOpen = false;
			view.reset();
			setSelected(preSelection);
			if (auto dw = getCurrentlyModalComponent())
			{
				dw->exitModalState(preSelection);
				//CommonUtils::close();
				CommonUtils::SetUtilsVisiblity(false);
			}

		}
	};

	void CommonList::show(const String& Title, std::function<void(int)> CallbackOnExit)
	{
		if (!isDialogOpen.get())
		{
			if(onDailogTrigger)
				onDailogTrigger(true);
			if (viewType == mt::Ignite::DailogViewType::CustomView)
			{
				auto noOfRows = (int)(options.size() / noOfColumns) + 1;
				isDialogOpen = true;
				view.reset(new CommonViewport());
				if (NUM_ROW_FOR_SCROLL > noOfRows)
					view->setScrollBarsShown(false, false, false);
				else
					view->setScrollBarsShown(false, true, true, true);
				view->setBounds(bounds);
				auto h = jmax(bounds.getHeight(), getRequiredHeight());
				setSize(bounds.getWidth(), h);
				view->setScrollOnDragMode(Viewport::ScrollOnDragMode::all);

				view->setViewedComponent(this, false);
				preSelection = selection;
				CommonUtils::showCustomDialog(Title.length() ? Title : title, view.get(), [this, CallbackOnExit](int r)
					{

						isDialogOpen = false;
						view.reset();
						if (r == 0 && ctrOpt)
						{
							setSelected(preSelection);
							onSelectionChanged(preSelection);
						}
						else if (r == 2 && ctrOpt)
						{
							setSelected(0);
							if (onApplyValueChanged)
								onApplyValueChanged(-1);
						}
						else
						{
							if (onApplyValueChanged)
								onApplyValueChanged(selection);
						}
						if(onDailogTrigger)
							onDailogTrigger(false);
						CommonUtils::close();
					}, bounds, ctrOpt, titleHeight, Theme::Instance().getColour(transparentBlack), showResetBtn? true:false);
				//Front panel code Disabled till Assert integration
				//TODO: commented to fix first element highlight issue (front pannel)
			//	options[currentFocus]->setOutlineColour((Colour(0xFFFFFFFF).withBrightness(1.0f)));
			}
			else
			{
				view.reset();
				isDialogOpen = true;
				view.reset(new Viewport());
				view->setBounds(bounds);
				auto h = jmax(bounds.getHeight(), getRequiredHeight());
				setSize(bounds.getWidth(), h);
				view->setScrollOnDragMode(Viewport::ScrollOnDragMode::all);
				view->setScrollBarsShown(true, true);
				view->setViewedComponent(this, false);

				CommonUtils::showDialog(Title.length() ? Title : title, view.get(), [this](int r)
					{
						isDialogOpen = false;
						if(onDailogTrigger)
							onDailogTrigger(false);
					});
			}
			
		}
	}
	bool CommonList::FPKeyHandler(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		for (int i = 0; i < options.size(); i++)
		{
			options[i]->setOutlineColour(Theme::Instance().getColour(customBlue15));
		}

		switch ((FrontPannelParam)param)
		{
		case FrontPannelParam::paramKey_RMOVELEFT:
			currentFocus = (currentFocus + 1 > (int)(options.size() - 1) ? (int)(options.size() - 1) : currentFocus + 1);
			options[currentFocus]->setOutlineColour(Theme::Instance().getColour(customOrange));
			break;
		case FrontPannelParam::paramKey_RMOVERIGHT:
			currentFocus = (currentFocus - 1 < 0 ? 0 : currentFocus - 1);
			options[currentFocus]->setOutlineColour(Theme::Instance().getColour(customOrange));
			break;
		case FrontPannelParam::paramKey_RSELECT:
			if (KeyValue == (uint32)FrontPannelKeyStatus::paramKeyStatusPressed)
			{
				setSelected(currentFocus);
				this->postCommandMessage(1);
			}
			break;
		case FrontPannelParam::paramKey_RETURN_NAV:
			this->postCommandMessage(2);
			break;
		}
		return true;
	}
	void CommonList::handleCommandMessage(int id)
	{
		buttonClicked(options[currentFocus]);

		if (ctrOpt)
		{

			if (auto dw = getCurrentlyModalComponent())
				dw->exitModalState((id == 1 ? (shiftKeyStatus? 2: 1) : 0));
			CommonUtils::SetUtilsVisiblity(false);
			CommonUtils::close();
		}
	}

	void CommonList::setBackgroundColourForRange(int range, Colour c)
	{
		for (int i = 0; i < range; i++)
			options[i]->setBackgroundColour(c);

		for (int i = range; i < options.size(); i++)
			options[i]->setBackgroundColour(Theme::Instance().getColour(transparentBlack));
	}

	void CommonList::setBackgroundColour(Colour c)
	{
		for (int i = 0; i < options.size(); i++)
			options[i]->setBackgroundColour(c);
	}

	void CommonList::setTextColour(Colour c)
	{
		for (int i = 0; i < options.size(); i++)
			options[i]->setTextColour(c);
	}

	//////////////////////
	/// COMMON List Box
	//////////////////////

	CommonListBox::CommonListBox(const String& Title, int NumColumns, bool showRstBtn)
		: CommonListBox(Title, {}, 0, NumColumns, showRstBtn)
	{}

	CommonListBox::CommonListBox(const String& Title, const std::vector<juce::String>& Options, int Selected, int NumColumns, bool showRstBtn)
		: CommonListBox(BoxType::withTitleBar, Title, Options, Selected, NumColumns, showRstBtn)
	{}

	CommonListBox::CommonListBox(BoxType Type, const String& Title, const std::vector<juce::String>& Options, int Selected, int NumColumns, bool showRstBtn)
		: type(Type), list(Title, Options, Selected, NumColumns, showRstBtn)
	{
		c.flexDirection = FlexBox::Direction::column;
		title.setColour(juce::Label::textColourId, juce::Colour(ui::color::system::yellow));

		this->setPaintingIsUnclipped(true);
		this->setInterceptsMouseClicks(true, true);
		title.setInterceptsMouseClicks(false, false);
		value.setInterceptsMouseClicks(false, false);
		value.setDisplayDropDown(true);

		// Setup defaults...
		title.setText(Title, dontSendNotification);
		value.setText(list.getSelected(), dontSendNotification);
		value.setTextFont(25);

		addMouseListener(this, true);

		// Perform Layout...
		setDisplayFormat(type);

		list.onSelectionChanged = [this](int Selection)
		{
			if (Selection >= 0)
			{
				auto selectedText = list.getSelected();
				value.setText(selectedText, dontSendNotification);

				if (onValueChanged)
					onValueChanged(selectedText);
				if (onSelectionChanged)
					onSelectionChanged(Selection, selectedText);
				if(onSelectionChangedWithName)
					onSelectionChangedWithName(Selection, selectedText, this->title.getText());
			}
			if (isDialogOpen.get())
			{
				if (auto dw = getCurrentlyModalComponent())
					dw->exitModalState(Selection);
			}
		};

		list.onApplyValueChanged = [this](int Selection)
		{
			auto selectedText = list.getSelected();
			value.setText(selectedText, dontSendNotification);
			if (onApplyValueChanged)
				onApplyValueChanged(Selection, selectedText);
		};

		list.onDailogTrigger = [this](bool status)
		{
			if (onDailogTrigger)
				onDailogTrigger(status);
		};
		normalImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("item-bg-modallink-122x80-default.png"));
		overImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("item-bg-modallink-122x80-default-hover.png"));
	}

	void CommonListBox::setTitleColour(juce::Colour col)
	{
		title.setTextColour(col);
	}

	void CommonListBox::setValueColour(juce::Colour col)
	{
		value.setTextColour(col);
	}

	void CommonListBox::setDisplayFormat(BoxType Format)
	{
		type = Format;

		removeAllChildren();
		c.items.clear();
		box.items.clear();
		
		// Central Layout.
		if (type == BoxType::withTitleBar || type == BoxType::withTitleBarWithNavigationButtons)
		{
			// Display Title
			title.makeVisible(this);
			c.items.add(FlexItem(title).withFlex(2));
		}

		// Display Value.
		value.makeVisible(this);
		if (type != BoxType::withTitleBottom)
			c.items.add(FlexItem(value).withFlex(5));


		if (type == BoxType::withoutTitleBarWithNavigationButtons || type == BoxType::withTitleBarWithNavigationButtons)
		{ // Minus - Central - Plus
			plus.makeVisibleAndAddListner(this);
			minus.makeVisibleAndAddListner(this);
			title.setJustificationType(Justification::centred);
			value.setJustificationType(Justification::centred);
			box.items.add(FlexItem(minus).withFlex(2));
			box.items.add(FlexItem(c).withFlex(6));
			box.items.add(FlexItem(plus).withFlex(2));
		}
		else if (type == BoxType::withTitleBottom)
		{
			title.makeVisible(this);
			title.setJustificationType(Justification::centred);
			value.setJustificationType(Justification::centred);
		}
		else // Only Central layout.
			box.items.add(FlexItem(c).withFlex(10));

		resized();
	}

	String CommonListBox::getSelectedValue(void)
	{
		return value.getText();
	}

	const String& CommonListBox::getSelected()
	{
		return list.getSelected();
	}

	int CommonListBox::getSelectedIndex()
	{
		return list.getSelectedIndex();
	}

	void CommonListBox::setSelected(const String& O)
	{
		list.setSelected(O);
		value.setText(list.getSelected(), dontSendNotification);
	}

	void CommonListBox::setSpecificString(const String& s)
	{
		value.setText(s, dontSendNotification);
	}

	void CommonListBox::setTitleText(const String& O)
	{
		title.setText(O, dontSendNotification);
	}

	void CommonListBox::setSelected(int O)
	{
		list.setSelected(O);
		value.setText(list.getSelected(), dontSendNotification);
	}

	void CommonListBox::clearSelected(int O)
	{
		list.clearSelected(O);
	}

	void CommonListBox::updateListOptions(const std::vector<juce::String>& Options, int selectedIndex)
	{
		list.setContent(Options, selectedIndex);
	}

	void CommonListBox::updateListOptionsWithSize(const std::vector<juce::String>& Options, int size, int selectedIndex)
	{
		std::vector<juce::String> OptionsList;
		OptionsList.clear();
		for (auto i = 0; i < size; i++)
		{
			OptionsList.push_back(Options[i]);
		}
		list.setContent(OptionsList, selectedIndex);
	}

	void CommonListBox::makeVisible(Component* Parent)
	{
		Parent->addAndMakeVisible(dynamic_cast<Component&>(*this));
	}

	void CommonListBox::showList()
	{
		if (isEditable)
		{
			list.show();
		}
	}

	void CommonListBox::mouseDown(const MouseEvent&)
	{
		if (isEditable)
		{
			list.show();
		}
	}

	void CommonListBox::mouseDoubleClick(const juce::MouseEvent& e)
	{
		if (isEditable)
			list.show();
	}

	void CommonListBox::resized()
	{
		auto b = getLocalBounds();
		box.performLayout(getLocalBounds());
		if (type == BoxType::withTitleBottom && !iscustombound)
		{
			value.setBounds(0, (int)((b.getY() + getHeight()) * 0.2), (int)getLocalBounds().getWidth(), 35);
			title.setBounds(0, (int)((b.getY() + getHeight()) * 0.6), (int)getLocalBounds().getWidth(), 22);
		}
		else if (iscustombound)
		{
			value.setBounds(valueBounds);
			title.setBounds(titleBounds);
		}

	}

	void CommonListBox::buttonClicked(juce::Button* button)
	{
		if (button == &minus)
			setSelected(getSelectedIndex() - 1);
		if (button == &plus)
			setSelected(getSelectedIndex() + 1);
	}

	void CommonListBox::paint(juce::Graphics& g)
	{
		auto bounds = getLocalBounds();
		auto cornerSize = 6.0f;

		if (bShouldDraw)
		{
			auto ImageToDraw = getFocusState() ? overImage : normalImage;
			g.drawImage(ImageToDraw, bounds.toFloat());
		}

		g.setColour(ui::Theme::Instance().getColour(customBlue12));
		if (layoutType)
		{
			auto flatOnLeft = layoutType & ConnectedOnLeft;
			auto flatOnRight = layoutType & ConnectedOnRight;
			auto flatOnTop = layoutType & ConnectedOnTop;
			auto flatOnBottom = layoutType & ConnectedOnBottom;
			if (flatOnLeft || flatOnRight || flatOnTop || flatOnBottom)
			{
				Path path;
				path.addRoundedRectangle((float)bounds.getX(), (float)bounds.getY(),
					(float)bounds.getWidth(), (float)bounds.getHeight(),
					cornerSize, cornerSize,
					!(flatOnLeft || flatOnTop),
					!(flatOnRight || flatOnTop),
					!(flatOnLeft || flatOnBottom),
					!(flatOnRight || flatOnBottom));

				g.fillPath(path);

				g.setColour(ui::Theme::Instance().getColour(neutralWhite));
				g.strokePath(path, PathStrokeType(1.0f));
			}
			else
			{
				g.fillRoundedRectangle(ui::Rectangle{ (float)bounds.getX(),(float)bounds.getY(),(float)bounds.getWidth(),(float)bounds.getHeight() }, cornerSize);

				g.setColour(ui::Theme::Instance().getColour(neutralWhite));
				g.drawRoundedRectangle(ui::Rectangle{ (float)bounds.getX(),(float)bounds.getY(),(float)bounds.getWidth(),(float)bounds.getHeight() }, cornerSize, 1.0f);
			}
		}
	}
	void CommonListBox::handleCommandMessage(int id)
	{
		if (id == 1)
		{
			list.currentFocus = list.getSelectedIndex();
			list.show();
		}
		else if (id == 2)
		{
			auto selectedIndex = (getSelectedIndex() - 1) < 0 ? 0 : (getSelectedIndex() - 1);
			setSelected(selectedIndex);
			if(list.onSelectionChanged)
				list.onSelectionChanged(selectedIndex);
			if(list.onApplyValueChanged)
				list.onApplyValueChanged(selectedIndex);
		}
		else if (id == 3)
		{
			auto selectedIndex = (getSelectedIndex() + 1) > (int)(list.getSize() - 1) ? (int)(list.getSize() - 1) : (getSelectedIndex() + 1);
			setSelected(selectedIndex);
			if (list.onSelectionChanged)
				list.onSelectionChanged(selectedIndex);
			if (list.onApplyValueChanged)
				list.onApplyValueChanged(selectedIndex);
		}
		else if (id == 4)
		{
			auto selectedIndex = (getSelectedIndex() + 1) > (int)(list.getSize() - 1) ? 0 : (getSelectedIndex() + 1);
			setSelected(selectedIndex);
			if (list.onSelectionChanged)
				list.onSelectionChanged(selectedIndex);
			if (list.onApplyValueChanged)
				list.onApplyValueChanged(selectedIndex);
		}
	}

	bool CommonListBox::FPKeyHandler(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		if (param == (paramId_t)FrontPannelParam::paramKey_MINUS_NAV)
		{
			if (isFocuse)
			{
				this->postCommandMessage(2);
				return true;
			}
		}
		else if (param == (paramId_t)FrontPannelParam::paramKey_PLUS_NAV)
		{
			if (isFocuse)
			{
				this->postCommandMessage(3);
				return true;
			}
		}

		if (isFocuse)
			setFocus(true);
		else
			setFocus(false);

		if (!IsEditing())
		{
			switch ((FrontPannelParam)param)
			{
			case FrontPannelParam::paramKey_ROTARYROW:
				if ((FrontPannelKeyStatus)KeyValue == FrontPannelKeyStatus::paramKeyStatusPressed)
					this->postCommandMessage(4);
				break;
			case FrontPannelParam::paramKey_MouseClick:
			case FrontPannelParam::paramKey_RMOVELEFT:
			case FrontPannelParam::paramKey_RMOVERIGHT://Fallthrough
				//Navigation Focus
				break;
			case FrontPannelParam::paramKey_RSELECT:
				if (KeyValue == (uint32)FrontPannelKeyStatus::paramKeyStatusPressed && isFocuse)
					this->postCommandMessage(1);
				break;
			}
		}
		else
		{
			list.FPKeyHandler(isFocuse, param, KeyValue);
		}
		return true;
	}

	void CommonListBox::mouseMove(const MouseEvent& event)
	{
#if PHY_MOUSE_OVER
		if (focusState != true)
		{
			focusState = true;
			if (onFocusChanged)
				onFocusChanged(true);

		}
#endif
	}

	void CommonListBox::mouseExit(const MouseEvent& event)
	{
#if PHY_MOUSE_OVER
		if (focusState != false)
		{
			focusState = false;
			if (onFocusChanged)
				onFocusChanged(false);
		}
#endif
	}

	void CommonListBox::setFocus(bool s)
	{
		if (focusState != s)
		{
			focusState = s;
			if (onFocusChanged)
				onFocusChanged(s);
		}
	}

	void CommonListBox::setcustombounds(bool state, Rectangle<int> a, Rectangle<int> b)
	{
		iscustombound = state;
		valueBounds = a;
		titleBounds = b;
	}

};
