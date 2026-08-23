/**
 *	@file Mario.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Contiene la definizione della classe relativa al personaggio Mario 
 */
#ifndef MARIO_H
#define MARIO_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Config.hpp"
#include "Physics.hpp"
#include "Sounds.hpp"
#include "Textures.hpp"
#include "Block.hpp"
#include "Enemy.hpp"
#include "Powerup.hpp"

/** Posizione iniziale del personaggio. */
#define MARIO_POSITION sf::Vector2f(0.0f, 0.0f)
/** Intervallo di animazione per il personaggio (in millisecondi). */
#define MARIO_ANIMATION_TIME 60
/** Tempo per cui Mario resta invisibile dopo il powerup. */
#define INVISIBLE_TIME 10000
/** Tempo per cui Mario resta invisibile dopo essere tornato piccolo. */
#define TRANSITION_TIME 2000
/** L'incremento di punteggio. */
#define SCORE_INC 10

/** Classe che rappresenta il personaggio. */
class Mario {
	private:
		std::vector<sf::Texture> textures;
		std::vector<sf::SoundBuffer *> soundBuffers;
		std::vector<sf::Sound *> sounds;
		sf::Sprite sprite;
		sf::Vector2i size;
		sf::Vector2f speed;
		int animationTime;
		int invisibleTime;
		unsigned int score;
		bool super;
		bool invisible;
		bool dead;
		bool running;
		bool onGround;
		bool ignoreEnemyCollision;
		direction_t facing;
		mario_texture_t textureID;
		void triggerBlockAction(Block *b, std::vector<Powerup *> *powerups);
		void loadSounds();
		int checkBlockCollisions(std::vector<Block *> blocks,
			sf::IntRect MarioR, sf::IntRect *IntR);
		int checkEnemyCollisions(std::vector<Enemy *> enemies,
			sf::IntRect MarioR, sf::IntRect *IntR);
		void checkPowerupCollision(std::vector<Powerup *> *powerups,
			sf::IntRect MarioR);
		bool checkBorderCollision(float *px, float *vx);
		void handleXCollisions(float *px, float *py, float *vx,
			std::vector<Block *> blocks, std::vector<Enemy *> enemies,
			std::vector<Powerup *> *powerups);
		void handleYCollisions(float *px, float *py, float *vy,
			std::vector<Block *> blocks, std::vector<Enemy *> enemies,
			std::vector<Powerup *> *powerups);
		void updateTexture(sf::Time dt);
	public:
		Mario();
		~Mario();
		sf::Sprite getSprite();
		sf::Vector2f getPosition();
		void setPosition(float x, float y);
		sf::Vector2f getSpeed();
		void setSpeed(float x, float y);
		void startJump();
		void endJump();
		void startRunning(direction_t d);
		void endRunning();
		void update(sf::Time dt, std::vector<Block *> blocks,
			std::vector<Enemy *> enemies, std::vector<Powerup *> *powerups);
		bool isSuper();
		void setSuper(bool v);
		bool isInvisible();
		void setInvisible(bool v);
		bool isDead();
		void setDead(bool v);
		void playSound(mario_sound_t id);
		unsigned int getScore();
};

/**
 *	@brief Restituisce la prossima texture da utilizzare per l'animazione
 *
 *	@param current identificativo della texture corrente
 *
 *	@return L'identificativo della texture successiva
 */
static inline mario_texture_t nextAnimationTexture(bool super,
	mario_texture_t current) {

	if (super == false) {
		switch (current) {
			case STANDING: return RUNNING_0;
			case RUNNING_0: return RUNNING_1;
			case RUNNING_1: return RUNNING_2;
			case RUNNING_2: return RUNNING_0;
			case STANDING_L: return RUNNING_0_L;
			case RUNNING_0_L: return RUNNING_1_L;
			case RUNNING_1_L: return RUNNING_2_L;
			case RUNNING_2_L: return RUNNING_0_L;
			// Dopo un salto riprendo a correre.
			case JUMPING: return STANDING;
			case JUMPING_L: return STANDING_L;
			default: return STANDING;
		}
	}
	else {
		switch (current) {
			case S_STANDING: return S_RUNNING_0;
			case S_RUNNING_0: return S_RUNNING_1;
			case S_RUNNING_1: return S_RUNNING_2;
			case S_RUNNING_2: return S_RUNNING_0;
			case S_STANDING_L: return S_RUNNING_0_L;
			case S_RUNNING_0_L: return S_RUNNING_1_L;
			case S_RUNNING_1_L: return S_RUNNING_2_L;
			case S_RUNNING_2_L: return S_RUNNING_0_L;
			// Dopo un salto riprendo a correre.
			case S_JUMPING: return S_STANDING;
			case S_JUMPING_L: return S_STANDING_L;
			default: return S_STANDING;
		}
	}
}

/**
 *	@brief Funzione di utilità che dato un identificativo di texture
 *	di Mario piccolo (risp. grande) restiuisce l'identificativo corrispondente
 *	di Mario grande (risp. piccolo)
 *
 *	@param id identificativo della texture
 *
 *	@return Identificativo della texture corrispondente
 */
static inline mario_texture_t switchMarioTexture(mario_texture_t id) {
	switch (id) {
		case RUNNING_0: return S_RUNNING_0;
		case RUNNING_1: return S_RUNNING_1;
		case RUNNING_2: return S_RUNNING_2;
		case STANDING: return S_STANDING;
		case JUMPING: return S_JUMPING;
		case RUNNING_0_L: return S_RUNNING_0_L;
		case RUNNING_1_L: return S_RUNNING_1_L;
		case RUNNING_2_L: return S_RUNNING_2_L;
		case STANDING_L: return S_STANDING_L;
		case JUMPING_L: return S_JUMPING_L;
		case S_RUNNING_0: return RUNNING_0;
		case S_RUNNING_1: return RUNNING_1;
		case S_RUNNING_2: return RUNNING_2;
		case S_STANDING: return STANDING;
		case S_JUMPING: return JUMPING;
		case S_RUNNING_0_L: return RUNNING_0_L;
		case S_RUNNING_1_L: return RUNNING_1_L;
		case S_RUNNING_2_L: return RUNNING_2_L;
		case S_STANDING_L: return STANDING_L;
		case S_JUMPING_L: return JUMPING_L;
	}
}

#endif
