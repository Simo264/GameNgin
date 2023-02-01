#ifndef CORE_MINIMAL_H
#define CORE_MINIMAL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <algorithm> 
#include <array>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>

#define VERSION "BETA 2.0"
#define EDITOR_VERSION "10.07.2021"
#define WINDOW_NAME "Game"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGH 720

using vec2    = glm::vec2;  // 2 floats
using vec2i   = glm::ivec2; // 2 integers
using vec2ui  = glm::uvec2; // 2 integers
using vec2d   = glm::dvec2; // 2 doubles
using vec2b   = glm::bvec2; // 2 bools

using vec3    = glm::vec3;  // 3 floats
using vec3i   = glm::ivec3; // 3 integers
using vec3ui  = glm::uvec3; // 3 integers
using vec3d   = glm::dvec3; // 3 doubles
using vec3b   = glm::bvec3; // 3 bools

using vec4    = glm::vec4;  // 4 floats
using vec4i   = glm::ivec4; // 4 integers
using vec4ui  = glm::uvec4; // 4 integers
using vec4d   = glm::dvec4; // 4 doubles
using vec4b   = glm::bvec4; // 4 bools

using mat2 = glm::mat2; // 2*2 matrix
using mat3 = glm::mat3; // 3*3 matrix
using mat4 = glm::mat4; // 4*4 matrix

using glm::radians;
using glm::ortho;
using glm::value_ptr;

#endif