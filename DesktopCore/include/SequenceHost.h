// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <string>
namespace Ignite {
class Pattern;
// The sequencer needs the musical document, never a device or firmware engine.
class SequenceHost {
public:
    virtual ~SequenceHost() = default;
    virtual Pattern* findPattern(const std::string& name) = 0;
};
}
