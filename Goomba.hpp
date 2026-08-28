/**
 *	@file Goomba.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Definition of the Goomba class
 */

#ifndef GOOMBA_H
#define GOOMBA_H

#include "Enemy.hpp"
#include "Textures.hpp"

/** Time elapsed between two Goomba textures. */
#define GOOMBA_ANIMATION_TIME 200
/** Speed with which the Goomba moves. */
#define GOOMBA_SPEED 7.0f

/**
 *	@brief Represents Goomba, one of the enemies of the game
 */
class Goomba : public Enemy {
	private:
		std::vector<sf::Texture> &textures;
		goomba_texture_t textureID;
		int elapsed;
	public:
		Goomba(float x, float y, std::vector<sf::Texture> &textures_);
		void update(sf::Time dt, std::vector<Block *> blocks, std::vector<Enemy *> enemies, int index);
		void handleXCollisions(float *px, float *py, float *vx, std::vector<Block *> blocks, std::vector<Enemy *> enemies, int index);
		void handleYCollisions(float *px, float *py, float *vy, std::vector<Block *> blocks, std::vector<Enemy *> enemies, int index);
};

/**
 *	@brief Utility function to get the next texture of a Goomba
 *
 *	@param id current texture identifier
 *
 *	@return next texture identifier
 */
static inline goomba_texture_t nextGoombaTexture(goomba_texture_t id) {
	return ((id == GOOMBA_0) ? GOOMBA_1 : GOOMBA_0);
}

#endif
