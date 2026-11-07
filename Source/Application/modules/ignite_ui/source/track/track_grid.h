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
	class AppTrackOpt;

	class IgniteTrackGrid :
		public juce::Component,
		public CommonButton::Listener, CommonTrackButton::Listener
	{
#define TRACKVIEW_ 17
#define TRACK_ROW_ITEMS 4
		enum TrackViewItemID
		{
			NO_FOCUS = 0,
			EN_TRACK1,
			EN_TRACK2,
			EN_TRACK3,
			EN_TRACK4,
			EN_TRACK5,
			EN_TRACK6,
			EN_TRACK7,
			EN_TRACK8,
			EN_TRACK9,
			EN_TRACK10,
			EN_TRACK11,
			EN_TRACK12,
			EN_TRACK13,
			EN_TRACK14,
			EN_TRACK15,
			EN_TRACK16,
			FOCUS_MAX = EN_TRACK16
		};
	public:
		IgniteTrackGrid(IgniteTrack* tPtr);
		~IgniteTrackGrid() override;
		void paint(juce::Graphics& g) override;
		void resized() override;
		virtual void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void updateTrackGridData();
		void updateTrackData(int trackIndex);
		void updateTrackButtonState();
		CommonTrackButton* getButton(int index);
		void onMouseClicked(CommonTrackButton*) override;
		void onMouseDoubleClicked(CommonTrackButton*) override;
		bool changeEditTrack(int trackIndex);

		void setTrackBtnState(int id, bool state)
		{
			CommonTrackButton* buttonThatWasClicked = getButton(((id > 16) ? (id - 16) : id) - 1);
			buttonThatWasClicked->setToggleState(state);
		}

		void setEditTrackState(int id, bool state)
		{
			CommonTrackButton* buttonThatWasClicked = getButton(((id > 16) ? (id - 16) : id) - 1);
			buttonThatWasClicked->setEditState(state);
		}

		static IgniteTrackGrid* GetAppTrackGridInstance(IgniteTrack* tPtr)
		{
			static IgniteTrackGrid* instanceAppTrackGrid;
			if (NULL == instanceAppTrackGrid)
			{
				instanceAppTrackGrid = new IgniteTrackGrid(tPtr);
			}
			return instanceAppTrackGrid;
		}

		bool PannelKeyHandler(paramId_t param, uint32_t KeyValue);
		void handleCommandMessage(int id);
		void updatePagerBullet(int index);
		void enablePagerBullet();
	private:
		IgniteTrack* pTrack;
		AppTrackOpt* pTrackOpt = nullptr;
		CommonInfoWindow* _pInfoWindow = nullptr;
		int keyFocusedItem = TrackViewItemID::NO_FOCUS;
		uint8_t optionsView[TRACKVIEW_] = { NO_FOCUS, EN_TRACK1,EN_TRACK2,EN_TRACK3,EN_TRACK4,EN_TRACK5,EN_TRACK6,EN_TRACK7,EN_TRACK8,EN_TRACK9,EN_TRACK10,EN_TRACK11,EN_TRACK12,EN_TRACK13,EN_TRACK14,EN_TRACK15,EN_TRACK16 };
		int KeyHighLitedtrackIndex = 0; //index on current banh
		bool isDoubleClick = false;

		juce::FlexBox trackBox;
		juce::FlexBox trackBox_colume1;
		juce::FlexBox trackBox_colume2;
		juce::FlexBox trackBox_colume3;
		juce::FlexBox trackBox_colume4;
		juce::FlexBox pageflex;

		CommonTrackButton trackBtn1;
		CommonTrackButton trackBtn2;
		CommonTrackButton trackBtn3;
		CommonTrackButton trackBtn4;
		CommonTrackButton trackBtn5;
		CommonTrackButton trackBtn6;
		CommonTrackButton trackBtn7;
		CommonTrackButton trackBtn8;
		CommonTrackButton trackBtn9;
		CommonTrackButton trackBtn10;
		CommonTrackButton trackBtn11;
		CommonTrackButton trackBtn12;
		CommonTrackButton trackBtn13;
		CommonTrackButton trackBtn14;
		CommonTrackButton trackBtn15;
		CommonTrackButton trackBtn16;

		CommonImageButton page1{ "page1", "track-pager-inactive.png", "track-pager-active.png", "track-pager-active.png" };
		CommonImageButton page2{ "page2", "track-pager-inactive.png", "track-pager-active.png", "track-pager-active.png" };
		CommonImageButton page3{ "page3", "track-pager-inactive.png", "track-pager-active.png", "track-pager-active.png" };
		CommonImageButton page4{ "page3", "track-pager-inactive.png", "track-pager-active.png", "track-pager-active.png" };
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IgniteTrackGrid)
	};
};
