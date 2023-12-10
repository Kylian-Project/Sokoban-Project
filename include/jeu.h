#ifndef JEU_H
#define JEU_H

#include "../include/jeuUtils.h"
#include "../include/loadLvl.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define TILE_SIZE 64

void drawImage(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y);
void calculerDimensions(int rows, int cols, int tile_size, int *screen_width, int *screen_height);
void RefreshTab(char level[MAX_ROWS][MAX_COLS], int nb_rows, int nb_cols, Player player, TabCaisse tabCaisse, SDL_Renderer* renderer, SDL_Texture* murTexture, SDL_Texture* autreTexture, SDL_Texture* joueurTexture, SDL_Texture* caisseTexture, SDL_Texture* cibleTexture);

int startGame();

#endif
