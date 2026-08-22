/**
 *	@file Coin.hpp
 *	@author Matteo Loporchio
 *	
 *	@brief Contiene la definizione della classe Coin per le monete presenti
 *	all'interno del gioco
 */

#ifndef COIN_H
#define COIN_H

#include <SFML/Graphics.hpp>
#include "Block.hpp"
#include "Textures.hpp"

class Coin : public Block {
	private:
		std::vector<sf::Texture> *textures;
		coin_texture_t textureID;
		int elapsed;
	public:
		Coin(float x, float y, std::vector<sf::Texture> *textures);
		void hit();
		void update(sf::Time dt);
};

/**
 *	@brief Funzione di utilità che restituisce la prossima texture da
 *	utilizzare per la moneta
 *
 *	@param id identificativo della texture corrente
 *	
 *	@return L'identificativo della prossima texture da utilizzare
 */
static inline coin_texture_t nextCoinTexture(coin_texture_t id) {
	return ((coin_texture_t) ((((int) id) + 1) % COIN_TEXTURE_N));
}


#endif
