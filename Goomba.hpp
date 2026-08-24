/**
 *	@file Goomba.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Contiene la definizione della classe Goomba, relativa all'omonimo
 *	nemico di Mario all'interno del gioco
 */

#ifndef GOOMBA_H
#define GOOMBA_H

#include "Enemy.hpp"
#include "Textures.hpp"

/** Tempo che trascorre fra una texture e l'altra di Goomba. */
#define GOOMBA_ANIMATION_TIME 200
/** Velocità con cui si muove il nemico. */
#define GOOMBA_SPEED 7.0f

class Goomba : public Enemy {
	private:
		std::vector<sf::Texture> &textures;
		goomba_texture_t textureID;
		int elapsed;
	public:
		Goomba(float x, float y, std::vector<sf::Texture> &textures_);
		void update(sf::Time dt, std::vector<Block *> blocks,
			std::vector<Enemy *> enemies, int index);
		void handleXCollisions(float *px, float *py, float *vx,
			std::vector<Block *> blocks, std::vector<Enemy *> enemies,
			int index);
		void handleYCollisions(float *px, float *py, float *vy,
			std::vector<Block *> blocks, std::vector<Enemy *> enemies,
			int index);
};

/**
 *	@brief Funzione di utilità che restituisce la prossima texture per Goomba
 *
 *	@param id identificativo della texture corrente
 *
 *	@return L'identificativo della texture successiva
 */
static inline goomba_texture_t nextGoombaTexture(goomba_texture_t id) {
	if (id == GOOMBA_0) return GOOMBA_1;
	else return GOOMBA_0;
}

#endif
