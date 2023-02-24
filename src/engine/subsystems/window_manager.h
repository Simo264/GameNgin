#ifndef WINDOW_H
#define WINDOW_H

#include "engine/core/design_pattern/singleton.h"

#include "imgui_manager.h"

namespace gn
{
  // Singleton WindowManager class
  // -----------------------------------------------------------
  class WindowManager : public Singleton<WindowManager>
  {
  private:
    GLFWwindow* m_window = nullptr;
    
    ImguiManager m_imguiManager;

    vec2ui m_size;
    mat4   m_orthographic;

  public:
    GLFWwindow* getWindow() { return m_window; }

    void init();
    void renderGUI();
    void free();        

    int   getKey(int key) const { return glfwGetKey(m_window, key);         }
    bool  shouldClose()   const { return glfwWindowShouldClose(m_window);   }
    void  close()               { glfwSetWindowShouldClose(m_window, true); }
    void  swapBuffers()         { glfwSwapBuffers(m_window);                }
    void  setVsync(int interval = 1) { glfwSwapInterval(interval);          }
    
    const vec2ui& getWindowSize() const { return m_size; }
    void setWindowSize(vec2ui size);

    const mat4& getOrthographic() const { return m_orthographic; }
  };
  // -----------------------------------------------------------

} 
#endif