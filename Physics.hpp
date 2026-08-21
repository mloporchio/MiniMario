/**
 *	@file Physics.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Definizioni e parametri della fisica del gioco
 */

#ifndef PHYSICS_H
#define PHYSICS_H

#include "tilemap.h"

/** Tipo enumerato per indicare le quattro direzioni. */
typedef enum {
	LEFT,
	RIGHT,
	UP,
	DOWN
} direction_t;

#define SIZE 32
#define GRAVITY 4.0f // Era 4.0f
#define FRICTION 0.8f
#define RUN_SPEED 15.0f
#define JUMP_SPEED 35.0f
#define FALL_SPEED 50.0f

/**
 *	@brief Funzione che stabilisce se un elemento della tilemap è
 *	solido oppure può essere attraversato
 *
 *	@param element elemento della tilemap
 *
 *  @return Un valore di verità che dice se l'elemento è solido oppure no
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
