// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <string>
namespace Ignite {
struct PatternData;
// Musical notifications and persistence are host services, not MCU services.
class PatternHost {
public:
    virtual ~PatternHost() = default;
    virtual void patternLengthChanged(const std::string& name,int bars)=0;
    virtual void patternCleared(const std::string& name)=0;
    virtual void savePatternReferences(const PatternData& data)=0;
};
}
