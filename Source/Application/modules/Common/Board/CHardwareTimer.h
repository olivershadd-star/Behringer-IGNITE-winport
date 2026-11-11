#pragma once
#include <stdint.h>
//#ifdef BUILD_SIMULATOR
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
//#endif
#ifdef __linux__
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#endif

namespace Ignite
{

    using HardwareTimerCb = void (*)(void*);

    class CHardwareTimer
    {
        public:
            explicit CHardwareTimer(HardwareTimerCb cb, void* context);
            virtual ~CHardwareTimer();
            bool start(const uint16_t intervalus);
            bool stop(void);
            bool changeInterval(const uint16_t intervalus);
            uint32_t getFrequency(void) const;
            int8_t getId(void) const;

        private:
            int8_t _id = -1;

#ifdef __linux__
            pthread_t _thread;
            static void* loop(void* arg);
            void run(void);
#endif
#ifdef _WIN32
            std::thread _thread;
			void hiResTimerThread(void);
#endif
            #ifdef _WIN32
            std::atomic<uint32_t> _intervalus{0};
            std::atomic<bool> _running{false}, _activeCB{false};
            std::mutex _timerMutex;
            std::condition_variable _timerCv;
#else
            uint32_t _intervalus = 0;
#endif
            HardwareTimerCb _callback;
            void* _context;
            #ifndef _WIN32
            bool _running = false;
            bool _activeCB = false;
#endif
#ifdef __linux__
            struct timespec _timepoint;
#endif
    };
} // namespace Ignite
