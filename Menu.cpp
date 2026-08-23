/**
 *	@file Menu.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Implementazione della classe relativa al menu principale del gioco
 */

#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "Menu.hpp"
#include "Errors.hpp"
#include "Textures.hpp"

/**
 *	@brief Costruttore della classe Menu
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
	// this -> labelFont.loadFromFile(FONT_PATH);
	// Creazione delle entry per il menu principale.
	for (int i = 0; i < MAIN_ENTRY_N; i++) {
		MenuEntry e((char *) getEntryName((main_entry_t) i),
		&(this -> labelFont), FONT_SIZE);
		this -> mainEntries.push_back(e);
	}
	// Creazione delle entry per il menu di selezione livelli.
	MenuEntry back((char *) "Indietro", &(this -> labelFont), FONT_SIZE);
	this -> levelEntries.push_back(back);
	// Scansiono la directory dei file di livello.
	if (this -> loadLevelEntries()) {
		throw std::runtime_error(E_LEVEL_LIST_LOAD);
	}
	// Imposto il logo da mostrare nella schermata principale.
	//this -> logoImage.loadFromFile(LOGO_TEXTURE);
	//this -> logoSprite.setTexture(this -> logoImage);
	unsigned int width = this -> logoImage.getSize().x;
	float px = (W_WIDTH - width) / 2, py = W_HEIGHT / 8;
	this -> logoSprite.setPosition({px, py});
	// Imposto lo sfondo del menu.
	// this -> bgImage.loadFromFile(BACKGROUND_TEXTURE);
	// this -> bgSprite.setTexture(bgImage);
	this -> bgSprite.setPosition(sf::Vector2f(0.f, 0.f));
	// Imposto l'immagine di primo piano.
	// this -> fgImage.loadFromFile(MENU_FOREGROUND_TEXTURE);
	// this -> fgSprite.setTexture(fgImage);
	this -> fgSprite.setPosition(sf::Vector2f(0.f, 0.f));
	// Imposto la scritta da mostrare nel sottomenu di selezione livello.
	// this -> selectionTitle.setString(SELECTION_TITLE);
	// this -> selectionTitle.setFont(this -> labelFont);
	// this -> selectionTitle.setCharacterSize(FONT_SIZE);
	float stringLength = this -> selectionTitle.getLocalBounds().size.x,
	x = (W_WIDTH - stringLength) / 2;
	this -> selectionTitle.setPosition({x, W_HEIGHT / 8});
	this -> selected = (int) PLAY_ENTRY;
}

/**
 *	@brief Analizza la directory contenente i livelli del gioco e
 *	crea una voce del menu per ciascuno di essi
 *
 *	@return 0 in caso di successo, 1 in caso di fallimento
 */
int Menu::loadLevelEntries() {
	DIR *dp = NULL;
	struct dirent *entry = NULL;
	char path[BUFSIZE];
	// Apro la directory.
	if (!(dp = opendir(LEVEL_DIRECTORY))) return 1;
	// Scorro tutti i file della directory.
	while ((entry = readdir(dp))) {
		memset(path, 0, sizeof(path));
		snprintf(path, sizeof(path), "%s/%s", LEVEL_DIRECTORY,
		entry -> d_name);
		// Prendo solo i file regolari e che non cominciano con il punto.
		struct stat s;
		if (!stat(path, &s)) {
			if (S_ISREG(s.st_mode) && strncmp(entry -> d_name, ".", 1)) {
				MenuEntry m((char *) entry -> d_name, &(this -> labelFont),
				FONT_SIZE);
				this -> levelEntries.push_back(m);
			}
		}
		else return 1;
	}
	closedir(dp);
	return 0;
}

/**
 *	@brief Funzione di gestione degli eventi indirizzati al menu di gioco
 *
 *	@param e evento ricevuto
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

	// if (e.type == sf::Event::KeyPressed) {
	// 	int entries =
	// 		((menuMode == MAIN) ? mainEntries.size() : levelEntries.size());
	// 	switch (e.key.code) {
	// 		case sf::Keyboard::Up: {
	// 			this -> selected = prevOption(this -> selected, entries);
	// 		}; break;
	// 		case sf::Keyboard::Down: {
	// 			this -> selected = nextOption(this -> selected, entries);
	// 		}; break;
	// 		case sf::Keyboard::Return: {
	// 			this -> enterKeyPressed = true;
	// 		}; break;
	// 		default: break;
	// 	}
	// }
	// return;
}

/**
 *	@brief Funzione di aggiornamento dello stato interno del menu
 *
 *	@param mode puntatore alla modalità di gioco
 */
void Menu::updateMenu(game_mode_t *gameMode) {
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
					*gameMode = QUIT;
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
				*gameMode = PLAYING;
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
 *	@brief Disegna il contenuto del menu sulla finestra
 *
 *	@param window puntatore alla finestra su cui disegnare
 */
void Menu::drawMenu(sf::RenderWindow *window) {
	std::vector<MenuEntry> *list = NULL;
	float y0 = 0.0f;
	// Disegno lo sfondo.
	window -> draw(this -> bgSprite);
	// Disegno l'immagine in primo piano.
	window -> draw(this -> fgSprite);
	// Controllo cos'altro devo disegnare.
	switch (this -> menuMode) {
		case MAIN: {
			list = &(this -> mainEntries);
			window -> draw(this -> logoSprite);
			y0 = W_HEIGHT / 2;
		}; break;
		case SELECTION: {
			list = &(this -> levelEntries);
			y0 = W_HEIGHT / 8 + VSPACE;
			window -> draw(this -> selectionTitle);
		}; break;
	}
	for (int i = 0; i < list -> size(); i++) {
		sf::FloatRect bounds = list -> at(i).getLocalBounds();
		float stringLength = bounds.size.x;
		float x = (W_WIDTH - stringLength) / 2, y = y0 + i * VSPACE;
		list -> at(i).setPosition({x, y});
		window -> draw(list -> at(i));
	}
	return;
}

/**
 *	@brief Restituisce il percorso del file di livello selezionato
 *
 *	@return Una stringa contenente il percorso del file selezionato
 *	in caso di successo, NULL in caso di fallimento
 */
std::string Menu::getLevelFile() {
	if (!this -> levelName.has_value()) {
		throw std::runtime_error("getLevelFile: level name has no value.");
	}
    return std::string(LEVEL_DIRECTORY) + "/" + (this -> levelName).value();
}



