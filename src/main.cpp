#include "core_minimal.h"
#include "window_manager.h"
#include "world.h"
#include "shader_manager.h"
#include "texture_manager.h"
#include "game_manager.h"

#include "logger.h"

using namespace gn;

WindowManager   gWindowManager;
ShaderManager   gShaders;
TextureManager  gTextures;
World           gWorld;
GameManager     gGameManager;

int main()
{
  // Start up engine systems in the correct order.
  LOG_TRACE("Init WindowManager...");
  if(!gWindowManager.init())
  {
    LOG_ERROR("Failed on init WindowManager!");
    return (EXIT_FAILURE);
  }
  gWindowManager.IMGUIinit();
  
  LOG_TRACE("Loading shaders...");
  gShaders.loadShader(
    "shaders/basic.vertex.shader", 
    "shaders/basic.fragment.shader", 
    "basic.shader");
  gShaders.loadShader(
    "shaders/texture.vertex.shader", 
    "shaders/texture.fragment.shader", 
    "texture.shader");
  
  LOG_TRACE("Loading textures...");
  gTextures.loadTexture("res/image.png", true, "image");
  
  

  // init world 
  // ----------
  // gWorld.init();
  // gWorld.pushObject(new Box(vec2{ 50,50 }, vec2{ 0,0 }));
  // gWorld.pushObject(new Box(vec2{ 50,50 }, vec2{ 100,100 }));
  // gWorld.pushObject(new Box(vec2{ 50,50 }, vec2{ 300,100 }));
  // gWorld.pushObject(new Box(vec2{ 50,50 }, vec2{ 100,300 }));


  // Run the game.
  gGameManager.run();
  
  
  // Shut everything down, in reverse order.
  gWorld.free();
  gShaders.free();
  gTextures.free();
  gWindowManager.IMGUIfree();
  gWindowManager.free();

  return 0;
}


