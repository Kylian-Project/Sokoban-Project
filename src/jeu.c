/**
 * @file jeu.c
 * @brief Fichier contenant les fonctions pour le jeu.
 */

#include "../include/jeu.h"

int Jeu;
Player player;
TabCaisse tabCaisse;


int startGame(int Niveau) {
    
    Jeu = 1;

    char level[MAX_ROWS][MAX_COLS] = {0};
    int rows, cols = 0;

    if (loadLevel(Niveau, level, &rows, &cols) != 0) {
        // Gestion de l'erreur, quitter le jeu
        return 1;
    }

    cols = strlen(level[0]); // On récupère le nombre de colonnes de la première ligne

    initscr();
    noecho(); // désative print de chaque entrée
    curs_set(0); // désactive curseur du cmd

    // Affiche le tableau au debut du jeu
    RefreshTab(level, rows, cols, player, tabCaisse);

    while (Jeu) {
        int ch = getch();
        int isCaisse = 0;
        switch (ch) {
            case 'z':
                // Si la case au-dessus du joueur n'est pas un mur
                if (level[player.y - 1][player.x] != '#') {
                    // Vérifie si une caisse se trouve sur la case suivante
                    for (int i = 0; i < nbCaisse; i++) {
                        if (tabCaisse.caisse[i].x == player.x && tabCaisse.caisse[i].y == player.y - 1) {
                            // Si la caisse peut être déplacée, la déplace
                            if (peutBougerCaisse(level, tabCaisse, player.x, player.y - 2)) {
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
                    for (int i = 0; i < nbCaisse; i++) {
                        if (tabCaisse.caisse[i].x == player.x - 1 && tabCaisse.caisse[i].y == player.y) {
                            // Si la caisse peut être déplacée, la déplace
                            if (peutBougerCaisse(level, tabCaisse, player.x - 2, player.y)) {
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
                    for (int i = 0; i < nbCaisse; i++) {
                        if (tabCaisse.caisse[i].x == player.x && tabCaisse.caisse[i].y == player.y + 1) {
                            // Si la caisse peut être déplacée, la déplace
                            if (peutBougerCaisse(level, tabCaisse, player.x, player.y + 2)) {
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
                    for (int i = 0; i < nbCaisse; i++) {
                        if (tabCaisse.caisse[i].x == player.x + 1 && tabCaisse.caisse[i].y == player.y) {
                            // Si la caisse peut être déplacée, la déplace
                            if (peutBougerCaisse(level, tabCaisse, player.x + 2, player.y)) {
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
            case 'c':
                // Quitte le jeu
                Jeu = 0;
                break;
            default:
                break;
        }
        // Met à jour l'affichage du tableau de jeu
        RefreshTab(level, rows, cols, player, tabCaisse);
    }

    clear();
    refresh();
    
    endwin();
    return 0;
}