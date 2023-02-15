#include "../core_minimal.h"

#include "window_manager.h"

#include "../logger.h"
#include "../world.h"

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
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
    glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
    
    setWindowSize(vec2ui(WINDOW_WIDTH, WINDOW_HEIGTH));
    
    IMGUIinit();
  }

  void WindowManager::free()
  {
    IMGUIfree();
    glfwDestroyWindow(m_window);
    glfwTerminate();
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

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(300, m_size.y));
    if(ImGui::Begin("Left Panel", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
    {
      // const auto& worldObj = gWorld.getWorldObjects();
      // for(auto it = worldObj.begin(); it != worldObj.end(); ++it)
      //   ImGui::Text(it->second->toString().c_str());
    }
    ImGui::End();


    // ImGui::SetNextWindowPos(ImVec2(m_size.x - 300, 0));
    // ImGui::SetNextWindowSize(ImVec2(300, m_size.y));
    // if(ImGui::Begin("Right Panel", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
    // {

    // }
    // ImGui::End();

    // ImGui::SetNextWindowPos(ImVec2(300, m_size.y - 300));
    // ImGui::SetNextWindowSize(ImVec2(m_size.x - 600, 300));
    // if(ImGui::Begin("Bottom Panel", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
    // {

    // }
    // ImGui::End();

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  void WindowManager::IMGUIfree()
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
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

