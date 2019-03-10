@page manual Manual

@subpage building_syengine "Building SYEngine"  
@subpage engine_concepts "Engine concepts"  
@subpage scripting_your_game "Scripting your game"  


@page building_syengine Building SYEngine

@note
    For now SYEngine sources are available only for MSVC compiler and Visual Studio IDE and result executables only for Windows 7+ OS.

@section msvc MSVC

-# Checkout [SYEngine repository](https://gitlab.com/sye-tech/SYEngine) to your computer.
-# Download [externals](http://devwesp.com/download/external.zip)
    -# Extract `external` directory into 'SYEngine' directory inside repository directory (e.g. `C:/SYEngine/SYEngine/`) so `external` directory lies next to 'SYEngine.vcxproj' file.
-# Download [resources](http://devwesp.com/download/resource.zip)
    -# Extract 'resource' directory into 'SYEngine' directory inside repository directory (e.g. `C:/SYEngine/SYEngine/`) so `resource` directory lies next to 'SYEngine.vcxproj' file.
-# Inside `{repo_root}/SYEngine/` create **'{repo_root}/SYEngine/Game/'** directory and place there some game logic.
    -# Good starting point are our examples (`{repo_root}/examples`) - just choose example open it's directory and **copy all contents into `{repo_root}/SYEngine/Game/` directory**.
    -# Inside `{repo_root}/SYEngine/Game/` there must be `{repo_root}/SYEngine/Game/scripts/` directory with `**_SceneBuilder.h**` file, which contains implementation of _SceneBuilder class that inherits from SYE::_SceneBuilderBase.
    -# Inside `{repo_root}/SYEngine/Game/` there also should be file `**game_script_includes.h**` that includes Scripts you want to use (both yours and those we provided with engine).

-# Build and run.

It should compile without any errors or warnings and game whose logic you copied inside 'Game' directory sould be running.

@note Sometimes it is necessary to manualy recompile 'SceneManager.cpp' source, because VS won't see any changes in files.

## Now you have two choices:
-# You don't plan to edit any of engine code
-# You want to extend/edit/remove sone of engine code

### 1) Just scripting
If so, feel free to create your own repository inside 'Game' directory and version control your code. When new version of SYEngine comes out you just pull new version and that's it.

@note Maybe you'd need to 'Include into project' your files, because they won't be present in newly pulled .vcproj file.

### 2) Edit engine code
If you want to extend/edit/remove engine code, feel free to do so, but remember that when we release new version of engine, updating your code will be very complicated.

