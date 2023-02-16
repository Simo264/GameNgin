#include "core_minimal.h"
#include "subsystems/window_manager.h"
#include "subsystems/shader_manager.h"
#include "subsystems/texture_manager.h"
#include "subsystems/game_manager.h"
#include "box.h"
#include "world.h"
#include "logger.h"

using namespace gn;

WindowManager   gWindowManager;
ShaderManager   gShaders;
TextureManager  gTextures;
World           gWorld;
GameManager     gGameManager;

int main()
{
  LOG_TRACE("Init WindowManager...");
  gWindowManager.init();
  
  LOG_TRACE("Loading shaders...");
  gShaders.loadShader("shaders/basic.vertex.shader", "shaders/basic.fragment.shader", "basic.shader");
  gShaders.loadShader("shaders/texture.vertex.shader", "shaders/texture.fragment.shader", "texture.shader");
  
  LOG_TRACE("Loading textures...");
  gTextures.loadTexture("res/background.jpg", false, "background");
  gTextures.loadTexture("res/image.png", true, "image");
  gTextures.loadTexture("res/tile.jpg", false, "tile");
  
  LOG_TRACE("Loading objects...");
  //gWorld.pushObject(new Box(0, "Background_0", vec2(600, 600), vec2(0,0), gTextures.getTexture("background")));
  gWorld.pushObject(new Box(1, "Box_0", vec2(50,50), vec2(0,0), gTextures.getTexture("tile")));
  gWorld.pushObject(new Box(2, "Box_1", vec2(50,50), vec2(-100,100), gTextures.getTexture("image")));

  // Run the game.
  LOG_TRACE("Running the game...");
  gGameManager.run();

  // Shut everything down, in reverse order.
  gWorld.free();
  gShaders.free();
  gTextures.free();
  gWindowManager.free();

  return 0;
}


