// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <algorithm>
#include <array>
#include <cstddef>

namespace IgniteDesktop {
// Bridges the existing fixed-block DSP to variable-size device callbacks.
// Owned and consumed exclusively by the audio callback thread.
template <std::size_t BlockSize> class MonoBlockAdapter {
    static_assert(BlockSize > 0, "Block size must be positive");
public:
    void reset() { cursor = BlockSize; }
    template <typename Render>
    void read(float* const* outputs, int channels, int samples, Render render) {
        if (channels <= 0 || samples <= 0) return;
        int offset = 0;
        while (offset < samples) {
            if (cursor == BlockSize) {
                block.fill(0.0f);
                render(block.data());
                cursor = 0;
            }
            const auto count = std::min<std::size_t>(BlockSize - cursor, samples - offset);
            for (int ch = 0; ch < channels; ++ch)
                if (outputs[ch] != nullptr)
                    std::copy_n(block.data() + cursor, count, outputs[ch] + offset);
            cursor += count;
            offset += static_cast<int>(count);
        }
    }
private:
    std::array<float, BlockSize> block{};
    std::size_t cursor = BlockSize;
};
}
