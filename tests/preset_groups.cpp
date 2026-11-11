#include "../Source/Application/modules/ignite_ui/source/instrument/PresetGroups.h"
#include <cassert>
int main() {
    for(int program=0;program<138;++program) {
        const auto group=ui::PresetGroups::group(program);
        const auto index=program-ui::PresetGroups::start(group);
        assert(group>=0 && group<16);
        assert(index>=0 && index<(group==5?16:group==15?10:8));
        assert(ui::PresetGroups::start(group)+index==program);
    }
    assert(ui::PresetGroups::group(8)==1);
    assert(ui::PresetGroups::group(48)==5);
    assert(ui::PresetGroups::group(56)==6);
    assert(ui::PresetGroups::group(128)==15);
    assert(ui::PresetGroups::start(15)==128);
}
