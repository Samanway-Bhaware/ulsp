#pragma once
#include "ulsp/ulsp_export.h"
#include <cstdint>

namespace ulsp::core {

    class ULSP_EXPORT Timer {
    public:
        static void init();
        static uint64_t now_ticks();
        static uint64_t ticks_to_ns(uint64_t ticks);
    };

}