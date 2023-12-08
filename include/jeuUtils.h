#ifndef JEU_UTILS_H
#define JEU_UTILS_H

#include <stdio.h>
#include <ncurses.h>

#define MAX_ROWS 100
#define MAX_COLS 100

extern int Jeu;  // Déclaration de la variable Jeu

typedef struct {
    int x;
    int y;
} Player, Caisse;

typedef struct {
    Caisse caisse[10];
} TabCaisse;

void RefreshTab(char level[MAX_ROWS][MAX_COLS], int rows, int cols, Player player, TabCaisse tabCaisse);
int peutBougerCaisse(char level[MAX_ROWS][MAX_COLS], int rows, int cols, Player player, TabCaisse tabCaisse, int x, int y);

#endif