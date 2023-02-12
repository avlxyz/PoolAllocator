#include "pool_allocator.h"
#include "stl_pool_allocator.h"

namespace LibAlloc {

/*!
 * \brief Выделение памти
 * \param n Кол-во объектов
 *
 * \todo  Суммарный размер запрошенной памяти может превысить размер блока,
 *        если выделить несколько блоков, они могут расположиться в памяти НЕ последовательно
 */
template<class T>
T* StlPoolAllocator<T>::allocate(std::size_t /* n */) {
    return static_cast<T*>(PoolAllocator::instance().allocate());
}

/*!
 * \brief Освобождение памти
 * \param first Указатель на первый объект
 * \param n Кол-во объектов
 */
template<class T>
void StlPoolAllocator<T>::deallocate(T* first, std::size_t /* n */) {
    PoolAllocator::instance().deallocate(first);
}

} // namespace LibAlloc
