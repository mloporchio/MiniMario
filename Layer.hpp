/**
 *	@file Layer.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Contiene la definizione della classe Layer
 *
 *	Il layer estende il concetto di vista fornito da SFML.
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
