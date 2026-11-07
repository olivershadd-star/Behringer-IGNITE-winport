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

#pragma once

namespace ui
{

    class CommonUtils
    {
    public:
        template<typename... Args>
        static void addChildComponents(juce::Component* parent, Args&&... args)
        {
            (parent->addChildComponent(args), ...);
        }

        template<typename... Args>
        static void addAndMakeVisible(juce::Component* parent, Args&&... args)
        {
            (parent->addAndMakeVisible(args), ...);
        }

        template<typename... Args>
        static void makeVisible(Args&&... args)
        {
            (args.setVisible(true), ...);
        }

        template<typename... Args>
        static void makeHidden(Args&&... args)
        {
            (args.setVisible(false), ...);
        }

        template<typename... Args>
        static void makeOpaque(Args&&... args)
        {
            (args.setOpaque(true), ...);
        }

        template<typename... Args>
        static void disableMouseIntercepts(Args&&... args)
        {
            (args.setInterceptsMouseClicks(false, false), ...);
        }

        template<typename... Args>
        static void disableMouseInterceptsAllowOnChildren(Args&&... args)
        {
            (args.setInterceptsMouseClicks(false, true), ...);
        }

        static void showCustomDialog(const juce::String& Title, juce::Component* Comp, std::function<void(int)> Callback,
            juce::Rectangle<int> bounds = ui::layout::dialog, bool ctrlOpt = false, int TitleHeight = heightDailogTitle,
            juce::Colour backgroundColour = Theme::Instance().backgroundColour(5).withAlpha(.25f), bool showRstBtn = false, bool isblockingpopup =false);

        static void showOptions(juce::Component* Comp, std::function<void(int)> Callback, juce::Rectangle<int> bounds = ui::layout::dialog, 
            juce::Colour backgroundColour = Theme::Instance().backgroundColour(5).withAlpha(.25f), int TitleHeight = heightDailogTitle);

		template <typename T>
		static T convertToPrecision(T Value, int precision = 3)
		{
			T tValue;
			std::stringstream o;
			o << std::setprecision(precision) << std::fixed << Value;
			tValue = (T)strtod(o.str().c_str(), nullptr);
			return tValue;
		}

		static void showDialog(const juce::String& Title, juce::Component* Comp, std::function<void(int)> Callback,
			int Width = layout::dialog.getWidth(), int Height = layout::dialog.getHeight())
		{
			DialogWindow::LaunchOptions options;
			options.content.setNonOwned(Comp);
			options.content->setSize(Width, Height);
			options.dialogTitle = Title;
			options.dialogBackgroundColour = Theme::Instance().getColour(neutralGrey4);
			options.escapeKeyTriggersCloseButton = true;
			options.useNativeTitleBar = false;
			options.resizable = false;

			juce::Component::SafePointer<juce::DialogWindow> dialogWindow{ options.launchAsync() };
			dialogWindow->setDraggable(false);
			dialogWindow->setLookAndFeel(CommonLooknFeel::getLnf());
			dialogWindow->setTitleBarTextCentred(false);
			ModalComponentManager::getInstance()->attachCallback(dialogWindow, ModalCallbackFunction::create([Callback, dialogWindow](int R)
				{
					Callback(R);
					delete dialogWindow;
				}));
		}

		static int timeDivStrToQl(const juce::String& timeDiv)
		{
			if (timeDiv == "4" || timeDiv == "8" || timeDiv == "16" || timeDiv == "32" || timeDiv == "64")
			{
				return static_cast<int>(juce::CharacterFunctions::getDoubleValue(timeDiv.getCharPointer()));
			}
			else if (timeDiv == "4T" || timeDiv == "8T" || timeDiv == "16T" || timeDiv == "32T" || timeDiv == "64T")
			{
				juce::String tmpDiv = timeDiv.removeCharacters("T");
				int tripletDiv = static_cast<int>(juce::CharacterFunctions::getDoubleValue(timeDiv.getCharPointer()));

				return (tripletDiv / 2) * 3;
			}
			else if (timeDiv == "1/4" || timeDiv == "1/8" || timeDiv == "1/16" || timeDiv == "1/32" || timeDiv == "1/64")
			{
				juce::String tmpDiv = timeDiv.substring(2);
				return static_cast<int>(juce::CharacterFunctions::getDoubleValue(tmpDiv.getCharPointer()));
			}

			return -1;
		}
		static void close();
		static void SetUtilsVisiblity(bool status);
		static void createUtilsUniqueObject();
		static void SetBlockingPopup(bool state);
		
    };

}// namespace ui
