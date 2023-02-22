#ifndef IMGUI_MANAGER_H
#define IMGUI_MANAGER_H

namespace gn
{
  class ImguiManager
  {
    private:
      static std::map<std::string, std::string> m_settings;

      class WindowManager* m_windowManager;


      // window menu bar
      void menubar();
      void newProject();
      void saveProject();
      void openProject();
      void settingsFrame();
      void close();

      // settings
      bool show_settings = false;
      int m_fontsize;
      void loadSettings();
      void saveSettings();
      void setTheme(const std::string& theme);
      void setFont(const std::string& fontfamily, int fontsize);
      


      // world outliner frame
      // ---------------------
      void worldoutlinerFrame(vec2ui position, vec2ui size);

      // editor object frame
      // ---------------------
      void editorFrame(vec2ui position, vec2ui size, class Object*);

      // output log frame
      // ---------------------
      void outputLogFrame();

    public:
      ImguiManager() = default;
      ~ImguiManager() = default;

      void init(class WindowManager* windowManager);
      void render();
      void free();
  };
}


#endif