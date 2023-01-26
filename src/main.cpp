#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <chrono>
#include <thread>
#include <map>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "../include/logger.h"
#include "../include/window.h"
#include "../include/globals.h"
#include "../include/shader.h"

#include "../include/triangle.h"
#include "../include/rectangle.h"


// Window config
#define WINDOW_WIDTH  720
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE  "GameNgin"

// deltaTime variables
// -------------------
float deltaTime = 0.0f;
float lastFrame = 0.0f;

static void input_callback(Window* window);

int main()
{
  // glfw: init
  // ----------------
  if(!glfwInit())
  {
    LOG_ERROR("Error on init GLFW");
    glfwTerminate();
    return -1;
  }
  LOG_TRACE("GLFW initialized successfully");
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  
  Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

  // glew: init
  // ----------------
  if(glewInit() != GLEW_OK)
  {
    LOG_ERROR("Error on init GLEW");
    glfwTerminate();
    return -1;
  }
  LOG_TRACE("GLEW initialized successfully");

  Shader shader("../shaders/vertex.shader", "../shaders/fragment.shader");
  LOG_TRACE("Shaders loaded successfully");

  Rectangle rect(glm::vec2{ 50,50 }, glm::vec2{ 100,100 });
  Rectangle rect2(glm::vec2{ 50,50 }, glm::vec2{ 300,200 });

  globals::world_objects.insert({rect.id,   &rect});
  globals::world_objects.insert({rect2.id,  &rect2});


  while (!window.shouldClose())
  {
    // calculate delta time
    // --------------------
    const double currentFrame = static_cast<double>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    globals::world_time = currentFrame;

    //LOG_MESSAGE(std::to_string(deltaTime) + "  " + std::to_string(100 * deltaTime));

    // input
    // ------
    window.processInput(input_callback);
    glfwPollEvents();

    // update state
    // ------



    // render
    // ------
    window.render(100.f, 255.f, 0.f);
    rect.render(&shader);
    rect2.render(&shader);



    // Swap front and back buffers 
    window.swapBuffers();
  }

  glfwTerminate();

  return 0;
}

void input_callback(Window* window)
{
  Rectangle* rect = dynamic_cast<Rectangle*>(globals::world_objects.at(0));

  if (window->getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    window->close();
    return;
  }
  
  if(window->getKey(GLFW_KEY_A) == GLFW_PRESS)
  {
    rect->position.x -= 2 * (deltaTime*100) ;
    return;
  }

  if(window->getKey(GLFW_KEY_D) == GLFW_PRESS)
  {
    rect->position.x += 2 * (deltaTime*100);
    return;
  }

  if(window->getKey(GLFW_KEY_W) == GLFW_PRESS)
  {
    rect->position.y -= 2 * (deltaTime*100) ;
    return;
  }

  if(window->getKey(GLFW_KEY_S) == GLFW_PRESS)
  {
    rect->position.y += 2 * (deltaTime*100);
    return;
  }


}

