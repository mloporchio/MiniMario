/**
 *	@file Enemy.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Contiene la definizione della classe Enemy, che modella il
 *	generico nemico di Mario
 */

#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Block.hpp"
#include "Tilemap.hpp"

class Enemy {
	protected:
		block_t type;
		bool onGround;
		bool alive;
		bool collidable;
		sf::Vector2f speed;
		sf::Vector2i size;
		sf::Sprite sprite;
	public:
		Enemy(block_t type_, float x, float y, int w, int h, sf::Texture &t);
		~Enemy();
		block_t getType();
		bool isAlive();
		void setAlive(bool v);
		bool isCollidable();
		void setCollidable(bool v);
		sf::Vector2f getSpeed();
		void setSpeed(float x, float y);
		sf::Vector2f getPosition();
		void setPosition(float x, float y);
		sf::Vector2i getSize();
		sf::IntRect getRectangle();
		sf::Sprite getSprite();
		virtual void update(sf::Time dt, std::vector<Block *> blocks) {};
		virtual void handleXCollisions(float *px, float *py, float *vx,
			std::vector<Block *> blocks, std::vector<Enemy *> enemies) {};
		virtual void handleYCollisions(float *px, float *py, float *vy,
			std::vector<Block *> blocks, std::vector<Enemy *> enemies) {};
};

#endif
