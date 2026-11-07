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
	class IgniteControlOptions;
	CommonPopUp::CommonPopUp(const juce::String& Title, int Width, int Height) :
		progressBarComp(nullptr)
	{
		width = Width;
		height = Height;
		title.makeVisible(this);
		closeBtn.makeVisible(this);
		closeBtn.addListener(this);
		title.setJustificationType(Justification::centred);
		title.setText(Title, dontSendNotification);
		setSize(Width, Height);
	}

	CommonPopUp::CommonPopUp()
	{

	}

	CommonPopUp::~CommonPopUp()
	{
		listofBtns.clear();
		delete dialogWindow;
	}

	void CommonPopUp::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &closeBtn)
		{
			isDialogOpen = false;
			close();
			CommonUtils::SetUtilsVisiblity(false);
		}
	}

	void CommonPopUp::close()
	{
		if (auto dw = getCurrentlyModalComponent())
		{
			dw->exitModalState(0);
		}

		
		width = 0;
		height = 0;
		title.setText("", dontSendNotification);
		info = "";
		Endline = true;
		setSize(width, height);
		for (int i = 0; i < listofImageBtns.size(); i++)
			listofImageBtns[i]->setBounds(ui::Rectangle<int>{0, 0, 0, 0});

		for (int i = 0; i < listofBtns.size(); i++)
			listofBtns.getReference(i)->setBounds(0, 0, 0, 0);
		listofImageBtns.clear();
		listofBtns.clear();
		ctlBox.items.clear();
		isDialogOpen = false;
		if (ispreloader)
		{
			exitModalState(0);
			ispreloader = false;
			CommonUtils::close();
		}
		retValue = false;
		if (isTimerRunning)
		{
			isTimerRunning = false;
			stopTimer();
		}
		autohide = false;
	}
	void CommonPopUp::showPreloader( String Title,String Info)
	{
		ispreloader = true;
		info = Info;
		title.setText(Title, dontSendNotification);
		Endline = false;
		preloaderImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("preloader-img-1.png"));
		this->repaint();
		preloaderCount = 1;
		setSize(604, 350);
		isTimerRunning = true;
		startTimer(200);

		std::function<void(int)> CallbackOnExit;
		isDialogOpen=true;
		CommonUtils::showCustomDialog("Copy", this, [this, CallbackOnExit](int r) {

			if (CallbackOnExit)
				CallbackOnExit(r);

			//isDialogOpen = false;
			}, ui::Rectangle<int>{0, 0, 604, 350}, false, heightDailogTitle, Theme::Instance().backgroundColour(5).withAlpha(.25f),false,true);

	}

	void CommonPopUp::paint(juce::Graphics& g)
	{
		
		if (!ispreloader)
		{
			juce::Rectangle <float>a{ (float)0,(float)0,(float)getWidth(),(float)getHeight() };
			Image dropImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("modal-container-4.png"));
			g.drawImage(dropImage, a, RectanglePlacement::centred);
			g.setColour(Theme::Instance().getColour(customGrey5));
			g.drawHorizontalLine(65, 0, 605);
			g.setColour(Theme::Instance().getColour(neutralWhite).withAlpha(0.75f));
			g.setFont(18.0f);
			if (!newButton)
				g.drawFittedText(info, ui::Rectangle{ 10,98,getWidth(),50 }, Justification::centred, 1);
			g.setColour(Theme::Instance().getColour(customGrey5));
			if (Endline)
				g.drawHorizontalLine(getHeight() - 90, 0, 605);
		}
		else
		{
			g.drawImage(preloaderImage, ui::Rectangle<float>{230,110,114,114}, RectanglePlacement::stretchToFit);
			g.setColour(Theme::Instance().getColour(neutralWhite).withAlpha(0.75f));
			g.setFont(22.0f);
			g.drawFittedText(info, ui::Rectangle{ 0,230,getWidth(),60 }, Justification::centred, 1);
		}

	}

	void CommonPopUp::resized()
	{
		auto b = getLocalBounds();

		if (newButton)
		{
			auto ctropt = b.removeFromBottom(10);
			ctlBox.performLayout(ui::Rectangle<float>{(float)(ctropt.getX()) + 30, (float)ctropt.getY() - 140, (float)ctropt.getWidth() - 60, (float)120});
			newButton = false;
		}
		else
		{
			auto ctropt = b.removeFromBottom(74);
			ctlBox.performLayout(ui::Rectangle<float>{(float)(ctropt.getX()) + 30, (float)ctropt.getY(), (float)ctropt.getWidth() - 60, (float)44});
		}
		title.setBounds(15, 10, getWidth() - 30, 50);
		if(!ispreloader)
			closeBtn.setBounds(getWidth() - 50, 25, 25, 25);
		/*if (progressBarComp)
			progressBarComp->setBounds(10, 155, getWidth() - 20, 30);*/
	}

	CommonButton* CommonPopUp::addButton(const String BtnName, const int returnValue)
	{
		ui::CommonButton* ptr = new ui::CommonButton(BtnName);
		addAndMakeVisible(ptr);
		ptr->showTitleAndBorder(true);
		ptr->setCommandToTrigger(nullptr, returnValue, false);
		ptr->onClick = [this, ptr] { exitAlert(ptr); };
		ctlBox.items.add(FlexItem(*ptr).withMargin(8).withFlex(1).withHeight((float)btnH).withWidth((float)btnW));
		listofBtns.add(ptr);
		resized();
		return ptr;
	}

	CommonButton* CommonPopUp::addButtonWithBounds(const String BtnName, const int returnValue, ui::Rectangle<int> b)
	{
		ui::CommonButton* ptr = new ui::CommonButton(BtnName);
		addAndMakeVisible(ptr);
		ptr->showTitleAndBorder(true);
		ptr->setCommandToTrigger(nullptr, returnValue, false);
		ptr->onClick = [this, ptr] { exitAlert(ptr); };
		ptr->setBounds(b);
		listofBtns.add(ptr);
		resized();
		return ptr;
	}

	CommonButton* CommonPopUp::addButtonNew(const String BtnName, const int returnValue)
	{
		ui::CommonButton* ptr = new ui::CommonButton(BtnName);
		addAndMakeVisible(ptr);
		ptr->showTitleAndBorder(true);
		ptr->setCommandToTrigger(nullptr, returnValue, false);
		ptr->onClick = [this, ptr] { exitAlert(ptr); };
		ctlBox.alignItems = FlexBox::AlignItems::center;
		ctlBox.flexDirection = juce::FlexBox::Direction::column;
		ctlBox.flexWrap = juce::FlexBox::Wrap::wrap;
		ctlBox.items.add(FlexItem(*ptr).withMargin(10).withFlex(1).withHeight((float)btnH).withWidth((float)btnW));
		listofBtns.add(ptr);
		newButton = true;
		resized();
		return ptr;
	}

	CommonImageButton* CommonPopUp::addImageButton(String BtnName, String defaultImage, String activeImage, const int returnValue)
	{
		ui::CommonImageButton* ptr = new ui::CommonImageButton(BtnName, defaultImage, activeImage, activeImage);
		addAndMakeVisible(ptr);
		ptr->setCommandToTrigger(nullptr, returnValue, false);
		ptr->onClick = [this, ptr] { exitAlert(ptr); };
		ctlBox.items.add(FlexItem(*ptr).withFlex(1).withHeight((float)btnH).withWidth((float)btnW));
		listofImageBtns.add(ptr);
		resized();
		return ptr;
	}

	CommonImageButton* CommonPopUp::addImageButtonwithBounds(String BtnName, String defaultImage, String activeImage, String hoverImage, const int returnValue, ui::Rectangle<int> b)
	{
		ui::CommonImageButton* ptr = new ui::CommonImageButton(BtnName, defaultImage, activeImage, hoverImage);
		addAndMakeVisible(ptr);
		ptr->setCommandToTrigger(nullptr, returnValue, false);
		ptr->onClick = [this, ptr] { exitAlert(ptr); };
		ptr->setBounds(b);
		listofImageBtns.add(ptr);
		resized();
		return ptr;
	}

	CommonImageButton* CommonPopUp::addDisabledImageButtonwithBounds(String BtnName, String defaultImage, String activeImage, String hoverImage, const int returnValue, ui::Rectangle<int> b)
	{
		ui::CommonImageButton* ptr = new ui::CommonImageButton(BtnName, defaultImage, activeImage, hoverImage);
		addAndMakeVisible(ptr);
		ptr->setCommandToTrigger(nullptr, returnValue, false);
		ptr->setBounds(b);
		listofImageBtns.add(ptr);
		resized();
		return ptr;
	}

	void CommonPopUp::addProgressBar(double& progress)
	{
		progressBarComp = new ui::CommonProgressBar(progress);
		progressBarComp->setColour(juce::ProgressBar::foregroundColourId, Theme::Instance().getColour(customOrange));
		addAndMakeVisible(progressBarComp);
		resized();
	}

	void CommonPopUp::setProgressBar(double& progress)
	{
		progressBarComp->updateProgress(progress);
	}

	void CommonPopUp::removeProgressBar()
	{
		progressBarComp->setVisible(false);
	}

	void CommonPopUp::exitAlert(Button* button)
	{
		onSelectionChanged(button->getCommandID());
		CommonUtils::SetUtilsVisiblity(false);
		if(retValue)
			onActionReturnvalue(button->getCommandID());
	}

	void CommonPopUp::show()
	{
		if (!isDialogOpen.get())
		{
			std::function<void(int)> CallbackOnExit;
			isDialogOpen = true;
			view.reset(new CommonViewport());
			view->setScrollBarsShown(false, false, false);
			view->setSize(width, height);
			view->setScrollOnDragMode(Viewport::ScrollOnDragMode::all);
			/*if (!listofImageBtns.size() && !listofBtns.size())
				timeinms = 2000;*/
			if (autohide)
			{
				startTimer(timeinms);
				isTimerRunning = true;
			}
			CommonUtils::showCustomDialog("Copy", this, [this, CallbackOnExit](int r) {

				if (CallbackOnExit)
					CallbackOnExit(r);
				
				isDialogOpen = false;
				}, ui::Rectangle<int>{0, 0, width, height}, false);
		}
	}

	bool CommonPopUp::isEditing()
	{
		if ((KeyFocusedItem == SAVE_BACKUP) ||
			(KeyFocusedItem == SAVE_BACKUP_USB) ||
			(KeyFocusedItem == LOAD_BACKUP) ||
			(KeyFocusedItem == LOAD_BACKUP_USB))
			return false;
		else
			return true;
	}


	bool CommonPopUp::FPKeyHandler(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		if (popupType == POPUP_WITHOKCANCEL || popupType == POPUP_WITHOK || popupType == POPUP_WITHCLOSE || popupType == POPUP_RESET || popupType == POPUP_WIPEDATA)
		{
			if (!isFocuse)
				return true;

			switch ((FrontPannelParam)param)
			{
			case FrontPannelParam::paramKey_RSELECT:
				if (KeyValue == (uint32)FrontPannelKeyStatus::paramKeyStatusPressed)
				{
					this->postCommandMessage(1);
					if(popupType == POPUP_RESET)
						this->postCommandMessage(3);
				}
				break;
			case FrontPannelParam::paramKey_RETURN_NAV:
				if (KeyValue == (uint32)FrontPannelKeyStatus::paramKeyStatusPressed)
					this->postCommandMessage(2);
				break;
			}
		}
		else if (popupType == POPUP_BACKUP)
		{
			bool setfocus = true;
			int editItem = backupItemID::NO_FOCUS;

			if (KeyFocusedItem == backupItemID::NO_FOCUS)
			{
				/*1st key after Page visible */
				KeyFocusedItem = backupItemID::SAVE_BACKUP;
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
					case FrontPannelParam::paramKey_RETURN_NAV:
						this->postCommandMessage(2);
						break;
					case FrontPannelParam::paramKey_RMOVELEFT:
						KeyFocusedItem = (KeyFocusedItem + 1 >= backupItemID::FOCUS_MAX ? (backupItemID::FOCUS_MAX) : KeyFocusedItem + 1);
						break;
					case FrontPannelParam::paramKey_RMOVERIGHT:
						KeyFocusedItem = (KeyFocusedItem - 1 <= backupItemID::NO_FOCUS ? (backupItemID::NO_FOCUS + 1) : KeyFocusedItem - 1);
						break;
					}
				}
			}
			if (setfocus)
			{
				PannelSendKey(true, param, KeyValue);
			}
		}
		else if (popupType == POPUP_CHANGEWARNING)
		{
			PannelSendKey(false, param, KeyValue);
			if (WarningFocusedItem == warningItemID::WARNING_NO_FOCUS)
			{
				/*1st key after Page visible */
				WarningFocusedItem = warningItemID::CANCEL;
			}
			else
			{
				if (!isFocuse)
					return true;

				switch ((FrontPannelParam)param)
				{
				case FrontPannelParam::paramKey_RETURN_NAV:
					this->postCommandMessage(2);
					break;
				case FrontPannelParam::paramKey_RMOVELEFT:
					WarningFocusedItem = (WarningFocusedItem + 1 >= warningItemID::WARNING_FOCUS_MAX ? (warningItemID::WARNING_FOCUS_MAX) : WarningFocusedItem + 1);
					break;
				case FrontPannelParam::paramKey_RMOVERIGHT:
					WarningFocusedItem = (WarningFocusedItem - 1 <= warningItemID::WARNING_NO_FOCUS ? (warningItemID::WARNING_NO_FOCUS + 1) : WarningFocusedItem - 1);
					break;
				}
			}
			PannelSendKey(true, param, KeyValue);

		}

		else if (popupType == POPUP_POWERCTL)
		{
			PannelSendKey(false, param, KeyValue);
			if (powerCtlFocusedItem == powerControlItemID::POWERCTL_WITH_NO_FOCUS)
			{
				/*1st key after Page visible */
				powerCtlFocusedItem = powerControlItemID::PWRCTL_CANCEL;
			}
			else
			{
				if (!isFocuse)
					return true;

				switch ((FrontPannelParam)param)
				{
				case FrontPannelParam::paramKey_RETURN_NAV:
					this->postCommandMessage(2);
					break;
				case FrontPannelParam::paramKey_RMOVELEFT:
					powerCtlFocusedItem = (powerCtlFocusedItem + 1 >= powerControlItemID::POWERCTL_FOCUS_MAX ? (powerControlItemID::POWERCTL_FOCUS_MAX) : powerCtlFocusedItem + 1);
					break;
				case FrontPannelParam::paramKey_RMOVERIGHT:
					powerCtlFocusedItem = (powerCtlFocusedItem - 1 <= powerControlItemID::POWERCTL_WITH_NO_FOCUS ? (powerControlItemID::POWERCTL_WITH_NO_FOCUS + 1) : powerCtlFocusedItem - 1);
					break;
				}
			}
			if (KeyValue == (uint32)FrontPannelKeyStatus::paramKeyStatusPressed)
				PannelSendKey(true, param, KeyValue);

		}

		return true;
	}

	void CommonPopUp::PannelSendKey(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		if (param == (paramId_t)FrontPannelParam::paramKey_RSELECT && (KeyValue == (uint8_t)FrontPannelKeyStatus::paramKeyStatusReleased))
			return;

		if (popupType == POPUP_BACKUP)
		{
			switch (backupItem[KeyFocusedItem])
			{
			case SAVE_BACKUP:
				listofImageBtns[0]->FPKeyHandler(isFocuse, param, KeyValue);
				break;
			case LOAD_BACKUP:
				listofImageBtns[1]->FPKeyHandler(isFocuse, param, KeyValue);
				break;
			case SAVE_BACKUP_USB:
				if (listofImageBtns[2]->isEnabled())
				{
					listofImageBtns[2]->FPKeyHandler(isFocuse, param, KeyValue);
				}
				else
				{
					if (param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT)
						KeyFocusedItem++;
					else
						KeyFocusedItem--;

					PannelSendKey(isFocuse, param, KeyValue);
				}
				break;
			case LOAD_BACKUP_USB:
				if (listofImageBtns[3]->isEnabled())
				{
					listofImageBtns[3]->FPKeyHandler(isFocuse, param, KeyValue);
				}
				else
				{
					if (param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT)
						KeyFocusedItem++;
					else
						KeyFocusedItem--;

					PannelSendKey(isFocuse, param, KeyValue);
				}
				break;
			}
		}
		else
		{
			switch (warningItem[WarningFocusedItem])
			{
			case CANCEL:
				listofImageBtns[0]->FPKeyHandler(isFocuse, param, KeyValue);
				break;
			case CONFIRM_SWITCH:
				listofImageBtns[1]->FPKeyHandler(isFocuse, param, KeyValue);
				break;
			case SAVE_SWITCH:
				listofImageBtns[2]->FPKeyHandler(isFocuse, param, KeyValue);
				break;
			}
		}
		repaint();
	}

	void CommonPopUp::handleCommandMessage(int id)
	{
		if (id == 2)
		{
			if (popupType == POPUP_WITHCLOSE || popupType == POPUP_BACKUP)
				closeBtn.triggerClick();
			else
				onSelectionChanged(id);
			CommonUtils::SetUtilsVisiblity(false);
		}
		else if (id == 3)
		{
			onActionReturnvalue(1);
		}
		else
		{
			onSelectionChanged(id);
			CommonUtils::SetUtilsVisiblity(false);
		}
	}

	void CommonPopUp::timerCallback()
	{
		if (ispreloader)
		{
			preloaderCount++;

			if (preloaderCount > 8)
			{
				preloaderCount = 1;
			}
			preloaderImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("preloader-img-" + (String)preloaderCount + (String)".png"));
			repaint();
		}
		else
		{
			close();
			CommonUtils::SetUtilsVisiblity(false);
		}
	}

	void CommonPopUp::setPopUpPropories(const juce::String& Title, int Width, int Height)
	{
		width = Width;
		height = Height;
		title.makeVisible(this);
		closeBtn.makeVisible(this);
		closeBtn.addListener(this);
		title.setJustificationType(Justification::centred);
		title.setText(Title, dontSendNotification);
		setSize(width, height);
		repaint();
		resized();
	}

	CommonWarningPopUp::CommonWarningPopUp(String inf)
	{
		title.makeVisible(this);
#ifdef ENABLE_CLOSEBUTTON
		closeBtn.makeVisible(this);
		closeBtn.addListener(this);
#endif
		title.setJustificationType(Justification::centred);
		OkayBtn.makeVisible(this);
		OkayBtn.addListener(this);
		info.makeVisible(this);
		info.setText(inf, dontSendNotification);
		info.setJustificationType(Justification::centred);
#ifdef ENABLE_CLOSEBUTTON
		closeBtn.onClick = [this] { onSelectionChanged(1); };
#endif
		OkayBtn.onClick = [this] { onSelectionChanged(1); };
	}

	CommonWarningPopUp::CommonWarningPopUp()
	{
		title.makeVisible(this);
#ifdef ENABLE_CLOSEBUTTON
		closeBtn.makeVisible(this);
		closeBtn.addListener(this);
#endif
		title.setJustificationType(Justification::centred);
		OkayBtn.makeVisible(this);
		OkayBtn.addListener(this);
		info.makeVisible(this);
		info.setJustificationType(Justification::centred);

#ifdef ENABLE_CLOSEBUTTON
		closeBtn.onClick = [this] { onSelectionChanged(1); };
#endif
		OkayBtn.onClick = [this] { onSelectionChanged(1); OkayBtn.setToggleState(false, dontSendNotification); };
	}

	CommonWarningPopUp::~CommonWarningPopUp()
	{

	}

	void CommonWarningPopUp::paint(juce::Graphics& g)
	{
		Image Draw = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("modal-container-4.png"));
		g.drawImage(Draw, ui::Rectangle<float>{0, 0, 604, 290});
		Draw = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("ico-exclamation-modal.png"));
		g.drawImage(Draw, ui::Rectangle<float>{30, 15, 40, 40});
		g.setColour(ui::Theme::Instance().getColour(customBlue18));
		g.fillRect(ui::Rectangle{ 0, 72, getLocalBounds().getWidth(),  1 });
		g.fillRect(ui::Rectangle{ 0, 210, getLocalBounds().getWidth(),  1 });
	}
	void CommonWarningPopUp::resized()
	{
		title.setBounds(0, 5, 604, 58);
		info.setBounds(0, 110, getWidth(), 28);
		OkayBtn.setBounds(30, 230, 544, 44);
#ifdef ENABLE_CLOSEBUTTON
		closeBtn.setBounds(540, 18, 25, 25);
#endif
	}

	void CommonWarningPopUp::show()
	{
		if (!isDialogOpen.get())
		{
			std::function<void(int)> CallbackOnExit;
			isDialogOpen = true;
			resized();
			repaint();
			view.reset(new CommonViewport());
			view->setScrollBarsShown(false, false, false);
			view->setSize(604, 297);
			view->setScrollOnDragMode(Viewport::ScrollOnDragMode::all);
			CommonUtils::showCustomDialog("Copy", this, [this, CallbackOnExit](int r) {
				isDialogOpen = false;
				if (CallbackOnExit)
					CallbackOnExit(r);
				close();
				//view.reset();
				}, ui::Rectangle<int>{0, 0, 604, 297}, false);
		}
	}

	void CommonWarningPopUp::close()
	{
		//view.reset();
		info.setText("",dontSendNotification);
		OkayBtn.setBounds(0, 0, 0, 0);
		
		setVisible(false);
		CommonUtils::SetUtilsVisiblity(false);
		Component* dw = getCurrentlyModalComponent();
		if ((dw != nullptr) && isDialogOpen.get())
		{
			dw->exitModalState(0);
		}
		isDialogOpen = false;
	}

	void CommonWarningPopUp::setWarningText(String inf)
	{
		info.setText(inf, dontSendNotification);
		info.setJustificationType(Justification::centred);
	}

	void CommonWarningPopUp::buttonClicked(juce::Button* buttonThatWasClicked)
	{
#ifdef ENABLE_CLOSEBUTTON
		if (buttonThatWasClicked == &closeBtn)
		{
			isDialogOpen = false;
			close();
		}
#endif
	}

	bool CommonWarningPopUp::FPKeyHandler(bool isFocuse, paramId_t param, uint32_t KeyValue)
	{
		if (!isFocuse)
			return true;

		switch ((FrontPannelParam)param)
		{
		case FrontPannelParam::paramKey_RSELECT:
		case FrontPannelParam::paramKey_RETURN_NAV:
			this->postCommandMessage(1);
			break;
		}

		return true;
	}

	void CommonWarningPopUp::handleCommandMessage(int id)
	{
		close();
		onSelectionChanged(1);
	}

	CommonInfoWindow::CommonInfoWindow()
	{
		InfoBounds.setY(520);
		InfoBounds.setHeight(32);
		setInterceptsMouseClicks(false, false);
	}

	void CommonInfoWindow::setTextandShow(String Text)
	{
		text = Text;
		Font a((float)(15.0f));
		float l = static_cast<float>(a.getStringWidth(text));
		
		if (l > minWidth)
		{
			InfoBounds.setWidth(l);
			InfoBounds.setX(screenWidth - l);
		}
		else
		{
			l = static_cast<float>(minWidth);
			InfoBounds.setWidth(l);
			InfoBounds.setX(screenWidth - l);
		}
		
		stopTimer();
		startTimer(time);
		setVisible(true);
		repaint();
	}

	void CommonInfoWindow::paint(juce::Graphics& g)
	{
		g.setColour(ui::Theme::Instance().getColour(customBlue20));
		g.fillRoundedRectangle(InfoBounds, 2.0f);
		g.setColour(ui::Theme::Instance().getColour(customBlue21));
		g.drawRoundedRectangle(InfoBounds, 2, 2.0f);
		g.setColour(ui::Theme::Instance().getColour(neutralWhite));
		g.drawText(text, InfoBounds, Justification::centred);
	}

	void CommonInfoWindow::timerCallback()
	{
		setVisible(false);
		toFront(false);
		stopTimer();
		
	}
};
