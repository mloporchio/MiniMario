/**
 *	@file Layer.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Definition of the Layer class
 *
 *	The Layer class extends the concept of view provided by the SFML library.
 */

#ifndef LAYER_H
#define LAYER_H

#include <SFML/Graphics.hpp>

class Layer : public sf::View {
	public:
		Layer(sf::FloatRect viewR);
		sf::FloatRect getViewRectangle();
		sf::FloatRect getRenderRectangle();
};

#endif
