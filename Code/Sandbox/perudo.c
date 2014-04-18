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
    long hauteurFenetre = 480;
    long largeurFenetre = 640;
    // loading de la config perso
    FILE* fconfig = NULL;
    if ((fconfig = fopen("config.ini","r+"))==NULL)
    {
        perror("fopen");
        fprintf(stdout,"\nAttention, options personnalisees impossibles a charger ! Verifiez config.ini \n");
    }
    /* Pour l'instant, config.ini va contenir 2 lignes : largeur=valeur
                                                         hauteur=valeur
        Si on n'arrive pas a l ouvrir, on panique pas, on prend les params de base
    */
    else
    // on lit les paramètres
    {
        char tampon[10] = "";
        rewind(fconfig);
        fgets(tampon,9,fconfig); //on vide "largeur="
        largeurFenetre = strtol((fgets(tampon,6,fconfig)),NULL,10); // on convertit jusqu'a 4 chiffres en un long
        printf("%s", tampon);
        fgets(tampon,9,fconfig); //on vide "hauteur="
        hauteurFenetre = strtol((fgets(tampon,6,fconfig)),NULL,10); // on convertit jusqu'a 4 chiffres en un long
        printf("%s", tampon);
        printf("largeur =%ld hauteur=%ld\n", largeurFenetre,hauteurFenetre);
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

