@page engine_concepts Engine concepts

@section basic_scene_composition Basic Scene composition

Game (**Scene**) consists of **Entities**.  
Entities are defined by their [Primary Components](@ref primary_components), Entity without Components is nothing but useless data in memory.  
[Primary Components](@ref primary_components) are specific classes with specific functionalities and responsibilities. Some of them have [SubComponents](@ref sub_components) attached to them.  

@subsection example_hierarchy "Example hierarchy"
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

@subsection engine_diagram Engine Scene/Entity/Component diagram

@image html engine_composition_diagram.jpg "Engine composition"

@subsection primary_components Primary Components

- @ref SYE::Transform "Transform"
- @ref SYE::MeshRenderer "MeshRenderer"
- @ref SYE::Camera "Camera"
- @ref SYE::Rigidbody "Rigidbody"
- @ref SYE::ScriptHandler "ScriptHandler"
- @ref SYE::DirectionalLight "DirectionalLight"
- @ref SYE::SpotLight "SpotLight"
- @ref SYE::PointLight "PointLight"


@subsection sub_components SubComponents

- @ref SYE::Collider "Collider"
- @ref SYE::Script "Script"
- @ref SYE::Camera "Camera"
- @ref SYE::Shininess "Shininess"
- @ref SYE::Texture "Texture"

@note There are implemented some shorthands for frequently used standard Entities like Camera, Block, Sphere etc. You can find Create{Something} methods in @ref SYE::Scene class.


