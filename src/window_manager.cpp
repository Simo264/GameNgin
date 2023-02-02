#include "include/core_minimal.h"

#include "include/window_manager.h"
#include "include/logger.h"
#include "include/globals.h"

void WindowManager::startUp()
{
  // glfw: init
  // ----------------
  if(!glfwInit())
  {
    LOG_ERROR("Init GLFW... Failed!");
    exit(EXIT_FAILURE);
  }
  LOG_TRACE("Init GLFW... OK!");
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  // create window
  // ----------------
  m_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGH, WINDOW_TITLE, nullptr, nullptr);
  if(!m_window)
  {
    LOG_ERROR("Creating Window... Failed!");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  LOG_TRACE("Creating Window... OK!");

  glfwMakeContextCurrent(m_window);
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGH);
  glfwSwapInterval(1);

  glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height){
  glViewport(0, 0, width, height);
    Globals::window_dimension = vec2(width, height);
  });

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    LOG_ERROR("Init GLAD... Failed!");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  LOG_TRACE("Init GLAD... Failed!");

}

void WindowManager::shutDown()
{
  glfwDestroyWindow(m_window);
}

void WindowManager::setWindowSize(int width, int height)
{
  glfwSetWindowSize(m_window, width, height);
  Globals::window_dimension = vec2ui(width, height);
}


