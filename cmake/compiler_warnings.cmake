# Дополнительные предупреждения
add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wold-style-cast
    -Wcast-qual
    -Wcast-align
    $<$<COMPILE_LANGUAGE:CXX>:-Wzero-as-null-pointer-constant>
    -Wundef
    -Wshadow
    -Wduplicated-cond
    -Wduplicated-branches
    -Wlogical-op
    -Wshift-overflow=2
    -Wconversion
    -Wsign-conversion
    $<$<COMPILE_LANGUAGE:CXX>:-Wsign-promo>
    -Wfloat-equal
    -Wdouble-promotion
)
