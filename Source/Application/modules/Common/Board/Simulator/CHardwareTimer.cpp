#include "../Board/CHardwareTimer.h"

#ifdef __linux__
#include <climits>
#define SEC_TO_NSEC_SCALER 1000000000
#define USEC_TO_NSEC_SCALER 1000
#endif

using namespace Ignite;

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#include <mmsystem.h>
#endif

CHardwareTimer::CHardwareTimer(HardwareTimerCb cb, void* context)
    : _callback(cb)
    , _context(context)
{
    _id = std::rand() % 100;
}

CHardwareTimer::~CHardwareTimer()
{
    stop();
#ifdef _WIN32
    _running.store(false);
    _timerCv.notify_all();
    if (_thread.joinable()) _thread.join();
#endif
}
bool CHardwareTimer::start(const uint16_t intervalus)
{
    _intervalus = intervalus;
#ifdef __linux__
    struct timespec ts;
    if (clock_gettime (CLOCK_MONOTONIC, &ts) < 0)
    {
        perror("clock_gettime");
        exit(1);
    }
    printf ("Start : Cur time %llu : %llu\n", ts.tv_sec, ts.tv_nsec);
    long long unsigned int currentTimeNs = (ts.tv_sec * SEC_TO_NSEC_SCALER) + ts.tv_nsec;
    long long unsigned int nextExpiryNs = currentTimeNs + (_intervalus * USEC_TO_NSEC_SCALER);
    _timepoint.tv_sec = nextExpiryNs / SEC_TO_NSEC_SCALER;
    _timepoint.tv_nsec = nextExpiryNs % SEC_TO_NSEC_SCALER;
    printf("_intervalus = %u\n", _intervalus);
    printf("Start : Next expiry %llu : %llu\n", _timepoint.tv_sec, _timepoint.tv_nsec);
    if (_running)
    {
        _activeCB = true;// thread we are not stoping
        return true;
    }
    struct sched_param param;
    int policy = SCHED_FIFO; // Use SCHED_FIFO for real-time scheduling
    int max_priority = sched_get_priority_max(policy);
    param.sched_priority = max_priority;

    if (pthread_create(&_thread, nullptr, &CHardwareTimer::loop, this) != 0)
    {
        std::cerr << "Failed to create thread" << std::endl;
        return EXIT_FAILURE;
    }
    _running = true;
    _activeCB = true;//updating below may not reach, as thread started safe to update now
    if (pthread_setschedparam(_thread, policy, &param) != 0)
    {
        std::cerr << "pthread_setschedparam failed: " << strerror(errno) << std::endl;
    }
    else
        std::cout << "pthread setschedparam success" << max_priority << std::endl;

    /* disabled CPU set - disabled bez thread timer has more distraction */
    //cpu_set_t cpuset;
    //CPU_ZERO(&cpuset);
    //CPU_SET(3, &cpuset); // Set affinity to CPU 0

    //if (pthread_setaffinity_np(_thread, sizeof(cpu_set_t), &cpuset) != 0) {
    //    std::cerr << "pthread_setaffinity_np failed: " << strerror(errno) << std::endl;
    //    return EXIT_FAILURE;
    //}
    //else {
    //    std::cout << "pthread_setaffinity_np success" << std::endl;
    //}
    pthread_detach(_thread);

#elif defined  _WIN32
    if (intervalus == 0) return false;
    _activeCB.store(true);
    // Publish state before spawning: the old worker could exit before start()
    // set _running. One worker remains alive across pause/resume.
    if (_running.exchange(true)) {
        _timerCv.notify_all();
        return true;
    }
    _thread = std::thread(&CHardwareTimer::hiResTimerThread, this);
#endif
     _running = true;
    _activeCB = true;
    return true;
}

bool CHardwareTimer::stop(void)
{
    if (_running)
    {
    //_running = false; -- not stoping
    _activeCB = false;// disable the Call back
#ifdef _WIN32
    _timerCv.notify_all();
#endif
#ifdef __linux__
    //pthread_join(_thread, nullptr);
#endif
    }
    return true;
}

bool CHardwareTimer::changeInterval(const uint16_t intervalus)
{
    if (intervalus == 0) return false;
    if (!_running)
    {
        start(intervalus);
    }
    else
    {
        _intervalus = intervalus;
#ifdef _WIN32
        _timerCv.notify_all();
#endif
#ifdef __linux__
        struct timespec ts;
        if (clock_gettime (CLOCK_MONOTONIC, &ts) < 0)
        {
            perror ("clock_gettime");
            return false;
        }
        //printf ("Change : Cur time %llu : %llu\n", ts.tv_sec, ts.tv_nsec);
        long long unsigned int currentTimeNs = (ts.tv_sec * SEC_TO_NSEC_SCALER) + ts.tv_nsec;
        long long unsigned int nextExpiryNs = currentTimeNs + (_intervalus * USEC_TO_NSEC_SCALER);
        _timepoint.tv_sec = nextExpiryNs / SEC_TO_NSEC_SCALER;
        _timepoint.tv_nsec = nextExpiryNs % SEC_TO_NSEC_SCALER;
        DBG("_intervalus :" + String(_intervalus));
        //printf ("Change : Next expiry %llu : %llu\n", _timepoint.tv_sec, _timepoint.tv_nsec);
        //std::cout << _intervalus << std::endl;;
#endif
    }
    return true;
}

uint32_t CHardwareTimer::getFrequency(void) const
{
    return 1000000;
}

int8_t CHardwareTimer::getId(void) const
{
    return _id;
}


#ifdef __linux__
void* CHardwareTimer::loop(void* arg) {
    CHardwareTimer* timer = static_cast<CHardwareTimer*>(arg);
    if (arg == nullptr) {
        std::cerr << "CHardwareTimer::loop Error: arg is nullptr" << std::endl;
        return nullptr;
    }
    timer->run();
    return nullptr;
}

void CHardwareTimer::run(void)
{
    while (_running)
    {
        struct timespec ts;
        if (!_activeCB)
        {
            std::this_thread::yield();
            continue;
        }
        if (clock_gettime(CLOCK_MONOTONIC, &ts) < 0)
        {
            perror("clock_gettime");
            continue;
        }
        long long unsigned int currentTimeNs = (ts.tv_sec * SEC_TO_NSEC_SCALER) + ts.tv_nsec;
        long long unsigned int expiryTimeNs = (_timepoint.tv_sec * SEC_TO_NSEC_SCALER) + _timepoint.tv_nsec;
        //std::cout << "currentTimeNs: " << currentTimeNs << ", expiryTimeNs: " << expiryTimeNs << " _activeCB " << _activeCB << std::endl;
        //if (currentTimeNs == 0) {
        //    std::cout << "currentTimeNs is zero, likely due to system boot or clock initialization." << std::endl;
        //    continue;
        //}
        if ((currentTimeNs >= expiryTimeNs) && _callback)
        {
            long long unsigned int nextExpiryNs = expiryTimeNs + (_intervalus * USEC_TO_NSEC_SCALER);
            _timepoint.tv_sec = nextExpiryNs / SEC_TO_NSEC_SCALER;
            _timepoint.tv_nsec = nextExpiryNs % SEC_TO_NSEC_SCALER;
            _callback(_context);
        }
    }
}
#endif /* __linux__ */

#ifdef _WIN32

void CHardwareTimer::hiResTimerThread(void)
{
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
    const bool resolutionSet = timeBeginPeriod(1) == TIMERR_NOERROR;
    std::unique_lock<std::mutex> lock(_timerMutex);
    auto next = std::chrono::steady_clock::now();
    while (_running.load()) {
        if (!_activeCB.load()) {
            _timerCv.wait(lock, [this] { return !_running.load() || _activeCB.load(); });
            next = std::chrono::steady_clock::now();
            continue;
        }
        const auto period = std::chrono::microseconds(_intervalus.load());
        next += period;
        if (_timerCv.wait_until(lock, next) != std::cv_status::timeout) {
            next = std::chrono::steady_clock::now();
            continue;
        }
        if (!_running.load() || !_activeCB.load()) continue;
        lock.unlock();
        if (_callback) _callback(_context);
        lock.lock();
        const auto now = std::chrono::steady_clock::now();
        if (now > next + period * 4) next = now;
    }
    lock.unlock();
    if (resolutionSet) timeEndPeriod(1);
}

#endif /* _WIN32 */
