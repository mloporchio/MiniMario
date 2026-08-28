/**
 *	@file Layer.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Implementation of the Layer class
 */

#include "Layer.hpp"
#include "Config.hpp"

/**
 *	@brief Layer constructor
 *
 *	@param viewR initial view rectangle
 */
Layer::Layer(sf::FloatRect viewR) : View(viewR) {
	// Nothing else to do here.
}

/**
 *	@brief Returns the view rectangle of the layer
 *
 *	@return view rectangle of the layer
 */
sf::FloatRect Layer::getViewRectangle() {
	sf::Vector2f c = this -> getCenter();
	sf::Vector2f s = this -> getSize();
	return sf::FloatRect({c.x - (s.x / 2), c.y - (s.y / 2)}, {s.x, s.y});
}

/**
 *	@brief Returns the rendering rectangle of the layer
 *
 *	@return rendering rectangle of the layer
 *
 *	The rendering rectangle is the part of the level considered "active". 
 *	Only the blocks and enemies contained in this rectangle are updated at any given time, 
 *	instead of the entire level. Note that the rendering rectangle of the layer is slightly 
 *	larger than the view rectangle.
 */
sf::FloatRect Layer::getRenderRectangle() {
	sf::Vector2f c = this -> getCenter();
	sf::Vector2f s = this -> getSize();
	float left = c.x - (s.x / 2 + s.x / 4);
	return sf::FloatRect({left, 0}, {3 * s.x / 2, s.y});
}
