#include "../include/core_minimal.h"
#include "../include/gamengin.h"

#include "../include/logger.h"
#include "../include/world.h"

#include "../include/box.h"
#include "../include/collision_detection.h"

int main()
{
  GameNgin::initGL();

  // GameNgin::loadShaders();
  Shader shader("../shaders/vertex.shader", "../shaders/fragment.shader");


  /* init world */
  Box* box1 = new Box(glm::vec2{ 50,50 }, glm::vec2{ 0,0 });
  Box* box2 = new Box(glm::vec2{ 50,50 }, glm::vec2{ 300,200 });
  world::insert_object(box1);
  world::insert_object(box2);


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


    // window.processInput(input_callback);
    // 

    // update state
    // ------
    GameNgin::update(deltaTime);


    // uint32_t drawmode = GL_TRIANGLES;
    // if(collision_detection::basic_hitbox(box1, box2))
    //   drawmode = GL_LINE_LOOP;

    // if(box2)
    // {
    //   if(collision_detection::basic_hitbox(box1, box2))
    //   {
    //     world::destroy_object(box2);
    //     box2 = nullptr;
    //   }
    // }


    // render
    // ------
    GameNgin::render(deltaTime, &shader);
  //   box1->render(&shader, drawmode);
  //   box2->render(&shader);
    
    // for(auto it = world::world_objects.begin(); it != world::world_objects.end(); ++it)
    // {
    //   Box* b = dynamic_cast<Box*>(it->second);
    //   if(b)
    //   {
    //     b->render(&shader);
    //   }
    // }
  // }

  }
  
  GameNgin::free();

  return 0;
}

// void input_callback(Window* window)
// {
//   if (window->getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
//   {
//     window->close();
//     return;
//   }
  
//   if(window->getKey(GLFW_KEY_A) == GLFW_PRESS)
//   {
//     box1->position.x -= 2 * (deltaTime*100);
//     return;
//   }

//   if(window->getKey(GLFW_KEY_D) == GLFW_PRESS)
//   {
//     box1->position.x += 2 * (deltaTime*100);
//     return;
//   }

//   if(window->getKey(GLFW_KEY_W) == GLFW_PRESS)
//   {
//     box1->position.y -= 2 * (deltaTime*100) ;
//     return;
//   }

//   if(window->getKey(GLFW_KEY_S) == GLFW_PRESS)
//   {
//     box1->position.y += 2 * (deltaTime*100);
//     return;
//   }
// }


