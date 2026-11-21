# Cube-Running-Game
A game made using OpenGL 3.3 about a cube trying to avoid obstacles ahead.
This project has two main parts:
- The game engine.
- The Game launcher.

# The Game Engine

The game used the "Basic-3D-Game-Engine" as a base. Link https://github.com/MsherifAr/Basic-3D-Game-Engine.
it's a simple 3D game engine written with C++ and OpenGL 3.3.
In the CubeRunningGameEngine folder, there is a visual studio 2019 .sln project.
The project is set to release for x86 32-bit, and compilation is simply done by pressing F5.
An executable will be generated in the release folder called "GameEngine.exe", and it can be used as it is provided
that all the assets and the settings.conf file are available.

# The Game Launcher

It's a Windows Forms app project, using .NET 2.0 as a runtime. it simply modifies the settings.conf file
and launches the game. the game reads the settings.conf contents to determine the screen resolution,
full screen mode, vsync, software rendering, and level. Be reminded that the "GameEngine.exe"
must be renamed to "engine.bin" and put into two folders: Software, and Hardware.
Note: Software must include an "opengl32.dll" in order to work with software rendering.
it could be downloaded from here https://fdossena.com/?p=mesa/index.frag

# System requirements

Minimum (640x480, CPU rendering):
- CPU : Core 2 DUO or faster
- Ram : 1 GB
- GPU : *Not needed for CPU rendering
- OS : Windows 7 32-bit (Windows XP is NOT supported)

Recommended (HD 1280x720, Hardware Accelerated):
- CPU : Core i3 2nd Gen or faster
- Ram : 2 GB
- GPU : Any Graphics Card that supports OpenGL 3.3 or newer
- OS : Windows 7 64-bit (32-bit doesn't support Hardware acceleration)
