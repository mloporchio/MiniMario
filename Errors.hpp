/**
 *	@file Errors.hpp
 *	@author Matteo Loporchio
 *
 *	@brief Macro e messaggi per la gestione degli errori
 */

#define N_ERR(code, msg) \
	if ((code)) {fprintf(stderr, "%s\n", msg); return 1;};

#define E_INVALID_ARG "Errore: argomento non valido."
#define E_FILE_OPEN "Errore nell'apertura del file."
#define E_TILEMAP_LOAD "Errore nel caricamento della tilemap da file."
#define E_LEVEL_LIST_LOAD "Errore nel caricamento della lista dei livelli."
