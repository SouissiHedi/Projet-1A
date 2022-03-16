#include "Perso.h"
#include "fonctions.h"

int main()
{
	srand(time(0));
	SDL_Surface *ecran=NULL , *Text=NULL ;
	SDL_Surface *LOGO[50];
	load_logoA(LOGO);
	Image fond,zozor,jouerB,Titre,logo,T_h,T_b,Douz,Mides;
	Init_Transi(&T_h,&T_b);
	load_descri(&Douz,&Mides);
	Titre.position.x=500;
	Titre.position.y=0;
	SDL_Event event;
	int continuer=1,count=0,div=1,pl=0,sb=0;
	Selection select;
	select.S=0;
	select.B=-1;
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
	Mix_Chunk *son;
	Mix_Music *music;
	TTF_Init();
	TTF_Font *police=NULL;
	SDL_Color couleurNoire={25,25,25};
	police = TTF_OpenFont("REVISTA.ttf",128);
	TTF_SetFontStyle(police,TTF_STYLE_ITALIC);
	Text = TTF_RenderText_Blended(police,"Menu",couleurNoire);
	SDL_Rect postxt;
	postxt.x=600;
	postxt.y=280;
	logo.position.x=1410;
	logo.position.y=0;
	logo.zone.x=1;
	logo.zone.y=1;
	logo.zone.w=128;
	logo.zone.h=134;
	logo.img=IMG_Load("logo0a.gif");
	Titre.img=IMG_Load("nomJ.png");
	jouerB.img=IMG_Load("fondJ.png");
	jouerB.position.x=0;
	jouerB.position.y=0;
	Bouton Jouer, Option, Quitter;
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024);
	son= Mix_LoadWAV( "bambou.wav" );
	ecran = SDL_SetVideoMode (1580,987,32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	Uint32 flags =(ecran->flags^SDL_FULLSCREEN);
	music=Mix_LoadMUS("music.mp3");
    	Mix_PlayMusic(music, -1);

	SDL_WM_SetIcon(IMG_Load("logo00.png"), NULL);
	SDL_WM_SetCaption("Stranded", NULL);


	if (!ecran){
		printf("Unable to set screen : %s",SDL_GetError());
		return 1;
	}
	Init_fond(&fond);
	load_allB(&Jouer,&Option,&Quitter);
	zozor.img = IMG_Load("perso.png");
	zozor.position.x=0;
	zozor.position.y=0;
	
	Volume V;
	Init_vol(&V);
	
	while (continuer){
		SDL_BlitSurface(fond.img,NULL,ecran,&fond.position);
		SDL_BlitSurface(Titre.img,NULL,ecran,&Titre.position);
/*
		SDL_BlitSurface(logo.img,NULL,ecran,&logo.position);
*/
		SDL_BlitSurface(LOGO[count],&logo.zone,ecran,&logo.position);
		if(div%6==0){
			if (count==49){
				count = 0;
			}
			else{
				count++;
			}
		}
		else if(div==600){
			div=1;
		}
		div++;
		SDL_BlitSurface(Text,NULL,ecran, &postxt);
		afficheFond(ecran, zozor,&(zozor.position.y));
		afficher_allBMENU(Jouer,Option,Quitter,ecran,select);
		aff_descri(event,Douz,Mides,ecran);
		SDL_Flip(ecran);
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					continuer =0;
					break;
				case SDL_MOUSEMOTION:
					select.S=0;
					select.B=-1;
					if(checkB_all(&Jouer,&Option,&Quitter,event)!=0){
						Mix_PlayChannel(-1,son,0);
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(Jouer.etat == 1){
						Aff_Transi(&T_h,&T_b,ecran,fond,Titre,LOGO,Text,zozor,Jouer,Option,Quitter,logo, postxt,select);
						jouer(ecran,jouerB,&T_h,&T_b);
					}
					else if(Option.etat == 1){
						Aff_Transi(&T_h,&T_b,ecran,fond,Titre,LOGO,Text,zozor,Jouer,Option,Quitter,logo, postxt,select);
						option(ecran,fond,flags,&V,&pl,&T_h,&T_b,&sb,son);
					}
					else if(Quitter.etat == 1){
						continuer =0;
					}
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_j:
							Aff_Transi(&T_h,&T_b,ecran,fond,Titre,LOGO,Text,zozor,Jouer,Option,Quitter,logo, postxt,select);
							jouer(ecran,jouerB,&T_h,&T_b);
							break;
						case SDLK_o:
							Aff_Transi(&T_h,&T_b,ecran,fond,Titre,LOGO,Text,zozor,Jouer,Option,Quitter,logo, postxt,select);
							option(ecran,fond,flags,&V,&pl,&T_h,&T_b,&sb,son);
							break;
						case SDLK_q:
						case SDLK_ESCAPE:
						case SDLK_e:
							continuer =0;
							break;
						case SDLK_DOWN:
							select.S=1;
							add_101(&select.B);
							break;
						case SDLK_UP:
							select.S=1;
							dim_101(&select.B);
							break;
						case SDLK_SPACE:
						case SDLK_KP_ENTER:
						case SDLK_RETURN:
							if(select.S=1){
								switch(select.B){
									case -1:
										Aff_Transi(&T_h,&T_b,ecran,fond,Titre,LOGO,Text,zozor,Jouer,Option,Quitter,logo, postxt,select);
										jouer(ecran,jouerB,&T_h,&T_b);
										break;
									case 0:
										Aff_Transi(&T_h,&T_b,ecran,fond,Titre,LOGO,Text,zozor,Jouer,Option,Quitter,logo, postxt,select);
										option(ecran,fond,flags,&V,&pl,&T_h,&T_b,&sb,son);
										break;
									case 1:
										continuer =0;
										break;
								}
							}
							break;

					}
					break;
			}					
		}
	}
	Mix_FreeChunk(son); 
}
