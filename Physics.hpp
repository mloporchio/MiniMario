/**
 *	@file Physics.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Definitions and parameters for the physics engine of the game
 */

#ifndef PHYSICS_H
#define PHYSICS_H

#include "Tilemap.hpp"

/** Enumerated type for representing the different directions. */
typedef enum {
	LEFT,
	RIGHT,
	UP,
	DOWN
} direction_t;

#define SIZE 32
#define GRAVITY 4.0f
#define FRICTION 0.8f
#define RUN_SPEED 15.0f
#define JUMP_SPEED 35.0f
#define FALL_SPEED 50.0f
#define BOUNCE_SPEED 20.0f

/**
 *	@brief Tells whether a tile element is solid or not
 *
 *	@param element identifier of the tilemap element
 *
 *  @return true if the element is solid, false otherwise
 */
static inline bool isCollidable(block_t element) {
	switch (element) {
		case BRICKS: return true;
		case QUESTION: return true;
		case TERRAIN: return true;
		case SOLID: return true;
		case COIN: return true;
		case PIPE_TOP_L: return true;
		case PIPE_TOP_R: return true;
		case PIPE_BOTTOM_L: return true;
		case PIPE_BOTTOM_R: return true;
		case GRASS: return true;
		default: return false;
	}
}

#endif
