#include "ulsp/benchmark/benchmark.h"
#include <vector>
#include <string>

namespace ulsp::benchmark {

    struct Entry {
        std::string name;
        internal::BenchFn fn;
        size_t iterations = 100000;
        size_t warmup = 1000;
    };

    // Singleton Registry
    class Registry {
    public:
        static Registry& instance() {
            static Registry r;
            return r;
        }
        std::vector<Entry> entries;
    };

    // Expose entries to Runner without exposing Registry type in headers
    std::vector<Entry>& get_internal_entries() {
        return Registry::instance().entries;
    }

    namespace internal {
        Registrar::Registrar(const char* name, BenchFn fn) {
            Registry::instance().entries.push_back({name, fn});
        }

        Registrar& Registrar::Iterations(size_t n) {
            Registry::instance().entries.back().iterations = n;
            return *this;
        }

        Registrar& Registrar::Warmup(size_t n) {
            Registry::instance().entries.back().warmup = n;
            return *this;
        }
    }
}