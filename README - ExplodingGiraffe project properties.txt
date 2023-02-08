==== External Dependency Versions ====

Versions of the dependencies in ExplodingGiraffe's "extern" directory:

GLFW 3.3.8
ImGui 1.89.1

==== Project Properties ====

Changes made to the ExplodingGiraffes Visual Studio 2022 project:

+ Configuration Properties
  + General
    - C++ Language Standard: ISO C++ Standard (/std:c++20)
    + VC++ Directories
      - Include Directories
        ..\extern
        ..\extern\glad\include
        ..\extern\glfw-3.3.8.bin.WIN64\include
	..\extern\imgui
        ..\shaders
      - Library Directories
        ..\extern\glfw-3.3.8.bin.WIN64\lib-vc2022

+ Linker
  + Input
    - Additional Dependencies:
      opengl32.lib
      glfw3.lib

+ Source Files
  + Glad
    Add glad.c to the project from ExplodingGiraffes\extern\glad\src

  + ImGui
    Add the files below to the project from ExplodingGiraffes\extern\imgui
    imgui.cpp
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_impl_glfw.cpp
    imgui_impl_opengl3.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
