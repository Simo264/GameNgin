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
  static Object* object;


  void ImguiManager::init(WindowManager* windowManager)
  {
    m_windowManager = windowManager;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_windowManager->get(), true);
    ImGui_ImplOpenGL3_Init("#version 450");
  }

  void ImguiManager::render()
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    const auto& worldObj = gWorld.getWorldObjects();

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(300, 500));
    ImGui::Begin("World objects", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    for(auto it = worldObj.begin(); it != worldObj.end(); ++it)
    {
      Object* obj = it->second;
      const std::string& label = obj->toString();
      if(ImGui::Selectable(label.c_str()))
        object = obj;
    }
    ImGui::End();


    if(object)
    {
      Box* boxobject = dynamic_cast<Box*>(object);

      ImGui::SetNextWindowPos(ImVec2(m_windowManager->getWindowSize().x - 300, 0));
      ImGui::SetNextWindowSize(ImVec2(300, 500));
      ImGui::Begin("Details");

      if(ImGui::CollapsingHeader("Transform"))
      {
        ImGui::Text(object->toString().c_str());
        ImGui::SliderFloat("Rotation", &boxobject->angle, -180.f, 180.f);
        ImGui::SliderFloat2("Scaling", (float*) &boxobject->scaling, -10.f, 10.f);
        ImGui::SliderFloat2("Translation", (float*) &boxobject->position, -1000.f, 1000.f);
      }
      if(ImGui::CollapsingHeader("Materials"))
      {
        
      }

      ImGui::End();
    }


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

}