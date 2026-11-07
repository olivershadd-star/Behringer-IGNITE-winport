/*
 * Copyright (c) - 2023 - MUSIC Tribe, MY.
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

using namespace Ignite;

namespace ui
{

	////////////////////////////////////////////////
	//   Class: IgniteTest
	////////////////////////////////////////////////
	IgniteTest::IgniteTest()
	{

		songNum.makeVisible(this);
		songNum.setDisplayTitle(true);
		songNum.setJustificationType(juce::Justification::centred);
		songNum.setTextColour(Theme::Instance().getColour(systemBlue));
		sceneNum.makeVisible(this);
		sceneNum.setDisplayTitle(true);
		sceneNum.setJustificationType(juce::Justification::centred);
		sceneNum.setTextColour(Theme::Instance().getColour(systemBlue));
		addAndMakeVisible(TrackNum);
		TrackNum.updateListOptions(numOfTracks);
		TrackNum.setSelected(0);
		TrackNum.setDisplayFormat(CommonListBox::BoxType::withTitleBottom);
		TrackNum.setValueColour(Theme::Instance().getColour(systemBlue));
		PatternNum.makeVisible(this);
		PatternNum.setDisplayTitle(true);
		PatternNum.setJustificationType(juce::Justification::centred);
		PatternNum.setTextColour(Theme::Instance().getColour(systemBlue));
		barNum.makeVisible(this);
		barNum.setDisplayTitle(true);
		barNum.setJustificationType(juce::Justification::centred);
		barNum.setTextColour(Theme::Instance().getColour(systemBlue));
		instrNum.makeVisible(this);
		instrNum.setDisplayTitle(true);
		instrNum.setJustificationType(juce::Justification::centred);
		instrNum.setTextColour(Theme::Instance().getColour(systemBlue));
		createTestData.makeVisibleAndAddListner(this);
		createTestData.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		touchTest.makeVisibleAndAddListner(this);
		WipeTestData.makeVisibleAndAddListner(this);
		WipeTestData.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		HW_Test.makeVisibleAndAddListner(this);
		Mcu_FW_Test.makeVisibleAndAddListner(this);
		const juce::Rectangle<int> bonds{ (0),(0),604,235 };
		TrackNum.setDailogViewType(mt::Ignite::DailogViewType::CustomView, true, bonds);

		ctlBox1.items.add(FlexItem(songNum).withMargin({ 0,8,8,0 }).withFlex(1));
		ctlBox1.items.add(FlexItem(sceneNum).withMargin({ 0,8,8,0 }).withFlex(1));
		ctlBox1.items.add(FlexItem(TrackNum).withMargin({ 0,8,8,0 }).withFlex(1));
		ctlBox2.items.add(FlexItem(PatternNum).withMargin({ 0,8,8,0 }).withFlex(1));
		ctlBox2.items.add(FlexItem(barNum).withMargin({ 0,8,8,0 }).withFlex(1));
		ctlBox2.items.add(FlexItem(instrNum).withMargin({ 0,8,8,0 }).withFlex(1));
		ctlBox3.items.add(FlexItem(createTestData).withMargin({ 0,8,8,0 }).withFlex(1));
		ctlBox3.items.add(FlexItem(WipeTestData).withMargin({ 0,8,8,0 }).withFlex(1));

		songNum.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;
			numOfSongs = value;
		};
		sceneNum.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::ParamTestSetNumScene, value);
		};
		TrackNum.onSelectionChanged = [this](int value, const juce::String&)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::ParamTestSetNumTrack, (value +1 )*16);
		};
		barNum.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::ParamTestSetNumPatternBars, value);
		};
		instrNum.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::ParamTestSetNumInstrument, value);
		};
		PatternNum.onValueChanged = [this](int value)
		{
			Component::BailOutChecker checker(this);

			if (checker.shouldBailOut())
				return;
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::ParamTestSetNumPattern, value);
		};

		songNum.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		sceneNum.onFocusChanged = [this](bool a)
		{
			repaint();
		};
		TrackNum.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		barNum.onFocusChanged = [this](bool a)
		{
			repaint();
		};
		instrNum.onFocusChanged = [this](bool a)
		{
			repaint();
		};

		PatternNum.onFocusChanged = [this](bool a)
		{
			repaint();
		};
	}

	IgniteTest::~IgniteTest()
	{
	}

	void IgniteTest::paint(juce::Graphics& g)
	{
		Image defaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("Setting_toggle-bg-default.png"));
		Image OverImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("Setting_toggle-bg-hover.png"));
		Image BtnActiveImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("Setting_toggle-bg-active.png"));
		Image disabledImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-bg-disabled.png"));
		Image Draw;

		MenuMode::GetMenuModeInstance()->setHeader("Test Data Management");

		g.setColour(Colour(0xFF000000));
		g.fillAll();

		Draw = songNum.getFocusState() ? OverImage : defaultImage;
		g.drawImage(Draw, ui::Rectangle<float>{ 10, 70, 328, 80 });

		Draw = sceneNum.getFocusState() ? OverImage : defaultImage;
		g.drawImage(Draw, ui::Rectangle<float>{ 348, 70, 328, 80 });

		Draw = TrackNum.getFocusState() ? OverImage : defaultImage;
		g.drawImage(Draw, ui::Rectangle<float>{ 686, 70, 328, 80 });

		Draw = PatternNum.getFocusState() ? OverImage : defaultImage;
		g.drawImage(Draw, ui::Rectangle<float>{ 10, 160, 328, 80 });

		Draw = barNum.getFocusState() ? OverImage : defaultImage;
		g.drawImage(Draw, ui::Rectangle<float>{ 348, 160, 328, 80 });

		Draw = instrNum.getFocusState() ? OverImage : defaultImage;
		g.drawImage(Draw, ui::Rectangle<float>{ 686, 160, 328, 80 });

		Draw = createTestData.isMouseOver() ? OverImage : defaultImage;
		g.drawImage(Draw, ui::Rectangle<float>{ 10, 350, 500, 80 });

		Draw = WipeTestData.isMouseOver() ? OverImage : defaultImage;
		g.drawImage(Draw, ui::Rectangle<float>{ 510, 350, 500, 80 });
	}

	void IgniteTest::resized()
	{
		ctlBox1.performLayout(ui::Rectangle(xStartSongMenuBox1, yStartSongMenuBox1, widthSongMenuBox1, heightSongMenuBox1));
		ctlBox2.performLayout(ui::Rectangle(xStartSongMenuBox1, yStartSongMenuBox2, widthSongMenuBox1, heightSongMenuBox1));
		ctlBox3.performLayout(ui::Rectangle(xStartSongMenuBox1, yStartSongMenuBox2 + heightSongMenuBox1 + 100, widthSongMenuBox1, heightSongMenuBox1));
		HW_Test.setBounds(xStartSongMenuBox1, yStartSongMenuBox2 + heightSongMenuBox1, 330, 90);
		touchTest.setBounds(xStartSongMenuBox1 + 340, yStartSongMenuBox2 + heightSongMenuBox1, 330, 90);
		Mcu_FW_Test.setBounds(xStartSongMenuBox1 + 680, yStartSongMenuBox2 + heightSongMenuBox1, 330, 90);
	}

	void IgniteTest::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &createTestData)
		{
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::ParamTestNumCreateSong, numOfSongs);
		}
		else if (buttonThatWasClicked == &WipeTestData)
		{
			_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::ParamDeleteAllSongInstPattern, 0);
			AppMainmode::getMainModeInstance()->enableTab(mt::Ignite::tabs::TRACK, false);
		}
		else if (buttonThatWasClicked == &HW_Test)
		{
			if (HW_Test.getToggleState())
			{
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::paramActiveSong, (uint32_t)0);
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleScene, (paramId_t)SceneParam::paramActiveScene, (uint32_t)0);
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::paramPlaySongCmd, (uint8_t)0);
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_HwTestMode, 1);
			}
			else	//set param for HW_TEST OFF
			{
				_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::paramPauseSongCmd, (uint8_t)0);
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_HwTestMode, 0);
			}

		}
		else if (buttonThatWasClicked == &Mcu_FW_Test)
		{
			if (Mcu_FW_Test.getToggleState())
			{
				_PUiVirtualEngine->SetCommand((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleFrontPannel, (paramId_t)FrontPannelParam::paramKey_FwUpgrade, 1);
			}
		}
		else if (buttonThatWasClicked == &touchTest)
		{
			AppHome::GetAppHomeInstance()->enableTouchTest(true);
		}

		IgniteSong::getAppSongInstance()->updateDataFromEngine();
		IgnitePattern::getAppPatternInstance()->updateDataFromEngine();
		IgniteInstruments::GetAppInstrumentsInstance()->updateDataFromEngine();

		IgniteSong::getAppSongInstance()->refreshSongUI();
		IgnitePattern::getAppPatternInstance()->refreshPatternUI();
		IgniteInstruments::GetAppInstrumentsInstance()->refreshInstrumentsUI();
	}
};
