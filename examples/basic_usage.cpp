#include <ulsp/benchmark/benchmark.h>
#include <vector>
#include <algorithm>
#include <cmath>

ULSP_BENCHMARK(VectorSort) {
    std::vector<int> v(1000);
    for(size_t i=0; i<v.size(); ++i) v[i] = 1000 - i;
    
    std::sort(v.begin(), v.end());
    ulsp::benchmark::DoNotOptimize(v.data());
}

ULSP_BENCHMARK(TrigMath) {
    double res = 0;
    for(int i=0; i<100; ++i) {
        res += std::sin(i) * std::cos(i);
    }
    ulsp::benchmark::DoNotOptimize(res);
}

int main() {
    ulsp::benchmark::RunAll();
    return 0;
}