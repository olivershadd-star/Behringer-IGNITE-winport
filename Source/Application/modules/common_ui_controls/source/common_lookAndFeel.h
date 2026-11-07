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

#ifndef COMMON_LOOK_AND_FEEL_H
#define COMMONK_LOOK_AND_FEEL_H

namespace ui
{
    using namespace juce;

    class CommonLooknFeel : public juce::LookAndFeel_V4
    {
    public:
        CommonLooknFeel();
        static CommonLooknFeel* getLnf()
        {
            static CommonLooknFeel _commonLnf;
            return &_commonLnf;
        };

    private:
        void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
        void drawTabButton(TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown) override;

    };

    class CommonActionButtonLooknFeel : public LookAndFeel_V4
    {
    public:
        CommonActionButtonLooknFeel();
        static CommonActionButtonLooknFeel* getLnf()
        {
            static CommonActionButtonLooknFeel _commonActionButtonLnf;
            return &_commonActionButtonLnf;
        };
    };

    class CommonPadButtonLooknFeel : public LookAndFeel_V4
    {
    public:
        CommonPadButtonLooknFeel();
        static CommonPadButtonLooknFeel* getLnf()
        {
            static CommonPadButtonLooknFeel _commonPadButtonLnf;
            return &_commonPadButtonLnf;
        };
    };

    class CommonAlertWindow : public LookAndFeel_V4
    {
    public:
        CommonAlertWindow() {};
        static CommonAlertWindow* getLnf()
        {
            static CommonAlertWindow _commonPadAlertWindow;
            return &_commonPadAlertWindow;
        };
        int getAlertWindowButtonHeight();


    };

    class CommonDailogWindow : public LookAndFeel_V4
    {
    public:
        CommonDailogWindow() {};
        static CommonDailogWindow* getLnf()
        {
            static CommonDailogWindow _CommonDailogWindow;
            return &_CommonDailogWindow;
        };
        void drawDocumentWindowTitleBar(DocumentWindow& window, Graphics& g,
            int w, int h, int titleSpaceX, int titleSpaceW,
            const Image* icon, bool drawTitleTextOnLeft) override;
        void positionDocumentWindowButtons(DocumentWindow&,
            int titleBarX, int titleBarY,
            int titleBarW, int titleBarH,
            Button* minimiseButton,
            Button* maximiseButton,
            Button* closeButton,
            bool positionTitleBarButtonsOnLeft) override;

    };

    class CommonToggleButtonLooknFeel : public juce::LookAndFeel_V4
    {
    public:
        CommonToggleButtonLooknFeel();
        static CommonToggleButtonLooknFeel* getLnf()
        {
            static CommonToggleButtonLooknFeel _commonLnf;
            return &_commonLnf;
        };

    private:
        void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

    };

    class CommonTextButtonLooknFeel : public juce::LookAndFeel_V4
    {
    public:
        CommonTextButtonLooknFeel();
        static CommonTextButtonLooknFeel* getLnf()
        {
            static CommonTextButtonLooknFeel _commonLnf;
            return &_commonLnf;
        };

    private:
        void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

    };

    class CustomSliderLookandFeel : public juce::LookAndFeel_V4
    {
    public:
        CustomSliderLookandFeel(){};
        static CustomSliderLookandFeel* getLnf()
        {
            static CustomSliderLookandFeel _commonLnf;
            return &_commonLnf;
        };

    private:
        void drawLinearSlider(Graphics& g, int x, int y, int width, int height,
            float sliderPos,
            float minSliderPos,
            float maxSliderPos,
            const Slider::SliderStyle style, Slider& slider) override;
  
    };

    class ImageButtonLookandFeel : public juce::LookAndFeel_V4
    {
    public:
        ImageButtonLookandFeel() {};
        static ImageButtonLookandFeel* getLnf()
        {
            static ImageButtonLookandFeel _commonLnf;
            return &_commonLnf;
        };

    private:
        void drawImageButton(Graphics&, Image*,
            int imageX, int imageY, int imageW, int imageH,
            const Colour& overlayColour, float imageOpacity, ImageButton&) override;

    };

    class AlertWindowLookandFeel : public juce::LookAndFeel_V4
    {
    public:
        AlertWindowLookandFeel() {
            
        };
        static AlertWindowLookandFeel* getLnf()
        {
            static AlertWindowLookandFeel _commonLnf;
            return &_commonLnf;
        };

    private:
        void drawAlertBox(Graphics&, AlertWindow&, const Rectangle<int>& textArea, TextLayout&) override;

    };

    class EmptyBackgroundLooknFeel : public juce::LookAndFeel_V4
    {
    public:
        EmptyBackgroundLooknFeel(){};
        static EmptyBackgroundLooknFeel* getLnf()
        {
            static EmptyBackgroundLooknFeel _commonLnf;
            return &_commonLnf;
        };

    private:
        void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

    };

    class BrightnessSilderLnF : public juce::LookAndFeel_V4
    {
    public:
        BrightnessSilderLnF() {};
        static BrightnessSilderLnF* getLnf()
        {
            static BrightnessSilderLnF _commonLnf;
            return &_commonLnf;
        };

    private:
        void drawLinearSlider(Graphics& g, int x, int y, int width, int height,
            float sliderPos,
            float minSliderPos,
            float maxSliderPos,
            const Slider::SliderStyle style, Slider& slider) override;

    };

    class CommonRotaryCv_gate :public juce::LookAndFeel_V4
    {
    public:
        CommonRotaryCv_gate() {};
        static CommonRotaryCv_gate* getLnf()
        {
            static CommonRotaryCv_gate _commonLnf;
            return &_commonLnf;
        };

    private:
        void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
            const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override;

    };

    class BarSilderLnF : public juce::LookAndFeel_V4
    {
    public:
        BarSilderLnF() {};
        static BarSilderLnF* getLnf()
        {
            static BarSilderLnF _commonLnf;
            return &_commonLnf;
        };

    private:
        void drawLinearSlider(Graphics& g, int x, int y, int width, int height,
            float sliderPos,
            float minSliderPos,
            float maxSliderPos,
            const Slider::SliderStyle style, Slider& slider) override;
        void drawLinearSliderBackground(Graphics&,
            int x, int y, int width, int height,
            float sliderPos,
            float minSliderPos,
            float maxSliderPos,
            const Slider::SliderStyle style,
            Slider&) override;
        
    };

    class EmptyTextBackgroundLooknFeel : public juce::LookAndFeel_V4
    {
    public:
        EmptyTextBackgroundLooknFeel() {};
        static EmptyTextBackgroundLooknFeel* getLnf()
        {
            static EmptyTextBackgroundLooknFeel _commonLnf;
            return &_commonLnf;
        };

    private:
        void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

        void drawToggleButton(Graphics&, ToggleButton&,
            bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    
    };
    

} // Namespace :: ui
#endif // IGNITE_LOOK_AND_FEEL_H
