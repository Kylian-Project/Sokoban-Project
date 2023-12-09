#ifndef MENU_H
#define MENU_H

#include "../include/jeu.h"

#include <ncurses.h>
#include <string.h>
#include <dirent.h>  // Pour la gestion des répertoires
#include <stdlib.h>  // Pour la fonction malloc()


/**
 * @brief Récupère la liste des niveaux à partir d'un répertoire spécifié.
 * 
 * @param levelDir Le chemin du répertoire contenant les niveaux.
 * @param levelList Un pointeur vers un tableau de chaînes de caractères qui contiendra la liste des niveaux.
 * @param numLevels Un pointeur vers un entier qui contiendra le nombre de niveaux récupérés.
 */
void getLevelList(char *levelDir, char ***levelList, int *numLevels);

/**
 * @brief Affiche le menu de sélection du niveau.
 *
 * @param levelDir Le répertoire contenant les niveaux.
 */
void showLevelMenu(char *levelDir);

/**
 * @brief Menu de fin de niveau.
 *
 * Cette fonction est appelée pour afficher le menu quand le niveau est terminer.
 *
 * @param terminal_height La hauteur du terminal.
 * @param terminal_width La largeur du terminal.
 * @param level Le niveau en cours pour pouvoir le recommencer.
 */
void finNiveau(int terminal_height, int terminal_width, int level);

/**
 * @brief Affiche le menu permettant de choisir sont niveau / lancer la partie.
 * 
 * @return Le choix de l'utilisateur.
 */
int menu();

#endif