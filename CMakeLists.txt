cmake_minimum_required(VERSION 3.25)
project(cnes C)

set(CMAKE_C_STANDARD 99)

add_compile_options(-Werror)

add_executable(${PROJECT_NAME}  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
                                ${CMAKE_CURRENT_SOURCE_DIR}/src/core/nes.c
                                ${CMAKE_CURRENT_SOURCE_DIR}/src/core/cpu.c
                                ${CMAKE_CURRENT_SOURCE_DIR}/src/core/mmu.c)
