#include "window.h"

#include <GLFW/glfw3.h>
#include <cstdlib>

#include <string>
#include <fstream>
#include <sstream>

#include "logger.h"
#include "globals.h"

Window::Window(
  uint16_t      width, 
  uint16_t      height, 
  const char*   title, 
  GLFWmonitor*  monitor, 
  GLFWwindow*   share)
{
  m_window = glfwCreateWindow(width, height, title, monitor, share);
  if(!m_window)
  {
    logger::error(__FILE__, __LINE__, "Error on create window");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(m_window);
  glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
  glViewport(0, 0, width, height);
  
  globals::window_width = width;
  globals::window_height= height;
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  // make sure the viewport matches the new window dimensions; note that width and 
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
  globals::window_width = width;
  globals::window_height= height;
}

void Window::render(float r, float g, float b, uint32_t mask)
{
  glClearColor(r/255.f, g/255.f, b/255.f, 1.f);
  glClear(mask);
}

