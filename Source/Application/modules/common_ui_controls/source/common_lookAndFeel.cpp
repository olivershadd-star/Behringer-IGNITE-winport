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
    using namespace juce;

    CommonLooknFeel::CommonLooknFeel()
    {
        auto theme = Theme::Instance();
        setColourScheme(Theme::getColourScheme());

        // Tabs...
        setColour(juce::TabbedComponent::backgroundColourId, theme.getColour(neutralBlack));
        setColour(juce::TabbedComponent::outlineColourId, theme.getColour(neutralBlack));

        // Label
        setColour(juce::Label::backgroundColourId, theme.getColour(transparentBlack));
        setColour(juce::Label::textColourId, theme.getColour(neutralWhite));
        setColour(juce::Label::outlineColourId, theme.getColour(neutralGrey4));
        setColour(juce::Label::backgroundWhenEditingColourId, theme.getColour(neutralBlack));
        setColour(juce::Label::textWhenEditingColourId, theme.getColour(systemBlue));
        setColour(juce::Label::outlineWhenEditingColourId, theme.getColour(systemBlue));

        // Text Editor
        setColour(juce::TextEditor::textColourId, theme.getColour(neutralBlack));
        setColour(juce::TextEditor::backgroundColourId, theme.getColour(transparentBlack));

        // Buttons..
        setColour(juce::TextButton::ColourIds::buttonColourId, theme.getColour(neutralGrey4));
        setColour(juce::TextButton::ColourIds::buttonOnColourId, theme.getColour(systemBlue).withAlpha((uint8)0x94));
        setColour(juce::TextButton::ColourIds::textColourOffId, theme.getColour(neutralGrey9));
        setColour(juce::TextButton::ColourIds::textColourOnId, theme.getColour(neutralWhite));

        // Slider
        setColour(juce::Slider::backgroundColourId, theme.getColour(neutralGrey4));
        setColour(juce::Slider::trackColourId, theme.getColour(systemBlue).withAlpha((uint8)0x94));
        setColour(juce::Slider::thumbColourId, theme.getColour(systemBlue).withAlpha((uint8)0x94));
        setColour(juce::Slider::textBoxOutlineColourId, theme.getColour(customOrange1).withAlpha((uint8)0x94));
        setColour(juce::Slider::textBoxBackgroundColourId, theme.getColour(systemBlue).withAlpha((uint8)0x94));
        setColour(juce::Slider::textBoxHighlightColourId, theme.getColour(neutralGrey4));
        setColour(juce::Slider::rotarySliderFillColourId, Colour(0xffff9300));
        setColour(juce::Slider::rotarySliderOutlineColourId, Colour(0xffff9300));

        //getSliderPopupFont
    }

    void CommonLooknFeel::drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
    {
        auto cornerSize = 1.0f;
        auto bounds = button.getLocalBounds().toFloat().reduced(0.5f, 0.5f);

        auto baseColour = backgroundColour.withMultipliedSaturation(button.hasKeyboardFocus(true) ? 1.3f : 0.9f)
            .withMultipliedAlpha(button.isEnabled() ? 1.0f : 0.5f);

        if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
            baseColour = baseColour.contrasting(shouldDrawButtonAsDown ? 0.2f : 0.05f);

        g.setColour(baseColour);

        {
            g.fillRoundedRectangle(bounds, cornerSize);

            g.setColour(juce::Colour(color::neutral::grey9));
            g.drawRoundedRectangle(bounds, cornerSize, 1.0f);
        }
    }

    void CommonLooknFeel::drawTabButton(TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown)
    {
        const int margin = 5;
        auto activeArea = button.getActiveArea();
        const bool isFrontTab = button.isFrontTab();
        Path p;

        // Create shape for tab button...
        auto bounds = activeArea;
        if (isFrontTab)
        {
            switch (button.getTabbedButtonBar().getOrientation())
            {
            break; case TabbedButtonBar::TabsAtLeft:   bounds = activeArea.reduced(0, margin); bounds.removeFromLeft(margin);
            break; case TabbedButtonBar::TabsAtRight:  bounds = activeArea.reduced(0, margin); bounds.removeFromRight(margin);
            break; case TabbedButtonBar::TabsAtBottom: bounds = activeArea.reduced(margin, 0); bounds.removeFromBottom(margin);
            break; case TabbedButtonBar::TabsAtTop:    bounds = activeArea.reduced(margin, 0); bounds.removeFromTop(margin);
            }
        }
        else
        {
            bounds = activeArea.reduced(margin);
        }
        p.addRectangle(bounds);

        // Fill background colour...
        g.setColour(Theme::Instance().getColour(neutralGrey4));
        if (button.isEnabled())
            button.setAlpha(1.0);
        else
            button.setAlpha(0.5);

        g.fillPath(p);

        // Fill button outline...
        g.setColour(isFrontTab ? Theme::Instance().getColour(systemBlue) : Theme::Instance().getColour(neutralGrey9));
        g.strokePath(p, PathStrokeType(isFrontTab ? 1.0f : 0.5f));

        // Write button text ...
        bounds = activeArea.reduced(margin);
        AffineTransform t;
        switch (button.getTabbedButtonBar().getOrientation())
        {
        break;  case TabbedButtonBar::TabsAtLeft:   t = t.rotated(MathConstants<float>::pi * -0.5f);
        break;  case TabbedButtonBar::TabsAtRight:  t = t.rotated(MathConstants<float>::pi * 0.5f);
                                                 break;
        }
        g.addTransform(t);
        g.drawFittedText(button.getButtonText().trim(), bounds, Justification::centred, 1);

        CommonMultiSelectTabBarButton* multiSelectButton = dynamic_cast<CommonMultiSelectTabBarButton*>(&button);
        if (multiSelectButton)
        {
            auto textRect = button.getTextArea();
            juce::Rectangle<int> multiCountRect(0, 0, textRect.getWidth(), 12);
            float drawStartx = multiCountRect.getCentreX() - ((multiSelectButton->getNumOfSelection() * 7 + (multiSelectButton->getNumOfSelection() - 1 * 3.0f)) / 2.0f);
            for (int i = 0; i < multiSelectButton->getNumOfSelection(); i++)
            {
                if (i == multiSelectButton->getCurrentSelection())
                    g.setColour(Theme::Instance().multiSelectTabActiveColour());
                else
                    g.setColour(Theme::Instance().multiSelectTabInActiveColour());
                g.fillEllipse(drawStartx, 8, 7, 7);
                drawStartx += 7 + 3;
            }
        }
    }

    CommonActionButtonLooknFeel::CommonActionButtonLooknFeel()
    {
        setColourScheme(Theme::getColourScheme());

        // Buttons..
        setColour(TextButton::ColourIds::buttonColourId, Theme::Instance().getColour(systemBlue));
        setColour(TextButton::ColourIds::buttonOnColourId, Theme::Instance().getColour(systemBlue));
        setColour(TextButton::ColourIds::textColourOffId, Theme::Instance().getColour(neutralWhite));
        setColour(TextButton::ColourIds::textColourOnId, Theme::Instance().getColour(neutralWhite));
    }

    CommonPadButtonLooknFeel::CommonPadButtonLooknFeel()
    {
        setColourScheme(Theme::getColourScheme());

        // Text Editor
        setColour(juce::TextEditor::textColourId, Theme::Instance().getColour(neutralWhite));
        setColour(juce::TextEditor::backgroundColourId, juce::Colours::transparentBlack);

        // Buttons..
        setColour(juce::TextButton::ColourIds::buttonColourId, Theme::Instance().getColour(neutralGrey1));
        setColour(juce::TextButton::ColourIds::buttonOnColourId, Theme::Instance().getColour(systemBlue).withAlpha((uint8)0x94));
        setColour(juce::TextButton::ColourIds::textColourOffId, Theme::Instance().getColour(neutralGrey9));
        setColour(juce::TextButton::ColourIds::textColourOnId, Theme::Instance().getColour(neutralWhite));
    }

    int CommonAlertWindow::getAlertWindowButtonHeight()
    {
        return (int)(48 * heightSaveoption);
    }

    void CommonDailogWindow::drawDocumentWindowTitleBar(DocumentWindow& window, Graphics& g,
        int w, int h, int titleSpaceX, int titleSpaceW,
        const Image* icon, bool drawTitleTextOnLeft)
    {
        if (w * h == 0)
            return;

        auto isActive = window.isActiveWindow();

        g.setColour(juce::Colour(ui::Theme::Instance().getColour(customBlue7)));
        g.fillRect(0, 0, w, h);
        g.setColour(ui::Theme::Instance().getColour(customBlue8));
        g.fillRect(1, 1, w - 2, h);
    

        Font font((float)h * 0.3f, Font::plain);
        g.setFont(font);

        auto textW = font.getStringWidth(window.getName());
        auto iconW = 0;
        auto iconH = 0;

        if (icon != nullptr)
        {
            iconH = static_cast<int> (font.getHeight());
            iconW = icon->getWidth() * iconH / icon->getHeight() + 4;
        }

        textW = jmin(titleSpaceW, textW + iconW);
        auto textX = drawTitleTextOnLeft ? titleSpaceX
            : jmax(titleSpaceX, (w - textW) / 2);

        if (textX + textW > titleSpaceX + titleSpaceW)
            textX = titleSpaceX + titleSpaceW - textW;

        if (icon != nullptr)
        {
            g.setOpacity(isActive ? 1.0f : 0.6f);
            g.drawImageWithin(*icon, textX, (h - iconH) / 2, iconW, iconH,
                RectanglePlacement::centred, false);
            textX += iconW;
            textW -= iconW;
        }

        if (window.isColourSpecified(DocumentWindow::textColourId) || isColourSpecified(DocumentWindow::textColourId))
            g.setColour(window.findColour(DocumentWindow::textColourId));
        else
            g.setColour(getCurrentColourScheme().getUIColour(ColourScheme::defaultText));

        g.drawText(window.getName(), textX, 8, textW, h, Justification::centredLeft, true);
    }

    void CommonDailogWindow::positionDocumentWindowButtons(DocumentWindow&, int titleBarX, int titleBarY, int titleBarW, int titleBarH,
        Button* minimiseButton, Button* maximiseButton, Button* closeButton, bool positionTitleBarButtonsOnLeft)
    {
        auto buttonW = static_cast<int> (titleBarH * 0.35);

        auto x = positionTitleBarButtonsOnLeft ? titleBarX
            : titleBarX + titleBarW - buttonW;

        if (closeButton != nullptr)
        {
            closeButton->setBounds((int)x - 10, (int)titleBarY + 10, (int)buttonW, (int)(titleBarH * 0.35));
            x += positionTitleBarButtonsOnLeft ? buttonW : -buttonW;
        }

        if (positionTitleBarButtonsOnLeft)
            std::swap(minimiseButton, maximiseButton);

        if (maximiseButton != nullptr)
        {
            maximiseButton->setBounds(x, titleBarY, buttonW, titleBarH);
            x += positionTitleBarButtonsOnLeft ? buttonW : -buttonW;
        }

        if (minimiseButton != nullptr)
            minimiseButton->setBounds(x, titleBarY, buttonW, titleBarH);
    }

    CommonToggleButtonLooknFeel::CommonToggleButtonLooknFeel()
    {
        setColourScheme(Theme::getColourScheme());

        // Buttons..
        setColour(TextButton::ColourIds::buttonColourId, Theme::Instance().getColour(customBlue16));
        setColour(TextButton::ColourIds::buttonOnColourId, Theme::Instance().getColour(customOrange6));
        setColour(TextButton::ColourIds::textColourOffId, Theme::Instance().getColour(neutralWhite));
        setColour(TextButton::ColourIds::textColourOnId, Theme::Instance().getColour(neutralWhite));
        setColour(juce::TextEditor::outlineColourId, Theme::Instance().getColour(customBlue15));
        setColour(juce::TextEditor::focusedOutlineColourId, Theme::Instance().getColour(customOrange1));
        
    }

    void CommonToggleButtonLooknFeel::drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
    {
        auto cornerSize = 6.0f;
        auto bounds = button.getLocalBounds().toFloat().reduced(0.5f, 0.5f);

        auto baseColour = backgroundColour.withMultipliedSaturation(button.hasKeyboardFocus(true) ? 1.3f : 0.9f)
            .withMultipliedAlpha(button.isEnabled() ? 1.0f : 0.5f);

        if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
            baseColour = baseColour.contrasting(shouldDrawButtonAsDown ? 0.2f : 0.05f);

        auto bgColour = button.getToggleState() ? button.findColour(TextButton::ColourIds::buttonOnColourId) : button.findColour(TextButton::ColourIds::buttonColourId);
        g.setColour(bgColour);

        auto flatOnLeft = button.isConnectedOnLeft();
        auto flatOnRight = button.isConnectedOnRight();
        auto flatOnTop = button.isConnectedOnTop();
        auto flatOnBottom = button.isConnectedOnBottom();

        if (flatOnLeft || flatOnRight || flatOnTop || flatOnBottom)
        {
            Path path;
            path.addRoundedRectangle(bounds.getX(), bounds.getY(),
                bounds.getWidth(), bounds.getHeight(),
                cornerSize, cornerSize,
                !(flatOnLeft || flatOnTop),
                !(flatOnRight || flatOnTop),
                !(flatOnLeft || flatOnBottom),
                !(flatOnRight || flatOnBottom));

            g.fillPath(path);

            g.setColour(ui::Theme::Instance().getColour(customBlue9));
            g.strokePath(path, PathStrokeType(1.0f));
        }
        else
        {
            g.fillRoundedRectangle(bounds, cornerSize);
            
            button.isMouseOver()?g.setColour(button.findColour(juce::TextEditor::focusedOutlineColourId)):g.setColour(button.findColour(juce::TextEditor::outlineColourId));
            g.drawRoundedRectangle(bounds, cornerSize, 2.0f);
        }

        auto* p = dynamic_cast<CommonButton*>(&button);

        if (p != nullptr)
        {
            auto fontSize = jmin(15.0f, (float)button.getHeight() * 0.75f);
            auto tickWidth = fontSize * 1.1f;
            ignoreUnused(button.isEnabled(), shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);

            Rectangle<float> tickBounds(4.0f, ((float)button.getHeight() - tickWidth) * 0.5f, tickWidth * 1.5f, tickWidth);

            if (button.getToggleState())
            {
                g.setColour(button.findColour(ToggleButton::tickColourId));
                auto tick = getTickShape(0.75f);
                g.fillPath(tick, tick.getTransformToScaleToFit(tickBounds.toFloat(), false));
            }
        }
    }

    CommonTextButtonLooknFeel::CommonTextButtonLooknFeel()
    {
        setColourScheme(Theme::getColourScheme());
        setColour(TextButton::ColourIds::buttonColourId, Theme::Instance().getColour(neutralWhite));
        setColour(TextButton::ColourIds::buttonOnColourId, Theme::Instance().getColour(neutralWhite));
        setColour(TextButton::ColourIds::textColourOffId, Theme::Instance().getColour(neutralWhite));
        setColour(TextButton::ColourIds::textColourOnId, Theme::Instance().getColour(neutralWhite));
        setColour(juce::TextEditor::outlineColourId, Theme::Instance().getColour(customBlue12));
    }

    void CommonTextButtonLooknFeel::drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
    {
        auto cornerSize = 6.0f;
        auto bounds = button.getLocalBounds().toFloat().reduced(0.5f, 0.5f);

        auto baseColour = backgroundColour.withMultipliedSaturation(button.hasKeyboardFocus(true) ? 1.3f : 0.9f)
            .withMultipliedAlpha(button.isEnabled() ? 1.0f : 0.5f);

        if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
            baseColour = baseColour.contrasting(shouldDrawButtonAsDown ? 0.2f : 0.05f);

        auto bgColour = button.getToggleState() ? button.findColour(TextButton::ColourIds::buttonOnColourId) : button.findColour(TextButton::ColourIds::buttonColourId);
        g.setColour(bgColour);

        auto flatOnLeft = button.isConnectedOnLeft();
        auto flatOnRight = button.isConnectedOnRight();
        auto flatOnTop = button.isConnectedOnTop();
        auto flatOnBottom = button.isConnectedOnBottom();

        if (flatOnLeft || flatOnRight || flatOnTop || flatOnBottom)
        {
            Path path;
            if (flatOnRight)
            {
                path.addRoundedRectangle(bounds.getX(), bounds.getY()+0.5f,
                    bounds.getWidth()+10, bounds.getHeight()-1,
                    cornerSize, cornerSize,
                    !(flatOnLeft || flatOnTop),
                    !(flatOnRight || flatOnTop),
                    !(flatOnLeft || flatOnBottom),
                    !(flatOnRight || flatOnBottom));
                g.setColour(ui::Theme::Instance().getColour(customBlue9));
                g.fillPath(path);
                g.setColour(ui::Theme::Instance().getColour(transparentBlack));
               
                g.strokePath(path, PathStrokeType(1.0f));
            }
            else
            {
                path.addRoundedRectangle((float)(bounds.getX()-1), (float)(bounds.getY()+0.5),
                    (float)bounds.getWidth(), (float)(bounds.getHeight()-1),
                    (float)cornerSize, (float)cornerSize,
                    !(flatOnLeft || flatOnTop),
                    !(flatOnRight || flatOnTop),
                    !(flatOnLeft || flatOnBottom),
                    !(flatOnRight || flatOnBottom)); 
                g.setColour(ui::Theme::Instance().getColour(customBlue9));
                g.fillPath(path);
                g.setColour(ui::Theme::Instance().getColour(transparentBlack));

                g.strokePath(path, PathStrokeType(1.0f));
            }
        }
        else
        {
            g.fillRoundedRectangle(bounds, cornerSize);

            g.setColour(button.findColour(juce::TextEditor::outlineColourId));
            g.drawRoundedRectangle(bounds, cornerSize, 2.0f);
        }
    }

    void CustomSliderLookandFeel::drawLinearSlider(Graphics& g, int x, int y, int width, int height,
        float sliderPos,
        float minSliderPos,
        float maxSliderPos,
        const Slider::SliderStyle style, Slider& slider)
    {
        if (slider.isBar())
        {
            g.setColour(slider.findColour(Slider::backgroundColourId));
            g.fillRoundedRectangle((float)x-1, (float)1, (float)width, (float)height , 1.0f);

            g.setColour(slider.findColour(Slider::trackColourId));
            g.fillRoundedRectangle((float)x-1, (float)y,(float) ((sliderPos+2) - (x-1)), (float)height, 1.0f);

            if (slider.isEnabled())
            {
                auto* p = dynamic_cast<CommonSlider*>(&slider);

                if (p != nullptr && p->focusState)
                {
                    g.setColour(ui::Theme::Instance().getColour(ui::customOrange));
                    g.drawRoundedRectangle((float)x - 1, (float)1, (float)width, (float)height, 1.0f, 1.4f);
                }
                else
                {
                    g.setColour(ui::Theme::Instance().getColour(ui::customGrey4));
                    g.drawRoundedRectangle((float)x - 1, (float)1, (float)width, (float)height, 1.0f, 1.4f);
                }
            }
            else
            {
                g.setColour(ui::Theme::Instance().getColour(ui::customGrey4));
                g.drawRoundedRectangle((float)x - 1, (float)1, (float)width, (float)height, 1.0f, 1.4f);
            }
        }
        else
        {
            auto isTwoVal = (style == Slider::SliderStyle::TwoValueVertical || style == Slider::SliderStyle::TwoValueHorizontal);
            auto isThreeVal = (style == Slider::SliderStyle::ThreeValueVertical || style == Slider::SliderStyle::ThreeValueHorizontal);

            auto trackWidth = jmin(6.0f, slider.isHorizontal() ? (float)height * 0.25f : (float)width * 0.25f);

            Point<float> startPoint(slider.isHorizontal() ? (float)x : (float)x + (float)width * 0.5f,
                slider.isHorizontal() ? (float)y + (float)height * 0.5f : (float)(height + y));

            Point<float> endPoint(slider.isHorizontal() ? (float)(width + x) : startPoint.x,
                slider.isHorizontal() ? startPoint.y : (float)y);

            Path backgroundTrack;
            backgroundTrack.startNewSubPath(startPoint);
            backgroundTrack.lineTo(endPoint);
            g.setColour(slider.findColour(Slider::backgroundColourId));
            g.strokePath(backgroundTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

            Path valueTrack;
            Point<float> minPoint, maxPoint, thumbPoint;

            if (isTwoVal || isThreeVal)
            {
                minPoint = { slider.isHorizontal() ? minSliderPos : (float)width * 0.5f,
                             slider.isHorizontal() ? (float)height * 0.5f : minSliderPos };

                if (isThreeVal)
                    thumbPoint = { slider.isHorizontal() ? sliderPos : (float)width * 0.5f,
                                   slider.isHorizontal() ? (float)height * 0.5f : sliderPos };

                maxPoint = { slider.isHorizontal() ? maxSliderPos : (float)width * 0.5f,
                             slider.isHorizontal() ? (float)height * 0.5f : maxSliderPos };
            }
            else
            {
                auto kx = slider.isHorizontal() ? sliderPos : ((float)x + (float)width * 0.5f);
                auto ky = slider.isHorizontal() ? ((float)y + (float)height * 0.5f) : sliderPos;

                minPoint = startPoint;
                maxPoint = { kx, ky };
            }

            auto thumbWidth = getSliderThumbRadius(slider);

            valueTrack.startNewSubPath(minPoint);
            valueTrack.lineTo(isThreeVal ? thumbPoint : maxPoint);
            g.setColour(slider.findColour(Slider::trackColourId));
            g.strokePath(valueTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

            if (!isTwoVal)
            {
                g.setColour(slider.findColour(Slider::thumbColourId));
                g.fillEllipse(Rectangle<float>(static_cast<float> (thumbWidth), static_cast<float> (thumbWidth)).withCentre(isThreeVal ? thumbPoint : maxPoint));
            }

            if (isTwoVal || isThreeVal)
            {
                auto sr = jmin(trackWidth, (slider.isHorizontal() ? (float)height : (float)width) * 0.4f);
                auto pointerColour = slider.findColour(Slider::thumbColourId);

                if (slider.isHorizontal())
                {
                    drawPointer(g, minSliderPos - sr,
                        jmax(0.0f, (float)y + (float)height * 0.5f - trackWidth * 2.0f),
                        trackWidth * 2.0f, pointerColour, 2);

                    drawPointer(g, maxSliderPos - trackWidth,
                        jmin((float)(y + height) - trackWidth * 2.0f, (float)y + (float)height * 0.5f),
                        trackWidth * 2.0f, pointerColour, 4);
                }
                else
                {
                    drawPointer(g, jmax(0.0f, (float)x + (float)width * 0.5f - trackWidth * 2.0f),
                        minSliderPos - trackWidth,
                        trackWidth * 2.0f, pointerColour, 1);

                    drawPointer(g, jmin((float)(x + width) - trackWidth * 2.0f, (float)x + (float)width * 0.5f), maxSliderPos - sr,
                        trackWidth * 2.0f, pointerColour, 3);
                }
            }
        }
    }

    void ImageButtonLookandFeel::drawImageButton(Graphics& g, Image* image,
        int imageX, int imageY, int imageW, int imageH,
        const Colour& overlayColour,
        float imageOpacity,
        ImageButton& button)
    {
        auto* p = dynamic_cast<CommonImageButton*>(&button);
      
        AffineTransform t = RectanglePlacement(RectanglePlacement::stretchToFit)
            .getTransformToFit(image->getBounds().toFloat(),
                Rectangle<int>(imageX, imageY, imageW, imageH).toFloat());
        
        g.setOpacity(imageOpacity);
        if (!button.isEnabled())
        {
                g.drawImageTransformed((p->getDisabledImage()), t, false);
        }
        else
        {
                if (button.getToggleState())
                {
                    if (p->isFocused)
                        g.drawImageTransformed((p->gethoverImages(1)), t, false);
                    else
                        g.drawImageTransformed((p->getDownImage()), t, false);
                }
                else
                {
                    if (p->isFocused)
                        g.drawImageTransformed((p->gethoverImages(0)), t, false);
                    else
                        g.drawImageTransformed((p->getNormalImage()), t, false);
                }
        }
    }

    void EmptyBackgroundLooknFeel::drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
    {
        
        //NoBackground colour
    }

    void BrightnessSilderLnF::drawLinearSlider(Graphics& g, int x, int y, int width, int height,
        float sliderPos,
        float minSliderPos,
        float maxSliderPos,
        const Slider::SliderStyle style, Slider& slider)
    {
        if (slider.isBar())
        {
            g.setColour(slider.findColour(Slider::trackColourId));
            g.fillRect(slider.isHorizontal() ? Rectangle<float>(static_cast<float> (x), (float)y + 0.5f, sliderPos - (float)x, (float)height - 1.0f)
                : Rectangle<float>((float)x + 0.5f, sliderPos, (float)width - 1.0f, (float)y + ((float)height - sliderPos)));
        }
        else
        {
            auto isTwoVal = (style == Slider::SliderStyle::TwoValueVertical || style == Slider::SliderStyle::TwoValueHorizontal);
            auto isThreeVal = (style == Slider::SliderStyle::ThreeValueVertical || style == Slider::SliderStyle::ThreeValueHorizontal);

            auto trackWidth = (float)height * 0.4f;

            Point<float> startPoint(slider.isHorizontal() ? (float)x : (float)x + (float)width * 0.5f,
                slider.isHorizontal() ? (float)y + (float)height * 0.5f : (float)(height + y));

            Point<float> endPoint(slider.isHorizontal() ? (float)(width + x) : startPoint.x,
                slider.isHorizontal() ? startPoint.y : (float)y);

            Path backgroundTrack;
            backgroundTrack.startNewSubPath(startPoint);
            backgroundTrack.lineTo(endPoint);
            g.setColour(slider.findColour(Slider::backgroundColourId));
            g.strokePath(backgroundTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });
            if(!slider.isMouseOver())
                g.setColour(Theme::Instance().getColour(customBlue19));
            else
                g.setColour(Theme::Instance().getColour(customOrange7));
            g.drawRoundedRectangle(Rectangle<float>(static_cast<float> (x - 6.0f), (float)y + 10.0f, width + 13.0f, (float)height / 3.0f), 4.0f, 1.0f);

            Path valueTrack;
            Point<float> minPoint, maxPoint, thumbPoint;

            if (isTwoVal || isThreeVal)
            {
                minPoint = { slider.isHorizontal() ? minSliderPos : (float)width * 0.5f,
                             slider.isHorizontal() ? (float)height * 0.5f : minSliderPos };

                if (isThreeVal)
                    thumbPoint = { slider.isHorizontal() ? sliderPos : (float)width * 0.5f,
                                   slider.isHorizontal() ? (float)height * 0.5f : sliderPos };

                maxPoint = { slider.isHorizontal() ? maxSliderPos : (float)width * 0.5f,
                             slider.isHorizontal() ? (float)height * 0.5f : maxSliderPos };
            }
            else
            {
                auto kx = slider.isHorizontal() ? sliderPos : ((float)x + (float)width * 0.5f);
                auto ky = slider.isHorizontal() ? ((float)y + (float)height * 0.5f) : sliderPos;

                minPoint = startPoint;
                maxPoint = { kx, ky };
            }

            auto thumbWidth = (float)height * 0.5f;

            valueTrack.startNewSubPath(minPoint);
            valueTrack.lineTo(isThreeVal ? thumbPoint : maxPoint);
            g.setColour(slider.findColour(Slider::trackColourId));
            g.strokePath(valueTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

            if (!isTwoVal)
            {
                g.setColour(slider.findColour(Slider::thumbColourId));
                g.fillEllipse(Rectangle<float>(static_cast<float> (thumbWidth), static_cast<float> (thumbWidth)).withCentre(isThreeVal ? thumbPoint : maxPoint));
            }
            
            if (isTwoVal || isThreeVal)
            {
                auto sr = jmin(trackWidth, (slider.isHorizontal() ? (float)height : (float)width) * 0.4f);
                auto pointerColour = slider.findColour(Slider::thumbColourId);

                if (slider.isHorizontal())
                {
                    drawPointer(g, minSliderPos - sr,
                        jmax(0.0f, (float)y + (float)height * 0.5f - trackWidth * 2.0f),
                        trackWidth * 2.0f, pointerColour, 2);

                    drawPointer(g, maxSliderPos - trackWidth,
                        jmin((float)(y + height) - trackWidth * 2.0f, (float)y + (float)height * 0.5f),
                        trackWidth * 2.0f, pointerColour, 4);
                }
                else
                {
                    drawPointer(g, jmax(0.0f, (float)x + (float)width * 0.5f - trackWidth * 2.0f),
                        minSliderPos - trackWidth,
                        trackWidth * 2.0f, pointerColour, 1);

                    drawPointer(g, jmin((float)(x + width) - trackWidth * 2.0f, (float)x + (float)width * 0.5f), maxSliderPos - sr,
                        trackWidth * 2.0f, pointerColour, 3);
                
                    
                }
            }
        }
    }


        void CommonRotaryCv_gate::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
            const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
        {
            auto theme = Theme::Instance();
            auto outline = slider.findColour(Slider::rotarySliderOutlineColourId);
            auto fill = slider.findColour(Slider::rotarySliderFillColourId);

            auto bounds = Rectangle<int>(x, y, width, height).toFloat();

            auto radius = jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
            auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
            auto lineW = jmin(4.2f, radius * 0.5f);
            auto arcRadius = radius - lineW * 0.5f;
            auto innerRadius = arcRadius * 2 - (3.2f * lineW);

            // Draw background arc...
            Path backgroundArc;
            backgroundArc.addCentredArc(bounds.getCentreX(), bounds.getCentreY(), arcRadius, arcRadius, 0.0f, rotaryStartAngle, rotaryEndAngle, true);
            g.setColour(outline);
            g.strokePath(backgroundArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::rounded));

            // Draw filled arc...
            Path valueArc;
            valueArc.addCentredArc(bounds.getCentreX(), bounds.getCentreY(), arcRadius, arcRadius, 0.0f, rotaryStartAngle, toAngle, true);
            g.setColour(ui::Theme::Instance().getColour(customOrange));
            g.strokePath(valueArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::rounded));

            g.setColour(slider.findColour(Slider::ColourIds::rotarySliderFillColourId));
            g.fillEllipse(Rectangle<float>(innerRadius, innerRadius).withCentre(bounds.getCentre()));

            // Draw Inner Circle...
#if 0
                if (!slider.isMouseOver() || !slider.isEnabled() )
                {
                    g.setColour(slider.findColour());
                    g.fillEllipse(Rectangle<float>(innerRadius, innerRadius).withCentre(bounds.getCentre()));
                }
                else
                {
                    slider.setColour(Slider::ColourIds::rotarySliderFillColourId, ui::Theme::Instance().getColour(customBlue19));
                    g.setColour(ui::Theme::Instance().getColour(customBlue19));
                    g.fillEllipse(Rectangle<float>(innerRadius, innerRadius).withCentre(bounds.getCentre()));
                }
#endif

            // Thumb...
            Path positionArc;
            positionArc.addRectangle(-lineW * .4f, -(innerRadius * .4f), (lineW * .7f), (innerRadius * .4f));
            positionArc.applyTransform(juce::AffineTransform::rotation(toAngle).translated(bounds.getCentreX(), bounds.getCentreY()));
            g.setColour(ui::Theme::Instance().getColour(customOrange));
            g.fillPath(positionArc);
            
        }

    void AlertWindowLookandFeel::drawAlertBox(Graphics& g, AlertWindow& alert, const Rectangle<int>& textArea, TextLayout& textLayout)
    {
        auto cornerSize = 4.0f;
        g.setColour(Colour(0xFF238FCA));
        //g.setColour(alert.findColour(Slider::trackColourId));
        g.drawRoundedRectangle(alert.getLocalBounds().toFloat(), cornerSize, 2.0f);

        auto bounds = alert.getLocalBounds().reduced(1);
        g.reduceClipRegion(bounds);

        g.setColour(Colour(0xFF238FCA));
        //g.setColour(alert.findColour(AlertWindow::backgroundColourId));
        g.fillRoundedRectangle(bounds.toFloat(), cornerSize);

        auto iconSpaceUsed = 0;

        auto iconWidth = 80;
        auto iconSize = juce::jmin(iconWidth + 50, bounds.getHeight() + 20);

        if (alert.containsAnyExtraComponents() || alert.getNumButtons() > 2)
            iconSize = juce::jmin(iconSize, textArea.getHeight() + 50);

        Rectangle<int> iconRect(iconSize / -10, iconSize / -10,
            iconSize, iconSize);

        if (alert.getAlertType() != MessageBoxIconType::NoIcon)
        {
            Path icon;
            char character;
            uint32 colour;

            if (alert.getAlertType() == MessageBoxIconType::WarningIcon)
            {
                character = '!';

                icon.addTriangle((float)iconRect.getX() + (float)iconRect.getWidth() * 0.5f, (float)iconRect.getY(),
                    static_cast<float> (iconRect.getRight()), static_cast<float> (iconRect.getBottom()),
                    static_cast<float> (iconRect.getX()), static_cast<float> (iconRect.getBottom()));

                icon = icon.createPathWithRoundedCorners(5.0f);
                colour = 0x66ff2a00;
            }
            else
            {
                colour = Colour(0xff00b0b9).withAlpha(0.4f).getARGB();
                character = alert.getAlertType() == MessageBoxIconType::InfoIcon ? 'i' : '?';

                icon.addEllipse(iconRect.toFloat());
            }

            GlyphArrangement ga;
            ga.addFittedText({ (float)iconRect.getHeight() * 0.9f, Font::bold },
                String::charToString((juce_wchar)(uint8)character),
                static_cast<float> (iconRect.getX()), static_cast<float> (iconRect.getY()),
                static_cast<float> (iconRect.getWidth()), static_cast<float> (iconRect.getHeight()),
                Justification::centred, false);
            ga.createPath(icon);

            icon.setUsingNonZeroWinding(false);
            g.setColour(Colour(colour));
            g.fillPath(icon);

            iconSpaceUsed = iconWidth;
        }

        g.setColour(alert.findColour(AlertWindow::textColourId));

        Rectangle<int> alertBounds(bounds.getX() + iconSpaceUsed, 30,
            bounds.getWidth(), bounds.getHeight() - getAlertWindowButtonHeight() - 20);

        textLayout.draw(g, alertBounds.toFloat());
    }

    void BarSilderLnF::drawLinearSlider(Graphics& g, int x, int y, int width, int height,
        float sliderPos,
        float minSliderPos,
        float maxSliderPos,
        const Slider::SliderStyle style, Slider& slider)
    {
        if (slider.isBar())
        {
            g.setColour(Theme::Instance().getColour(customGrey4));
            g.fillRoundedRectangle(Rectangle<float>((float)x + 0.5f, sliderPos, (float)width - 1.0f, (float)y + ((float)height - sliderPos)), 5.1f);

            if (!slider.isMouseOver())
            {
                g.setColour(Theme::Instance().getColour(customGrey1));
                g.drawRoundedRectangle((float)(x + 0.5f), (float)0.5, (float)(width - 1.0f), (float)(height), 5.1f, 2.0f);
            }
            else
            {
                g.setColour(Colour(0xFFAFE4FF));
                g.drawRoundedRectangle((float)(x - 0.5f), (float)0.5, (float)(width - 1.0f), (float)(height), 5.1f, 1.0f);
            }
        }
        else
        {
            Image dropImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile(slider.isMouseOver()?"bg-barslider-hover.png":"bg-barslider-default.png"));
            g.drawImage(dropImage, Rectangle<float>{(float)x+1.3f, (float)y-12, (float)36, ((float)slider.getHeight())}, RectanglePlacement::stretchToFit);
            
            auto isTwoVal = (style == Slider::SliderStyle::TwoValueVertical || style == Slider::SliderStyle::TwoValueHorizontal);
            auto isThreeVal = (style == Slider::SliderStyle::ThreeValueVertical || style == Slider::SliderStyle::ThreeValueHorizontal);

            auto trackWidth = jmin(6.0f, slider.isHorizontal() ? (float)height * 0.25f : (float)width * 0.25f);

            Point<float> startPoint(slider.isHorizontal() ? (float)x : (float)x + (float)width * 0.5f,
                slider.isHorizontal() ? (float)y + (float)height * 0.5f : (float)(height + y));

            Point<float> endPoint(slider.isHorizontal() ? (float)(width + x) : startPoint.x,
                slider.isHorizontal() ? startPoint.y : (float)y);

            Path backgroundTrack;
            backgroundTrack.startNewSubPath(startPoint);
            backgroundTrack.lineTo(endPoint);
            g.setColour(slider.findColour(Slider::backgroundColourId));
            g.strokePath(backgroundTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

            Path valueTrack;
            Point<float> minPoint, maxPoint, thumbPoint;

            if (isTwoVal || isThreeVal)
            {
                minPoint = { slider.isHorizontal() ? minSliderPos : (float)width * 0.5f,
                             slider.isHorizontal() ? (float)height * 0.5f : minSliderPos };

                if (isThreeVal)
                    thumbPoint = { slider.isHorizontal() ? sliderPos : (float)width * 0.5f,
                                   slider.isHorizontal() ? (float)height * 0.5f : sliderPos };

                maxPoint = { slider.isHorizontal() ? maxSliderPos : (float)width * 0.5f,
                             slider.isHorizontal() ? (float)height * 0.5f : maxSliderPos };
            }
            else
            {
                auto kx = slider.isHorizontal() ? sliderPos : ((float)x + (float)width * 0.5f);
                auto ky = slider.isHorizontal() ? ((float)y + (float)height * 0.5f) : sliderPos;

                minPoint = startPoint;
                maxPoint = { kx, ky };
            }

            valueTrack.startNewSubPath(minPoint);
            valueTrack.lineTo(isThreeVal ? thumbPoint : maxPoint);
            g.setColour(slider.findColour(Slider::trackColourId));
            g.strokePath(valueTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

            Point<float> startPoint1((float)x + (float)width * 0.5f, (float)y + (float)height*0.5f);
            Path valueTrack1;
            Point<float> endPoint1((float)x + (float)width * 0.5f, sliderPos);
            
            valueTrack1.startNewSubPath(startPoint1);
            valueTrack1.lineTo(endPoint1);
            g.setColour(Theme::Instance().getColour(customOrange));
            g.strokePath(valueTrack1, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

            if (!isTwoVal)
            {
               // g.setColour(slider.findColour(Slider::thumbColourId));
               //g.fillEllipse(Rectangle<float>(static_cast<float> (thumbWidth), static_cast<float> (thumbWidth)).withCentre(isThreeVal ? thumbPoint : maxPoint));
            }

            dropImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile(slider.isMouseOver() ?"knob-barslider-hover.png":"knob-barslider-default.png"));
            g.drawImage(dropImage, Rectangle<float>{(float)x + 7.7f, (float)sliderPos-6.5f , (float)23, ((float)15)}, RectanglePlacement::centred);

            if (isTwoVal || isThreeVal)
            {
                auto sr = jmin(trackWidth, (slider.isHorizontal() ? (float)height : (float)width) * 0.4f);
                auto pointerColour = slider.findColour(Slider::thumbColourId);

                if (slider.isHorizontal())
                {
                    drawPointer(g, minSliderPos - sr,
                        jmax(0.0f, (float)y + (float)height * 0.5f - trackWidth * 2.0f),
                        trackWidth * 2.0f, pointerColour, 2);

                    drawPointer(g, maxSliderPos - trackWidth,
                        jmin((float)(y + height) - trackWidth * 2.0f, (float)y + (float)height * 0.5f),
                        trackWidth * 2.0f, pointerColour, 4);
                }
                else
                {
                    drawPointer(g, jmax(0.0f, (float)x + (float)width * 0.5f - trackWidth * 2.0f),
                        minSliderPos - trackWidth,
                        trackWidth * 2.0f, pointerColour, 1);

                    drawPointer(g, jmin((float)(x + width) - trackWidth * 2.0f, (float)x + (float)width * 0.5f), maxSliderPos - sr,
                        trackWidth * 2.0f, pointerColour, 3);
                }
            }
        }
    }
        void BarSilderLnF::drawLinearSliderBackground(Graphics&,
            int x, int y, int width, int height,
            float sliderPos,
            float minSliderPos,
            float maxSliderPos,
            const Slider::SliderStyle style,
            Slider&)
        {

        }

    void EmptyTextBackgroundLooknFeel::drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
    {

    }

    void EmptyTextBackgroundLooknFeel::drawToggleButton(Graphics&, ToggleButton&,
        bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
    {

    }

} // namespace :: ui
