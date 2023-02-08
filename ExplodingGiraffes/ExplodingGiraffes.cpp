#include <cstdlib>
#include <iostream>

#include "application.h"

/* ------------------------------------------------------------------------------------------------------------------
 * Dear ImGui demo.
 *-----------------------------------------------------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
  giraffe::Application application;

  std::cout << "Initializing Exploding Giraffes and its subsystems: We have ignition\n";
  bool success = application.Init();
  if (!success) {
    std::cerr << "Exploding Giraffes initialization failed: Boom\n";
    return EXIT_FAILURE;
  }

  std::cout << "Running the Exploding Giraffes event and rendering loop: Go\n";
  application.Run();

  std::cout << "Shutting down Exploding Giraffes and its subsystems: Good bye\n";
  application.Shutdown();

  return EXIT_SUCCESS;
}
