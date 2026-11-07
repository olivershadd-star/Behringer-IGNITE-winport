#include "common_progressbar.h"
namespace ui
{
CommonProgressBar::CommonProgressBar(double & progress) :
    _progress(progress),
    ProgressBar(_progress)
{
    setColour(juce::ProgressBar::backgroundColourId, Theme::Instance().getColour(neutralGrey1));
    setColour(juce::ProgressBar::foregroundColourId, Theme::Instance().getColour(customBlue4));
}

CommonProgressBar::~CommonProgressBar()
{
}

void CommonProgressBar::updateProgress(double& newProgreess)
{
    _progress = newProgreess;
    //repaint();
}

void CommonProgressBar::close()
{
    juce::DialogWindow* dw = findParentComponentOfClass<juce::DialogWindow>();
    if (dw == nullptr)
        return;
    
    dw->exitModalState(1);
}

void CommonProgressBar::drawProgressBar(Graphics& g, ProgressBar& progressBar, int width, int height,
    double current_progress, const String& textToShow)
{
    auto background = progressBar.findColour(ProgressBar::backgroundColourId);
    auto foreground = progressBar.findColour(ProgressBar::foregroundColourId);

    auto barBounds = progressBar.getLocalBounds().toFloat();

    g.setColour(background);
    g.fillRoundedRectangle(barBounds, (float)progressBar.getHeight() * 0.5f);

    if (current_progress >= 0.0f && current_progress <= 1.0f)
    {
        Path p;
        p.addRoundedRectangle(barBounds, (float)progressBar.getHeight() * 0.5f);
        g.reduceClipRegion(p);

        barBounds.setWidth(barBounds.getWidth() * (float)current_progress);
        g.setColour(foreground);
        g.fillRoundedRectangle(barBounds, (float)progressBar.getHeight() * 0.5f);
    }
 }

bool CommonProgressBar::isProgressBarOpaque(ProgressBar&)
{
    return false;
}

}