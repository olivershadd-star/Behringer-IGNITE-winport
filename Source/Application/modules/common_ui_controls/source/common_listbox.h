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
	class CommonUtils;
	class FrountPannel;
	class CommonList : public juce::Component, public CommonButton::Listener
	{
	public:
		std::function<void(int Selection)> onSelectionChanged;
		std::function<void(int)> onApplyValueChanged;
		std::function<void(bool)> onDailogTrigger;

		explicit CommonList(const String& Title, int NumColumns = 1);
		explicit CommonList(const String& Title, const std::vector<juce::String>& Options, int Selected = 0, int NumColumns = 1, bool showRstBtn = false);

		~CommonList();

		void setContent(const std::vector<juce::String>& Data, int Selected = 0);
		inline int getSize() { return options.size(); }

		const String& getTitle();
		const int getColumns();
		const int getSelectedIndex();
		const String& getSelected();

		void setTitle(const String& Title);
		void setColumns(int Cols);
		void setSelected(int O);
		void clearSelected(int O);
		void setSelected(const String& O);
		void setBackgroundColour(Colour c);
		void setBackgroundColourForRange(int range, Colour c);
		void setTextColour(Colour c);
		void makeVisible(Component* Parent);
		const int getRequiredHeight();
		void show(const String& Title = "", std::function<void(int)> CallbackOnExit = nullptr);
		void setDailogViewType(mt::Ignite::DailogViewType type, bool ctrlOpt = false, Rectangle<int> Bounds = ui::layout::dialog)
		{
			viewType = type;
			bounds = Bounds;
			ctrOpt = ctrlOpt;
		}
		void changeListLnF(LookAndFeel*);
		void setTitleHeight(int value) { titleHeight = value; };
		bool IsEditing() {
			return(isDialogOpen.get() == true);
		};
		juce::Atomic<bool> isDialogOpen{ false };

		bool FPKeyHandler(bool isFocuse, paramId_t param, uint32_t KeyValue);
		void setShiftStatus(bool shiftStatus) {
			shiftKeyStatus = shiftStatus;
		};
		int currentFocus{ 0 };
	private:
		String title;
		bool shiftKeyStatus = false;
		bool showResetBtn = false;
		int noOfColumns{ 1 };
		int selection{ -1 };
		int preSelection{ -1 };
		int titleHeight{ heightDailogTitle };
		volatile int reqHeight{ 0 };
		Array<CommonToggleButton*> options;
		bool ctrOpt{ false };
		CommonLabel listTitle{ "" };
		Rectangle<int> bounds{ ui::layout::dialog };
		std::unique_ptr<Viewport> view;
		CommonImageButton closeBtn{ "Close","ico-close.png","ico-close.png" };
		void paint(juce::Graphics& g) override;
		void resized() override;
		void deleteAndFree();
		mt::Ignite::DailogViewType viewType{ mt::Ignite::DailogViewType::DefaultView };
		void buttonClicked(juce::Button* button) override;
		void handleCommandMessage(int id);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CommonList);
	};

	class CommonListBox : public juce::Component, public CommonButton::Listener
	{
	public:
		
		enum class BoxType
		{
			withoutTitleBar,
			withTitleBar,
			withoutTitleBarWithNavigationButtons,
			withTitleBarWithNavigationButtons,
			withTitleBottom
		};
		enum ConnectedEdgeFlags
		{
			ConnectedOnLeft = 1,
			ConnectedOnRight = 2,
			ConnectedOnTop = 4,
			ConnectedOnBottom = 8,
			NoConnected = 16,
			NoLayout
		};
		std::function<void(const String&)> onValueChanged;
		std::function<void(int, const String&)> onApplyValueChanged;
		std::function<void(int, const String&)> onSelectionChanged;
		std::function<void(int, const String&, const String&)> onSelectionChangedWithName;
		std::function<void(bool)> onFocusChanged;
		std::function<void(bool)> onDailogTrigger;

		CommonListBox(const String& Title, int NumColumns = 1, bool showRstBtn = false);
		CommonListBox(const String& Title, const std::vector<juce::String>& Options, int Selected = 0, int NumColumns = 1, bool showRstBtn = false);
		CommonListBox(BoxType Type, const String& Title, const std::vector<juce::String>& Options, int Selected = 0, int NumColumns = 1, bool showRstBtn = false);

		void setDisplayFormat(BoxType Format);

		String getSelectedValue(void);
		const String& getSelected();
		int getSelectedIndex();

		void setSpecificString(const String& O);
		void setSelected(const String& O);
		void setSelected(int O);
		void clearSelected(int O);
		void setTitleText(const String& O);
		void setTitleColour(Colour c);
		void setValueColour(Colour c);
		void setValueFontSize(float newFontSize) { value.setTextFont(newFontSize); }
		void updateListOptions(const std::vector<juce::String>& Options, int selectedIndex = 0);
		void updateListOptionsWithSize(const std::vector<juce::String>& Options, int size, int selectedIndex = 0);
		inline int getSize() { return list.getSize(); }
		void makeVisible(Component* Parent);
		void showList();
		void setDailogViewType(mt::Ignite::DailogViewType boxType, bool ctrOpt = false, Rectangle<int> Bounds = ui::layout::dialog)
		{
			list.setDailogViewType(boxType, ctrOpt, Bounds);
		}
		void changeListLnF(LookAndFeel* newlnf) { list.changeListLnF(newlnf); }
		void setBackgroundColour(Colour backgroundColor) { list.setBackgroundColour(backgroundColor); }
		void setBackgroundColourForRange(int range, Colour backgroundColor) { list.setBackgroundColourForRange(range, backgroundColor); }
		void setTextColour(Colour textColor) { list.setTextColour(textColor); }
		void setLayoutType(int edgetype) { if (layoutType != edgetype) layoutType = edgetype; };
		bool IsEditing()
		{
			if ((list.IsEditing() == true) || (isDialogOpen.get() == true))
				return true;
			return false;
		};
		bool FPKeyHandler(bool isFocuse, paramId_t param, uint32_t KeyValue);
		void handleCommandMessage(int id);
		void setFocus(bool s);
		bool getFocusState() {
			return focusState;
		};
		void setEditable(bool s) {
			isEditable = s;
		};
		void setEditing(bool s) { isDialogOpen = s; list.isDialogOpen = s; }
		void setValueFont(Font a)
		{
			value.setTextFont(a);
		}
		void setJustification(Justification j)
		{
			value.setJustificationType(j);
			repaint();
		}
		void setcustombounds(bool state, Rectangle<int> a, Rectangle<int> b);
		void drawBorder(bool bDraw) { bShouldDraw = bDraw; };
		void setShiftStatus(bool shiftStatus) {
			list.setShiftStatus(shiftStatus);
		};
	private:
		BoxType type;
		CommonList list;
		CommonLabel title{ "" }, value{ "" };
		CommonButton plus{ ">" }, minus{ "<" };
		FlexBox c, box;
		int layoutType = { 0 };
		juce::Atomic<bool> isDialogOpen{ false };
		bool enableEdit{ 0 };
		void mouseDoubleClick(const juce::MouseEvent& e);
		void mouseDown(const MouseEvent&) override;
		void resized() override;
		void buttonClicked(juce::Button* button) override;
		void paint(juce::Graphics& g) override;
		void mouseMove(const MouseEvent& event) override;
		void mouseExit(const MouseEvent& event) override;
		
		bool focusState{ 0 };
		bool isEditable{ true };
		ui::Rectangle<int> valueBounds;
		ui::Rectangle<int> titleBounds;
		bool iscustombound{false};

		Image normalImage;
		Image overImage;
		bool bShouldDraw = false;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CommonListBox)
	};
};
