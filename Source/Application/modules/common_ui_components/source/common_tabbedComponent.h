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
class CommonTabbedComponent : public juce::TabbedComponent, public Button::Listener
{
public:
    std::function<void( bool )> onBackButtonPressed;
    std::function<void( int NewTabIndex, const String& NewTabName )> onTabChanged;
    std::function<void(int NewTabIndex, int multiSelectIndex,  const String& NewTabName) > onMultiSelctTabChanged;

    explicit CommonTabbedComponent( TabbedButtonBar::Orientation orientation );

    void setBounds( Rectangle<int> Normal, Rectangle<int> FullScreen );
    void showFullSize();
    void showNormalSize();
    void setMultiselectTab(int tabIndex, int noOfSelect);
    void setTabVisibile(int tabIndex, bool isVisible);

private:
    TabBarButton* createTabButton(const String& tabName, int tabIndex) override;
    void resized() override;
    bool isFullSize{false};
    Rectangle<int> normalBounds, fullScreenBounds;
    CommonImageButton back{"Back", "Mode Back Button - Round.png"};
    CommonImageButton fullscreen{"FullScreen", "Mode Show Bar.png"};

    void setupSize( bool isFull );
    virtual void currentTabChanged( int NewTabIndex, const String& NewTabName ) override final;
    virtual void buttonClicked( Button* Button ) override;

private:
    std::map<int, int> multiSelectTab;
    int currentTab = 0;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(  CommonTabbedComponent )
};
}
