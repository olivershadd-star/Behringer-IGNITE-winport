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
using namespace ignite_Constants;
namespace ui
{
	class IgniteScene;
	class AppOptCtl;

	class AppSceneView : public juce::Component,
		public juce::Button::Listener,
		public CommonLabel::Listener,
		public juce::ModalComponentManager,
		private Timer
	{
	public:
		CommonNumber tempoComp{ "Tempo", minTempo, maxTempo, defTempo, true };

		AppSceneView(IgniteScene* ptr);
		~AppSceneView() override;

		void setFTSListUpdateState(bool state) { isFTSListUpdateNeeded = state; }
		bool getFTSListUpdateState() { return isFTSListUpdateNeeded; }

		void refreshData(int SerialNumber, mt::Ignite::sceneData* data);
		String getListData(mt::Ignite::sceneDataIndex index);
		void clearTapTempoData() { tapTempo.resetTapTempoData(); };
		void setTapTempo(float value, bool sendTempoAsPlayModeData, bool timerStart);

		static AppSceneView* getAppSceneViewInstance(IgniteScene* ptr)
		{
			static AppSceneView* instanceAppSceneView;
			if (NULL == instanceAppSceneView)
			{
				instanceAppSceneView = new AppSceneView(ptr);
			}
			return instanceAppSceneView;
		}

		bool pannelKeyHandler(paramId_t param, uint32_t keyValue);
		void pannelSendKey(bool isFocuse, paramId_t param, uint32_t keyValue);
		void getAssets();
	private:
#define SCENE_DETAIL_ROW_ITEMS 3
#define SCENE_DETAL_ITEMS 12
		enum sceneDetailsViewItemID
		{
			NO_FOCUS = 0,
			SWINGCOMP ,
			GBARCOMP,
			MUTEHOLD,
			LENCOMP,
			SONGADV,
			TEMPOCOMP,
			FTSROOTNOTE,
			FTSSCALE,
			XFTS,
			XPOSECOMP,
			TAP_TEMPO,
			FOCUS_MAX = TAP_TEMPO
		};

		int numItemsInRow = 4;
		int keyFocusedItem = sceneDetailsViewItemID::NO_FOCUS;
		uint8_t detailsViewItems[SCENE_DETAL_ITEMS] = { NO_FOCUS, SWINGCOMP, GBARCOMP, MUTEHOLD, LENCOMP, SONGADV, TEMPOCOMP, FTSROOTNOTE, FTSSCALE, XFTS, XPOSECOMP, TAP_TEMPO };
		
		IgniteSong* _pSong = nullptr;
		IgniteScene* _pScene = nullptr;
		IgniteSceneConfig* _pSceneConfigComp = nullptr;
		IgniteControlOptions* optPtr = nullptr;

		juce::FlexBox sceneBox1;
		juce::FlexBox sceneBox2;
		juce::FlexBox sceneBox3;
		juce::FlexBox sceneBox4;
		mt::Ignite::sceneData sceneData;
		TextEditor sceneNameText;
		Image imageSceneHeader, imageSceneBgContainerDefault, imageSceneBgContainerSelected, imageXposePostDefault, imageXposePostHover,
			imageXposePreDefault, imageXposePreHover, imageSongTempoDefault, imageSongTempoHover, imageSongTempoClick;

		Label serialNumLabel;
		CommonNameLabel optionsSceneName{ "" };
		CommonNumber swingComp{ "Swing", minSwing, maxSwing, maxSwing };
		CommonNumber gbarComp{ "GBAR", minGbar, maxGbar, defGbar };
		CommonNumber lenComp{ "Length", minLength, maxLength, defLength };
		CommonNumber xposeComp{ "Xpose", minXpose, maxXpose, defXpose };
		CommonKey nameLabel{ "SCENE_NAME" };

		CommonListBox songAdv{ "Scene Advance", 2 };
		std::vector<juce::String> songAdvOptions{ "Auto", "Manual" };

		CommonListBox ftsRootNote{ "FTS: Root Note", 4 };
		std::vector<juce::String> rootNotes{ "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
		CommonListBox ftsScale{ "FTS: Scale", 2 };
		std::vector<juce::String> scaleList{ "All Notes", "ScaleMajor", "ScaleAeolian", "ScaleHarmonicMinor", "ScaleMelodicMinor", "ScaleBlues1", "ScaleMinorPentatonic", "ScaleMixolydian", "ScaleLydianDiminished",
											"ScaleBlues2", "ScaleAugmented", "ScaleArabian", "ScaleBalinese", "ScaleHungarian1", "ScaleOriental", "ScaleIndian1", "ScaleChinese", "ScaleHungarian2", "ScaleJapanese1",
											"ScaleJapanese2", "ScaleJapanese3", "ScaleJapanese4", "ScalePersian", "ScaleDiminished", "ScaleWholeNote", "ScaleMongolian", "ScaleAlgerian", "ScaleByzantine", "ScaleAncientChinese",
											"ScaleIndian2", "ScalePrometheus" };

		CommonListBox muteHold{ "Mute Hold", 3 };
		std::vector<juce::String> muteHolfOptions{ "Off", "Next", "Lock" };

		CommonToggleButton xfts{""};

		IgniteTapTempo tapTempo;
		bool isFTSListUpdateNeeded = true;

		int isEditing();
		void updateScaleList();
		void updateLableText(mt::Ignite::sceneDataIndex item_id, bool state);
		void paint(juce::Graphics& g) override;
		void resized() override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void labelTextChanged(Label* labelThatHasChanged) override;
		void mouseUp(const MouseEvent& event)override;
		void timerCallback() override;
		void updateComponentState(Component& comp, bool state);
		void skipItemFromFocus(bool isFocuse,paramId_t param, uint32_t keyValue);
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AppSceneView)
	};
};
