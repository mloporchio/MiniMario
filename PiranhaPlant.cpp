/**
 *	@file PiranhaPlant.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Implementation of the PiranhaPlant class
 */

#include "PiranhaPlant.hpp"
#include "Physics.hpp"

/**
 *	@brief PiranhaPlant constructor
 *	
 *	@param x initial position along the x axis
 *	@param y initial position along the y axis
 *	@param textures_ vector of textures to be used for the PiranhaPlant sprite
 */
PiranhaPlant::PiranhaPlant(float x, float y, std::vector<sf::Texture> &textures_) :
	Enemy(PIRANHA_PLANT, x, y, SIZE, PIRANHAPLANT_HEIGHT, textures_[0]),
	textures(textures_),
	textureID(PLANT_0),
	elapsed(0)
{
	// Nothing else to do here.
}

/**
 *	@brief Update function for the PiranhaPlant object
 *
 *	@param dt time elapsed since last update
 */
void PiranhaPlant::update(sf::Time dt) {
	// Update the texture of the PiranhaPlant.
	if (elapsed >= PIRANHAPLANT_ANIMATION_TIME) {
		this -> textureID = nextPiranhaPlantTexture(this -> textureID);
		elapsed = 0;
	}
	else elapsed += dt.asMilliseconds();
	this -> sprite.setTexture(textures[(int) textureID]);
}
