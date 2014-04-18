/**
* \file menu.c
* \brief code du menu avant le jeu
* \author Dede
* \version 0.2
* \date 09/04
*
* Menu du jeu, disposant de plusieurs boutons : créer, rejoindre, options
*
*/

#include "menu.h"
/**
* \fn void menu(SDL_Surface * fond)
* \brief Menu du jeu, disposant de plusieurs boutons : créer, rejoindre, options
* \param fond Le fond de la fenêtre d'affichage, où on colle tout ce qu'il ya à afficher
* \author Dede
* \date 16/04
*
* Ce menu comporte 3 boutons visibles : Créer, permettant de se signaler comme hôte potentiel d'un partie; Rejoindre, pour se connecter à un hôte; et Options ,pour gérer divers paramètres du jeu
* De plus, il existe un bouton caché, en bas à gauche; permettant de rentrer des codes
*/
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

    //création des boutons:

    //Bouton créer : Surface

    SDL_Surface *boutonCreer = NULL;

    boutonCreer = SDL_CreateRGBSurface(SDL_HWSURFACE, ((fond->w)/2), ((fond->h)-200)/5, 32, 0, 0, 0, 0);
    SDL_FillRect(boutonCreer,NULL,ROUGE);
    SDL_Rect positionCreer;
    positionCreer.x = (fond->w)/4;
    positionCreer.y = 100;
    SDL_BlitSurface(boutonCreer,NULL,fond,&positionCreer);

    //Bouton créer : Texte

    SDL_Surface *texteCreer = NULL;
    texteCreer = TTF_RenderText_Shaded(policePerudo,"CREER", couleurNoire, couleurRouge);
    positionCreer.x = ((fond->w)/2) -(texteCreer->w / 2);
    positionCreer.y = (100+(((fond->h)-200)/10)) - (texteCreer->h /2);
    SDL_BlitSurface(texteCreer, NULL, fond, &positionCreer);

    //Bouton rejoindre: Surface

    SDL_Surface *boutonRejoindre = NULL;

    boutonRejoindre = SDL_CreateRGBSurface(SDL_HWSURFACE, (fond->w)/2,((fond->h)-200)/5 , 32, 0, 0, 0, 0);
    SDL_FillRect(boutonRejoindre,NULL,ROUGE);
    SDL_Rect positionRejoindre;
    positionRejoindre.x = (fond->w)/4;
    positionRejoindre.y = (100+(2*((fond->h)-200)/5));
    SDL_BlitSurface(boutonRejoindre,NULL,fond,&positionRejoindre);

    //Bouton rejoindre : Texte

    SDL_Surface *texteRejoindre = NULL;
    texteRejoindre = TTF_RenderText_Shaded(policePerudo,"REJOINDRE", couleurNoire, couleurRouge);
    positionRejoindre.x = ((fond->w)/2) -(texteRejoindre->w / 2);
    positionRejoindre.y = ((fond->h)/2) - (texteRejoindre->h /2);
    SDL_BlitSurface(texteRejoindre, NULL, fond, &positionRejoindre);

    //Bouton options : Surface

    SDL_Surface *boutonOptions = NULL;

    boutonOptions = SDL_CreateRGBSurface(SDL_HWSURFACE, ((fond->w)/2), ((fond->h)-200)/5, 32, 0, 0, 0, 0);
    SDL_FillRect(boutonOptions,NULL,ROUGE);
    SDL_Rect positionOptions;
    positionOptions.x = (fond->w)/4;
    positionOptions.y = (100+(4*((fond->h)-200)/5));
    SDL_BlitSurface(boutonOptions,NULL,fond,&positionOptions);

    //Bouton options : Texte

    SDL_Surface *texteOptions = NULL;
    texteOptions = TTF_RenderText_Shaded(policePerudo,"OPTIONS", couleurNoire, couleurRouge);
    positionOptions.x = ((fond->w)/2) -(texteOptions->w / 2);
    positionOptions.y = (100+(9*((fond->h)-200)/10)) - (texteOptions->h /2);
    SDL_BlitSurface(texteOptions, NULL, fond, &positionOptions);

    //Bouton cheats : Surface

    SDL_Surface *boutonCheats = NULL;

    boutonCheats = SDL_CreateRGBSurface(SDL_HWSURFACE,10, 10, 32, 0, 0, 0, 0);
    SDL_FillRect(boutonCheats,NULL,VERT);
    SDL_Rect positionCheats;
    positionCheats.x = 0;
    positionCheats.y = ((fond->h)-10);
    SDL_BlitSurface(boutonCheats,NULL,fond,&positionCheats);

    SDL_Flip(fond);

    //boucle principale

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
                        partie(fond);
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
                    char saisie[11]= "          ";

                    //Définition de la surface de saisie
                    SDL_Surface *champSaisie = NULL;
                    champSaisie = SDL_CreateRGBSurface(SDL_HWSURFACE,320, 50, 32, 0, 0, 0, 0);
                    SDL_FillRect(champSaisie,NULL,VIOLET);
                    SDL_Rect positionChamp;
                    positionChamp.x = 0;
                    positionChamp.y = 0;
                    SDL_BlitSurface(champSaisie,NULL,fond,&positionChamp);
                    SDL_Flip(fond);

                    // on définit la police et les couleurs de police de saisie
                    TTF_Font *policeSaisie = NULL;
                    if ((policeSaisie = TTF_OpenFont("../../Documents/arcadeclassic.ttf", 30))==NULL)
                    {
                        SDL_GetError();
                        fprintf(stdout,"Quelque chose cloche... Avez vous la police arcadeclassic.ttf ?");
                        exit(EXIT_FAILURE);
                    }
                    SDL_Color couleurBlanche = {255,255,255} ;
                    SDL_Color couleurViolette = {150,0,150};
                    printf("Abwa1\n");
                    //maintenant on lance la saisie
                    saisir(champSaisie,positionChamp,VIOLET,policeSaisie,couleurBlanche,couleurViolette,saisie,10,fond);
                    printf("Abwa2\n");
                    //on compare le code entré auw cheats valables
                    if(strcasecmp(saisie,"KLIKLEPACO")==0)
                        {
                        klik(fond);
                        }
                    //On remet le champ de cheat normal
                    printf("Abwa3\n");
                    SDL_FillRect(champSaisie,NULL,VERT);
                    printf("Abwa4\n");
                    SDL_BlitSurface(champSaisie,NULL,fond,&positionChamp);
                    printf("Abwa5\n");
                    SDL_Flip(fond);
                    printf("Abwa6\n");
                    SDL_FreeSurface(champSaisie);
                    printf("Abwa7\n");
                    continuer =FAUX;
                    printf("Abwa8\n");
                    TTF_CloseFont(policeSaisie);
                    }
                }
                break;
            }
    }
//On libère tout ce que l'on a alloué
 printf("Abwa10\n");
 TTF_CloseFont(policePerudo);
 SDL_FreeSurface(boutonCreer);
 SDL_FreeSurface(texteCreer);
 SDL_FreeSurface(boutonRejoindre);
 SDL_FreeSurface(texteRejoindre);
 SDL_FreeSurface(boutonOptions);
 SDL_FreeSurface(texteOptions);
 SDL_FreeSurface(boutonCheats);
 printf("Abwa11\n");
 }
}



