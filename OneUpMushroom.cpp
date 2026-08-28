/**
 *	@file OneUpMushroom.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Implementation of the OneUpMushroom class
 */

#include "OneUpMushroom.hpp"
#include "Physics.hpp"

/**
 *	@brief OneUpMushroom constructor
 *
 *	@param x initial position on the x axis
 *	@param y initial position on the y axis
 *	@param t initial texture for the OneUpMushroom sprite
 */
OneUpMushroom::OneUpMushroom(float x, float y, sf::Texture &t) : 
	Powerup(ONEUP_MUSHROOM, x, y, SIZE, SIZE, t) 
{
	// Set the speed with which the powerup will be ejected.
	this -> setSpeed(ONEUP_MUSHROOM_SPEED, 0);
}

/**
 *	@brief Update function for the OneUpMushroom object
 *
 *	@param dt time elapsed since last update
 *	@param blocks vector of blocks
 */
void OneUpMushroom::update(sf::Time dt, std::vector<Block *> &blocks) {
	float posX = this -> sprite.getPosition().x;
	float posY = this -> sprite.getPosition().y;
	float velX = this -> speed.x;
	float velY = this -> speed.y;
	posX += velX * 0.2f;
	handleXCollisions(&posX, &posY, &velX, blocks);
	posY += velY * 0.5f;
	handleYCollisions(&posX, &posY, &velY, blocks);
	if ((velY += GRAVITY * 0.5f) > FALL_SPEED) velY = FALL_SPEED;
	// Scrivo i risultati dei calcoli.
	this -> setPosition(posX, posY);
	this -> speed.x = velX;
	this -> speed.y = velY;
}

/**
 *	@brief Handles collisions of OneUpMushroom along the x axis
 *
 *	@param px current position on the x axis
 *	@param py current position on the y axis
 *	@param vx current velocity on the x axis
 *	@param blocks vector of blocks
 */
void OneUpMushroom::handleXCollisions(float *px, float *py, float *vx, std::vector<Block *> &blocks) {
	sf::IntRect MushR({(int) *px, (int) *py}, {SIZE, SIZE}), BlockR, IntR;
	std::optional<sf::IntRect> intersection;
	bool collision = false, collidable = false;
	// Controllo se c'è una collisione.
	for (int i = 0; i < blocks.size(); i++) {
		BlockR = blocks[i] -> getRectangle();
		collidable = blocks[i] -> isCollidable();
		intersection = MushR.findIntersection(BlockR);
		if (collidable && intersection.has_value()) {
			collision = true;
			break;
		}
	}
	// Gestisco la collisione.
	if (collision) {
		IntR = intersection.value();
		if (MushR.position.x < BlockR.position.x) {
			*px = *px - IntR.size.x;
			*vx = -(*vx);
		}
		else {
			*px = *px + IntR.size.x;
			*vx = -(*vx);
		}
	}
}

/**
 *	@brief Handles collisions of OneUpMushroom along the y axis
 *
 *	@param px current position on the x axis
 *	@param py current position on the y axis
 *	@param vy current velocity on the y axis
 *	@param blocks vector of blocks
 */
void OneUpMushroom::handleYCollisions(float *px, float *py, float *vy, std::vector<Block *> &blocks) {
	sf::IntRect MushR({(int) *px, (int) *py}, {SIZE, SIZE}), BlockR, IntR;
	std::optional<sf::IntRect> intersection;
	bool collision = false, collidable = false;
	// Controllo se c'è una collisione.
	for (int i = 0; i < blocks.size(); i++) {
		BlockR = blocks[i] -> getRectangle();
		collidable = blocks[i] -> isCollidable();
		intersection = MushR.findIntersection(BlockR);
		if (collidable && intersection.has_value()) {
			collision = true;
			break;
		}
	}
	// Gestisco la collisione.
	if (collision) {
		IntR = intersection.value();
		if (MushR.position.y < BlockR.position.y) {
			*py = *py - IntR.size.y;
			*vy = 0;
		}
		else {
			*py = *py + IntR.size.y;
			*vy = 0;
		}
	}
}
