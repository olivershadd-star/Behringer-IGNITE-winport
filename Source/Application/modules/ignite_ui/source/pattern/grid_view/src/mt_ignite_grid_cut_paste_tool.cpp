#include "../inc/mt_ignite_grid_cut_paste_tool.h"

namespace ui
{
	GridCutPasteTool::GridCutPasteTool(NoteManagement& noteManagement, GridData& gData)
		: noteMgmt(noteManagement)
		, gridData(gData)
	{
		setType(GridToolType::GridCutPasteTool);
	}

	void GridCutPasteTool::paint(Graphics& g)
	{
	}

	void GridCutPasteTool::mouseDown(const MouseEvent& event)
	{
		auto patternPtr = IgnitePattern::getAppPatternInstance();
		auto gridViewPtr = AppGrid::getGridInstance();
		if (gridViewPtr->isSelectToolActive() && (patternPtr->selectedNotesInGrid.size() > 0))
		{
			float x2 = juce::jmax<float>(0.0, event.position.getX());
			float y2 = juce::jmax<float>(0.0, event.position.getY());
			int note1 = gridData.findRow(y2);
			auto step1 = gridData.findColumn(x2);
			patternPtr->notesCutPaste(step1, note1);
			gridViewPtr->setCutButtonState(false);
		}
	}
}//namespace ui

