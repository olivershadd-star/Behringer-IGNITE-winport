/*
 * Copyright (c) - 2021 - MUSIC Tribe, MY.
 * This file is part of IGNITE.
 *
 * IGNITE is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Affero General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * IGNITE is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with IGNITE. If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */
#pragma once
namespace ui
{
    class JUCE_API  CommonThreadWithProgressBar : public Thread,
        private Timer
    {
    public:
        CommonThreadWithProgressBar(const String& windowTitle, int timeOutMsWhenCancelling = 10000);
        ~CommonThreadWithProgressBar() override;
        bool runThread(int priority = 0);

        void run() override;
        void launchThread(int priority = 0);
        void setProgress(double newProgress);
        void setStatusMessage(const String& newStatusMessage);
        void threadComplete();
        void setStatusMessageStartEnd(String statusTextStart, String statusTextEnd);
        std::function<void()> jobTask;
        bool FPKeyHandler(bool isFocuse, paramId_t param, uint32_t KeyValue);
        bool isEditing();

    private:
        void timerCallback() override;

        String _statusMsgStart;
        String _statusMsgEnd;
        String _title;
        String message;
        double progress;
        CommonPopUp* ptr;
        CriticalSection messageLock;
        const int timeOutMsWhenCancelling;
        

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CommonThreadWithProgressBar)
    };
};