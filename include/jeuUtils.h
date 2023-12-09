#ifndef JEU_UTILS_H
#define JEU_UTILS_H

#include <stdio.h>
#include <ncurses.h>

#define MAX_ROWS 100
#define MAX_COLS 100
#define MAX_CAISSES 100


extern int Jeu;  // Déclaration de la variable Jeu
extern int Niveau;  // Déclaration de la variable Niveau

/**
 * @brief Structure représentant le joueur et les caisses.
 *
 */
typedef struct {
    int x; /**< Coordonnée x du point. */
    int y; /**< Coordonnée y du point. */
} Player, Caisse;

/**
 * @brief Structure représentant le tableau de caisses.
 *
 */
typedef struct {
    Caisse caisse[MAX_CAISSES]; /**< Tableau de caisses. */
} TabCaisse;


/**
 * @brief Rafraîchit l'affichage du tableau de jeu.
 *
 * @param level Tableau représentant le niveau.
 * @param rows Nombre de lignes dans le tableau.
 * @param cols Nombre de colonnes dans le tableau.
 * @param player Structure représentant le joueur.
 * @param tabCaisse Tableau de structures représentant les caisses.
 */
void RefreshTab(char level[MAX_ROWS][MAX_COLS], int rows, int cols, Player player, TabCaisse tabCaisse);

/**
 * @brief Vérifie si la caisse peut être déplacée à la nouvelle position.
 *
 * @param level Tableau représentant le niveau.
 * @param tabCaisse Tableau de structures représentant les caisses.
 * @param x Nouvelle position en colonne.
 * @param y Nouvelle position en ligne.
 * @return 1 si la caisse peut être déplacée, 0 sinon.
 */
int peutBougerCaisse(char level[MAX_ROWS][MAX_COLS], TabCaisse tabCaisse, int x, int y);

#endif