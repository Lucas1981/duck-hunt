cmake_minimum_required(VERSION 3.10)

# Project name
project(DuckHunt)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Compiler warning flags
set(WARN_FLAGS
    -Wall
    -Wextra
    -Werror
    -Wshadow
    -Wconversion
    -pedantic
    -pedantic-errors
    -Wformat=2
    -Wundef
    -Wredundant-decls
    -Wmissing-declarations
    -Wmissing-include-dirs
    -Wswitch-enum
)

# Apply warning flags
add_compile_options(${WARN_FLAGS})

# Enable IWYU
set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "include-what-you-use;-Xiwyu;--mapping_file=../mappings.imp")

# Find SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Add the executable
add_executable(DuckHunt 
    src/main.cpp 
    src/game.cpp
    src/state.cpp
    src/play.cpp
    src/input.cpp
    src/graphics.cpp
    src/clock.cpp
    # src/sound.cpp
    src/frames.cpp
    src/animator.cpp
    src/player.cpp
    src/duck.cpp
    src/screens.cpp
    # src/collision.cpp
)

# Link SFML libraries
target_link_libraries(DuckHunt sfml-system sfml-window sfml-graphics)