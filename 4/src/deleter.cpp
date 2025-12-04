#include "deleter.hpp"

namespace figure {

std::atomic<size_t> DeletionStats::total_deletions_{0};
std::atomic<size_t> DeletionStats::point_deletions_{0};

}
