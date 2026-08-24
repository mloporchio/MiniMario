/*
 *	@file Game.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Contiene la definizione della classe principale del gioco
 */

#ifndef GAME_H
#define GAME_H

#include "Menu.hpp"
#include "Scene.hpp"
#include "Config.hpp"

// Definizione della classe del gioco.
class Game {
	private:
		sf::RenderWindow window;
		Scene *scene;
		Menu mainMenu;
		game_mode_t gameMode;
		void handleEvent();
		int update();
		void draw();
	public:
		Game();
		~Game();
		int run();
};

#endif
