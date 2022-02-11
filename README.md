
> This is quite an old project where I practised basic principles of 3D game engines. This engine has basic physics implemented as well as a form of scripting the game logic without modifying the engine itself. The built-in example is a pinball game which you can control using left/right arrows and B for firing the ball.

# SYEngine
(Yet) very basic 3D game engine that allows you to conviniently script your game just using prepared API engine calls. Scripting language is C++ and scripts are just classes you can attach to any Entity (to it's ScriptHandler Component).

In scripts, you have access to all Managers and primary Components, that are attached to certain Entity, therefore you're free to code whatever behaviour you need.

## Build
Use CMake to generate the project and then just build it with your favourite build system. 

For example on Windows:
```sh
mkdir build && cd build
cmake .. -G "Visual Studio 16 2019" -A x64
cmake --build . --config Release
cmake --install . --config Release
```

For example on UNIX systems:
```sh
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

> You my need to copy the `SYEngine/resource/` directory next to the executable.

## Development notice
This engine is not top priority project for us. It is more of a playgound for us in sense that it is used primarily for learning purposes and it is "just" long term project that we will push forward from time to time and maybe in future it will even become useful.

## Documentation
All documentation is present `/docs/html/index.html` in repository.
