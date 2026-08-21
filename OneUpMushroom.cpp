/**
 *	@file OneUpMushroom.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Contiene l'implementazione della classe OneUpMushroom
 */

#include "OneUpMushroom.hpp"
#include "Physics.hpp"

/**
 *	@brief Costruttore della classe OneUpMushroom
 *
 *	@param x posizione iniziale sull'asse x
 *	@param y posizione iniziale sull'asse y
 *	@param t puntatore alla texture iniziale
 */
OneUpMushroom::OneUpMushroom(int x, int y, sf::Texture *t)
	: Powerup(ONEUP_MUSHROOM, x, y, SIZE, SIZE, t) {
	// Imposto la velocità con cui esce fuori il powerup.
	this -> setSpeed(ONEUP_MUSHROOM_SPEED, 0);
}

/**
 *	@brief Funzione di aggiornamento dell'oggetto OneUpMushroom
 *
 *	@param dt intervallo di tempo
 *	@param blocks vettore dei blocchi
 */
void OneUpMushroom::update(sf::Time dt, std::vector<Block *> blocks) {
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
 *	@brief Funzione di gestione delle collisioni lungo l'asse x
 *
 *	@param px puntatore alla posizione corrente sull'asse x
 *	@param py puntatore alla posizione corrente sull'asse y
 *	@param vx puntatore alla velocità corrente sull'asse x
 *	@param blocks vettore dei blocchi
 */
void OneUpMushroom::handleXCollisions(float *px, float *py, float *vx, std::vector<Block *> blocks) {
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
 *	@brief Funzione di gestione delle collisioni lungo l'asse y
 *
 *	@param px puntatore alla posizione corrente sull'asse x
 *	@param py puntatore alla posizione corrente sull'asse y
 *	@param vy puntatore alla velocità corrente sull'asse y
 *	@param blocks vettore dei blocchi
 */
void OneUpMushroom::handleYCollisions(float *px, float *py, float *vy,
	std::vector<Block *> blocks) {
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
