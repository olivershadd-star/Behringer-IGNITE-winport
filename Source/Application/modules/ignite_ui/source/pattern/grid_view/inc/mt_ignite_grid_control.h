/*
 * Copyright (c) - 2021 - MUSIC Tribe, MY
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

class AppGridControl : public juce::Component,
	public juce::Button::Listener
{
public:
#define GRID_OPTIONS_VIEW 8
	enum gridOptionsViewItemID
	{
		GRID_NO_FOCUS = 0,
		GRID_GANG_EDIT,
		GRID_PENCIL,
		GRID_ERASE,
		GRID_SELECT,
		GRID_CUT,
		GRID_COPY,
		GRID_UNDO,
		GRID_FOCUS_MAX = GRID_UNDO
	};
	AppGridControl();
	~AppGridControl() override;

	bool isPencilSelected(void) { return (boPencilSelected); }
	bool isEraserSelected(void) { return (boEraseSelected); }
	bool isCutIconSelected(void) { return (boCutIconSelected); };
	bool isCopyIconSelected(void) { return (boCopyIconSelected); };
	bool isGangSelected(void) { return gangBtn.getToggleState(); }

	void setGangMode(bool state);
	void setUndoButtonState(bool state) { optionUndo.setEnabled(state); }
	void setSculptButtonState(bool state) { sculptBtn.setEnabled(state); }
	void setSculptState(bool state) { sculptBtn.setToggleState(state, dontSendNotification); }
	void setCopyBtnState(bool state) { imageButtonCopy.setToggleState(state, dontSendNotification); }
	void setCutBtnState(bool state) {
		imageButtonCut.setToggleState(state, dontSendNotification); toolSelectionChanged.emit(GridToolType::GridSelectTool);
	}
	void setPensePencilSelected(bool state) {
		imageButtonPencil.setToggleState(state, sendNotification);
	}
	void setSelectTool(bool state)
	{
		selectBtn.setToggleState(state, sendNotification);
	}
	void refreshGridctrl();
	bool pannelKeyOptionsHandler(paramId_t param, uint32_t keyValue);
	void pannelSendKey(bool isFocuse, paramId_t param, uint32_t keyValue);


SIGNALS:
	sig::Signal<GridToolType> toolSelectionChanged;
	int gridKeyFocusedItem = gridOptionsViewItemID::GRID_NO_FOCUS;
	uint8_t gridOptionsView[GRID_OPTIONS_VIEW] = { GRID_NO_FOCUS, GRID_GANG_EDIT, GRID_PENCIL, GRID_ERASE, GRID_SELECT, GRID_CUT, GRID_COPY, GRID_UNDO };
	
	CommonImageButton imageButtonPencil{ "PENCIL","btn-pen-default.png","btn-pen-active.png","btn-pen-default-hover.png" };
	CommonImageButton imageButtonErase{ "ERASE","btn-erase-default.png","btn-erase-active.png","btn-erase-default-hover.png" };
	CommonImageButton selectBtn{ "SELECT","btn-select-default.png","btn-select-active.png","btn-select-default-hover.png" };
	CommonImageButton imageButtonCut{ "CUT","btn-cut-default.png","btn-cut-active.png","btn-cut-default-hover.png" };
	CommonImageButton imageButtonCopy{ "COPY","btn-copy-default.png","btn-copy-active.png","btn-copy-default-hover.png" };
	CommonImageButton gangBtn{ "GANG","btn-gangedit-120x44-default.png","btn-gangedit-120x44-active.png","btn-gangedit-120x44-default-hover.png" };

	CommonImageButton optionCopy{ "COPY" ,"btn-copy-default.png","btn-cut-default-hover","btn-cut-default-hover" };
	CommonImageButton optionUndo{ "UNDO","btn-undo-default.png","btn-undo-active.png","btn-undo-active.png" };
	CommonToggleButton sculptBtn{ "SCULPT" };
	FlexBox box;

	bool boPencilSelected{ false };
	bool boEraseSelected{ false };
	bool boCutIconSelected{ false };
	bool boCopyIconSelected{ false };
	bool boSelectionIconSelected{ false };
	bool boGangIconSelected{ false };

	void paint(juce::Graphics& g) override;
	void resized() override;
	void buttonClicked(juce::Button* buttonThatWasClicked) override;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AppGridControl)
};
