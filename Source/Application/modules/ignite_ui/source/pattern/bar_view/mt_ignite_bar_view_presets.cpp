#include "mt_ignite_bar_view_presets.h"
namespace ui
{
	constexpr int threshold_local(127);
#define SPACING 8
	StepPresets::StepPresets()
	{
		levelSlider.makeVisibleAndAddListner(this);
		levelSlider.setRange(-64, 64);
		levelSlider.setValue(0.0, dontSendNotification);
		levelSlider.setColour(Slider::ColourIds::trackColourId, Colour(0xFF34111A));
		levelSlider.setColour(Slider::ColourIds::textBoxOutlineColourId, Theme::Instance().getColour(transparentBlack));
		levelSlider.setColour(Slider::backgroundColourId, Theme::Instance().getColour(neutralBlack));
		levelSlider.setColour(Slider::trackColourId, Theme::Instance().getColour(neutralBlack));
		levelSlider.setLookAndFeel(BarSilderLnF::getLnf());
		levelSlider.setTitle("Level");

		_pRampPreset = new StepRampPresets();
		_pRampPreset->setParent(this);
		_pPulsePreset = new StepPulsePresets();
		_pPulsePreset->setParent(this);
		_pTriangle = new StepTrianglePresets();
		_pTriangle->setParent(this);

		presets.push_back(_pRampPreset);
		presets.push_back(_pPulsePreset);
		presets.push_back(_pTriangle);

		addAndMakeVisible(*_pRampPreset);
		addAndMakeVisible(*_pPulsePreset);
		addAndMakeVisible(*_pTriangle);
		inverseLevels.makeVisibleAndAddListner(this);
		inverseLevels.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		flipLevels.makeVisibleAndAddListner(this);
		flipLevels.setLookAndFeel(EmptyBackgroundLooknFeel::getLnf());
		enablePresets(false);
		getAssets();
		_pRampPreset->getAssets();
		_pPulsePreset->getAssets();
		_pTriangle->getAssets();
		this->setBufferedToImage(true);
		_pPulsePreset->setBufferedToImage(true);
		_pRampPreset->setBufferedToImage(true);
		_pTriangle->setBufferedToImage(true);
	}

	void StepPresets::enablePresets(bool enable)
	{
		for (auto it : presets)
		{
			it->setVisible(enable);
		}
		inverseLevels.setVisible(enable);
		flipLevels.setVisible(enable);
		levelSlider.setVisible(!enable);
	}

	StepPresets::~StepPresets()
	{
		for (auto it : presets)
		{
			delete it;
		}
	}

	void StepPresets::getAssets()
	{
		presetEmpdefaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-preset-inv-default.png"));
		presetEmpDefaultHoverImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-preset-inv-default-hover.png"));
		presetEmpActiveImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-preset-flip-default.png"));
		presetEmpActiveHoverImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-preset-flip-default-hover.png"));
	}

	void StepPresets::paint(juce::Graphics& g)
	{
		Image DrawImage;

		if (inverseLevels.isVisible())
		{
			DrawImage = (inverseLevels.isMouseOver() || inverseLevels.isFocused ? presetEmpDefaultHoverImage : presetEmpdefaultImage);
			g.drawImage(DrawImage, ui::Rectangle<float>{0, 138, 39, 40 }, RectanglePlacement::centred);
		}

		if (flipLevels.isVisible())
		{
			DrawImage = (flipLevels.isMouseOver() || flipLevels.isFocused ? presetEmpActiveHoverImage : presetEmpActiveImage);
			g.drawImage(DrawImage, ui::Rectangle<float>{0, 188, 39, 40 }, RectanglePlacement::centred);
		}
	}

	void StepPresets::resized()
	{
		int prevBottom = 0;
		for (auto it : presets)
		{
			it->setBounds(0, prevBottom, 37, 36);
			prevBottom = it->getBottom() + 10;
		}
		inverseLevels.setBounds(0, prevBottom, 39, 40);
		levelSlider.setBounds(0, 0, 39, 312);
		flipLevels.setBounds(0, prevBottom + 40 + 10, 39, 40);
	}

	void StepPresets::setActivePreset(StepPresetType type)
	{
		for (auto preset : presets)
		{
			if (preset->getType() != type)
				preset->setActive(false);
		}
		repaint();
	}

	void StepPresets::setQl(int ql)
	{
		quantizationLevel = ql;
		presetValues.resize(ql);
		std::fill(presetValues.begin(), presetValues.end(), 0);
	}

	void StepPresets::sliderDragEnded(juce::Slider* slider)
	{
		if (slider == &levelSlider)
		{
			offset = (int8_t)slider->getValue() - slider_prev_value;
			slider_prev_value = (int8_t)slider->getValue();
			valuesChanged.emit(presetValues, offset, false, false, false);
		}
		slider_prev_value = offset = 0;
		levelSlider.setValue(0.0, dontSendNotification);
	}

	void StepPresets::sliderValueChanged(juce::Slider* slider)
	{
		if (slider == &levelSlider)
		{
			offset = (int8_t)slider->getValue() - slider_prev_value;
			slider_prev_value = (int8_t)slider->getValue();
			valuesChanged.emit(presetValues, offset, false, true, true);
		}
	}

	void StepPresets::buttonClicked(juce::Button* buttonThatWasClicked)
	{
		auto param_max_value = IgnitePattern::getAppPatternInstance()->getThreshold();
		if (buttonThatWasClicked == &inverseLevels)
		{
			for (int i = 0; i < presetValues.size(); i++)
			{
				presetValues[i] = param_max_value - presetValues[i]; // (presetValues[i] * param_max_value) / 127;
				if (presetValues[i] > param_max_value)
					presetValues[i] = param_max_value;
			}
			valuesChanged.emit(presetValues, 0, false, false, false);
		}
		else if (buttonThatWasClicked == &flipLevels)
		{
			for (int i = 0; i < presetValues.size(); i++)
			{
				if (presetValues[i] == 0)
				{
					presetValues[i] = param_max_value;
				}
				else
				{
					presetValues[i] = 0;
				}
			}
			valuesChanged.emit(presetValues, 0, true, false, false);
		}
	}

	void StepPresets::setStepValue(int index, int value)
	{
		if (index >= quantizationLevel)
			return;

		presetValues[index] = value;
	}

	void StepPresets::timerCallback()
	{
		offset = (int8_t)levelSlider.getValue() - slider_prev_value;
		slider_prev_value = (int8_t)levelSlider.getValue();
		valuesChanged.emit(presetValues, offset, false, false, false);
		slider_prev_value = offset = 0;
		levelSlider.setValue(0.0, dontSendNotification);
		rMoveLeftCount = 0;
		rMoveRightCount = 0;
		timerStarted = false;
		stopTimer();
	}

	void StepPresets::setStepValues(paramId_t param)
	{
		if (param == (paramId_t)FrontPannelParam::paramKey_RMOVELEFT)
		{
			levelSlider.setValue(levelSlider.getValue() + 1, sendNotification);
			rMoveLeftCount = rMoveLeftCount + 1;
			if (rMoveLeftCount > 0)
			{
				if (timerStarted)
				{
					stopTimer();
					startTimer(TIMER_TIMEOUT_SLIDER_RESET_MILLISECOND);
				}
				else
				{
					startTimer(TIMER_TIMEOUT_SLIDER_RESET_MILLISECOND);
					timerStarted = true;
				}
			}
		}
		else
		{
			levelSlider.setValue(levelSlider.getValue() - 1, sendNotification);
			rMoveRightCount = rMoveRightCount + 1;
			if (rMoveRightCount > 0)
			{
				if (timerStarted)
				{
					stopTimer();
					startTimer(TIMER_TIMEOUT_SLIDER_RESET_MILLISECOND);
				}
				else
				{
					startTimer(TIMER_TIMEOUT_SLIDER_RESET_MILLISECOND);
					timerStarted = true;
				}
			}
		}
	}

	void StepRampPresets::getAssets()
	{
		presetEmpdefaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-preset-empty-default.png"));
		presetEmpDefaultHoverImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-preset-empty-default-hover.png"));
		presetEmpActiveImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-preset-empty-active.png"));
		presetEmpActiveHoverImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-preset-empty-active-hover.png"));
	}

	void StepRampPresets::paint(juce::Graphics& g)
	{
		Image dropImage;
		stepControl = StepSequencer::getStepSequencerInstance();
		if (!active)
		{
			dropImage = (isMouseOver || (stepControl->barPresetKeyFocusedItem == stepControl->barPresetViewItemID::BAR_PRESET_RAMP)) ? presetEmpDefaultHoverImage : presetEmpdefaultImage;
			g.drawImage(dropImage, ui::Rectangle<float>{0, 0, (float)getWidth(), (float)getHeight() }, RectanglePlacement::centred);
			g.setColour(Theme::Instance().getColour(customOrange));
		}
		else
		{
			dropImage = (isMouseOver || (stepControl->barPresetKeyFocusedItem == stepControl->barPresetViewItemID::BAR_PRESET_RAMP)) ? presetEmpActiveHoverImage : presetEmpActiveImage;
			g.drawImage(dropImage, ui::Rectangle<float>{0, 0, (float)getWidth(), (float)getHeight() }, RectanglePlacement::centred);
			g.setColour(juce::Colours::white);
		}
		float vWidth = static_cast<float>(getWidth());
		float vHeight = static_cast<float>(getHeight());

		float sawDistance = (vWidth - (2 * SPACING)) * (1.0f / presetCount);
		Path myPath;
		if (type == Single || type == Double || type == Quadruple)
		{
			myPath.startNewSubPath(SPACING, vHeight - SPACING);
			for (int i = 1; i <= presetCount; i++)
			{
				myPath.lineTo(SPACING + i * sawDistance, SPACING);
				myPath.lineTo(SPACING + i * sawDistance, vHeight - SPACING);
			}
		}
		else if (type == ReverseSingle || type == ReverseDouble || type == ReverseQuadruple)
		{
			myPath.startNewSubPath(vWidth - SPACING, vHeight - SPACING);
			for (int i = presetCount - 1; i >= 0; i--)
			{
				myPath.lineTo(i * sawDistance + SPACING, SPACING);
				myPath.lineTo(i * sawDistance + SPACING, vHeight - SPACING);
			}
		}

		g.strokePath(myPath, PathStrokeType(2.0f));
	}

	void StepRampPresets::mouseMove(const MouseEvent& event)
	{
		isMouseOver = true;
		repaint();
	}

	void StepRampPresets::mouseExit(const MouseEvent& event)
	{
		isMouseOver = false;
		repaint();
	}

	void StepRampPresets::mouseUp(const MouseEvent& event)
	{
		nextPresetValueType();
		repaint();
	}

	void StepRampPresets::calculateValues()
	{
		int ql = 16;// parent->getQl();
		auto param_max_value = IgnitePattern::getAppPatternInstance()->getThreshold();
		std::vector<int>& presetValues = parent->getPresetValues();
		presetValues.clear();
		presetValues.resize(ql);
		float imgX = 160;
		float xMax = imgX / presetCount;
		int nl = ql / presetCount;
		float dx = xMax / nl;
		float m = param_max_value / xMax;
		float x = dx;

		std::list<int> valuesTmp;
		for (int i = 0; i < nl; i++)
		{
			int paramV = static_cast<int>(std::ceil(m * x));
			if (type == Single || type == Double || type == Quadruple)
			{
				valuesTmp.push_back(paramV);
			}
			else
			{
				valuesTmp.push_front(paramV);
			}
			x += dx;
		}

		for (int i = 0; i < ql;)
		{
			for (int val : valuesTmp)
			{
				if (presetValues[i] > param_max_value)
					presetValues[i] = param_max_value;
				else
					presetValues[i] = val;
				i++;
			}
		}

		parent->valuesChanged.emit(presetValues, 0, false, false, false);
	}

	void StepPulsePresets::getAssets()
	{
		presetEmpdefaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-preset-empty-default.png"));
		presetEmpDefaultHoverImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-preset-empty-default-hover.png"));
		presetEmpActiveImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-preset-empty-active.png"));
		presetEmpActiveHoverImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-preset-empty-active-hover.png"));
	}

	void StepPulsePresets::paint(juce::Graphics& g)
	{
		Image dropImage;
		stepControl = StepSequencer::getStepSequencerInstance();
		if (!active)
		{
			dropImage = (isMouseOver || (stepControl->barPresetKeyFocusedItem == stepControl->barPresetViewItemID::BAR_PRESET_PULSE)) ? presetEmpDefaultHoverImage : presetEmpdefaultImage;
			g.drawImage(dropImage, ui::Rectangle<float>{0, 0, (float)getWidth(), (float)getHeight() }, RectanglePlacement::centred);
			g.setColour(Theme::Instance().getColour(customOrange));
		}
		else
		{
			dropImage = (stepControl->barPresetKeyFocusedItem == stepControl->barPresetViewItemID::BAR_PRESET_PULSE) ? presetEmpActiveHoverImage : presetEmpActiveImage;
			g.drawImage(dropImage, ui::Rectangle<float>{0, 0, (float)getWidth(), (float)getHeight() }, RectanglePlacement::centred);
			g.setColour(juce::Colours::white);
		}

		float vWidth = static_cast<float>(getWidth());
		float vHeight = static_cast<float>(getHeight());

		float sawDistance = (vWidth - (2 * SPACING)) * (1.0f / presetCount);
		Path myPath;
		if (type == Single || type == Double || type == Quadruple)
		{
			myPath.startNewSubPath(SPACING, vHeight - SPACING);
			float xstart = SPACING;
			for (int i = 1; i <= presetCount; i++)
			{
				myPath.lineTo(xstart, SPACING);
				myPath.lineTo(xstart + (sawDistance / 2), SPACING);
				myPath.lineTo(xstart + (sawDistance / 2), vHeight - SPACING);
				myPath.lineTo(xstart + (sawDistance), vHeight - SPACING);
				xstart += sawDistance;
			}
		}
		else if (type == ReverseSingle || type == ReverseDouble || type == ReverseQuadruple)
		{
			myPath.startNewSubPath(SPACING, vHeight - SPACING);
			float xstart = SPACING;
			for (int i = 1; i <= presetCount; i++)
			{
				myPath.lineTo(xstart + (sawDistance / 2), vHeight - SPACING);
				myPath.lineTo(xstart + (sawDistance / 2), SPACING);
				myPath.lineTo(xstart + sawDistance, SPACING);
				myPath.lineTo(xstart + (sawDistance), vHeight - SPACING);
				xstart += sawDistance;
			}
		}
		g.strokePath(myPath, PathStrokeType(2.0f));
	}

	void StepPulsePresets::mouseMove(const MouseEvent& event)
	{
		isMouseOver = true;
		repaint();
	}

	void StepPulsePresets::mouseExit(const MouseEvent& event)
	{
		isMouseOver = false;
		repaint();
	}

	void StepPulsePresets::mouseUp(const MouseEvent& event)
	{
		nextPresetValueType();
		repaint();
	}

	void StepPulsePresets::calculateValues()
	{
		int ql = 16;// parent->getQl();
		auto param_max_value = IgnitePattern::getAppPatternInstance()->getThreshold();
		std::vector<int>& presetValues = parent->getPresetValues();
		presetValues.clear();
		presetValues.resize(ql);

		int nl = ql / presetCount;
		std::list<int> valuesTmp;
		for (int i = 0; i < nl; i++)
		{
			int paramV = param_max_value;
			if (i >= (nl / 2))
				paramV = 0;

			if (type == Single || type == Double || type == Quadruple)
			{
				valuesTmp.push_back(paramV);
			}
			else
			{
				valuesTmp.push_front(paramV);
			}
		}

		for (int i = 0; i < ql;)
		{
			for (int val : valuesTmp)
			{
				if (presetValues[i] > param_max_value)
					presetValues[i] = param_max_value;
				else
					presetValues[i] = val;
				i++;
			}
		}

		parent->valuesChanged.emit(presetValues, 0, false, false, false);
	}

	IStepPreset::IStepPreset()
	{
		calculateCount();
	}

	IStepPreset::~IStepPreset()
	{}

	void IStepPreset::nextPresetValueType()
	{
		if (active)
		{
			int typeI = static_cast<int>(type);
			typeI++;
			if (typeI > 5)
				typeI = 0;

			type = static_cast<PresetValueType>(typeI);
		}
		if (!active)
		{
			active = true;
			parent->setActivePreset(getType());
		}
		calculateCount();
		calculateValues();
	}

	void IStepPreset::calculateCount()
	{
		if (type == Single || type == ReverseSingle)
		{
			presetCount = 1;
		}
		else if (type == Double || type == ReverseDouble)
		{
			presetCount = 2;
		}
		else if (type == Quadruple || type == ReverseQuadruple)
		{
			presetCount = 4;
		}
	}

	void StepTrianglePresets::getAssets()
	{
		presetEmpdefaultImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-preset-empty-default.png"));
		presetEmpDefaultHoverImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-preset-empty-default-hover.png"));
		presetEmpActiveImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-preset-empty-active.png"));
		presetEmpActiveHoverImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("btn-preset-empty-active-hover.png"));
	}

	void StepTrianglePresets::paint(juce::Graphics& g)
	{
		Image dropImage;
		stepControl = StepSequencer::getStepSequencerInstance();
		if (!active)
		{
			dropImage = (isMouseOver || (stepControl->barPresetKeyFocusedItem == stepControl->barPresetViewItemID::BAR_PRESET_TRIANGLE)) ? presetEmpDefaultHoverImage : presetEmpdefaultImage;
			g.drawImage(dropImage, ui::Rectangle<float>{0, 0, (float)getWidth(), (float)getHeight() }, RectanglePlacement::centred);
			g.setColour(Theme::Instance().getColour(customOrange));
		}
		else
		{
			dropImage = (isMouseOver || (stepControl->barPresetKeyFocusedItem == stepControl->barPresetViewItemID::BAR_PRESET_TRIANGLE)) ? presetEmpActiveHoverImage : presetEmpActiveImage;
			g.drawImage(dropImage, ui::Rectangle<float>{0, 0, (float)getWidth(), (float)getHeight() }, RectanglePlacement::centred);
			g.setColour(juce::Colours::white);
		}
		float vWidth = static_cast<float>(getWidth());
		float vHeight = static_cast<float>(getHeight());

		float sawDistance = (vWidth - (2 * SPACING)) * (1.0f / presetCount);

		Path myPath;
		float xstart = SPACING;
		if (type == Single || type == Double || type == Quadruple)
		{
			myPath.startNewSubPath(SPACING, vHeight - SPACING);
			for (int i = 1; i <= presetCount; i++)
			{
				myPath.lineTo(xstart + (sawDistance / 2), SPACING);
				myPath.lineTo(xstart + sawDistance, vHeight - SPACING);
				xstart += sawDistance;
			}
		}
		else
		{
			myPath.startNewSubPath(SPACING, SPACING);
			for (int i = 1; i <= presetCount; i++)
			{
				myPath.lineTo(xstart + (sawDistance / 2), vHeight - SPACING);
				myPath.lineTo(xstart + sawDistance, SPACING);
				xstart += sawDistance;
			}
		}
		g.strokePath(myPath, PathStrokeType(2.0f));
	}

	void StepTrianglePresets::mouseMove(const MouseEvent& event)
	{
		isMouseOver = true;
		repaint();
	}

	void StepTrianglePresets::mouseExit(const MouseEvent& event)
	{
		isMouseOver = false;
		repaint();
	}

	void StepTrianglePresets::mouseUp(const MouseEvent& event)
	{
		nextPresetValueType();
		repaint();
	}

	void StepTrianglePresets::calculateValues()
	{
		int ql = 16;// parent->getQl();
		auto param_max_value = IgnitePattern::getAppPatternInstance()->getThreshold();
		std::vector<int>& presetValues = parent->getPresetValues();
		presetValues.clear();
		presetValues.resize(ql);

		float imgX = 160;
		float xMax = imgX / presetCount;
		int nl = ql / presetCount;
		float dx = xMax / nl;
		float m1, m2 = 0;
		float x = 0;
		int c1, c2 = 0;
		if (type == Single || type == Double || type == Quadruple)
		{
			m1 = param_max_value / (xMax / 2);
			m2 = -m1;
			c1 = 0;
			c2 = 2 * param_max_value;
			x = dx;
		}
		else
		{
			m1 = -(param_max_value / (xMax / 2));
			m2 = -m1;
			c1 = param_max_value;
			c2 = -param_max_value;
		}
		std::list<int> valuesTmp;
		int paramV = param_max_value;
		for (int i = 0; i < nl; i++)
		{
			if (i < nl / 2)
			{
				paramV = static_cast<int>(std::ceil(c1 + (m1 * x)));
				x += dx;
			}
			else if (i == (nl / 2))
			{
				//last calculated value
				paramV = paramV;
				// special case for reverse triangle
				if (x != (xMax / 2) + dx)
					x = (xMax / 2) + (2 * dx);
			}
			else
			{
				paramV = static_cast<int>(std::ceil((m2 * x) + c2));
				x += dx;
			}

			valuesTmp.push_back(paramV);
		}

		for (int i = 0; i < ql;)
		{
			for (int val : valuesTmp)
			{
				if (presetValues[i] > param_max_value)
					presetValues[i] = param_max_value;
				else
					presetValues[i] = val;
				i++;
			}
		}

		parent->valuesChanged.emit(presetValues, 0, false, false, false);
	}
}
