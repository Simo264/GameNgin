#include "../include/core_minimal.h"
#include "../include/gamengin.h"
#include "../include/world.h"
#include "../include/resource_manager.h"

#include "../include/box.h"


int main()
{
  // init OpenGL 
  // -----------
  GameNgin::initGL();
  
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
  world::push_object(new Box(glm::vec2{ 50,50 }, glm::vec2{ 100,100 }));


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

  GameNgin::free();
  GameNgin::destroyImGui();

  return 0;
}


