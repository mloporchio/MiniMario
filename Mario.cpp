/**
 *	@file Mario.cpp
 *	@author Matteo Loporchio
 *
 *	@brief Implementation of the Mario class
 */

#include <climits>
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
 *	@brief Loads Mario textures from a texture sheet
 *
 *	@return vector containing the textures loaded from the texture sheet
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
 *	@brief Mario constructor
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
 *	@brief Mario destructor
 */
Mario::~Mario() {
	// Nothing to do here.
}

/**
 *	@brief Loads Mario's sound effects
 */
void Mario::loadSounds() {
	for (int i = 0; i < MARIO_SOUND_N; ++i) {
        auto sb = std::make_unique<sf::SoundBuffer>();
        if (!sb->loadFromFile(getMarioSoundPath(static_cast<mario_sound_t>(i)))) {
            throw std::runtime_error("loadSounds: Cannot load sound.");
        }
        auto sound = std::make_unique<sf::Sound>(*sb);
        this->soundBuffers.push_back(std::move(sb));
        this->sounds.push_back(std::move(sound));
    }
}

/**
 *	@brief Returns Mario's current position
 *
 *	@return Mario's position vector
 */
sf::Vector2f Mario::getPosition() {
	return this -> sprite.getPosition();
}

/**
 *	@brief Sets Mario's current position
 *
 *	@param x x-axis position
 *	@param y y-axis position
 */
void Mario::setPosition(float x, float y) {
	this -> sprite.setPosition({x, y});
}

/**
 *	@brief Returns Mario's current bounding rectangle
 *
 *	@return bounding rectangle of Mario
 */
sf::IntRect Mario::getRectangle() {
	sf::Vector2f p = this -> getPosition();
	return sf::IntRect({static_cast<int>(p.x), static_cast<int>(p.y)}, {this->size.x, this->size.y});
}

/**
 *	@brief Returns Mario's sprite
 *
 *	@return sprite associated with Mario
 */
sf::Sprite Mario::getSprite() {
	return this -> sprite;
}

/**
 *	@brief Returns Mario's current speed
 *
 *	@return Mario's speed vector 
 */
sf::Vector2f Mario::getSpeed() {
	return this -> speed;
}

/**
 *	@brief Sets Mario's current speed
 *
 *	@param x x-axis speed
 *	@param y y-axis speed
 */
void Mario::setSpeed(float x, float y) {
	this -> speed.x = x;
	this -> speed.y = y;
}

/**
 *	@brief Called when Mario starts jumping
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
 *	@brief Called when Mario stops jumping
 */
void Mario::endJump() {
	if (this -> speed.y < -JUMP_SPEED / 2) {
		this -> speed.y = -JUMP_SPEED / 2;
	}
}

/**
 *	@brief Called when Mario starts running
 *
 *	@param d direction in which Mario should move
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
			default: {
				this -> speed.x = 0; 
			}; break;
		}
		this -> sprite.setTexture(textures[(int) textureID]);
		this -> running = true;
	}
}

/**
 *	@brief Called when Mario stops running
 */
void Mario::endRunning() {
	this -> running = false;
	this -> speed.x = 0;
}

/**
 *	@brief Updates Mario's texture
 *
 *	@param dt time elapsed since last update
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
 *	@brief Update function for Mario
 *
 *	@param dt time elapsed since last update
 *	@param blocks vector of pointers to the current scene's blocks
 *	@param enemies vector of pointers to the current scene's enemies
 *	@param powerups vector of pointers to the current scene's powerups
 */
void Mario::update(sf::Time dt, std::vector<Block *> &blocks, std::vector<Enemy *> &enemies, std::vector<Powerup *> &powerups) {
	sf::Vector2f pos = this -> getPosition();
	sf::Vector2f vel = this -> getSpeed();
	this->onGround = false;
	pos.x += vel.x * 0.3f;
	handleXCollisions(pos.x, pos.y, vel.x, blocks, enemies, powerups);
	pos.y += vel.y * 0.5f;
	handleYCollisions(pos.x, pos.y, vel.y, blocks, enemies, powerups);
	if ((vel.y += GRAVITY * 0.5f) > FALL_SPEED) vel.y = FALL_SPEED;
	this -> setPosition(pos.x, pos.y);
	this -> setSpeed(vel.x, vel.y);
	updateTexture(dt);
}

/**
 *	@brief Checks for collisions between Mario and a block
 *
 *	@param blocks vector of pointers to the current scene's blocks
 *	@param MarioR current bounding rectangle of Mario
 *	@param IntR pointer to the intersection rectangle
 *
 *	@return index of the block intersected in case of intersection, -1 in case of no intersection
 */
int Mario::checkBlockCollisions(std::vector<Block *> &blocks, sf::IntRect &MarioR, sf::IntRect &IntR) {
	for (int i = 0; i < blocks.size(); i++) {
		if (!blocks[i] -> isCollidable()) continue;
		auto intersection = MarioR.findIntersection(blocks[i] -> getRectangle());
		if (intersection.has_value()) {
			IntR = intersection.value();
			return i;
		}
	}
	return -1;
}

/**
 *	@brief Checks for collisions between Mario and an enemy
 *
 *	@param enemies vector of pointers to the current scene's enemies
 *	@param MarioR current bounding rectangle of Mario
 *	@param IntR pointer to the intersection rectangle
 *
 *	@return index of the enemy intersected in case of intersection, -1 in case of no intersection
 */
int Mario::checkEnemyCollisions(std::vector<Enemy *> &enemies, sf::IntRect &MarioR, sf::IntRect &IntR) {
	for (int i = 0; i < enemies.size(); i++) {
		if (!enemies[i] -> isCollidable()) continue;
		auto intersection = MarioR.findIntersection(enemies[i] -> getRectangle());
		if (intersection.has_value()) {
			IntR = intersection.value();
			return i;
		}
	}
	return -1;
}

/**
 *	@brief Checks for collisions between Mario and a powerup
 *
 *	@param powerups vector of pointers to the current scene's powerups
 *	@param MarioR current bounding rectangle of Mario
 */
void Mario::checkPowerupCollision(std::vector<Powerup *> &powerups, sf::IntRect &MarioR) {
	sf::IntRect PowerR;
	bool taken = false;
	powerup_t type;
	for (int i = 0; i < powerups.size(); i++) {
		PowerR = powerups[i] -> getRectangle();
		taken = powerups[i] -> isTaken();
		type = powerups[i] -> getType();
		std::optional<sf::IntRect> intersection = MarioR.findIntersection(PowerR);
		if (!taken && intersection.has_value()) {
			// Controllo di che tipo si tratta.
			switch (type) {
				case SUPER_MUSHROOM: this -> setSuper(true); break;
				case ONEUP_MUSHROOM: this -> setInvisible(true); break;
				default: break;
			}
			powerups[i] -> setTaken(true);
		}
	}
	return;
}

/**
 *	@brief Checks for collisions between Mario and the level boundary
 *
 *	@param px current position along the x axis
 *	@param vx current velocity along the x axis
 *
 *	@brief true if there is a collision, false otherwise
 */
bool Mario::checkBorderCollision(float &px, float &vx) {
	if (px < 0) {
		px = 0;
		vx = 0;
		return true;
	}
	return false;
}

/**
 *	@brief Handles Mario's collisions along the x axis
 *
 *	@param px current position along the x axis
 *	@param py current position along the y axis
 *	@param vx current velocity along the x axis
 *	@param blocks vector of pointers to the current scene's blocks
 *	@param enemies vector of pointers to the current scene's enemies
 *	@param powerups vector of pointers to the current scene's powerups
 */
void Mario::handleXCollisions(
	float &px, 
	float &py, 
	float &vx,
	std::vector<Block *> &blocks, 
	std::vector<Enemy *> &enemies, 
	std::vector<Powerup *> &powerups
) {
	// Controllo se il personaggio ha posizione negativa.
	if (checkBorderCollision(px, vx)) return;
	// Build Mario's current bounding rectangle.
	sf::IntRect MarioR{{static_cast<int>(px), static_cast<int>(py)}, {this->size.x, this->size.y}};
	sf::IntRect IntR;
	// Controllo se c'è una collisione con qualche blocco.
	int collidedBlock = checkBlockCollisions(blocks, MarioR, IntR);
	// Gestisco la collisione con il blocco.
	if (collidedBlock != -1) {
		// Determino il rettangolo e il tipo del blocco.
		sf::IntRect BlockR = blocks[collidedBlock] -> getRectangle();
		block_t type = blocks[collidedBlock] -> getType();
		// Se è una moneta non gestisco la collisione.
		if (type == COIN) {
			this -> interactWithCoin(blocks[collidedBlock]);
			return;
		}
		// Altrimenti si procede normalmente.
		if (MarioR.position.x < BlockR.position.x) {
			px = px - IntR.size.x;
			vx = 0;
		}
		else {
			px = px + IntR.size.x;
			vx = 0;
		}
		// Termino non appena ho gestito la collisione.
		return;
	}
	// Se sono qui controllo se c'è una collisione con qualche nemico.
	int collidedEnemy = checkEnemyCollisions(enemies, MarioR, IntR);
	if (collidedEnemy != -1 && !ignoreEnemyCollision) { // Mario muore.
		sf::IntRect EnemyR = enemies[collidedEnemy] -> getRectangle();
		block_t type = enemies[collidedEnemy] -> getType();
		// Tratto le collisioni con i Koopa.
		if (type == GREEN_KOOPA || type == RED_KOOPA) {
			Koopa *k = (Koopa *) enemies[collidedEnemy];
			if (!(k -> isMoving())) {
				if (MarioR.position.x < EnemyR.position.x) {
					px = px - IntR.size.x;
					vx = 0;
					k -> move(RIGHT);
				}
				else {
					px = px + IntR.size.x;
					vx = 0;
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
 *	@brief Handles Mario's collisions along the y axis
 *
 *	@param px current position along the x axis
 *	@param py current position along the y axis
 *	@param vy current velocity along the y axis
 *	@param blocks vector of pointers to the current scene's blocks
 *	@param enemies vector of pointers to the current scene's enemies
 *	@param powerups vector of pointers to the current scene's powerups
 */
void Mario::handleYCollisions(
	float &px, 
	float &py, 
	float &vy,
	std::vector<Block *> &blocks, 
	std::vector<Enemy *> &enemies,
	std::vector<Powerup *> &powerups
) {
	// Build Mario's current bounding rectangle.
	sf::IntRect MarioR{{static_cast<int>(px), static_cast<int>(py)}, {this->size.x, this->size.y}};
	sf::IntRect IntR;
	// Controllo se c'è una collisione con qualche blocco.
	int collidedBlock = checkBlockCollisions(blocks, MarioR, IntR);
	// Gestisco la collisione con il blocco.
	if (collidedBlock != -1) {
		sf::IntRect BlockR = blocks[collidedBlock] -> getRectangle();
		block_t type = blocks[collidedBlock] -> getType();
		// Se è una moneta non gestisco la collisione.
		if (type == COIN) {
			this -> interactWithCoin(blocks[collidedBlock]);
			return;
		}
		// Altrimenti si procede normalmente.
		if (MarioR.position.y < BlockR.position.y) {
			this -> onGround = true;
			py = py - IntR.size.y;
			vy = 0;
		}
		else {
			py = py + IntR.size.y;
			vy = 0;
			if (type == QUESTION) {
				this -> interactWithQuestionBlock(blocks[collidedBlock], powerups);
			}
		}
		return;
	}
	// Se sono qui controllo se c'è una collisione con qualche nemico.
	int collidedEnemy = checkEnemyCollisions(enemies, MarioR, IntR);
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
			vy = 0;
			this -> onGround = true;
			py = py - IntR.size.y;
			if (type == GREEN_KOOPA || type == RED_KOOPA) {
				Koopa *k = (Koopa *) enemies[collidedEnemy];
				if (!(k -> isHit())) this -> playSound(STOMP);
				k -> setHit();
			}
			if (type == GOOMBA) {
				enemies[collidedEnemy] -> setAlive(false);
				enemies[collidedEnemy] -> setCollidable(false);
				this -> playSound(STOMP);
				vy = -BOUNCE_SPEED;
			}
		}
		else {
			py = py + IntR.size.y;
			vy = 0;
		}
		return;
	}
	// Controllo se ci sono collisioni con i powerup.
	checkPowerupCollision(powerups, MarioR);
}

/**
 *	@brief Plays a sound related to Mario's action
 *
 *	@param id identifier of the sound to play
 */
void Mario::playSound(mario_sound_t id) {
	if (this -> dead && id != DIE) return;
	this -> sounds[(int) id] -> play();
	return;
}

/**
 *	@brief Called when Mario has collided with a Coin block
 *
 *	@param b pointer to a Coin block
 */
void Mario::interactWithCoin(Block *b) {
	if (b -> getType() != COIN) return;
	((Coin *) b) -> hit();
	this -> playSound(PICK_COIN);
	this -> score += SCORE_INC;
}

/**
 *	@brief Called when Mario has collided with a QuestionBlock
 *
 *	@param b pointer to a QuestionBlock
 */
void Mario::interactWithQuestionBlock(Block *b, std::vector<Powerup *> &powerups) {
	if (b -> getType() != QUESTION) return;
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
			this -> score += 5 * SCORE_INC;
		}
		// Lo aggiungo alla scena.
		powerups.push_back(p);
	}
}

/**
 *	@brief Tells whether Mario is in super mode or not
 *
 *	@return true if Mario is in super mode, false otherwise
 */
bool Mario::isSuper() {
	return this -> super;
}

/**
 *	@brief Called when Mario changes its size from normal to super and vice versa
 *
 *	@param v true to make Mario super, false to make him normal
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
 *	@brief Tells whether Mario is currently invisible or not
 *
 *	@return true if Mario is invisible, false otherwise
 */
bool Mario::isInvisible() {
	return this -> invisible;
}

/**
 *	@brief Sets whether Mario is invisible or not
 *
 *	@param v true to make Mario invisible, false to make him visible
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
 *	@brief Tells whether Mario is dead or not
 *
 * 	@return true if Mario is dead, false otherwise
 */
bool Mario::isDead() {
	return this -> dead;
}

/**
 *	@brief Sets whether Mario is dead or not
 *
 *	@param v true to make Mario dead, false to let him live
 */
void Mario::setDead(bool v) {
	this -> dead = v;
	return;
}

/**
 *	@brief Returns the current score of Mario
 *
 *	@return total score of Mario
 */
unsigned int Mario::getScore() {
	return this -> score;
}
