/**
 *	@file MenuEntry.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Definition of the MenuEntry class
 */

#ifndef MENUENTRY_H
#define MENUENTRY_H

#include <SFML/Graphics.hpp>

/**
 *	@brief Represents an entry of the game menu
 */
class MenuEntry : public sf::Text {
	private:
		bool selected;
	public:
		MenuEntry(const std::string &label, const sf::Font &font, int fontSize);
		std::string getLabel();
		void setLabel(const std::string &label);
		bool isSelected();
		void setSelected(bool v);
};

#endif
