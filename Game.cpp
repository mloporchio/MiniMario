/** 
 *	@file Game.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Implementation of the Game class
 */

#include <ctime>
#include "Game.hpp"
#include "Config.hpp"

/**
 *	@brief Game constructor
 */
Game::Game() : 
	window(sf::VideoMode({W_WIDTH, W_HEIGHT}), W_TITLE), 
	scene(NULL), 
	gameMode(MENU) 
{
	// Initialize the window.
	this -> window.setVerticalSyncEnabled(true);
	this -> window.setFramerateLimit(W_FRAMERATE_LIMIT);
}

/**
 *	@brief Game destructor
 */
Game::~Game() {
	if (scene) delete scene;
}

/**
 *	@brief Handles all events directed to the main game window
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
                this->scene->handleEvent(*event, this->gameMode);
                break;

            default:
                break;
        }
    }
}

/**
 *	@brief Updates the current game state
 */
void Game::update() {
	switch (this -> gameMode) {
		// Main menu.
		case MENU: {
			// Check if we have just left the level.
			if (this -> scene) {
				// Delete the level scene.
				delete scene;
				this -> scene = NULL;
				// Reset the view.
				sf::View defaultView(sf::FloatRect({0, 0}, {W_WIDTH, W_HEIGHT}));
				window.setView(defaultView);
			}
			// Update the menu.
			this -> mainMenu.updateMenu(this -> gameMode);
			if (this -> gameMode == PLAYING) {
				// Open the level file and create a new scene object.
				std::string levelPath = (this -> mainMenu).getLevelFile();
				this -> scene = new Scene(levelPath);
			}
			if (this -> gameMode == QUIT) this -> window.close();
		}; break;
		// Playing.
		case PLAYING: {
			// Update the scene.
			this -> scene -> updateScene();
		}; break;
		default: break;
	}
}

/**
 *	@brief Draws the content of the game window.
 */
void Game::draw() {
	switch (this -> gameMode) {
		// Draw the main menu.
		case MENU: {
			this -> mainMenu.drawMenu(this -> window);
		}; break;
		// Draw the game scene.
		case PLAYING: {
			this -> scene -> drawScene(this -> window);
		}; break;
		default: break;
	}
}

/**
 *	@brief Runs the game loop.
 */
void Game::run() {
	while (window.isOpen()) {
        this -> handleEvent();
        this -> update();
		this -> window.clear(C_BACKGROUND);
		// Draw the content of the window.
		this -> draw();
		// Display the window.
		this -> window.display();
    }
}
