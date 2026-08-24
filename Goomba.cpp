/**
 *	@file Goomba.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Contiene l'implementazione della classe relativa al nemico Goomba
 */

#include "Goomba.hpp"
#include "Physics.hpp"

/**
 *	@brief Costruttore della classe Goomba
 *
 *	@param x posizione sull'asse x
 *	@param y posizione sull'asse y
 *	@param textures puntatore al vettore con le texture
 */
Goomba::Goomba(float x, float y, std::vector<sf::Texture> &textures_) :
	Enemy(GOOMBA, x, y, SIZE, SIZE, textures_[0]), 
	textures(textures_), 
	textureID(GOOMBA_0), 
	elapsed(0) 
{
	this -> setSpeed(-GOOMBA_SPEED, 0);
}

/**
 *	@brief Funzione di aggiornamento del nemico Goomba
 *
 *	@param dt intervallo di tempo dall'ultimo aggiornamento
 *	@param blocks vettore contenente i blocchi
 *	@param enemies vettore contenente i nemici
 *	@param index indice di Goomba all'interno del vettore dei nemici
 */
void Goomba::update(sf::Time dt, std::vector<Block *> blocks,
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
	if (elapsed >= GOOMBA_ANIMATION_TIME) {
		this -> textureID = nextGoombaTexture(this -> textureID);
		elapsed = 0;
	}
	else elapsed += dt.asMilliseconds();
	this -> sprite.setTexture(textures[(int) textureID]);
}

/**
 *	@brief Funzione di gestione delle collisioni di Goomba lungo l'asse x
 *
 *	@param px puntatore alla posizione sull'asse x
 *	@param py puntatore alla posizione sull'asse y
 *	@param vx puntatore alla velocità lungo l'asse x
 *	@param blocks vettore contenente i blocchi
 *	@param enemies vettore contenente i nemici
 *	@param index indice di Goomba all'interno del vettore dei nemici
 */
void Goomba::handleXCollisions(float *px, float *py, float *vx,
	std::vector<Block *> blocks, std::vector<Enemy *> enemies, int index) {
	sf::IntRect GoombaR({(int) *px, (int) *py}, {SIZE, SIZE}), BlockR, EnemyR, IntR;
	bool collidable = false;
	// Controllo se c'è una collisione con un blocco.
	for (int i = 0; i < blocks.size(); i++) {
		BlockR = blocks[i] -> getRectangle();
		collidable = blocks[i] -> isCollidable();
		std::optional<sf::IntRect> intersection = GoombaR.findIntersection(BlockR);
		if (collidable && intersection.has_value()) {
			sf::IntRect IntR = intersection.value();
			block_t type = blocks[i] -> getType();
			// Se il blocco è una moneta, ignoro la collisione.
			if (type == COIN) return;
			if (GoombaR.position.x < BlockR.position.x) {
				*px = *px - IntR.size.x; // *px = *px - IntR.width;
				*vx = -(*vx);
			}
			else {
				*px = *px + IntR.size.x; // *px = *px + IntR.width;
				*vx = -(*vx);
			}
			return;
		}
	}
	// Controllo se c'è una collisione con un nemico.
	for (int i = 0; i < enemies.size(); i++) {
		EnemyR = enemies[i] -> getRectangle();
		collidable = enemies[i] -> isCollidable();
		std::optional<sf::IntRect> intersection = GoombaR.findIntersection(EnemyR);
		if (collidable && intersection.has_value() && i != index) {
			sf::IntRect IntR = intersection.value();
			if (GoombaR.position.x < EnemyR.position.x) {
				*px = *px - IntR.size.x; // *px = *px - IntR.width;
				*vx = -(*vx);
			}
			else {
				*px = *px + IntR.size.x; // *px = *px + IntR.width;
				*vx = -(*vx);
			}
			return;
		}
	}
}

/**
 *	@brief Funzione di gestione delle collisioni di Goomba lungo l'asse y
 *
 *	@param px puntatore alla posizione sull'asse x
 *	@param py puntatore alla posizione sull'asse y
 *	@param vy puntatore alla velocità lungo l'asse y
 *	@param blocks vettore contenente i blocchi
 *	@param enemies vettore contenente i nemici
 *	@param index indice di Goomba all'interno del vettore dei nemici
 */
void Goomba::handleYCollisions(float *px, float *py, float *vy,
	std::vector<Block *> blocks, std::vector<Enemy *> enemies, int index) {
	sf::IntRect GoombaR({(int) *px, (int) *py}, {SIZE, SIZE}), BlockR, EnemyR, IntR;
	bool collidable = false;
	// Controllo se c'è una collisione con un blocco.
	for (int i = 0; i < blocks.size(); i++) {
		BlockR = blocks[i] -> getRectangle();
		collidable = blocks[i] -> isCollidable();
		std::optional<sf::IntRect> intersection = GoombaR.findIntersection(BlockR);
		if (collidable && intersection.has_value()) {
			sf::IntRect IntR = intersection.value();
			block_t type = blocks[i] -> getType();
			// Se il blocco è una moneta, ignoro la collisione.
			if (type == COIN) return;
			if (GoombaR.position.y < BlockR.position.y) {
				*py = *py - IntR.size.y; // *py = *py - IntR.height;
				*vy = 0;
			}
			else {
				*py = *py + IntR.size.y; // *py = *py + IntR.height;
				*vy = 0;
			}
			return;
		}
	}
	// Controllo se c'è una collisione con un nemico.
	for (int i = 0; i < enemies.size(); i++) {
		EnemyR = enemies[i] -> getRectangle();
		collidable = enemies[i] -> isCollidable();
		std::optional<sf::IntRect> intersection = GoombaR.findIntersection(EnemyR);
		if (collidable && intersection.has_value() && i != index) {
			sf::IntRect IntR = intersection.value();
			if (GoombaR.position.y < EnemyR.position.y) {
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
