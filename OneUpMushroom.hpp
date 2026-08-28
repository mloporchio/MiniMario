/**
 *	@file OneUpMushroom.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Definition of the OneUpMushroom class
 */

#ifndef ONEUP_MUSHROOM_H
#define ONEUP_MUSHROOM_H

#include "Powerup.hpp"

#define ONEUP_MUSHROOM_SPEED 3.5f

class OneUpMushroom : public Powerup {
	public:
		OneUpMushroom(float x, float y, sf::Texture &t);
		void update(sf::Time dt, std::vector<Block *> &blocks);
		void handleXCollisions(float *px, float *py, float *vx, std::vector<Block *> &blocks);
		void handleYCollisions(float *px, float *py, float *vy, std::vector<Block *> &blocks);
};

#endif
