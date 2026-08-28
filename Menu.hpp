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

/** Text for the Play menu entry. */
#define PLAY_ENTRY_TEXT "Play"

/** Text for the Quit menu entry. */
#define QUIT_ENTRY_TEXT "Quit"

/**
 *	@brief Returns the name of the entry in the main menu
 *
 *	@param id entry identifier
 *
 *	@return string containing the name of the entry
 */
static inline std::string getEntryName(main_entry_t id) {
	switch (id) {
		case PLAY_ENTRY: return PLAY_ENTRY_TEXT;
		case QUIT_ENTRY: return QUIT_ENTRY_TEXT;
	}
}

/** Vertical space between two entries (in pixels). */
#define VSPACE 64

/** Title of the level selection screen. */
#define SELECTION_TITLE "Select a level"

/** Enumerated type for the internal state of the menu. */
typedef enum {
	MAIN 		= 0,
	SELECTION 	= 1
} menu_mode_t;

/**
 *	@brief Represents the main menu of the game
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
 *	@brief Utility function for scrolling forward in the menu
 *
 *	@param id identifier of the currently selected entry
 *	@param n number of entries in the menu
 *	@return identifier of the next entry
 */
static inline int nextOption(int id, int n) {
	return ((id + 1) % n);
}

/**
 *	@brief Utility function for scrolling backward in the menu
 *
 *	@param id identifier of the currently selected entry
 *	@param n number of entries in the menu
 *	@return identifier of the previous entry
 */
static inline int prevOption(int id, int n) {
	if (id > 0) return ((id - 1) % n);
	return n - 1;
}

#endif
