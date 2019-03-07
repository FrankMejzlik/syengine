# SYEngine
(Yet) very basic 3D game engine that allows you to conviniently script your game just using prepared API engine calls. Scripting language is C++ and scripts are just classes you can attach to any Entity (to it's ScriptHandler Component).

In scripts, you have access to all Managers and primary Components, that are attached to certain Entity, therefore you're free to code whatever behaviour you need.

# Brief scripting concepts
Game (**Scene**) consists of **Entities**.
Entities are defined by their **Primary Components**, Entity without Components is nothing but useless data in memory.
Primary Components are specific classes with specific functionalities and responsibilities and can have **SubComponents**

### Example hierarchy
ENTITY
    -> Transform
    -> MeshRenderer
    ------>> Mesh
    ------>> Material
    ---------->>> Texture
    ---------->>> Shininess
    ---------->>> Shader
    -> Rigidbody
    ------>> SphereCollider
    ---------->>> Mesh
    -> ScriptHandler
        ------->> BallController (inherits from Script class)

### Current Primary Components:
##### Transform
##### Camera
##### MeshRenderer
##### ScriptHandler
##### Rigidbody


*There are implemented some shorthands for frequently used standard Entities like Camera, Block, Sphere etc. You can find **Create{Something}** methods in [Scene class](docs/auto/index.html).*


