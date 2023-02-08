Exploding Giraffes
=====

Demonstrates using OpenGL, GLFW, and ImGui together to build an application.

You can use `README - ExplodingGiraffe project properties.txt` for ideas on how you might want to structure your own project using these libraries and VS build events.

Note: Exploding Giraffes has its VS solution and project files in different directories for flexibility (e.g., we want the solution to encompass different projects that all rely upon the libraries in `extern`.) There is nothing specific to GLFW, ImGui, etc. dictating this structure.

### Motivation

I wanted to create an application using ImGui to learn how a project would be started from scratch instead of relying heavily upon code in ImGui's [examples](https://github.com/ocornut/imgui/tree/master/examples) directory.

Then when the time came to start a larger project, I wouldn't be spending a lot of time up front learning how to integrate ImGui -- this project accomplished that initial goal.

### Roadmap

Next task: complete work on the `GlslVFProgram` class. Then create an OpenGL shader program that can be manipulated using ImGui.

At one point I was considering expanding this project to include:
- Loading meshes with Assimp
- Using a scene graph
- Integrating a physics engine
- Profiling using EasyProfiler and Optick

However, I think that a future game engine would be multithreaded from the start, using an architecture similar to what is discussed in [Multithreading for Game Engines](https://vkguide.dev/docs/extra-chapter/multithreading/), rather than starting with a GLFW event loop.
