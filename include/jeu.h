#ifndef JEU_H
#define JEU_H

#include "../include/jeuUtils.h"
#include "../include/loadLvl.h"

#include <string.h>

extern Player player;
extern TabCaisse tabCaisse;

/**
 * @brief Démarre le jeu avec le niveau spécifié.
 *
 * @param Niveau Le niveau du jeu.
 * @return Un entier représentant le statut de la partie.
 */
int startGame(int Niveau);

#endif
