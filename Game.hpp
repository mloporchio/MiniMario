/** 
 *	@file Game.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Definition of the Game class
 *
 *	The Game class is the main class of the game. It contains the main menu and the scene.
 */

#ifndef GAME_H
#define GAME_H

#include "Menu.hpp"
#include "Scene.hpp"
#include "Config.hpp"

class Game {
	private:
		sf::RenderWindow window;
		Scene *scene;
		Menu mainMenu;
		game_mode_t gameMode;
		void handleEvent();
		void update();
		void draw();
	public:
		Game();
		~Game();
		void run();
};

#endif
