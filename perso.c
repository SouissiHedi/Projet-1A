#include "Perso.h"


void initPerso(Personne *p){
	(*p).position.x=722;
	(*p).position.y=577;
	(*p).position.w=50;
	(*p).position.h=50;
	(*p).initial=IMG_Load("personiv.png");
	(*p).etat=0;
}

void afficherPerso(Personne p, SDL_Surface * screen){
	SDL_BlitSurface(p.initial,NULL,screen,&p.position);
}

void deplacerPerso (Personne *p, int dt, int dir){
	switch(dir){
		case 1:
			(*p).position.x+=dt;
			break;
		case 2:
			(*p).position.x-=dt;
			break;
		case 3:
			(*p).position.y+=dt;
			break;
		case 4:
			(*p).position.y-=dt;
			break;
	}
}

void animerPerso (Personne* p){
	
}

void saut (Personne* p){
	
}

