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
	class CommonProgressBar : public juce::ProgressBar,
		juce::ProgressBar::LookAndFeelMethods
	{
	public:
		CommonProgressBar(double& progress);
		~CommonProgressBar();
		void updateProgress(double& newProgreess);
		void close();
		Style getDefaultProgressBarStyle(const ProgressBar& progressbar) override { return Style::circular; };

	private:
		void drawProgressBar(Graphics&, ProgressBar&, int width, int height,
			double progress, const String& textToShow) override;
		bool isProgressBarOpaque(ProgressBar&) override;
	private:
		double _progress = 0.0;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CommonProgressBar)
	};
};