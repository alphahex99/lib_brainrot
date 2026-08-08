cmake_minimum_required(VERSION 3.23)
project(lib_brainrot)

add_executable(brainrot)

target_compile_options(brainrot PRIVATE
    -g -O0
)

target_include_directories(brainrot PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_sources(brainrot PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/translators/my_pformat.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/translators/translate_gen_x.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/wrappers/wrap_streambuf.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

function(wrap_symbols arg_target)
    foreach(arg_symbol IN LISTS ARGN)
        target_compile_options(${arg_target} PRIVATE
            # Disable optimizations that can replace calls to our wrapped functions,
            # for example: 'printf(str)' without varargs gets replaced by 'puts(str)'
            -fno-builtin-${arg_symbol}
        )

        target_link_options(${arg_target} PRIVATE
            -Wl,--wrap=${arg_symbol}
        )

        target_sources(${arg_target} PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/wrappers/wrap_${arg_symbol}.cpp
        )
    endforeach()
endfunction()

wrap_symbols(brainrot
    $<$<BOOL:${MINGW}>:__mingw_pformat>
    # pformat
)
