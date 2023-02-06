#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

class RenderManager
{
private:

public:
  RenderManager() = default;
  ~RenderManager() = default;

  void render(class Shader*, class ObjectGL*);
};


#endif