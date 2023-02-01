#include "include/core_minimal.h"

#include "include/window.h"
#include "include/logger.h"
#include "include/globals.h"


namespace GameNgin
{
  Window::Window(vec2ui dimension, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
  {
    // glfw: init
    // ----------------
    if(!glfwInit())
    {
      LOG_ERROR("Error on init GLFW");
      glfwTerminate();
      exit(EXIT_FAILURE);
    }
    LOG_TRACE("GLFW initialized successfully");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    auto vMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);
		glfwWindowHint(GLFW_RED_BITS, vMode->redBits);
		glfwWindowHint(GLFW_BLUE_BITS, vMode->blueBits);
		glfwWindowHint(GLFW_GREEN_BITS, vMode->greenBits);
		glfwWindowHint(GLFW_REFRESH_RATE, vMode->refreshRate);

    m_window = glfwCreateWindow(dimension.x, dimension.y, title, monitor, share);
    assert(m_window);

    Globals::window_dimension = dimension;
    
    glfwMakeContextCurrent(m_window);
    glViewport(0, 0, dimension.x, dimension.y);
    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
      Globals::window_dimension = vec2(width, height);
    });
  }

  void Window::setWindowSize(int width, int height)
  {
    glfwSetWindowSize(m_window, width, height);
    Globals::window_dimension = vec2ui(width, height);
  }
}


