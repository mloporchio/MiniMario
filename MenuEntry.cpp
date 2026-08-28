/**
 *	@file MenuEntry.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Implementation of the MenuEntry class
 */

#include <cstring>
#include "MenuEntry.hpp"
#include "Config.hpp"

/**
 *	@brief MenuEntry constructor
 *
 *	@param label string representing the entry's label
 *	@param font font for the entry's label
 *	@param fontSize font size for the entry's label
 */
MenuEntry::MenuEntry(const std::string &label, const sf::Font &font, int fontSize) : sf::Text(font, label, fontSize) {
	// this -> setString(label);
	// this -> setCharacterSize(fontSize);
	// this -> setFont(*font);
	this -> setSelected(false);
}

/**
 *	@brief Returns the label associated with the MenuEntry
 *
 *	@return string containing the MenuEntry's label
 */
std::string MenuEntry::getLabel() {
	sf::String nameSfString = this -> getString();
	return nameSfString.toAnsiString();
}

/**
 *	@brief Sets the label associated with the MenuEntry
 *
 *	@param label string containing the MenuEntry's label
 */
void MenuEntry::setLabel(const std::string &label) {
	// Nothing to do here.
	return;
}

/**
 *	@brief Tells whether the MenuEntry is selected or not
 *
 *	@return true if the MenuEntry is selected, false otherwise
 */
bool MenuEntry::isSelected() {
	return this -> selected;
}

/**
 *	@brief Sets whether the MenuEntry is selected or not
 *
 * 	@param v true to make the MenuEntry selected, false to make it unselected
 */
void MenuEntry::setSelected(bool v) {
	this -> selected = v;
	if (this -> selected) this -> setFillColor(C_YELLOW);
	else this -> setFillColor(C_WHITE);
	return;
}
