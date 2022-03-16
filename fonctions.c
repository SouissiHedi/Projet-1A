#include "fonctions.h"
#include "Perso.h"


SDL_Color GetPixel(SDL_Surface *pSurface,int x,int y){
	SDL_Color color;
	Uint32 col=0;
	char *pPosition=(char*) pSurface->pixels;
	pPosition+=(pSurface->pitch *y);
	pPosition+=(pSurface->format->BytesPerPixel *x);
	memcpy(&col, pPosition ,pSurface->format->BytesPerPixel);
	SDL_GetRGB(col,pSurface->format,&color.r,&color.g,&color.b);
	return (color);
}


int CollitionParfaitePerso(SDL_Surface *MaskSurface,Personne perso){
	int a =0;
	a+=CollitionParfaite(MaskSurface,perso.position.x,perso.position.y+25-20);
	a+=CollitionParfaite(MaskSurface,perso.position.x+25,perso.position.y-18);
	a+=CollitionParfaite(MaskSurface,perso.position.x+25,perso.position.y+50-22);
	a+=CollitionParfaite(MaskSurface,perso.position.x+50,perso.position.y+5);

	a+=CollitionParfaite(MaskSurface,perso.position.x,perso.position.y-18);
	a+=CollitionParfaite(MaskSurface,perso.position.x,perso.position.y+50-22);
	a+=CollitionParfaite(MaskSurface,perso.position.x+50,perso.position.y+50-22);
	a+=CollitionParfaite(MaskSurface,perso.position.x+50,perso.position.y-18);

	a+=CollitionParfaite(MaskSurface,perso.position.x+12,perso.position.y-18);
	a+=CollitionParfaite(MaskSurface,perso.position.x+12,perso.position.y+50-22);
	a+=CollitionParfaite(MaskSurface,perso.position.x+38,perso.position.y+50-22);
	a+=CollitionParfaite(MaskSurface,perso.position.x+38,perso.position.y-18);

	a+=CollitionParfaite(MaskSurface,perso.position.x,perso.position.y-7);
	a+=CollitionParfaite(MaskSurface,perso.position.x,perso.position.y+17);
	a+=CollitionParfaite(MaskSurface,perso.position.x+50,perso.position.y+17);
	a+=CollitionParfaite(MaskSurface,perso.position.x+50,perso.position.y-7);

	return a;
}

int check_turn(Personne *Joueur,int ch_dir,int *dir,SDL_Surface *MaskSurface){
	deplacerPerso(Joueur, 4,ch_dir);
	if (CollitionParfaitePerso(MaskSurface,*Joueur)!=0){
		deplacerPerso(Joueur, 4,opp_dir(ch_dir));
	}
	else{
		(*dir)=ch_dir;
		return 1;
	}
	for(int i=0;i<3;i++){
		deplacerPerso(Joueur, 1,*dir);
		deplacerPerso(Joueur, 1,ch_dir);
		if (CollitionParfaitePerso(MaskSurface,*Joueur)!=0){
			deplacerPerso(Joueur, 1,opp_dir(ch_dir));
		}
		else{
			(*dir)=ch_dir;
			return 1;
		}
	}
	deplacerPerso(Joueur, 3,opp_dir(*dir));
	return 0;
}

int CollitionParfaite(SDL_Surface *MaskSurface,int x,int y){
	SDL_Color c;
	c=GetPixel(MaskSurface,x,y);
	if (c.r== 0 && c.g== 0 && c.b== 0){
		return 1;
	}
	return 0;
}

void add_101(int* N){
	if (*N==1){
		(*N)=-1;
	}
	else{
		(*N)++;
	}
}

int opp_dir(int N){
	if (N==1){
		return 2;
	}
	else if (N==2){
		return 1;
	}
	else if (N==3){
		return 4;
	}
	else {
		return 3;
	}
}

int rand4(){
	return (rand()%4+1);
}

void dim_101(int* N){
	if (*N==-1){
		(*N)=1;
	}
	else{
		(*N)--;
	}
}


void delay(int number_of_seconds){
	int milli_seconds = number_of_seconds,a;
	milli_seconds=milli_seconds*100000;
	clock_t start_time = clock();
	while (clock() < start_time + milli_seconds){
		a++;
	}
}

int check_descri(SDL_Event event,int x,int y,int w,int h){
	if(event.motion.x>=x && event.motion.x<=x+w && event.motion.y>=y && event.motion.y<=y+h){
		return 1;
	}
	else{
		return 0;
	}
}

void load_descri(Image* A,Image* B){
	(*A).img=IMG_Load("fondComDOUZs.png");
	(*B).img=IMG_Load("fondComMIDESs.png");
}

void aff_descri(SDL_Event event,Image A,Image B,SDL_Surface* ecran){
	SDL_Rect pos;
	if(check_descri(event,156,123,474,90)==1){
		pos.x=event.motion.x+10;
		pos.y=event.motion.y+10;
		SDL_BlitSurface(A.img,NULL,ecran,&pos);
	}
	else if(check_descri(event,150,880,480,160)==1){
		pos.x=event.motion.x-10;
		pos.y=event.motion.y-210;
		SDL_BlitSurface(B.img,NULL,ecran,&pos);
	}
}

void loadBouton(Bouton *B){
	(*B).etat=0;
	(*B).app.position.w=400;
	(*B).app.position.h=120;
	(*B).app.position.x=590;
	(*B).N_app.position.w=400;
	(*B).N_app.position.h=120;
	(*B).N_app.position.x=590;
}

void loadBoutonOP(Bouton *B,Bouton *B2){
	(*B).N_app.img=IMG_Load("vol_N.png");
	(*B).app.img=IMG_Load("vol_.png");
	(*B).etat=0;
	(*B).app.position.x=490;
	(*B).app.position.y=290;
	(*B).N_app.position.x=490;
	(*B).N_app.position.y=290;
	(*B).app.position.w=99;
	(*B).app.position.h=96;
	(*B).N_app.position.w=99;
	(*B).N_app.position.h=96;
	(*B2).N_app.img=IMG_Load("vol+N.png");
	(*B2).app.img=IMG_Load("vol+.png");
	(*B2).etat=0;
	(*B2).app.position.x=1050;
	(*B2).app.position.y=290;
	(*B2).N_app.position.x=1050;
	(*B2).N_app.position.y=290;
	(*B2).app.position.w=99;
	(*B2).app.position.h=96;
	(*B2).N_app.position.w=99;
	(*B2).N_app.position.h=96;
}

void load_allB(Bouton* J,Bouton* O,Bouton* Q){
	loadBouton(J);
	loadBouton(O);
	loadBouton(Q);
	
	(*J).N_app.img=IMG_Load("protoJ_Napp.png");
	(*J).app.img=IMG_Load("protoJ_app.png");
	
	(*O).N_app.img=IMG_Load("protoO_Napp.png");
	(*O).app.img=IMG_Load("protoO_app.png");

	(*Q).N_app.img=IMG_Load("protoQ_Napp.png");
	(*Q).app.img=IMG_Load("protoQ_app.png");

	(*J).app.position.y=440;
	(*O).app.position.y=600;
	(*Q).app.position.y=760;
	(*J).N_app.position.y=440;
	(*O).N_app.position.y=600;
	(*Q).N_app.position.y=760;
}

void Init_fond(Image *I){
	(*I).img=IMG_Load("j2.png");
	(*I).position.x=0;
	(*I).position.y=0;
}

void Init_Transi(Image *I,Image *P){
	(*I).img=IMG_Load("transiH.png");
	(*I).position.x=0;
	(*I).position.y=0;
	(*I).zone.x=0;
	(*I).zone.y=660;
	(*I).zone.w=1680;
	(*I).zone.h=0;
	(*P).img=IMG_Load("transiB.png");
	(*P).position.x=0;
	(*P).position.y=987;
}

void Aff_Transi(Image *I,Image *P,SDL_Surface* ecran,Image fond,Image Titre,SDL_Surface * LOGO[50],SDL_Surface *Text,Image zozor,Bouton Jouer,Bouton Option,Bouton Quitter,Image logo,SDL_Rect postxt,Selection select){
	while((*P).position.y>350){
		SDL_BlitSurface(fond.img,NULL,ecran,&fond.position);
		SDL_BlitSurface(Titre.img,NULL,ecran,&Titre.position);
		SDL_BlitSurface(LOGO[0],&logo.zone,ecran,&logo.position);
		SDL_BlitSurface(Text,NULL,ecran, &postxt);
		afficheFond(ecran, zozor,&(zozor.position.y));
		afficher_allBMENU(Jouer,Option,Quitter,ecran,select);
		SDL_BlitSurface((*I).img,&(*I).zone,ecran,&(*I).position);
		SDL_BlitSurface((*P).img,NULL,ecran,&(*P).position);
		(*P).position.y-=15;
		(*I).zone.y-=15;
		(*I).zone.h+=15;
		SDL_Flip(ecran);
	}
	delay(1);
}

void Aff_Transi_F_O(Image *I,Image *U,SDL_Surface* ecran,Image fond,Image Panneau,Image barre,Bouton D,Bouton A,Bouton R,Bouton F,Bouton P,Volume* V,Bouton M){
	while((*U).position.y!=987){
		SDL_BlitSurface(fond.img,NULL,ecran,&fond.position);
		SDL_BlitSurface(Panneau.img,NULL,ecran,&Panneau.position);
		SDL_BlitSurface(barre.img,NULL,ecran,&barre.position);
		afficher_allBO(D,A,ecran);
		afficherV((*V),ecran);
		afficherB(M,ecran);
		afficher_allB(R,F,P,ecran);
		SDL_BlitSurface((*I).img,&(*I).zone,ecran,&(*I).position);
		SDL_BlitSurface((*U).img,NULL,ecran,&(*U).position);
		(*U).position.y+=15;
		(*I).zone.y+=15;
		(*I).zone.h-=15;
		SDL_Flip(ecran);
	}
}

void Aff_Transi_F_J(Image *I,Image *U,SDL_Surface* ecran,Image jouerB, Bouton R,Image panneauJ, Bouton N1, Bouton N2, Bouton N3){
	while((*U).position.y!=987){
		SDL_BlitSurface(jouerB.img,NULL,ecran,&jouerB.position);
		SDL_BlitSurface(panneauJ.img,NULL,ecran,&panneauJ.position);
		afficherB(R,ecran);
		afficher_allB(N1,N2,N3,ecran);
		SDL_BlitSurface((*I).img,&(*I).zone,ecran,&(*I).position);
		SDL_BlitSurface((*U).img,NULL,ecran,&(*U).position);
		(*U).position.y+=15;
		(*I).zone.y+=15;
		(*I).zone.h-=15;
		SDL_Flip(ecran);
	}
}

void load_logoA(SDL_Surface * l[50]){
	char S[2],p[4],t[7];
	int k;
	for(int i=0;i<50;i++){
		k=i+1;
		sprintf(S,"%d",k);
		t[0]=S[0];
		t[1]=S[1];
		if(i>9){
			t[2]='.';
			t[3]='p';
			t[4]='n';
			t[5]='g';
			t[6]='\0';
		}
		else{
			t[1]='.';
			t[2]='p';
			t[3]='n';
			t[4]='g';
			t[5]='\0';
		}
		l[i]=IMG_Load(t);
	}
}

void afficherB(Bouton B,SDL_Surface* ecran){
	if(B.etat==0){
		SDL_BlitSurface(B.N_app.img,NULL,ecran,&B.N_app.position);
	}
	else {
		SDL_BlitSurface(B.app.img,NULL,ecran,&B.app.position);
	}
}

void afficher_allB(Bouton J,Bouton O,Bouton Q,SDL_Surface* ecran){
	afficherB(J,ecran);
	afficherB(O,ecran);
	afficherB(Q,ecran);
}

void afficherBMENU(Bouton B,SDL_Surface* ecran,Selection select,int a){
	if(select.S==0){
		if(B.etat==0){
			SDL_BlitSurface(B.N_app.img,NULL,ecran,&B.N_app.position);
		}
		else {
			SDL_BlitSurface(B.app.img,NULL,ecran,&B.app.position);
		}
	}
	else if (a==0){
		SDL_BlitSurface(B.N_app.img,NULL,ecran,&B.N_app.position);
	}
	else{
		SDL_BlitSurface(B.app.img,NULL,ecran,&B.app.position);
	}
}

void afficher_allBMENU(Bouton J,Bouton O,Bouton Q,SDL_Surface* ecran,Selection select){
	if (select.B==-1){
		afficherBMENU(J,ecran,select,1);
		afficherBMENU(O,ecran,select,0);
		afficherBMENU(Q,ecran,select,0);
	}
	else if (select.B==0){
		afficherBMENU(J,ecran,select,0);
		afficherBMENU(O,ecran,select,1);
		afficherBMENU(Q,ecran,select,0);
	}
	else{
		afficherBMENU(J,ecran,select,0);
		afficherBMENU(O,ecran,select,0);
		afficherBMENU(Q,ecran,select,1);
	}
}

void afficher_allBO(Bouton J,Bouton O,SDL_Surface* ecran){
	afficherB(J,ecran);
	afficherB(O,ecran);
}

int checkB(Bouton* B,SDL_Event event){
	int a=0;
	if(event.motion.x>=(*B).app.position.x && event.motion.x<=(*B).app.position.x+(*B).app.position.w && event.motion.y>=(*B).N_app.position.y && event.motion.y<=(*B).N_app.position.y+(*B).N_app.position.h){
		if ((*B).etat==0){
			a=1;
		}
		(*B).etat=1;
	}
	else{
		(*B).etat=0;
	}
	return a;
}

void flipB(Bouton* B,SDL_Event event,Mix_Chunk *son,int *sb){
	if(event.motion.x>=(*B).app.position.x && event.motion.x<=(*B).app.position.x+(*B).app.position.w && event.motion.y>=(*B).N_app.position.y && event.motion.y<=(*B).N_app.position.y+(*B).N_app.position.h){
		if ((*B).etat==1){
			Mix_VolumeChunk(son,MIX_MAX_VOLUME);
			(*sb)--;
			(*B).etat=0;
		}
		else{
			Mix_VolumeChunk(son,0);
			(*sb)++;
			(*B).etat=1;
		}
	}
}

int checkB_all(Bouton* J,Bouton* O,Bouton* Q,SDL_Event event){
	int ret=0;
	if(checkB(J,event)==1){
		ret++;
	}
	if(checkB(O,event)==1){
		ret++;
	}
	if(checkB(Q,event)==1){
		ret++;
	}
	return ret;
}

void Init_vol(Volume *B){
	(*B).app.img=IMG_Load("BoutonV2.png");
	(*B).app.position.x=636;
	(*B).app.position.y=311;
	(*B).vol=5;
}

void afficherV(Volume B,SDL_Surface* ecran){
	for (int i =0;i<B.vol;i++){
		SDL_BlitSurface(B.app.img,NULL,ecran,&B.app.position);
		B.app.position.x+=75;
	}
}

int checkB_allOP(Bouton* J,Bouton* O,SDL_Event event){
	int ret=0;
	if(checkB(J,event)==1){
		ret++;
	}
	if(checkB(O,event)==1){
		ret++;
	}
	return ret;
}

void mute(Bouton* B,SDL_Event event,Volume* V){
	if(event.motion.x>=(*B).app.position.x && event.motion.x<=(*B).app.position.x+(*B).app.position.w && event.motion.y>=(*B).N_app.position.y && event.motion.y<=(*B).N_app.position.y+(*B).N_app.position.h){
		if ((*B).etat==0){
			(*B).etat=1;
			(*V).vol=0;
		}
		else {
			(*B).etat=0;
			(*V).vol=5;
		}
	}
	else if((*V).vol==0){
		(*B).etat=1;
	}
	else if((*V).vol!=0){
		(*B).etat=0;
	}
}

int plein(Bouton* B,SDL_Event event,Uint32 flags){
	if(event.motion.x>=(*B).app.position.x && event.motion.x<=(*B).app.position.x+(*B).app.position.w && event.motion.y>=(*B).N_app.position.y && event.motion.y<=(*B).N_app.position.y+(*B).N_app.position.h){
		if ((*B).etat==0){
			(*B).etat=1;
			switchFullScreen(flags);
			return 1;
		}
		else {
			(*B).etat=0;
			SDL_SetVideoMode(0, 0, 0, flags^SDL_FULLSCREEN);
			return -1;
		}
	}
	return 0;
}

void option(SDL_Surface* ecran, Image fond,Uint32 flags,Volume* V,int *pl,Image* T_h,Image* T_b,int *sb,Mix_Chunk *son){
	int opt=1;
	SDL_Event evento;
	Bouton A,D,R,F,P,M;
	R.N_app.img=IMG_Load("R_Napp.png");
	R.app.img=IMG_Load("R_app.png");
	loadBouton(&R);
	R.N_app.position.y=710;
	R.app.position.y=710;
	R.N_app.position.x=630;
	R.app.position.x=630;
	F.N_app.img=IMG_Load("unmute1.png");
	F.app.img=IMG_Load("mute2.png");
	loadBouton(&F);
	if ((*V).vol==0){
		F.etat=1;
	}
	F.N_app.position.y=430;
	F.app.position.y=430;
	F.N_app.position.x=620;
	F.app.position.x=620;
	F.N_app.position.h=96;
	F.app.position.h=96;
	F.N_app.position.w=99;
	F.app.position.w=99;
	M.N_app.position.y=430;
	M.N_app.position.x=920;
	M.N_app.position.h=96;
	M.N_app.position.w=99;
	M.app.position.y=430;
	M.app.position.x=920;
	M.app.position.h=96;
	M.app.position.w=99;
	P.N_app.img=IMG_Load("P_E0.png");
	P.app.img=IMG_Load("p_E1.png");
	M.N_app.img=IMG_Load("SB.png");
	M.app.img=IMG_Load("SB_N2.png");
	if ((*pl)==1){
		P.etat=1;
	}
	else{
		P.etat=0;
	}
	if ((*sb)==1){
		M.etat=1;
	}
	else{
		M.etat=0;
	}
	P.N_app.position.y=570;
	P.app.position.y=570;
	P.N_app.position.x=770;
	P.app.position.x=770;
	P.N_app.position.h=96;
	P.app.position.h=96;
	P.N_app.position.w=99;
	P.app.position.w=99;
	
	loadBoutonOP(&D,&A);
	Image barre,Panneau;
	Panneau.img=IMG_Load("F_option2.png");
	barre.img=IMG_Load("barre_vol3.png");
	Panneau.position.x=0;
	Panneau.position.y=0;
	barre.position.x=624;
	barre.position.y=290;
	Aff_Transi_F_O(T_h,T_b,ecran,fond,Panneau,barre,D,A,R,F,P,V,M);
	while(opt){
		int y=0;
		Mix_VolumeMusic(((*V).vol)*(MIX_MAX_VOLUME/5));
		SDL_BlitSurface(fond.img,NULL,ecran,&fond.position);
		SDL_BlitSurface(Panneau.img,NULL,ecran,&Panneau.position);
		SDL_BlitSurface(barre.img,NULL,ecran,&barre.position);
		afficher_allBO(D,A,ecran);
		afficherV((*V),ecran);
		afficher_allB(R,F,P,ecran);
		afficherB(M,ecran);
		SDL_Flip(ecran);
		while(SDL_PollEvent(&evento)){
			switch(evento.type){
				case SDL_QUIT:
					opt=0;
					break;
				case SDL_MOUSEMOTION:
					checkB_allOP(&D,&A,evento);
					checkB(&R,evento);
					break;
				case SDL_MOUSEBUTTONDOWN:
					flipB(&M,evento,son,sb);
					if(D.etat == 1){
						if((*V).vol>0){
							(*V).vol--;
						}
					}
					else if(A.etat == 1){
						if((*V).vol<5){
							(*V).vol++;
						}
					}
					else if(R.etat == 1){
						opt=0;
					}
					mute(&F,evento,V);
					y=plein(&P,evento,flags);
					if (y==1){
						SDL_WarpMouse(800,600);
						(*pl)=1;
					}
					else if (y==-1) {
						SDL_WarpMouse(800,600);
						(*pl)=0;
					}
					break;
				case SDL_KEYDOWN:
					switch(evento.key.keysym.sym){
						case SDLK_ESCAPE:
							opt =0;
							break;
						case SDLK_r:
							opt =0;
							break;
					}
					break;
			}					
		}
	}
}

void jouer(SDL_Surface *ecran, Image jouerB,Image* T_h,Image* T_b){
	int jj=1;
	Bouton R,N1,N2,N3;
	Image panneauJ;
	Image ffff;
	ffff.img=IMG_Load("fond_niv_1.02.png");
	ffff.position.x=0;
	ffff.position.y=20;
	panneauJ.img=IMG_Load("panneauJ2.png");
	panneauJ.position.x=398;
	panneauJ.position.y=20;
	R.N_app.img=IMG_Load("R_Napp.png");
	R.app.img=IMG_Load("R_app.png");
	loadBouton(&R);
	R.N_app.position.y=710;
	R.app.position.y=710;
	R.N_app.position.x=570;
	R.app.position.x=570;



	loadBouton(&N1);
	loadBouton(&N2);
	loadBouton(&N3);
	N1.N_app.img=IMG_Load("bouton_indis.png");
	N2.N_app.img=IMG_Load("bouton_indis.png");
	N3.N_app.img=IMG_Load("bouton_indis.png");
	N1.app.img=IMG_Load("bouton_dis.png");
	N2.app.img=IMG_Load("bouton_dis.png");
	N3.app.img=IMG_Load("bouton_dis.png");
	
	N1.N_app.position.y=150;
	N1.app.position.y=150;
	N1.N_app.position.x=570;
	N1.app.position.x=570;
	
	N2.N_app.position.y=350;
	N2.app.position.y=350;
	N2.N_app.position.x=570;
	N2.app.position.x=570;
	
	N3.N_app.position.y=550;
	N3.app.position.y=550;
	N3.N_app.position.x=570;
	N3.app.position.x=570;


	SDL_Surface *MaskSurface;
	MaskSurface=IMG_Load("fond_niv_1.03.png");
	

	SDL_Event eventj,eventniv;
	Aff_Transi_F_J(T_h,T_b,ecran,jouerB,R,panneauJ,N1,N2,N3);
	while (jj){
		SDL_BlitSurface(jouerB.img,NULL,ecran,&jouerB.position);
		SDL_BlitSurface(panneauJ.img,NULL,ecran,&panneauJ.position);
		afficherB(R,ecran);
		afficher_allB(N1,N2,N3,ecran);
		SDL_Flip(ecran);
		while(SDL_PollEvent(&eventj)){
			switch(eventj.type){
				case SDL_QUIT:
					jj=0;
					break;
				case SDL_MOUSEMOTION:
					checkB(&R,eventj);
					checkB(&N1,eventj);
					checkB(&N2,eventj);
					checkB(&N3,eventj);
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(N1.etat == 1){
						int niv1=1,dir=2,dir2=2,ch_dir=2,change=0;
						Personne Joueur,mechant;
						mechant.position.x=782;
						mechant.position.y=577;
						mechant.position.w=50;
						mechant.position.h=50;
						mechant.initial=IMG_Load("mechan.png");
						mechant.etat=0;
						initPerso(&Joueur);
						while (niv1){
							change=0;
							if (Joueur.position.x==1417 && Joueur.position.y==473 && dir!=2){
								Joueur.position.x=94;
								dir=1;
							}
							else if(Joueur.position.x==94 && Joueur.position.y==473 && dir!=1){
								Joueur.position.x=1417;
								dir=2;
							}
							if (mechant.position.x==1417 && mechant.position.y==473 && dir2!=2){
								mechant.position.x=94;
								dir2=1;
							}
							else if(mechant.position.x==94 && mechant.position.y==473 && dir2!=1){
								mechant.position.x=1417;
								dir2=2;
							}
							SDL_BlitSurface(jouerB.img,NULL,ecran,&jouerB.position);
							SDL_BlitSurface(ffff.img,NULL,ecran,&ffff.position);
							afficherPerso(Joueur,ecran);
							afficherPerso(mechant,ecran);
							SDL_Flip(ecran);
							change=check_turn(&Joueur,ch_dir,&dir,MaskSurface);
							if (change==0){
								deplacerPerso(&Joueur, 4,dir);
								if (CollitionParfaitePerso(MaskSurface,Joueur)!=0){
									deplacerPerso(&Joueur, 4,opp_dir(dir));
								}
							}
							deplacerPerso(&mechant, 4,dir2);
							if (CollitionParfaitePerso(MaskSurface,mechant)!=0){
								deplacerPerso(&mechant, 4,opp_dir(dir2));
								dir2=rand4();
							}
							while(SDL_PollEvent(&eventniv)){
								switch(eventniv.type){
									case SDL_QUIT:
										niv1=0;
										break;
									case SDL_MOUSEMOTION:
/*
										if (CollitionParfaite(MaskSurface,eventniv.motion.x,eventniv.motion.y-20)==1){
											SDL_BlitSurface(MaskSurface,NULL,ecran,&ffff.position);
											SDL_Flip(ecran);
										}
*/
										break;
									case SDL_KEYDOWN:
										switch(eventniv.key.keysym.sym){
											case SDLK_ESCAPE:
												niv1=0;
												break;
											case SDLK_RIGHT:
												ch_dir=1;
												break;
											case SDLK_LEFT:
												ch_dir=2;
												break;
											case SDLK_DOWN:
												ch_dir=3;
												break;
											case SDLK_UP:
												ch_dir=4;
												break;
										}
										break;
								}
							}
						}
/*.position.x,Joueur.position.y-20*/	
					}
					else if(N2.etat == 1){
						
					}
					else if(N3.etat == 1){
						
					}
					else if(R.etat == 1){
						jj=0;
					}
					break;
				case SDL_KEYDOWN:
					switch(eventj.key.keysym.sym){
						case SDLK_ESCAPE:
							jj=0;
							break;
						case SDLK_r:
							jj =0;
							break;
					}
					break;
			}
		}
	}
}

void afficheFond(SDL_Surface *ecran, Image zozor, Sint16* a){
	zozor.position.y += 10;
	if ( (*a) <50){
		(*a) = 50;
	}
	else if(zozor.position.y < 667){
		(*a) += 10;
	}
	else{
		(*a) = 50;
	}
	SDL_BlitSurface(zozor.img, NULL, ecran, &zozor.position);
}

SDL_Surface* switchFullScreen(Uint32 flags){
	SDL_Surface *screen =SDL_GetVideoSurface();
	screen =SDL_SetVideoMode(0, 0, 0, flags);
	if (screen==NULL){
        	fprintf(stderr, "Err / switchFullScreen : changement de format impossible :%s\n",   SDL_GetError());
        	screen=SDL_SetVideoMode(0, 0, 0, flags^SDL_FULLSCREEN);
	}
	return(screen);
}	
	
