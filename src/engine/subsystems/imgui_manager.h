#ifndef IMGUI_MANAGER_H
#define IMGUI_MANAGER_H

namespace gn
{
  class ImguiManager
  {
    private:
      map<string, string> m_settings;

      class WindowManager* m_windowManager;

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

      void init(class WindowManager* windowManager);
      void render();
      void free();
  };
}


#endif