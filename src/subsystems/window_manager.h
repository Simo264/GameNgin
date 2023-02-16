#ifndef WINDOW_H
#define WINDOW_H

#include "imgui_manager.h"

namespace gn
{
  // WindowManager class
  // -----------------------------------------------------------
  class WindowManager
  {
  private:
    static GLFWwindow* m_window;

    ImguiManager m_imguiManager;

    vec2ui m_size;

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

  public:
    WindowManager() = default;
    ~WindowManager() = default;

    void init();
    void renderGUI();
    void free();        

    static GLFWwindow* get()    { return m_window;                          }

    int   getKey(int key) const { return glfwGetKey(m_window, key);         }
    bool  shouldClose()   const { return glfwWindowShouldClose(m_window);   }
    void  close()               { glfwSetWindowShouldClose(m_window, true); }
    void  swapBuffers()         { glfwSwapBuffers(m_window);                }
    void  setVsync(int interval = 1) { glfwSwapInterval(interval);                   }
    
    const vec2ui getWindowSize() const { return m_size; }
    void  setWindowSize(vec2ui size);
  };
  // -----------------------------------------------------------

} 
#endif