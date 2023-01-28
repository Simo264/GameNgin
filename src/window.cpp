#include "../include/core_minimal.h"

#include "../include/window.h"
#include "../include/logger.h"
#include "../include/globals.h"


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
    LOG_ERROR("Error on create window");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(m_window);
  glViewport(0, 0, width, height);

  globals::window_width = width;
  globals::window_height = height;
  
  glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
    globals::window_width = width;
    globals::window_height = height;
  });
}

void Window::render(float r, float g, float b, uint32_t mask)
{
  glClearColor(r/255.f, g/255.f, b/255.f, 1.f);
  glClear(mask);
}

