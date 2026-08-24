/**
 *	@file Scene.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Implementazione della classe Scene, corrispondente al generico livello
 *	del gioco
 */

#include <iostream>
#include <stdexcept>
#include "Scene.hpp"
#include "Config.hpp"
#include "Errors.hpp"
#include "Physics.hpp"
#include "Textures.hpp"
#include "Sounds.hpp"
#include "Block.hpp"
#include "QuestionBlock.hpp"
#include "Coin.hpp"
#include "Goomba.hpp"
#include "Koopa.hpp"
#include "PiranhaPlant.hpp"
#include "SuperMushroom.hpp"
#include "OneUpMushroom.hpp"
#include "CoinPowerup.hpp"

/**
 *	@brief Metodo costruttore della classe scena
 *
 *	@param level puntatore al file del livello
 *
 *	@note Può lanciare un'eccezione nei casi in cui l'argomento è NULL,
 *	oppure se fallisce il caricamento della tilemap da file
 *
 */
Scene::Scene(const std::string &path) :
	tilemap(path),
	fg(sf::FloatRect({0, 0}, {W_WIDTH, W_HEIGHT})),
	bg(sf::FloatRect({0, 0}, {W_WIDTH, W_HEIGHT})),
	bgImage(BACKGROUND_TEXTURE),
	bgSprite(bgImage),
	font(FONT_PATH),
	scoreLabel(font, SCORE_INIT_MSG, SCORE_FONT_SIZE),
	gameOverLabel(font, GAME_OVER_MSG, GAME_OVER_FONT_SIZE),
	winLabel(font, WIN_MSG, WIN_FONT_SIZE),
	infoLabel(font, INFO_MSG, INFO_FONT_SIZE)
{
	// Carico le texture.
	this -> loadTextures();
	// Analizzo la tilemap per produrre le sprite e gli ostacoli.
	this -> processTilemap();
	// Inizializzo la vista.
	this -> fg.setCenter({W_WIDTH / 2, W_HEIGHT / 2});
	// Aggiorno il vettore degli ostacoli correnti.
	this -> refreshCurrentBlocks();
	// Aggiorno il vettore dei nemici correnti.
	this -> refreshCurrentEnemies();
	// Carico i suoni.
	this -> loadSounds();
	// Inizializza le etichette.
	this -> scoreLabel.setPosition(SCORE_POSITION);
	// Imposta lo stato del gioco.
	this -> win = false;
	this -> gameOver = false;
	this -> seed = time(NULL);
}

/**
 *	@brief Distruttore della classe scena
 */
Scene::~Scene() {
	// Distruggo tutti i blocchi.
	for (int i = 0; i < this -> blocks.size(); i++) {
		delete blocks[i];
	}
	// Distruggo tutti i nemici.
	for (int i = 0; i < this -> enemies.size(); i++) {
		delete enemies[i];
	}
	// Distruggo tutti i powerup.
	for (int i = 0; i < this -> powerups.size(); i++) {
		delete powerups[i];
	}
	// Cancello la tilemap.
	// destroyTilemap(this -> tilemap);
	// Cancello i suoni.
	for (int i = 0; i < SCENE_SOUND_N; i++) {
		delete soundBuffers[i];
		delete sounds[i];
	}
	std::cout << "Scene destroyed!" << std::endl;
}


/**
 *	@brief Carica tutte le texure dai relativi file e le aggiunge
 *	all'array delle texture
 */
void Scene::loadTextures() {
	bool loadResult = false;
	// Carico le texture statiche.
	for (int i = 0; i < STATIC_TEXTURE_N; i++) {
		sf::Texture t;
		loadResult = t.loadFromFile(getStaticTexturePath((static_texture_t) i));
		if (!loadResult) throw std::runtime_error("loadTextures: Cannot load static texture.");
		this -> staticTextures.push_back(t);
	}
	sf::Image questionSheet, coinSheet, goombaSheet, piranhaPlantSheet, koopaSheet;
	// Carico le texture per i question block.
	loadResult = questionSheet.loadFromFile(QUESTION_TEXTURE_SHEET);
	if (!loadResult) throw std::runtime_error("loadTextures: Cannot load question block texture sheet.");
	for (int i = 0; i < QUESTION_TEXTURE_N; i++) {
		sf::Texture t;
		sf::IntRect rect({i * SIZE, 0}, {SIZE, SIZE});
		loadResult = t.loadFromImage(questionSheet, false, rect);
		if (!loadResult) throw std::runtime_error("loadTextures: Cannot load question block texture.");
		this -> questionTextures.push_back(t);
	}
	// Carico le texture per le monete.
	loadResult = coinSheet.loadFromFile(COIN_TEXTURE_SHEET);
	if (!loadResult) throw std::runtime_error("loadTextures: Cannot load coin texture sheet.");
	for (int i = 0; i < COIN_TEXTURE_N; i++) {
		sf::Texture t;
		sf::IntRect rect({i * SIZE, 0}, {SIZE, SIZE});
		loadResult = t.loadFromImage(coinSheet, false, rect);
		if (!loadResult) throw std::runtime_error("loadTextures: Cannot load coin texture.");
		this -> coinTextures.push_back(t);
	}
	// Carico le texture per i Goomba.
	loadResult = goombaSheet.loadFromFile(GOOMBA_TEXTURE_SHEET);
	if (!loadResult) throw std::runtime_error("loadTextures: Cannot load Goomba texture sheet.");
	for (int i = 0; i < GOOMBA_TEXTURE_N; i++) {
		sf::Texture t;
		sf::IntRect rect({i * SIZE, 0}, {SIZE, SIZE});
		loadResult = t.loadFromImage(goombaSheet, false, rect);
		if (!loadResult) throw std::runtime_error("loadTextures: Cannot load Goomba texture.");
		this -> goombaTextures.push_back(t);
	}
	// Carico le texture per le Piranha Plant.
	loadResult = piranhaPlantSheet.loadFromFile(PIRANHAPLANT_TEXTURE_SHEET);
	if (!loadResult) throw std::runtime_error("loadTextures: Cannot load Piranha Plant texture sheet.");
	for (int i = 0; i < PIRANHAPLANT_TEXTURE_N; i++) {
		sf::Texture t;
		sf::IntRect rect({i * SIZE, 0}, {SIZE, PIRANHAPLANT_HEIGHT});
		loadResult = t.loadFromImage(piranhaPlantSheet, false, rect);
		if (!loadResult) throw std::runtime_error("loadTextures: Cannot load Piranha Plant texture.");
		this -> piranhaPlantTextures.push_back(t);
	}
	// Carico le texture per Koopa.
	loadResult = koopaSheet.loadFromFile(KOOPA_TEXTURE_SHEET);
	if (!loadResult) throw std::runtime_error("loadTextures: Cannot load Koopa texture sheet.");
	for (int i = 0; i < KOOPA_TEXTURE_N - 2; i++) {
		sf::Texture t;
		sf::IntRect rect({i * SIZE, 0}, {SIZE, KOOPA_HEIGHT});
		loadResult = t.loadFromImage(koopaSheet, false, rect);
		if (!loadResult) throw std::runtime_error("loadTextures: Cannot load Koopa texture.");
		this -> koopaTextures.push_back(t);
	}
	sf::Texture koopaGreenShell, koopaRedShell;
	loadResult = koopaGreenShell.loadFromFile(KOOPA_GREEN_SHELL_TEXTURE);
	if (!loadResult) throw std::runtime_error("loadTextures: Cannot load Koopa green shell texture.");
	loadResult = koopaRedShell.loadFromFile(KOOPA_RED_SHELL_TEXTURE);
	if (!loadResult) throw std::runtime_error("loadTextures: Cannot load Koopa red shell texture.");
	this -> koopaTextures.push_back(koopaGreenShell);
	this -> koopaTextures.push_back(koopaRedShell);
}

/**
 *	@brief Carica tutti i suoni e gli effetti sonori della scena e
 *	li inserisce negli appositi array
 */
void Scene::loadSounds() {
	bool loadResult = false;
	loadResult = this -> theme.openFromFile(SCENE_MUSIC_THEME);
	if (!loadResult) throw std::runtime_error("loadSounds: Cannot load music file.");
	this -> theme.setLooping(true);
	this -> theme.play();
	for (int i = 0; i < SCENE_SOUND_N; i++) {
		sf::SoundBuffer *sb = new sf::SoundBuffer();
		loadResult = sb -> loadFromFile(SceneSoundPath((scene_sound_t) i));
		if (!loadResult) throw std::runtime_error("loadSounds: Cannot load sound file.");
		this -> soundBuffers.push_back(sb);
		sf::Sound *snd = new sf::Sound(*(this -> soundBuffers[i]));
		//snd -> setBuffer(*(this -> soundBuffers[i]));
		this -> sounds.push_back(snd);
	}
}

/**
 *	@brief Scandisce tutta la tilemap per produrre le sprite e gli
 *	ostacoli
 */
void Scene::processTilemap() {
	block_t current;
	unsigned int rows = (this -> tilemap).getRows();
	unsigned int cols = (this -> tilemap).getCols();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			current = (this -> tilemap).getElement(i, j);
			// Controllo di che tipo di blocco si tratta.
			switch (current) {
				case QUESTION: {
					QuestionBlock *q = new QuestionBlock(j * SIZE, i * SIZE, getSpawnID(rand_r(&seed)), this -> questionTextures);
					this -> blocks.push_back(q);
				}; break;
				case COIN: {
					Coin *c = new Coin(j * SIZE, i * SIZE, this -> coinTextures);
					this -> blocks.push_back(c);
				}; break;
				case GOOMBA: {
					Goomba *g = new Goomba(j * SIZE, i * SIZE, this -> goombaTextures);
					this -> enemies.push_back(g);
				}; break;
				case GREEN_KOOPA: {
					Koopa *k = new Koopa(j * SIZE, i * SIZE - (KOOPA_HEIGHT - SIZE), GREEN_KOOPA, this -> koopaTextures);
					this -> enemies.push_back(k);
				}; break;
				case RED_KOOPA: {
					Koopa *k = new Koopa(j * SIZE, i * SIZE - (KOOPA_HEIGHT - SIZE), RED_KOOPA, this -> koopaTextures);
					this -> enemies.push_back(k);
				}; break;
				case PIRANHA_PLANT: {
					PiranhaPlant *p = new PiranhaPlant(j * SIZE, i * SIZE - (PIRANHAPLANT_HEIGHT - SIZE), this -> piranhaPlantTextures);
					this -> enemies.push_back(p);
				}; break;
				default: {
					// Altimenti si tratta di un blocco statico.
					int tid = getStaticTextureID(current);
					if (tid != -1) {
						Block *b = new Block(current, j * SIZE, i * SIZE, this -> staticTextures[tid]);
						b -> setCollidable(isCollidable(current));
						this -> blocks.push_back(b);
					}
				}; break;
			}
		}
	}
}

/**
 *	@brief Funzione di gestione degli eventi
 *
 *	@param e l'evento da gestire
 */
void Scene::handleEvent(sf::Event e, game_mode_t *gameMode) {
	if (const auto* keyPressed = e.getIf<sf::Event::KeyPressed>()) {
		switch (keyPressed->code) {
			case sf::Keyboard::Key::Left: {
					this -> hero.startRunning(LEFT);
				}; break;
			case sf::Keyboard::Key::Right: {
					this -> hero.startRunning(RIGHT);
				}; break;
			case sf::Keyboard::Key::Space: {
					this -> hero.startJump();
				}; break;
			case sf::Keyboard::Key::Enter: {
					if (gameOver || win) *gameMode = MENU;
				}; break;
			default: break;
		};
	}
	else if (const auto* keyReleased = e.getIf<sf::Event::KeyReleased>()) {
		switch (keyReleased->code) {
			case sf::Keyboard::Key::Space: {
					this -> hero.endJump();
				}; break;
				case sf::Keyboard::Key::Left: {
					this -> hero.endRunning();
				}; break;
				case sf::Keyboard::Key::Right: {
					this -> hero.endRunning();
				}; break;
				default: break;
		};
	}
}

/**
 *	@brief Aggiorna lo stato dei blocchi della scena
 *
 * 	@param dt intervallo di tempo dall'ultimo aggiornamento
 */
void Scene::updateBlocks(sf::Time dt) {
	static int elapsed = 0;
	if (elapsed >= BLOCK_ANIMATION_TIME) {
		for (int i = 0; i < this -> blocks.size(); i++) {
			block_t type = blocks[i] -> getType();
			switch (type) {
				case QUESTION: {
					QuestionBlock *q = (QuestionBlock *) (blocks[i]);
					if (q) q -> update(dt);
				}; break;
				case COIN: {
					Coin *c = (Coin *) (blocks[i]);
					if (c) c -> update(dt);
				}; break;
				default: break;
			}
		}
		elapsed = 0;
	}
	else elapsed += dt.asMilliseconds();
}

/**
 *	@brief Aggiorna lo stato dei nemici nella scena
 *
 * 	@param dt intervallo di tempo dall'ultimo aggiornamento
 */
void Scene::updateEnemies(sf::Time dt) {
	for (int i = 0; i < this -> currentEnemies.size(); i++) {
		block_t type = this -> currentEnemies[i] -> getType();
		switch (type) {
			case GOOMBA: {
				Goomba *g = (Goomba *) (this -> currentEnemies[i]);
				g -> update(dt, currentBlocks, currentEnemies, i);
			}; break;
			case GREEN_KOOPA: {
				Koopa *k = (Koopa *) (this -> currentEnemies[i]);
				k -> update(dt, currentBlocks, currentEnemies, i);
			}; break;
			case RED_KOOPA: {
				Koopa *k = (Koopa *) (this -> currentEnemies[i]);
				k -> update(dt, currentBlocks, currentEnemies, i);
			}; break;
			case PIRANHA_PLANT: {
				PiranhaPlant *p = (PiranhaPlant *) (this -> currentEnemies[i]);
				p -> update(dt);
			}; break;
			default: break;
		}
	}
}

/**
 *	@brief Aggiorna lo stato dei powerup nella scena
 *
 *	@param dt intervallo di tempo dall'ultimo aggiornamento
 */
void Scene::updatePowerups(sf::Time dt) {
	for (int i = 0; i < this -> powerups.size(); i++) {
		powerup_t type = powerups[i] -> getType();
		switch (type) {
			case SUPER_MUSHROOM: {
				SuperMushroom *sm = (SuperMushroom *) powerups[i];
				sm -> update(dt, this -> currentBlocks);
			}; break;
			case ONEUP_MUSHROOM: {
				OneUpMushroom *om = (OneUpMushroom *) powerups[i];
				om -> update(dt, this -> currentBlocks);
			}; break;
			case COIN_POWERUP: {
				CoinPowerup *cp = (CoinPowerup *) powerups[i];
				cp -> update(dt);
			}; break;
			default: break;
		}
	}
}

/**
 *	@brief Aggiorna le etichette da mostrare nella scena
 */
void Scene::updateLabels() {
	// Durante il gioco aggiorno l'etichetta del punteggio.
	if (!gameOver && !win) {
		sf::Vector2f center = this -> fg.getCenter();
		sf::Vector2f position = SCORE_POSITION;
		float x = center.x - W_WIDTH / 2 + position.x,
		y = center.y - W_HEIGHT / 2 + position.y;
		this -> scoreLabel.setPosition({x, y});
		char scoreString[(BUFSIZE / 8)];
		unsigned int scoreValue = this -> hero.getScore();
		snprintf(scoreString, sizeof(scoreString), "Score: %u", scoreValue);
		this -> scoreLabel.setString(scoreString);
		return;
	}
	sf::FloatRect viewR = fg.getViewRectangle();
	float scoreX = (W_WIDTH - scoreLabel.getLocalBounds().size.x) / 2,
	infoX = (W_WIDTH - infoLabel.getLocalBounds().size.x) / 2;
	scoreLabel.setPosition({viewR.position.x + scoreX, W_HEIGHT / 2});
	infoLabel.setPosition({viewR.position.x + infoX, 9 * W_HEIGHT / 16});
	if (gameOver) {
		float gameOverX = (W_WIDTH - gameOverLabel.getLocalBounds().size.x) / 2;
		gameOverLabel.setPosition({viewR.position.x + gameOverX, 7 * W_HEIGHT / 16});
		return;
	}
	if (win) {
		float winX = (W_WIDTH - winLabel.getLocalBounds().size.x) / 2;
		winLabel.setPosition({viewR.position.x + winX, 7 * W_HEIGHT / 16});
		return;
	}
}

/**
 *	@brief Aggiorna i layer della scena (primo piano e sfondo)
 *
 *	@param p posizione corrente del personaggio
 */
void Scene::updateLayers(sf::Vector2f p) {
	// Escludo l'aggiornamento se il personaggio è morto.
	if (hero.isDead()) return;
	// Altrimenti aggiorno il layer del primo piano e quello in secondo piano.
	int sceneWidth = getSceneWidth();
	if (W_WIDTH / 2 <= p.x && p.x <= sceneWidth - (W_WIDTH / 2)) {
		fg.setCenter({p.x, W_HEIGHT / 2});
		bg.setCenter({p.x / 2, W_HEIGHT / 2});
	}
	else {
		if (p.x < W_WIDTH / 2) {
			fg.setCenter({W_WIDTH / 2, W_HEIGHT / 2});
			bg.setCenter({W_WIDTH / 4, W_HEIGHT / 2});
		}
		if (p.x > sceneWidth - (W_WIDTH / 2)) {
			fg.setCenter({static_cast<float>(sceneWidth - (W_WIDTH / 2)), W_HEIGHT / 2});
			//bg.setCenter({sceneWidth - (W_WIDTH / 4), W_HEIGHT / 2});
		}
	}
}

/**
 *	@brief Determina i blocchi nella vista corrente e li aggiunge
 *	al vettore dei blocchi correnti
 */
void Scene::refreshCurrentBlocks() {
	block_t type = EMPTY;
	bool active = false;
	sf::FloatRect r = this -> fg.getRenderRectangle();
	this -> currentBlocks.clear();
	for (int i = 0; i < this -> blocks.size(); i++) {
		//
		type = blocks[i] -> getType();
		active = blocks[i] -> isActive();
		if (type == COIN && !active) continue;
		//
		sf::IntRect BlockR = blocks[i] -> getRectangle();
		sf::Vector2f p{
			static_cast<float>(BlockR.position.x), 
			static_cast<float>(BlockR.position.y)
		};
		//sf::Vector2f p(BlockR.left, BlockR.top);
		if (r.contains(p)) {
			this -> currentBlocks.push_back(this -> blocks[i]);
		}
	}
}

/**
 *	@brief Determina i nemici nella vista corrente e li aggiunge
 *	al vettore dei nemici correnti
 */
void Scene::refreshCurrentEnemies() {
	sf::FloatRect r = this -> fg.getRenderRectangle();
	this -> currentEnemies.clear();
	for (int i = 0; i < this -> enemies.size(); i++) {
		sf::IntRect EnemyR = enemies[i] -> getRectangle();
		// Prendo solo i nemici ancora vivi.
		bool alive = enemies[i] -> isAlive();
		sf::Vector2f p{
			static_cast<float>(EnemyR.position.x), 
			static_cast<float>(EnemyR.position.y)
		};
		//sf::Vector2f p(EnemyR.left, EnemyR.top);
		if (alive && r.contains(p)) {
			this -> currentEnemies.push_back(this -> enemies[i]);
		}
	}
}

/**
 *	@brief Controlla la posizione di Mario per stabilire se è morto
 *
 * 	@return Un valore di verità che indica se Mario è morto o no
 */
bool Scene::checkPlayerDead() {
	// Ottengo la posizione corrente di Mario.
	sf::Vector2f p = this -> hero.getPosition();
	// Guardo se è stato settato il valore 'dead' nel personaggio.
	// Vale a dire se è entrato in collisione con qualche nemico.
	if (this -> hero.isDead()) return true;
	// Altrimenti controllo se è caduto nel vuoto.
	if (p.x <= getSceneWidth() && getSceneHeight() <= p.y) {
		this -> hero.setDead(true);
		return true;
	}
	return false;
}

/**
 *	@brief Controlla la posizione di Mario per stabilire se ha vinto
 *
 * 	@return Un valore di verità che indica se la partita è stata vinta
 */
bool Scene::checkPlayerWin() {
	// Ottengo la posizione corrente di Mario.
	sf::Vector2f p = this -> hero.getPosition();
	if (p.x >= getSceneWidth()) return true;
	return false;
}

/**
 *	@brief Funzione di aggiornamento della scena
 */
void Scene::updateScene() {
	// Aggiorno Mario e gestisco le sue collisioni.
	sf::Time dt = timer.restart();
	this -> hero.update(dt, this -> currentBlocks, this -> currentEnemies,
	&(this -> powerups));
	// Controllo se Mario è morto.
	if (this -> checkPlayerDead() && !gameOver) {
		gameOver = true;
		this -> theme.stop();
		hero.playSound(DIE);
	}
	// Controllo se ho vinto.
	if (this -> checkPlayerWin() && !win) {
		win = true;
		this -> theme.stop();
		this -> playSound(WIN);
	}
	// Aggiorno i blocchi.
	this -> updateBlocks(dt);
	// Aggiorno i nemici.
	this -> updateEnemies(dt);
	// Aggiorno i powerup.
	this -> updatePowerups(dt);
	// Aggiorno i layer.
	this -> updateLayers(hero.getPosition());
	// Aggiorno i blocchi nella vista corrente.
	this -> refreshCurrentBlocks();
	// Aggiorno i nemici nella vista corrente.
	this -> refreshCurrentEnemies();
	// Aggiorno le etichette.
	this -> updateLabels();
}

/**
 *	@brief Funzione per disegnare la scena corrente
 *
 *	@param window puntatore alla finestra su cui disegnare
 */
void Scene::drawScene(sf::RenderWindow *window) {
	if (window) {
		if (gameOver) window -> clear(C_GREY);
		window -> setView(bg);
		// Disegno lo sfondo.
		int width = (int) bgSprite.getLocalBounds().size.x;
		for (int i = 0; i < getSceneWidth(); i += W_WIDTH) {
			bgSprite.setPosition({
				static_cast<float>(i), 
				0
			});
			if (gameOver) bgSprite.setColor(C_GREY);
			window -> draw(bgSprite);
		}
		window -> setView(fg);
		// Disegno i blocchi.
		for (int i = 0; i < this -> currentBlocks.size(); i++) {
			block_t type = currentBlocks[i] -> getType();
			bool active = currentBlocks[i] -> isActive();
			if (type == COIN && !active) continue;
			sf::Sprite s = currentBlocks[i] -> getSprite();
			if (gameOver) s.setColor(C_GREY);
			window -> draw(s);
		}
		// Disegno i nemici.
		for (int i = 0; i < this -> currentEnemies.size(); i++) {
			bool alive = currentEnemies[i] -> isAlive();
			if (!alive) continue;
			sf::Sprite s = currentEnemies[i] -> getSprite();
			if (gameOver) s.setColor(C_GREY);
			window -> draw(s);
		}
		// Disegno i powerup.
		for (int i = 0; i < this -> powerups.size(); i++) {
			if (!(powerups[i] -> isTaken())) {
				sf::Sprite s = powerups[i] -> getSprite();
				if (gameOver) s.setColor(C_GREY);
				window -> draw(s);
			}
		}
		if (!gameOver) {
			// Disegno Mario.
			window -> draw(this -> hero.getSprite());
			// Se ho vinto disegno la scritta.
			if (win) {
				window -> draw(this -> winLabel);
				window -> draw(this -> infoLabel);
			}
			// Disegno l'etichetta del punteggio.
			window -> draw(this -> scoreLabel);
		}
		else {
			window -> draw(this -> gameOverLabel);
			window -> draw(this -> infoLabel);
			window -> draw(this -> scoreLabel);
		}
	}
	return;
}

/**
 *	@brief Riproduce un suono della scena
 *
 * 	@param id identificativo del suono da riprodurre
 */
void Scene::playSound(scene_sound_t id) {
	this -> sounds[(int) id] -> play();
	return;
}

/**
 *	@brief Restituisce la larghezza complessiva della scena
 *	espressa in pixel
 *
 *	@return Numero di pixel di larghezza
 */
int Scene::getSceneWidth() {
	int cols = (this -> tilemap).getCols();
	return cols * SIZE;
}

/**
 *	@brief Restituisce l'altezza complessiva della scena
 *	espressa in pixel
 *
 * 	@return Numero di pixel in altezza
 */
int Scene::getSceneHeight() {
	int rows = (this -> tilemap).getRows();
	return rows * SIZE;
}
