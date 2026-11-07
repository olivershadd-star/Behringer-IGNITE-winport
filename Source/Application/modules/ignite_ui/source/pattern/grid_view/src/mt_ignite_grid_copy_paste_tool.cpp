#include "../inc/mt_ignite_grid_copy_paste_tool.h"

namespace ui
{
	GridCopyPasteTool::GridCopyPasteTool(NoteManagement& noteManagement, GridData& gData)
		: noteMgmt(noteManagement)
		, gridData(gData)
	{
		setType(GridToolType::GridCopyPasteTool);
	}

	void GridCopyPasteTool::paint(Graphics& g)
	{
	}

	void GridCopyPasteTool::mouseDown(const MouseEvent& event)
	{
		auto patternPtr = IgnitePattern::getAppPatternInstance();
		if (AppGrid::getGridInstance()->isSelectToolActive() && (patternPtr->selectedNotesInGrid.size() > 0))
		{
			float x2 = juce::jmax<float>(0.0, event.position.getX());
			float y2 = juce::jmax<float>(0.0, event.position.getY());
			int note1 = gridData.findRow(y2);
			auto step1 = gridData.findColumn(x2);
			patternPtr->pasteSelectedNotes(step1, note1);
		}
	}
}//namespace ui

