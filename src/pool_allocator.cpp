#include <exception>
#include "pool_allocator.h"

namespace LibAlloc {

/*!
 * \brief Инициализация аллокатора
 * \param pool Статически выделенная память
 * \param poolSize Размер пула
 * \param blockSize Размер аллоцируемого блока
 * \param enterCritical Старт критической секции
 * \param exitCritical Окончание критической секции
 */
PoolAllocator& PoolAllocator::init(void* pool,
                                   size_t poolSize,
                                   size_t blockSize,
                                   Callback enterCritical,
                                   Callback exitCritical) {
    static PoolAllocator instance {pool, poolSize, blockSize, enterCritical, exitCritical};
    return instance;
}

/*!
 * \brief Получить экземпляр аллокатора
 */
PoolAllocator& PoolAllocator::instance() {
    return init(
        nullptr, 0, 0, []() {}, []() {});
}

/*!
 * \brief Конструктор
 * \param pool Статически выделенная память
 * \param poolSize Размер пула
 * \param blockSize Размер аллоцируемого блока
 * \param enterCritical Старт критической секции
 * \param exitCritical Окончание критической секции
 */
PoolAllocator::PoolAllocator(void* pool,
                             size_t poolSize,
                             size_t blockSize,
                             Callback enterCritical,
                             Callback exitCritical):
    _pool {static_cast<char*>(pool)},
    _blockSize {blockSize < sizeof(Block) ? sizeof(Block) : blockSize},
    _blocksCount {poolSize / _blockSize},
    _enterCritical {enterCritical},
    _exitCritical {exitCritical},
    _head {static_cast<Block*>(pool)} {
    // Проверка, что конструктор вызван из init, не из instance
    if(!_pool) {
        std::terminate();
    }
    // Размечаем память
    auto blockAddr = _pool;
    const auto blockAddrLast = blockAddr + _blockSize * (_blocksCount - 1);
    while(blockAddr < blockAddrLast) {
        auto block = reinterpret_cast<Block*>(blockAddr);
        blockAddr += _blockSize;
        block->next = reinterpret_cast<Block*>(blockAddr);
    }
    reinterpret_cast<Block*>(blockAddr)->next = nullptr;
}

/*!
 * \brief Выделяем блок
 */
void* PoolAllocator::allocate() {
    _enterCritical();
    auto block = _head;
    if(_head)
        _head = _head->next;
    _exitCritical();
    return block;
}

/*!
 * \brief Освобождаем блок
 * \param block Указатель на начало блока
 */
void PoolAllocator::deallocate(void* block) {
    _enterCritical();
    static_cast<Block*>(block)->next = _head;
    _head = static_cast<Block*>(block);
    _exitCritical();
}

} // namespace LibAlloc
