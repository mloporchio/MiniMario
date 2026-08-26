/**
 *	@file Enemy.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Implementation of the Enemy class
 */

#include "Enemy.hpp"
#include "Physics.hpp"

/**
 *	@brief Enemy constructor
 *
 *	@param type_ 
 *	@param x initial position on the x axis
 *	@param y initial position on the y axis
 *	@param w enemy width
 *	@param h enemy height
 *	@param t texture to be used for the Enemy sprite
 */
Enemy::Enemy(block_t type_, float x, float y, int w, int h, sf::Texture &t) : 
	sprite(t),
	type(type_),
	onGround(false),
	alive(true),
	collidable(true),
	speed(0, 0),
	size({w, h})
{
	this -> sprite.setPosition({x, y});
}

/**
 *	@brief Enemy destructor
 */
Enemy::~Enemy() {}

/**
 *	@brief Returns the type of the Enemy
 *
 *	@return Enemy type identifier
 */
block_t Enemy::getType() {
	return this -> type;
}

/**
 *	@brief Tells whether the Enemy is alive or not
 *
 *	@return true if the Enemy is alive, false otherwise
 */
bool Enemy::isAlive() {
	return this -> alive;
}

/**
 *	@brief Sets the Enemy alive or dead
 *
 *	@param v true to make the Enemy alive, false to make it dead
 */
void Enemy::setAlive(bool v) {
	this -> alive = v;
}

/**
 *	@brief Tells whether the Enemy is collidable or not
 *	
 *	@return true if the Enemy is collidable, false otherwise
 */
bool Enemy::isCollidable() {
	return this -> collidable;
}

/**
 *	@brief Makes the Enemy collidable or not
 *
 *	@param v true to make the Enemy collidable, false to disable collisions
 */
void Enemy::setCollidable(bool v) {
	this -> collidable = v;
}

/**
 *	@brief Returns the current speed of the Enemy
 *
 *	@return Enemy speed vector
 */
sf::Vector2f Enemy::getSpeed() {
	return this -> speed;
}

/**
 *	@brief Sets the current speed of the Enemy
 *
 *	@param x speed component along the x axis
 *	@param y speed component along the y axis
 */
void Enemy::setSpeed(float x, float y) {
	this -> speed.x = x; 
	this -> speed.y = y;
}

/**
 *	@brief Restiuisce la posizione corrente del nemico
 *
 *	@return Il vettore posizione del nemico
 */
sf::Vector2f Enemy::getPosition() {
	return this -> sprite.getPosition();
}

/**
 *	@brief Imposta la posizione corrente del nemico
 *
 *	@param x ascissa del punto
 *	@param y ordinata del punto
 */
void Enemy::setPosition(float x, float y) {
	this -> sprite.setPosition({x, y});
}

/**
 *	@brief Restituisce la dimensione del nemico
 *
 *	@return Il vettore contenente larghezza e altezza del nemico
 */
sf::Vector2i Enemy::getSize() {
	return this -> size;
}

/**
 *	@brief Restituisce il bounding rectangle del nemico
 *
 *	@return Il rettangolo che contiene il nemico
 */
sf::IntRect Enemy::getRectangle() {
	sf::Vector2f p = this -> getPosition();
	return sf::IntRect({(int) p.x, (int) p.y}, {size.x, size.y});
}

/**
 *	@brief Restituisce la sprite associata al nemico
 *
 *	@return La sprite associata al nemico
 */
sf::Sprite Enemy::getSprite() {
	return this -> sprite;
}
