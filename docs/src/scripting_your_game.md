@page scripting_your_game Scripting your game

@note At this point you should have some demo engine with some example game logic working. If not, just follow steps in @ref building_syengine "Building SYEngine".

Engine is designed to allow users to write whole game without need of altering any of it's code (but feel free to do so). Therefore your playground should be only `Game` directory. 

That is where whole logic of your game will exist and engine won't disturb you there in any way. You will be able to update engine with just pulling from repository in future (and maybe rewrite some calls we changed).

Inside `Game` there is `scripts` directory, where you will place all your Scripts. Scripts are just C++ classes that engine will compile and use them as you tell him to.

Beside this directory, you can do whatever you want to - create whole C++ project structures and use them in scripts or whatever.

But let's go one step at a time.

@section scripting_your_game_building_scene Initial building Scene

Before your game will be launched for the first time, you have to setup Scene properly. Scene is representing whole one game level or world.

There is special class `_SceneBuilder` inside `_SceneBuilder.h` file. This class has to override method @ref SYE::_SceneBuilderBase::SetupScene(). 

This method will be called exactly once before main game loop starts running. Use this method to place Entities into the world and to attach Components on those Entities.


@section scripting_your_game_writing_custom_scripts Writing custom scripts

Every script has to inherit from @ref SYE::Script class. This class contains important methods you can override:

@ref SYE::Script::OnInitializeScene()
    This method is called at most once when Scene is being initialized. Use this to do thing you want to do before main game loop starts.

@ref SYE::Script::OnProcessFrame()
    This method is called every frame. Use this to update game logic.

@ref SYE::Script::OnCollision()
    This method is called whenever this Physicsbody collides with something.

## Inside Script you have access to:
@note Many of those Manager aren't implemented yet.

### Managers
- @ref SYE::InputManager "InputManager"
- @ref SYE::EntityManager "EntityManager"
- @ref SYE::NetworkManager "NetworkManager"
- @ref SYE::OutputManager "OutputManager"
- @ref SYE::ScriptHandler "ScriptHandler"
- @ref SYE::SceneManager "SceneManager"
- @ref SYE::SimulationManager "SimulationManager"
- @ref SYE::AudioManager "AudioManager"
- @ref SYE::ComponentManager "ComponentManager"
- @ref SYE::KeyboardManager "KeyboardManager"
- @ref SYE::MouseManager "MouseManager"
- @ref SYE::PhysicsManager "PhysicsManager"
- @ref SYE::MaterialManager "MaterialManager"
- @ref SYE::MeshManager "MeshManager"
- @ref SYE::ShaderManager "ShaderManager"
- @ref SYE::ShadowManager "ShadowManager"
- @ref SYE::TextureManager "TextureManager"
- @ref SYE::WindowManager "WindowManager"
- @ref SYE::ModelManager "ModelManager"
- @ref SYE::UiManager "UiManager"
- @ref SYE::AiManager "AiManager"
- @ref SYE::ScriptManager "ScriptManager"

Get them using `Get{name_of_manager}Ptr()`, e.g. `GetEntityManagerPtr()`.
All getters can be found @ref SYE::IEngineContextInterface "here".

### Entity's Primary Components
- @ref SYE::Transform "Transform"
- @ref SYE::MeshRenderer "MeshRenderer"
- @ref SYE::Camera "Camera"
- @ref SYE::Rigidbody "Rigidbody"
- @ref SYE::ScriptHandler "ScriptHandler"
- @ref SYE::DirectionalLight "DirectionalLight"
- @ref SYE::SpotLight "SpotLight"
- @ref SYE::PointLight "PointLight"

Get them using `Get{name_of_component}Ptr()`, e.g. `GetTransformPtr()`.
All getters can be found @ref SYE::IComponentsInterface "here".

You can use all their public methods as you want.

@section scripting_your_game_building_scene Scene in action

When main game loop starts it will in each frame iteration loop through all active Entities and it's Components and call their "updating" methods (e.g. `OnProcessFrame()` on Scripts).

If you placed some ScriptHandlers with Scripts attached on some Entities, their `OnProcessFrame()` method will be called.


@note Take a look at our examples in `{repo_root}/examples` where you'll find well commented code that builds Scene.

@note If you want inspiration how Scripts are written, take a look inside `{repo_root}/SYEngine/scripts/` directory where our generic scripts are written.
