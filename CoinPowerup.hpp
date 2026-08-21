/**
 *	@file CoinPowerup.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Contiene la definizione della classe CoinPowerup, relativa al
 *	powerup di tipo moneta
 */

#ifndef COIN_POWERUP_H
#define COIN_POWERUP_H

#include "Powerup.hpp"

/** Velocità con cui esce il powerup. */
#define COIN_POWERUP_SPEED 35.0f

class CoinPowerup : public Powerup {
	private:
		float y0;
	public:
		CoinPowerup(int x, int y, sf::Texture *t);
		void update(sf::Time dt);
};

#endif
