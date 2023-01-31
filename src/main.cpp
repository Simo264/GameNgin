#include "../include/core_minimal.h"
#include "../include/gamengin.h"

#include "../include/logger.h"
#include "../include/world.h"

#include "../include/box.h"
#include "../include/collision_detection.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

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
  Shader basicShader("../shaders/basic.vertex.shader", "../shaders/basic.fragment.shader");
  Shader textShader("../shaders/texture.vertex.shader", "../shaders/texture.fragment.shader");

  // load and create a texture 
  // -------------------------
  


  // init world 
  // ----------
  world::push_object(new Box(glm::vec2{ 50,50 }, glm::vec2{ 0,0 }));
  //world::push_object(new Box(glm::vec2{ 50,50 }, glm::vec2{ 300,200 }));


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
    GameNgin::render(&textShader);
  }

  GameNgin::free();
  GameNgin::destroyImGui();

  return 0;
}


