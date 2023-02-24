#include "engine/core/core.h"

#include "imgui_manager.h"
#include "window_manager.h"
#include "texture_manager.h"
#include "file_manager.h"

#include "engine/world.h"
#include "engine/box.h"
#include "engine/texture.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

extern gn::World gWorld;

static gn::ObjectBase* m_selectedObject = nullptr;
static bool drawlines = false;
static char textpath[100];
static const char* themes[3] = { "Classic", "Light", "Dark" };

namespace gn
{
  void ImguiManager::init(WindowManager* windowManager)
  {
    m_windowManager = windowManager;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(m_windowManager->getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 450");

    loadSettings();
  }

  void ImguiManager::render()
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    menubar();

    outputLogFrame();

    // if(show_settings)
    //   settingsFrame();

    // worldoutliner_panel(vec2ui(m_windowManager->getWindowSize().x - 300, 0), vec2ui(300, 300));                                   

    // if(m_selectedObject)
    //   details_panel(vec2ui(m_windowManager->getWindowSize().x - 300, 400), vec2ui(300, 300), m_selectedObject);

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


  // ------- Menubar items ---------- 
  // --------------------------------
  void ImguiManager::menubar()
  {
    ImGui::BeginMainMenuBar();
    
    ImGui::SetNextWindowSize({ 300.0f,150.0f });

    if(ImGui::BeginMenu("File"))
    {
      if(ImGui::MenuItem("New project"))
        newProject();
      
      if(ImGui::MenuItem("Save"))
        saveProject();

      if(ImGui::MenuItem("Open"))
        openProject();

      ImGui::Separator();

      show_settings = ImGui::MenuItem("Preferences");
      // if(ImGui::MenuItem("Preferences"))
        // show_preferences = true;
        //preferences();

      if(ImGui::MenuItem("Close"))
        close();

      ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
  }

  void ImguiManager::newProject()
  {
    // TODO ...  
  }

  void ImguiManager::saveProject()
  {
    // TODO ...
  }

  void ImguiManager::openProject()
  {
    // TODO ...
  }

  void ImguiManager::close()
  {
    // TODO ...
  }

  // ------- Settings --------------- 
  // --------------------------------
  void ImguiManager::settingsFrame()
  {
    ImGui::SetNextWindowSize({ 500.f,500.f });

    ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

    string& theme = m_settings.at("theme");
    if(ImGui::BeginCombo("Theme", &theme[0]))
    {
      for (int i = 0; i < 3; i++)
      {
        bool is_selected = (theme == themes[i]); 

        if (ImGui::Selectable(themes[i], is_selected))
        {
          theme = themes[i];
          setTheme(theme);
        }
        if (is_selected)
          ImGui::SetItemDefaultFocus();  
      }
      ImGui::EndCombo();
    }

    string& fontfamily = m_settings.at("font-family");
    ImGui::InputText("Font family", &fontfamily[0], 100);

    ImGui::InputInt("Font size", &m_fontsize);
    m_settings["font-size"] = to_string(m_fontsize);

    if(ImGui::Button("Save changes"))
      saveSettings();

    ImGui::End();
  }

  void ImguiManager::loadSettings()
  {
    vector<string> buffer;
    FileManager::read(PREFERENCES_CONF_FILE, buffer);

    array<char, 50> key;
    array<char, 50> value;

    for(auto it = buffer.begin(); it != buffer.end(); it++)
    {
      key.fill(0);
      value.fill(0);

      int delimiter = it->find("=");

      copy_n(it->begin(), delimiter, key.begin());
      copy(it->begin() + delimiter + 1, it->end(), value.begin()); 

      m_settings.insert({ key.data(), value.data() });
    }

    m_fontsize = stoi(m_settings.at("font-size"));
    setTheme(m_settings.at("theme"));
    setFont(m_settings.at("font-family"), m_fontsize);
  }
  
  void ImguiManager::saveSettings()
  {
    string data = "";
    for(auto it = m_settings.begin(); it != m_settings.end(); it++)
      data.append(it->first + "=" + it->second + "\n");
    
    FileManager::write(PREFERENCES_CONF_FILE, data);
  }

  void ImguiManager::setTheme(const string& theme)
  {
    if(theme == "Dark")
      ImGui::StyleColorsDark();
    else if(theme == "Classic")
      ImGui::StyleColorsClassic();
    else if(theme == "Light")
      ImGui::StyleColorsLight();
  }
  
  void ImguiManager::setFont(const string& fontfamily, int fontsize)
  {
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF(fontfamily.c_str(), fontsize);
  }





  
  void ImguiManager::worldoutlinerFrame(vec2ui position, vec2ui size)
  { 
    const auto& worldObj = gWorld.getObjects();
    ImGui::Begin("World outliner");
    
    for(auto it = worldObj.begin(); it != worldObj.end(); ++it)
    {
      if(ImGui::Selectable(it->second->getName().c_str()))
      {
        ImGui::SetItemDefaultFocus();
        m_selectedObject = it->second;
      }
    }
    ImGui::End();
  }

  void ImguiManager::editorFrame(vec2ui position, vec2ui size, ObjectBase* object)
  { 
    Box* boxobject = dynamic_cast<Box*>(object);
    ImGui::Begin("Details");

    // transform
    // --------- 
    if(ImGui::CollapsingHeader("Transform"))
    {
      ImGui::Text(object->getName().c_str());
      ImGui::SliderAngle("Rotation", &boxobject->rotation);
      ImGui::Spacing();
      ImGui::SliderFloat2("Scaling", (float*) &boxobject->scaling, -10.f, 10.f);
      ImGui::Spacing();
      ImGui::SliderFloat2("Translation", (float*) &boxobject->position, -1000.f, 1000.f);
      ImGui::Separator();
      // ImGui::Checkbox("Draw lines", &drawlines);
      // if(drawlines) 
      //   boxobject->drawmode = GL_LINE_LOOP;
      // else  
      //   boxobject->drawmode = GL_TRIANGLES;
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
        // ImGui::Text("Select color");
        // color_t objectColor = boxobject->getColor();
        // float color[3] = { 
        //   (float)(objectColor[0] / 255.f),
        //   (float)(objectColor[1] / 255.f),
        //   (float)(objectColor[2] / 255.f),
        // };

        // ImGui::ColorPicker3("Color", color);
        // uint8_t r = (uint8_t)(color[0] * 255);
        // uint8_t g = (uint8_t)(color[1] * 255);
        // uint8_t b = (uint8_t)(color[2] * 255);
        // boxobject->color = color8_t{ r,g,b };
        // boxobject->setColor(color8_t{ r,g,b });
      }  

    }
    ImGui::End();
  }

  void ImguiManager::outputLogFrame()
  {
    ImGui::SetNextWindowSize({ (float) m_windowManager->getWindowSize().x, 200.f });
    ImGui::SetNextWindowPos({ 0.f, (float) m_windowManager->getWindowSize().y - 200 });
    
    ImGui::Begin("Log", nullptr, ImGuiWindowFlags_NoCollapse );

    ImGui::Text("Hello world\n");
    ImGui::Text("Hello world\n");
    ImGui::Text("Hello world\n");
    ImGui::Text("Hello world\n");
    ImGui::Text("Hello world\n");
    ImGui::Text("Hello world\n");
    ImGui::Text("Hello world\n");
    ImGui::Text("Hello world\n");
    ImGui::Text("Hello world\n");
    ImGui::Text("Hello world\n");
    ImGui::Text("Hello world\n");
    ImGui::Text("Hello world\n");

    ImGui::End();
  }

}