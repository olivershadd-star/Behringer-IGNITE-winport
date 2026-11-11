// SPDX-License-Identifier: AGPL-3.0-or-later
#include "EmbeddedBank.h"
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
EmbeddedBank getEmbeddedBank() {
    const auto module=GetModuleHandleW(nullptr);
    const auto resource=FindResourceW(module,MAKEINTRESOURCEW(101),RT_RCDATA);
    if(resource==nullptr)return {};
    const auto loaded=LoadResource(module,resource);
    return {loaded?LockResource(loaded):nullptr,SizeofResource(module,resource)};
}
#else
EmbeddedBank getEmbeddedBank(){return {};}
#endif
