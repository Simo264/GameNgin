#include "include/core_minimal.h"
#include "include/gamengin.h"
#include "include/resource_manager.h"

#include "include/globals.h"
#include "include/logger.h"
#include "include/world.h"
#include "include/box.h"
#include "include/collision_detection.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define WINDOW_TITLE  "GameNgin"

static int color[3] = { 255,255,255 };

namespace GameNgin
{
  Window window = Window(vec2ui(WINDOW_WIDTH, WINDOW_HEIGH), WINDOW_TITLE);
  bool gameloop = true;

  void initGL()
  {
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      LOG_ERROR("Failed to initialize GLAD");
      exit(EXIT_FAILURE);
    }    
  }

  void input(double deltatime)
  {
    glfwPollEvents();

    Box* box1 = dynamic_cast<Box*>(World::getObjectByID(0));
    float velocity = 250.f * deltatime;

    // Close window
    if (window.getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS || window.shouldClose())
    {
      gameloop = false; // end of game loop
      window.close(); 
      return;
    }

    // press W
    if (window.getKey(GLFW_KEY_W) == GLFW_PRESS)
    {
      box1->position.y -= velocity;
      return;
    }
    
    // press A
    if (window.getKey(GLFW_KEY_A) == GLFW_PRESS)
    {
      box1->position.x -= velocity;
      return;
    }
    
    // press S
    if (window.getKey(GLFW_KEY_S) == GLFW_PRESS)
    {
      box1->position.y += velocity;
      return;
    }
    
    // press D
    if (window.getKey(GLFW_KEY_D) == GLFW_PRESS)
    {
      box1->position.x += velocity;
      return;
    }

  }

  void update(double deltatime)
  {
    // Box* box1 = dynamic_cast<Box*>(world::get_object_by_id(0));
    // Box* box2 = dynamic_cast<Box*>(world::get_object_by_id(1));

    // box1->drawmode = GL_TRIANGLES;
    // if(collision_detection::basic_hitbox(box1, box2))
    //   box1->drawmode = GL_LINE_LOOP;
  }

  void render(Shader* shader)
  {
    glClearColor(1.f, 1.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);    
    
    for(auto it = World::world_objects.begin(); it != World::world_objects.end(); ++it)
    {
      Box* box = dynamic_cast<Box*>(it->second);
      box->render(shader);
    }

    renderImGui();

    window.swapBuffers();
  }

  void free()
  {
    World::free();
    ResourceManager::free();
    glfwTerminate();
  }


  void initImGui()
  {
    // // Setup Dear ImGui context
    // IMGUI_CHECKVERSION();
    // ImGui::CreateContext();
    // ImGuiIO& io = ImGui::GetIO(); (void)io;
    // //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // // Setup Dear ImGui style
    // ImGui::StyleColorsDark();

    // // Setup Platform/Renderer backends
    // ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
    // ImGui_ImplOpenGL3_Init("#version 450");
  }

  void renderImGui()
  {
    // Box* box = dynamic_cast<Box*>(World::getObjectByID(0));
    
    // ImGui_ImplOpenGL3_NewFrame();
    // ImGui_ImplGlfw_NewFrame();
    // ImGui::NewFrame();
    // ImGui::SetWindowSize(ImVec2(200, 720));
    // if(ImGui::Begin("Hello, world!"))
    // {
    //   ImGui::SliderInt3("Box color", color, 0, 255);
      
    //   // color8_t col8t;
    //   // std::copy(color, color + 3, col8t.begin());
    //   // box->setColor(col8t);

    //   ImGui::End();
    // }                          

    // // Rendering
    // ImGui::Render();
    // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  void destroyImGui()
  {
    // ImGui_ImplOpenGL3_Shutdown();
    // ImGui_ImplGlfw_Shutdown();
    // ImGui::DestroyContext();
  }

}