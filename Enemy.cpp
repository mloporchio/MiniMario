/**
 *	@file Enemy.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Contiene l'implementazione della classe Enemy relativa al
 *	generico nemico di Mario
 */

#include "Enemy.hpp"
#include "Physics.hpp"

/**
 *	@brief Costruttore della classe Enemy
 *
 *	@param type elemento della tilemap che identifica il tipo di nemico
 *	@param x posizione inziale sull'asse x
 *	@param y posizione iniziale sull'asse y
 *	@param w larghezza dell'elemento
 *	@param h altezza dell'elemento
 *	@param t puntatore alla texture da utilizzare
 */
Enemy::Enemy(block_t type, int x, int y, int w, int h, sf::Texture *t) : sprite(*t) {
	this -> type = type;
	this -> onGround = false;
	this -> alive = true;
	this -> collidable = true;
	this -> speed.x = 0;
	this -> speed.y = 0;
	//this -> sprite.setTexture(*t);
	this -> sprite.setPosition({static_cast<float>(x), static_cast<float>(y)});
	this -> size.x = w;
	this -> size.y = h;
}

/**
 *	@brief Distruttore della classe Enemy
 */
Enemy::~Enemy() {}

/**
 *	@brief Restituisce il tipo del nemico corrente
 *
 *	@return Identificativo del tipo di nemico
 */
block_t Enemy::getType() {
	return this -> type;
}

/**
 *	@brief Dice se il nemico è vivo oppure no
 *
 *	@return Un valore di verità che indica se il nemico è vivo o no
 */
bool Enemy::isAlive() {
	return this -> alive;
}

/**
 *	@brief Rende il nemico vivo/morto
 *
 *	@param v valore di verità che indica se il nemico è vivo o morto
 */
void Enemy::setAlive(bool v) {
	this -> alive = v;
}

/**
 *	@brief Indica se il nemico è soggetto a collisioni
 *	
 *	@return Un valore di verità che indica se il nemico è soggetto
 *	alle collisioni oppure no
 */
bool Enemy::isCollidable() {
	return this -> collidable;
}

/**
 *	@brief Rende il nemico soggetto/non soggetto a collisioni
 *
 *	@param v valore di verità che indica se il nemico è o non è
 *	soggetto a collisioni
 */
void Enemy::setCollidable(bool v) {
	this -> collidable = v;
}

/**
 *	@brief Restituisce la velocità corrente del nemico
 *
 *	@return Il vettore velocità del nemico
 */
sf::Vector2f Enemy::getSpeed() {
	return this -> speed;
}

/**
 *	@brief Imposta la velocità corrente del nemico
 *
 *	@param x componente del vettore lungo l'asse x
 *	@param y componente del vettore lungo l'asse y
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
