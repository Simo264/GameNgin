#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <iostream>

#include "logger.h"
#include "window.h"
#include "globals.h"

#include "shader.h"

#include "geometry/triangle.h"
#include "geometry/rectangle.h"


// Window config
#define WINDOW_WIDTH  720
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE  "Breakout"

static void process_input(Window* window);

int main()
{
  if(!glfwInit())
  {
    logger::error("Error on init GLFW");
    glfwTerminate();
    return -1;
  }
  logger::trace("GLFW initialized successfully");
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

  // glew: init
  // ----------------
  if(glewInit() != GLEW_OK)
  {
    logger::error("Error on init GLEW");
    glfwTerminate();
    return -1;
  }
  logger::trace("GLEW initialized successfully");
  

  // OpenGL configuration
  // --------------------
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

  Shader shader("../shaders/vertex.shader", "../shaders/fragment.shader");
  logger::trace("Shaders loaded successfully");

  //Triangle triangle;
  Rectangle rectangle;

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
    rectangle.scale(0.5, 0.5f);
    rectangle.translate(sin(currentFrame), 0);


    // render
    // ------
    window.render(0.7f, 0.1f, 0.2);
    //triangle.render(&shader);
    rectangle.render(&shader);

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

