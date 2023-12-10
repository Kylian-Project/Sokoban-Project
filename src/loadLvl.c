#include "loadLvl.h"

/**
 * @brief Charge le niveau à partir d'un fichier.
 *
 * @param filename Le nom du fichier du niveau.
 * @param level Le tableau à deux dimensions pour stocker le niveau.
 * @param rows Le nombre de lignes dans le niveau.
 * @param cols Le nombre de colonnes dans le niveau.
 * @return 0 si le chargement a réussi, sinon une valeur différente.
 */
int loadLevel(const int filename, char level[MAX_ROWS][MAX_COLS], int *rows, int *cols) {

    // Convertir l'entier en une chaîne de caractères
    char filenameStr[MAX_PATH];
    sprintf(filenameStr, "%d", filename);
    
    // Construire le chemin du fichier
    char path[MAX_PATH];
    strcpy(path, "../data/lvl/");
    strcat(path, filenameStr);
    strcat(path, ".txt");

    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    // Lis le fichier et le met dans un tableau à 2 dimensions
    int c;
    *rows = 0;
    *cols = 0;

    int nbCaisse = 0;

    while ((c = fgetc(fp)) != EOF && *rows < MAX_ROWS - 1 && *cols < MAX_COLS - 1) {
        // enregistrer l'emplacement du joueur
        if (c == 'P') {
            level[*rows][*cols] = ' ';
            player.x = *cols;
            player.y = *rows;
            (*cols)++;
        }
        else if (c == 'C') {
            level[*rows][*cols] = ' ';
            tabCaisse.caisse[nbCaisse].x = *cols;
            tabCaisse.caisse[nbCaisse].y = *rows;
            nbCaisse++;
            (*cols)++;
        } 
        else{
            if (c == '\n') {
                level[*rows][*cols] = '\n';  // Ajoute un passage de ligne au tableau
                *cols = 0;
                (*rows)++;
            } else {
                level[*rows][*cols] = (char)c;
                (*cols)++;
            }
        }
    }

    // Assurez-vous que la dernière ligne est correctement terminée par un caractère nul
    if (*cols > 0 && *rows < MAX_ROWS - 1) {
        level[*rows][*cols] = '\0';
    }

    // Ferme le fichier
    fclose(fp);

    return 0;
}