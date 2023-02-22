#include "../core_minimal.h"

#include "window_manager.h"

#include "../world.h"
#include "../box.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

extern gn::World gWorld;

namespace gn
{
  GLFWwindow* WindowManager::m_window = nullptr;

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
    m_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGTH, WINDOW_TITLE, nullptr, nullptr);
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
    // glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
    // glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
    
    setWindowSize(vec2ui(WINDOW_WIDTH, WINDOW_HEIGTH));
   
    m_imguiManager.init(this);
  }

  void WindowManager::renderGUI()
  {
    m_imguiManager.render();
  }

  void WindowManager::free()
  {
    m_imguiManager.free();    
    glfwDestroyWindow(m_window);
    glfwTerminate();
  }

  
  void WindowManager::setWindowSize(vec2ui size) 
  { 
    m_size = size;
    glfwSetWindowSize(m_window, size.x, size.y); 
  }

  void WindowManager::framebufferSizeCallback(GLFWwindow* window, int width, int height)
  {
    glViewport(0, 0, width, height);
  }
  
  void WindowManager::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
  {
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
    {
      double xpos, ypos;
      glfwGetCursorPos(window, &xpos, &ypos);
      std::cout << "Cursor Position at (" << xpos << " : " << ypos << ")\n";
    }
  }

}

