#ifndef GAMENGIN_H
#define GAMENGIN_H

#include "../include/window.h"
#include "../include/shader.h"

namespace GameNgin
{ 
  extern Window window;
  extern bool gameloop;

  void initGL();

  void input(double deltatime);
  void update(double deltatime);
  void render(double deltatime, Shader* shader);

  void free();
};

#endif