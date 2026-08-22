/**
 *	@file Koopa.cpp
 *	@author Matteo Loporchio
 *
 * 	@brief Contiene l'implementazione della classe relativa al nemico Koopa
 */

#include "Koopa.hpp"
#include "Physics.hpp"

/**
 *	@brief Costruttore della classe Koopa
 *
 *	@param x posizione iniziale sull'asse x
 *	@param y posizione iniziale sull'asse y
 *	@param k identificativo del tipo di Koopa (verde o rosso)
 *	@param textures puntatore al vettore contenente le texture
 */
Koopa::Koopa(float x, float y, block_t k, std::vector<sf::Texture> *textures)
	: Enemy(k, x, y, SIZE, KOOPA_HEIGHT, ((*textures)[0])) {
	this -> textures = textures;
	this -> textureID = ((k == GREEN_KOOPA) ? GREEN_KOOPA_0 : RED_KOOPA_0);
	this -> hit = false;
	this -> elapsed = 0;
	this -> setSpeed(-KOOPA_SPEED, 0);
}

/**
 *	@brief Dice se Koopa è atterrato (sul suolo)
 *
 *	@return Un valore di verità che indica se Koopa è atterrato
 */
bool Koopa::isOnGround() {
	return this -> onGround;
}

/**
 *	@brief Dice se Koopa è stato colpito dall'alto
 *
 *	@return Un valore di verità che indica se Koopa è stato colpito
 */
bool Koopa::isHit() {
	return this -> hit;
}

/**
 *	@brief Funzione invocata quando Koopa viene colpito dall'alto
 *	e si ritira dentro il guscio
 */
void Koopa::setHit() {
	if (!hit) {
		this -> textureID = ((this -> type == GREEN_KOOPA) ?
		GREEN_KOOPA_SHELL : RED_KOOPA_SHELL);
		this -> size.x = SIZE;
		this -> size.y = SIZE;
	}
	this -> speed.x = 0;
	this -> hit = true;
}

/**
 *	@brief Indica se il guscio di Koopa è in movimento oppure no
 *
 *	@return Un valore di verità che indica il movimento del guscio di Koopa
 */
bool Koopa::isMoving() {
	return (this -> speed.x != 0);
}

/**
 *	@brief Funzione invocata quando il guscio di Koopa viene spinto
 *
 *	@param d direzione in cui mandare il guscio
 */
void Koopa::move(direction_t d) {
	switch (d) {
		case LEFT: this -> speed.x = -3 * KOOPA_SPEED; break;
		case RIGHT: this -> speed.x = 3 * KOOPA_SPEED; break;
		default: break;
	}
}

/**
 *	@brief Funzione di aggiornamento del personaggio Koopa
 *
 * 	@param dt intervallo di tempo
 *	@param blocks vettore dei blocchi
 *	@param enemies vettore dei nemici
 *	@param index indice del personaggio nel vettore dei nemici
 */
void Koopa::update(sf::Time dt, std::vector<Block *> blocks,
	std::vector<Enemy *> enemies, int index) {
	float posX = this -> sprite.getPosition().x;
	float posY = this -> sprite.getPosition().y;
	float velX = this -> speed.x;
	float velY = this -> speed.y;
	posX += velX * 0.3f;
	handleXCollisions(&posX, &posY, &velX, blocks, enemies, index);
	posY += velY * 0.5f;
	handleYCollisions(&posX, &posY, &velY, blocks, enemies, index);
	if ((velY += GRAVITY * 0.5f) > FALL_SPEED) velY = FALL_SPEED;
	// Scrivo i risultati dei calcoli.
	this -> setPosition(posX, posY);
	this -> speed.x = velX;
	this -> speed.y = velY;
	// Aggiorno la texture del personaggio.
	if (!hit) {
		if (elapsed >= KOOPA_ANIMATION_TIME) {
			this -> textureID = nextKoopaTexture(this -> textureID);
			elapsed = 0;
		}
		else elapsed += dt.asMilliseconds();
	}
	else this -> sprite.setTextureRect(sf::IntRect({0, 0}, {size.x, size.y}));
	this -> sprite.setTexture((*textures)[(int) textureID]);
}

/**
 *	@brief Funzione di gestione delle collisioni di Koopa lungo l'asse x
 *
 * 	@param px puntatore alla posizione corrente lungo l'asse x
 * 	@param py puntatore alla posizione corrente lungo l'asse y
 * 	@param vx puntatore alla velocità corrente lungo l'asse x
 * 	@param blocks vettore dei blocchi
 * 	@param enemies vettore dei nemici
 * 	@param index indice del personaggio nel vettore dei nemici
 */
void Koopa::handleXCollisions(float *px, float *py, float *vx,
	std::vector<Block *> blocks, std::vector<Enemy *> enemies, int index) {
	sf::IntRect KoopaR({(int) *px, (int) *py}, {size.x, size.y}), BlockR, EnemyR, IntR;
	bool collidable = false;
	// Controllo se c'è una collisione con un blocco.
	for (int i = 0; i < blocks.size(); i++) {
		BlockR = blocks[i] -> getRectangle();
		collidable = blocks[i] -> isCollidable();
		std::optional<sf::IntRect> intersection = KoopaR.findIntersection(BlockR);
		if (collidable && intersection.has_value()) {
			sf::IntRect IntR = intersection.value();
			block_t type = blocks[i] -> getType();
			// Se il blocco è una moneta, ignoro la collisione.
			if (type == COIN) return;
			if (KoopaR.position.x < BlockR.position.x) {
				*px = *px - IntR.size.x;
				*vx = -(*vx);
				this -> textureID = flipKoopaTexture(this -> textureID);
			}
			else {
				*px = *px + IntR.size.x;
				*vx = -(*vx);
				this -> textureID = flipKoopaTexture(this -> textureID);
			}
			return;
		}
	}
	// Controllo se c'è una collisione con un nemico.
	for (int i = 0; i < enemies.size(); i++) {
		EnemyR = enemies[i] -> getRectangle();
		collidable = enemies[i] -> isCollidable();
		std::optional<sf::IntRect> intersection = KoopaR.findIntersection(EnemyR);
		if (collidable && intersection.has_value() && i != index) {
			sf::IntRect IntR = intersection.value();
			// Se Koopa ha solo il guscio, ignoro le collisioni con i nemici.
			if (this -> hit) {
				enemies[i] -> setAlive(false);
				enemies[i] -> setCollidable(false);
				return;
			}
			// Altrimenti procedo normalmente.
			if (KoopaR.position.x < EnemyR.position.x) {
				*px = *px - IntR.size.x;
				*vx = -(*vx);
				this -> textureID = flipKoopaTexture(this -> textureID);
			}
			else {
				*px = *px + IntR.size.x;
				*vx = -(*vx);
				this -> textureID = flipKoopaTexture(this -> textureID);
			}
			return;
		}
	}
}

/**
 *	@brief Funzione di gestione delle collisioni di Koopa lungo l'asse y
 *
 * 	@param px puntatore alla posizione corrente lungo l'asse x
 * 	@param py puntatore alla posizione corrente lungo l'asse y
 * 	@param vy puntatore alla velocità corrente lungo l'asse y
 * 	@param blocks vettore dei blocchi
 * 	@param enemies vettore dei nemici
 * 	@param index indice del personaggio nel vettore dei nemici
 */
void Koopa::handleYCollisions(float *px, float *py, float *vy,
	std::vector<Block *> blocks, std::vector<Enemy *> enemies, int index) {
	sf::IntRect KoopaR({(int) *px, (int) *py}, {size.x, size.y}), BlockR, EnemyR, IntR;
	bool collidable = false;
	// Controllo se c'è una collisione con un blocco.
	for (int i = 0; i < blocks.size(); i++) {
		BlockR = blocks[i] -> getRectangle();
		collidable = blocks[i] -> isCollidable();
		std::optional<sf::IntRect> intersection = KoopaR.findIntersection(BlockR);
		if (collidable && intersection.has_value()) {
			sf::IntRect IntR = intersection.value();
			block_t type = blocks[i] -> getType();
			// Se il blocco è una moneta, ignoro la collisione.
			if (type == COIN) return;
			if (KoopaR.position.y < BlockR.position.y) {
				*py = *py - IntR.size.y;
				*vy = 0;
			}
			else {
				*py = *py + IntR.size.y;
				*vy = 0;
			}
			return;
		}
	}
	// Controllo se c'è una collisione con un nemico.
	for (int i = 0; i < enemies.size(); i++) {
		EnemyR = enemies[i] -> getRectangle();
		collidable = enemies[i] -> isCollidable();
		std::optional<sf::IntRect> intersection = KoopaR.findIntersection(EnemyR);
		if (collidable && intersection.has_value() && i != index) {
			sf::IntRect IntR = intersection.value();
			if (KoopaR.position.y < EnemyR.position.y) {
				*py = *py - IntR.size.y;
				*vy = 0;
			}
			else {
				*py = *py + IntR.size.y;
				*vy = 0;
			}
			return;
		}
	}
}
