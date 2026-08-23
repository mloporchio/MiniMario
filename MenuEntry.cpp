/**
 *	@file MenuEntry.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Implementazione della classe relativa alla menu entry
 */

#include <cstring>
#include "MenuEntry.hpp"
#include "Config.hpp"

/**
 *	@brief Costruttore della classe MenuEntry
 *
 *	@param label stringa che costituisce il testo
 *	@param font puntatore al font da utilizzare
 *	@param fontSize dimensione del font
 */
MenuEntry::MenuEntry(const std::string &label, sf::Font *font, int fontSize) : sf::Text(*font, label, fontSize) {
	// this -> setString(label);
	// this -> setCharacterSize(fontSize);
	// this -> setFont(*font);
	this -> setSelected(false);
}

/**
 *	@brief Restituisce il testo associato all'entry
 *
 *	@return Una stringa contenente il testo in caso di successo, NULL in
 *	caso di fallimento
 */
std::string MenuEntry::getLabel() {
	sf::String nameSfString = this -> getString();
	return nameSfString.toAnsiString();
}

/**
 *	@brief Imposta il testo associato all'entry
 *
 *	@param label stringa con il testo associato all'entry
 */
void MenuEntry::setLabel(const std::string &label) {
	// Per ora non fa nulla.
	return;
}

/**
 *	@brief Dice se l'entry è selezionata oppure no
 *
 *	@return Un valore di verità che indica se l'entry è selezionata
 */
bool MenuEntry::isSelected() {
	return this -> selected;
}

/**
 *	@brief Seleziona o deseleziona l'entry
 *
 * 	@param v valore di verità per selezionare o deselezionare
 */
void MenuEntry::setSelected(bool v) {
	this -> selected = v;
	if (this -> selected) this -> setFillColor(C_YELLOW);
	else this -> setFillColor(C_WHITE);
	return;
}
