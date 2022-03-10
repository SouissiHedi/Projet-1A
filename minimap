#ifndef Header_H
#define Header_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

typedef struct {
  SDL_Surface * img;
  SDL_Rect pos;
  SDL_Surface * img_pers;
  SDL_Rect pos_pers;
}minimap;

initminimap( minimap * m);
MAJMinimap(SDL_Rect posJoueur , minimap * m, SDL_Rect camera, int redimensionnement);
afficherminimap (minimap m, SDL_Surface * screen);
void sauvegarder( int score, char nomjoueur[], char nomfichier[]);
void meilleur( char nomfichier[], int *score, char nomjoueur[]);

#endif
