/**
 *	@file Koopa.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Contiene la definizione della classe relativa al nemico Koopa
 */

#ifndef KOOPA_H
#define KOOPA_H

#include "Enemy.hpp"
#include "Physics.hpp"
#include "Textures.hpp"

/** Tempo di animazione per Koopa. */
#define KOOPA_ANIMATION_TIME 200
/** Numero massimo di rimbalzi del guscio di Koopa. */
#define KOOPA_BOUNCE_MAX 3
/** Altezza del personaggio Koopa. */
#define KOOPA_HEIGHT 48
/** Velocità standard del personaggio Koopa. */
#define KOOPA_SPEED 5.0f

class Koopa : public Enemy {
	private:
		block_t koopaType;
		koopa_texture_t textureID;
		std::vector<sf::Texture> *textures;
		int elapsed;
		int bounce;
		bool hit;
		void checkBounce();
	public:
		Koopa(float x, float y, block_t k, std::vector<sf::Texture> *textures);
		bool isOnGround();
		bool isHit();
		void setHit();
		bool isMoving();
		void move(direction_t d);
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
 *	@brief Restituisce la prossima texture da utilizzare per Koopa
 *
 * 	@param id identificativo della texture in uso
 *
 * 	@return Identificativo della nuova texture da applicare
 */
static inline koopa_texture_t nextKoopaTexture(koopa_texture_t id) {
	switch (id) {
		case GREEN_KOOPA_0: return GREEN_KOOPA_1;
	 	case GREEN_KOOPA_1: return GREEN_KOOPA_0;
	 	case GREEN_KOOPA_0_L: return GREEN_KOOPA_1_L;
	 	case GREEN_KOOPA_1_L: return GREEN_KOOPA_0_L;
	 	case RED_KOOPA_0: return RED_KOOPA_1;
	 	case RED_KOOPA_1: return RED_KOOPA_0;
	 	case RED_KOOPA_0_L: return RED_KOOPA_1_L;
	 	case RED_KOOPA_1_L: return RED_KOOPA_0_L;
	 	case GREEN_KOOPA_SHELL: return GREEN_KOOPA_SHELL;
	 	case RED_KOOPA_SHELL: return RED_KOOPA_SHELL;
	}
}

/**
 *	@brief Restituisce l'identificativo della texture simmetrizzata per Koopa
 *
 * 	@param id l'identificativo della texture in uso
 *
 * 	@return Identificativo della nuova texture da applicare
 */
static inline koopa_texture_t flipKoopaTexture(koopa_texture_t id) {
	switch (id) {
		case GREEN_KOOPA_0: return GREEN_KOOPA_0_L;
	 	case GREEN_KOOPA_1: return GREEN_KOOPA_1_L;
	 	case GREEN_KOOPA_0_L: return GREEN_KOOPA_0;
	 	case GREEN_KOOPA_1_L: return GREEN_KOOPA_1;
	 	case RED_KOOPA_0: return RED_KOOPA_0_L;
	 	case RED_KOOPA_1: return RED_KOOPA_1_L;
	 	case RED_KOOPA_0_L: return RED_KOOPA_0;
	 	case RED_KOOPA_1_L: return RED_KOOPA_1;
	 	case GREEN_KOOPA_SHELL: return GREEN_KOOPA_SHELL;
	 	case RED_KOOPA_SHELL: return RED_KOOPA_SHELL;
	}
}

#endif
