/**
 *	@file PiranhaPlant.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Contiene l'implementazione della classe PiranhaPlant
 */

#include "PiranhaPlant.hpp"
#include "Physics.hpp"

/**
 *	@brief Costruttore della classe PiranhaPlant
 *	
 *	@param x posizione lungo l'asse x
 *	@param y posizione lungo l'asse y
 *	@param textures puntatore al vettore delle texture da utilizzare
 */
PiranhaPlant::PiranhaPlant(int x, int y, std::vector<sf::Texture> *textures)
	: Enemy(PIRANHA_PLANT, x, y, SIZE, PIRANHAPLANT_HEIGHT, ((*textures)[0]))
{
	this -> textures = textures;
	this -> textureID = PLANT_0;
	this -> elapsed = 0;
}

/**
 *	@brief Funzione di aggiornamento dell'elemento PiranhaPlant
 *
 *	@param dt intervallo di tempo dall'ultimo aggiornamento
 */
void PiranhaPlant::update(sf::Time dt) {
	// Aggiorno la texture del personaggio.
	if (elapsed >= PIRANHAPLANT_ANIMATION_TIME) {
		this -> textureID = nextPiranhaPlantTexture(this -> textureID);
		elapsed = 0;
	}
	else elapsed += dt.asMilliseconds();
	this -> sprite.setTexture((*textures)[(int) textureID]);
}
