cmake_minimum_required(VERSION 3.20)
project(nitmod_companion C)

add_executable(nitmod-companion src/main.c)
target_compile_features(nitmod-companion PRIVATE c_std_99)

if(WIN32)
    target_link_libraries(nitmod-companion PRIVATE ws2_32)
endif()
