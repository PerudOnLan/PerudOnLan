/**
* \file menu.c
* \brief code du menu avant le jeu
* \author Dede
* \version 0.1
* \date 06/04
*
* Fichier destiné à accueillir la partie "jeu" du projet, c'est à dire la gestion des annonces, l'envoi de messages aux joueurs, et la gestion des callbacks.
*
*/

#include "menu.h"

void menu(SDL_Surface * fond)
{
Booleen quitter = FAUX;
while(!quitter)
{
    Booleen continuer = VRAI;
    SDL_Event event;
    //chargement de la paco-police
    TTF_Font *policePerudo = NULL;
    policePerudo = TTF_OpenFont("../../Documents/policePerudo.ttf", ((fond->w)/15));
    SDL_Color couleurNoire = { 0,0,0 } ;
    SDL_Color couleurRouge = { 200,0,0};

    SDL_Surface *boutonCreer = NULL;

    boutonCreer = SDL_CreateRGBSurface(SDL_HWSURFACE, ((fond->w)/2), ((fond->h)-200)/5, 32, 0, 0, 0, 0);
    SDL_FillRect(boutonCreer,NULL,ROUGE);
    SDL_Rect positionCreer;
    positionCreer.x = (fond->w)/4;
    positionCreer.y = 100;
    SDL_BlitSurface(boutonCreer,NULL,fond,&positionCreer);

    SDL_Surface *texteCreer = NULL;
    texteCreer = TTF_RenderText_Shaded(policePerudo,"CREER", couleurNoire, couleurRouge);
    positionCreer.x = ((fond->w)/2) -(texteCreer->w / 2);
    positionCreer.y = (100+(((fond->h)-200)/10)) - (texteCreer->h /2);
    SDL_BlitSurface(texteCreer, NULL, fond, &positionCreer);

    SDL_Surface *boutonRejoindre = NULL;

    boutonRejoindre = SDL_CreateRGBSurface(SDL_HWSURFACE, (fond->w)/2,((fond->h)-200)/5 , 32, 0, 0, 0, 0);
    SDL_FillRect(boutonRejoindre,NULL,ROUGE);
    SDL_Rect positionRejoindre;
    positionRejoindre.x = (fond->w)/4;
    positionRejoindre.y = (100+(2*((fond->h)-200)/5));
    SDL_BlitSurface(boutonRejoindre,NULL,fond,&positionRejoindre);

    SDL_Surface *texteRejoindre = NULL;
    texteRejoindre = TTF_RenderText_Shaded(policePerudo,"REJOINDRE", couleurNoire, couleurRouge);
    positionRejoindre.x = ((fond->w)/2) -(texteRejoindre->w / 2);
    positionRejoindre.y = ((fond->h)/2) - (texteRejoindre->h /2);
    SDL_BlitSurface(texteRejoindre, NULL, fond, &positionRejoindre);

    SDL_Surface *boutonOptions = NULL;

    boutonOptions = SDL_CreateRGBSurface(SDL_HWSURFACE, ((fond->w)/2), ((fond->h)-200)/5, 32, 0, 0, 0, 0);
    SDL_FillRect(boutonOptions,NULL,ROUGE);
    SDL_Rect positionOptions;
    positionOptions.x = (fond->w)/4;
    positionOptions.y = (100+(4*((fond->h)-200)/5));
    SDL_BlitSurface(boutonOptions,NULL,fond,&positionOptions);

    SDL_Surface *texteOptions = NULL;
    texteOptions = TTF_RenderText_Shaded(policePerudo,"OPTIONS", couleurNoire, couleurRouge);
    positionOptions.x = ((fond->w)/2) -(texteOptions->w / 2);
    positionOptions.y = (100+(9*((fond->h)-200)/10)) - (texteOptions->h /2);
    SDL_BlitSurface(texteOptions, NULL, fond, &positionOptions);

    SDL_Surface *boutonCheats = NULL;

    boutonCheats = SDL_CreateRGBSurface(SDL_HWSURFACE,100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(boutonCheats,NULL,BLEU);
    SDL_Rect positionCheats;
    positionCheats.x = 0;
    positionCheats.y = ((fond->h)-100);
    SDL_BlitSurface(boutonCheats,NULL,fond,&positionCheats);

    SDL_Flip(fond);

    while (continuer)
    {
        FE_WaitEvent(&event);
        char cheat[10];
        switch(event.type)
            {
                case SDL_QUIT:
                    continuer = FAUX ;
                    quitter = VRAI;
                break;
                case SDL_MOUSEBUTTONDOWN:
                if(event.button.button==SDL_BUTTON_LEFT)
                {

                    if (estDans(event,boutonCreer,positionCreer))
                    {
                     //début du jeu
                        jeu(fond);
                        continuer = FAUX;

                    }
                    if (estDans(event,boutonRejoindre,positionRejoindre))
                    {
                        continuer = FAUX;
                        quitter = VRAI;

                    }
                    if  (estDans(event,boutonOptions,positionOptions))
                    {
                        continuer=FAUX;
                        quitter = VRAI;
                    }
                     if  (estDans(event,boutonCheats,positionCheats))
                    {
                    char saisie[11];
                    SDL_Surface *champSaisie = NULL;

                    champSaisie = SDL_CreateRGBSurface(SDL_HWSURFACE,300, 50, 32, 0, 0, 0, 0);
                    SDL_FillRect(champSaisie,NULL,VIOLET);
                    SDL_Rect positionChamp;
                    positionChamp.x = 220;
                    positionChamp.y = 0;
                    SDL_BlitSurface(champSaisie,NULL,fond,&positionChamp);
                    SDL_Flip(fond);
                    saisir(champSaisie,positionChamp, saisie,10,fond);
                    fprintf(stdout,"%s",saisie);

                    }
                }
                break;
            }
    }
 SDL_FreeSurface(boutonCreer);
 SDL_FreeSurface(texteCreer);
 SDL_FreeSurface(boutonRejoindre);
 SDL_FreeSurface(texteRejoindre);
 SDL_FreeSurface(boutonOptions);
 SDL_FreeSurface(texteOptions);
 TTF_CloseFont(policePerudo);
 }
}






