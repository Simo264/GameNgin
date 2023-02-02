#ifndef WINDOW_H
#define WINDOW_H

// WindowManager class
// -----------------------------------------------------------
class WindowManager
{
private:
  static GLFWwindow* m_window;

public:
  /* Constructors */
  WindowManager() = default;
  
  /* Destructor */
  ~WindowManager() = default;

  void startUp();

  void shutDown();

  static GLFWwindow* get() { return m_window; }

  bool  shouldClose()   const { return glfwWindowShouldClose(m_window);   }
  void  close()               { glfwSetWindowShouldClose(m_window, true); }
  void  swapBuffers()         { glfwSwapBuffers(m_window);                }
  int   getKey(int key) const { return glfwGetKey(m_window, key);         }

  void setVsync(int interval = 1) { glfwSwapInterval(interval); }

  void setWindowSize(int width, int height); // window.cpp
};
// -----------------------------------------------------------

#endif