#include "../inc/mt_ignite_grid_erase_tool.h"
#include "../inc/mt_ignite_keyboard_component.h"
namespace ui
{
	GridEraseTool::GridEraseTool(NoteManagement& noteManagement, GridData& gData)
		: noteMgmt(noteManagement)
		, gridData(gData)
	{
		setType(GridToolType::GridEraseTool);
	}

	void GridEraseTool::clearSelectRegion()
	{
		startX = endX = startY = endY = 0;
	}

	bool GridEraseTool::isSelectRegionValid()
	{
		bool isValid = false;
		if (startX >= 0 && startY >= 0 && endX > 0 && endY > 0) isValid = true;
		return isValid;
	}

	void GridEraseTool::paint(Graphics& g)
	{
		//draw selection region
		if (isSelectRegionValid())
		{
			Rectangle<float> selRect(startX, startY, (endX - startX), (endY - startY));
			g.drawRect(selRect);
		}
	}

	void GridEraseTool::mouseDrag(const MouseEvent& event)
	{
		if (!isActive())
			return;

		float x1 = juce::jmax<float>(0.0, event.mouseDownPosition.getX());
		float x2 = juce::jmax<float>(0.0, event.position.getX());

		if (x1 != x2)
		{
			startX = juce::jmin<float>(x1, x2);
			endX = juce::jmax<float>(x1, x2);

			float y1 = juce::jmax<float>(0.0, event.mouseDownPosition.getY());
			float y2 = juce::jmax<float>(0.0, event.position.getY());
			startY = juce::jmin<float>(y1, y2);
			endY = juce::jmax<float>(y1, y2);
		}
	}

	void GridEraseTool::mouseDown(const MouseEvent& event)
	{
	}

	void GridEraseTool::mouseUp(const MouseEvent& event)
	{
		if (!isActive()) return;

		auto patternPtr = IgnitePattern::getAppPatternInstance();

		float x1 = juce::jmax<float>(0.0, event.mouseDownPosition.getX());
		float x2 = juce::jmax<float>(0.0, event.position.getX());
		auto step1 = gridData.findColumn(x1);
		auto step2 = gridData.findColumn(x2);
		int stepMin = juce::jmin<int>(step1, step2);
		int stepMax = juce::jmax<int>(step1, step2);

		float y1 = juce::jmax<float>(0.0, event.mouseDownPosition.getY());
		float y2 = juce::jmax<float>(0.0, event.position.getY());
		int note1 = gridData.findRow(y1);
		int note2 = gridData.findRow(y2);
		int noteMin = juce::jmin<int>(note1, note2);
		int noteMax = juce::jmax<int>(note1, note2);

		patternPtr->delNotes(stepMin, stepMax, noteMin, noteMax);
		if (isSelectRegionValid())
		{
			clearSelectRegion();
		}
	}
}//namespace mt

