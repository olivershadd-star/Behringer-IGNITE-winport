// SPDX-License-Identifier: AGPL-3.0-or-later
#include "MainComponent.h"
class IgniteStandaloneApp final : public juce::JUCEApplication {
public:
    const juce::String getApplicationName() override {return "IGNITE Standalone";}
    const juce::String getApplicationVersion() override {return "0.1.1";}
    void initialise(const juce::String& command) override {
        auto dir=juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory).getChildFile("IgniteStandalone");dir.createDirectory();
        logger=std::make_unique<juce::FileLogger>(dir.getChildFile("last-run.log"),"IGNITE Standalone 0.1.1",64*1024);juce::Logger::setCurrentLogger(logger.get());
        window=std::make_unique<Window>(command.contains("--ui-self-test"),command.contains("--startup-check"));
    }
    void shutdown() override {window.reset();juce::Logger::setCurrentLogger(nullptr);logger.reset();}
    void systemRequestedQuit() override {quit();}
private:
    class Window final : public juce::DocumentWindow {
    public:
        explicit Window(bool test,bool startup):DocumentWindow("IGNITE Standalone 0.1.1",juce::Colour(0xff0c1725),DocumentWindow::allButtons) {
            setUsingNativeTitleBar(true);setContentOwned(new MainComponent(test,startup),true);setResizable(true,false);setResizeLimits(900,540,1800,1100);
            auto area=juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()->userArea;
            centreWithSize(juce::jmin(1060,area.getWidth()-24),juce::jmin(650,area.getHeight()-24));setVisible(true);toFront(true);
        }
        void closeButtonPressed() override {juce::JUCEApplication::getInstance()->systemRequestedQuit();}
    };
    std::unique_ptr<Window> window;
    std::unique_ptr<juce::FileLogger> logger;
};
START_JUCE_APPLICATION(IgniteStandaloneApp)
