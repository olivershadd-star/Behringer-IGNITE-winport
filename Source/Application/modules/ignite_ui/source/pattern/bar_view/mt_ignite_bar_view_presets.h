/*
* Copyright (C) Musictribe Innovation India Pvt. Ltd
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
	class StepPresets;
	class StepSequencer;

	enum class StepPresetType
	{
		Ramp,
		Pulse,
		Triangle
	};

	class IStepPreset : public juce::Component
	{
	public:
		enum PresetValueType
		{
			Single,
			Double,
			Quadruple,
			ReverseSingle,
			ReverseDouble,
			ReverseQuadruple,
		};

		IStepPreset();
		virtual ~IStepPreset();

		virtual StepPresetType getType() = 0;
		void nextPresetValueType();
		virtual void calculateValues() = 0;
		void setParent(StepPresets* prnt) { parent = prnt; }
		void setActive(bool activated) { active = activated; }

	private:
		void calculateCount();

	protected:
		bool active = false;
		PresetValueType type = PresetValueType::Single;
		StepPresets* parent = nullptr;
		int presetCount = 0;
		StepSequencer* stepControl = nullptr;
	};

	class StepRampPresets : public IStepPreset
	{
	public:
		virtual StepPresetType getType() { return StepPresetType::Ramp; }
		void getAssets();

	private:
		bool isMouseOver = false;
		Image presetEmpdefaultImage, presetEmpDefaultHoverImage, presetEmpActiveImage, presetEmpActiveHoverImage;

		virtual void calculateValues();
		void paint(juce::Graphics& g) override;
		virtual void mouseUp(const MouseEvent& event) override;
		void mouseMove(const MouseEvent& event) override;
		void mouseExit(const MouseEvent& event) override;
	};

	class StepPulsePresets : public IStepPreset
	{
	public:
		virtual StepPresetType getType() override { return StepPresetType::Pulse; }
		void getAssets();

	private:
		bool isMouseOver = false;
		Image presetEmpdefaultImage, presetEmpDefaultHoverImage, presetEmpActiveImage, presetEmpActiveHoverImage;

		void paint(juce::Graphics& g) override;
		virtual void mouseUp(const MouseEvent& event) override;
		virtual void calculateValues() override;
		void mouseMove(const MouseEvent& event) override;
		void mouseExit(const MouseEvent& event) override;
	};

	class StepTrianglePresets : public IStepPreset
	{
	public:
		virtual StepPresetType getType() override { return StepPresetType::Triangle; }
		void getAssets();

	private:
		bool isMouseOver = false;
		Image presetEmpdefaultImage, presetEmpDefaultHoverImage, presetEmpActiveImage, presetEmpActiveHoverImage;

		void paint(juce::Graphics& g) override;
		virtual void mouseUp(const MouseEvent& event) override;
		virtual void calculateValues() override;
		void mouseMove(const MouseEvent& event) override;
		void mouseExit(const MouseEvent& event) override;
	};

	class StepPresets : public juce::Component,
		public CommonButton::Listener,
		public CommonSlider::Listener,
		private Timer
	{
	public:
		CommonSlider levelSlider{ Slider::LinearVertical, Slider::NoTextBox };

		CommonButton inverseLevels{ TRANS("") };
		CommonButton flipLevels{ TRANS("") };

		StepRampPresets* _pRampPreset = nullptr;
		StepPulsePresets* _pPulsePreset = nullptr;
		StepTrianglePresets* _pTriangle = nullptr;

		StepPresets();
		~StepPresets();

		void enablePresets(bool enable);
		void setActivePreset(StepPresetType type);
		void setQl(int ql);
		int getQl() { return quantizationLevel; }
		std::vector<int>& getPresetValues() { return presetValues; }
		void setStepValue(int index, int value);
		void setSliderRange(float min, float max) { levelSlider.setRange(min, max); }
		void setStepValues(paramId_t param);
		void getAssets();

	SIGNALS:
		//values and flip
		sig::Signal<std::vector<int>&, int16_t, bool, bool, bool> valuesChanged;

	private:
		StepSequencerControl stepControl;
		std::vector<int> presetValues;
		std::list<IStepPreset*> presets;
		int quantizationLevel = 4;
		int16_t slider_prev_value = 0;
		int16_t offset = 0;
		int rMoveLeftCount = 0;
		int rMoveRightCount = 0;
		int timerStarted = false;

		Image presetEmpdefaultImage, presetEmpDefaultHoverImage, presetEmpActiveImage, presetEmpActiveHoverImage;

		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		virtual void paint(juce::Graphics& g) override;
		virtual void resized() override;
		void sliderValueChanged(juce::Slider* slider) override;
		void sliderDragEnded(juce::Slider*) override;
		void timerCallback() override;
	};
}
