/*
 *	@file Game.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Implementazione della classe principale del gioco
 */

#include <ctime>
#include "Game.hpp"
#include "Config.hpp"
#include "Errors.hpp"

/**
 *	@brief Costruttore della classe di gioco
 */
Game::Game() : window(sf::VideoMode({W_WIDTH, W_HEIGHT}), W_TITLE) {
	// Inizializzo la finestra.
	this -> window.setVerticalSyncEnabled(true);
	this -> window.setFramerateLimit(W_FRAMERATE_LIMIT);
	this -> scene = NULL;
	this -> gameMode = MENU;
}

/**
 *	@brief Distruttore della classe di gioco
 */
Game::~Game() {
	if (scene) delete scene;
}

/**
 *	@brief Gestisce gli eventi indirizzati alla finestra principale di gioco
 */
void Game::handleEvent() {
	while (const std::optional<sf::Event> event = this->window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            this->window.close();
            continue;
        }
        switch (this->gameMode) {
            case MENU:
                this->mainMenu.handleEvent(*event);
                break;

            case PLAYING:
                this->scene->handleEvent(*event, &gameMode);
                break;

            default:
                break;
        }
    }
}

/**
 *	@brief Aggiorna lo stato corrente del gioco
 *
 *	@return 0 in caso di successo, 1 in caso di fallimento
 */
int Game::update() {
	switch (this -> gameMode) {
		// Finisco qui se sono nel menu principale del gioco.
		case MENU: {
			// Controllo se sono appena uscito dal livello.
			if (this -> scene) {
				// Cancello il livello.
				delete scene;
				this -> scene = NULL;
				// Resetto la vista.
				sf::View defaultView(sf::FloatRect({0, 0}, {W_WIDTH, W_HEIGHT}));
				window.setView(defaultView);
			}
			// Aggiorno il menu.
			this -> mainMenu.updateMenu(&(this -> gameMode));
			if (this -> gameMode == PLAYING) {
				// Open the level file and create a new scene.
				std::string levelPath = (this -> mainMenu).getLevelFile();
				this -> scene = new Scene(levelPath);
			}
			if (this -> gameMode == QUIT) this -> window.close();
		}; break;
		// Finisco qui se sto giocando.
		case PLAYING: {
			this -> scene -> updateScene();
		}; break;
		default: break;
	}
	return 0;
}

/**
 *	@brief Disegna il contenuto della finestra
 */
void Game::draw() {
	switch (this -> gameMode) {
		// Disegno il menu.
		case MENU: {
			this -> mainMenu.drawMenu(&(this -> window));
		}; break;
		// Disegno la schermata di gioco.
		case PLAYING: {
			this -> scene -> drawScene(&(this -> window));
		}; break;
		default: break;
	}
}

/**
 *	@brief Manda in esecuzione il game loop
 *
 *	@return 0 in caso di successo, 1 in caso di fallimento
 */
int Game::run() {
	while (window.isOpen()) {
        this -> handleEvent();
        if (this -> update()) return 1;
		this -> window.clear(C_BACKGROUND);
		// Da qui in poi si disegna...
		this -> draw();
		// Fine dei disegni...
		this -> window.display();
    }
	return 0;
}
