#pragma once
#include "ulsp/ulsp_export.h"
#include <vector>

namespace ulsp::core {

    struct StatsResult {
        double min;
        double max;
        double mean;
        double p50;
        double p95;
        double p99;
    };

    class ULSP_EXPORT Stats {
    public:
        static StatsResult calculate(std::vector<double>& samples);
    };

}