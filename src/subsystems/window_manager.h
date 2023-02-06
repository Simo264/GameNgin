#ifndef WINDOW_H
#define WINDOW_H


namespace gn
{
  // WindowManager class
  // -----------------------------------------------------------
  class WindowManager
  {
  private:
    static GLFWwindow* m_window;

  public:
    WindowManager() = default;
    ~WindowManager() = default;

    bool init();        
    void IMGUIinit();   

    void IMGUIrender(); 

    void free();        
    void IMGUIfree();   

    static GLFWwindow* get()    { return m_window;                          }
    int   getKey(int key) const { return glfwGetKey(m_window, key);         }
    bool  shouldClose()   const { return glfwWindowShouldClose(m_window);   }
    void  close()               { glfwSetWindowShouldClose(m_window, true); }
    void  swapBuffers()         { glfwSwapBuffers(m_window);                }
    void setVsync(int interval = 1) { glfwSwapInterval(interval);                   }
    void setWindowSize(vec2ui size) { glfwSetWindowSize(m_window, size.x, size.y);  }
    
    const vec2ui getWindowSize() const; 
  };
  // -----------------------------------------------------------

} 
#endif