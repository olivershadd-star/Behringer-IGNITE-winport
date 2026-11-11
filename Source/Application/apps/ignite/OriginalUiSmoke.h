// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
// Test-only automation of the existing JUCE buttons. No alternative interface.
class OriginalUiSmoke final : private juce::Timer {
public:
    static void start(Ignite::IgniteEngine& engine) { (new OriginalUiSmoke(engine))->startTimer(500); }
private:
    explicit OriginalUiSmoke(Ignite::IgniteEngine& engineIn) : engine(engineIn), initialCount(engineIn.instrumentManager->getInstrumentCount()) {}
    juce::Button* find(juce::Component& root, const juce::String& id) {
        if (root.isShowing() && root.isEnabled() && root.getProperties()["automationID"].toString() == id)
            if (auto* button = dynamic_cast<juce::Button*>(&root)) return button;
        for (auto* child : root.getChildren()) if (auto* button = find(*child, id)) return button;
        return nullptr;
    }
    bool click(const juce::String& id) {
        if (auto* button = find(ui::getAppHome(), id)) { button->triggerClick(); return true; }
        return false;
    }
    bool capture(const juce::String& name) {
        auto& screen = ui::getAppHome();
        auto stream = juce::File::getCurrentWorkingDirectory().getChildFile(name).createOutputStream();
        return stream && juce::PNGImageFormat().writeImageToStream(screen.createComponentSnapshot(screen.getLocalBounds()), *stream);
    }
    void finish(bool ok, const juce::String& reason) {
        juce::File::getCurrentWorkingDirectory().getChildFile("original-ui-test.txt")
            .replaceWithText((ok ? "PASS: " : "FAIL: ") + reason + " stage=" + juce::String(stage));
        capture("original-ui-final.png");
        std::_Exit(ok ? 0 : 3);
    }
    void timerCallback() override {
        if (++ticks > 60) { finish(false, "UI control unavailable or engine update timed out"); return; }
        switch (stage) {
        case 0:
            if (click("ignite.instruments")) ++stage;
            break;
        case 1:
            if (click("ignite.addInstrument")) ++stage;
            break;
        case 2:
            if (engine.instrumentManager->getInstrumentCount() > initialCount && click("ignite.presets")) ++stage;
            break;
        case 3:
            if (click("ignite.preset.nextGroup")) ++stage;
            break;
        case 4:
            if (click("ignite.preset.second")) ++stage;
            break;
        case 5:
            if (click("ignite.dialog.apply")) ++stage;
            break;
        case 6: {
            auto* instrument = engine.instrumentManager->getInstrumentFromListIndex(initialCount);
            if (instrument && instrument->getInternalSoundPgm() == 9 && click("ignite.presets")) ++stage;
            break;
        }
        case 7: {
            auto* group = find(ui::getAppHome(), "ignite.preset.group");
            auto* second = find(ui::getAppHome(), "ignite.preset.second");
            auto* instrument = engine.instrumentManager->getInstrumentFromListIndex(initialCount);
            if (!group || !second || !instrument) break;
            if (group->getButtonText() != "Chromatic Percussion" || !second->getToggleState() || instrument->getInternalSoundPgm() != 9) {
                finish(false, "Reopening presets changed the selected group or sound"); return;
            }
            capture("original-ui-presets.png");
            if (click("ignite.dialog.apply")) ++stage;
            break;
        }
        case 8:
            finish(true, "Original Instruments -> Add -> Presets -> category -> sound -> Apply; engine program=9; reopening retains selection");
            break;
        }
    }
    Ignite::IgniteEngine& engine;
    int initialCount = 0, stage = 0, ticks = 0;
};
