#include "application.h"

#include <cstdlib>
#include <iostream>

#include <glad/glad.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace {

// TODO: Move this function out of application.cpp
void CreateTriangle(GLuint& out_vao, GLuint& out_vbo, GLuint& out_ebo) {
  const GLsizei NUMBER_OF_OBJECTS = 1;

  float vertices[] = {
    0.0f,   0.25f,  0.0f, // position vertex 1
    1.0f,   0.0f,   0.0f,	// color vertex 1
    0.25f,  -0.25f, 0.0f, // position vertex 2
    0.0f,   1.0f,   0.0f,	// color vertex 2
    -0.25f, -0.25f, 0.0f, // position vertex 3
    0.0f,   0.0f,   1.0f,	// color vertex 3
  };
  unsigned int indices[] = {0, 1, 2};

  // Create the OpenGL buffers needed for the triangle.
  glGenVertexArrays(NUMBER_OF_OBJECTS, &out_vao);
  glGenBuffers(NUMBER_OF_OBJECTS, &out_vbo);
  glGenBuffers(NUMBER_OF_OBJECTS, &out_ebo);

  // Bind the VAO (Vertext Array Object), which contains our VBO.
  glBindVertexArray(out_vao);

  // Bind the VBO (Vertex Buffer Object), which contains our vertex data.
  glBindBuffer(GL_ARRAY_BUFFER, out_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Bind the EBO (Element Buffer Object), which describes which vertices to draw.
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, out_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // Define the triangle's position attributes.
  glVertexAttribPointer(
    (GLuint)0,
    (GLint)3,
    GL_FLOAT,
    GL_FALSE,
    (GLsizei)6 * sizeof(float),
    (void*)0
  );
  glEnableVertexAttribArray(0);

  // Definte the triangle's color attributes.
  glVertexAttribPointer(
    (GLuint)1,
    (GLint)3,
    GL_FLOAT,
    GL_FALSE,
    (GLsizei)6 * sizeof(float),
    (void*)(3 * sizeof(float))
  );
  glEnableVertexAttribArray(1);

  // Unbind our OpenGL objects.
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

}

namespace giraffe {

Application::Application() noexcept { }

Application::~Application() {
  if (!did_shutdown_) {
    Shutdown();
  }
}

bool Application::Init(const InitialState& initial_state) {
  if (!InitGlfw()) {
    std::cerr << "Unable to intialize GLFW\n";
    return false;
  }

  if (!InitGlfwWindow(initial_state)) {
    std::cerr << "Unable to create the GLFW window\n";
    return false;
  }

  if (!InitGlad()) {
    std::cerr << "Unable to initialize GLAD\n";
    return false;
  }

  if (!InitImGui()) {
    std::cerr << "Unable to initialize ImGui\n";
    return false;
  }

  return true;
}

void Application::Run() {
  // TODO: Ideally, OpenGL and shader program initialization will be moved out of this method....
  GLuint vao = 0;
  GLuint vbo = 0;
  GLuint ebo = 0;
  CreateTriangle(vao, vbo, ebo);
  bool success = glsl_triangle_program.Init("resources/shaders/triangle_shader.vs", "resources/shaders/triangle_shader.fs");
  if (!success) {
    std::cerr << "Unable to create the triangle shader\n";
    exit(EXIT_FAILURE);
  }

  while (!glfwWindowShouldClose(glfw_window_)) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // TODO: Use shader program here.

    BuildUi();

    ImGui::Render();

    int width = 0;
    int height = 0;
    glfwGetFramebufferSize(glfw_window_, &width, &height);

    glViewport(0, 0, width, height);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      GLFWwindow* glfw_current_context_window = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(glfw_current_context_window);
    }

    glfwSwapBuffers(glfw_window_);
  }
}

void Application::Shutdown() {
  if (!did_shutdown_) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(glfw_window_);
    glfwTerminate();

    did_shutdown_ = true;
  }
}

void Application::SetWindowPosition(int x, int y) {
  glfwSetWindowPos(glfw_window_, x, y);
}

void Application::BuildUi() {
  ImGui::Begin("Properties");
  ImGui::Text("This is a floating Exploding Giraffes properties window with nothing in it but this text for now");
  ImGui::End();
}

bool Application::InitGlad() {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    return false;
  }

  return true;
}

bool Application::InitGlfw() {
  glfwSetErrorCallback(Application::HandleGlfwError);

  if (!glfwInit()) {
    return false;
  }

  return true;
}

bool Application::InitGlfwWindow(const InitialState& initial_state) {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfw_window_ = glfwCreateWindow(
    initial_state.window_width,
    initial_state.window_height,
    initial_state.window_title.c_str(),
    nullptr,
    nullptr
  );
  if (glfw_window_ == nullptr) {
    return false;
  }

  glfwMakeContextCurrent(glfw_window_);
  glfwSwapInterval(1);

  glfwSetFramebufferSizeCallback(glfw_window_, HandleGlfwWindowResize);

  SetWindowPosition(initial_state.window_position_x, initial_state.window_position_y);

  return true;
}

bool Application::InitImGui() {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO& io = ImGui::GetIO();

  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;     // enable multi-viewport / platform windows
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;       // enable docking
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // enable keyboard input
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // enable gamepad input

  io.Fonts->AddFontFromFileTTF("resources/fonts/Roboto-Medium.ttf", 24.0f);

  ImGui::StyleColorsDark();

  if (!ImGui_ImplGlfw_InitForOpenGL(glfw_window_, true)) {
    return false;
  }

  if (!ImGui_ImplOpenGL3_Init()) {
    return false;
  }

  return true;
}

void Application::HandleGlfwError(int error, const char* description) {
  std::cerr << "GLFW error: " << description << " (" << error << ")\n";
}

void Application::HandleGlfwWindowResize(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

}
