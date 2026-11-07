
namespace ui
{
CommonMultiSelectTabBarButton::CommonMultiSelectTabBarButton(int numSel, juce::TabbedButtonBar& ownerBar, const juce::String& buttonName)
    :TabBarButton(buttonName, ownerBar)
    , noOfSelections(numSel)
{
}

int CommonMultiSelectTabBarButton::getNumOfSelection()
{
    return noOfSelections;
}
int CommonMultiSelectTabBarButton::getSelectionSpacing()
{
    return 5;
}
int CommonMultiSelectTabBarButton::getSelectionSize()
{
    return 20;
}
int CommonMultiSelectTabBarButton::getCurrentSelection()
{
    return currentSelection;
}
void CommonMultiSelectTabBarButton::incrementSelection()
{
    currentSelection++;
    if (currentSelection >= noOfSelections)
        currentSelection = 0;
}
void CommonMultiSelectTabBarButton::clearSelection()
{
    currentSelection = -1;
}
}
