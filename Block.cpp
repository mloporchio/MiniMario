/**
 *	@file Block.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Questo file contiene l'implementazione della classe Block
 *	relativa al generico blocco che costituisce il livello
 */

#include <cmath>
#include "Block.hpp"
#include "Physics.hpp"

/**
 *	@brief Costruttore della classe Block
 *	
 *	@param type identificativo del tipo di blocco
 *	@param x posizione iniziale sull'asse x
 *	@param y posizione iniziale sull'asse y
 *	@param t puntatore alla texture da usare
 */
Block::Block(block_t type, int x, int y, sf::Texture *t) : sprite(*t) {
	this -> type = type;
	this -> active = true;
	this -> collidable = true;
	this -> sprite.setPosition({static_cast<float>(x), static_cast<float>(y)});
	//this -> sprite.setTexture(*t);
}

/**
 *	@brief Distruttore della classe Block
 */
Block::~Block() {
	// Do nothing!
}

/**
 *	@brief Restituisce il tipo del blocco
 *	
 *	@return L'identificativo del tipo di blocco
 */
block_t Block::getType() {
	return this -> type;
}

/**
 *	@brief Dice se il blocco è attivo oppure no
 *
 *	@return Un valore di verità che indica se il blocco è attivo
 */
bool Block::isActive() {
	return this -> active;
}

/**
 *	@brief Attiva/disattiva il blocco
 *
 *	@param v valore di verità che indica se attivare o disattivare
 */
void Block::setActive(bool v) {
	this -> active = v;
}

/**
 *	@brief Indica se il blocco è soggetto a collisioni
 *
 * 	@return Un valore di verità che indica se il blocco è soggetto
 *	alle collisioni oppure no
 */
bool Block::isCollidable() {
	return this -> collidable;
}

/**
 *	@brief Rende il blocco soggetto/non soggetto a collisioni
 *
 *	@param v valore di verità che indica se il blocco è o non è
 *	soggetto a collisioni
 */
void Block::setCollidable(bool v) {
	this -> collidable = v;
}

/**
 *	@brief Imposta la posizione corrente del blocco
 *
 *	@param x ascissa del punto
 *	@param y ordinata del punto
 */
void Block::setPosition(float x, float y) {
	this -> sprite.setPosition({x, y});
}

/**
 *	@brief Restiuisce la posizione corrente del blocco
 *
 *	@return Il vettore posizione del blocco
 */
sf::Vector2f Block::getPosition() {
	return (this -> sprite.getPosition());
}

/**
 *	@brief Restituisce il bounding rectangle del blocco
 *
 *	@return Il rettangolo che contiene il blocco
 */
sf::IntRect Block::getRectangle() {
	sf::Vector2f p = this -> getPosition();
	return sf::IntRect({(int) p.x, (int) p.y}, {SIZE, SIZE});
}

/**
 *	@brief Restituisce la sprite associata al blocco
 *
 *	@return La sprite associata al blocco
 */
sf::Sprite Block::getSprite() {
	return this -> sprite;
}
