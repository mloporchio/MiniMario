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
 *	@param textures_ riferimento al vettore delle texture da utilizzare
 */
Coin::Coin(float x, float y, std::vector<sf::Texture> &textures_) : 
	Block(COIN, x, y, textures_[0]), 
	textures(textures_),
	elapsed(0), 
	textureID(STILL) 
{
	// The following are automatically set:
	// this -> active = true;
	// this -> collidable = true;
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
		this -> sprite.setTexture(textures[(int) textureID]);
	}
}
