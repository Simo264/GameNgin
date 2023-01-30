#include "../include/core_minimal.h"
#include "../include/gamengin.h"

#include "../include/logger.h"
#include "../include/world.h"
#include "../include/box.h"

// Default Window config
#define WINDOW_WIDTH  720
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE  "GameNgin"

namespace GameNgin
{
  Window window;
  bool gameloop = true;



  void initGL()
  {
    // glfw: init
    // ----------------
    if(!glfwInit())
    {
      LOG_ERROR("Error on init GLFW");
      glfwTerminate();
      exit(EXIT_FAILURE);
    }
    LOG_TRACE("GLFW initialized successfully");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  
    // glfw window
    // ----------------
    window.create(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    // glew: init
    // ----------------
    if(glewInit() != GLEW_OK)
    {
      LOG_ERROR("Error on init GLEW");
      glfwTerminate();
      exit(EXIT_FAILURE);
    }
    LOG_TRACE("GLEW initialized successfully");
  
  }// end initGL()

  void input(double deltatime)
  {
    glfwPollEvents();

    // press ESC
    if (window.getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
      gameloop = false; // end of game loop
      window.close(); 
      return;
    }
  
  

  }

  void update(double deltatime)
  {

  }

  void render(double deltatime, Shader* shader)
  {
    window.render(200, 100, 255);

    for(auto it = world::world_objects.begin(); it != world::world_objects.end(); ++it)
    {
      Box* b = dynamic_cast<Box*>(it->second);
      if(b)
        b->render(shader);

    }


    window.swapBuffers();
  }


  void free()
  {
    glfwTerminate();
  }

}