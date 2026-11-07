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

namespace ui
{
	class IgniteSong;
	class IgniteBottomBar : public juce::Component
	{
	public:
		IgniteBottomBar();
		~IgniteBottomBar();


		static IgniteBottomBar* GetBottomBarInstance()
		{
			static IgniteBottomBar* GetAppBbarInstance;
			if (NULL == GetAppBbarInstance)
			{
				GetAppBbarInstance = new IgniteBottomBar();
			}

			return GetAppBbarInstance;
		}

		void updateOneSongData(int item_id, float value);
		void updateSongData(float dtempo, float dswing);
	private:
		juce::FlexBox box;
		ui::CommonNumber volume{ "VOLUME", 0, 100, 50 }, swing{ "Edit Options", -120, 20, 0 };
		ui::CommonNumber tempo{ "TEMPO", 0, 200,  130 };
		ui::CommonLabel loop{ "Play/Pause/Stop/Record/Browse/Save/Move/Copy/Delete/Loop" };
		ui::CommonLabel quantize{ "QUANTIZE","1/16", true };
		ui::CommonLabel bbs{ "","0.00.000", true };

		void paint(juce::Graphics& g) override;
		void resized() override;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteBottomBar)
	};
};
