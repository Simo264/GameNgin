#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <chrono>
#include <thread>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "logger.h"
#include "window.h"
#include "globals.h"
#include "shader.h"

#include "geometry/triangle.h"
#include "geometry/rectangle.h"


// Window config
#define WINDOW_WIDTH  720
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE  "GameNgin"

static void process_input(Window* window);

int main()
{
  // glfw: init
  // ----------------
  if(!glfwInit())
  {
    logger::error(__FILE__, __LINE__,"Error on init GLFW");
    glfwTerminate();
    return -1;
  }
  logger::trace(__FILE__, __LINE__,"GLFW initialized successfully");
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

  // glew: init
  // ----------------
  if(glewInit() != GLEW_OK)
  {
    logger::error(__FILE__, __LINE__, "Error on init GLEW");
    glfwTerminate();
    return -1;
  }
  logger::trace(__FILE__, __LINE__, "GLEW initialized successfully");

  Shader shader("../shaders/vertex.shader", "../shaders/fragment.shader");
  logger::trace(__FILE__, __LINE__,"Shaders loaded successfully");

  Rectangle rect(glm::vec2{ 50,50 }, glm::vec2{ 100,100 });

  // deltaTime variables
  // -------------------
  float deltaTime = 0.0f;
  float lastFrame = 0.0f;
  while (!window.shouldClose())
  {
    // calculate delta time
    // --------------------
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    globals::world_time = currentFrame;

    // input
    // ------
    process_input(&window);
    glfwPollEvents();

    // update state
    // ------
    rect.position.x += 2;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
     
    // render
    // ------
    window.render(100.f, 255.f, 0.f);
    rect.render(&shader);

    // Swap front and back buffers 
    window.swapBuffers();
  }

  glfwTerminate();

  return 0;
}

void process_input(Window* window)
{
  if (window->getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
    window->close();
}

