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

namespace ui
{
    mt_ignite_app_joystick::mt_ignite_app_joystick()
    {
        setSize(150, 150);
        knobPosition = juce::Point<int>(getWidth() / 2, getHeight() / 2);
        isMouseDragging = false;
        currentDirection = _Direction::CENTER;
    }
   
    mt_ignite_app_joystick::~mt_ignite_app_joystick()
    {
    }

    void mt_ignite_app_joystick::setKnobPosition(juce::Point<int> newPosition)
    {
        knobPosition = newPosition;
        repaint();
    }

    juce::Point<int> mt_ignite_app_joystick::getKnobPosition() const
    {
        return knobPosition;
    }

    void mt_ignite_app_joystick::paint(juce::Graphics& g)
    {
        const int totalWidth = getWidth();
        const int totalHeight = getHeight();
        const int knobSize = 10;

        g.drawLine(0, static_cast<float>(totalHeight) * 0.5f, static_cast<float>(totalWidth), static_cast<float>(totalHeight) * 0.5f, 2);
        g.drawLine(static_cast<float>(totalWidth) * 0.5f, 0, static_cast<float>(totalWidth) * 0.5f, static_cast<float>(totalHeight), 2);
        const int knobX = knobPosition.x - knobSize / 2;
        const int knobY = knobPosition.y - knobSize / 2;
        g.fillEllipse(static_cast<float>(knobX), static_cast<float>(knobY), static_cast<float>(knobSize), static_cast<float>(knobSize));
        g.setFont(16.0f);
        juce::String directionText = "Direction: " + getKnobDirection();
     
        Image image_name = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cross-slide-default.png"));
        switch (currentDirection)
        {
        case _Direction::CENTER:
            image_name = isMouseOver() ? juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cross-slide-default-1.png")) : image_name;
            break;
        case _Direction::UP:
            image_name = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cross-slide-top.png"));
            break;
        case _Direction::DOWN:
            image_name = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cross-slide-bottom.png"));
            break;
        case _Direction::RIGHT:
            image_name = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cross-slide-right.png"));
            break;
        case _Direction::LEFT:
            image_name = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("cross-slide-left.png"));
            break;
        }

        int imageX = getWidth() / 2 - image_name.getWidth() / 2;
        int imageY = getHeight() / 2 - image_name.getHeight() / 2;  
        juce::Rectangle<float> imageBounds(static_cast<float>(imageX), static_cast<float>(imageY), static_cast<float>(image_name.getWidth()), static_cast<float>(image_name.getHeight()));
        g.drawImage(image_name, imageBounds);
    }

    void mt_ignite_app_joystick::resized()
    {
        double ratioX = static_cast<double>(knobPosition.x - previousBounds.getX()) / static_cast<double>(previousBounds.getWidth());
        double ratioY = static_cast<double>(knobPosition.y - previousBounds.getY()) / static_cast<double>(previousBounds.getHeight());
        const juce::Rectangle<int> newBounds = getLocalBounds();
        knobPosition.setX(static_cast<int>(previousBounds.getX() + ratioX * newBounds.getWidth()));
        knobPosition.setY(static_cast<int>(previousBounds.getY() + ratioY * newBounds.getHeight()));
        previousBounds = newBounds;
    }

    juce::String mt_ignite_app_joystick::getKnobDirection()
    {
        const int centerX = getWidth() / 2;
        const int centerY = getHeight() / 2;
        int distanceX = std::abs(knobPosition.x - centerX);
        int distanceY = std::abs(knobPosition.y - centerY);
        int centerThreshold = 3; 
        if (distanceX <= centerThreshold && distanceY <= centerThreshold)
        {
            currentDirection = _Direction::CENTER;
            return "Center";
        }

       Direction knobDirection = getDirectionFromPosition();

        switch (knobDirection)
        {
        case Direction::Up:
            currentDirection = _Direction::UP;
            return "Up";
        case Direction::Down:
            currentDirection = _Direction::DOWN;
            return "Down";
        case Direction::Left:
            currentDirection = _Direction::LEFT;
            return "Left";
        case Direction::Right:
            currentDirection = _Direction::RIGHT;
            return "Right";
        case Direction::UpLeft:
            return "Up-Left";
        case Direction::UpRight:
            return "Up-Right";
        case Direction::DownLeft:
            return "Down-Left";
        case Direction::DownRight:
            return "Down-Right";
        default:
            return ""; 
        }
    }

    mt_ignite_app_joystick::Direction mt_ignite_app_joystick::getDirectionFromPosition() const
    {
        const int centerX = getWidth() / 2;
        const int centerY = getHeight() / 2;
        const float areaWidthPercentage = 0.2f; 
        const float areaHeightPercentage = 0.2f; 
        int totalWidth = getWidth();
        int totalHeight = getHeight();
        int areaWidth = static_cast<int>(totalWidth * areaWidthPercentage);
        int areaHeight = static_cast<int>(totalHeight * areaHeightPercentage);
        int toleranceX = areaWidth / 2; 
        int toleranceY = areaHeight / 2; 
        int distanceX = std::abs(knobPosition.x - centerX);
        int distanceY = std::abs(knobPosition.y - centerY);
        if (distanceX <= toleranceX && distanceY <= toleranceY)
        {
            if (previousKnobPosition.x < knobPosition.x)
                return Direction::Right;
            else if (previousKnobPosition.x > knobPosition.x)
                return Direction::Left;
            else if (previousKnobPosition.y < knobPosition.y)
                return Direction::Down;
            else if (previousKnobPosition.y > knobPosition.y)
                return Direction::Up;
        }
        else if (knobPosition.x < centerX - toleranceX)
        {
            if (knobPosition.y < centerY - toleranceY)
                return Direction::UpLeft;
            else if (knobPosition.y > centerY + toleranceY)
                return Direction::DownLeft;
            else
                return Direction::Left;
        }
        else if (knobPosition.x > centerX + toleranceX)
        {
            if (knobPosition.y < centerY - toleranceY)
                return Direction::UpRight;
            else if (knobPosition.y > centerY + toleranceY)
                return Direction::DownRight;
            else
                return Direction::Right;
        }
        else
        {
            if (knobPosition.y < centerY - toleranceY)
                return Direction::Up;
            else if (knobPosition.y > centerY + toleranceY)
                return Direction::Down;
            else if (knobPosition.x < centerX - toleranceX)
                return Direction::Left;
            else if (knobPosition.x > centerX + toleranceX)
                return Direction::Right;
        }
        return Direction::None;
    }
    double minAngle = -45.0; 
    double maxAngle = 45.0; 

    void mt_ignite_app_joystick::mouseDown(const juce::MouseEvent& event)
    {
        isMouseDragging = true;
        previousKnobPosition = knobPosition;
        knobPosition = event.getPosition();
        knobPosition.setX(juce::jlimit(0, getWidth(), knobPosition.getX()));
        knobPosition.setY(juce::jlimit(0, getHeight(), knobPosition.getY()));
        repaint();
    }

    void mt_ignite_app_joystick::mouseDrag(const juce::MouseEvent& event)
    {
        if (isMouseDragging)
        {
            previousKnobPosition = knobPosition; 
            knobPosition = event.getPosition(); 
            knobPosition.setX(juce::jlimit(0, getWidth(), knobPosition.getX()));
            knobPosition.setY(juce::jlimit(0, getHeight(), knobPosition.getY()));
            updateSelectionAndRepaint();
        }
    }

    void mt_ignite_app_joystick::mouseUp(const juce::MouseEvent&)
    {
        isMouseDragging = false;
        knobPosition = juce::Point<int>(getWidth() / 2, getHeight() / 2);
        updateSelectionAndRepaint();
    }

    void mt_ignite_app_joystick::updateSelectionAndRepaint()
    {
        if (onSelectionChanged)
        {
            onSelectionChanged(currentDirection);
        }
        repaint();
    }
}