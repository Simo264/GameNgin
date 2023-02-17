#include "../core_minimal.h"

#include "imgui_manager.h"
#include "window_manager.h"
#include "texture_manager.h"

#include "../world.h"
#include "../box.h"
#include "../texture.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

extern gn::World gWorld;
extern gn::TextureManager gTextures;

static bool drawlines = false;
static char textpath[100];

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
      vec2ui(m_windowManager->getWindowSize().x - 300, 0), // position
      vec2ui(300, 300));                                   // size 

    if(m_selectedObject)
      details_panel(
        vec2ui(m_windowManager->getWindowSize().x - 300, 400), // position
        vec2ui(300, 300),                                      // size
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
    ImGui::Begin("World outliner");
    
    for(auto it = worldObj.begin(); it != worldObj.end(); ++it)
    {
      if(ImGui::Selectable(it->second->toString().c_str()))
      {
        ImGui::SetItemDefaultFocus();
        m_selectedObject = it->second;
      }
    }
    ImGui::End();
  }

  void ImguiManager::details_panel(vec2ui position, vec2ui size, Object* object)
  { 
    Box* boxobject = dynamic_cast<Box*>(object);
    ImGui::Begin("Details");

    // transform
    // --------- 
    if(ImGui::CollapsingHeader("Transform"))
    {
      ImGui::Text(object->toString().c_str());
      ImGui::SliderAngle("Rotation", &boxobject->angle);
      ImGui::Spacing();
      ImGui::SliderFloat2("Scaling", (float*) &boxobject->scaling, -10.f, 10.f);
      ImGui::Spacing();
      ImGui::SliderFloat2("Translation", (float*) &boxobject->position, -1000.f, 1000.f);
      ImGui::Separator();
      ImGui::Checkbox("Draw lines", &drawlines);
      if(drawlines) 
        boxobject->drawmode = GL_LINE_LOOP;
      else  
        boxobject->drawmode = GL_TRIANGLES;
    }

    // Materials
    // ---------
    if(ImGui::CollapsingHeader("Materials"))
    {
      // current texture
      // --------------
      ImGui::Text("Current texture");
      ImGui::Image((void*)(intptr_t) boxobject->texture->getID(), ImVec2(100, 100));

      ImGui::Separator();
      ImGui::Spacing();
            
      // select texture
      // --------------
      ImGui::Text("Change texture");
      ImGui::InputTextWithHint("Load texture", "path here...", textpath, 100);
      if(ImGui::Button("Load", ImVec2(100, 25)))
      {
        
      }
      
      ImGui::Separator();
      ImGui::Spacing();

      // color picker
      // --------------
      {
        ImGui::Text("Select color");
        float color[3] = { 
          (float)(boxobject->color[0] / 255.f),
          (float)(boxobject->color[1] / 255.f),
          (float)(boxobject->color[2] / 255.f),
        };

        ImGui::ColorPicker3("Color", color);
        uint8_t r = (uint8_t)(color[0] * 255);
        uint8_t g = (uint8_t)(color[1] * 255);
        uint8_t b = (uint8_t)(color[2] * 255);
        boxobject->color = color8_t{ r,g,b };
        boxobject->setColor(color8_t{ r,g,b });
      }  

    }
    ImGui::End();
  }

}