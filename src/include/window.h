#ifndef WINDOW_H
#define WINDOW_H

// Window class
// -----------------------------------------------------------
namespace GameNgin
{
  class Window
  {
  private:
    GLFWwindow* m_window;

  public:
    /* Constructors */
    Window(vec2ui dimension, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
    
    /* Destructor */
    ~Window() { glfwDestroyWindow(m_window); }

    GLFWwindow* getWindow() const { return m_window; }

    bool  shouldClose()   const { return glfwWindowShouldClose(m_window);   }
    void  close()               { glfwSetWindowShouldClose(m_window, true); }
    void  swapBuffers()         { glfwSwapBuffers(m_window);                }
    int   getKey(int key) const { return glfwGetKey(m_window, key);         }

    void setWindowSize(int width, int height);

    void setVsync(int interval = 1) { glfwSwapInterval(interval); }
  };
}
// -----------------------------------------------------------

#endif