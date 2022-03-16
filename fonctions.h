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
#include "Perso.h"


typedef struct {
	SDL_Rect position;
	SDL_Rect zone;
	SDL_Surface *img;
}Image;

typedef struct {
	Image N_app;
	Image app;
	int etat;
}Bouton;

typedef struct {
	Image app;
	int vol;
}Volume;

typedef struct {
	int S,B;
}Selection;

/*
typedef struct {
	SDL_Rect position;
	TTF_Font *font;
	SDL_Surface * surfaceTexte;
	SDL_Color textColor;
	char texte [50];
}Text;
*/

void add_101(int* N);
int opp_dir(int N);
int rand4();
void dim_101(int* N);
void delay(int number_of_seconds);
int check_turn(Personne *Joueur,int ch_dir,int *dir,SDL_Surface *MaskSurface);
void flipB(Bouton* B,SDL_Event event,Mix_Chunk *son,int *sb);
int check_descri(SDL_Event event,int x,int y,int w,int h);
void load_descri(Image* A,Image* B);
void aff_descri(SDL_Event event,Image A,Image B,SDL_Surface* ecran);
void loadBouton(Bouton *B);
void load_allB(Bouton* J,Bouton* O,Bouton* Q);
void Init_fond(Image *I);
void Init_vol(Volume *B);
void Init_Transi(Image *I,Image *P);
void Aff_Transi(Image *I,Image *P,SDL_Surface* ecran,Image fond,Image Titre,SDL_Surface * LOGO[50],SDL_Surface *Text,Image zozor,Bouton Jouer,Bouton Option,Bouton Quitter,Image logo,SDL_Rect postxt,Selection select);
void Aff_Transi_F_O(Image *I,Image *U,SDL_Surface* ecran,Image fond,Image Panneau,Image barre,Bouton D,Bouton A,Bouton R,Bouton F,Bouton P,Volume* V,Bouton M);
void Aff_Transi_F_J(Image *I,Image *U,SDL_Surface* ecran,Image jouerB, Bouton R,Image panneauJ, Bouton N1, Bouton N2, Bouton N3);
void afficherB(Bouton B,SDL_Surface* ecran);
void afficherBMENU(Bouton B,SDL_Surface* ecran,Selection select,int a);
void mute(Bouton* F,SDL_Event event,Volume* V);
void load_logoA(SDL_Surface * l[50]);
void afficher_allB(Bouton J,Bouton O,Bouton Q,SDL_Surface* ecran);
void afficher_allBMENU(Bouton J,Bouton O,Bouton Q,SDL_Surface* ecran,Selection select);
void afficher_allBO(Bouton J,Bouton O,SDL_Surface* ecran);
void afficherV(Volume B,SDL_Surface* ecran);
void loadBoutonOP(Bouton *B,Bouton *B2);
int checkB(Bouton* B,SDL_Event event);
int checkB_all(Bouton* J,Bouton* O,Bouton* Q,SDL_Event event);
int checkB_allOP(Bouton* J,Bouton* O,SDL_Event event);
int plein(Bouton* B,SDL_Event event,Uint32 flags);
void option(SDL_Surface* ecran, Image fond,Uint32 flags,Volume* V,int *pl,Image* T_h,Image* T_b,int *sb,Mix_Chunk *son);
void jouer(SDL_Surface *ecran, Image jouerB,Image* T_h,Image* T_b);
void afficheFond(SDL_Surface *ecran, Image zozor,Sint16* a);
SDL_Surface* switchFullScreen(Uint32 flags);

SDL_Color GetPixel(SDL_Surface *pSurface,int x,int y);
int CollitionParfaite(SDL_Surface *MaskSurface,int x,int y);
int CollitionParfaitePerso(SDL_Surface *MaskSurface,Personne perso);


#endif
