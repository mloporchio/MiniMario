/**
 *	@file Textures.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Definitions related to the textures used in the game
 *
 *	This file contains definitions related to the textures used in the game.
 */

#ifndef TEXTURES_H
#define TEXTURES_H

#include "Tilemap.hpp"

#define MENU_FOREGROUND_TEXTURE "images/FOREGROUND.png"
#define BACKGROUND_TEXTURE "images/BACKGROUND.png"
#define LOGO_TEXTURE "images/LOGO.png"

/*
 *	Definizione delle texture di tipo statico.
 *	Le texture statiche vengono applicate a tutti i blocchi che non
 *	devono essere animati.
 */

/** Numero di texture statiche definite. */
#define STATIC_TEXTURE_N 12
#define SKY_TEXTURE "images/SKY.png"
#define BRICKS_TEXTURE "images/BRICKS.png"
#define TERRAIN_TEXTURE "images/TERRAIN.png"
#define SOLID_TEXTURE "images/SOLID.png"
#define BUSH_L_TEXTURE "images/BUSH_L.png"
#define BUSH_M_TEXTURE "images/BUSH_M.png"
#define BUSH_R_TEXTURE "images/BUSH_R.png"
#define PIPE_TOP_L_TEXTURE "images/PIPE_TOP_L.png"
#define PIPE_TOP_R_TEXTURE "images/PIPE_TOP_R.png"
#define PIPE_BOTTOM_L_TEXTURE "images/PIPE_BOTTOM_L.png"
#define PIPE_BOTTOM_R_TEXTURE "images/PIPE_BOTTOM_R.png"
#define GRASS_TEXTURE "images/GRASS.png"
#define WATER_TEXTURE "images/WATER.png"

/** Tipo enumerato per indicizzare le texture statiche. */
typedef enum {
	STATIC_BRICKS = 0,
	STATIC_TERRAIN = 1,
	STATIC_SOLID = 2,
	STATIC_BUSH_L = 3,
	STATIC_BUSH_M = 4,
	STATIC_BUSH_R = 5,
	STATIC_PIPE_TOP_L = 6,
	STATIC_PIPE_TOP_R = 7,
	STATIC_PIPE_BOTTOM_L = 8,
	STATIC_PIPE_BOTTOM_R = 9,
	STATIC_GRASS = 10,
	STATIC_WATER = 11
} static_texture_t;

/**
 *	@brief Restituisce il path di una texture statica
 *
 *	@param id identificativo della texture
 *
 *	@return Stringa contenente il percorso della texture
 */
static inline const char *getStaticTexturePath(static_texture_t id) {
	switch (id) {
		case STATIC_BRICKS: return BRICKS_TEXTURE;
		case STATIC_TERRAIN: return TERRAIN_TEXTURE;
		case STATIC_SOLID: return SOLID_TEXTURE;
		case STATIC_BUSH_L: return BUSH_L_TEXTURE;
		case STATIC_BUSH_M: return BUSH_M_TEXTURE;
		case STATIC_BUSH_R: return BUSH_R_TEXTURE;
		case STATIC_PIPE_TOP_L: return PIPE_TOP_L_TEXTURE;
		case STATIC_PIPE_TOP_R: return PIPE_TOP_R_TEXTURE;
		case STATIC_PIPE_BOTTOM_L: return PIPE_BOTTOM_L_TEXTURE;
		case STATIC_PIPE_BOTTOM_R: return PIPE_BOTTOM_R_TEXTURE;
		case STATIC_GRASS: return GRASS_TEXTURE;
		case STATIC_WATER: return WATER_TEXTURE;
	}
}

/**
 *	@brief Dato un elemento della tilemap, restituisce l'identificativo
 *	della texture statica ad esso associata
 *
 *	@param element elemento della tilemap
 *
 *	@return L'identificativo della texture statica in caso di successo,
 *	-1 in caso di fallimento
 */
static inline int getStaticTextureID(block_t element) {
	switch (element) {
		case BRICKS: return (int) STATIC_BRICKS;
		case TERRAIN: return (int) STATIC_TERRAIN;
		case SOLID: return (int) STATIC_SOLID;
		case BUSH_L: return (int) STATIC_BUSH_L;
		case BUSH_M: return (int) STATIC_BUSH_M;
		case BUSH_R: return (int) STATIC_BUSH_R;
		case PIPE_TOP_L: return (int) STATIC_PIPE_TOP_L;
		case PIPE_TOP_R: return (int) STATIC_PIPE_TOP_R;
		case PIPE_BOTTOM_L: return (int) STATIC_PIPE_BOTTOM_L;
		case PIPE_BOTTOM_R: return (int) STATIC_PIPE_BOTTOM_R;
		case GRASS: return (int) STATIC_GRASS;
		case WATER: return (int) STATIC_WATER;
		default: return -1;
	}
}

/*
 *	Definizione delle texture dinamiche, utilizzate per tutti i blocchi
 *	con un'animazione.
 */
#define QUESTION_TEXTURE_N 4
#define QUESTION_TEXTURE_SHEET "images/QUESTION_S.png"

/** Tipo enumerato per indicizzare le texture relative al Question Block. */
typedef enum {
	ACTIVE_0 = 0,
	ACTIVE_1 = 1,
	ACTIVE_2 = 2,
	INACTIVE = 3
} question_texture_t;

#define COIN_TEXTURE_N 4
#define COIN_TEXTURE_SHEET "images/COIN_S.png"

/** Tipo enumerato per indicizzare le texture relative alle monete. */
typedef enum {
	STILL = 0,
	MOVING_1 = 1,
	MOVING_2 = 2,
	MOVING_3 = 3
} coin_texture_t;

/*
 *	Definizione delle texture per il personaggio Mario.
 */
#define MARIO_TEXTURE_N 20
#define MARIO_TEXTURE_SHEET "images/MARIO_S.png"

/** Tipo enumerato per indicizzare le texture di Mario. */
typedef enum {
	// Dimensione standard.
	RUNNING_0 	= 0,
	RUNNING_1 	= 1,
	RUNNING_2 	= 2,
	STANDING	= 3,
	JUMPING		= 4,
	RUNNING_0_L 	= 5,
	RUNNING_1_L 	= 6,
	RUNNING_2_L 	= 7,
	STANDING_L	= 8,
	JUMPING_L	= 9,
	// Dimensione grande.
	S_RUNNING_0 	= 10,
	S_RUNNING_1 	= 11,
	S_RUNNING_2 	= 12,
	S_STANDING	= 13,
	S_JUMPING	= 14,
	S_RUNNING_0_L 	= 15,
	S_RUNNING_1_L 	= 16,
	S_RUNNING_2_L 	= 17,
	S_STANDING_L	= 18,
	S_JUMPING_L	= 19
} mario_texture_t;

/*
 *	Definizione delle texture per il nemico Goomba.
 */
#define GOOMBA_TEXTURE_N 2
#define GOOMBA_TEXTURE_SHEET "images/GOOMBA_S.png"

/** Tipo enumerato per indicizzare le texture di Goomba. */
typedef enum {
	GOOMBA_0 = 0,
	GOOMBA_1 = 1
} goomba_texture_t;


/*
 *	Definizione delle texture per il nemico Piranha Plant.
 */
#define PIRANHAPLANT_TEXTURE_N 2
#define PIRANHAPLANT_TEXTURE_SHEET "images/PIRANHA_PLANT_S.png"

/** Tipo enumerato per indicizzare le texture della Piranha Plant. */
typedef enum {
	PLANT_0 = 0,
	PLANT_1 = 1
} plant_texture_t;

/*
 *	Definizioni delle texture relative al nemico Koopa.
 */
#define KOOPA_TEXTURE_N 10
#define KOOPA_TEXTURE_SHEET "images/KOOPA_S.png"
#define KOOPA_GREEN_SHELL_TEXTURE "images/GREEN_KOOPA_SHELL.png"
#define KOOPA_RED_SHELL_TEXTURE "images/RED_KOOPA_SHELL.png"

/** Tipo enumerato per indicizzare le texture di Koopa. */
typedef enum {
	GREEN_KOOPA_0 = 0,
 	GREEN_KOOPA_1 = 1,
 	GREEN_KOOPA_0_L = 2,
 	GREEN_KOOPA_1_L = 3,
 	RED_KOOPA_0 = 4,
 	RED_KOOPA_1 = 5,
 	RED_KOOPA_0_L = 6,
 	RED_KOOPA_1_L = 7,
 	GREEN_KOOPA_SHELL = 8,
 	RED_KOOPA_SHELL = 9
} koopa_texture_t;

/*
 *	Definizioni delle texture relative ai powerup usati nel gioco.
 */
#define SUPERMUSHROOM_TEXTURE "images/SUPER_MUSHROOM.png"
#define ONEUPMUSHROOM_TEXTURE "images/ONEUP_MUSHROOM.png"
#define COIN_POWERUP_TEXTURE "images/COIN_POWERUP.png"

#endif
