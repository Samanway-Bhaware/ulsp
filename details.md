# ulsp — Ultra Low-latency Systems Profiler

ulsp is a small, portable C++20 micro-benchmarking library inspired by Google Benchmark. It provides nanosecond-precision timing on macOS, Linux and Windows and a minimal API to define and run microbenchmarks.

Key project files:
- [CMakeLists.txt](CMakeLists.txt)
- [CMakePresets.json](CMakePresets.json)
- [cmake/version.h.in](cmake/version.h.in)
- [cmake/ulspConfig.cmake.in](cmake/ulspConfig.cmake.in)
- Public headers:
  - [include/ulsp/benchmark/benchmark.h](include/ulsp/benchmark/benchmark.h)
  - [include/ulsp/core/timer.h](include/ulsp/core/timer.h)
  - [include/ulsp/core/stats.h](include/ulsp/core/stats.h)
- Core sources:
  - [src/benchmark/registry.cpp](src/benchmark/registry.cpp)
  - [src/benchmark/runner.cpp](src/benchmark/runner.cpp)
  - [src/core/timer.cpp](src/core/timer.cpp)
  - [src/core/stats.cpp](src/core/stats.cpp)
- Example: [examples/basic_usage.cpp](examples/basic_usage.cpp)

Highlights
- Nanosecond timing on:
  - macOS via mach_absolute_time ([`ulsp::core::Timer::now_ticks`](include/ulsp/core/timer.h), implementation [src/core/timer.cpp](src/core/timer.cpp))
  - Linux via clock_gettime ([`ulsp::core::Timer::now_ticks`](include/ulsp/core/timer.h))
  - Windows via QPC ([`ulsp::core::Timer::now_ticks`](include/ulsp/core/timer.h))
- Built-in optimizer barrier: [`ulsp::benchmark::DoNotOptimize`](include/ulsp/benchmark/benchmark.h)
- Easy benchmark registration via macro: `ULSP_BENCHMARK` ([include/ulsp/benchmark/benchmark.h](include/ulsp/benchmark/benchmark.h))
- Simple runner: [`ulsp::benchmark::RunAll`](include/ulsp/benchmark/benchmark.h) (driver in [src/benchmark/runner.cpp](src/benchmark/runner.cpp))
- Basic stats (min/max/mean/p50/p95/p99): [`ulsp::core::Stats::calculate`](include/ulsp/core/stats.h) (implementation [src/core/stats.cpp](src/core/stats.cpp))

Quickstart (local build)
1. Configure (Release recommended for valid measurements):
```sh
mkdir -p build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release