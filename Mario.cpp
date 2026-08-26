/**
 *	@file Mario.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Implementation of the Mario class
 */

#include <cmath>
#include "Mario.hpp"
#include "Textures.hpp"
#include "QuestionBlock.hpp"
#include "Coin.hpp"
#include "Goomba.hpp"
#include "Koopa.hpp"
#include "SuperMushroom.hpp"
#include "OneUpMushroom.hpp"

/**
 *	@brief Utility function that loads Mario textures from a texture sheet and places them in a vector.
 *
 *	@return A vector containing the textures loaded from the texture sheet
 */
std::vector<sf::Texture> buildTextureVector() {
	bool loadResult = false;
	std::vector<sf::Texture> textures;
	sf::Image sheet;
	loadResult = sheet.loadFromFile(MARIO_TEXTURE_SHEET);
	if (!loadResult) throw std::runtime_error("buildTextureVector: Cannot load texture sheet.");
	for (int i = 0; i < MARIO_TEXTURE_N / 4; i++) {
		sf::Texture t;
		sf::IntRect rect({i * SIZE, 0}, {SIZE, SIZE});
		loadResult = t.loadFromImage(sheet, false, rect);
		if (!loadResult) throw std::runtime_error("buildTextureVector: Cannot load texture.");
		textures.push_back(t);
	}
	for (int i = 0; i < MARIO_TEXTURE_N / 4; i++) {
		sf::Texture t;
		sf::IntRect rect({i * SIZE, SIZE}, {SIZE, SIZE});
		loadResult = t.loadFromImage(sheet, false, rect);
		if (!loadResult) throw std::runtime_error("buildTextureVector: Cannot load texture.");
		textures.push_back(t);
	}
	for (int i = 0; i < MARIO_TEXTURE_N / 4; i++) {
		sf::Texture t;
		sf::IntRect rect({i * SIZE, 2 * SIZE}, {SIZE, 2 * SIZE});
		loadResult = t.loadFromImage(sheet, false, rect);
		if (!loadResult) throw std::runtime_error("buildTextureVector: Cannot load texture.");
		textures.push_back(t);
	}
	for (int i = 0; i < MARIO_TEXTURE_N / 4; i++) {
		sf::Texture t;
		sf::IntRect rect({i * SIZE, 4 * SIZE}, {SIZE, 2 * SIZE});
		loadResult = t.loadFromImage(sheet, false, rect);
		if (!loadResult) throw std::runtime_error("buildTextureVector: Cannot load texture.");
		textures.push_back(t);
	}
	return textures;
}

/**
 *	@brief Metodo costruttore della classe relativa a Mario
 */
Mario::Mario() : 
	textures(buildTextureVector()), 
	sprite(textures[(int) STANDING]),
	size({SIZE, SIZE}),
	speed(0, 0),
	animationTime(0),
	invisibleTime(0),
	score(0),
	super(false),
	invisible(false),
	dead(false),
	running(false),
	onGround(false),
	ignoreEnemyCollision(false),
	facing(RIGHT),	
	textureID(STANDING)
{
	this -> loadSounds();
	this -> sprite.setPosition(MARIO_POSITION);
}

/**
 *	@brief Distruttore della classe relativa a Mario
 */
Mario::~Mario() {
	// Cancello tutti i suoni.
	for (int i = 0; i < MARIO_SOUND_N; i++) {
		delete soundBuffers[i];
		delete sounds[i];
	}
}

/**
 *	@brief Carica i file audio per gli effetti sonori
 */
void Mario::loadSounds() {
	bool loadResult = false;
	for (int i = 0; i < MARIO_SOUND_N; i++) {
		sf::SoundBuffer *sb = new sf::SoundBuffer();
		loadResult = sb -> loadFromFile(getMarioSoundPath((mario_sound_t) i));
		if (!loadResult) throw std::runtime_error("loadSounds: Cannot load sound.");
		this -> soundBuffers.push_back(sb);
		sf::Sound *snd = new sf::Sound(*(this -> soundBuffers[i]));
		this -> sounds.push_back(snd);
	}
}

/**
 *	@brief Restituisce la posizione corrente della sprite di Mario
 *
 *	@return Vettore posizione del personaggio
 */
sf::Vector2f Mario::getPosition() {
	return this -> sprite.getPosition();
}

/**
 *	@brief Imposta la posizione della sprite di Mario
 *
 *	@param x ascissa del punto
 *	@param y ordinata del punto
 */
void Mario::setPosition(float x, float y) {
	this -> sprite.setPosition({x, y});
}

/**
 *	@brief Restituisce la sprite associata a Mario
 *
 *	@return La sprite associata al personaggio
 */
sf::Sprite Mario::getSprite() {
	return this -> sprite;
}

/**
 *	@brief Restituisce la velocità corrente di Mario
 *
 *	@return Il vettore velocità del personaggio
 */
sf::Vector2f Mario::getSpeed() {
	return this -> speed;
}

/**
 *	@brief Imposta la velocità di Mario
 *
 *	@param x componente del vettore velocità lungo l'asse x
 *	@param y componente del vettore velocità lungo l'asse y
 */
void Mario::setSpeed(float x, float y) {
	this -> speed.x = x;
	this -> speed.y = y;
}

/**
 *	@brief Funzione chiamata quando il personaggio deve iniziare il salto
 */
void Mario::startJump() {
	if (this -> onGround) {
		// Determino la texture da impostare.
		if (!(this -> super)) {
			textureID = ((this -> facing == RIGHT) ? JUMPING : JUMPING_L);
		}
		else textureID = ((this -> facing == RIGHT) ? S_JUMPING : S_JUMPING_L);
		this -> sprite.setTexture(textures[(int) textureID]);
		// Faccio partire il salto.
        this -> speed.y = -JUMP_SPEED;
        this -> onGround = false;
		if (!(this -> super)) this -> playSound(JUMP);
		else this -> playSound(JUMP_BIG);
    }
}

/**
 *	@brief Funzione chiamata quando il personaggio deve concludere il salto
 */
void Mario::endJump() {
	if (this -> speed.y < -JUMP_SPEED / 2) {
		this -> speed.y = -JUMP_SPEED / 2;
	}
}

/**
 *	@brief Funzione chiamata quando il personaggio deve iniziare a correre
 *
 *	@param d la direzione in cui il personaggio deve muoversi
 */
void Mario::startRunning(direction_t d) {
	if (!(this -> running)) {
		this -> facing = d;
		switch (d) {
			case LEFT: {
				this -> speed.x = -RUN_SPEED;
				// NOTA: Cambio la texture ma controllo prima se sto saltando.
				if (!(this -> onGround)) {
					if (!(this -> super)) this -> textureID = JUMPING_L;
					else this -> textureID = S_JUMPING_L;
				}
				else {
					if (!(this -> super)) this -> textureID = STANDING_L;
					else this -> textureID = S_STANDING_L;
				}
			}; break;
			case RIGHT: {
				this -> speed.x = RUN_SPEED;
				// NOTA: Cambio la texture ma controllo prima se sto saltando.
				if (!(this -> onGround)) {
					if (!(this -> super)) this -> textureID = JUMPING;
					else this -> textureID = S_JUMPING;
				}
				else {
					if (!(this -> super)) this -> textureID = STANDING;
					else this -> textureID = S_STANDING;
				}
			}; break;
			default: this -> speed.x = 0; break;
		}
		this -> sprite.setTexture(textures[(int) textureID]);
		this -> running = true;
	}
}

/**
 *	@brief Funzione chiamata quando il personaggio deve smettere di correre
 */
void Mario::endRunning() {
	this -> running = false;
	this -> speed.x = 0;
}

/**
 *	@brief Funzione di aggiornamento della texture del personaggio
 *
 *	@param dt intervallo di tempo trascorso dall'ultimo aggiornamento
 */
void Mario::updateTexture(sf::Time dt) {
	// Applico la texture giusta al personaggio.
	if (onGround) {
		if (running) {
			if (animationTime >= MARIO_ANIMATION_TIME) {
				textureID = nextAnimationTexture(super, textureID);
				this -> sprite.setTexture(textures[(int) textureID]);
				animationTime = 0;
			}
			else animationTime += dt.asMilliseconds();
		}
		else {
			if (!super) {
				textureID = ((facing == RIGHT) ? STANDING : STANDING_L);
			}
			else {
				textureID = ((facing == RIGHT) ? S_STANDING : S_STANDING_L);
			}
			this -> sprite.setTexture(textures[(int) textureID]);
			animationTime = 0;
		}
	}
	// Controllo se sono in modalità "semitrasparente".
	if (ignoreEnemyCollision) {
		int max = ((this -> invisible) ? INVISIBLE_TIME : TRANSITION_TIME);
		if (invisibleTime <= max) {
			this -> sprite.setColor(C_HALFTRANSP);
			invisibleTime += dt.asMilliseconds();
		}
		else {
			this -> sprite.setColor(C_WHITE);
			ignoreEnemyCollision = false;
			invisible = false;
			invisibleTime = 0;
		}
	}
}

/**
 *	@brief Funzione di aggiornamento del personaggio
 *
 *	@param dt intervallo di tempo trascorso dall'ultimo aggiornamento
 *	@param blocks array di puntatori ai blocchi della scena corrente
 */
void Mario::update(sf::Time dt, std::vector<Block *> blocks, std::vector<Enemy *> enemies, std::vector<Powerup *> *powerups) {
	//float t = (float) dt.asMilliseconds();
	//float tx = (t / 100) * 2;
	//float ty = round(((t / 100) * 3) * 10) / 10;
	float posX = this -> sprite.getPosition().x;
	float posY = this -> sprite.getPosition().y;
	float velX = this -> speed.x;
	float velY = this -> speed.y;
	// Calcolo la nuova posizione.
	//posX += velX * tx;
	posX += velX * 0.3f;
	handleXCollisions(&posX, &posY, &velX, blocks, enemies, powerups);
	//posY += velY * ty;
	posY += velY * 0.5f;
	handleYCollisions(&posX, &posY, &velY, blocks, enemies, powerups);
	//if ((velY += GRAVITY * ty) > FALL_SPEED) velY = FALL_SPEED;
	if ((velY += GRAVITY * 0.5f) > FALL_SPEED) velY = FALL_SPEED;
	// Scrivo i risultati dei calcoli.
	this -> setPosition(posX, posY);
	this -> speed.x = velX;
	this -> speed.y = velY;
	// Aggiorno la texture.
	updateTexture(dt);
}

/**
 *	@brief Controlla se c'è una collisione fra Mario e un blocco
 *
 *	@param blocks il vettore contenente i blocchi
 *	@param MarioR il rettangolo corrente del personaggio
 *	@param IntR puntatore al rettangolo di intersezione
 *
 *	@return L'indice del blocco intersecato in caso di intersezione,
 *	-1 in caso di non intersezione
 */
int Mario::checkBlockCollisions(std::vector<Block *> blocks, sf::IntRect MarioR, sf::IntRect *IntR) {
	sf::IntRect BlockR;
	bool collidable = false;
	for (int i = 0; i < blocks.size(); i++) {
		BlockR = blocks[i] -> getRectangle();
		collidable = blocks[i] -> isCollidable();
		std::optional<sf::IntRect> intersection = MarioR.findIntersection(BlockR);
		if (collidable && intersection.has_value()) {
			*IntR = intersection.value();
			return i;
		}
	}
	return -1;
}

/**
 *	@brief Controlla se c'è una collisione fra Mario e un nemico
 *
 *	@param enemies il vettore contenente i nemici
 *	@param MarioR il rettangolo corrente del personaggio
 *	@param IntR puntatore al rettangolo di intersezione
 *
 *	@return L'indice del nemico intersecato in caso di intersezione,
 *	-1 in caso di non intersezione
 */
int Mario::checkEnemyCollisions(std::vector<Enemy *> enemies, sf::IntRect MarioR, sf::IntRect *IntR) {
	sf::IntRect EnemyR;
	bool collidable = false;
	for (int i = 0; i < enemies.size(); i++) {
		EnemyR = enemies[i] -> getRectangle();
		collidable = enemies[i] -> isCollidable();
		std::optional<sf::IntRect> intersection = MarioR.findIntersection(EnemyR);
		if (collidable && intersection.has_value()) {
			*IntR = intersection.value();
			return i;
		}
	}
	return -1;
}

/**
 *	@brief Controlla se c'è una collisione fra Mario e un powerup
 *
 *	@param powerups puntatore al vettore contenente i powerup
 *	@param MarioR il rettangolo corrente del personaggio Mario
 */
void Mario::checkPowerupCollision(std::vector<Powerup *> *powerups, sf::IntRect MarioR) {
	sf::IntRect PowerR;
	bool taken = false;
	powerup_t type;
	for (int i = 0; i < powerups -> size(); i++) {
		PowerR = (*powerups)[i] -> getRectangle();
		taken = (*powerups)[i] -> isTaken();
		type = (*powerups)[i] -> getType();
		std::optional<sf::IntRect> intersection = MarioR.findIntersection(PowerR);
		if (!taken && intersection.has_value()) {
			// IntR = intersection.value();
			// Controllo di che tipo si tratta.
			switch (type) {
				case SUPER_MUSHROOM: this -> setSuper(true); break;
				case ONEUP_MUSHROOM: this -> setInvisible(true); break;
				default: break;
			}
			(*powerups)[i] -> setTaken(true);
		}
	}
	return;
}

/**
 *	@brief Controlla se c'è una collisione fra Mario e il bordo
 *	del livello ed eventualmente la gestisce
 *
 *	@param px puntatore alla posizione corrente lungo l'asse x
 *	@param vx puntatore alla velocità corrente lungo l'asse x
 *
 *	@brief Un valore di verità che indica se c'è la collisione
 */
bool Mario::checkBorderCollision(float *px, float *vx) {
	if (*px < 0) {
		*px = 0;
		*vx = 0;
		return true;
	}
	return false;
}

/**
 *	@brief Funzione di gestione delle collisioni lungo l'asse x
 *
 *	@param px puntatore alla posizione corrente lungo l'asse x
 *	@param py puntatore alla posizione corrente lungo l'asse y
 *	@param vx puntatore alla velocità corrente lungo l'asse x
 *	@param blocks array di puntatori ai blocchi della scena corrente
 */
void Mario::handleXCollisions(float *px, float *py, float *vx,
	std::vector<Block *> blocks, std::vector<Enemy *> enemies,
	std::vector<Powerup *> *powerups) {
	// Controllo se il personaggio ha posizione negativa.
	if (checkBorderCollision(px, vx)) return;
	sf::IntRect MarioR({(int) *px, (int) *py}, size);
	sf::IntRect IntR;
	int collidedBlock = -1, collidedEnemy = -1;
	// Controllo se c'è una collisione con qualche blocco.
	collidedBlock = checkBlockCollisions(blocks, MarioR, &IntR);
	// Gestisco la collisione con il blocco.
	if (collidedBlock != -1) {
		// Determino il rettangolo e il tipo del blocco.
		sf::IntRect BlockR = blocks[collidedBlock] -> getRectangle();
		block_t type = blocks[collidedBlock] -> getType();
		// Se è una moneta non gestisco la collisione.
		if (type == COIN) {
			this -> triggerBlockAction(blocks[collidedBlock], NULL);
			return;
		}
		// Altrimenti si procede normalmente.
		if (MarioR.position.x < BlockR.position.x) {
			*px = *px - IntR.size.x;
			*vx = 0;
		}
		else {
			*px = *px + IntR.size.x;
			*vx = 0;
		}
		// Termino non appena ho gestito la collisione.
		return;
	}
	// Se sono qui controllo se c'è una collisione con qualche nemico.
	collidedEnemy = checkEnemyCollisions(enemies, MarioR, &IntR);
	if (collidedEnemy != -1 && !ignoreEnemyCollision) { // Mario muore.
		sf::IntRect EnemyR = enemies[collidedEnemy] -> getRectangle();
		block_t type = enemies[collidedEnemy] -> getType();
		// Tratto le collisioni con i Koopa.
		if (type == GREEN_KOOPA || type == RED_KOOPA) {
			Koopa *k = (Koopa *) enemies[collidedEnemy];
			if (!(k -> isMoving())) {
				if (MarioR.position.x < EnemyR.position.x) {
					*px = *px - IntR.size.x;
					*vx = 0;
					k -> move(RIGHT);
				}
				else {
					*px = *px + IntR.size.x;
					*vx = 0;
					k -> move(LEFT);
				}
				return;
			}
		}
		// Altrimenti è una normale collisione con un nemico.
		if (this -> super) {
			this -> setSuper(false);
			this -> ignoreEnemyCollision = true;
			this -> invisibleTime = 0;
			return;
		}
		this -> setDead(true);
		return;
	}
	// Controllo se ci sono collisioni con i powerup.
	checkPowerupCollision(powerups, MarioR);
}

/**
 *	@brief Funzione di gestione delle collisioni lungo l'asse y
 *
 *	@param px puntatore alla posizione corrente lungo l'asse x
 *	@param py puntatore alla posizione corrente lungo l'asse y
 *	@param vx puntatore alla velocità corrente lungo l'asse y
 *	@param blocks array di puntatori ai blocchi della scena corrente
 */
void Mario::handleYCollisions(
	float *px, 
	float *py, 
	float *vy,
	std::vector<Block *> blocks, 
	std::vector<Enemy *> enemies,
	std::vector<Powerup *> *powerups
) {
	sf::IntRect MarioR({(int) *px, (int) *py}, size), IntR;
	//sf::IntRect MarioR((int) *px, (int) *py, size.x, size.y), IntR;
	int collidedBlock = -1, collidedEnemy = -1;
	// Controllo se c'è una collisione con qualche blocco.
	collidedBlock = checkBlockCollisions(blocks, MarioR, &IntR);
	// Gestisco la collisione con il blocco.
	if (collidedBlock != -1) {
		sf::IntRect BlockR = blocks[collidedBlock] -> getRectangle();
		block_t type = blocks[collidedBlock] -> getType();
		// Se è una moneta non gestisco la collisione.
		if (type == COIN) {
			this -> triggerBlockAction(blocks[collidedBlock], NULL);
			return;
		}
		// Altrimenti si procede normalmente.
		if (MarioR.position.y < BlockR.position.y) {
			this -> onGround = true;
			*py = *py - IntR.size.y;
			*vy = 0;
		}
		else {
			*py = *py + IntR.size.y;
			*vy = 0;
			if (type == QUESTION) {
				this -> triggerBlockAction(blocks[collidedBlock], powerups);
			}
		}
		return;
	}
	// Se sono qui controllo se c'è una collisione con qualche nemico.
	collidedEnemy = checkEnemyCollisions(enemies, MarioR, &IntR);
	if (collidedEnemy != -1 && !ignoreEnemyCollision) {
		sf::IntRect EnemyR = enemies[collidedEnemy] -> getRectangle();
		block_t type = enemies[collidedEnemy] -> getType();
		if (MarioR.position.y < EnemyR.position.y) {
			if (type == PIRANHA_PLANT) {
				if (this -> super) {
					this -> setSuper(false);
					this -> ignoreEnemyCollision = true;
					this -> invisibleTime = 0;
					return;
				}
				this -> setDead(true);
				return;
			}
			if (type == GREEN_KOOPA || type == RED_KOOPA) {
				Koopa *k = (Koopa *) enemies[collidedEnemy];
				if (!(k -> isHit())) this -> playSound(STOMP);
				k -> setHit();
			}
			if (type == GOOMBA) {
				enemies[collidedEnemy] -> setAlive(false);
				enemies[collidedEnemy] -> setCollidable(false);
				this -> playSound(STOMP);
			}
			this -> onGround = true;
			*py = *py - IntR.size.y;
			*vy = 0;
		}
		else {
			*py = *py + IntR.size.y;
			*vy = 0;
		}
		return;
	}
	// Controllo se ci sono collisioni con i powerup.
	checkPowerupCollision(powerups, MarioR);
}

/**
 *	@brief Emette un suono relativo ad un'azione del personaggio
 *
 *	@param id identificativo del suono da riprodurre
 */
void Mario::playSound(mario_sound_t id) {
	if (this -> dead && id != DIE) return;
	this -> sounds[(int) id] -> play();
	return;
}

/**
 *	@brief Funzione invocata quando Mario collide con un blocco dinamico
 *
 *	@param b puntatore al blocco
 *	@param powerups puntatore al vettore dei powerup
 */
void Mario::triggerBlockAction(Block *b, std::vector<Powerup *> *powerups) {
	block_t type = b -> getType();
	switch (type) {
		case QUESTION: {
			Powerup *p;
			// Ho colpito un QuestionBlock.
			QuestionBlock *q = (QuestionBlock *) b;
			q -> hit();
			// Produco il powerup e lo aggiungo alla scena.
			if ((p = q -> getPowerup())) {
				// Controllo che tipo di powerup ho preso.
				powerup_t type = p -> getType();
				if (type == COIN_POWERUP) {
					this -> playSound(PICK_COIN);
					this -> score += SCORE_INC;
				}
				else {
					// Riproduco il suono di uscita powerup.
					this -> playSound(POWERUP_TRIGGERED);
				}
				// Lo aggiungo alla scena.
				powerups -> push_back(p);
			}
		}; break;
		case COIN: {
			((Coin *) b) -> hit();
			this -> playSound(PICK_COIN);
			this -> score += SCORE_INC;
		}; break;
		default: break;
	}
}

/**
 *	@brief Indica se Mario è in modalità super oppure no
 *
 *	@return Un valore di verità che indica se Mario è super oppure no
 */
bool Mario::isSuper() {
	return this -> super;
}

/**
 *	@brief Funzione invocata quando Mario cambia le proprie dimensioni
 *	da normale a super e vicecersa
 *
 *	@param v valore di verità che indica se Mario diventa super oppure no
 */
void Mario::setSuper(bool v) {
	// Voglio settare super a true.
	if (v) {
		// Incremento il punteggio.
		this -> score += 5 * SCORE_INC;
		// Se era già true, non devo fare nulla.
		if (this -> super) return;
		// Altrimenti cambio lo stato.
		this -> size.y = 2 * SIZE;
		this -> super = true;
		this -> textureID = switchMarioTexture(this -> textureID);
		sf::Vector2f p = this -> getPosition();
		this -> sprite.setTextureRect(sf::IntRect({0, 0}, {size.x, size.y}));
		this -> sprite.setTexture(textures[(int) textureID]);
		this -> playSound(POWERUP_TAKEN);
	}
	// Voglio settare super a false.
	else {
		// Se era già false, non devo fare nulla.
		if (!(this -> super)) return;
		// Altrimenti cambio lo stato.
		this -> size.y = SIZE;
		this -> super = false;
		// Ripristino la texture small.
		this -> textureID = switchMarioTexture(this -> textureID);
		this -> sprite.setTextureRect(sf::IntRect({0, 0}, {size.x, size.y}));
		this -> sprite.setTexture(textures[(int) textureID]);
	}
	return;
}

/**
 *	@brief Dice se il personaggio è correntemente in modalità invisibile
 *
 *	@return Un valore di verità che dice se Mario è invisibile
 */
bool Mario::isInvisible() {
	return this -> invisible;
}

/**
 *	@brief Attiva o disattiva la modalità invisibile di Mario
 *
 *	@param v valore di verità che indica se attivare o disattivare
 */
void Mario::setInvisible(bool v) {
	if (v) {
		this -> score += 10 * SCORE_INC;
		if (this -> invisible) return;
		this -> playSound(ONEUP_TAKEN);
		ignoreEnemyCollision = true;
		invisible = true;
	}
	else {
		if (!(this -> invisible)) return;
		ignoreEnemyCollision = false;
		invisible = false;
	}
	invisibleTime = 0;
}

/**
 *	@brief Restituisce un valore di verità che dice se Mario è morto
 *
 * 	@return Un valore di verità che indica se Mario è morto
 */
bool Mario::isDead() {
	return this -> dead;
}

/**
 *	@brief Imposta il valore di verità che dice se Mario è vivo oppure no
 *
 *	@param v valore di verità da assegnare
 */
void Mario::setDead(bool v) {
	this -> dead = v;
	return;
}

/**
 *	@brief Restituisce il punteggio corrente del personaggio
 *
 *	@return Il punteggio corrente totalizzato da Mario
 */
unsigned int Mario::getScore() {
	return this -> score;
}
