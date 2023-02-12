#pragma once

#include <cstdint>

namespace LibAlloc {

//! Блочный аллокатор
class PoolAllocator {
public:
    //! Тип указатель на callback-функцию
    using Callback = void (*)();

    static PoolAllocator& init(
        void* pool,
        size_t poolSize,
        size_t blockSize,
        Callback enterCritical = []() {},
        Callback exitCritical = []() {});
    static PoolAllocator& instance();

    void* allocate();
    void deallocate(void* block);

private:
    PoolAllocator(void* pool, size_t poolSize, size_t blockSize, Callback enterCritical, Callback exitCritical);

    //! Вспомогательная структура, в начале каждого свободного блока храним указатель на след. свободный блок
    struct Block {
        Block* next; //!< Следующий свободный блок
    };

    char* const _pool; //!< Статически выделенная память
    const size_t _blockSize; //!< Размер аллоцируемого блока
    const size_t _blocksCount; //!< Максимальное кол-во блоков
    const Callback _enterCritical; //!< Старт критической секции, зависит от API пользовательской системы
    const Callback _exitCritical; //!< Окончание критической секции, зависит от API пользовательской системы
    Block* _head; //!< Свободный блок
};

} // namespace Liballoc
