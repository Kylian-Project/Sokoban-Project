#include "../include/jeu.h"

int quit = 0;
int Niveau = 1;

Player player;
TabCaisse tabCaisse;

void drawImage(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y) {
    SDL_Rect destRect = { x, y, TILE_SIZE, TILE_SIZE };
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}

// Fonction pour calculer SCREEN_WIDTH et SCREEN_HEIGHT
void calculerDimensions(int rows, int cols, int tile_size, int *screen_width, int *screen_height) {
    *screen_width = cols * tile_size;
    *screen_height = rows * tile_size;
}


void RefreshTab(char level[MAX_ROWS][MAX_COLS], int nb_rows, int nb_cols, Player player, TabCaisse tabCaisse, SDL_Renderer* renderer, SDL_Texture* murTexture, SDL_Texture* autreTexture, SDL_Texture* joueurTexture, SDL_Texture* caisseTexture, SDL_Texture* cibleTexture) {
    int isCaisse = 0;

    int nbCible = 0;
    int nbCibleValide = 0;
    for (int i = 0; i <= nb_rows; i++) {
        for (int j = 0; j < nb_cols; j++) {
            drawImage(renderer, autreTexture, j * TILE_SIZE, i * TILE_SIZE);
            isCaisse = 0;
            for (int k = 0; k < 3; k++){
                if (i == tabCaisse.caisse[k].y && j == tabCaisse.caisse[k].x) {
                    drawImage(renderer, caisseTexture, j * TILE_SIZE, i * TILE_SIZE);
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
                    drawImage(renderer, cibleTexture, j * TILE_SIZE, i * TILE_SIZE); // Affichage de la cible
                }
                if (i == player.y && j == player.x) {
                    drawImage(renderer, joueurTexture, j * TILE_SIZE, i * TILE_SIZE);
                }
                else if (level[i][j] == '#') {
                    drawImage(renderer, murTexture, j * TILE_SIZE, i * TILE_SIZE);
                }
                else if (level[i][j] == ' ') {
                   drawImage(renderer, autreTexture, j * TILE_SIZE, i * TILE_SIZE);
                }
            }
        }
    }
    if (nbCible == nbCibleValide){
        printf("Vous avez gagné, fin du jeu !\n");
        quit = 1;
    }
}

int startGame() {
    
    char level[MAX_ROWS][MAX_COLS];
    int rows, cols;

    if (loadLevel(Niveau, level, &rows, &cols) != 0) {
        // Gestion de l'erreur, quitter le jeu
        return 1;
    }

    int nb_cols = strlen(level[0]); // On récupère le nombre de colonnes de la première ligne
    nb_cols --; // On enlève le \n

    int nb_rows = rows;

    // Calculer SCREEN_WIDTH et SCREEN_HEIGHT
    int screen_width, screen_height;
    calculerDimensions(nb_rows, nb_cols, TILE_SIZE, &screen_width, &screen_height);


    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }

    // Création de la fenêtre
    SDL_Window* window = SDL_CreateWindow("level à deux dimensions", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, 0);
    if (window == NULL) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Création du renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Erreur lors de la création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Chargement des textures
    SDL_Texture* murTexture = IMG_LoadTexture(renderer, "../data/img/mur.png");
    SDL_Texture* autreTexture = IMG_LoadTexture(renderer, "../data/img/sol.png");
    SDL_Texture* joueurTexture = IMG_LoadTexture(renderer, "../data/img/joueur.png");
    SDL_Texture* caisseTexture = IMG_LoadTexture(renderer, "../data/img/caisse.png");
    SDL_Texture* cibleTexture = IMG_LoadTexture(renderer, "../data/img/cible.png");
    if (murTexture == NULL || autreTexture == NULL || joueurTexture == NULL || caisseTexture == NULL || cibleTexture == NULL) {
        printf("Erreur lors du chargement des textures : %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    RefreshTab(level, nb_rows, nb_cols, player, tabCaisse, renderer, murTexture, autreTexture, joueurTexture, caisseTexture, cibleTexture);

    // Rafraîchissement de l'écran
    SDL_RenderPresent(renderer);

    // Boucle principale
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            else if (event.type == SDL_KEYDOWN) {
                SDL_Keycode keycode = event.key.keysym.sym;
                int isCaisse = 0;
                switch (keycode) {
                    case SDLK_z:
                        // Si la case au-dessus du joueur n'est pas un mur
                        if (level[player.y - 1][player.x] != '#') {
                            // Vérifie si une caisse se trouve sur la case suivante
                            for (int i = 0; i < 3; i++) {
                                if (tabCaisse.caisse[i].x == player.x && tabCaisse.caisse[i].y == player.y - 1) {
                                    // Si la caisse peut être déplacée, la déplace
                                    if (peutBougerCaisse(level, rows, cols, player, tabCaisse, player.x, player.y - 2)) {
                                        tabCaisse.caisse[i].y--;
                                    }
                                    else {
                                        isCaisse = 1;
                                    }
                                }
                            }
                            // Déplace le joueur
                            if (isCaisse == 0) {
                                player.y--;
                            }
                        }
                        break;
                    case SDLK_q:
                        // Si la case à gauche du joueur n'est pas un mur
                        if (level[player.y][player.x - 1] != '#') {
                            // Vérifie si une caisse se trouve sur la case suivante
                            for (int i = 0; i < 3; i++) {
                                if (tabCaisse.caisse[i].x == player.x - 1 && tabCaisse.caisse[i].y == player.y) {
                                    // Si la caisse peut être déplacée, la déplace
                                    if (peutBougerCaisse(level, rows, cols, player, tabCaisse, player.x - 2, player.y)) {
                                        tabCaisse.caisse[i].x--;
                                    }
                                    else {
                                        isCaisse = 1;
                                    }
                                }
                            }
                            // Déplace le joueur
                            if (isCaisse == 0) {
                                player.x--;
                            }
                        }
                        break;
                    case SDLK_s:
                        // Si la case en-dessous du joueur n'est pas un mur
                        if (level[player.y + 1][player.x] != '#') {
                            // Vérifie si une caisse se trouve sur la case suivante
                            for (int i = 0; i < 3; i++) {
                                if (tabCaisse.caisse[i].x == player.x && tabCaisse.caisse[i].y == player.y + 1) {
                                    // Si la caisse peut être déplacée, la déplace
                                    if (peutBougerCaisse(level, rows, cols, player, tabCaisse, player.x, player.y + 2)) {
                                        tabCaisse.caisse[i].y++;
                                    }
                                    else {
                                        isCaisse = 1;
                                    }
                                }
                            }
                            // Déplace le joueur
                            if (isCaisse == 0) {
                                player.y++;
                            }
                        }
                        break;
                    case SDLK_d:
                        // Si la case à droite du joueur n'est pas un mur
                        if (level[player.y][player.x + 1] != '#') {
                            // Vérifie si une caisse se trouve sur la case suivante
                            for (int i = 0; i < 3; i++) {
                                if (tabCaisse.caisse[i].x == player.x + 1 && tabCaisse.caisse[i].y == player.y) {
                                    // Si la caisse peut être déplacée, la déplace
                                    if (peutBougerCaisse(level, rows, cols, player, tabCaisse, player.x + 2, player.y)) {
                                        tabCaisse.caisse[i].x++;
                                    }
                                    else {
                                        isCaisse = 1;
                                    }
                                }
                            }
                            // Déplace le joueur
                            if (isCaisse == 0) {
                                player.x++;
                            }
                        }
                        break;
                    default:
                        break;
                }
            }
        }

        RefreshTab(level, nb_rows, nb_cols, player, tabCaisse, renderer, murTexture, autreTexture, joueurTexture, caisseTexture, cibleTexture);

        // Rafraîchissement de l'écran
        SDL_RenderPresent(renderer);
    }

    // Libération des ressources
    SDL_DestroyTexture(murTexture);
    SDL_DestroyTexture(autreTexture);
    SDL_DestroyTexture(joueurTexture);
    SDL_DestroyTexture(caisseTexture);
    SDL_DestroyTexture(cibleTexture);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
