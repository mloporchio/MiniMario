/**
 *	@file Layer.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Definition of the Layer class
 */

#ifndef LAYER_H
#define LAYER_H

#include <SFML/Graphics.hpp>

/**
 *	@brief Represents a layer of the game scene
 *
 *	The Layer class extends the concept of view provided by the SFML library.
 */
class Layer : public sf::View {
	public:
		Layer(sf::FloatRect viewR);
		sf::FloatRect getViewRectangle();
		sf::FloatRect getRenderRectangle();
};

#endif
