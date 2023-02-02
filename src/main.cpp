#include "include/core_minimal.h"
#include "include/gamengin.h"
#include "include/world.h"
#include "include/resource_manager.h"

#include "include/box.h"

#include "include/window_manager.h"

WindowManager gWindowManager;

int main()
{
  // Start up engine systems in the correct order.
  gWindowManager.startUp();
  //gMemoryManager.startUp();
  //gFileSystemManager.startUp();
  //gVideoManager.startUp();
  //gTextureManager.startUp();
  //gRenderManager.startUp();
  //gAnimationManager.startUp();
  //gPhysicsManager.startUp();
  // ...
  
  // init ImGui 
  // ----------
  GameNgin::initImGui();

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
  World::pushObject(new Box(vec2{ 50,50 }, vec2{ 0,0 }));
  World::pushObject(new Box(vec2{ 50,50 }, vec2{ 100,100 }));
  World::pushObject(new Box(vec2{ 50,50 }, vec2{ 300,100 }));
  World::pushObject(new Box(vec2{ 50,50 }, vec2{ 100,300 }));


  // Run the game.
  //gSimulationManager.run();




  // deltaTime variables
  // -------------------
  double deltaTime    = 0.0f;
  double lastFrame    = 0.0f;
  double currentFrame = 0.f;
  while (GameNgin::gameloop)
  {
    // calculate delta time
    // --------------------
    currentFrame = static_cast<double>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // input
    // ------
    GameNgin::input(deltaTime);

    // update state
    // ------
    GameNgin::update(deltaTime);

    // render
    // ------
    GameNgin::render(shader);
  }
  
  // Shut everything down, in reverse order.
  // ...
  // gPhysicsManager.shutDown();
  // gAnimationManager.shutDown();
  // gRenderManager.shutDown();
  // gFileSystemManager.shutDown();
  // gMemoryManager.shutDown();
  gWindowManager.shutDown();

  GameNgin::free();
  GameNgin::destroyImGui();

  return 0;
}


