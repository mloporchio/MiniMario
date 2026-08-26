/**
 *	@file Block.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Definition of the Block class
 *
 *	The Block is the base class for all elements in the game.
 */

#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>
#include "Tilemap.hpp"

class Block {
	protected:
		block_t type;
		bool active;
		bool collidable;
		sf::Sprite sprite;
	public:
		Block(block_t type_, float x, float y, sf::Texture &t);
		~Block();
		block_t getType();
		bool isActive();
		void setActive(bool v);
		bool isCollidable();
		void setCollidable(bool v);
		sf::Vector2f getPosition();
		void setPosition(float x, float y);
		sf::IntRect getRectangle();
		sf::Sprite getSprite();
		virtual void update(sf::Time dt) {};
		virtual void hit() {};
};

#endif
