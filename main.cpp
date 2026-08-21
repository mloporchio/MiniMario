/**
 *	@file main.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Entry point di tutto il gioco
 *
 *	Questo è il file principale del gioco, contenente la funzione
 *	main(). Qui viene creata la finestra principale del gioco e viene
 *	inizializzata la scena di gioco.
 */

#include <cstdlib>
#include "Game.hpp"

int main(int argc, char const *argv[]) {
	Game myFavouriteGame;
	return ((!myFavouriteGame.run()) ? EXIT_SUCCESS : EXIT_FAILURE);
}
