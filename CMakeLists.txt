cmake_minimum_required(VERSION 3.10)
project(SuperTicTacToe)

set(SRC_DIR src)
set(INCLUDE_DIR headers)

file(GLOB SRC_FILES "${SRC_DIR}/*.c")
file(GLOB headers_FILES "${INCLUDE_DIR}/*.h")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${INCLUDE_DIR})
find_package(WebP QUIET)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(SuperTicTacToe ${SRC_FILES})
target_link_libraries(SuperTicTacToe PRIVATE SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)

target_compile_options(SuperTicTacToe PRIVATE -ggdb3 -O2 -std=c99 -Wall)

include(InstallRequiredSystemLibraries)

install(TARGETS SuperTicTacToe DESTINATION .)
install(DIRECTORY assets/ DESTINATION assets)

if(WIN32)
    install(FILES $<TARGET_FILE:SDL2::SDL2> $<TARGET_FILE:SDL2_image::SDL2_image> $<TARGET_FILE:SDL2_ttf::SDL2_ttf> DESTINATION .)
endif()

set(CPACK_GENERATOR "ZIP")
include(CPack)
