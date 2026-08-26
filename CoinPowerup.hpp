/**
 *	@file CoinPowerup.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Definition of the CoinPowerup class
 */

#ifndef COIN_POWERUP_H
#define COIN_POWERUP_H

#include "Powerup.hpp"

/** Speed of the coin powerup. */
#define COIN_POWERUP_SPEED 35.0f

class CoinPowerup : public Powerup {
	private:
		float y0;
	public:
		CoinPowerup(float x, float y, sf::Texture &t);
		void update(sf::Time dt);
};

#endif
