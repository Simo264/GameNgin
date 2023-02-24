#ifndef GAMENGIN_H
#define GAMENGIN_H

#include "engine/core/design_pattern/singleton.h"

namespace gn
{ 
  // Singleton GameManager class
  // -----------------------------------------------------------
  class GameManager : public Singleton<GameManager>
  {
    private:
      bool   gameloop     = true;
      double deltatime    = 0.0f;
      double lastFrame    = 0.0f;
      double currentFrame = 0.f;

      void input(double deltatime);   
      void update(double deltatime);  
      void render();    

    public:
      GameManager() = default;
      ~GameManager() = default;

      void run();                     
  };
  // -----------------------------------------------------------
  
};

#endif