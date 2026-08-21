/**
 *	@file QuestionBlock.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Implementazione della classe QuestionBlock relativa al blocco
 *	capace di produrre dei powerup
 */

#include <ctime>
#include "QuestionBlock.hpp"
#include "SuperMushroom.hpp"
#include "OneUpMushroom.hpp"
#include "CoinPowerup.hpp"
#include "Textures.hpp"
#include "Physics.hpp"

/**
 *	@brief Costruttore della classe QuestionBlock
 *
 *	@param x posizione lungo l'asse x
 *	@param y posizione lungo l'asse y
 *	@param id identificativo del tipo di powerup da generare
 *	@param textures puntatore al vettore delle texture da utilizzare
 */
QuestionBlock::QuestionBlock(
	int x, 
	int y, 
	powerup_t id, 
	std::vector<sf::Texture> *textures
) : Block(QUESTION, x, y, &((*textures)[0])) {
	// Automaticamente vengono settati:
	// this -> active = true;
	// this -> collidable = true;
	this -> textures = textures;
	this -> elapsed = 0;
	this -> textureID = ACTIVE_0;
	this -> hasPowerup = true;
	this -> spawn = id;
}

/**
 *	@brief Funzione invocata quando il QuestionBlock viene colpito
 */
void QuestionBlock::hit() {
	if (this -> active) {
		this -> active = false;
		this -> sprite.setTexture((*textures)[(int) INACTIVE]);
	}
}

/**
 *	@brief Restituisce il powerup prodotto dal blocco
 *
 *	@return Un puntatore al nuovo oggetto di tipo Powerup
 */
Powerup *QuestionBlock::getPowerup() {
	if (this -> hasPowerup) {
		Powerup *p = NULL;
		switch (this -> spawn) {
			case SUPER_MUSHROOM: {
				// Ottengo la posizione del blocco corrente.
				sf::Vector2f pos = this -> getPosition();
				sf::Texture *t = new sf::Texture();
				t -> loadFromFile(SUPERMUSHROOM_TEXTURE);
				SuperMushroom *m = new SuperMushroom((int) pos.x,
				((int) pos.y) - SIZE, t);
				p = (Powerup *) m;
			}; break;
			case ONEUP_MUSHROOM: {
				sf::Vector2f pos = this -> getPosition();
				sf::Texture *t = new sf::Texture();
				t -> loadFromFile(ONEUPMUSHROOM_TEXTURE);
				OneUpMushroom *o = new OneUpMushroom((int) pos.x,
				((int) pos.y) - SIZE, t);
				p = (Powerup *) o;
			}; break;
			case COIN_POWERUP: {
				sf::Vector2f pos = this -> getPosition();
				sf::Texture *t = new sf::Texture();
				t -> loadFromFile(COIN_POWERUP_TEXTURE);
				CoinPowerup *c = new CoinPowerup((int) pos.x, ((int) pos.y) - SIZE, t);
				p = (Powerup *) c;
			}; break;
			default: break;
		}
		this -> hasPowerup = false;
		return p;
	}
	return NULL;
}

/**
 *	@brief Funzione di aggiornamento del Question Block
 *
 *	@param dt intervallo di tempo dall'ultimo aggiornamento
 */
void QuestionBlock::update(sf::Time dt) {
	if (this -> active) {
		textureID = nextQuestionTexture(textureID);
		this -> sprite.setTexture((*textures)[(int) textureID]);
	}
}
