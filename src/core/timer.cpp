#include "ulsp/core/timer.h"
#include <mutex>

#if defined(__APPLE__)
    #include <mach/mach_time.h>
    static mach_timebase_info_data_t g_tb;
    static std::once_flag g_init;
#elif defined(_WIN32)
    #include <windows.h>
    static double g_freq_inv = 0.0;
#else // Linux
    #include <time.h>
#endif

namespace ulsp::core {

    void Timer::init() {
    #if defined(__APPLE__)
        std::call_once(g_init, [](){ mach_timebase_info(&g_tb); });
    #elif defined(_WIN32)
        LARGE_INTEGER freq;
        QueryPerformanceFrequency(&freq);
        g_freq_inv = 1.0e9 / (double)freq.QuadPart;
    #endif
    }

    uint64_t Timer::now_ticks() {
    #if defined(__APPLE__)
        return mach_absolute_time();
    #elif defined(_WIN32)
        LARGE_INTEGER c;
        QueryPerformanceCounter(&c);
        return c.QuadPart;
    #else
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        return (uint64_t)ts.tv_sec * 1000000000ULL + ts.tv_nsec;
    #endif
    }

    uint64_t Timer::ticks_to_ns(uint64_t ticks) {
    #if defined(__APPLE__)
        return (ticks * g_tb.numer) / g_tb.denom;
    #elif defined(_WIN32)
        return (uint64_t)(ticks * g_freq_inv);
    #else
        return ticks;
    #endif
    }

}