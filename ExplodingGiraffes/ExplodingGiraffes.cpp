#include <cstdlib>
#include <iostream>

#include "application.h"

/* ------------------------------------------------------------------------------------------------------------------
 * Demonstrates using OpenGL, GLFW, and ImGui together to build an application.
 *-----------------------------------------------------------------------------------------------------------------*/

giraffe::Application application;

void HandleApplicationShutdown() {
  std::cout << "Shutting down Exploding Giraffes and its subsystems: Good bye\n";
  application.Shutdown();
}

int main(int argc, char* argv[]) {
  std::atexit(HandleApplicationShutdown);

  std::cout << "Initializing Exploding Giraffes and its subsystems: We have ignition\n";
  bool success = application.Init();
  if (!success) {
    std::cerr << "Exploding Giraffes initialization failed: Boom\n";
    return EXIT_FAILURE;
  }

  std::cout << "Running the Exploding Giraffes event and rendering loop: Go\n";
  application.Run();

  return EXIT_SUCCESS;
}
