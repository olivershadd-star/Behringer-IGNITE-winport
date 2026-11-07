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

namespace ui
{
CommonTabbedComponent::CommonTabbedComponent( TabbedButtonBar::Orientation orientation ) : TabbedComponent( orientation )
{
    setLookAndFeel(CommonLooknFeel::getLnf());
    addChildComponent( back );
    addChildComponent( fullscreen );
    back.addListener( this );
    fullscreen.addListener( this );
    setOutline( 0 );
    setTabBarDepth(38);
}

void CommonTabbedComponent::setBounds( Rectangle<int> Normal, Rectangle<int> FullScreen )
{
    normalBounds = Normal;
    fullScreenBounds = FullScreen;
    setupSize( isFullSize );
}

void CommonTabbedComponent::showFullSize()
{
    setupSize( true );
};

void CommonTabbedComponent::showNormalSize()
{
    setupSize( false );
};

void CommonTabbedComponent::setMultiselectTab(int tabIndex, int noOfSelect)
{
    multiSelectTab.insert({ tabIndex, noOfSelect });
}
void CommonTabbedComponent::setupSize( bool isFull )
{
    isFullSize = isFull;
    back.setVisible( isFull );
    fullscreen.setVisible( isFull );

    TabbedComponent::setBounds( isFullSize ? fullScreenBounds : normalBounds );
}

void CommonTabbedComponent::setTabVisibile(int tabIndex, bool isVisible)
{
    getTabbedButtonBar().getTabButton(tabIndex)->setEnabled(isVisible);
}

void CommonTabbedComponent::currentTabChanged( int newTabIndex, const String& NewTabName )
{
    //DBG( "Tab: " << NewTabIndex << ", Name: " << NewTabName );
    if (newTabIndex != currentTab)
    {
        auto multiIt = multiSelectTab.find(currentTab);
        if (multiIt != multiSelectTab.end())
        {
            CommonMultiSelectTabBarButton* tabButton = static_cast<CommonMultiSelectTabBarButton*>(getTabbedButtonBar().getTabButton(currentTab));
            tabButton->clearSelection();
        }
    }
    currentTab = newTabIndex;
    if( onTabChanged )
        onTabChanged( newTabIndex, NewTabName );
}

void CommonTabbedComponent::buttonClicked( Button* Button )
{
    if (Button == &back)
    {
        if (onBackButtonPressed)
            onBackButtonPressed(Button->getToggleState());
    }
    else if (Button == &fullscreen)
    {
        setupSize(!isFullSize);
    }
    else
    {

    }
}

void CommonTabbedComponent::resized()
{
    juce::TabbedComponent::resized();

    auto& bar = getTabbedButtonBar();
    Rectangle<int> b = bar.getBounds();

    if( isFullSize )
    {
        auto depth = getTabBarDepth();
        back.setBounds( b.getX(), b.getY(), depth, depth );
        fullscreen.setBounds( b.getTopRight().getX() - depth, b.getY(), depth, depth );
        b = bar.getBounds().withTrimmedLeft( depth ).withTrimmedRight( depth );
    }
    getTabbedButtonBar().setBounds( b );
}

TabBarButton* CommonTabbedComponent::createTabButton(const String& tabName, int tabIndex)
{
    auto multiIt = multiSelectTab.find(tabIndex);
    if (multiIt != multiSelectTab.end())
    {
        auto* multiBtn =  new CommonMultiSelectTabBarButton(multiIt->second, getTabbedButtonBar(), tabName);
        multiBtn->onClick = [tabName, tabIndex, this, multiBtn]()
        {
            multiBtn->incrementSelection();
            if (onMultiSelctTabChanged)
                onMultiSelctTabChanged(tabIndex, multiBtn->getCurrentSelection(), tabName);
        };

        return multiBtn;
    }
    else
    {
        return TabbedComponent::createTabButton(tabName, tabIndex);
    }
}
};
