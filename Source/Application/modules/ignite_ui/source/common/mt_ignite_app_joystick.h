/*
 * Copyright (c) - 2023 - MUSIC Tribe, MY
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
    class ParameterViewControl;
    enum _Direction
    {
        RIGHT,
        LEFT,
        UP,
        DOWN,
        CENTER

    };
    class mt_ignite_app_joystick : public juce::Component
    {
    public:
       std::function<void(_Direction selection)> onSelectionChanged;
       
        mt_ignite_app_joystick();
        ~mt_ignite_app_joystick() override;

        void paint(juce::Graphics&) override;
        void resized() override;
        void mouseDown(const juce::MouseEvent& event);
        void mouseDrag(const juce::MouseEvent& event);
        void mouseUp(const juce::MouseEvent& event);
        void updateSelectionAndRepaint();

        void setKnobPosition(juce::Point<int> newPosition);
      
        juce::Point<int> getKnobPosition() const;
        juce::String getKnobDirection();

        static mt_ignite_app_joystick* GetobjInstance()
        {
            static mt_ignite_app_joystick* GetInstance;
            if (NULL == GetInstance)
            {
                GetInstance = new mt_ignite_app_joystick();
            }
            return GetInstance;
        }
        
        _Direction currentDirection;
       
    private:
        juce::Point<int> knobPosition;
        int previousWidth;
        int previousHeight;
        bool isMouseDragging;
        juce::Rectangle<int> previousBounds;
        juce::Point<int> previousKnobPosition;
        
        enum class Direction
        {
            Up,
            Down,
            Left,
            Right,
            UpLeft,
            UpRight,
            DownLeft,
            DownRight,
            Center,
            None
        };

        Direction getDirectionFromPosition() const;
        juce::Point<double> knobRelativePosition;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(mt_ignite_app_joystick)
    };
}