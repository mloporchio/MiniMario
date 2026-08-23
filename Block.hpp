/**
 *	@file Block.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Contiene la definizione della classe Block
 *
 *	La classe modella tutte le entità di tipo blocco. Un blocco è un
 *	generico elemento del mondo in cui si trova Mario.
 *
 *	I blocchi hanno tutti una dimensione fissa SIZE x SIZE, dove SIZE
 *	è un parametro definito nel file Physics.hpp.
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
		Block(block_t type, float x, float y, sf::Texture &t);
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
