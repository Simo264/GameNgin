cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(GameNgin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)


if (WIN32)
  set(PLATFORM "Windows")
endif (WIN32)

if(UNIX AND NOT APPLE)
  set(PLATFORM "Linux")
endif()


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(COMMON_CXX_FLAGS "${COMMON_CXX_FLAGS} -g3 -O0 -Wall -pedantic -Wextra -m64 -mavx2 -mfma -ffast-math")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(COMMON_CXX_FLAGS "${COMMON_CXX_FLAGS} -Wall -pedantic -Wextra -m64 -mavx2 -mfma -ffast-math")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set(COMMON_CXX_FLAGS "${COMMON_CXX_FLAGS} /std:c++17 /W4 /arch:AVX2 /fp:fast /MP /DNOMINMAX")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/")

find_package(OpenGL REQUIRED)

add_subdirectory(externals/cmake/glad)
add_subdirectory(externals/cmake/glfw)
add_subdirectory(externals/cmake/glm)

include_directories(src/)
include_directories(externals/includes)

file(GLOB_RECURSE GameNginSources "Source/**.cpp" "Source/**.h" "Source/**.hpp")

add_library(FractalEngine STATIC ${GameNginSources})

if(PLATFORM STREQUAL "Linux")
target_link_libraries(GameNgin -lGL) 
target_link_libraries(GameNgin -lglfw)
target_link_libraries(GameNgin -lglad)
target_link_libraries(GameNgin -lassimp)
target_link_libraries(GameNgin -ltinyxml2)
endif()

if(PLATFORM STREQUAL "Windows")
target_link_libraries(GameNgin opengl32)
target_link_libraries(GameNgin glfw)
target_link_libraries(GameNgin glad)
target_link_libraries(GameNgin tinyxml2)
target_link_libraries(GameNgin assimp)
endif()