#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <iostream>

#include "logger.h"
#include "window.h"

#include "shader.h"
#include "vertex_buffer.h"
#include "vertex_array.h"


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

  float positions[] = {
    -1, -1,
    +1, -1,
     0, +1
  };
  u_char colors[] = {
    255, 255, 255,
    255, 255, 255,
    255, 255, 255
  };


  VertexArray vaOBJ;

  VertexBuffer vbOBJ(sizeof(positions) + sizeof(colors));
  vbOBJ.namedBufferSubData(0, sizeof(positions), positions);
  vbOBJ.namedBufferSubData(sizeof(positions), sizeof(colors), colors);

  vaOBJ.enableAttribute(0);
  vaOBJ.enableAttribute(1);
  vaOBJ.setAttribFormat(0, 2, GL_FLOAT, false, 0);
  vaOBJ.setAttribFormat(1, 3, GL_UNSIGNED_BYTE, true, sizeof(positions));
  vaOBJ.setAttribBinding(0, 0);
  vaOBJ.setAttribBinding(1, 1);
  vaOBJ.bindVertexBuffer(0, &vbOBJ, 0, sizeof(float)*2);
  vaOBJ.bindVertexBuffer(1, &vbOBJ, 0, sizeof(u_char)*3);


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

    // input
    // ------
    process_input(&window);
    glfwPollEvents();

    // update state
    // ------

    
    // render
    // ------
    window.render(0.7f, 0.1f, 0.2);
    shader.use();
    vaOBJ.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);

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

