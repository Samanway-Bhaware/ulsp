#include "ulsp/benchmark/benchmark.h"
#include "ulsp/core/timer.h"
#include "ulsp/core/stats.h"
#include <iostream>
#include <iomanip>
#include <vector>

namespace ulsp::benchmark {
    
    // Forward declare the struct from registry.cpp
    struct Entry {
        std::string name;
        internal::BenchFn fn;
        size_t iterations;
        size_t warmup;
    };
    std::vector<Entry>& get_internal_entries();

    void RunAll() {
        core::Timer::init();
        auto& entries = get_internal_entries();

        std::cout << "\n[ ULSP Benchmark Runner ]\n";
        std::cout << "------------------------------------------------------------\n";
        std::cout << std::left << std::setw(30) << "Benchmark" 
                  << " | " << std::setw(10) << "Mean" 
                  << " | " << std::setw(10) << "p99" 
                  << " | Iterations\n";
        std::cout << "------------------------------------------------------------\n";

        for (const auto& entry : entries) {
            // Warmup
            for(size_t i=0; i<entry.warmup; ++i) entry.fn();

            // Measure
            std::vector<double> samples;
            samples.reserve(entry.iterations);

            for(size_t i=0; i<entry.iterations; ++i) {
                auto start = core::Timer::now_ticks();
                entry.fn();
                auto end = core::Timer::now_ticks();
                samples.push_back((double)core::Timer::ticks_to_ns(end - start));
            }

            // Report
            auto stats = core::Stats::calculate(samples);
            
            std::cout << std::left << std::setw(30) << entry.name 
                      << " | " << std::fixed << std::setprecision(1) << std::setw(7) << stats.mean << " ns"
                      << " | " << std::setw(7) << stats.p99 << " ns"
                      << " | " << entry.iterations << "\n";
        }
        std::cout << "------------------------------------------------------------\n";
    }
}