#include "include/core_minimal.h"
#include "include/window_manager.h"
#include "include/game_manager.h"

#include "include/world.h"
#include "include/resource_manager.h"

using namespace gn;

WindowManager gWindowManager;
World         gWorld;
// ShadersManager gShaders;
// TexturesManager gTextures;
GameManager   gGameManager;

int main()
{
  // Start up engine systems in the correct order.
  gWindowManager.init();
  gWindowManager.IMGUIinit();

  //gMemoryManager.startUp();
  //gFileSystemManager.startUp();
  //gVideoManager.startUp();
  //gTextureManager.startUp();
  //gRenderManager.startUp();
  //gAnimationManager.startUp();
  //gPhysicsManager.startUp();
  // ...


  // load and create shaders
  // -------------------------
  ResourceManager::loadShader("../shaders/basic.vertex.shader", 
                              "../shaders/basic.fragment.shader", 
                              nullptr, 
                              "basic.shader");
  ResourceManager::loadShader("../shaders/texture.vertex.shader", 
                              "../shaders/texture.fragment.shader", 
                              nullptr, 
                              "texture.shader");
  Shader* shader = ResourceManager::getShader("texture.shader");
  
  // load and create textures
  // -------------------------
  ResourceManager::loadTexture("../res/image.png", true, "image");


  // init world 
  // ----------
  // gWorld.pushObject(new Box(vec2{ 50,50 }, vec2{ 0,0 }));
  // gWorld.pushObject(new Box(vec2{ 50,50 }, vec2{ 100,100 }));
  // gWorld.pushObject(new Box(vec2{ 50,50 }, vec2{ 300,100 }));
  // gWorld.pushObject(new Box(vec2{ 50,50 }, vec2{ 100,300 }));


  // Run the game.
  gGameManager.run();
  
  
  // Shut everything down, in reverse order.
  // ...
  // gPhysicsManager.shutDown();
  // gAnimationManager.shutDown();
  // gRenderManager.shutDown();
  // gFileSystemManager.shutDown();
  // gMemoryManager.shutDown();
  ResourceManager::free();
  // gShaders.free();
  // gTextures.free();
  gWorld.free();
  gWindowManager.IMGUIfree();
  gWindowManager.free();

  return 0;
}


