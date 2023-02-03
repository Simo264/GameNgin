#include "include/core_minimal.h"
#include "include/window_manager.h"
#include "include/game_manager.h"

extern gn::WindowManager gWindowManager;

using namespace GL;

namespace gn
{
  void GameManager::run()
  {
    while (gameloop || gWindowManager.shouldClose())
    {
      // calculate delta time
      // --------------------
      currentFrame = static_cast<double>(glfwGetTime());
      deltatime = currentFrame - lastFrame;
      lastFrame = currentFrame;

      input(deltatime);
      update(deltatime);
      render(nullptr);

      // Swap front and back buffers 
      gWindowManager.swapBuffers();

      // Poll for and process events 
      glfwPollEvents();
    }
    
  }
  void GameManager::input(double deltatime)
  {
    // Close window
    if (gWindowManager.getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
      gWindowManager.close(); 
      return;
    }
  }
  void GameManager::update(double deltatime)
  {
    
  }
  void GameManager::render(Shader* shader)
  {
    glClearColor(1.f, 1.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    gWindowManager.IMGUIrender();
  }



  // void input(double deltatime)
  // {
  //   glfwPollEvents();

  //   Box* box1 = dynamic_cast<Box*>(World::getObjectByID(0));
  //   float velocity = 250.f * deltatime;



  //   // press W
  //   if (window.getKey(GLFW_KEY_W) == GLFW_PRESS)
  //   {
  //     box1->position.y -= velocity;
  //     return;
  //   }
    
  //   // press A
  //   if (window.getKey(GLFW_KEY_A) == GLFW_PRESS)
  //   {
  //     box1->position.x -= velocity;
  //     return;
  //   }
    
  //   // press S
  //   if (window.getKey(GLFW_KEY_S) == GLFW_PRESS)
  //   {
  //     box1->position.y += velocity;
  //     return;
  //   }
    
  //   // press D
  //   if (window.getKey(GLFW_KEY_D) == GLFW_PRESS)
  //   {
  //     box1->position.x += velocity;
  //     return;
  //   }

  // }

  // void update(double deltatime)
  // {
  //   Box* box1 = dynamic_cast<Box*>(world::get_object_by_id(0));
  //   Box* box2 = dynamic_cast<Box*>(world::get_object_by_id(1));

  //   box1->drawmode = GL_TRIANGLES;
  //   if(collision_detection::basic_hitbox(box1, box2))
  //     box1->drawmode = GL_LINE_LOOP;
  // }

  // void render(Shader* shader)
  // {
  //   glClearColor(1.f, 1.f, 1.f, 1.f);
  //   glClear(GL_COLOR_BUFFER_BIT);    
    
  //   for(auto it = World::world_objects.begin(); it != World::world_objects.end(); ++it)
  //   {
  //     Box* box = dynamic_cast<Box*>(it->second);
  //     box->render(shader);
  //   }

  //   renderImGui();

  //   window.swapBuffers();
  // }


}