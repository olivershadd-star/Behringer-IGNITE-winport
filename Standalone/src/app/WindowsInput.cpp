// SPDX-License-Identifier: AGPL-3.0-or-later
#include "WindowsInput.h"
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
bool clickWindowsPoint(int x,int y) {
    const auto width=GetSystemMetrics(SM_CXSCREEN),height=GetSystemMetrics(SM_CYSCREEN);
    if(width<2||height<2)return false;
    INPUT events[3]{};
    events[0].type=INPUT_MOUSE;events[0].mi.dx=static_cast<LONG>((static_cast<double>(x)*65535)/(width-1));events[0].mi.dy=static_cast<LONG>((static_cast<double>(y)*65535)/(height-1));events[0].mi.dwFlags=MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
    events[1].type=INPUT_MOUSE;events[1].mi.dwFlags=MOUSEEVENTF_LEFTDOWN;
    events[2].type=INPUT_MOUSE;events[2].mi.dwFlags=MOUSEEVENTF_LEFTUP;
    return SendInput(3,events,sizeof(INPUT))==3;
}
bool sendWindowsKey(unsigned short key) {
    INPUT events[2]{};events[0].type=events[1].type=INPUT_KEYBOARD;events[0].ki.wVk=events[1].ki.wVk=key;events[1].ki.dwFlags=KEYEVENTF_KEYUP;
    return SendInput(2,events,sizeof(INPUT))==2;
}
#else
bool clickWindowsPoint(int,int){return false;}
bool sendWindowsKey(unsigned short){return false;}
#endif
