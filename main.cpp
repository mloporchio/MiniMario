/**
 *	@file main.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Main entry point of the game.
 *
 *	This is the main entry point of the game. 
 *	It contains the main() function, which creates the main window of the game and initializes the game scene.
 */

#include "Game.hpp"

int main(int argc, char const *argv[]) {
	Game myFavouriteGame;
	myFavouriteGame.run();
	return 0;
}
