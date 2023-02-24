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
  WindowManager::getInstance().init();
  ShaderManager::getInstance().init();
  TextureManager::getInstance().init();
  
  // gWorld.init();
  gWorld.insertObject(new Box(0, "Box_0", {0,0}, {50,50}, {1.f,1.f}, 0.f, TextureManager::getInstance().getTextureByName("image")));


  // Run the game.
  GameManager::getInstance().run();

  // Shut everything down, in reverse order.
  gWorld.free();
  ShaderManager::getInstance().free();
  TextureManager::getInstance().free();
  WindowManager::getInstance().free();

  return 0;
}


