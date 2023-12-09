/**
 * @file menu.c
 * @brief Fichier contenant les fonctions pour le menu.
 */

#include "../include/menu.h"

// Fonction pour obtenir la liste des fichiers dans un répertoire
void getLevelList(char *levelDir, char ***levelList, int *numLevels) {
    DIR *dir;
    struct dirent *ent;
    int i = 0;

    if ((dir = opendir(levelDir)) != NULL) {
        // Compter le nombre de fichiers dans le répertoire
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) {
                i++;
            }
        }

        // Allouer de la mémoire pour le tableau de chaînes
        *levelList = (char **)malloc(i * sizeof(char *));
        rewinddir(dir);

        // Remplir le tableau avec les noms de fichiers
        i = 0;
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) {
                (*levelList)[i++] = strdup(ent->d_name);
            }
        }

        *numLevels = i;  // Mettre à jour le nombre total de niveaux
        closedir(dir);
    }
}


void showLevelMenu(char *levelDir) {
    int level_highlight = 0;
    int level_choice;
    int scroll_offset = 0;

    char **levelList = NULL;
    int numLevels = 0;
    getLevelList(levelDir, &levelList, &numLevels);

    // Obtenir la taille du terminal
    int terminal_height, terminal_width;
    getmaxyx(stdscr, terminal_height, terminal_width);

    // Définir les dimensions de la sous-fenêtre
    int starty = (terminal_height - numLevels - 3) / 2;  // Centrer verticalement
    int startx = (terminal_width - 30) / 2;  // Centrer horizontalement
    int height = numLevels+3, width = 30;

    // Créer une sous-fenêtre pour le sous-menu
    WINDOW *level_menu_win = newwin(height, width, starty, startx);
    keypad(level_menu_win, TRUE);  // Activer le mode clavier

    while (1) {
        // Effacer la sous-fenêtre
        wclear(level_menu_win);

        // Dessiner le cadre autour de la sous-fenêtre
        box(level_menu_win, 0, 0);
        mvwprintw(level_menu_win, 0, (width - strlen("NIVEAUX")) / 2, "NIVEAUX");

        // Mettre en surbrillance le bouton "Retour" si sélectionné
        if (level_highlight == 0) {
            wattron(level_menu_win, A_REVERSE);
            mvwprintw(level_menu_win, 1, (width - strlen("Retour")) / 2, "Retour");
            wattroff(level_menu_win, A_REVERSE);
        } else {
            mvwprintw(level_menu_win, 1, (width - strlen("Retour")) / 2, "Retour");
        }

        // Afficher la liste des niveaux dans la sous-fenêtre avec défilement
        for (int i = scroll_offset; i < scroll_offset + 6 && i < numLevels; i++) {
            if (i + 1 == level_highlight) {
                wattron(level_menu_win, A_REVERSE);  // Mettre en surbrillance le niveau sélectionné
            }
            mvwprintw(level_menu_win, i - scroll_offset + 2, (width - strlen(levelList[i])) / 2, "%s", levelList[i]);
            wattroff(level_menu_win, A_REVERSE);
        }

        // Rafraîchir la sous-fenêtre du sous-menu
        wrefresh(level_menu_win);

        // Obtenir la touche de l'utilisateur pour le sous-menu
        level_choice = wgetch(level_menu_win);

        switch (level_choice) {
            case KEY_UP:
                if (level_highlight > 0) {
                    level_highlight--;
                    if (level_highlight < scroll_offset+1) {
                        if (scroll_offset > 0){
                            scroll_offset--;
                        }
                    }
                }
                break;
            case KEY_DOWN:
                if (level_highlight < numLevels) {
                    level_highlight++;
                    if (level_highlight > scroll_offset + 6) {
                        scroll_offset++;
                    }
                }
                break;
            case 10:  // Touche "Entrée"
                // Traiter la sélection dans le sous-menu
                if (level_highlight == 0) {
                    
                    wclear(level_menu_win);
                    wrefresh(level_menu_win);

                    // Retour au menu principal
                    delwin(level_menu_win);

                    // Libérer la mémoire allouée pour la liste des niveaux
                    for (int i = 0; i < numLevels; i++) {
                        free(levelList[i]);
                    }
                    free(levelList);

                    return;
                } else if (level_highlight > 0) {
                    // les niveaux sont du genre 1.txt, 2.txt, 3.txt, etc.
                    // transformer la cbaine de caractère en entier
                    int level = atoi(levelList[level_highlight - 1]);
                    startGame(level);
                }
                break;
        }
    }
}


void finNiveau(int terminal_height, int terminal_width, int level) {
    // Menu de fin de partie ncurses
    WINDOW *end_menu_win = newwin(5, 30, (terminal_height - 4) / 2, (terminal_width - 30) / 2);
    keypad(end_menu_win, TRUE);  // Activer le mode clavier

    char *end_choices[] = {
        "Suivant",
        "Recommencer",
        "Quitter"
    };

    int end_n_choices = sizeof(end_choices) / sizeof(end_choices[0]);
    int end_highlight = 0;
    int end_choice;

    while (1) {
        // Effacer la sous-fenêtre
        wclear(end_menu_win);

        // Dessiner le cadre autour de la sous-fenêtre
        box(end_menu_win, 0, 0);
        mvwprintw(end_menu_win, 0, (30 - strlen("FIN DE NIVEAU")) / 2, "FIN DE NIVEAU");

        // Afficher le menu dans la sous-fenêtre
        for (int i = 0; i < end_n_choices; i++) {
            if (i == end_highlight) {
                wattron(end_menu_win, A_REVERSE);  // Mettre en surbrillance l'option sélectionnée
            }
            mvwprintw(end_menu_win, i + 1, (30 - strlen(end_choices[i])) / 2, "%s", end_choices[i]);
            wattroff(end_menu_win, A_REVERSE);
        }

        // Rafraîchir la sous-fenêtre
        wrefresh(end_menu_win);

        // Obtenir la touche de l'utilisateur pour la sous-fenêtre
        end_choice = wgetch(end_menu_win);

        switch (end_choice) {
            case KEY_UP:
                end_highlight = (end_highlight - 1 + end_n_choices) % (end_n_choices);
                break;
            case KEY_DOWN:
                end_highlight = (end_highlight + 1) % (end_n_choices);
                break;
            case 10:  // Touche "Entrée"
                if (end_highlight == 0) {
                    // Continuer le jeu
                    delwin(end_menu_win);
                    return;
                }
                else if (end_highlight == 1) {
                    // Recommencer le niveau
                    startGame(level);
                } else if (end_highlight == 2) {
                    // Quitter le jeu
                    endwin();  // Fermer NCurses
                    exit(0);
                }
                break;
        }
    }
}

int menu() {
    // Initialiser NCurses
    initscr();
    cbreak();  // Désactiver la mise en mémoire tampon de ligne
    noecho();  // Désactiver l'affichage des caractères saisis
    curs_set(0);  // Masquer le curseur

    // Obtenir la taille du terminal
    int terminal_height, terminal_width;
    getmaxyx(stdscr, terminal_height, terminal_width);

    // Créer un tableau de chaînes pour les options du menu
    char *choices[] = {
        "Lancer le jeu",
        "Selectionner un niveau",
        "Quitter le jeu"
    };

    int n_choices = sizeof(choices) / sizeof(choices[0]);
    int highlight = 0;
    int choice;

    // Définir les dimensions de la sous-fenêtre principale
    int starty = (terminal_height - n_choices - 2) / 2;  // Centrer verticalement
    int startx = (terminal_width - 30) / 2;  // Centrer horizontalement
    int height = n_choices + 2, width = 30; // Ajuster la taille de la sous-fenêtre principale selon vos besoins

    // Créer une sous-fenêtre principale
    WINDOW *menu_win = newwin(height, width, starty, startx);
    keypad(menu_win, TRUE);  // Activer le mode clavier

    while (1) {
        // Effacer la sous-fenêtre principale
        wclear(menu_win);

        // Dessiner le cadre autour de la sous-fenêtre principale
        box(menu_win, 0, 0);
        mvwprintw(menu_win, 0, (width - strlen("MENU")) / 2, "MENU");

        // Afficher le menu dans la sous-fenêtre principale
        for (int i = 0; i < n_choices; i++) {
            if (i == highlight) {
                wattron(menu_win, A_REVERSE);  // Mettre en surbrillance l'option sélectionnée
            }
            mvwprintw(menu_win, i + 1, (width - strlen(choices[i])) / 2, "%s",choices[i]);
            wattroff(menu_win, A_REVERSE);
        }

        // Rafraîchir la sous-fenêtre principale
        wrefresh(menu_win);

        // Obtenir la touche de l'utilisateur pour la sous-fenêtre principale
        choice = wgetch(menu_win);

        switch (choice) {
            case KEY_UP:
                highlight = (highlight - 1 + n_choices) % n_choices;
                break;
            case KEY_DOWN:
                highlight = (highlight + 1) % n_choices;
                break;
            case 10:  // Touche "Entrée"
                // Traiter la sélection dans la sous-fenêtre principale
                if (highlight == 0) {
                    // Lancer les niveaux 1 à 4
                    for (int i = 1; i <= 4; i++) {
                        startGame(i);
                        
                        if (i == 4) {
                            break;
                            // fin des niveaux 1 à 4, retour au menu principal
                        } else {
                            // Afficher le menu de fin de partie
                            finNiveau(terminal_height, terminal_width, i+1);
                        }
                    }
                } else if (highlight == 1) {
                    // Sélectionner un niveau
                    // Appeler la fonction pour afficher le sous-menu des niveaux
                    clear();
                    refresh();

                    showLevelMenu("../data/lvl");
                } else if (highlight == 2) {
                    // Quitter le jeu
                    endwin();  // Fermer NCurses
                    return 0;
                }
                break;
        }
    }

    // Fermer la sous-fenêtre principale
    delwin(menu_win);

    // Fermer NCurses
    endwin();

    return 0;
}
