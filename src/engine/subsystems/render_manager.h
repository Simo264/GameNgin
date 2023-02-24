#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "engine/core/design_pattern/singleton.h"

namespace gn
{
  // Singleton RenderManager class
  // -------------------------------------------
  class RenderManager : public Singleton<RenderManager>
  {
  public:
    RenderManager() = default;
    ~RenderManager() = default;

    uint32_t drawmode = GL_TRIANGLES;

    void draw(class Shader* shader, class Box*);
  };
  // -------------------------------------------

}

#endif