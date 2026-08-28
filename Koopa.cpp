/**
 *	@file Koopa.cpp
 *	@author Matteo Loporchio
 *
 * 	@brief Implementation of the Koopa class
 */

#include "Koopa.hpp"
#include "Physics.hpp"

/**
 *	@brief Koopa constructor
 *
 *	@param x initial position on the x axis
 *	@param y initial position on the y axis
 *	@param k identifier of the Koopa type (green or red)
 *	@param textures_ vector of textures to be used for the Koopa sprite
 */
Koopa::Koopa(float x, float y, block_t k, std::vector<sf::Texture> &textures_) : 
	Enemy(k, x, y, SIZE, KOOPA_HEIGHT, textures_[0]),
	textures(textures_),
	textureID(((k == GREEN_KOOPA) ? GREEN_KOOPA_0 : RED_KOOPA_0)),
	hit(false),
	elapsed(0)
{
	this -> setSpeed(-KOOPA_SPEED, 0);
}

/**
 *	@brief Tells whether Koopa is on the ground or not
 *
 *	@return true if Koopa is on the ground, false otherwise
 */
bool Koopa::isOnGround() {
	return this -> onGround;
}

/**
 *	@brief Tells whether Koopa has been hit from above or not
 *
 *	@return true if Koopa has been hit, false otherwise
 */
bool Koopa::isHit() {
	return this -> hit;
}

/**
 *	@brief Called when Koopa is hit from above and hides inside its shell
 */
void Koopa::setHit() {
	if (!hit) {
		this -> textureID = ((this -> type == GREEN_KOOPA) ?
		GREEN_KOOPA_SHELL : RED_KOOPA_SHELL);
		this -> size.x = SIZE;
		this -> size.y = SIZE;
	}
	this -> speed.x = 0;
	this -> hit = true;
}

/**
 *	@brief Tells whether the shell of Koopa is moving or not
 *
 *	@return true if the shell of Koopa is moving, false otherwise
 */
bool Koopa::isMoving() {
	return (this -> speed.x != 0);
}

/**
 *	@brief Called when the shell of Koopa is spun
 *
 *	@param d direction in which the shell is spun
 */
void Koopa::move(direction_t d) {
	switch (d) {
		case LEFT: this -> speed.x = -3 * KOOPA_SPEED; break;
		case RIGHT: this -> speed.x = 3 * KOOPA_SPEED; break;
		default: break;
	}
}

/**
 *	@brief Update function for the Koopa object
 *
 * 	@param dt time elapsed since last update
 *	@param blocks vector of blocks
 *	@param enemies vector of enemies
 *	@param index index of Koopa within the vector of enemies
 */
void Koopa::update(sf::Time dt, std::vector<Block *> blocks,
	std::vector<Enemy *> enemies, int index) {
	float posX = this -> sprite.getPosition().x;
	float posY = this -> sprite.getPosition().y;
	float velX = this -> speed.x;
	float velY = this -> speed.y;
	posX += velX * 0.3f;
	handleXCollisions(&posX, &posY, &velX, blocks, enemies, index);
	posY += velY * 0.5f;
	handleYCollisions(&posX, &posY, &velY, blocks, enemies, index);
	if ((velY += GRAVITY * 0.5f) > FALL_SPEED) velY = FALL_SPEED;
	// Scrivo i risultati dei calcoli.
	this -> setPosition(posX, posY);
	this -> speed.x = velX;
	this -> speed.y = velY;
	// Aggiorno la texture del personaggio.
	if (!hit) {
		if (elapsed >= KOOPA_ANIMATION_TIME) {
			this -> textureID = nextKoopaTexture(this -> textureID);
			elapsed = 0;
		}
		else elapsed += dt.asMilliseconds();
	}
	else this -> sprite.setTextureRect(sf::IntRect({0, 0}, {size.x, size.y}));
	this -> sprite.setTexture(textures[(int) textureID]);
}

/**
 *	@brief Handles collisions of Koopa along the x axis
 *
 * 	@param px current position on the x axis
 * 	@param py current position on the y axis
 * 	@param vx current velocity on the x axis
 * 	@param blocks vector of blocks
 * 	@param enemies vector of enemies
 * 	@param index index of Koopa within the vector of enemies
 */
void Koopa::handleXCollisions(float *px, float *py, float *vx,
	std::vector<Block *> blocks, std::vector<Enemy *> enemies, int index) {
	sf::IntRect KoopaR({(int) *px, (int) *py}, {size.x, size.y}), BlockR, EnemyR, IntR;
	bool collidable = false;
	// Controllo se c'è una collisione con un blocco.
	for (int i = 0; i < blocks.size(); i++) {
		BlockR = blocks[i] -> getRectangle();
		collidable = blocks[i] -> isCollidable();
		std::optional<sf::IntRect> intersection = KoopaR.findIntersection(BlockR);
		if (collidable && intersection.has_value()) {
			sf::IntRect IntR = intersection.value();
			block_t type = blocks[i] -> getType();
			// Se il blocco è una moneta, ignoro la collisione.
			if (type == COIN) return;
			if (KoopaR.position.x < BlockR.position.x) {
				*px = *px - IntR.size.x;
				*vx = -(*vx);
				this -> textureID = flipKoopaTexture(this -> textureID);
			}
			else {
				*px = *px + IntR.size.x;
				*vx = -(*vx);
				this -> textureID = flipKoopaTexture(this -> textureID);
			}
			return;
		}
	}
	// Controllo se c'è una collisione con un nemico.
	for (int i = 0; i < enemies.size(); i++) {
		EnemyR = enemies[i] -> getRectangle();
		collidable = enemies[i] -> isCollidable();
		std::optional<sf::IntRect> intersection = KoopaR.findIntersection(EnemyR);
		if (collidable && intersection.has_value() && i != index) {
			sf::IntRect IntR = intersection.value();
			// Se Koopa ha solo il guscio, ignoro le collisioni con i nemici.
			if (this -> hit) {
				enemies[i] -> setAlive(false);
				enemies[i] -> setCollidable(false);
				return;
			}
			// Altrimenti procedo normalmente.
			if (KoopaR.position.x < EnemyR.position.x) {
				*px = *px - IntR.size.x;
				*vx = -(*vx);
				this -> textureID = flipKoopaTexture(this -> textureID);
			}
			else {
				*px = *px + IntR.size.x;
				*vx = -(*vx);
				this -> textureID = flipKoopaTexture(this -> textureID);
			}
			return;
		}
	}
}

/**
 *	@brief Handles collisions of Koopa along the y axis
 *
 * 	@param px current position on the x axis
 * 	@param py current position on the y axis
 * 	@param vy current velocity on the y axis
 * 	@param blocks vector of blocks
 * 	@param enemies vector of enemies
 * 	@param index index of Koopa within the vector of enemies
 */
void Koopa::handleYCollisions(float *px, float *py, float *vy,
	std::vector<Block *> blocks, std::vector<Enemy *> enemies, int index) {
	sf::IntRect KoopaR({(int) *px, (int) *py}, {size.x, size.y}), BlockR, EnemyR, IntR;
	bool collidable = false;
	// Controllo se c'è una collisione con un blocco.
	for (int i = 0; i < blocks.size(); i++) {
		BlockR = blocks[i] -> getRectangle();
		collidable = blocks[i] -> isCollidable();
		std::optional<sf::IntRect> intersection = KoopaR.findIntersection(BlockR);
		if (collidable && intersection.has_value()) {
			sf::IntRect IntR = intersection.value();
			block_t type = blocks[i] -> getType();
			// Se il blocco è una moneta, ignoro la collisione.
			if (type == COIN) return;
			if (KoopaR.position.y < BlockR.position.y) {
				*py = *py - IntR.size.y;
				*vy = 0;
			}
			else {
				*py = *py + IntR.size.y;
				*vy = 0;
			}
			return;
		}
	}
	// Controllo se c'è una collisione con un nemico.
	for (int i = 0; i < enemies.size(); i++) {
		EnemyR = enemies[i] -> getRectangle();
		collidable = enemies[i] -> isCollidable();
		std::optional<sf::IntRect> intersection = KoopaR.findIntersection(EnemyR);
		if (collidable && intersection.has_value() && i != index) {
			sf::IntRect IntR = intersection.value();
			if (KoopaR.position.y < EnemyR.position.y) {
				*py = *py - IntR.size.y;
				*vy = 0;
			}
			else {
				*py = *py + IntR.size.y;
				*vy = 0;
			}
			return;
		}
	}
}
