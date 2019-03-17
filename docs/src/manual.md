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
- There may be some memory leaks in third party libs (assimp, etc).
    - Some parts of code are untouched since I wrote them initially and at the time I was way way worse C++ programmer then now.
    - In newer code I don't use owner raw pointer so there shouldn't be any leaks.
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

-# Checkout [SYEngine repository](https://gitlab.com/sye-tech/SYEngine) to your computer.
-# Download [externals](http://devwesp.com/download/external.zip)
    -# Extract `external` directory into 'SYEngine' directory inside repository directory (e.g. `C:/SYEngine/SYEngine/`) so `external` directory lies next to 'SYEngine.vcxproj' file.
-# Download [resources](http://devwesp.com/download/resource.zip)
    -# Extract 'resource' directory into 'SYEngine' directory inside repository directory (e.g. `C:/SYEngine/SYEngine/`) so `resource` directory lies next to 'SYEngine.vcxproj' file.
-# Inside `{repo_root}/SYEngine/` create '{repo_root}/SYEngine/Game/' directory and place there some game logic.
    -# Good starting point are our examples (`{repo_root}/examples`) - just choose example open it's directory and **copy all contents into `{repo_root}/SYEngine/Game/` directory**.

@note
    -# Inside `{repo_root}/SYEngine/Game/` there must be `{repo_root}/SYEngine/Game/scripts/` directory with `_SceneBuilder.h` file, which contains implementation of _SceneBuilder class that inherits from SYE::_SceneBuilderBase.
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

@section hello_syengine  HelloSYEngine

@section basic_terrain  BasicTerrain
Just example of rendering proceduraly generated data you send in as vertex data.

@section pinball  Pinball3D