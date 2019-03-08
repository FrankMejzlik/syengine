Manual {#manual}
======

- @subpage building_syengine Building SYEngine
- @subpage engine_concepts Engine concepts
- @subpage scripting_your_game Scripting your game


@page building_syengine Building SYEngine

@note
    For now SYEngine sources are available only for MSVC compiler and Visual Studio IDE and result executables only for Windows 7+ OS.

# MSVC
1) Checkout repository to your computer
2) Download [externals](http://devwesp.com/download/external.zip)
    a) Extract 'external' directory into 'SYEngine' directory inside repository directory (e.g. C:/SYEngine/SYEngine/) so 'external' directory lies next to 'SYEngine.vcxproj' file.
3) Download [resources](http://devwesp.com/download/resource.zip)
    a) Extract 'resource' directory into 'SYEngine' directory inside repository directory (e.g. C:/SYEngine/SYEngine/) so 'resource' directory lies next to 'SYEngine.vcxproj' file.



@page engine_concepts Engine concepts
# Brief concepts
Game (**Scene**) consists of **Entities**.
Entities are defined by their **Primary Components**, Entity without Components is nothing but useless data in memory.
Primary Components are specific classes with specific functionalities and responsibilities and can have **SubComponents**

## Example hierarchy
- Entity
    - Transform
    - MeshRenderer
        - Mesh
        - Material
            - Texture
            - Shininess
            - Shader
        - Rigidbody
        - SphereCollider
            - Mesh
        - ScriptHandler
            - BallController (inherits from Script class)

## Primary Components:
### Transform
### Camera
### MeshRenderer
### ScriptHandler
### Rigidbody

*There are implemented some shorthands for frequently used standard Entities like Camera, Block, Sphere etc. You can find **Create{Something}** methods in [Scene class](docs/auto/html/class_s_y_e_1_1_scene.html).*

@page scripting_your_game Scripting your game
