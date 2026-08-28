/**
 *	@file Powerup.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Implementation of the Powerup class
 */

#include "Powerup.hpp"

/**
 *	@brief Powerup constructor
 *
 *	@param type_ powerup type identifier
 *	@param x initial position along the x axis
 *	@param y initial position along the y axis
 *	@param w width of the powerup
 *	@param h height of the powerup
 *	@param t texture to use for the powerup
 */
Powerup::Powerup(powerup_t type_, float x, float y, int w, int h, sf::Texture &t) : 
	sprite(t),
	type(type_),
	taken(false),
	speed(0, 0),
	size({w, h})
{
	this -> sprite.setPosition({x, y});
}

/**
 *	@brief Returns the powerup type
 *
 *	@return powerup type identifier
 */
powerup_t Powerup::getType() {
	return this -> type;
}

/**
 *	@brief Tells whether the powerup has been taken
 *
 *	@return true if the powerup has been taken, false otherwise
 */
bool Powerup::isTaken() {
	return this -> taken;
}

/**
 *	@brief Sets whether the powerup has been taken
 *
 *	@param v true to set the powerup as taken, false to set it as not taken
 */
void Powerup::setTaken(bool v) {
	this -> taken = v;
}

/**
 *	@brief Returns the current speed of the powerup
 *
 *	@return vector containing the speed of the powerup
 */
sf::Vector2f Powerup::getSpeed() {
	return this -> speed;
}

/**
 *	@brief Sets the current speed of the powerup
 *
 *	@param x speed along the x axis
 *	@param y speed along the y axis
 */
void Powerup::setSpeed(float x, float y) {
	this -> speed.x = x; 
	this -> speed.y = y;
}

/**
 *	@brief Returns the current position of the powerup
 *
 *	@return vector representing the position of the powerup
 */
sf::Vector2f Powerup::getPosition() {
	return this -> sprite.getPosition();
}

/**
 *	@brief Sets the current position of the powerup
 *
 *	@param x position along the x axis
 *	@param y position along the y axis
 */
void Powerup::setPosition(float x, float y) {
	this -> sprite.setPosition({x, y});
}

/**
 *	@brief Returns the size of the powerup
 *
 *	@return vector containing the size of the powerup
 */
sf::Vector2i Powerup::getSize() {
	return this -> size;
}

/**
 *	@brief Returns the bounding rectangle of the powerup
 *
 * 	@return bounding rectangle of the powerup
 */
sf::IntRect Powerup::getRectangle() {
	sf::Vector2f p = this -> getPosition();
	return sf::IntRect({(int) p.x, (int) p.y}, {size.x, size.y});
}

/**
 *	@brief Returns the sprite associated with the powerup
 *
 *	@return sprite associated with the powerup
 */
sf::Sprite Powerup::getSprite() {
	return this -> sprite;
}
