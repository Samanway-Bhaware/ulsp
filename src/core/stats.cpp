#include "ulsp/core/stats.h"
#include <algorithm>
#include <numeric>
#include <cmath>

namespace ulsp::core {

    static double get_percentile(const std::vector<double>& s, double p) {
        if (s.empty()) return 0.0;
        size_t idx = static_cast<size_t>(std::ceil(p * s.size())) - 1;
        idx = std::max(size_t(0), std::min(idx, s.size() - 1));
        return s[idx];
    }

    StatsResult Stats::calculate(std::vector<double>& samples) {
        if (samples.empty()) return {};
        
        std::sort(samples.begin(), samples.end());
        double sum = std::accumulate(samples.begin(), samples.end(), 0.0);
        
        return {
            samples.front(),
            samples.back(),
            sum / samples.size(),
            get_percentile(samples, 0.50),
            get_percentile(samples, 0.95),
            get_percentile(samples, 0.99)
        };
    }

}