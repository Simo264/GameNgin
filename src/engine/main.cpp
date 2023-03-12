#include "engine/core/core.h"
#include "engine/subsystems/window_manager.h"
#include "engine/subsystems/shader_manager.h"
#include "engine/subsystems/texture_manager.h"
#include "engine/subsystems/render_manager.h"
#include "engine/subsystems/game_manager.h"

#include "engine/box.h"
#include "engine/world.h"

using namespace gn;

World gWorld;

int main()
{
  WindowManager& windowManager    = WindowManager::getInstance();
  ShaderManager& shaderManager    = ShaderManager::getInstance();
  TextureManager& textureManager  = TextureManager::getInstance();
  GameManager& gameManager        = GameManager::getInstance();

  windowManager.init();
  shaderManager.init();
  textureManager.init();

  gWorld.load(WORLD_INI_FILE);

  // Run the game.
  gameManager.run();

  // Shut everything down, in reverse order.
  gWorld.free();
  shaderManager.free();
  textureManager.free();
  windowManager.free();

  return 0;
}


