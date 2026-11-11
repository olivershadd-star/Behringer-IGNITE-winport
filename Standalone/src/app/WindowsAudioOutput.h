// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>
// Driver-paced PCM output, following KICK Lab's working WinMM transport.
// There is only one render consumer, and no UI timer drives the sample clock.
class WindowsAudioOutput {
public:
    static constexpr unsigned defaultDevice=0xffffffffu;
    using Prepare=std::function<void(double)>;
    using Render=std::function<void(float*,float*,int)>;
    WindowsAudioOutput();
    ~WindowsAudioOutput();
    bool start(Prepare,Render,unsigned device=defaultDevice);
    void stop();
    bool active() const;
    bool running() const;
    unsigned error() const;
    std::wstring errorText() const;
    std::wstring deviceName() const;
    static std::vector<std::pair<unsigned,std::wstring>> devices();
private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};
