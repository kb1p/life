cmake_minimum_required(VERSION 3.1)

project(life)

set(CMAKE_CXX_STANDARD 11)
#add_compile_options(-Wall -Werror -Wl,--no-undefined)

find_package(SDL2 REQUIRED)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")
include_directories("."
                    ${SDL2_INCLUDE_DIRS}
                    "${SDL2_INCLUDE_DIRS}/SDL2")

file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_executable(life ${sources})

target_link_libraries(life ${SDL2_LIBRARIES})

install(TARGETS life DESTINATION "bin")
