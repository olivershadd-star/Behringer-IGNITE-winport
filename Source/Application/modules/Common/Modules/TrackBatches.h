// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <cstddef>
namespace Ignite {
// The eight playback workers each accept up to eight tracks. The final partial
// group must be delivered too (a song is not necessarily 8/16/.../64 tracks).
template<class Iterator, class Dispatch>
void dispatchTrackBatches(Iterator first, Iterator last, Dispatch dispatch) {
    std::size_t worker = 0;
    while (first != last) {
        auto end = first;
        for (int count = 0; count < 8 && end != last; ++count) ++end;
        dispatch(worker++, first, end);
        first = end;
    }
}
}
