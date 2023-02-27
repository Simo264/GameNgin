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

static vector<string> m_editorTextureNameList = {"image.png", "tile.jpg", "background.jpg"};

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

    textureListPanel();

    // outputLogFrame();

    // if(show_settings)
    //   settingsFrame();

    worldOutlinerPanel();         

    editorObjectPanel(gWorld.getObjectByID(0));


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

      m_showSettings = ImGui::MenuItem("Preferences");
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
    // TODO:   
  }

  void ImguiManager::saveProject()
  {
    // TODO: 
  }

  void ImguiManager::openProject()
  {
    // TODO:
  }

  void ImguiManager::close()
  {
    // TODO:
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
        bool is_selected = (theme == m_themes[i]); 

        if (ImGui::Selectable(m_themes[i], is_selected))
        {
          theme = m_themes[i];
          setTheme(theme);
        }
        if (is_selected)
          ImGui::SetItemDefaultFocus();  
      }
      ImGui::EndCombo();
    }

    string& fontfamily = m_settings.at("font-family");
    ImGui::InputText("Font family", &fontfamily[0], 100);

    ImGui::InputInt("Font size", &m_fontSize);
    m_settings["font-size"] = to_string(m_fontSize);

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

    m_fontSize = stoi(m_settings.at("font-size"));
    setTheme(m_settings.at("theme"));
    setFont(m_settings.at("font-family"), m_fontSize);
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





  // ---------- Panels -----------
  // -----------------------------
  void ImguiManager::worldOutlinerPanel()
  { 
    const auto& worldObj = gWorld.getObjects();
    ImGui::Begin("World outliner");
    
    for(auto it = worldObj.begin(); it != worldObj.end(); ++it)
    {
      if(ImGui::Selectable(it->second->getName().c_str()))
      {

      }
    }
    ImGui::End();
  }

  void ImguiManager::editorObjectPanel(Box* object)
  { 
    const string& panelName = "Details " + object->getName();
    ImGui::Begin(panelName.c_str());

    // transform
    // -----------
    if(ImGui::CollapsingHeader("Transform"))
    {
      ImGui::SliderAngle("Rotation", &object->rotation);
      ImGui::Spacing();
      ImGui::SliderFloat2("Scaling", (float*) &object->scaling, -10.f, 10.f);
      ImGui::Spacing();
      ImGui::SliderFloat2("Translation", (float*) &object->position, -1000.f, 1000.f);
      ImGui::Separator();
    }

    // Color
    // -----------
    if(ImGui::CollapsingHeader("Color"))
    {
      ImGui::Text("Select color");
      color8_t objectColor = object->getColor();
      m_editorObjectColor[0] = (float)(objectColor[0] / 255.f);
      m_editorObjectColor[1] = (float)(objectColor[1] / 255.f);
      m_editorObjectColor[2] = (float)(objectColor[2] / 255.f);
      
      ImGui::ColorPicker3("Color", m_editorObjectColor);
      uint8_t r = (uint8_t)(m_editorObjectColor[0] * 255);
      uint8_t g = (uint8_t)(m_editorObjectColor[1] * 255);
      uint8_t b = (uint8_t)(m_editorObjectColor[2] * 255);

      color8_t newColor { r,g,b };
      object->setColor(newColor);
    }

    // Materials
    // -----------
    if(ImGui::CollapsingHeader("Texture"))
    {
      // show current texture
      // --------------
      ImGui::Text("Current texture");
      ImGui::SameLine();
      ImGui::Image((void*)(intptr_t) object->texture->getID(), { 100,100 } );

      // ImGui::Separator();
            
      // select texture
      // --------------
      ImGui::Text("Change texture");
      ImGui::SameLine();

      TextureManager::getInstance().getTextureName(object->texture, m_editorCurrentTextureName);

      if (ImGui::BeginCombo("##Combo", m_editorCurrentTextureName.c_str())) 
      {
        for (int i = 0; i < m_editorTextureNameList.size(); i++)
        {
          bool is_selected = (m_editorCurrentTextureName == m_editorTextureNameList[i]); 
          ImGui::Image((void*)(intptr_t) TextureManager::getInstance().getTextureByName(m_editorTextureNameList[i])->getID(), { 20,20 });
          ImGui::SameLine();
          if (ImGui::Selectable(m_editorTextureNameList[i].c_str(), is_selected))
          {
            m_editorCurrentTextureName = m_editorTextureNameList[i];
            object->texture = TextureManager::getInstance().getTextureByName(m_editorCurrentTextureName);
          }
          if (is_selected)
            ImGui::SetItemDefaultFocus();   
        }
        
        ImGui::EndCombo();
      }
    }
    
    
    ImGui::End();
  }

  void ImguiManager::outputLogPanel()
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

  void ImguiManager::textureListPanel()
  {
    ImGui::Begin("Textures");

    TextureManager& tm = TextureManager::getInstance();
    for(auto it = tm.getTextures().begin(); it != tm.getTextures().end(); it++)
    {
      const string& name = it->first;
      const Texture* texture = it->second;

      ImGui::Image((void*)(intptr_t) texture->getID(), { 70,70 });
      ImGui::SameLine();
      ImGui::Text(name.c_str());
      ImGui::Separator();
    } 
    ImGui::End();
  }

}