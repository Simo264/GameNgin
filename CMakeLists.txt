cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(GameNgin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(COMMON_CXX_FLAGS "${COMMON_CXX_FLAGS} -Wall -pedantic -Wextra -m64 -mavx2 -mfma -ffast-math")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

file(GLOB_RECURSE srcfiles "src/engine/**.cpp" "src/engine/**.h")
add_executable(GameNgin ${srcfiles})

add_subdirectory(externals/glad)
add_subdirectory(externals/glfw)
add_subdirectory(externals/glm)
add_subdirectory(externals/imgui)

include_directories(externals/glad/include)
include_directories(externals/glfw/include)
include_directories(externals/glm)
include_directories(externals/imgui)
include_directories(src/)

target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} imgui)
