cmake_minimum_required(VERSION 3.20)
project(PoolAllocator)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
include(compiler_warnings)

# Переменные сборки
string(TOLOWER ${PROJECT_NAME} TARGET_NAME)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Перечисление исходников
set(TARGET_SOURCE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
set(TARGET_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
foreach(SOURCE_DIR ${TARGET_SOURCE_DIRS} ${TARGET_INCLUDE_DIRS})
    file(GLOB SOURCES
        ${SOURCE_DIR}/*.cpp
        ${SOURCE_DIR}/*.h
        ${SOURCE_DIR}/*.tcc
    )
    list(APPEND TARGET_SOURCES ${SOURCES})
endforeach()

# Правило сборки
add_library(${TARGET_NAME} STATIC ${TARGET_SOURCES})
target_include_directories(${TARGET_NAME} PUBLIC ${TARGET_INCLUDE_DIRS})

#Тесты
enable_testing()
file(GLOB TESTS
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp
)
foreach(TEST_CPP ${TESTS})
    get_filename_component(TEST_NAME ${TEST_CPP} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_CPP})
    target_link_libraries(${TEST_NAME} PRIVATE ${TARGET_NAME})
    add_test(${TEST_NAME} ${TEST_NAME})
endforeach()

