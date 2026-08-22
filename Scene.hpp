/**
 *	@file Scene.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Contiene la definizione della classe Scene, che rappresenta ciascun
 *	livello del gioco
 */

#ifndef SCENE_H
#define SCENE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdio>
#include <vector>
#include "Config.hpp"
#include "Mario.hpp"
#include "Enemy.hpp"
#include "Powerup.hpp"
#include "Layer.hpp"
#include "Tilemap.hpp"

/** Testo iniziale dell'etichetta del punteggio. */
#define SCORE_INIT_MSG "Score: 0"

/** Posizione iniziale dell'etichetta del punteggio. */
#define SCORE_POSITION sf::Vector2f(16.f, 16.f)

/** Dimensione del font dell'etichetta del punteggio. */
#define SCORE_FONT_SIZE 12

/** Testo dell'etichetta di game over. */
#define GAME_OVER_MSG "Game over!"

/** Dimensione del font dell'etichetta di game over. */
#define GAME_OVER_FONT_SIZE 20

/** Testo dell'etichetta da mostrare quando si vince. */
#define WIN_MSG "Livello completato!"

/** Dimensione del font dell'etichetta di vittoria. */
#define WIN_FONT_SIZE 20

/** Testo dell'etichetta con le informazioni. */
#define INFO_MSG "Premi invio per tornare al menu"

/** Dimensione del font dell'etichetta con le informazioni. */
#define INFO_FONT_SIZE 12

/** Tempo di animazione dei blocchi dinamici nella scena. */
#define BLOCK_ANIMATION_TIME 100

class Scene {
	private:
		Layer fg;
		Layer bg;
		sf::Texture bgImage;
		sf::Sprite bgSprite;
		sf::Font font;
		sf::Text scoreLabel;
		sf::Text gameOverLabel;
		sf::Text winLabel;
		sf::Text infoLabel;
		unsigned int seed;
		std::vector<sf::Texture> staticTextures;
		std::vector<sf::Texture> questionTextures;
		std::vector<sf::Texture> coinTextures;
		std::vector<sf::Texture> goombaTextures;
		std::vector<sf::Texture> piranhaPlantTextures;
		std::vector<sf::Texture> koopaTextures;
		std::vector<Block *> blocks;
		std::vector<Block *> currentBlocks;
		std::vector<Enemy *> enemies;
		std::vector<Enemy *> currentEnemies;
		std::vector<Powerup *> powerups;
		sf::Music theme;
		std::vector<sf::SoundBuffer *> soundBuffers;
		std::vector<sf::Sound *> sounds;
		Tilemap tilemap;
		sf::Clock timer;
		Mario hero;
		bool win;
		bool gameOver;
		void loadTextures();
		void loadSounds();
		void initLabels();
		void processTilemap();
		void updateBlocks(sf::Time dt);
		void updateEnemies(sf::Time dt);
		void updatePowerups(sf::Time dt);
		void updateLabels();
		void updateLayers(sf::Vector2f p);
		void refreshCurrentBlocks();
		void refreshCurrentEnemies();
		bool checkPlayerDead();
		bool checkPlayerWin();
		void playSound(scene_sound_t id);
	public:
		Scene(FILE *level);
		~Scene();
		void handleEvent(sf::Event e, game_mode_t *gameMode);
		void updateScene();
		void drawScene(sf::RenderWindow *window);
		int getSceneWidth();
		int getSceneHeight();
};

#endif
