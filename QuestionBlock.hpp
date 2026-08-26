/**
 *	@file QuestionBlock.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Definition of the QuestionBlock class
 */
#ifndef QUESTIONBLOCK_H
#define QUESTIONBLOCK_H

#include "Block.hpp"
#include "Powerup.hpp"
#include "Textures.hpp"

class QuestionBlock : public Block {
	private:
		std::vector<sf::Texture> &textures;
		question_texture_t textureID;
		powerup_t spawn;
		int elapsed;
		bool hasPowerup;
	public:
		QuestionBlock(float x, float y, powerup_t id, std::vector<sf::Texture> &textures_);
		void setActive(bool v);
		bool getActive();
		void hit();
		Powerup *getPowerup();
		void update(sf::Time dt);
};

/**
 *	@brief Restituisce la prossima texture da utilizzare per il Question Block
 *
 *	@param id identificativo della texture corrente
 *
 *	@return L'identificativo della prossima texture da usare
 */
static inline question_texture_t nextQuestionTexture(question_texture_t id) {
	switch (id) {
		case ACTIVE_0: return ACTIVE_1;
		case ACTIVE_1: return ACTIVE_2;
		case ACTIVE_2: return ACTIVE_0;
		default: return INACTIVE;
	}
}

#endif
