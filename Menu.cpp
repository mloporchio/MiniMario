/**
 *	@file Menu.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Implementation of the Menu class
 */

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <filesystem>
#include "Menu.hpp"
#include "Textures.hpp"

/**
 *	@brief Menu constructor
 */
Menu::Menu() : 
	bgImage(BACKGROUND_TEXTURE), 
	bgSprite(bgImage),
	fgImage(MENU_FOREGROUND_TEXTURE), 
	fgSprite(fgImage),
	logoImage(LOGO_TEXTURE), 
	logoSprite(logoImage),
	labelFont(FONT_PATH),
	selectionTitle(labelFont, SELECTION_TITLE, FONT_SIZE)
{
	this -> menuMode = MAIN;
	this -> levelName = std::nullopt;
	this -> enterKeyPressed = false;
	// Creazione delle entry per il menu principale.
	for (int i = 0; i < MAIN_ENTRY_N; i++) {
		MenuEntry e(getEntryName((main_entry_t) i), this -> labelFont, FONT_SIZE);
		this -> mainEntries.push_back(e);
	}
	// Creazione delle entry per il menu di selezione livelli.
	MenuEntry back("Back", this -> labelFont, FONT_SIZE);
	this -> levelEntries.push_back(back);
	// Scansiono la directory dei file di livello.
	if (this -> loadLevelEntries()) {
		throw std::runtime_error("Menu: error while loading level entries.");
	}
	// Set the position of the logo to be displayed in the initial screen.
	unsigned int width = this -> logoImage.getSize().x;
	float px = (W_WIDTH - width) / 2, py = W_HEIGHT / 8;
	this -> logoSprite.setPosition({px, py});
	// Set the position of the background.
	this -> bgSprite.setPosition(sf::Vector2f(0.f, 0.f));
	// Set the position of the foreground image.
	this -> fgSprite.setPosition(sf::Vector2f(0.f, 0.f));
	// Set the position of the submenu title for level selection.
	float stringLength = this -> selectionTitle.getLocalBounds().size.x,
	x = (W_WIDTH - stringLength) / 2;
	this -> selectionTitle.setPosition({x, W_HEIGHT / 8});
	this -> selected = (int) PLAY_ENTRY;
}

/**
 *	@brief Reads the level files from the predefined LEVEL_DIRECTORY and creates a MenuEntry for each of them
 *
 *	@return 0 in case of success, 1 in case of failure
 */
int Menu::loadLevelEntries() {
    try {
        for (const auto& entry : std::filesystem::directory_iterator(LEVEL_DIRECTORY)) {
			// Skip hidden files.
            if (entry.path().filename().string().front() == '.') continue;
			// Skip non-regular files.
            if (entry.is_regular_file()) {
                MenuEntry m(entry.path().filename().string(), this->labelFont, FONT_SIZE);
                this->levelEntries.push_back(m);
            }
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
		std::cerr << "Menu: error while loading level entries: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

/**
 *	@brief Handles events directed to the game Menu
 *
 *	@param e event received
 */
void Menu::handleEvent(sf::Event e) {
	if (const auto* keyPressed = e.getIf<sf::Event::KeyPressed>()) {
        int entries = (menuMode == MAIN) ? mainEntries.size() : levelEntries.size();
        switch (keyPressed->code)
        {
            case sf::Keyboard::Key::Up:
                this->selected = prevOption(this->selected, entries);
                break;

            case sf::Keyboard::Key::Down:
                this->selected = nextOption(this->selected, entries);
                break;

            case sf::Keyboard::Key::Enter:
                this->enterKeyPressed = true;
                break;

            default:
                break;
        }
    }
}

/**
 *	@brief Updates the internal state of the Menu
 *
 *	@param mode indicator of the current game mode
 */
void Menu::updateMenu(game_mode_t &gameMode) {
	// Aggiorno lo sfondo.
	sf::Time dt = timer.restart();
	float t = dt.asMilliseconds();
	sf::Vector2f p = this -> bgSprite.getPosition();
	float x = p.x - (32 * (t / 750.f));
	if (x <= - 3 * W_WIDTH / 4) x = W_WIDTH;
	this -> bgSprite.setPosition({x, 0});

	// Se non ho premuto il tasto 'Invio' sto selezionando.
	if (!enterKeyPressed) {
		// Ottengo un puntatore all'array delle entry da utilizzare.
		std::vector<MenuEntry> *list = ((menuMode == MAIN) ?
		&(this -> mainEntries) : &(this -> levelEntries));
		// Evidenzio l'opzione correntemente attiva.
		list -> at(this -> selected).setSelected(true);
		unsigned int size = list -> size();
		// Deseleziono tutte le altre opzioni.
		for (int i = 0; i < size; i++) {
			if (i != this -> selected) {
				list -> at(i).setSelected(false);
			}
		}
	}
	// Altrimenti controllo che cosa ho selezionato.
	else {
		if (menuMode == MAIN) {
			switch (this -> selected) {
				case PLAY_ENTRY: {
					menuMode = SELECTION;
					if (!(this -> levelEntries.empty())) {
						this -> levelEntries[0].setSelected(true);
					}
					this -> enterKeyPressed = false;
				}; break;
				case QUIT_ENTRY: {
					gameMode = QUIT;
				}; break;
			}
		}
		else {
			// Controllo se ho selezionato un livello oppure voglio
			// tornare al menu principale.
			if (this -> selected) {
				levelName = this -> levelEntries[this -> selected].getLabel();
				this -> enterKeyPressed = false;
				// Resetto i parametri per un'eventuale ritorno al menuMode
				// principale dopo aver giocato.
				menuMode = MAIN;
				this -> selected = 0;
				// Imposto la modalità di gioco su PLAYING.
				gameMode = PLAYING;
			}
			// Voglio solo tornare al menu principale.
			else {
				this -> enterKeyPressed = false;
				menuMode = MAIN;
			}
		}
	}
}


/**
 *	@brief Draws the content of the Menu to the screen
 *
 *	@param window main window to draw to
 */
void Menu::drawMenu(sf::RenderWindow &window) {
	std::vector<MenuEntry> *list = NULL;
	float y0 = 0.0f;
	// Disegno lo sfondo.
	window.draw(this -> bgSprite);
	// Disegno l'immagine in primo piano.
	window.draw(this -> fgSprite);
	// Controllo cos'altro devo disegnare.
	switch (this -> menuMode) {
		case MAIN: {
			list = &(this -> mainEntries);
			window.draw(this -> logoSprite);
			y0 = W_HEIGHT / 2;
		}; break;
		case SELECTION: {
			list = &(this -> levelEntries);
			y0 = W_HEIGHT / 8 + VSPACE;
			window.draw(this -> selectionTitle);
		}; break;
	}
	for (int i = 0; i < list -> size(); i++) {
		sf::FloatRect bounds = list -> at(i).getLocalBounds();
		float stringLength = bounds.size.x;
		float x = (W_WIDTH - stringLength) / 2;
		float y = y0 + i * VSPACE;
		list -> at(i).setPosition({x, y});
		window.draw(list -> at(i));
	}
	return;
}

/**
 *	@brief Returns the path of the level file selected in the Menu
 *
 *	@return string containing the path of the level file selected
 *
 *	@throw std::runtime_error if the level name has no value
 */
std::string Menu::getLevelFile() {
	if (!this -> levelName.has_value()) {
		throw std::runtime_error("getLevelFile: level name has no value.");
	}
    return std::string(LEVEL_DIRECTORY) + "/" + (this -> levelName).value();
}



