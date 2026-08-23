/**
 *	@file Powerup.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Definizione della classe relativa al generico powerup del gioco
 */

#ifndef POWERUP_H
#define POWERUP_H

#include "Block.hpp"

/** Tipo enumerato per indicizzare le varie tipologie di powerup. */
typedef enum {
	SUPER_MUSHROOM = 0,
	ONEUP_MUSHROOM = 1,
	COIN_POWERUP = 2
} powerup_t;

class Powerup {
	protected:
		powerup_t type;
		bool taken;
		sf::Vector2f speed;
		sf::Vector2i size;
		sf::Sprite sprite;
	public:
		Powerup(powerup_t type, float x, float y, int w, int h, sf::Texture &t);
		powerup_t getType();
		bool isTaken();
		void setTaken(bool v);
		sf::Vector2f getSpeed();
		void setSpeed(float x, float y);
		sf::Vector2f getPosition();
		void setPosition(float x, float y);
		sf::Vector2i getSize();
		sf::IntRect getRectangle();
		sf::Sprite getSprite();
		// Metodi virtuali: da implementare da parte delle sottoclassi.
		virtual void update(sf::Time dt, std::vector<Block *> blocks) {};
		virtual void handleXCollisions(float *px, float *py, float *vx, std::vector<Block *> blocks) {};
		virtual void handleYCollisions(float *px, float *py, float *vy, std::vector<Block *> blocks) {};
};

#endif
