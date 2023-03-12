#ifndef IMGUI_MANAGER_H
#define IMGUI_MANAGER_H

#include "engine/core/design_pattern/singleton.h"

namespace gn
{
  // Singleton ImguiManager class
  // -------------------------------------------
  class ImguiManager : public Singleton<ImguiManager>
  {
    private:
      map<string, string> m_settings;

      // window menu bar
      void menubar();
      void newProject();
      void saveProject();
      void openProject();
      void settingsFrame();
      void close();

      // settings
      const char* m_themes[3] = { "Classic", "Light", "Dark" };
      bool m_showSettings = false;
      int m_fontSize;
      void loadSettings();
      void saveSettings();
      void setTheme(const string& theme);
      void setFont(const string& fontfamily, int fontsize);

      // object editor
      class Box* m_boxSelected = nullptr;
      float m_editorObjectColor[3];
      string m_editorCurrentTextureName;
      
      
      // world outliner panel
      // ---------------------
      void worldOutlinerPanel();

      // editor object panel
      // ---------------------
      void editorObjectPanel(class Box*);

      // output log panel
      // ---------------------
      void outputLogPanel();

      // texture list panel
      void textureListPanel();

    public:
      ImguiManager() = default;
      ~ImguiManager() = default;

      void init();
      void render();
      void free();
  };
}


#endif