#include "engine/core/core.h"

#include "game_manager.h"
#include "window_manager.h"
#include "shader_manager.h"
#include "render_manager.h"

#include "engine/core/shader/shader.h"
#include "engine/world.h"
#include "engine/box.h"

extern gn::World gWorld;

namespace gn
{
  void GameManager::run()
  {
    while (gameloop && !WindowManager::getInstance().shouldClose())
    {
      // calculate delta time
      // --------------------
      currentFrame = static_cast<double>(glfwGetTime());
      deltatime = currentFrame - lastFrame;
      lastFrame = currentFrame;

      input(deltatime);
      update(deltatime);
      render();

      // Swap front and back buffers 
      WindowManager::getInstance().swapBuffers();
    }
    
  }
  
  void GameManager::input(double deltatime)
  {
    // Poll for and process events 
    glfwPollEvents();
    
    // Close window
    if (WindowManager::getInstance().getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
      WindowManager::getInstance().close(); 
      return;
    }

    // Box* box = dynamic_cast<Box*>(gWorld.getObjectByID(1));

    // // press W
    // if (WindowManager::getInstance().getKey(GLFW_KEY_W) == GLFW_PRESS)
    // {
    //   box->translate(vec2(0.f, 2.f * (deltatime*100)));
    //   return;
    // }
    
    // // press A
    // if (WindowManager::getInstance().getKey(GLFW_KEY_A) == GLFW_PRESS)
    // {
    //   box->translate(vec2(-2.f * (deltatime*100), 0.f));
    //   return;
    // }
    
    // // press S
    // if (WindowManager::getInstance().getKey(GLFW_KEY_S) == GLFW_PRESS)
    // {
    //   box->translate(vec2(0.f, -2.f * (deltatime*100)));
    //   return;
    // }
    
    // // press D
    // if (WindowManager::getInstance().getKey(GLFW_KEY_D) == GLFW_PRESS)
    // {
    //   box->translate(vec2(2.f * (deltatime*100), 0.f));
    //   return;
    // }
  }
  
  void GameManager::update(double deltatime)
  {
    
  }

  void GameManager::render()
  {
    glClearColor(1.f, 1.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    // render world objects
    // ----------------------------
    gWorld.render(ShaderManager::getInstance().getShader("texture.shader"));


    // render window GUI
    // ----------------------------
    WindowManager::getInstance().renderGUI();
  }

}