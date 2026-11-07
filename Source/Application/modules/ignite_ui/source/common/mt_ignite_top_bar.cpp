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

#include "Common/Modules/IDevice.h"

using namespace Ignite;

extern std::unique_ptr<IDevice> _PUiVirtualEngine;

using namespace ignite_Constants;
namespace ui
{
	IgniteTopBar::IgniteTopBar()
	{
		addAndMakeVisible(menuButton);
		menuButton.addListener(this);
		menuButton.setBounds(10, 5, 49, 46);

		addAndMakeVisible(mainModeButton);
		mainModeButton.addListener(this);
		//mainModeButton.setBounds(80, 5, widthTopbar, heightTopbar);

		addAndMakeVisible(barButton);
		barButton.addListener(this);
		//barButton.setBounds(150, 5, 49, 46);

		addAndMakeVisible(gridButton);
		gridButton.addListener(this);
		//gridButton.setBounds(220, 5, 49, 46);

		addAndMakeVisible(listButton);
		listButton.addListener(this);
		//listButton.setBounds(290, 5, 49, 46);

		addAndMakeVisible(settings);
		settings.setButtonText(TRANS("Settings"));
		settings.addListener(this);
		settings.setClickingTogglesState(true);

		addAndMakeVisible(igniteSaveButton);
		igniteSaveButton.setButtonText(TRANS("Save"));
		igniteSaveButton.addListener(this);
		igniteSaveButton.setClickingTogglesState(false);

		addAndMakeVisible(igniteBrowseButton);
		igniteBrowseButton.setButtonText(TRANS("Browse"));
		igniteBrowseButton.addListener(this);
		igniteBrowseButton.setClickingTogglesState(false);

		addAndMakeVisible(ignitePlayButton);
		ignitePlayButton.setButtonText(TRANS("Play"));
		ignitePlayButton.addListener(this);
		ignitePlayButton.setClickingTogglesState(true);

		topBarBox.items.add(FlexItem(igniteBrowseButton).withMargin(5).withFlex(10));
		topBarBox.items.add(FlexItem(igniteSaveButton).withMargin(5).withFlex(10));
		topBarBox.items.add(FlexItem(ignitePlayButton).withMargin(5).withFlex(10));
		topBarBox.items.add(FlexItem(settings).withMargin(5).withFlex(25));

		mainModeButton.setToggleState(true, dontSendNotification);
	}



	IgniteTopBar::~IgniteTopBar()
	{}

	void IgniteTopBar::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		if (buttonThatWasClicked == &mainModeButton)
		{
			if (mainModeButton.getState() == juce::Button::buttonOver)
			{
				settings.setToggleState(false, sendNotification);
				getAppHome().show(screen::APP_MAIN_MODE, true);

			}
			else
				getAppHome().show(screen::APP_MAIN_MODE, false);
		}
		else if (buttonThatWasClicked == &menuButton)
		{
			if (menuButton.getState() == juce::Button::buttonOver)
			{
				menuButton.setToggleState(false, sendNotification);
				getAppHome().show(screen::MENU, true);

			}
			else
				getAppHome().show(screen::MENU, false);
		}
		else if (buttonThatWasClicked == &listButton)
		{
			if (listButton.getState() == juce::Button::buttonOver)
			{
				listButton.setToggleState(false, sendNotification);
				getAppHome().show(screen::LIST, true);

			}
			else
				getAppHome().show(screen::LIST, false);
		}
		else if (buttonThatWasClicked == &gridButton)
		{
			if (gridButton.getState() == juce::Button::buttonOver)
			{
				gridButton.setToggleState(false, sendNotification);
				getAppHome().show(screen::GRID, true);

			}
			else
				getAppHome().show(screen::GRID, false);
		}
		else if (buttonThatWasClicked == &barButton)
		{
			if (barButton.getState() == juce::Button::buttonOver)
			{
				barButton.setToggleState(false, sendNotification);
				getAppHome().show(screen::BAR, true);

			}
			else
				getAppHome().show(screen::BAR, false);
		}
		else if (buttonThatWasClicked == &settings)
		{
			if (settings.getState() == juce::Button::buttonOver)
			{
				mainModeButton.setToggleState(false, sendNotification);
				getAppHome().show(screen::SETTING, true);

			}
			else
				getAppHome().show(screen::SETTING, false);
		}
		else if (buttonThatWasClicked == &ignitePlayButton)
		{
			if (IgniteSong::getAppSongInstance()->isSongCreated() && IgniteSong::getAppSongInstance()->getSongData(mt::Ignite::songsDataIndex::SCENE_CREATED)) {
				if (ignitePlayButton.getToggleState() == true)
				{
					_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::paramActiveSong, (uint32_t)IgniteSong::getAppSongInstance()->getSelected());
					_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SceneParam::paramActiveScene, (uint32_t)IgniteScene::getAppSceneInstance()->getSelected());
					_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::paramActiveSong, (uint32_t)IgniteSong::getAppSongInstance()->getCurrentSongRow());
					_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::paramPlaySongCmd, (uint8_t)0);
				}
				else
				{
					_PUiVirtualEngine->setParam((moduleId_t)ModuleName::moduleUI, (moduleId_t)ModuleName::moduleSong, (paramId_t)SongParam::paramPauseSongCmd, (uint8_t)0);
				}
			}
			else
				ignitePlayButton.setToggleState(false, dontSendNotification);
		}
	}

	void IgniteTopBar::paint(juce::Graphics& g)
	{
		g.setColour(Theme::Instance().getColour(neutralBlack));
		g.fillAll();
	}

	void IgniteTopBar::resized()
	{
		mainModeButton.setBounds(getLocalBounds());
		topBarBox.performLayout(getLocalBounds().removeFromRight(300));
	}
	///
};
