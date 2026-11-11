// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <cstddef>
struct EmbeddedBank { const void* data=nullptr; size_t size=0; };
EmbeddedBank getEmbeddedBank();
