/**
 *	@file Menu.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Definition of the Menu class
 */

#ifndef MENU_H
#define MENU_H

#include "MenuEntry.hpp"
#include "Config.hpp"
#include <SFML/Graphics.hpp>

/** Font size for menu entries. */
#define FONT_SIZE 20

/** Number of entries in the main menu. */
#define MAIN_ENTRY_N 2

/** Enumeration for identifying main menu entries. */
typedef enum {
	PLAY_ENTRY = 0,
	QUIT_ENTRY = 1
} main_entry_t;

#define PLAY_ENTRY_TEXT "Play"
#define QUIT_ENTRY_TEXT "Quit"

/**
 *	@brief Restituisce il nome della voce del menu principale
 *
 *	@param id identificativo della voce
 *
 *	@return Una stringa contenente il nome della voce
 */
static inline std::string getEntryName(main_entry_t id) {
	switch (id) {
		case PLAY_ENTRY: return PLAY_ENTRY_TEXT;
		case QUIT_ENTRY: return QUIT_ENTRY_TEXT;
	}
}

/** Spazio verticale fra una voce e l'altra (in pixel). */
#define VSPACE 64

/** Titolo della schermata di selezione livelli. */
#define SELECTION_TITLE "Select a level"

/** Tipo enumerato per lo stato interno del menu. */
typedef enum {
	MAIN 		= 0,
	SELECTION 	= 1
} menu_mode_t;

/**
 *	@brief La classe che rappresenta il menu principale del gioco
 */
class Menu {
	private:
		int selected;
		bool enterKeyPressed;
		std::optional<std::string> levelName;
		menu_mode_t menuMode;
		std::vector<MenuEntry> mainEntries;
		std::vector<MenuEntry> levelEntries;
		sf::Clock timer;
		sf::Font labelFont;
		sf::Texture bgImage;
		sf::Sprite bgSprite;
		sf::Texture fgImage;
		sf::Sprite fgSprite;
		sf::Texture logoImage;
		sf::Sprite logoSprite;
		sf::Text selectionTitle;
		int loadLevelEntries();
	public:
		Menu();
		void handleEvent(sf::Event e);
		void updateMenu(game_mode_t &gameMode);
		void drawMenu(sf::RenderWindow &window);
		std::string getLevelFile();
};

/**
 *	@brief Funzione di utilità per lo scorrimento in avanti
 *	delle voci nel menu
 *
 *	@param id identificativo della voce correntemente selezionata
 *	@param n numero di voci nel menu
 *	@return L'identificativo della voce successiva
 */
static inline int nextOption(int id, int n) {
	return ((id + 1) % n);
}

/**
 *	@brief Funzione di utilità per lo scorrimento all'indietro
 *	delle voci nel menu
 *
 *	@param id identificativo della voce correntemente selezionata
 *	@param n numero di voci nel menu
 *	@return L'identificativo della voce precedente
 */
static inline int prevOption(int id, int n) {
	if (id > 0) return ((id - 1) % n);
	return n - 1;
}

#endif
