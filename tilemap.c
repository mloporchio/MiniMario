/**
 *	@file tilemap.c
 *	@author Matteo Loporchio
 *
 *	@brief Implementazione delle funzioni per la tilemap
 *
 *	Questo file contiene l'Implementazione delle funzioni per
 *	la gestione della tilemap, definite in tilemap.h.
 */

#include <stdlib.h>
#include "tilemap.h"

/**
 *	@brief Crea una nuova tilemap
 *
 *	@param nrows il numero di righe della tilemap
 *	@param ncols il numero di colonne della tilemap
 *
 *	@return Un puntatore alla tilemap creata in caso di successo,
 *	NULL in caso di fallimento.
 */
tilemap_t *newTilemap(unsigned int nrows, unsigned int ncols) {
	tilemap_t *t = (tilemap_t *) malloc(sizeof(tilemap_t));
	if (t) {
		t -> rows = nrows;
		t -> cols = ncols;
		t -> map = (block_t **) calloc(nrows, sizeof(block_t *));
		if (t -> map) {
			for (int i = 0; i < nrows; i++) {
				t -> map[i] = (block_t *) calloc(ncols, sizeof(block_t));
				// Controllo se l'allocazione non ha avuto successo.
				if (!(t -> map[i])) {
					// Rollback in caso di fallimento.
					for (int j = 0; j < i; j++) free(t -> map[j]);
					free(t -> map);
					free(t);
					return NULL;
				}
			}
			// Se sono qui, tutto è andato bene.
			return t;
		}
		// Se sono qui, l'allocazione di t -> map non ha avuto successo.
		free(t);
	}
	return NULL;
}

/**
 *	@brief Elimina una tilemap
 *
 *	@param t puntatore alla tilemap
 *
 *	Elimina la tilemap passata come argomento, liberando in modo
 *	opportuno la memoria.
 */
void destroyTilemap(tilemap_t *t) {
	if (t) {
		if (t -> map) {
			for (int i = 0; i < t -> rows; i++) {
				if (t -> map[i]) free(t -> map[i]);
			}
			free(t -> map);
		}
		free(t);
	}
	return;
}

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
void setElement(tilemap_t *t, unsigned int i, unsigned int j, block_t e) {
	if (t && (t -> map) && (t -> map[i])) {
		t -> map[i][j] = e;
	}
	return;
}

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
block_t getElement(tilemap_t *t, unsigned int i, unsigned int j) {
	if (t && (t -> map) && (t -> map[i])) {
		return (t -> map[i][j]);
	}
	return EMPTY;
}

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
int saveTilemap(tilemap_t *t, FILE *fp) {
	if (t && t -> map && fp) {
		// Riavvolgo il file.
		rewind(fp);
		// Scrivo su file la larghezza e la lunghezza della tilemap.
		unsigned int size[2];
		size[0] = t -> rows;
		size[1] = t -> cols;
		fwrite(size, sizeof(unsigned int), 2, fp);
		// Scrivo il contenuto della matrice.
		for (int i = 0; i < t -> rows; i++) {
			fwrite(t -> map[i], sizeof(block_t), t -> cols, fp);
		}
		// Riavvolgo nuovamente il file.
		rewind(fp);
		return 0;
	}
	return 1;
}

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
tilemap_t *loadTilemap(FILE *fp) {
	if (fp) {
		// Leggo da file la larghezza e l'altezza della tilemap.
		unsigned int size[2];
		fread(size, sizeof(unsigned int), 2, fp);
		// Creo la nuova tilemap.
		tilemap_t *t = newTilemap(size[0], size[1]);
		if (t && t -> map) {
			for (int i = 0; i < size[0]; i++) {
				fread(t -> map[i], sizeof(block_t), size[1], fp);
			}
			return t;
		}
	}
	return NULL;
}
