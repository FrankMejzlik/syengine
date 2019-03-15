#pragma once

/**
 * Include all Scripts that are going to be used
 *
 * TODO:
 *  Generate this file programically.
 */



// Adds basic movement and turning capiblites to Entity with Camera Component.
#include "FirstPersonCameraController.h"

// Right paddle logic
#include "LookAtQuad.h"

// Left paddle logic
#include "LeftPaddleController.h"

// Logic of play ball
#include "BallController.h"

// Logic for general input e.g. Esc to quit game
#include "GeneralInputHandler.h"

// Makes primitive to be always in front of main Camera
#include "LookAtQuad.h"