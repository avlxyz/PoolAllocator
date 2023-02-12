#include "pool_allocator.h"

uint8_t pool[1024];
auto alloc = LibAlloc::PoolAllocator::init(pool, sizeof(pool), 100);

int main() {
    void* block;
    for(uint32_t i = 0; i <= 10; ++i) {
        block = LibAlloc::PoolAllocator::instance().allocate();
    }
    return block == nullptr ? 0 : -1;
}
