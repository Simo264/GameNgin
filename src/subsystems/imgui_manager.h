#ifndef IMGUI_MANAGER_H
#define IMGUI_MANAGER_H

namespace gn
{
  class ImguiManager
  {
    private:
      class WindowManager* m_windowManager;
      class Object* m_selectedObject;

      // show world objects panel
      void worldoutliner_panel(vec2ui position, vec2ui size);

      // object details panel
      void details_panel(vec2ui position, vec2ui size, class Object*);

    public:
      ImguiManager() = default;
      ~ImguiManager() = default;

      void init(class WindowManager* windowManager);
      void render();
      void free();
  };
}


#endif