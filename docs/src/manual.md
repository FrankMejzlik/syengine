@page manual Manual

@subpage roadmap "Roadmap"  
@subpage building_syengine "Building SYEngine"  
@subpage engine_concepts "Engine concepts"  
@subpage scripting_your_game "Scripting your game"  
@subpage examples "Examples" 

@page roadmap Roadmap

@note I will appreciate any advice or feedback you could provide. Down below are major thing I am well aware of so you don't have to report them.

@section known_issues  Known issues

- Low performance of dynamic lights .
    - I use standard shadow mapping technique with PCF for soft shadows without any optimizations.
    - I will address this with implementing variance shadow mapping and/or deferred shading.
- I am not doing any runtime error solving.
    - I have error queue on every instance that inherits from IErrorLogging, so it allows me to solve problems locally if it's possible.
    - This is just for future, for now I am just reporting those errors to stdout.


@section future_efforts  Future efforts

@note Those are just few things I will work on in near future

-# Variance shadow mapping (in progress in own branch)
-# Defferred shading
-# Support for model loading (I have it working but not in new architecture)
-# Skeletal animation
-# Text rendering
-# Implement UI
-# Visual scene editor
-# Scene export to file

And everything else engine will need... 




@page building_syengine Building SYEngine

@note
    For now SYEngine sources are available only for MSVC compiler and Visual Studio IDE and result executables only for Windows 7+ OS.

@section msvc MSVC

-# Checkout [SYEngine repository](https://gitlab.com/devWeSp/syengine) to your computer.
-# Download [externals](http://devwesp.com/download/external.zip)
    -# Extract `external` directory into 'SYEngine' directory inside repository directory (e.g. `C:/SYEngine/SYEngine/`) so `external` directory lies next to 'SYEngine.vcxproj' file.
-# Download [resources](http://devwesp.com/download/resource.zip)
    -# Extract 'resource' directory into 'SYEngine' directory inside repository directory (e.g. `C:/SYEngine/SYEngine/`) so `resource` directory lies next to 'SYEngine.vcxproj' file.
-# Inside `{repo_root}/SYEngine/` create 'Game' directory and place there some game logic.
    -# Good starting point are our examples (`{repo_root}/examples/{exmaple_name}`) - just choose example open it's directory and **copy all contents of example directory** into `{repo_root}/SYEngine/Game/`.

@note
    -# Inside `{repo_root}/SYEngine/Game/` there must be `scripts` directory with `_SceneBuilder.h` file, which contains implementation of _SceneBuilder class that inherits from SYE::_SceneBuilderBase.
    -# Inside `{repo_root}/SYEngine/Game/` there also should be file `game_script_includes.h` that includes Scripts you want to use (both yours and those we provided with engine).

-# Build and run.

Project folder structure should look something like:  
@code
SYEngine/ 
├── Diagnostics/ 
│   └── ...  
├── Engine/  
│   └── ...  
├── .  
├── .  
├── .  
├── Game/  
│   ├── scripts/  
│   │   ├── _SceneBuilder.h  
│   │   ├── game_script_includes.h  
│   │   ├── ... (your other scripts)  
│   │  
│   └── (arbitrary your file structure)  
├── .  
├── .  
├── .  
├── resource/  
│   └── ...  
├── shaders/  
│   └── ...  
├── imgui.ini  
├── main.cpp  
├── .  
├── .  
├── .  
├── SYEngine.vcxproj.filters  
└── SYEngine.vcxproj.user  
@endcode

It should compile without any errors or warnings and game whose logic you copied inside 'Game' directory should be running.

@note Sometimes it is necessary to manually recompile 'SceneManager.cpp' source, because VS won't see any changes in files.

## Now you have two choices:
-# You don't plan to edit any of engine code
-# You want to extend/edit/remove sonme of engine code

### 1) Just scripting
If so, feel free to create your own repository inside 'Game' directory and version control your code. When new version of SYEngine comes out you just pull new version and that's it.

@note Maybe you'd need to 'Include into project' your files, because they won't be present in newly pulled .vcproj file.

### 2) Edit engine code
If you want to extend/edit/remove engine code, feel free to do so, but remember that when we release new version of engine, updating your code will be very complicated.


@page examples Examples

In all examples there is Script called GeneralInputHandler that provides:
- F1: Turn on debug physics collision geometry rendering
- F2: Turn on debug physics AABB bounding boxex rendering

@note Those are quite performance expensive since they are pushed and deleted from GPU memory each frame.

@section hello_syengine  HelloSYEngine

Basic startup application that can be used as your startup project. Nothing really interesting there, just one camera and empty space.


@section basic_terrain  BasicTerrain
Example of rendering proceduraly generated data you send in as vertex data. You can fly over with spot light attached to your Camera.

@section pinball  Pinball3D
3D pinball game everybody knows. Goal is to keep ball in game as long as possible and make it as much hitters as possible - this increases your score (that you cannot see right know because I have to implement UI Manager yet).

Controls:
- B: Hold B to accumulate incrasing force to throw your ball into game
- R: Resets ball position if it falls out (this is cheating though!)
- F: Toggles between Action and Free (WASD, Space and Shift + Space with mouse movement) camera
- Left/Right arrow: Controls left and right paddle
