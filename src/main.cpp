#include "core_minimal.h"
#include "subsystems/window_manager.h"
#include "subsystems/shader_manager.h"
#include "subsystems/texture_manager.h"
#include "subsystems/game_manager.h"
#include "subsystems/file_manager.h"
#include "box.h"
#include "world.h"

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
  gWorld.init();

  // Run the game.
  gGameManager.run();

  // Shut everything down, in reverse order.
  gWorld.free();
  gShaders.free();
  gTextures.free();
  gWindowManager.free();

  return 0;
}


