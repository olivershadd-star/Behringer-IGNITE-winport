#include "../inc/mt_ignite_grid_pencil_tool.h"
namespace ui
{

	GridPencilTool::GridPencilTool(NoteManagement& noteManagement, GridData& gData)
		: noteMgmt(noteManagement)
		, gridData(gData)
	{
		setType(GridToolType::GridPencilTool);
	}

	void GridPencilTool::clearSelectRegion()
	{
		startX = endX = startY = endY = 0;
	}

	bool GridPencilTool::isSelectRegionValid()
	{
		bool isValid = false;
		if (startX >= 0 && startY >= 0 && endX > 0 && endY > 0) isValid = true;
		return isValid;
	}

	void GridPencilTool::paint(Graphics& g)
	{
		if (isSelectRegionValid())
		{
			Rectangle<float> selRect(startX, startY, (endX - startX), (endY - startY));
			g.drawRect(selRect);
		}
	}

	void GridPencilTool::mouseDown(const MouseEvent& event)
	{
	}

	void GridPencilTool::mouseDrag(const MouseEvent& event)
	{
		if (!isActive() || IgnitePattern::getAppPatternInstance()->getGangMode())
			return;

		float x1 = juce::jmax(0.0f, event.mouseDownPosition.getX());
		float x2 = juce::jmax(0.0f, event.position.getX());

		if (x1 != x2)
		{
			startX = juce::jmin(x1, x2);
			endX = juce::jmax(x1, x2);

			float y1 = juce::jmax(0.0f, event.mouseDownPosition.getY());
			float y2 = juce::jmax(0.0f, event.position.getY());

			startY = juce::jmin(y1, y2);
			endY = juce::jmax(y1, y2);
		}
	}


	void GridPencilTool::mouseUp(const MouseEvent& event)
	{
		auto _pPatternPtr = IgnitePattern::getAppPatternInstance();
		if (!isActive() || _pPatternPtr->getGangMode())
			return;

		std::unordered_map<uint8_t, ClientPatternNodeData> newNodeList;

		float x1 = juce::jmax(0.0f, event.mouseDownPosition.getX());
		float x2 = juce::jmax(0.0f, event.position.getX());
		int stepMin = juce::jmin(gridData.findColumn(x1), gridData.findColumn(x2));
		int stepMax = juce::jmax(gridData.findColumn(x1), gridData.findColumn(x2));

		float y1 = juce::jmax(0.0f, event.mouseDownPosition.getY());
		float y2 = juce::jmax(0.0f, event.position.getY());
		int noteMin = juce::jmin(gridData.findRow(y1), gridData.findRow(y2));
		int noteMax = juce::jmax(gridData.findRow(y1), gridData.findRow(y2));

		_pPatternPtr->addNotes(stepMin, stepMax, noteMin, noteMax);
		_pPatternPtr->setPatternEditIndication(true);

		if (isSelectRegionValid())
		{
			clearSelectRegion();
		}
	}

	void GridPencilTool::mouseDoubleClick(const MouseEvent& event)
	{
		if (!isActive()) return;

		auto _pPatternPtr = IgnitePattern::getAppPatternInstance();

		selectedNote = gridData.findRow(event.position.getY());
		selectedStep = gridData.findColumn(event.position.getX());

		if (_pPatternPtr->isNotePresent(selectedStep, selectedNote))
			_pPatternPtr->delNote(-1, selectedStep, selectedNote);
	}

}//namespace ui

