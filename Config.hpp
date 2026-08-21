/**
 *	@file Config.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Definizioni e parametri globali
 *
 *	Questo file contiene macro, definizioni globali e parametri di
 *	configurazione del gioco. Ad esempio, dimensione e titolo delle finestre,
 *	colori e altre risorse utilizzate frequentemente.
 */

#ifndef CONFIG_H
#define CONFIG_H

/** Larghezza della finestra principale. */
#define W_WIDTH 1024
/** Altezza della finestra principale. */
#define W_HEIGHT 640
/** Titolo della finestra principale. */
#define W_TITLE "MiniMario"
/** Limite sul framerate per la finestra principale. */
#define W_FRAMERATE_LIMIT 60
/** Percorso della cartella in cui memorizzare i livelli. */
#define LEVEL_DIRECTORY "./maps"
/** Font utilizzato per le scritte del menu. */
#define FONT_PATH "fonts/emulogic.ttf"
/** Dimensione predefinita dei buffer. */
#define BUFSIZE 1024
/** Stato corrente del gioco. */
typedef enum {
	MENU = 0,
	PLAYING = 1,
	QUIT = 2
} game_mode_t;

// Colori utilizzati più frequentemente.
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
