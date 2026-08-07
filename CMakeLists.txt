cmake_minimum_required(VERSION 3.23)
project(lib_brainrot)

add_executable(brainrot)

target_compile_options(brainrot PRIVATE
    -g -O0
)

target_include_directories(brainrot PRIVATE
    translators/
)

target_sources(brainrot PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/translators/translate_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

function(wrap_symbol arg_target arg_symbol)

    target_compile_options(${arg_target} PRIVATE
        -fno-builtin-${arg_symbol}
    )

    target_link_options(${arg_target} PRIVATE
        -Wl,--wrap=${arg_symbol}
    )

    target_sources(${arg_target} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/wrappers/wrap_${arg_symbol}.cpp
    )
endfunction()

wrap_symbol(brainrot
    printf
)
