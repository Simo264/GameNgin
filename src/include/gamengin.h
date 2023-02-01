#ifndef GAMENGIN_H
#define GAMENGIN_H

#include "../include/window.h"
#include "../include/shader.h"

namespace GameNgin
{ 
  class Window;

  extern bool     gameloop;

  void initGL();
  void input(double deltatime);
  void update(double deltatime);
  void render(Shader* shader);
  void free();

  void initImGui();
  void renderImGui();
  void destroyImGui();
};

#endif