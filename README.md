# Cube-Running-Game
A game made using OpenGL 3.3 about a cube trying to avoid obstacles ahead.
===============================================================================
This project has two main parts:
- The game engine.
- The Game launcher.
===============================================================================
#The Game Engine
The game used the "Basic-3D-Game-Engine" as a base. Link https://github.com/MsherifAr/Basic-3D-Game-Engine.
it's a simple 3D game engine written with C++ and OpenGL 3.3.
In the CubeRunningGameEngine folder, there is a visual studio 2019 .sln project.
The project is set to release for x86 32-bit, and compilation is simply done by pressing F5.
An executable will be generated in the release folder called "GameEngine.exe", and it can be used as it is provided
that all the assets and the settings.conf file are available.
===============================================================================
#The Game Launcher
It's a Windows Forms app project, using .NET 2.0 as a runtime. it simply modifies the settings.conf file
and launches the game. the game reads the settings.conf contents to determine the screen resolution,
full screen mode, vsync, software rendering, and level. It needs to be reminded that the "GameEngine.exe"
must be renamed to "engine.bin" and put into two folders: Software, and Hardware.
Note: Software must include an "opengl32.dll" in order to work with software rendering.
it could be downloaded from here https://fdossena.com/?p=mesa/index.frag
