#include "../core_minimal.h"
#include "game_manager.h"
#include "window_manager.h"
#include "shader_manager.h"

#include "../shader.h"
#include "../world.h"
#include "../box.h"
#include "../logger.h"

extern gn::WindowManager gWindowManager;
extern gn::ShaderManager gShaders;
extern gn::World         gWorld;

namespace gn
{
  void GameManager::run()
  {
    while (gameloop && !gWindowManager.shouldClose())
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
      gWindowManager.swapBuffers();
    }
    
  }
  
  void GameManager::input(double deltatime)
  {
    // Poll for and process events 
    glfwPollEvents();
    
    // Close window
    if (gWindowManager.getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
      gWindowManager.close(); 
      return;
    }

    Box* box = dynamic_cast<Box*>(gWorld.getObjectByID(1));

    // press W
    if (gWindowManager.getKey(GLFW_KEY_W) == GLFW_PRESS)
    {
      box->translate(vec2(0.f, 2.f * (deltatime*100)));
      return;
    }
    
    // press A
    if (gWindowManager.getKey(GLFW_KEY_A) == GLFW_PRESS)
    {
      box->translate(vec2(-2.f * (deltatime*100), 0.f));
      return;
    }
    
    // press S
    if (gWindowManager.getKey(GLFW_KEY_S) == GLFW_PRESS)
    {
      box->translate(vec2(0.f, -2.f * (deltatime*100)));
      return;
    }
    
    // press D
    if (gWindowManager.getKey(GLFW_KEY_D) == GLFW_PRESS)
    {
      box->translate(vec2(2.f * (deltatime*100), 0.f));
      return;
    }
  }
  
  void GameManager::update(double deltatime)
  {
    
  }

  void GameManager::render()
  {
    glClearColor(1.f, 1.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    Shader* shader = gShaders.getShader("texture.shader");
    
    const auto& worldObj = gWorld.getWorldObjects();
    for(auto it = worldObj.begin(); it != worldObj.end(); ++it)
      it->second->render(shader);

    gWindowManager.IMGUIrender();
  }

}