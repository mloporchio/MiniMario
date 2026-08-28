/**
 *	@file PiranhaPlant.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Definition of the PiranhaPlant class
 */

#ifndef PIRANHAPLANT_H
#define PIRANHAPLANT_H

#include "Enemy.hpp"
#include "Textures.hpp"

/** Time elapsed before the PiranhaPlant texture changes. */
#define PIRANHAPLANT_ANIMATION_TIME 200

/** Height (in pixels) of the PiranhaPlant sprite. */
#define PIRANHAPLANT_HEIGHT 48

/**
 *	@brief Represents the PiranhaPlant, one of the enemies of the game
 */
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
 *	@brief Returns the next texture to be used for the PiranhaPlant
 *
 *	@param id current texture identifier
 *	
 *	@return next texture identifier
 */
static inline plant_texture_t nextPiranhaPlantTexture(plant_texture_t id) {
	return ((id == PLANT_0) ? PLANT_1 : PLANT_0);
}

#endif
