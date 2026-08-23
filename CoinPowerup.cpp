/**
 *	@file CoinPowerup.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Contiene l'implementazione della classe relativa al powerup
 *	di tipo moneta
 */

#include "CoinPowerup.hpp"
#include "Physics.hpp"

/**
 *	@brief Costruttore della classe CoinPowerup
 *
 *	@param x posizione iniziale lungo l'asse x
 *	@param y posizione iniziale lungo l'asse y
 *	@param t puntatore alla texture da utilizzare
 */ 
CoinPowerup::CoinPowerup(float x, float y, sf::Texture &t) 
: Powerup(COIN_POWERUP, x, y, SIZE, SIZE, t) 
{
	this -> y0 = y;
	this -> setSpeed(0, -COIN_POWERUP_SPEED);
}

/**
 *	@brief Funzione di aggiornamento del powerup CoinPowerup
 *
 *	@param dt intervallo di tempo dall'ultimo aggiornamento
 */
void CoinPowerup::update(sf::Time dt) {
	float posX = this -> sprite.getPosition().x;
	float posY = this -> sprite.getPosition().y;
	float velY = this -> speed.y;
	posY += velY * 0.2f;
	// Controllo se è giunto il momento di disattivarlo.
	if (posY < y0 - SIZE) {
		this -> taken = true;
		return;
	}
	// Scrivo i risultati dei calcoli.
	this -> setPosition(posX, posY);
	this -> speed.y = velY;
}
