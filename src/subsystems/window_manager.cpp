#include "../core_minimal.h"
#include "window_manager.h"
#include "../logger.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace gn
{
  GLFWwindow* WindowManager::m_window = nullptr;

  bool WindowManager::init()
  {
    // glfw: init
    // ----------------
    if(!glfwInit())
      return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // create window
    // ----------------
    m_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGH, WINDOW_TITLE, nullptr, nullptr);
    if(!m_window)
      return false;

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);


    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
      return false;
    
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGH);
    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height){
      glViewport(0, 0, width, height);
    });

    return true;
  }

  void WindowManager::IMGUIinit()
  {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 450");
  }


  void WindowManager::IMGUIrender()
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if(ImGui::Begin("Hello, world!"))
    {
      
    }
    ImGui::End();

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }


  void WindowManager::free()
  {
    glfwDestroyWindow(m_window);
    glfwTerminate();
  }

  void WindowManager::IMGUIfree()
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  }





  const vec2ui WindowManager::getWindowSize() const
  {
    int w, h;
    glfwGetFramebufferSize(m_window, &w, &h);
    return vec2ui(w, h);
  }

}

