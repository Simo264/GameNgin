#ifndef GAMENGIN_H
#define GAMENGIN_H

#include "shader.h"

using namespace GL;

namespace gn
{ 

  // GameManager class
  // -----------------------------------------------------------
  class GameManager
  {
    private:
      bool   gameloop     = true;
      double deltatime    = 0.0f;
      double lastFrame    = 0.0f;
      double currentFrame = 0.f;

      void input(double deltatime);   
      void update(double deltatime);  
      void render(Shader* shader);    

    public:
      GameManager() = default;
      ~GameManager() = default;

      void run();                     
  };
  // -----------------------------------------------------------
  
};

#endif