# **🚀 ulsp — Ultra Low-latency Systems Profiler**

**ulsp** is a production-grade C++20 library for high-performance systems engineers.  
 It provides a **Google Benchmark–style API** for measuring micro-architectural and operating system latencies with **nanosecond precision** across macOS, Linux, and Windows.

---

## **✨ Key Features**

### **Nanosecond-Precision Timing**

* **macOS** → `mach_absolute_time`

* **Linux** → `clock_gettime(CLOCK_MONOTONIC_RAW)`

* **Windows** → `QueryPerformanceCounter (QPC)`

Define benchmarks using a single macro:

`ULSP_BENCHMARK(MyBenchmark) {`

    `// code to measure`
    
`}`

### **Optimizer-Safe**

Built-in `DoNotOptimize()` prevents the compiler from eliminating benchmarked code.

### **Statistical Rigor**

Automatically reports:

* Mean
* p50
* p95
* p99

  ### **Installable & Relocatable**

Fully CMake-integrated and discoverable via:

`find_package(ulsp REQUIRED)`

---

## **📥 Getting ulsp**

### **Option A — Git Clone \+ CMake Install (Recommended)**

`git clone https://github.com/<your-org>/ulsp.git`

`cd ulsp`

`# Release mode is mandatory for valid measurements`

`cmake -B build -DCMAKE_BUILD_TYPE=Release`

`cmake --build build`

`sudo cmake --install build`

This installs:

* Headers → `/usr/local/include/ulsp`

* Library → `/usr/local/lib`

* CMake package → `/usr/local/lib/cmake/ulsp`

  ---

  ## **🛠 Build Requirements**

* CMake ≥ 3.20
* C++20 Compiler
* GCC 10+
* Clang 10+
* MSVC 19.28+

  ---

  ## **💻 Usage**

  ### **1\. CMake Integration**

  `cmake_minimum_required(VERSION 3.20)`

  `project(MyProject LANGUAGES CXX)`

  `find_package(ulsp REQUIRED)`

  `add_executable(my_app main.cpp)`

  `target_link_libraries(my_app PRIVATE ulsp::benchmark)`


  ---

  ### **2\. Writing Benchmarks**

  `#include <ulsp/benchmark/benchmark.h>`

  `#include <vector>`

  `#include <algorithm>`


  `ULSP_BENCHMARK(VectorSort) {`

      `std::vector<int> v(1000);`

      `for (size_t i = 0; i < v.size(); ++i)`

          `v[i] = 1000 - i;`


      `std::sort(v.begin(), v.end());`

      `ulsp::benchmark::DoNotOptimize(v.data());`

  `}`

  `int main() {`

      `ulsp::benchmark::RunAll();`

      `return 0;`

  `}`

  ---

  ## **⚙️ Advanced Configuration**

Override warmup and measurement iterations:

`ULSP_BENCHMARK(HeavyTask) {`

    `// expensive logic`

`}`

`static auto& cfg =`

    `ulsp::benchmark::internal::Registrar("HeavyTask", nullptr)`

        `.Iterations(5000)`

        `.Warmup(100);`

Defaults:

* Warmup → 10,000 iterations

* Measurement → 100,000 iterations

  ---

  ## **🎯 Practical Applications**

* Algorithmic trading engines

* Game engine subsystems

* Real-time audio and graphics pipelines

* Cloud infrastructure latency analysis

* Hardware and architecture comparison

  ---

