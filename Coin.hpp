/**
 *	@file Coin.hpp
 *	@author Matteo Loporchio
 *	
 *	@brief Definition of the Coin class
 */

#ifndef COIN_H
#define COIN_H

#include <SFML/Graphics.hpp>
#include "Block.hpp"
#include "Textures.hpp"

/**
 *	@brief Represents a coin, a collectible item of the game
 */
class Coin : public Block {
	private:
		std::vector<sf::Texture> &textures;
		coin_texture_t textureID;
		int elapsed;
	public:
		Coin(float x, float y, std::vector<sf::Texture> &textures_);
		void hit();
		void update(sf::Time dt);
};

/**
 *	@brief Returns the identifier of the next texture to be used for the Coin
 *
 *	@param id current texture identifier
 *	
 *	@return identifier of the next texture to be used
 */
static inline coin_texture_t nextCoinTexture(coin_texture_t id) {
	return ((coin_texture_t) ((((int) id) + 1) % COIN_TEXTURE_N));
}


#endif
