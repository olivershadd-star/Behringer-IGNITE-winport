#include <atomic>
#include <cassert>
#include <chrono>
#include <thread>
#include "CHardwareTimer.h"
int main() {
    std::atomic<int> ticks{0};
    {
        Ignite::CHardwareTimer timer([](void* p) { ++*static_cast<std::atomic<int>*>(p); }, &ticks);
        assert(!timer.start(0));
        assert(timer.start(2000));
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        assert(ticks.load() >= 5 && ticks.load() < 500);
        timer.stop();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        const int paused = ticks.load();
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
        assert(ticks.load() == paused);
        assert(timer.start(3000));
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
        assert(ticks.load() > paused);
        assert(!timer.changeInterval(0));
        assert(timer.changeInterval(4000));
    }
    const int stopped = ticks.load();
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
    assert(ticks.load() == stopped);
}
