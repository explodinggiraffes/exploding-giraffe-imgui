#pragma once

#include <string>

#define GLFW_INCLUDE_NONE // use the OpenGL header file provided by Glad, not GLFW
#include <GLFW/glfw3.h>

#include "glsl_vf_program.h"

namespace giraffe {

struct InitialState {
  std::string window_title = "Exploding Giraffes";
  int window_width = 1920;
  int window_height = 1080;
  int window_position_x = 64;
  int window_position_y = 96;
};

/* ------------------------------------------------------------------------------------------------------------------
 * Initializes UI systems used by ExplodingGiraffes and renders a basic UI.
 *-----------------------------------------------------------------------------------------------------------------*/
class Application final {
public:
  Application() noexcept;

  Application(const Application&) = delete;
  Application& operator=(const Application&) = delete;
  Application(Application&&) = delete;
  Application& operator=(Application&&) = delete;

  ~Application();

  bool Init(const InitialState& initial_state = InitialState());

  void Run();

  void Shutdown();

  void SetWindowPosition(int x, int y);

private:
  bool InitGlad();
  bool InitGlfw();
  bool InitGlfwWindow(const InitialState& initial_state);
  bool InitImGui();

  void BuildUi();

  static void HandleGlfwError(int error, const char* description);
  static void HandleGlfwWindowResize(GLFWwindow* window, int width, int height);

  shader::GlslVFProgram glsl_triangle_program;

  GLFWwindow* glfw_window_ = nullptr;

  bool did_shutdown_ = false;
};

}
