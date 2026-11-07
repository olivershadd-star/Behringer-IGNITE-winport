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
	class IgniteStep;

	class PatternBarLengthCtl : public juce::Component,
		public CommonButton::Listener,
		public CommonSlider::Listener
	{
	public:
		juce::Atomic<bool> isDialogOpen{ false };

		PatternBarLengthCtl();
		~PatternBarLengthCtl() override;

		void setSliderValue(int steps, int ticks);
		const mt::Ignite::track::patternLenInfo& getPatternLenData(void) const { return(patternLenData); }
		bool pannelKeyHandler(paramId_t param, uint32_t keyValue);
		void setLenInStepSliderRange(int newMin, int newMax, int newStepSize = stepLengthStepSize) { stepSlider.setRange(newMin, newMax, stepLengthStepSize); }

		static PatternBarLengthCtl* getPatternBarLengthCtlInstance()
		{
			static PatternBarLengthCtl* getPatternBarLengthCtlObj;
			if (NULL == getPatternBarLengthCtlObj)
			{
				getPatternBarLengthCtlObj = new PatternBarLengthCtl();
			}

			return getPatternBarLengthCtlObj;
		}

		bool IsEditing()
		{
			if (isDialogOpen.get() == true)
				return true;
			return false;
		};
		void updateTickRange(int min, int max) { tickSlider.setRange(min, max, tickLengthStepSize); }
	private:
#define STEP_LENGTH_VIEW 7
		enum stepLengthViewItemID
		{
			NO_FOCUS = 0,
		//	KEY_HOLD,
		//	KEY_STEP,
			KEY_STEP_DEC,
			KEY_STEP_INC,
			KEY_TICK_DEC,
			KEY_TIC_INC,
			KEY_CANCEL,
			KEY_APPLY,
			FOCUS_MAX = KEY_APPLY
		};

		uint8_t stepLengthView[STEP_LENGTH_VIEW] = { NO_FOCUS, /*KEY_HOLD, KEY_STEP,*/ KEY_STEP_DEC, KEY_STEP_INC, KEY_TICK_DEC, KEY_TIC_INC, KEY_CANCEL, KEY_APPLY };
		int keyFocusedItem = stepLengthViewItemID::NO_FOCUS;

		uint8_t stepSliderValue = 0;
		uint8_t tickSliderValue = 0;
		uint8_t stepValue = 1;
		FrountPannel* FrountPannelRef = nullptr;

		CommonLabel stepLabel{ "Step" };
		CommonLabel tickLabel{ "Tick" };
		CommonImageButton ctlHold{ "HOLD","btn-hold-default.png","btn-hold-active.png","btn-hold-default-hover.png" };
		CommonImageButton ctlStep{ "STEP","btn-step-default.png","btn-step-active.png","btn-step-default-hover.png" };
		CommonSlider stepSlider;
		CommonSlider tickSlider;
		CommonImageButton stepIncButton{ "STEPINC","textbox-slider-plus-btn-default.png","textbox-slider-plus-btn-default-hover.png","textbox-slider-plus-btn-default-hover.png" };
		CommonImageButton stepDecButton{ "STEPDEC","textbox-slider-minus-btn-default.png","textbox-slider-minus-btn-default-hover.png","textbox-slider-minus-btn-default-hover.png" };
		CommonImageButton tickIncButton{ "TICKINC","textbox-slider-plus-btn-default.png","textbox-slider-plus-btn-default-hover.png","textbox-slider-plus-btn-default-hover.png" };
		CommonImageButton tickDecButton{ "TICKDEC","textbox-slider-minus-btn-default.png","textbox-slider-minus-btn-default-hover.png","textbox-slider-minus-btn-default-hover.png" };
		mt::Ignite::track::patternLenInfo patternLenData;
		CommonLabel	lengthTitle{ "Length" };
		CommonImageButton closeBtn{ "Close","ico-close.png","ico-close.png" };
		CommonImageButton applyButton{ "Apply","btn-apply-267x44-default.png","btn-apply-267x44-default-hover.png","btn-apply-267x44-default-hover.png" };
		CommonImageButton cancelButton{ "Cancel","btn-cancel-267x44-default.png","btn-cancel-267x44-default-hover.png","btn-cancel-267x44-default-hover.png" };
		FlexBox stepRow{ FlexBox::Direction::row, FlexBox::Wrap::noWrap, FlexBox::AlignContent::stretch, FlexBox::AlignItems::stretch, FlexBox::JustifyContent::spaceBetween };
		FlexBox tickRow{ FlexBox::Direction::row, FlexBox::Wrap::noWrap, FlexBox::AlignContent::stretch, FlexBox::AlignItems::stretch, FlexBox::JustifyContent::spaceBetween };

		void resized() override;
		void paint(juce::Graphics& g) override;
		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void sliderValueChanged(juce::Slider* sliderThatWasMoved) override;
		void pannelSendKey(bool isFocuse, paramId_t param, uint32_t keyValue);
		void handleCommandMessage(int id) override;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PatternBarLengthCtl)
	};
}