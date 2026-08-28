/**
 *	@file Sounds.hpp
 *	@author Matteo Loporchio
 *	
 *	@brief Definitions for sound resources used in the game
 */

#ifndef SOUNDS_H
#define SOUNDS_H

#include <string>

/*
 *	Definition of the sound resources required in the game, used within the Scene class.
 */
#define SCENE_MUSIC_THEME "sounds/scene_theme.ogg"
#define SCENE_SOUND_WIN "sounds/scene_win.wav"

/*
 *	Definition of the sound resources required by the player, used within the Mario class.
 */

/** Number of sounds for the player. */
#define MARIO_SOUND_N 8
#define MARIO_SOUND_JUMP "sounds/mario_jump.wav"
#define MARIO_SOUND_COIN "sounds/mario_coin.wav"
#define MARIO_SOUND_JUMP_BIG "sounds/mario_jump_big.wav"
#define MARIO_SOUND_STOMP "sounds/mario_stomp.wav"
#define MARIO_SOUND_POWERUP_TRIGGERED "sounds/mario_powerup_triggered.wav"
#define MARIO_SOUND_POWERUP_TAKEN "sounds/mario_powerup_taken.wav"
#define MARIO_SOUND_ONEUP_TAKEN "sounds/mario_oneup_taken.wav"
#define MARIO_SOUND_DIE "sounds/mario_die.wav"

/** Enumerated type for indexing the sounds of the player. */
typedef enum {
	JUMP 				= 0,
	PICK_COIN 			= 1,
	JUMP_BIG 			= 2,
	STOMP 				= 3,
	POWERUP_TRIGGERED 	= 4,
	POWERUP_TAKEN 		= 5,
	ONEUP_TAKEN 		= 6,
	DIE 				= 7
} mario_sound_t;

/**
 *	@brief Returns the path of the sound resource for the player
 *
 *	@param id sound identifier
 *
 *	@return string containing the path of the sound resource
 */
static inline std::string getMarioSoundPath(mario_sound_t id) {
	switch (id) {
		case JUMP: return MARIO_SOUND_JUMP;
		case PICK_COIN: return MARIO_SOUND_COIN;
		case JUMP_BIG: return MARIO_SOUND_JUMP_BIG;
		case STOMP: return MARIO_SOUND_STOMP;
		case POWERUP_TRIGGERED: return MARIO_SOUND_POWERUP_TRIGGERED;
		case POWERUP_TAKEN: return MARIO_SOUND_POWERUP_TAKEN;
		case ONEUP_TAKEN: return MARIO_SOUND_ONEUP_TAKEN;
		case DIE: return MARIO_SOUND_DIE;
	}
}

#endif
