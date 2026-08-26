/**
 *	@file CoinPowerup.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Implementation of the CoinPowerup class
 */

#include "CoinPowerup.hpp"
#include "Physics.hpp"

/**
 *	@brief CoinPowerup constructor
 *
 *	@param x initial position on the x axis
 *	@param y initial position on the y axis
 *	@param t initial texture for the powerup sprite
 */ 
CoinPowerup::CoinPowerup(float x, float y, sf::Texture &t) :
	Powerup(COIN_POWERUP, x, y, SIZE, SIZE, t),
	y0(y)
{
	this -> setSpeed(0, -COIN_POWERUP_SPEED);
}

/**
 *	@brief Update function for the CoinPowerup object
 *
 *	@param dt time elapsed since last update
 */
void CoinPowerup::update(sf::Time dt) {
	float posX = this -> sprite.getPosition().x;
	float posY = this -> sprite.getPosition().y;
	float velY = this -> speed.y;
	posY += velY * 0.2f;
	// Check if it is time to deactivate it.
	if (posY < y0 - SIZE) {
		this -> taken = true;
		return;
	}
	// Write the results of the calculations.
	this -> setPosition(posX, posY);
	this -> speed.y = velY;
}
