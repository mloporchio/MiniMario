/**
 *	@file Tilemap.cpp
 *	@author Matteo Loporchio
 *
 *	This file contains the implementation of the data structures and functions for the game tilemap.
 */

#include "Tilemap.hpp"
#include <stdexcept>

/**
 *	@brief Tilemap constructor
 *
 *	@param nrows number of rows of the tilemap
 *	@param ncols number of columns of the tilemap
 *
 *	@throw std::invalid_argument if the number of rows or columns is not positive
 */
Tilemap::Tilemap(unsigned int nrows, unsigned int ncols) : rows(nrows), cols(ncols) {
    if (!(rows > 0 && cols > 0)) {
        throw std::invalid_argument("Rows and columns must be positive integers.");
    }
    map = new block_t*[rows];
    for (unsigned int i = 0; i < rows; i++) {
        map[i] = new block_t[cols]();
    }
}

/**
 *	@brief Tilemap constructor
 *
 *	@param fp pointer to the file (should be already open)
 *
 *	@throw std::invalid_argument if the file pointer is NULL
 */
Tilemap::Tilemap(FILE *fp) {
    if (!fp) throw std::invalid_argument("File pointer is NULL.");
	// Read the width and height of the tilemap from the file.
	unsigned int size[2];
	fread(size, sizeof(unsigned int), 2, fp);
	// Create the tilemap with the specified dimensions.
    this -> rows = size[0];
    this -> cols = size[1];
    this -> map = new block_t*[this -> rows];
    for (unsigned int i = 0; i < this -> rows; i++) {
        this -> map[i] = new block_t[this -> cols]();
    }
	// Read the content of the matrix.
    for (int i = 0; i < size[0]; i++) {
        fread(this -> map[i], sizeof(block_t), size[1], fp);
	}
}

/**
 *	@brief Tilemap destructor
 *
 *	Destroys the tilemap and frees the allocated memory.
 */
Tilemap::~Tilemap() {
    for (unsigned int i = 0; i < rows; i++) {
        delete[] map[i];
    }
    delete[] map;
}

/**
 *	@brief Returns the number of rows of the tilemap
 *
 *	@return The number of rows of the tilemap
 */
unsigned int Tilemap::getRows() {
    return this -> rows;
}

/**
 *	@brief Returns the number of columns of the tilemap
 *
 *	@return The number of columns of the tilemap
 */
unsigned int Tilemap::getCols() {
    return this -> cols;
}

/**
 *	@brief Returns the value of a cell in the tilemap
 *
 *	@param i row index of the cell
 *	@param j column index of the cell
 *
 * 	@return The value of the element at position (i, j) within the tilemap.
 */
block_t Tilemap::getElement(unsigned int i, unsigned int j) {
    if (i >= this -> rows || j >= this -> cols) {
        throw std::out_of_range("getElement: Index out of range.");
    }
    return this -> map[i][j];
}

/**
 *	@brief Assigns a value to a cell in the tilemap
 *
 *	@param i row index of the cell
 *	@param j column index of the cell
 *	@param e the element to assign to the cell
 */
void Tilemap::setElement(unsigned int i, unsigned int j, block_t e) {
    if (i >= this -> rows || j >= this -> cols) {
        throw std::out_of_range("setElement: Index out of range.");
    }
    this -> map[i][j] = e;
}

/**
 *	@brief Saves the tilemap to a file in binary format
 *
 *	@param fp pointer to the file (should be already open)
 *
 *  @throw std::invalid_argument if the file pointer is NULL or the tilemap is NULL
 */
void Tilemap::save(FILE *fp) {
    // Check that the file pointer is not NULL.
    if (!fp) {
        throw std::invalid_argument("save: File pointer is NULL.");
    }
    // Check that the tilemap is not NULL.
    if (!this -> map) {
        throw std::invalid_argument("save: Tilemap is NULL.");
    }
	// Rewind the file.
	rewind(fp);
	// Write the width and height of the tilemap to the file.
	unsigned int size[2];
	size[0] = this -> rows;
	size[1] = this -> cols;
	fwrite(size, sizeof(unsigned int), 2, fp);
	// Write the content of the matrix.
	for (int i = 0; i < this -> rows; i++) {
		fwrite(this -> map[i], sizeof(block_t), this -> cols, fp);
	}
	// Rewind the file.
	rewind(fp);
}


