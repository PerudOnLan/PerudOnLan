/**
* \file perudo.c
* \brief Corps du programme, contient le main
* \author Dede, François
* \version 0.2
* \date 09/04
*
* En gros, ne contient que toutes les initialisations, fermetures, et appel au menu
*
*/
#include "perudo.h"


int main() {

    //on initialise les paramètres au cas où on ne puisse les lire
    int resolution = 0;
    long hauteurFenetre = 600;
    long largeurFenetre = 800;
    // loading de la config perso
    FILE* fconfig = NULL;
    if ((fconfig = fopen("config.ini","r"))==NULL)
    {
        perror("fopen");
        fprintf(stderr,"\nAttention, options personnalisees impossibles a charger ! Verifiez config.ini \n");
    }
    /* Pour l'instant, config.ini va contenir 1 ligne : la résolution
        Si on n'arrive pas a l ouvrir, on panique pas, on prend les params de base
    */
    else
    // on lit les paramètres
    {
        char tampon[TAILLE_MAX] = "";
        rewind(fconfig);
        fgets(tampon,5,fconfig); //on vide "res="
        resolution = strtol((fgets(tampon,2,fconfig)),NULL,10);
        switch(resolution)
            {
                case 0:
                hauteurFenetre = 600;
                largeurFenetre = 800;
                break;
                case 1:
                hauteurFenetre = 900;
                largeurFenetre = 1200;
                break;
                case 2:
                hauteurFenetre = 1060;
                largeurFenetre = 1900;
                break;
                default:
                fprintf(stderr,"\nAttention, options personnalisees impossibles a charger ! Verifiez config.ini \n");
                break;
            }
        printf ("resolution : %d\n", resolution);
        fclose(fconfig);
    }

    //init SDL
    mySDLInitOrQuit(SDL_INIT_EVENTTHREAD | SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE);
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n",
        TTF_GetError());
        exit(EXIT_FAILURE);
    }

    //creation du fond
    SDL_Surface *fond=NULL;
    if ((fond = SDL_SetVideoMode(largeurFenetre,hauteurFenetre,32,SDL_DOUBLEBUF))==NULL)
    {
        fprintf(stderr,"Erreur a l'initialisation de la video : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("PerudOnLan",NULL);
    SDL_FillRect(fond,NULL,VERT);
    SDL_Flip(fond);

    //lancement du menu
    menu(fond);
    //Quitte la SDL
    SDL_FreeSurface(fond);
    TTF_Quit();
    mySDL_Quit();
    return EXIT_SUCCESS;
}

