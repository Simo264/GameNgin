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
  gWindowManager.init();
  LOG_TRACE("Init WindowManager... OK!");

  gWindowManager.IMGUIinit();
  LOG_TRACE("Init IMGUI... OK!");

  gShaders.loadShader("../shaders/basic.vertex.shader", "../shaders/basic.fragment.shader", nullptr, "basic.shader");
  //gShaders.loadShader("../shaders/texture.vertex.shader", "../shaders/texture.fragment.shader", nullptr, "texture.shader");
  //LOG_TRACE("Loading shaders... OK!");

  //gTextures.loadTexture("../res/image.png", true, "image");
  //LOG_TRACE("Loading textures... OK!");
  

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


