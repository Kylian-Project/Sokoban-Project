#include "../include/jeu.h"

#include <string.h>
#include <stdio.h>
#include <ncurses.h>

#define MAX_ROWS 100
#define MAX_COLS 100

typedef struct {
    int x;
    int y;
} Player, Caisse;

typedef struct {
    Caisse caisse[10];
} TabCaisse;

int Jeu = 1;


void RefreshTab(char level[MAX_ROWS][MAX_COLS], int rows, int cols, Player player, TabCaisse tabCaisse){
    clear();
    int isCaisse = 0;

    int nbCible = 0;
    int nbCibleValide = 0;
    for (int i = 0; i <= rows; i++) {
        for (int j = 0; j < cols; j++) {
            isCaisse = 0;
            for (int k = 0; k < 3; k++){
                if (i == tabCaisse.caisse[k].y && j == tabCaisse.caisse[k].x) {
                    printw("C");
                    isCaisse = 1;
                }
            }
            if (isCaisse == 0){
                if (level[i][j] == 'o'){
                    nbCible++;
                    for (int k = 0; k < 3; k++) { // Vérifie si une caisse est à la même position
                        if (tabCaisse.caisse[k].x == j && tabCaisse.caisse[k].y == i) {
                            nbCibleValide++;
                            break;
                        }
                    }
                }
                if (i == player.y && j == player.x) {
                    printw("P");
                }
                else {
                    printw("%c", level[i][j]);
                }
            }
        }
    }
    refresh();
    if (nbCible == nbCibleValide){
        printf("Vous avez gagne !");
        Jeu = 0;
    }
}

int peutBougerCaisse(char level[MAX_ROWS][MAX_COLS], int rows, int cols, Player player, TabCaisse tabCaisse, int x, int y){
    // Vérifie si la caisse peut bouger
    if (level[y][x] == '#' || level[y][x] == 'C'){
        return 0;
    }
    for (int i = 0; i < 3; i++){
        if (tabCaisse.caisse[i].x == x && tabCaisse.caisse[i].y == y){
            return 0;
        }
    }
    return 1;
}

int startGame() {
    FILE* fp = fopen("../data/lvl/1.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    // Lis le fichier et le met dans un tableau à 2 dimensions
    char level[MAX_ROWS][MAX_COLS];
    int rows = 0, cols = 0;
    int c;  // Variable pour stocker le caractère lu

    while ((c = fgetc(fp)) != EOF && rows < MAX_ROWS - 1 && cols < MAX_COLS - 1) {
        if (c == '\n') {
            level[rows][cols] = '\n';  // Ajoute passage de ligne au tableau
            cols = 0;
            rows++;
        } else {
            level[rows][cols] = (char)c;
            cols++;
        }
    }

    // Assurez-vous que la dernière ligne est correctement terminée par un caractère nul
    if (cols > 0 && rows < MAX_ROWS - 1) {
        level[rows][cols] = '\0';
    }

    // Ferme le fichier
    fclose(fp);

    cols = strlen(level[0]); // On récupère le nombre de colonnes de la première ligne
    Player player = {1, 1};
    TabCaisse tabCaisse = {{ {7, 2}, {5, 5}, {14, 4} }};

    initscr();
    noecho(); // désative print de chaque entrée
    curs_set(0); // désactive curseur du cmd

    // Affiche le tableau
    RefreshTab(level, rows, cols, player, tabCaisse);

    while (Jeu) {
        int ch = getch();
        int isCaisse = 0;
        switch (ch) {
            case 'z':
                // Si la case au-dessus du joueur n'est pas un mur
                if (level[player.y - 1][player.x] != '#') {
                    // Vérifie si une caisse se trouve sur la case suivante
                    for (int i = 0; i < 3; i++) {
                        if (tabCaisse.caisse[i].x == player.x && tabCaisse.caisse[i].y == player.y - 1) {
                            // Si la caisse peut être déplacée, la déplace
                            if (peutBougerCaisse(level, rows, cols, player, tabCaisse, player.x, player.y - 2)) {
                                tabCaisse.caisse[i].y--;
                            }
                            else{
                                isCaisse = 1;
                            }
                        }
                    }
                    // Déplace le joueur
                    if (isCaisse == 0){
                        player.y--;
                    }
                }
                break;
            case 'q':
                // Si la case à gauche du joueur n'est pas un mur
                if (level[player.y][player.x - 1] != '#') {
                    // Vérifie si une caisse se trouve sur la case suivante
                    for (int i = 0; i < 3; i++) {
                        if (tabCaisse.caisse[i].x == player.x - 1 && tabCaisse.caisse[i].y == player.y) {
                            // Si la caisse peut être déplacée, la déplace
                            if (peutBougerCaisse(level, rows, cols, player, tabCaisse, player.x - 2, player.y)) {
                                tabCaisse.caisse[i].x--;
                            }
                            else{
                                isCaisse = 1;
                            }
                        }
                    }
                    // Déplace le joueur
                    if (isCaisse == 0){
                        player.x--;
                    }
                }
                break;
            case 's':
                // Si la case en-dessous du joueur n'est pas un mur
                if (level[player.y + 1][player.x] != '#') {
                    // Vérifie si une caisse se trouve sur la case suivante
                    for (int i = 0; i < 3; i++) {
                        if (tabCaisse.caisse[i].x == player.x && tabCaisse.caisse[i].y == player.y + 1) {
                            // Si la caisse peut être déplacée, la déplace
                            if (peutBougerCaisse(level, rows, cols, player, tabCaisse, player.x, player.y + 2)) {
                                tabCaisse.caisse[i].y++;
                            }
                            else{
                                isCaisse = 1;
                            }
                        }
                    }
                    // Déplace le joueur
                    if (isCaisse == 0){
                        player.y++;
                    }
                }
                break;
            case 'd':
                // Si la case à droite du joueur n'est pas un mur
                if (level[player.y][player.x + 1] != '#') {
                    // Vérifie si une caisse se trouve sur la case suivante
                    for (int i = 0; i < 3; i++) {
                        if (tabCaisse.caisse[i].x == player.x + 1 && tabCaisse.caisse[i].y == player.y) {
                            // Si la caisse peut être déplacée, la déplace
                            if (peutBougerCaisse(level, rows, cols, player, tabCaisse, player.x + 2, player.y)) {
                                tabCaisse.caisse[i].x++;
                            }
                            else{
                                isCaisse = 1;
                            }
                        }
                    }
                    // Déplace le joueur
                    if (isCaisse == 0){
                        player.x++;
                    }
                }
                break;
            default:
                break;
        }
        // Met à jour l'affichage du tableau de jeu
        RefreshTab(level, rows, cols, player, tabCaisse);
    }
    
    endwin();
    return 0;
}
