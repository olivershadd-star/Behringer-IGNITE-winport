#include "common_threadwithprogressbar.h"
namespace ui
{
    CommonThreadWithProgressBar::CommonThreadWithProgressBar(const String& title, const int cancellingTimeOutMs)
        : Thread("ThreadWithProgressWindow"),
        progress(0.0),
        timeOutMsWhenCancelling(cancellingTimeOutMs),
        _title(title)
    {

        ptr = new CommonPopUp(title, 604, 290);
        ptr->addProgressBar(progress);
        ptr->SetControlBtnLine(false);
        ptr->isCloseButtonVisible(false);
    }

    bool CommonThreadWithProgressBar::isEditing()
    {
        if (ptr!= nullptr && ptr->IsEditing())
            return true;
        return false;
    }

    bool CommonThreadWithProgressBar::FPKeyHandler(bool isFocuse, paramId_t param, uint32_t KeyValue)
    {
        ptr->popupType = POPUP_WITHOK;
        return ptr->FPKeyHandler(isFocuse, param, KeyValue);
    }

    void CommonThreadWithProgressBar::setStatusMessageStartEnd(String statusTextStart, String statusTextEnd)
    {
        _statusMsgStart = statusTextStart;
        _statusMsgEnd = statusTextEnd;
    }

    CommonThreadWithProgressBar::~CommonThreadWithProgressBar()
    {
        stopThread(timeOutMsWhenCancelling);
    }

    void CommonThreadWithProgressBar::launchThread(int priority)
    {
        JUCE_ASSERT_MESSAGE_THREAD

        startThread((Priority)priority);
        startTimer(100);

        {
            const ScopedLock sl(messageLock);
            ptr->setInfoText(_statusMsgStart);
        }

        ptr->show();
    }

    void CommonThreadWithProgressBar::setProgress(const double newProgress)
    {
        progress = newProgress;
        ptr->setProgressBar(progress);
    }

    void CommonThreadWithProgressBar::setStatusMessage(const String& newStatusMessage)
    {
        const ScopedLock sl(messageLock);
        message = newStatusMessage;
    }

    void CommonThreadWithProgressBar::timerCallback()
    {
        bool threadStillRunning = isThreadRunning();

        if (!(threadStillRunning))
        {
            stopTimer();
            stopThread(timeOutMsWhenCancelling);
            threadComplete();
            return; // (this may be deleted now)
        }

        const ScopedLock sl(messageLock);
        ptr->setInfoText(_statusMsgStart);
    }

    void CommonThreadWithProgressBar::run()
    {
        setStatusMessage(_statusMsgStart);
        wait(2000);
        jobTask();
        /*TODO: Actual Firmware upgrade Handling*/
        int thingsToDo = 10;

        for (int i = 0; i <= thingsToDo; ++i)
        {
            if (threadShouldExit())
                return;
            setProgress(i / (double)thingsToDo);
            wait(500);
        }
        setStatusMessage(_statusMsgStart);
        wait(2000);
    }

    void CommonThreadWithProgressBar::threadComplete()
    {
        ptr->removeProgressBar();
        ptr->setInfoText(_statusMsgEnd);
        
    }

    bool CommonThreadWithProgressBar::runThread(const int priority)
    {
        launchThread(priority);

        while (isTimerRunning())
            MessageManager::getInstance()->runDispatchLoopUntil(5);

        return false;
    }
}