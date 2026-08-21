/**
 *	@file Layer.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Contiene l'implementazione della classe Layer
 */

#include "Layer.hpp"
#include "Config.hpp"

/**
 *	@brief Costruttore della classe Layer
 */
Layer::Layer(sf::FloatRect viewR) : View(viewR) {
	// Non c'è niente da fare!
}

/**
 *	@brief Restituisce il rettangolo della vista del layer
 *
 *	@return Il rettangolo della vista corrente associata al layer
 */
sf::FloatRect Layer::getViewRectangle() {
	sf::Vector2f c = this -> getCenter();
	sf::Vector2f s = this -> getSize();
	return sf::FloatRect({c.x - (s.x / 2), c.y - (s.y / 2)}, {s.x, s.y});
}

/**
 *	@brief Restituisce il rettangolo di rendering del layer
 *
 *	@return Il rettangolo di rendering associato al layer
 *
 *	Il rettangolo "di rendering" è quella parte di livello considerata
 *	"attiva". Ad ogni istante si aggiornano solamente i blocchi e i nemici
 *	contenuti in essa, invece che quelli di tutto il livello. 
 *
 *	NOTA: Il rettangolo di rendering associato al layer è leggermente più
 *	largo rispetto al rettangolo della vista.
 */
sf::FloatRect Layer::getRenderRectangle() {
	sf::Vector2f c = this -> getCenter();
	sf::Vector2f s = this -> getSize();
	float left = c.x - (s.x / 2 + s.x / 4);
	return sf::FloatRect({left, 0}, {3 * s.x / 2, s.y});
}
