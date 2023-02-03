#include "include/core_minimal.h"

#include "include/window_manager.h"
#include "include/logger.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace gn
{
  GLFWwindow* WindowManager::m_window = nullptr;

  void WindowManager::init()
  {
    // glfw: init
    // ----------------
    if(!glfwInit())
    {
      LOG_ERROR("Init GLFW... Failed!");
      exit(EXIT_FAILURE);
    }
    LOG_TRACE("Init GLFW... OK!");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // create window
    // ----------------
    m_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGH, WINDOW_TITLE, nullptr, nullptr);
    if(!m_window)
    {
      LOG_ERROR("Creating Window... Failed!");
      glfwTerminate();
      exit(EXIT_FAILURE);
    }
    LOG_TRACE("Creating Window... OK!");

    glfwMakeContextCurrent(m_window);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGH);
    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height){
      glViewport(0, 0, width, height);
    });

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      LOG_ERROR("Init GLAD... Failed!");
      glfwTerminate();
      exit(EXIT_FAILURE);
    }
    LOG_TRACE("Init GLAD... Failed!");

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
      ImGui::End();
    }

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

