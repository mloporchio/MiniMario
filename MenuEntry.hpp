/**
 *	@file MenuEntry.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Definizione della classe MenuEntry per le voci del menu
 */

#ifndef MENUENTRY_H
#define MENUENTRY_H

#include <SFML/Graphics.hpp>

class MenuEntry : public sf::Text {
	private:
		bool selected;
	public:
		MenuEntry(char *label, sf::Font *font, int fontSize);
		char *getLabel();
		void setLabel(char *label);
		bool isSelected();
		void setSelected(bool v);
};

#endif
