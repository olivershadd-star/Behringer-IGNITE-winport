#pragma once
namespace ui
{
class CommonMultiSelectTabBarButton : public juce::TabBarButton
{
public:
    CommonMultiSelectTabBarButton(int numSel, juce::TabbedButtonBar& ownerBar, const juce::String& buttonName = "");
    int getNumOfSelection();
    int getSelectionSpacing();
    int getSelectionSize();
    int getCurrentSelection();
    void incrementSelection();
    void clearSelection();

private:
    int noOfSelections = 0;
    int currentSelection = -1;
};
}
