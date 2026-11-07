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

#pragma once

using namespace ignite_Constants;
namespace ui
{
	class AppOptions;
	class IgniteAnimatdText : public juce::Component,private Timer
		
	{
	public:
		CommonLabel TextLabel{ "" };

		IgniteAnimatdText();
		~IgniteAnimatdText(){};
		void setScrollingBounds(ui::Rectangle<int> a,float f=16.f);
		void startAnimate();
		void setAnimatedText(String s);
	private:
		String text{ "" };
		float font = 16.0f;
		void timerCallback() override;
		ui::Rectangle<int> b;
		ui::Rectangle<int> scrollingbounds;
		void paint(juce::Graphics& g) override;
		void resized() override;
		bool isTextRotating = false;
		int reqWidth;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteAnimatdText)
	};
};
