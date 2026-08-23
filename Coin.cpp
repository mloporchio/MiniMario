/**
 *	@file Coin.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Contiene l'implementazione della classe Coin relativa alle
 *	monete presenti nel gioco
 */

#include "Coin.hpp"
#include "Config.hpp"

/**
 *	@brief Costruttore della classe Coin
 *
 *	@param x posizione del blocco sull'asse x
 *	@param y posizione del blocco sull'asse y
 *	@param textures puntatore al vettore delle texture da utilizzare
 */
Coin::Coin(float x, float y, std::vector<sf::Texture> *textures) : Block(COIN, x, y, ((*textures)[0])) {
	// Automaticamente vengono settati:
	// this -> active = true;
	// this -> collidable = true;
	this -> textures = textures;
	this -> elapsed = 0;
	this -> textureID = STILL;
}

/**
 *	@brief Funzione invocata quando la moneta viene raccolta
 */
void Coin::hit() {
	this -> active = false;
	this -> collidable = false;
}

/**
 *	@brief Funzione di aggiornamento della moneta
 *
 *	@param dt intervallo di tempo dall'ultimo aggiornamento
 */
void Coin::update(sf::Time dt) {
	if (this -> active) {
		textureID = nextCoinTexture(textureID);
		this -> sprite.setTexture((*textures)[(int) textureID]);
	}
}
