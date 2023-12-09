#ifndef LOADLVL_H
#define LOADLVL_H

#include "../include/jeu.h"
#include <string.h>

#define MAX_PATH 256

extern int nbCaisse;

/**
 * @brief Charge le niveau dans un tableau à partir d'un fichier txt.
 *
 * @param filename Le nom du fichier du niveau.
 * @param level Le tableau à deux dimensions pour stocker le niveau.
 * @param rows Le nombre de lignes dans le niveau.
 * @param cols Le nombre de colonnes dans le niveau.
 * @return 0 si le chargement a réussi, sinon une valeur différente.
 */
int loadLevel(const int filename, char level[MAX_ROWS][MAX_COLS], int *rows, int *cols);

#endif