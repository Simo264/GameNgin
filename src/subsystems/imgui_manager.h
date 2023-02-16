#ifndef IMGUI_MANAGER_H
#define IMGUI_MANAGER_H

namespace gn
{
  class ImguiManager
  {
    private:
      class WindowManager* m_windowManager;

    public:
      ImguiManager() = default;
      ~ImguiManager() = default;

      void init(class WindowManager* windowManager);
      void render();
      void free();
  };
}


#endif