/**
 *	@file PiranhaPlant.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Contiene la definizione della classe PiranhaPlant relativa
 *	all'omonimo nemico di Mario
 */

#ifndef PIRANHAPLANT_H
#define PIRANHAPLANT_H

#include "Enemy.hpp"
#include "Textures.hpp"

/** Tempo trascorso fra una texture e l'altra della Piranha Plant. */
#define PIRANHAPLANT_ANIMATION_TIME 200

/** Altezza del nemico Piranha Plant. */
#define PIRANHAPLANT_HEIGHT 48

class PiranhaPlant : public Enemy {
	private:
		std::vector<sf::Texture> &textures;
		plant_texture_t textureID;
		int elapsed;
	public:
		PiranhaPlant(float x, float y, std::vector<sf::Texture> &textures_);
		void update(sf::Time dt);
};

/**
 *	@brief Restituisce la prossima texture da utilizzare per la Piranha Plant
 *
 *	@param id identificativo della texture corrente
 *	
 *	@return L'identificativo della prossima texture da utilizzare
 */
static inline plant_texture_t nextPiranhaPlantTexture(plant_texture_t id) {
	return ((id == PLANT_0) ? PLANT_1 : PLANT_0);
}

#endif
