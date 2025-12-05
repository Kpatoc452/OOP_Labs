#include "memory_resource.hpp"
#include <stdexcept>
#include <cstdlib>
#include <cstring>

namespace memory {

FixedBlockMemoryResource::FixedBlockMemoryResource(size_t size)
    : buffer_(nullptr), buffer_size_(size), offset_(0) {
    buffer_ = std::malloc(buffer_size_);
    if (!buffer_) {
        throw std::bad_alloc();
    }
    std::memset(buffer_, 0, buffer_size_);
}

FixedBlockMemoryResource::~FixedBlockMemoryResource() {
    if (buffer_) {
        std::free(buffer_);
        buffer_ = nullptr;
    }
}

void* FixedBlockMemoryResource::do_allocate(size_t bytes, size_t alignment) {
    size_t aligned_offset = (offset_ + alignment - 1) & ~(alignment - 1);

    if (aligned_offset + bytes > buffer_size_) {
        throw std::bad_alloc();
    }

    void* ptr = static_cast<char*>(buffer_) + aligned_offset;
    offset_ = aligned_offset + bytes;

    allocations_[ptr] = bytes;

    return ptr;
}

void FixedBlockMemoryResource::do_deallocate(void* p, size_t bytes, size_t alignment) {
    auto it = allocations_.find(p);
    if (it != allocations_.end()) {
        allocations_.erase(it);
    }
}

bool FixedBlockMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}

size_t FixedBlockMemoryResource::GetAllocatedCount() const noexcept {
    return allocations_.size();
}

size_t FixedBlockMemoryResource::GetUsedMemory() const noexcept {
    return offset_;
}

size_t FixedBlockMemoryResource::GetTotalMemory() const noexcept {
    return buffer_size_;
}

}
