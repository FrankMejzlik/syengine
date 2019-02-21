#pragma once

/**
 * Settings for Components and their management.
 */

#define COMPONENTS_NUM_SLOTS 10

#define COMPONENT_SLOT_SINGLETONS 1, 2, 3, 4, 5, 7, 8
#define COMPONENT_SLOT_SINGLETONS_COUNT 7

/** List of slots that can have only one Component */
constexpr size_t gSingletonSlots[] = { COMPONENT_SLOT_SINGLETONS };

/** Transform slot */
#define COMPONENT_TRANSFORM_SLOT 1

/** Slot for directional light source */
#define COMPONENT_DIRECTIONAL_LIGHT_SOURCE_SLOT 2

/** Slot for omnidirectional light source */
#define COMPONENT_POINT_LIGHT_SOURCE_SLOT 3

/** Slot for omnidirectional light source */
#define COMPONENT_SPOT_LIGHT_SOURCE_SLOT 4

/** Standard behavioral scripts */
#define COMPONENT_SCRIPT_HANDLER_SLOT 5

/** Camera slot */
#define COMPONENT_CAMERA_SLOT 6

/** Physical bodies (Rigidbody, Softbody, ...) */
#define COMPONENT_PHYSICS_BODY_SLOT 7

/** Physics colliders (BlockCollider, MeshCollider, ...) */
#define COMPONENT_PHYSICS_COLLIDER_SLOT 8

/** MeshRenderers */
#define COMPONENT_MESH_RENDERER_SLOT 9
