/**
 *	@file SuperMushroom.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Definition of the SuperMushroom class
 */

#ifndef SUPERMUSHROOM_H
#define SUPERMUSHROOM_H

#include "Powerup.hpp"

/** Speed of the SuperMushroom powerup. */
#define SUPER_MUSHROOM_SPEED 3.5f

/**
 *	@brief Represents the SuperMushroom powerup
 */
class SuperMushroom : public Powerup {
	public:
		SuperMushroom(float x, float y, sf::Texture &t);
		void update(sf::Time dt, std::vector<Block *> blocks);
		void handleXCollisions(float *px, float *py, float *vx, std::vector<Block *> blocks);
		void handleYCollisions(float *px, float *py, float *vy, std::vector<Block *> blocks);
};

#endif
