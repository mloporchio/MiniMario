/**
 *	@file tilemap.h
 *	@author Matteo Loporchio
 *
 *	@brief Definizioni di strutture dati e funzioni per la tilemap
 *
 *	Questo file contiene la definizione delle strutture dati e delle
 *	funzioni per la gestione della tilemap.
 */

#ifndef TILEMAP_H
#define TILEMAP_H

#include <stdio.h>

/** Numero di blocchi rappresentati. */
#define BLOCK_N 20

/**
 *	@brief Rappresenta il generico elemento della tilemap
 *
 *	Rappresenta il generico elemento della tilemap, detto anche blocco.
 */
typedef enum {
	EMPTY 		= 0,
	SKY		= 1,
	BRICKS 		= 2,
	QUESTION 	= 3,
	TERRAIN 	= 4,
	SOLID 		= 5,
	COIN		= 6,
	BUSH_L		= 7,
	BUSH_M		= 8,
	BUSH_R		= 9,
	PIPE_TOP_L 	= 10,
	PIPE_TOP_R	= 11,
	PIPE_BOTTOM_L 	= 12,
	PIPE_BOTTOM_R 	= 13,
	GRASS		= 14,
	WATER		= 15,
	GOOMBA		= 16,
	GREEN_KOOPA	= 17,
	RED_KOOPA	= 18,
	PIRANHA_PLANT 	= 19
} block_t;


/**
 *	@brief Rappresenta la generica tilemap.
 *
 *	Una tilemap è rappresentata come una matrice di blocchi.
 */
typedef struct {
	unsigned int rows;
	unsigned int cols;
	block_t **map;
} tilemap_t;

/**
 *	@brief Crea una nuova tilemap
 *
 *	@param nrows il numero di righe della tilemap
 *	@param ncols il numero di colonne della tilemap
 *
 *	@return Un puntatore alla tilemap creata in caso di successo,
 *	NULL in caso di fallimento.
 */
tilemap_t *newTilemap(unsigned int nrows, unsigned int ncols);

/**
 *	@brief Elimina una tilemap
 *
 *	@param t puntatore alla tilemap
 *
 *	Elimina la tilemap passata come argomento, liberando in modo
 *	opportuno la memoria.
 */
void destroyTilemap(tilemap_t *t);

/**
 *	@brief Assegna un valore ad una casella della tilemap
 *
 *	@param t puntatore alla tilemap
 *	@param i indice di riga della casella
 *	@param j indice di colonna della casella
 *	@param e l'elemento da assegnare alla casella
 *
 *	Assegna il valore specificato all'elemento di posizione (i, j)
 *	all'interno della tilemap.
 */
void setElement(tilemap_t *t, unsigned int i, unsigned int j, block_t e);

/**
 *	@brief Restituisce il valore di una casella della tilemap
 *
 *	@param t puntatore alla tilemap
 *	@param i indice di riga della casella
 *	@param j indice di colonna della casella
 *
 * 	@return Il valore dell'elemento di posizione (i, j) all'interno
 * 	della tilemap.
 */
block_t getElement(tilemap_t *t, unsigned int i, unsigned int j);

/**
 *	@brief Salva la tilemap su un file specificato, in formato binario
 *
 *	@param t puntatore alla tilemap
 *	@param fp puntatore al file
 *
 *	@return Restituisce 0 in caso di successo, 1 altrimenti.
 *
 *	@note Si suppone che il file sia già stato aperto.
 */
int saveTilemap(tilemap_t *t, FILE *fp);

/**
 *	@brief Carica una tilemap dal file specificato, in formato binario
 *
 *	@param fp puntatore al file
 *
 *	@return Restituisce un puntatore alla tilemap in caso di successo,
 *	NULL in caso di fallimento.
 *
 *	@note Si suppone che il file sia già stato aperto.
 */
tilemap_t *loadTilemap(FILE *fp);

#endif
