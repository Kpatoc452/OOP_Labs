#pragma once

#include <memory_resource>
#include <map>
#include <cstddef>

namespace memory {

class FixedBlockMemoryResource : public std::pmr::memory_resource {
    void* buffer_;
    size_t buffer_size_;
    size_t offset_;
    std::map<void*, size_t> allocations_;

protected:
    void* do_allocate(size_t bytes, size_t alignment) override;
    void do_deallocate(void* p, size_t bytes, size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

public:
    FixedBlockMemoryResource(size_t size);
    ~FixedBlockMemoryResource();

    size_t GetAllocatedCount() const noexcept;
    size_t GetUsedMemory() const noexcept;
    size_t GetTotalMemory() const noexcept;
};

}
