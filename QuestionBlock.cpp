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
 *	@param textures_ riferimento al vettore delle texture da utilizzare
 */
QuestionBlock::QuestionBlock(float x, float y, powerup_t id, std::vector<sf::Texture> &textures_) :
	Block(QUESTION, x, y, textures_[0]),
	textures(textures_),
	elapsed(0),
	textureID(ACTIVE_0),
	hasPowerup(true),
	spawn(id)
{
	// Automaticamente vengono settati:
	// this -> active = true;
	// this -> collidable = true;
}

/**
 *	@brief Funzione invocata quando il QuestionBlock viene colpito
 */
void QuestionBlock::hit() {
	if (this -> active) {
		this -> active = false;
		this -> sprite.setTexture(textures[(int) INACTIVE]);
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
		bool loadResult = false;
		sf::Vector2f pos = this -> getPosition();
		switch (this -> spawn) {
			case SUPER_MUSHROOM: {
				// Ottengo la posizione del blocco corrente.
				sf::Texture *t = new sf::Texture();
				loadResult = t -> loadFromFile(SUPERMUSHROOM_TEXTURE);
				if (!loadResult) throw std::runtime_error("getPowerup: Cannot load super mushroom texture.");
				SuperMushroom *m = new SuperMushroom(pos.x, pos.y - SIZE, *t);
				p = (Powerup *) m;
			}; break;
			case ONEUP_MUSHROOM: {
				sf::Texture *t = new sf::Texture();
				loadResult = t -> loadFromFile(ONEUPMUSHROOM_TEXTURE);
				if (!loadResult) throw std::runtime_error("getPowerup: Cannot load one-up mushroom texture.");
				OneUpMushroom *o = new OneUpMushroom(pos.x, pos.y - SIZE, *t);
				p = (Powerup *) o;
			}; break;
			case COIN_POWERUP: {
				sf::Texture *t = new sf::Texture();
				loadResult = t -> loadFromFile(COIN_POWERUP_TEXTURE);
				if (!loadResult) throw std::runtime_error("getPowerup: Cannot load coin texture.");
				CoinPowerup *c = new CoinPowerup(pos.x, pos.y - SIZE, *t);
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
		this -> sprite.setTexture(textures[(int) textureID]);
	}
}
