/**
 *	@file Coin.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Implementation of the Coin class
 */

#include "Coin.hpp"
#include "Config.hpp"

/**
 *	@brief Coin constructor
 *
 *	@param x initial position on the x axis 
 *	@param y initial position on the y axis
 *	@param textures_ texture vector for the associated sprite
 */
Coin::Coin(float x, float y, std::vector<sf::Texture> &textures_) : 
	Block(COIN, x, y, textures_[0]), 
	textures(textures_),
	elapsed(0), 
	textureID(STILL) 
{
	// The following are automatically set:
	// this -> active = true;
	// this -> collidable = true;
}

/**
 *	@brief Called when the Coin is hit by the player
 */
void Coin::hit() {
	this -> active = false;
	this -> collidable = false;
}

/**
 *	@brief Update function for the Coin object
 *
 *	@param dt time elapsed since last update
 */
void Coin::update(sf::Time dt) {
	if (this -> active) {
		textureID = nextCoinTexture(textureID);
		this -> sprite.setTexture(textures[(int) textureID]);
	}
}
