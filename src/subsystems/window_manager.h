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

    vec2ui m_size;

    void IMGUIinit();   
    void IMGUIfree(); 

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

  public:
    WindowManager() = default;
    ~WindowManager() = default;

    void init();
    void free();        

    void IMGUIrender(); 
      
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