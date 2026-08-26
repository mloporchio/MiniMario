/**
 *	@file Block.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Implementation of the Block class
 */

#include <cmath>
#include "Block.hpp"
#include "Physics.hpp"

/**
 *	@brief Block constructor
 *	
 *	@param type_ block type identifier
 *	@param x initial position on the x axis
 *	@param y initial position on the y axis
 *	@param t initial texture for the Block sprite
 */
Block::Block(block_t type_, float x, float y, sf::Texture &t) : 
	sprite(t),
	type(type_),
	active(true),
	collidable(true)
{
	this -> sprite.setPosition({x, y});
}

/**
 *	@brief Block destructor
 */
Block::~Block() {
	// Do nothing!
}

/**
 *	@brief Returns the block type identifier
 *	
 *	@return block type identifier
 */
block_t Block::getType() {
	return this -> type;
}

/**
 *	@brief Tells whether the block is active or not
 *
 *	@return true if the block is active, false otherwise
 */
bool Block::isActive() {
	return this -> active;
}

/**
 *	@brief Activates or disables the block
 *
 *	@param v true to make the block active, false to disable it
 */
void Block::setActive(bool v) {
	this -> active = v;
}

/**
 *	@brief Tells whether the block is collidable or not
 *
 * 	@return true if the block is collidable, false otherwise
 */
bool Block::isCollidable() {
	return this -> collidable;
}

/**
 *	@brief Makes the block collidable or not
 *
 *	@param v true to make the block collidable, false to disable collisions
 */
void Block::setCollidable(bool v) {
	this -> collidable = v;
}

/**
 *	@brief Sets the position of the block
 *
 *	@param x x-axis position
 *	@param y y-axis position
 */
void Block::setPosition(float x, float y) {
	this -> sprite.setPosition({x, y});
}

/**
 *	@brief Returns the position of the block
 *
 *	@return position vector of the block
 */
sf::Vector2f Block::getPosition() {
	return (this -> sprite.getPosition());
}

/**
 *	@brief Returns the bounding rectangle of the block
 *
 *	@return bounding rectangle of the block
 */
sf::IntRect Block::getRectangle() {
	sf::Vector2f p = this -> getPosition();
	return sf::IntRect({(int) p.x, (int) p.y}, {SIZE, SIZE});
}

/**
 *	@brief Returns the sprite associated with the block
 *
 *	@return sprite associated with the block
 */
sf::Sprite Block::getSprite() {
	return this -> sprite;
}
