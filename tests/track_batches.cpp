#include "../Source/Application/modules/Common/Modules/TrackBatches.h"
#include <cassert>
#include <vector>
#include <numeric>
int main() {
    for(int tracks : {0,1,7,8,9,15,16,63,64}) {
        std::vector<int> input(tracks), delivered;
        std::iota(input.begin(), input.end(), 0);
        std::size_t workers = 0;
        Ignite::dispatchTrackBatches(input.begin(), input.end(), [&](std::size_t worker, auto first, auto last) {
            assert(worker == workers++ && worker < 8);
            assert(last-first > 0 && last-first <= 8);
            delivered.insert(delivered.end(), first, last);
        });
        assert(delivered == input);
        assert(workers == static_cast<std::size_t>((tracks+7)/8));
    }
}
