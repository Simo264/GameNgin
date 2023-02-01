cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(GameNgin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(COMMON_CXX_FLAGS "${COMMON_CXX_FLAGS} -Wall -pedantic -Wextra -m64 -mavx2 -mfma -ffast-math")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/bin/")

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

file(GLOB_RECURSE Sources "src/**.cpp" "src/**.h" "externals/glad/src/glad.c" "externals/imgui/*.cpp")
add_executable(GameNgin ${Sources})

add_subdirectory(externals/glfw)
add_subdirectory(externals/glm)

include_directories(externals/glad/include)
include_directories(externals/glfw/include)
include_directories(externals/glm)
include_directories(externals/imgui)

target_link_libraries(GameNgin glfw ${GLFW_LIBRARIES})

# add_library(GameNgin STATIC ${Sources})