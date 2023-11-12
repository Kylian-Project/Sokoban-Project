#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define MAX_ROWS 100
#define MAX_COLS 100

// Structure de joueur et de caisse
typedef struct {
    int x;
    int y;
} Player, Caisse;

// Tableau de structurea de caisses
typedef struct{
    Caisse caisse[10];
} TabCaisse;

int Jeu = 1;


/**
 * @brief Rafraîchit l'affichage du tableau de jeu.
 *
 * @param level Tableau représentant le niveau.
 * @param rows Nombre de lignes dans le tableau.
 * @param cols Nombre de colonnes dans le tableau.
 * @param player Structure représentant le joueur.
 * @param tabCaisse Tableau de structures représentant les caisses.
 */
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

/**
 * @brief Vérifie si la caisse peut être déplacée à la nouvelle position.
 *
 * @param level Tableau représentant le niveau.
 * @param rows Nombre de lignes dans le tableau.
 * @param cols Nombre de colonnes dans le tableau.
 * @param player Structure représentant le joueur.
 * @param tabCaisse Tableau de structures représentant les caisses.
 * @param x Nouvelle position en colonne.
 * @param y Nouvelle position en ligne.
 * @return 1 si la caisse peut être déplacée, 0 sinon.
 */
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


/**
 * @brief Fonction principale du jeu.
 *
 * @return 0 si le jeu s'est terminé normalement.
 */
int main() {
    FILE* fp = fopen("lvl/level.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    // Lis le fichier et le met dans un tableau a 2 dimensions
    char level[MAX_ROWS][MAX_COLS];
    int rows = 0, cols = 0;
    while (fscanf(fp, "%c", &level[rows][cols]) != EOF) {
        if (level[rows][cols] == '\n') {
            cols = 0;
            rows++;
        } else {
            cols++;
        }
    }

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