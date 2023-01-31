#include "../include/core_minimal.h"
#include "../include/gamengin.h"

#include "../include/logger.h"
#include "../include/world.h"

#include "../include/box.h"
#include "../include/collision_detection.h"

int main()
{
  // init OpenGL 
  // ------
  GameNgin::initGL();
  
  // init ImGui 
  // ------
  GameNgin::initImGui();

  // GameNgin::loadShaders();
  Shader shader("../shaders/vertex.shader", "../shaders/fragment.shader");


  /* init world */
  Box* box1 = new Box(glm::vec2{ 50,50 }, glm::vec2{ 0,0 });
  Box* box2 = new Box(glm::vec2{ 50,50 }, glm::vec2{ 300,200 });
  world::push_object(box1);
  world::push_object(box2);


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
    GameNgin::render(&shader);
  }

  GameNgin::free();
  GameNgin::destroyImGui();

  return 0;
}


