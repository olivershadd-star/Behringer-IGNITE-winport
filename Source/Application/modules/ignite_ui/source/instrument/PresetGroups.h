// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
namespace ui { namespace PresetGroups {
// Original IGNITE grouping: Strings includes the GM Ensemble family (16 sounds).
constexpr int start(int group) { return group <= 5 ? group * 8 : group * 8 + 8; }
constexpr int group(int program) {
    return program < 40 ? program / 8 : program < 56 ? 5 : program < 128 ? (program - 8) / 8 : 15;
}
} }
