/**
* \file jeu.c
* \brief code du jeu à proprement parler
* \author Dede
* \version 0.1
* \date 06/04
*
* Fichier destiné à accueillir la partie "jeu" du projet, c'est à dire la gestion des annonces, l'envoi de messages aux joueurs, et la gestion des callbacks.
*
*/


#include "jeu.h"


void klik(SDL_Surface * fond)
{
    TTF_Font *policePerudo = NULL;
    policePerudo = TTF_OpenFont("../../Documents/policePerudo.ttf", ((fond->w)/15));
    SDL_Color couleurNoire = { 0,0,0 } ;
    SDL_Color couleurVerte = { 10,180,30};
    SDL_Surface *R1 = NULL, *R2 = NULL, *R3 = NULL, *R4 = NULL, *R5 = NULL, *R6 = NULL;
    SDL_Rect posR1, posR2, posR3, posR4, posR5, posR6;

    //init dé rouge 1
    if ((R1 = IMG_Load("../../Documents/Des/R1.png"))==NULL)
    {
        fprintf(stderr,"impossible de charger l'image du dé R1");
    }
    posR1.x = ((fond->w)/2)-40;
    posR1.y = ((fond->h)/2)-40;
    SDL_BlitSurface(R1,NULL,fond,&posR1);

    //init dé rouge 2
    if ((R2 = IMG_Load("../../Documents/Des/R2.png"))==NULL)
    {
        fprintf(stderr,"impossible de charger l'image du dé R2");
    }
    posR2.x = ((fond->w)/2)-40;
    posR2.y = ((fond->h)/2)+80;
    SDL_BlitSurface(R2,NULL,fond,&posR2);

    //init dé rouge 3
    if ((R3 = IMG_Load("../../Documents/Des/R3.png"))==NULL)
    {
        fprintf(stderr,"impossible de charger l'image du dé R3");
    }
    posR3.x = ((fond->w)/2)-40;
    posR3.y = ((fond->h)/2)+200;
    SDL_BlitSurface(R3,NULL,fond,&posR3);

    //init dé rouge 4
    if ((R4 = IMG_Load("../../Documents/Des/R4.png"))==NULL)
    {
        fprintf(stderr,"impossible de charger l'image du dé R4");
    }
    posR4.x = ((fond->w)/2)+80;
    posR4.y = ((fond->h)/2)-40;
    SDL_BlitSurface(R4,NULL,fond,&posR4);

    //init dé rouge 5
    if ((R5 = IMG_Load("../../Documents/Des/R5.png"))==NULL)
    {
        fprintf(stderr,"impossible de charger l'image du dé R5");
    }
    posR5.x = ((fond->w)/2)+80;
    posR5.y = ((fond->h)/2)+80;
    SDL_BlitSurface(R5,NULL,fond,&posR5);

    //init dé rouge 6
    if ((R6 = IMG_Load("../../Documents/Des/R6.png"))==NULL)
    {
        fprintf(stderr,"impossible de charger l'image du dé R6");
    }
    posR6.x = ((fond->w)/2)+80;
    posR6.y = ((fond->h)/2)+200;
    SDL_BlitSurface(R6,NULL,fond,&posR6);

    //init du timer
    SDL_Surface *texteTimer = NULL;
    texteTimer = TTF_RenderText_Shaded(policePerudo,"60", couleurNoire, couleurVerte);
    SDL_Rect positionTimer;
    positionTimer.x = ((fond->w) -(texteTimer->w) -100);
    positionTimer.y = 10;

    SDL_BlitSurface(texteTimer, NULL, fond, &positionTimer);
    SDL_Flip(fond);

    long timerDebut = SDL_GetTicks();
    long timerActuel = timerDebut;
    char tempsRestant[2] = "60";
    int indice = 0;
    int score = 0;

    Booleen continuer = VRAI;
    SDL_Event event;
    while (continuer && ((timerActuel-timerDebut)<60000))
    {
       for( indice=0 ; indice < 10 ; indice++)
       {
            FE_PollEvent(&event);
            switch(event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    if (estDans(event,R1,posR1))
                    {
                        score ++;   //on modifie la position des dés
                        posR1.x = random()%((fond->w)-80);
                        posR1.y = random()%((fond->h)-80);

                        posR2.x = random()%((fond->w)-80);
                        posR2.y = random()%((fond->h)-80);

                        posR3.x = random()%((fond->w)-80);
                        posR3.y = random()%((fond->h)-80);

                        posR4.x = random()%((fond->w)-80);
                        posR4.y = random()%((fond->h)-80);

                        posR5.x = random()%((fond->w)-80);
                        posR5.y = random()%((fond->h)-80);

                        posR6.x = random()%((fond->w)-80);
                        posR6.y = random()%((fond->h)-80);

                    }
                }
                break;
                case SDL_QUIT:
                    continuer = FAUX;
                break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                        continuer =FAUX;
                        break;
                        case SDLK_UP:
                        break;
                        case SDLK_DOWN:
                        break;
                    }
                break;
            }
        SDL_Delay(2);
        }
        SDL_FillRect(fond,NULL,VERT);
        posR1.x += (((random()%41)-20));           //on actualise
        posR1.x = (posR1.x)%((fond->w)-80);    //et on renormalise
        posR1.y += (((random()%41)-20));
        posR1.y = (posR1.y)%((fond->h)-80);

        posR2.x += (((random()%41)-20));           //on actualise
        posR2.x = (posR2.x)%((fond->w)-80);    //et on renormalise
        posR2.y += (((random()%41)-20));
        posR2.y = (posR2.y)%((fond->h)-80);

        posR3.x += (((random()%41)-20));           //on actualise
        posR3.x = (posR3.x)%((fond->w)-80);    //et on renormalise
        posR3.y += (((random()%41)-20));
        posR3.y = (posR3.y)%((fond->h)-80);

        posR4.x += (((random()%41)-20));           //on actualise
        posR4.x = (posR4.x)%((fond->w)-80);    //et on renormalise
        posR4.y += (((random()%41)-20));
        posR4.y = (posR4.y)%((fond->h)-80);

        posR5.x += (((random()%41)-20));           //on actualise
        posR5.x = (posR5.x)%((fond->w)-80);    //et on renormalise
        posR5.y += (((random()%41)-20));
        posR5.y = (posR5.y)%((fond->h)-80);

        posR6.x += (((random()%41)-20));           //on actualise
        posR6.x = (posR6.x)%((fond->w)-80);    //et on renormalise
        posR6.y += (((random()%41)-20));
        posR6.y = (posR6.y)%((fond->h)-80);

        SDL_BlitSurface(R1,NULL,fond,&posR1);
        SDL_BlitSurface(R2,NULL,fond,&posR2);
        SDL_BlitSurface(R3,NULL,fond,&posR3);
        SDL_BlitSurface(R4,NULL,fond,&posR4);
        SDL_BlitSurface(R5,NULL,fond,&posR5);
        SDL_BlitSurface(R6,NULL,fond,&posR6);
        SDL_Delay(20);
        timerActuel = SDL_GetTicks();

        tempsRestant[0]=(6-((timerActuel-timerDebut)/10000))+'0'; //les dizaines du timer
        tempsRestant[1]=(10-(((timerActuel-timerDebut)/1000))%10)+'0'; //les unités du timer

        texteTimer = TTF_RenderText_Shaded(policePerudo,tempsRestant, couleurNoire, couleurVerte);
        SDL_BlitSurface(texteTimer, NULL, fond, &positionTimer);
        SDL_Flip(fond);

    }
    fprintf(stdout,"\nscore : %d\n",score);
    SDL_FreeSurface(R1);
    SDL_FreeSurface(R2);
    SDL_FreeSurface(R3);
    SDL_FreeSurface(R4);
    SDL_FreeSurface(R5);
    SDL_FreeSurface(R6);
}
