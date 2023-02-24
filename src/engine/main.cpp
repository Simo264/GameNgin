#include "engine/core/core.h"
#include "engine/subsystems/window_manager.h"
#include "engine/subsystems/shader_manager.h"
#include "engine/subsystems/texture_manager.h"
#include "engine/subsystems/game_manager.h"
#include "engine/subsystems/file_manager.h"
#include "engine/box.h"
#include "engine/world.h"

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
  
  // gWorld.init();
  gWorld.insertObject(new Box(0, "Box_0", {0,0}, {50,50}));


  // Run the game.
  gGameManager.run();

  // Shut everything down, in reverse order.
  gWorld.free();
  gShaders.free();
  gTextures.free();
  gWindowManager.free();

  return 0;
}


