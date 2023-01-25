#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

// Window class
// -----------------------------------------------------------
class Window
{
private:
  GLFWwindow* m_window;
  static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:
  Window(uint16_t width, 
    uint16_t      height, 
    const char*   title, 
    GLFWmonitor*  monitor = nullptr, 
    GLFWwindow*   share   = nullptr);
  
  ~Window()                 { glfwDestroyWindow(m_window);              }

  bool shouldClose() const  { return glfwWindowShouldClose(m_window);   }
  void close()              { glfwSetWindowShouldClose(m_window, true); }
  void swapBuffers()        { glfwSwapBuffers(m_window);                }
  void use() const          { glfwMakeContextCurrent(m_window);         }
  int getKey(int key) const { return glfwGetKey(m_window, key);         }
  GLFWwindow* getWindowObj() const { return m_window; }

  void render(float r, float g, float b, uint32_t mask = GL_COLOR_BUFFER_BIT);
};
// -----------------------------------------------------------

#endif