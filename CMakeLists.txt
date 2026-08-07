cmake_minimum_required(VERSION 3.23)
project(Obfus)

# set_property(TARGET obfus PROPERTY CXX_STANDARD 20)

add_executable(obfus)

# TODO: C++ ?
function(wrap_symbol arg_target arg_symbol)

    target_compile_options(${arg_target} PRIVATE
        # -fno-builtin-${arg_symbol}
        -include ${CMAKE_CURRENT_SOURCE_DIR}/wrappers/wrap_${arg_symbol}.h
    )

    target_link_options(${arg_target} PRIVATE
        -Wl,--wrap=${arg_symbol}
    )

    target_sources(${arg_target} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/wrappers/wrap_${arg_symbol}.c
    )
endfunction()

wrap_symbol(obfus
    printf
)

target_compile_options(obfus PRIVATE
    -g -O0
)

target_sources(obfus PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)
