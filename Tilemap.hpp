/**
 *	@file Tilemap.hpp
 *	@author Matteo Loporchio
 *
 *	This file contains the definitions of data structures and functions for the game tilemap.
 */

#ifndef TILEMAP_H
#define TILEMAP_H

#include <string>
#include <vector>

/** Number of distinct blocks represented in a tilemap. */
#define BLOCK_N 20

/**
 *	@brief Represents the generic element of the tilemap (a.k.a. block).
 */
typedef enum {
	EMPTY 		    = 0,
	SKY		        = 1,
	BRICKS 		    = 2,
	QUESTION 	    = 3,
	TERRAIN 	    = 4,
	SOLID 		    = 5,
	COIN		    = 6,
	BUSH_L		    = 7,
	BUSH_M		    = 8,
	BUSH_R		    = 9,
	PIPE_TOP_L 	    = 10,
	PIPE_TOP_R	    = 11,
	PIPE_BOTTOM_L 	= 12,
	PIPE_BOTTOM_R 	= 13,
	GRASS		    = 14,
	WATER		    = 15,
	GOOMBA		    = 16,
	GREEN_KOOPA	    = 17,
	RED_KOOPA	    = 18,
	PIRANHA_PLANT 	= 19
} block_t;


/**
 *	@brief Represents a generic tilemap
 *
 *	A tilemap is represented as a rows*cols matrix of blocks.
 *	The tilemap is linearized in memory, i.e., stored as a single vector of block_t elements.
 */
class Tilemap {
public:
    Tilemap(unsigned int rows, unsigned int cols);
    Tilemap(const std::string &path);
    ~Tilemap();
    unsigned int getRows();
    unsigned int getCols();
    void setElement(unsigned int i, unsigned int j, block_t e);
    block_t getElement(unsigned int i, unsigned int j);
    void save(const std::string &path);
private:
    unsigned int rows;
    unsigned int cols;
	std::vector<block_t> map;
};

#endif
