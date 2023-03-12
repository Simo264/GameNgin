#include "engine/core/core.h"

#include "window_manager.h"
#include "imgui_manager.h"

#include "engine/world.h"
#include "engine/box.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "engine/core/IO/logger.h"

extern gn::World gWorld;

namespace gn
{
  void WindowManager::init()
  {
    // glfw: init
    // ----------------
    if(!glfwInit())
    {
      LOG_ERROR("Error on init GLFW");  
      exit(EXIT_FAILURE); 
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // create window
    // ----------------
    m_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGTH, PROJECT_NAME, nullptr, nullptr);
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      LOG_ERROR("Error on init GLAD");
      exit(EXIT_FAILURE); 
    }
    
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGTH);
    setWindowSize({WINDOW_WIDTH, WINDOW_HEIGTH});

    ImguiManager::getInstance().init();
  }

  void WindowManager::renderGUI()
  {
    ImguiManager::getInstance().render();
  }

  void WindowManager::free()
  {
    ImguiManager::getInstance().free();
    glfwDestroyWindow(m_window);
    glfwTerminate();
  }

  void WindowManager::setWindowSize(vec2ui size) 
  { 
    m_size = size;
    glfwSetWindowSize(m_window, size.x, size.y); 

    // origin to the center of the screen
    m_orthographic = ortho(
      -(float)m_size.x / 2, // left
      +(float)m_size.x / 2, // right
      -(float)m_size.y / 2, // bottom
      +(float)m_size.y / 2, // top 
      -1.0f, 1.0f);
  }

}

