/**
 *	@file Config.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Global definitions and configuration parameters for the game
 *
 *	This file contains macros, global definitions and configuration parameters for the game
 * 	(e.g., window size, title, framerate limit, level directory, fonts, etc.).
 */

#ifndef CONFIG_H
#define CONFIG_H

/** Width of the main window. */
#define W_WIDTH 1024
/** Height of the main window. */
#define W_HEIGHT 640
/** Title of the main window. */
#define W_TITLE "MiniMario"
/** Framerate limit for the main window. */
#define W_FRAMERATE_LIMIT 60
/** Path to the directory containing level files. */
#define LEVEL_DIRECTORY "./maps"
/** Path to the directory containing sound files. */
#define FONT_PATH "fonts/emulogic.ttf"
/** Current game mode. */
typedef enum {
	MENU = 0,
	PLAYING = 1,
	QUIT = 2
} game_mode_t;

// Macros for frequently used colors.
#define C_HALFTRANSP sf::Color(255, 255, 255, 128)
#define C_BACKGROUND sf::Color(85, 111, 255)
#define C_GREY sf::Color(128, 128, 128)
#define C_BLACK sf::Color::Black
#define C_WHITE sf::Color::White
#define C_RED sf::Color::Red
#define C_GREEN sf::Color::Green
#define C_BLUE sf::Color::Blue
#define C_YELLOW sf::Color::Yellow
#define C_MAGENTA sf::Color::Magenta
#define C_CYAN sf::Color::Cyan
#define C_TRANSP sf::Color::Transparent

#endif
