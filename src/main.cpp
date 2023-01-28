#include "../include/core_minimal.h"

#include "../include/logger.h"
#include "../include/window.h"
#include "../include/world.h"
#include "../include/shader.h"

#include "../include/box.h"
#include "../include/collision_detection.h"


// Window config
#define WINDOW_WIDTH  720
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE  "GameNgin"

// deltaTime variables
// -------------------
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// boxes
// -------------------
Box* box1 = nullptr;
Box* box2 = nullptr;
static void input_callback(Window* window);

int main()
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
  
  Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

  // glew: init
  // ----------------
  if(glewInit() != GLEW_OK)
  {
    LOG_ERROR("Error on init GLEW");
    glfwTerminate();
    return -1;
  }
  LOG_TRACE("GLEW initialized successfully");



  Shader shader("../shaders/vertex.shader", "../shaders/fragment.shader");
  LOG_TRACE("Shaders loaded successfully");

  box1 = new Box(glm::vec2{ 50,50 }, glm::vec2{ 0,0 });
  box2 = new Box(glm::vec2{ 50,50 }, glm::vec2{ 300,200 });

  world::insert_object(box1);
  world::insert_object(box2);

  while (!window.shouldClose())
  {
    // calculate delta time
    // --------------------
    const double currentFrame = static_cast<double>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    world::world_time = currentFrame;

    // input
    // ------
    window.processInput(input_callback);
    glfwPollEvents();

    // update state
    // ------
    uint32_t drawmode = GL_TRIANGLES;
    if(collision_detection::basic_hitbox(box1, box2))
      drawmode = GL_LINE_LOOP;

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
    window.render(100.f, 255.f, 0.f);
    box1->render(&shader, drawmode);
    box2->render(&shader);
    
    // for(auto it = world::world_objects.begin(); it != world::world_objects.end(); ++it)
    // {
    //   Box* b = dynamic_cast<Box*>(it->second);
    //   if(b)
    //   {
    //     b->render(&shader);
    //   }
    // }



    // Swap front and back buffers 
    window.swapBuffers();
  }

  glfwTerminate();

  return 0;
}

void input_callback(Window* window)
{
  if (window->getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    window->close();
    return;
  }
  
  if(window->getKey(GLFW_KEY_A) == GLFW_PRESS)
  {
    box1->position.x -= 2 * (deltaTime*100);
    return;
  }

  if(window->getKey(GLFW_KEY_D) == GLFW_PRESS)
  {
    box1->position.x += 2 * (deltaTime*100);
    return;
  }

  if(window->getKey(GLFW_KEY_W) == GLFW_PRESS)
  {
    box1->position.y -= 2 * (deltaTime*100) ;
    return;
  }

  if(window->getKey(GLFW_KEY_S) == GLFW_PRESS)
  {
    box1->position.y += 2 * (deltaTime*100);
    return;
  }
}


