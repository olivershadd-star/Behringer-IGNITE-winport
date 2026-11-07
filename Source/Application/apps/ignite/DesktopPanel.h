// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <juce_audio_utils/juce_audio_utils.h>

// The original touchscreen is retained. These controls replace the physical
// switches/encoders, feeding MCU events into the original engine dispatcher.
class DesktopPanel final : public juce::Component, private juce::Timer
{
    using Key = Ignite::FrontPannelParam;
    struct Control {
        std::unique_ptr<juce::TextButton> button;
        Ignite::paramId_t id;
        bool down = false;
        bool held = false;
        double pressedAt = 0;
        int value = 1;
        bool momentary = true;
    };
public:
    explicit DesktopPanel(Ignite::IgniteEngine& model)
        : engine(model), screen(ui::getAppHome())
    {
        setWantsKeyboardFocus(true);
        addAndMakeVisible(surface);
        surface.addAndMakeVisible(screen);
        screen.setBounds(98, 76, 1024, 600);
        label(title, "IGNITE  /  WINDOWS", {16, 4, 290, 28}, 20);
        label(status, "", {450, 4, 750, 28}, 14);
        label(help, "Original touchscreen + virtual hardware. New instrument: internal sound by default. INSERT + pads edits steps.", {98, 678, 1040, 30}, 13);
        row({{"SONG", Key::paramKey_SONG}, {"SCENE", Key::paramKey_SCENE},
             {"TRACK", Key::paramKey_TRACK}, {"PATTERN", Key::paramKey_PATTERN},
             {"MENU", Key::paramKey_MENU}, {"SOUNDS", Key::paramKey_INTERNALSOUNDS},
             {"SAVE", Key::paramKey_SAVE}}, 14, 38, 96);
        action("Audio settings", {996, 38, 124, 30}, [this] { audioSettings(); });
        action("Help", {1126, 38, 80, 30}, [this] {
            juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::InfoIcon,
                "IGNITE on Windows", "The centre is the original touchscreen. The surrounding controls replace the hardware.\n\n"
                "SONG / SCENE / TRACK / PATTERN change the working level. INSERT + pads inserts steps; the small row below each pad is its encoder (-, push, +).\n\n"
                "SHIFT stays held until clicked again. The arrows move the navigation encoder; SELECT presses it.\n\n"
                "Create an instrument, choose Internal Sound and a preset, assign it to a track and choose a pattern. GeneralUser GS supplies replacement GM sounds; it is not the missing factory bank.");
        });
        row({{"RECORD", Key::paramKey_REC}, {"STOP", Key::paramKey_STOP},
             {"PLAY", Key::paramKey_PLAY}, {"TEMPO", Key::paramKey_TEMPO},
             {"INSERT", Key::paramKey_INSERT}, {"DELETE", Key::paramKey_DELETE},
             {"COPY", Key::paramKey_COPY_NAV}, {"RETURN", Key::paramKey_RETURN_NAV},
             {"SELECT", Key::paramKey_RSELECT}, {"<", Key::paramKey_RMOVELEFT},
             {">", Key::paramKey_RMOVERIGHT}}, 14, 714, 104);
        shift.setButtonText("SHIFT (hold)"); shift.setClickingTogglesState(true);
        surface.addAndMakeVisible(shift); shift.setBounds(14, 752, 116, 30);
        shift.onClick = [this] { send(Key::paramKey_PAGESHIFT, 1); };
        row({{"LAST", Key::paramKey_LAST}, {"FILL", Key::paramKey_FILL_X},
             {"SOLO / SKIP", Key::paramKey_SOLO_SKIP}, {"GANG", Key::paramKey_GANG},
             {"NEXT / TIE", Key::paramKey_NEXT_TIE}, {"SCULPT", Key::paramKey_SCULPT}}, 140, 752, 116);
        for (int i = 0; i < 16; ++i) {
            const int x = 14 + i * 75;
            control(juce::String(i + 1), static_cast<Key>(static_cast<int>(Key::paramKey_TRACKSEL1) + i), {x, 794, 70, 40});
            const auto encoder = static_cast<Key>(static_cast<int>(Key::paramRot_PADROT1) + i);
            control("-", encoder, {x, 840, 22, 28}, 0, false);
            control("o", static_cast<Key>(static_cast<int>(Key::paramKey_TRACKROTARY1) + i), {x + 24, 840, 22, 28});
            control("+", encoder, {x + 48, 840, 22, 28}, 1, false);
        }
        const std::pair<const char*, Key> knobs[] = {{"RELEASE", Key::paramKey_RELEASE}, {"FILTER", Key::paramKey_FILTER},
            {"RESONANCE", Key::paramKey_RESONANCE}, {"VOLUME", Key::paramKey_VOLUME},
            {"REVERB", Key::paramKey_REVERBE}, {"CHORUS", Key::paramKey_CHORUS},
            {"HIGH EQ", Key::paramKey_EQHI}, {"LOW EQ", Key::paramKey_EQLO}};
        for (int i = 0; i < 8; ++i) {
            const int x = i < 4 ? 8 : 1130, y = 132 + (i % 4) * 124;
            auto caption = std::make_unique<juce::Label>();
            label(*caption, knobs[i].first, {x, y, 82, 26}, 12);
            captions.push_back(std::move(caption));
            control("-", knobs[i].second, {x, y + 32, 38, 32}, 0, false);
            control("+", knobs[i].second, {x + 42, y + 32, 38, 32}, 1, false);
        }
        control("ROW", Key::paramKey_ROTARYROW, {8, 570, 82, 32});
        control("-", Key::paramRot_ROW, {8, 608, 38, 28}, 0, false);
        control("+", Key::paramRot_ROW, {50, 608, 38, 28}, 1, false);
        control("BAR", Key::paramKey_ROTARYBAR, {1130, 570, 82, 32});
        control("-", Key::paramRot_BAR, {1130, 608, 38, 28}, 0, false);
        control("+", Key::paramRot_BAR, {1172, 608, 38, 28}, 1, false);
        startTimerHz(20);
    }
    ~DesktopPanel() override { stopTimer(); surface.removeChildComponent(&screen); }
    void resized() override {
        const auto scale = juce::jmin(getWidth() / 1220.0f, getHeight() / 900.0f);
        surface.setBounds(0, 0, 1220, 900);
        surface.setTransform(juce::AffineTransform::scale(scale));
    }
    void paint(juce::Graphics& g) override { g.fillAll(juce::Colour(0xff171b24)); }
    bool keyPressed(const juce::KeyPress& key) override {
        const int c = key.getKeyCode();
        Key id;
        if (c == juce::KeyPress::spaceKey) id = Key::paramKey_PLAY;
        else if (c == juce::KeyPress::escapeKey) id = Key::paramKey_STOP;
        else if (c == juce::KeyPress::leftKey) id = Key::paramKey_RMOVELEFT;
        else if (c == juce::KeyPress::rightKey) id = Key::paramKey_RMOVERIGHT;
        else if (c == juce::KeyPress::returnKey) id = Key::paramKey_RSELECT;
        else return false;
        send(id, 1); send(id, 2); return true;
    }
private:
    void send(Key id, uint8_t value) {
        if (!engine.frontPannelManager->desktopKey(static_cast<Ignite::paramId_t>(id), value))
            status.setText("Control queue full: try again", juce::dontSendNotification);
    }
    void label(juce::Label& item, const juce::String& text, juce::Rectangle<int> bounds, float size) {
        surface.addAndMakeVisible(item); item.setBounds(bounds);
        item.setText(text, juce::dontSendNotification); item.setFont(juce::Font(size));
        item.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    }
    void control(const juce::String& text, Key id, juce::Rectangle<int> bounds, int value = 1, bool momentary = true) {
        auto item = std::make_unique<Control>();
        item->button = std::make_unique<juce::TextButton>(text);
        item->id = static_cast<Ignite::paramId_t>(id); item->value = value; item->momentary = momentary;
        auto* itemPtr = item.get();
        auto& button = *item->button;
        button.setWantsKeyboardFocus(false); button.setBounds(bounds);
        button.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff303b4d));
        if (momentary) button.onStateChange = [this, itemPtr] {
            const bool isPressed = itemPtr->button->isDown();
            if (isPressed == itemPtr->down) return;
            itemPtr->down = isPressed; itemPtr->held = false;
            itemPtr->pressedAt = juce::Time::getMillisecondCounterHiRes();
            send(static_cast<Key>(itemPtr->id), isPressed ? 1 : 2);
        };
        else button.onClick = [this, itemPtr] { send(static_cast<Key>(itemPtr->id), static_cast<uint8_t>(itemPtr->value)); };
        surface.addAndMakeVisible(button); controls.push_back(std::move(item));
    }
    void row(std::initializer_list<std::pair<const char*, Key>> items, int x, int y, int width) {
        for (const auto& item : items) { control(item.first, item.second, {x, y, width - 6, 30}); x += width; }
    }
    void action(const juce::String& text, juce::Rectangle<int> bounds, std::function<void()> fn) {
        auto button = std::make_unique<juce::TextButton>(text);
        button->setBounds(bounds); button->onClick = std::move(fn);
        surface.addAndMakeVisible(*button); actions.push_back(std::move(button));
    }
    void audioSettings() {
        if (engine.songManager->dm == nullptr) return;
        auto* selector = new juce::AudioDeviceSelectorComponent(*engine.songManager->dm, 0, 0, 0, 2, false, false, true, false);
        selector->setSize(520, 450);
        juce::DialogWindow::LaunchOptions options;
        options.content.setOwned(selector); options.dialogTitle = "Windows audio output - select 48000 Hz";
        options.dialogBackgroundColour = juce::Colour(0xff202633);
        options.useNativeTitleBar = true; options.escapeKeyTriggersCloseButton = true;
        options.launchAsync();
    }
    void timerCallback() override {
        for (auto& item : controls) {
            if (item->momentary && item->down && !item->held && juce::Time::getMillisecondCounterHiRes() - item->pressedAt > 500) {
                send(static_cast<Key>(item->id), 3); item->held = true;
            }
            if (item->momentary) {
                auto state = engine.frontPannelManager->desktopLed(item->id);
                if (item->id >= 30 && item->id <= 45) {
                    const auto rgb = engine.frontPannelManager->desktopLed(100u + item->id - 30u);
                    if (rgb >= 0xa0) state = rgb;
                }
                auto colour = juce::Colour(0xff303b4d);
                if (state == 2 || state == 4) colour = juce::Colour(0xff187d92);
                else if (state >= 6 && state <= 11) {
                    const bool phase = (juce::Time::getMillisecondCounter() / 250u) % 2u == 0;
                    if (phase) colour = juce::Colour(0xff187d92);
                } else if (state > 0xa0) {
                    const juce::uint32 palette[] = {0xffdf5050, 0xff45b877, 0xff4588db, 0xffa368c9,
                        0xffdddddd, 0xff64bdcf, 0xff78838f, 0xffc999df};
                    colour = juce::Colour(palette[juce::jmin(7, static_cast<int>(state) - 0xa1)]);
                }
                item->button->setColour(juce::TextButton::buttonColourId, colour);
            }
        }
        auto* device = engine.songManager->dm ? engine.songManager->dm->getCurrentAudioDevice() : nullptr;
        status.setText(juce::String(engine.songManager->get_tsf_instance() ? "GM bank loaded" : "Missing Ignite.sf2")
            + "  |  " + (device ? device->getName() + " / " + juce::String(device->getCurrentSampleRate(), 0) + " Hz" : "No audio output - open Audio settings"), juce::dontSendNotification);
    }
    Ignite::IgniteEngine& engine;
    juce::Component surface;
    juce::Component& screen;
    juce::Label title, status, help;
    juce::TextButton shift;
    std::vector<std::unique_ptr<Control>> controls;
    std::vector<std::unique_ptr<juce::TextButton>> actions;
    std::vector<std::unique_ptr<juce::Label>> captions;
};
