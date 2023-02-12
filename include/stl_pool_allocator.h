#pragma once

#include <cstdint>

namespace LibAlloc {

//! Адаптер нашего аллокатора для Stl контейнеров
template<class T>
class StlPoolAllocator {
public:
    using value_type = T;

    T* allocate(size_t n);
    void deallocate(T* first, size_t n);
};
} // namespace LibAlloc

#include "stl_pool_allocator.tcc"
