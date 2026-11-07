/*
 * Copyright (c) - 2022 - MUSIC Tribe, MY
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
	class CommonHelpInfoPopUp : public juce::Component, public juce::Button::Listener
	{
	public:
		CommonHelpInfoPopUp(const juce::String& Title, int Width, int Height);
		~CommonHelpInfoPopUp();
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void show();
		void setInfoText(String a);
	private:
		juce::Component::SafePointer<juce::DialogWindow> dialogWindow;
		std::unique_ptr<Viewport> view;
		Viewport infoViewPort;
		CommonLabel title{ "" };
		CommonLabel infoLabel{ "" };
		int width{ 0 }, height{ 0 };
		CommonImageButton closeBtn{ "Close","ico-close.png","ico-close.png" };
		CommonImageButton infoBtn{ "Info","icon-helper-title.png","icon-helper-title.png" };
		int availableHeightForViewPort = 0;
		int requiredHeight = 0;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CommonHelpInfoPopUp)
	};
};