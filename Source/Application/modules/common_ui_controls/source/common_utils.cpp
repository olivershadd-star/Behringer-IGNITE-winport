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
#include "ignite_ui/source/home/mt_ignite_mainmode.h"
#include "ignite_ui/source/common/mt_ignite_cntropt.h"

namespace ui
{
	enum BUTTONS
	{
		CANCEL = 0,
		APPLY,
		DELETE,
		OK
	};
} // namespace ui

namespace ui
{
	using compPeer = juce::ComponentPeer;

	class AppMainmode;
	class IgniteControlOptions;
	class dialogDisplayer;
	dialogDisplayer* Displayerptr= nullptr;

	class dialogDisplayer : public juce::Component
	{
	public:
		dialogDisplayer(bool ShowYesNoButtons, bool showResetButton, const juce::String& Title, juce::Component* Content, juce::Rectangle<int> bounds, juce::Colour backgroundColour) :
			showYesNoButtons(ShowYesNoButtons)
			, pCont(Content)
			, contentBackgroundColour(backgroundColour)
			, showResetButton(showResetButton)
		{
			if (showResetButton)
				CommonUtils::addAndMakeVisible(this, title, apply, cancel, resetButton);
			else
				CommonUtils::addAndMakeVisible(this, title, apply, cancel);

			setOpaque(true);

			title.setInterceptsMouseClicks(false, false);
			title.setText(Title.length() ? Title : pCont ? pCont->getName() : "", dontSendNotification);
			title.setJustificationType(Justification::centred);
			apply.onClick = [&]() { close(ui::APPLY); };
			cancel.onClick = [&]() { close(ui::CANCEL); };
			resetButton.onClick = [&]() { close(ui::DELETE); };
			apply.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
			cancel.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
			resetButton.setLookAndFeel(CommonToggleButtonLooknFeel::getLnf());
			cancel.setBackgroundColour(ui::Theme::Instance().getColour(customRed3));
			cancel.setColour(juce::TextEditor::focusedOutlineColourId, Theme::Instance().getColour(customRed5));
			cancel.setOutlineColour(ui::Theme::Instance().getColour(customRed4));
			apply.setBackgroundColour(Theme::Instance().getColour(customOrange));
			apply.setOutlineColour(ui::Theme::Instance().getColour(customOrange5));
			apply.setColour(juce::TextEditor::focusedOutlineColourId, Theme::Instance().getColour(customOrange4));
			resetButton.setBackgroundColour(Theme::Instance().getColour(customBlue6));
			setContent(Content);
			setContentBounds(bounds);
			setContentBackgroundColour(backgroundColour);
			setShowYesNoButtons(ShowYesNoButtons);
			setTitle(Title);

			auto display = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay();
			auto b = display->totalArea;

			setBounds(b);
			addToDesktop(compPeer::windowIsTemporary | compPeer::windowHasDropShadow);
		}

		~dialogDisplayer() {
			removeContent();
		}

		void removeContent()
		{
			if (pCont)
				removeChildComponent(pCont);
		}		

		void close(int exitCode) {
			if (auto dw = findParentComponentOfClass<DialogWindow>())
				dw->exitModalState(exitCode);
			else
				exitModalState(exitCode);
			reset();
		}

		void setShowYesNoButtons(bool ShowYesNoButtons) { showYesNoButtons = ShowYesNoButtons; }
		void setShowResetButton(bool ShowResetButton) {
			showResetButton = ShowResetButton; repaint(); resized();
		}
		void setContent(juce::Component* Content) { pCont = Content;  }
		void setContentBounds(juce::Rectangle<int> Bounds) { contentBounds = Bounds; resized();}
		void setContentBackgroundColour(juce::Colour backgroundColour) { contentBackgroundColour = backgroundColour; }

		void reset()
		{
			cancel.setVisible(false);
			apply.setVisible(false);
			showImage = false;
			isInUse = false;
			removeAllChildren();
			setContent(nullptr);
			setTitle("");
			cancel.setBounds(0, 0, 0, 0);
			apply.setBounds(0, 0, 0, 0);
			resetButton.setBounds(0, 0, 0, 0);
			setVisible(false);


		}

		void show(std::function<void(int R)> Callback)
		{
			image.clear(ui::layout::screen);
			if(!showImage)
			if (auto w = juce::TopLevelWindow::getActiveTopLevelWindow())
			{
			
				image =( w->createComponentSnapshot(ui::Rectangle<int>{0, 0, 1024, 600}, true));
				showImage = true;
				repaint();
			}

			setVisible(true);
			toFront(true);

			enterModalState(true, juce::ModalCallbackFunction::create([Callback, this](int R) {
				Callback(R);
				}),
				false);
		}
		virtual void resized()
		{
			auto b = contentBounds.constrainedWithin(getLocalBounds());
			b.setCentre(ui::layout::screen.getCentre());
			displayBounds = b;			

			// If options, Setup yes/no/reset buttons
			if (showYesNoButtons)
			{
				row = b.removeFromBottom(84);
				if (showResetButton)
				{
					cancel.setBounds(row.getX() + 20, row.getY() + 15, 175, 44);
					apply.setBounds(row.getX() + 212, row.getY() + 15, 175, 44);
					resetButton.setBounds(row.getX() + 390 + 15, row.getY() + 15, 175, 44);
					CommonUtils::addAndMakeVisible(this, title, apply, cancel, resetButton);
				}
				else
				{
					cancel.setBounds(row.getX() + 30, row.getY() + 15, 262, 44);
					apply.setBounds((row.getX() + (row.getWidth() / 2)) + 15, row.getY() + 15, 262, 44);
					CommonUtils::addAndMakeVisible(this, title, apply, cancel);
				}
			}

			// Setup content
			if (pCont)
			{
				contentArea = b;
				pCont->setBounds(contentArea);
				ui::CommonUtils::addAndMakeVisible(this, *pCont);
			}
		}

		std::atomic<bool> isInUse{ false };
		bool isBlockingScreen = false;
	private:
		bool showYesNoButtons{ false };
		bool showResetButton{ false };
		juce::Component* pCont{ nullptr };
		juce::Rectangle<int> contentBounds{ ui::layout::dialog }, row, buttonArea, contentArea, displayBounds;
		juce::Colour contentBackgroundColour{ Theme::Instance().backgroundColour(5).withAlpha(.25f) };
		ui::CommonLabel title{ "" };
		ui::CommonButton apply{ "Apply" }, cancel{ "Cancel" }, resetButton{ "Reset" };
		float backgroundAlpha{ 0.75f };		
		juce::Image          image;
		bool showImage = false;

		void paint(juce::Graphics& g)
		{
			g.drawImageAt(image, 0, 0);

			g.setColour(contentBackgroundColour);
			g.fillRect(contentArea);

			g.setColour(juce::Colours::black.withAlpha(0.5f));
			g.fillAll();
			if (showYesNoButtons)
			{
				g.setColour(juce::Colour(ui::Theme::Instance().getColour(customBlue15)));
				g.fillRoundedRectangle((float)row.getX(), (float)row.getY(), (float)row.getWidth(), 84.0f, 3.0f);
				g.setColour(ui::Theme::Instance().getColour(customBlue14));
				g.fillRoundedRectangle((float)row.getX() + 1.0f, (float)row.getY(), (float)row.getWidth() - 2.0f, 83.0f, 3.0f);
				g.setColour(juce::Colour(ui::Theme::Instance().getColour(customBlue15)));
				g.fillRect(row.getX(), row.getY(), (int)row.getWidth(), 1);
			}			
		}

		void mouseDown(const juce::MouseEvent& e) {
			if (!isBlockingScreen)
			{
				if (!pCont->getBounds().contains(e.getPosition()))
					close(ui::CANCEL);
			}
			else
			{
				constexpr int blinkDuration = 100; // in milliseconds

				// Reduce opacity and restore it after a short delay
				pCont->setAlpha(0.8f);

				juce::Timer::callAfterDelay(blinkDuration, [this]() {
					pCont->setAlpha(1.0f);
					});
			}
		}
	};

	///
	/// KickUtils...
	///

	dialogDisplayer* getDialogDisplayer(bool showResetBtn)
	{
		static std::vector<std::unique_ptr<dialogDisplayer>> _dlgBoxes;
		// Find available free instance...
		for (auto& it : _dlgBoxes)
		{
			if (!it->isInUse.load())
			{
				it->isInUse = true;
				it->setShowResetButton(showResetBtn);
				return it.get();
			}
		}
		// No free instance found in list, create and add one.
		_dlgBoxes.emplace_back(new dialogDisplayer{ false, showResetBtn, "", nullptr, {}, juce::Colours::transparentBlack });
		auto& p = _dlgBoxes.back();
		auto  c = juce::TopLevelWindow::getActiveTopLevelWindow();
		c->addAndMakeVisible(p.get());
		p->isInUse = true;
		return p.get();
	}

	void showDialog_(bool IsOptions, const juce::String& Title, juce::Component* Comp, std::function<void(int)> Callback,
		juce::Rectangle<int> bounds, juce::Colour backgroundColour, int TitleHeight, bool showResetBtn = false, bool isblockingpopup = false);

	void showDialog_(bool IsOptions, const juce::String& Title, juce::Component* Comp, std::function<void(int)> Callback,
		juce::Rectangle<int> bounds, juce::Colour backgroundColour, int TitleHeight, bool showResetBtn, bool isblockingpopup)
	{
		auto _dialogBox = getDialogDisplayer(showResetBtn);

		// Setup _dialogbox contents.
		_dialogBox->reset();
		_dialogBox->setShowYesNoButtons(IsOptions);
		_dialogBox->setShowResetButton(showResetBtn);
		_dialogBox->setContent(Comp);
		_dialogBox->setContentBounds(bounds);
		_dialogBox->setContentBackgroundColour(backgroundColour);
		_dialogBox->setTitle(Title);
		_dialogBox->show(std::move(Callback));
		_dialogBox->isBlockingScreen = isblockingpopup;
		Displayerptr = _dialogBox;
	
	}

	void CommonUtils::showCustomDialog(const juce::String& Title, juce::Component* Comp, std::function<void(int)> Callback,
		juce::Rectangle<int> bounds, bool ctrlOpt, int TitleHeight, juce::Colour backgroundColour, bool showRstBtn, bool isblockingpopup)
	{
		showDialog_(ctrlOpt, Title, Comp, Callback, bounds, backgroundColour, TitleHeight, showRstBtn, isblockingpopup);
	}

	void CommonUtils::showOptions(juce::Component* Comp, std::function<void(int)> Callback, juce::Rectangle<int> bounds, juce::Colour backgroundColour, int TitleHeight)
	{
		showDialog_(true, "", Comp, Callback, bounds, backgroundColour, TitleHeight);
	}
	void CommonUtils::close()
	{
		if(Displayerptr!= nullptr)
		Displayerptr->reset();
	}

	void CommonUtils::SetUtilsVisiblity(bool status)
	{
		if (Displayerptr != nullptr)
			Displayerptr->setVisible(status);
	}

	void CommonUtils::createUtilsUniqueObject()
	{
		auto _dialogBox = getDialogDisplayer(false);
		Displayerptr = _dialogBox;
		close();
		_dialogBox->setVisible(false);
	}

	void CommonUtils::SetBlockingPopup(bool state)
	{
		Displayerptr->isBlockingScreen = state;
	}

}
