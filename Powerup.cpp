/**
 *	@file Powerup.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Contiene l'implementazione della classe Powerup
 */

#include "Powerup.hpp"

/**
 *	@brief Constructor of the Powerup class
 *
 *	@param type identificativo del tipo di powerup
 *	@param x posizione lungo l'asse x
 *	@param y posizione lungo l'asse y
 *	@param w larghezza del powerup
 *	@param h altezza del powerup
 *	@param t puntatore alla texture da utilizzare per il powerup
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
 *	@brief Restituisce il tipo del powerup
 *
 *	@return L'identificativo del tipo di powerup
 */
powerup_t Powerup::getType() {
	return this -> type;
}

/**
 *	@brief Dice se il powerup è stato raccolto oppure no
 *
 *	@return Un valore di verità che dice se il powerup è stato preso
 */
bool Powerup::isTaken() {
	return this -> taken;
}

/**
 *	@brief Imposta il valore di verità relativo al powerup raccolto
 *
 *	@param v valore di verità da assegnare
 */
void Powerup::setTaken(bool v) {
	this -> taken = v;
}

/**
 *	@brief Restituisce la velocità corrente del powerup
 *
 *	@return Il vettore della velocità corrente del powerup
 */
sf::Vector2f Powerup::getSpeed() {
	return this -> speed;
}

/**
 *	@brief Imposta la velocità corrente del powerup
 *
 *	@param x componente del vettore velocità lungo l'asse x
 *	@param y componente del vettore velocità lungo l'asse y
 */
void Powerup::setSpeed(float x, float y) {
	this -> speed.x = x; 
	this -> speed.y = y;
}

/**
 *	@brief Restituisce la posizione corrente del powerup
 *
 *	@return Il vettore posizione corrente del powerup
 */
sf::Vector2f Powerup::getPosition() {
	return this -> sprite.getPosition();
}

/**
 *	@brief Imposta la posizione corrente del powerup
 *
 *	@param x componente del vettore posizione lungo l'asse x
 *	@param y componente del vettore posizione lungo l'asse y
 */
void Powerup::setPosition(float x, float y) {
	this -> sprite.setPosition({x, y});
}

/**
 *	@brief Restituisce le dimensioni del powerup
 *
 *	@return Il vettore contenente le dimensioni dell'oggetto
 */
sf::Vector2i Powerup::getSize() {
	return this -> size;
}

/**
 *	@brief Restituisce il rettangolo associato all'oggetto powerup
 *
 * 	@return Un rettangolo con origine e dimensioni del powerup
 */
sf::IntRect Powerup::getRectangle() {
	sf::Vector2f p = this -> getPosition();
	return sf::IntRect({(int) p.x, (int) p.y}, {size.x, size.y});
}

/**
 *	@brief Restituisce la sprite associata al powerup
 *
 *	@return La sprite associata al powerup
 */
sf::Sprite Powerup::getSprite() {
	return this -> sprite;
}
