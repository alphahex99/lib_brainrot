cmake_minimum_required(VERSION 3.23)
project(Obfus)

add_executable(obfus)

# set_property(TARGET obfus PROPERTY CXX_STANDARD 20)

target_compile_options(obfus PRIVATE
    -g -O0
)

target_sources(obfus
    PRIVATE
    main.cpp
)
