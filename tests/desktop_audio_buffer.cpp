#include "../Source/Application/modules/Firmware/Application/Model/DesktopAudioBuffer.h"
#include <cassert>
#include <vector>
int main() {
    IgniteDesktop::MonoBlockAdapter<960> adapter;
    int generated = 0, consumed = 0;
    auto render = [&](float* block) { for (int i=0;i<960;++i) block[i]=float(generated++); };
    for (int n : {1, 127, 256, 512, 960, 1024, 2048, 3}) {
        std::vector<float> left(n+2, -99), right(n+2, -99);
        float* outputs[] = {left.data()+1, nullptr, right.data()+1};
        adapter.read(outputs, 3, n, render);
        assert(left.front()==-99 && left.back()==-99);
        assert(right.front()==-99 && right.back()==-99);
        for (int i=0;i<n;++i) {
            assert(left[i+1]==float(consumed++));
            assert(right[i+1]==left[i+1]);
        }
    }
    adapter.reset();
    float value = -1; float* out[] = {&value};
    const int next = generated;
    adapter.read(out, 1, 1, render);
    assert(value==float(next));
    adapter.read(nullptr, 0, 100, render);
    adapter.read(out, 1, 0, render);
}
