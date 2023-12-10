#include "../include/jeuUtils.h"


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