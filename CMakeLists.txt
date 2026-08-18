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
    ${CMAKE_CURRENT_SOURCE_DIR}/translators/translate_gen_x.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/translators/translate_owo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/translators/translate.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

function(target_wrap_sources arg_target arg_prefix)
    foreach(arg_symbol IN LISTS ARGN)
        if(arg_prefix)
            target_compile_options(${arg_target} PRIVATE
                # Avoids duplicating source files and needing callbacks to __real_wrap_FN,
                # for example: '__mingw_pformat' vs 'pformat', see commit hash 'aa26ddd7'
                -D__real_${arg_symbol}=__real_${arg_prefix}${arg_symbol}
                -D__wrap_${arg_symbol}=__wrap_${arg_prefix}${arg_symbol}
            )
        endif()

        target_compile_options(${arg_target} PRIVATE
            # Disable optimizations that can replace calls to our wrapped functions,
            # for example: 'printf(str)' without varargs gets replaced by 'puts(str)'
            -fno-builtin-${arg_prefix}${arg_symbol}
        )

        target_link_options(${arg_target} PRIVATE
            -Wl,--wrap=${arg_prefix}${arg_symbol}
        )

        target_sources(${arg_target} PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/wrappers/wrap_${arg_symbol}.cpp
        )
    endforeach()
endfunction()

if(MINGW)
    set(MINGW_PREFIX "__mingw_")
else()
    set(MINGW_PREFIX "")
endif()

target_wrap_sources(brainrot ${MINGW_PREFIX}
    pformat
)
