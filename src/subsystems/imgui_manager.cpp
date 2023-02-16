#include "../core_minimal.h"

#include "imgui_manager.h"
#include "window_manager.h"

#include "../world.h"
#include "../box.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

extern gn::World gWorld;

namespace gn
{
  void ImguiManager::init(WindowManager* windowManager)
  {
    m_windowManager = windowManager;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("fonts/OpenSans/OpenSans-SemiBold.ttf", 16);

    ImGui::GetStyle().WindowRounding = 5.0f;

    // Setup Dear ImGui style
    //ImGui::StyleColorsClassic();
    ImGui::StyleColorsLight();
    //ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_windowManager->get(), true);
    ImGui_ImplOpenGL3_Init("#version 450");
  }

  void ImguiManager::render()
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    worldoutliner_panel(
      vec2ui(m_windowManager->getWindowSize().x - 300, 0), 
      vec2ui(300, m_windowManager->getWindowSize().y / 2));

    if(m_selectedObject)
      details_panel(
        vec2ui(m_windowManager->getWindowSize().x - 300, m_windowManager->getWindowSize().y / 2), 
        vec2ui(300, m_windowManager->getWindowSize().y / 2), 
        m_selectedObject);

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  void ImguiManager::free()
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  }

  
  
  void ImguiManager::worldoutliner_panel(vec2ui position, vec2ui size)
  { 
    const auto& worldObj = gWorld.getWorldObjects();
    ImGui::Begin("World outliner", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    
    ImGui::SetWindowSize(ImVec2(size.x, size.y));
    ImGui::SetWindowPos(ImVec2(position.x, position.y));

    for(auto it = worldObj.begin(); it != worldObj.end(); ++it)
    {
      if(ImGui::Selectable(it->second->toString().c_str()))
      {
        m_selectedObject = it->second;
      }
    }
    ImGui::End();
  }

  void ImguiManager::details_panel(vec2ui position, vec2ui size, Object* object)
  { 
    Box* boxobject = dynamic_cast<Box*>(object);

    // transform
    // --------- 
    ImGui::Begin("Details", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    
    ImGui::SetWindowSize(ImVec2(size.x, size.y));
    ImGui::SetWindowPos(ImVec2(position.x, position.y));
    
    if(ImGui::CollapsingHeader("Transform"))
    {
      ImGui::Text(object->toString().c_str());
      ImGui::SliderFloat("Rotation", &boxobject->angle, -180.f, 180.f);
      ImGui::SliderFloat2("Scaling", (float*) &boxobject->scaling, -10.f, 10.f);
      ImGui::SliderFloat2("Translation", (float*) &boxobject->position, -1000.f, 1000.f);
    }

    // Materials
    // ---------
    if(ImGui::CollapsingHeader("Materials"))
    {
      
    }
    ImGui::End();
  }

}