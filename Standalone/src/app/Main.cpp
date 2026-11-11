// SPDX-License-Identifier: AGPL-3.0-or-later
#include "MainComponent.h"
class IgniteStandaloneApp final : public juce::JUCEApplication {
public:
    const juce::String getApplicationName() override {return "IGNITE Standalone";}
    const juce::String getApplicationVersion() override {return "0.1.0";}
    void initialise(const juce::String& command) override {window=std::make_unique<Window>(command.contains("--ui-self-test"));}
    void shutdown() override {window.reset();}
    void systemRequestedQuit() override {quit();}
private:
    class Window final : public juce::DocumentWindow {
    public:
        explicit Window(bool test):DocumentWindow("IGNITE Standalone 0.1",juce::Colour(0xff0c1725),DocumentWindow::allButtons) {
            setUsingNativeTitleBar(true);setContentOwned(new MainComponent(test),true);setResizable(true,false);setResizeLimits(900,540,1800,1100);
            auto area=juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()->userArea;
            centreWithSize(juce::jmin(1060,area.getWidth()-24),juce::jmin(650,area.getHeight()-24));setVisible(true);toFront(true);
        }
        void closeButtonPressed() override {juce::JUCEApplication::getInstance()->systemRequestedQuit();}
    };
    std::unique_ptr<Window> window;
};
START_JUCE_APPLICATION(IgniteStandaloneApp)
