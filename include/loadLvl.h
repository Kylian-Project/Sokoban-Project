#ifndef LOADLVL_H
#define LOADLVL_H

#include "../include/jeu.h"
#include <string.h>

#define MAX_PATH 256

extern Player player;
extern TabCaisse tabCaisse;

int loadLevel(const int filename, char level[MAX_ROWS][MAX_COLS], int *rows, int *cols);

#endif