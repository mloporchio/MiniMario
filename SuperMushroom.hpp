/**
 *	@file SuperMushroom.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Contiene la definizione della classe del powerup Super Mushroom
 */

#ifndef SUPERMUSHROOM_H
#define SUPERMUSHROOM_H

#include "Powerup.hpp"

/** Velocità con cui esce il powerup SuperMushroom. */
#define SUPER_MUSHROOM_SPEED 3.5f

class SuperMushroom : public Powerup {
	public:
		SuperMushroom(int x, int y, sf::Texture *t);
		void update(sf::Time dt, std::vector<Block *> blocks);
		void handleXCollisions(float *px, float *py, float *vx,
			std::vector<Block *> blocks);
		void handleYCollisions(float *px, float *py, float *vy,
			std::vector<Block *> blocks);
};

#endif
