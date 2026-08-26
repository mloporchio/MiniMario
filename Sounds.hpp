/**
 *	@file Sounds.hpp
 *	@author Matteo Loporchio
 *	
 *	@brief Definizioni per le risorse relative ai suoni del gioco
 */

#ifndef SOUNDS_H
#define SOUNDS_H

/*
 *	Definizione dei suoni relativi al livello.
 *	Vengono utilizzati nella classe "Scene".
 */
#define SCENE_MUSIC_THEME "sounds/scene_theme.ogg"
#define SCENE_SOUND_WIN "sounds/scene_win.wav"

/*
 *	Definizione dei suoni relativi al personaggio Mario.
 *	Vengono utilizzati nella classe "Mario".
 */

/** Numero di suoni per il personaggio. */
#define MARIO_SOUND_N 8
#define MARIO_SOUND_JUMP "sounds/mario_jump.wav"
#define MARIO_SOUND_COIN "sounds/mario_coin.wav"
#define MARIO_SOUND_JUMP_BIG "sounds/mario_jump_big.wav"
#define MARIO_SOUND_STOMP "sounds/mario_stomp.wav"
#define MARIO_SOUND_POWERUP_TRIGGERED "sounds/mario_powerup_triggered.wav"
#define MARIO_SOUND_POWERUP_TAKEN "sounds/mario_powerup_taken.wav"
#define MARIO_SOUND_ONEUP_TAKEN "sounds/mario_oneup_taken.wav"
#define MARIO_SOUND_DIE "sounds/mario_die.wav"

/** Tipo enumerato per indicizzare i suoni di Mario. */
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
 *	@brief Restituisce il percorso dei suoni relativi a Mario
 *
 *	@param id identificativo del suono
 *
 *	@return Una stringa contenente il path del suono
 */
static inline const char *getMarioSoundPath(mario_sound_t id) {
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
