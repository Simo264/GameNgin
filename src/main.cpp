#include "core_minimal.h"
#include "subsystems/window_manager.h"
#include "subsystems/shader_manager.h"
#include "subsystems/texture_manager.h"
#include "subsystems/game_manager.h"
#include "subsystems/file_manager.h"
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
  gWindowManager.init();
  gShaders.init();
  gTextures.init();

  LOG_TRACE("Loading world...");
  // gWorld.init();
  gWorld.pushObject(new Box(0, "Box_0", vec2(50,50), vec2(0,0), gTextures.getTexture("image")));
  gWorld.pushObject(new Box(1, "Box_1", vec2(50,50), vec2(-200,200), gTextures.getTexture("tile")));

  // Run the game.
  LOG_TRACE("Running the engine...");
  gGameManager.run();

  // Shut everything down, in reverse order.
  gWorld.free();
  gShaders.free();
  gTextures.free();
  gWindowManager.free();

  return 0;
}


