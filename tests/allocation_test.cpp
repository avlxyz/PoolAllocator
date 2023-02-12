#include <vector>
#include <algorithm>
#include "stl_pool_allocator.h"

uint8_t pool[1024];
auto alloc = LibAlloc::PoolAllocator::init(pool, sizeof(pool), 100);

int main() {
    const uint32_t size = 25;
    std::vector<uint32_t, LibAlloc::StlPoolAllocator<uint32_t>> vec1(size);
    std::vector<uint32_t, LibAlloc::StlPoolAllocator<uint32_t>> vec2(size);
    for(uint32_t i = 0; i < size; ++i) {
        vec1[i] = i;
        vec2[i] = i;
    }
    return vec1 == vec2 ? 0 : -1;
}
