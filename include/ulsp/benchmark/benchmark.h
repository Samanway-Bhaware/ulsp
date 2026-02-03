#pragma once
#include "ulsp/ulsp_export.h"
#include <cstddef>

namespace ulsp::benchmark {

    // --- Optimization Barrier ---
    template <typename T>
    inline void DoNotOptimize(T&& datum) {
        #if defined(__clang__) || defined(__GNUC__)
            asm volatile("" : "+r,m" (datum) : : "memory");
        #else
            volatile T* p = &datum; (void)*p;
        #endif
    }

    // --- Public Runner ---
    ULSP_EXPORT void RunAll();

    // --- Internal Registry Helper ---
    namespace internal {
        using BenchFn = void(*)();

        class ULSP_EXPORT Registrar {
        public:
            Registrar(const char* name, BenchFn fn);
            Registrar& Iterations(size_t n);
            Registrar& Warmup(size_t n);
        };
    }
}

// --- Macros ---
#define ULSP_BENCHMARK(name) \
    void ulsp_bench_##name(); \
    static ::ulsp::benchmark::internal::Registrar name##_registrar(#name, &ulsp_bench_##name); \
    void ulsp_bench_##name()