/**
 *	@file Tilemap.cpp
 *	@author Matteo Loporchio
 *
 *	This file contains the implementation of the data structures and functions for the game tilemap.
 */

#include "Tilemap.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>

/** 
 *  @brief Utility function to validate the size of a tilemap
 *
 *  @param n size to validate
 *
 *  @return The input size if it is positive, otherwise throws an exception
 *
 *  @throw std::invalid_argument if the size is not positive
 */
static unsigned int validateSize(unsigned int n) {
    if (n == 0) throw std::invalid_argument("Rows and columns must be positive integers.");
    return n;
}

/**
 *	@brief Tilemap constructor
 *
 *	@param nrows number of rows of the tilemap
 *	@param ncols number of columns of the tilemap
 *
 *	@throw std::invalid_argument if the number of rows or columns is not positive
 */
Tilemap::Tilemap(unsigned int nrows, unsigned int ncols) : 
    rows(validateSize(nrows)), 
    cols(validateSize(ncols)), 
    map(nrows*ncols, EMPTY) 
{
    // Nothing else to do here.
}

/**
 *	@brief Tilemap constructor
 *
 *	@param path path to the file containing the tilemap data
 *
 *	@throw std::invalid_argument if the file pointer is NULL
 */
Tilemap::Tilemap(const std::string &path) {
    // Open the file in binary mode.
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open file: " + path);
    }
    // Read the width and height of the tilemap from the file.
    unsigned int size[2];
    file.read(reinterpret_cast<char*>(size), sizeof(size));
    if (!file) {
        throw std::runtime_error("Could not read tilemap dimensions.");
    }
    // Create the tilemap with the specified dimensions.
    this->rows = size[0];
    this->cols = size[1];
    if (this->rows == 0 || this->cols == 0) {
        throw std::runtime_error("Invalid tilemap dimensions.");
    }
    // Allocate the linearized tilemap.
    this->map.resize(this->rows * this->cols);
    // Read the tilemap data.
    file.read(reinterpret_cast<char*>(this->map.data()), this->map.size() * sizeof(block_t));
    if (!file) {
        throw std::runtime_error("Could not read tilemap data.");
    }
}

/**
 *	@brief Tilemap destructor
 */
Tilemap::~Tilemap() {
    std::cout << "Tilemap destroyed!" << std::endl;
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
    return this -> map[i * (this -> cols) + j];
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
    this -> map[i * (this -> cols) + j] = e;
}

/**
 *	@brief Saves the tilemap to a file in binary format
 *
 *	@param path the path to the file where the tilemap will be saved
 *
 *  @throw std::invalid_argument if the file pointer is NULL or the tilemap is NULL
 */
void Tilemap::save(const std::string &path) {
    // Open the file in binary mode.
    std::ofstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("save: Could not open file: " + path);
    }
    // Write the width and height of the tilemap to the file.
    unsigned int size[2];
    size[0] = this->rows;
    size[1] = this->cols;
    file.write(reinterpret_cast<char*>(size), sizeof(size));
    if (!file) {
        throw std::runtime_error("save: Could not write tilemap dimensions.");
    }
    // Write the content of the matrix.
    file.write(reinterpret_cast<char*>(this->map.data()), this->map.size() * sizeof(block_t));
    if (!file) {
        throw std::runtime_error("save: Could not write tilemap data.");
    }
}

