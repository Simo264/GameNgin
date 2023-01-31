#include "../include/core_minimal.h"
#include "../include/gamengin.h"


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

    Box* box1 = dynamic_cast<Box*>(world::get_object_by_id(0));

    // press ESC
    if (window.getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
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
    Box* box1 = dynamic_cast<Box*>(world::get_object_by_id(0));
    Box* box2 = dynamic_cast<Box*>(world::get_object_by_id(1));

    box1->drawmode = GL_TRIANGLES;
    if(collision_detection::basic_hitbox(box1, box2))
      box1->drawmode = GL_LINE_LOOP;
  }

  void render(Shader* shader)
  {
    window.render(200, 100, 255);

    world::render(shader);

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
    ImGui_ImplOpenGL3_Init("#version 130");
  }

  void renderImGui()
  {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Hello, world!");                          
    ImGui::Text("This is some useful text.");               
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

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