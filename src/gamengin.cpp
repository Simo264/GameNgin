#include "../include/core_minimal.h"
#include "../include/gamengin.h"

#include "../include/globals.h"
#include "../include/logger.h"
#include "../include/world.h"
#include "../include/box.h"
#include "../include/collision_detection.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

// Default Window config
#define WINDOW_WIDTH  720
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE  "GameNgin"

static int color[3] = { 255,255,255 };

namespace GameNgin
{
  Window    window;
  bool      gameloop = true;

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

    glfwSwapInterval(1); // Enable vsync
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // glew: init
    // ----------------
    if(glewInit() != GLEW_OK)
    {
      LOG_ERROR("Error on init GLEW");
      glfwTerminate();
      exit(EXIT_FAILURE);
    }
    LOG_TRACE("GLEW initialized successfully");

    globals::window_width = WINDOW_WIDTH;
    globals::window_height = WINDOW_HEIGHT;
  
  }

  void input(double deltatime)
  {
    glfwPollEvents();

    Box* box1 = dynamic_cast<Box*>(world::get_object_by_id(0));

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
      box1->position.y -= 2 * (deltatime * 100);
      return;
    }
    
    // press A
    if (window.getKey(GLFW_KEY_A) == GLFW_PRESS)
    {
      box1->position.x -= 2 * (deltatime * 100);
      return;
    }
    
    // press S
    if (window.getKey(GLFW_KEY_S) == GLFW_PRESS)
    {
      box1->position.y += 2 * (deltatime * 100);
      return;
    }
    
    // press D
    if (window.getKey(GLFW_KEY_D) == GLFW_PRESS)
    {
      box1->position.x += 2 * (deltatime * 100);
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
    window.render(200, 100, 255);
    
    Box* box = dynamic_cast<Box*>(world::get_object_by_id(0));
    box->render(shader);

    renderImGui();

    window.swapBuffers();
  }

  void free()
  {
    world::free();
    glfwTerminate();
  }


  void initImGui()
  {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window.getWindowObj(), true);
    ImGui_ImplOpenGL3_Init("#version 450");
  }

  void renderImGui()
  {
    Box* box = dynamic_cast<Box*>(world::get_object_by_id(0));
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::SetWindowSize(ImVec2(200, 720));
    if(ImGui::Begin("Hello, world!"))
    {
      ImGui::SliderInt3("Box color", color, 0, 255);
      
      color8_t col8t;
      std::copy(color, color + 3, col8t.begin());
      box->setColor(col8t);

      ImGui::End();
    }                          

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  void destroyImGui()
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  }

}