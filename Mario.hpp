/**
 *	@file Mario.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Definition of the Mario class
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

/** Initial position of Mario. */
#define MARIO_POSITION sf::Vector2f(0.0f, 0.0f)
/** Animation time interval for Mario (in milliseconds). */
#define MARIO_ANIMATION_TIME 60
/** Time for Mario to remain invisible after a powerup is collected (in milliseconds). */
#define INVISIBLE_TIME 10000
/** Time for Mario to remain invisible after becoming small (in milliseconds). */
#define TRANSITION_TIME 2000
/** Default score increment. */
#define SCORE_INC 10

/** Class representing Mario. */
class Mario {
	private:
		std::vector<sf::Texture> textures;
		std::vector<std::unique_ptr<sf::SoundBuffer>> soundBuffers;
		std::vector<std::unique_ptr<sf::Sound>> sounds;
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
		int checkBlockCollisions(std::vector<Block *> blocks, sf::IntRect MarioR, sf::IntRect *IntR);
		int checkEnemyCollisions(std::vector<Enemy *> enemies, sf::IntRect MarioR, sf::IntRect *IntR);
		void checkPowerupCollision(std::vector<Powerup *> *powerups, sf::IntRect MarioR);
		bool checkBorderCollision(float *px, float *vx);
		void handleXCollisions(float *px, float *py, float *vx, std::vector<Block *> blocks, std::vector<Enemy *> enemies, std::vector<Powerup *> *powerups);
		void handleYCollisions(float *px, float *py, float *vy, std::vector<Block *> blocks, std::vector<Enemy *> enemies, std::vector<Powerup *> *powerups);
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
		void update(sf::Time dt, std::vector<Block *> blocks, std::vector<Enemy *> enemies, std::vector<Powerup *> *powerups);
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
 *	@brief Returns the next texture to be used for Mario animation
 *
 *	@param current current texture identifier
 *
 *	@return identifier of the next texture to be used
 */
static inline mario_texture_t nextAnimationTexture(bool super, mario_texture_t current) {
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
 *	Given a texture identifier for small (resp. large) Mario returns the texture identifier 
 *	for the corresponding larger (resp. smaller) texture.
 *
 *	@param id current texture identifier
 *
 *	@return identifer of the corresponding larger or smaller texture
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
