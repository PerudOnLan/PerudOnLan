#include "testSDL.h"

int main(int argc, char *argv[])
{
    //initialisation de la randomisation
    int seed = time(NULL);
    srandom(seed);
    //Config de base
    long hauteurFenetre = 480;
    long largeurFenetre = 640;
    // loading de la config perso
    FILE* fconfig = NULL;
    if ((fconfig = fopen("config.ini","r+"))==NULL)
    {
        perror("fopen");
        fprintf(stdout,"\nAttention, options personnalisées impossibles à charger ! Vérifiez config.ini \n");
    }
    /* Pour l'instant, config.ini va contenir 2 lignes : largeur=valeur
                                                         hauteur=valeur
        Si on n'arrive pas à louvrir, on panique pas, on prend les params de base
    */
    else
    {
        char tampon[10] = "";
        rewind(fconfig);
        fgets(tampon,9,fconfig); //on vide "largeur="
        printf("%s \n", tampon);
        largeurFenetre = strtol((fgets(tampon,6,fconfig)),NULL,10); // on convertit jusqu'à 4 chiffres en un long
        printf("%s \n", tampon);
        fgets(tampon,9,fconfig); //on vide "hauteur="
        printf("%s \n", tampon);
        hauteurFenetre = strtol((fgets(tampon,6,fconfig)),NULL,10); // on convertit jusqu'à 4 chiffres en un long
        printf("%s \n", tampon);
        fclose(fconfig);
        printf("largeur =%ld hauteur=%ld\n", largeurFenetre,hauteurFenetre);
    }

    //init SDL
    mySDLInitOrQuit(SDL_INIT_EVENTTHREAD | SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE);
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n",
        TTF_GetError());
        exit(EXIT_FAILURE);
    }
    //création du fond
    SDL_Surface *fond=NULL;
    if ((fond = SDL_SetVideoMode(largeurFenetre,hauteurFenetre,32,SDL_DOUBLEBUF))==NULL)
    {
        fprintf(stderr,"Erreur à l'initialisation de la video : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("PerudOnLan",NULL);
    SDL_FillRect(fond,NULL,VERT);
    SDL_Flip(fond);
    //lancement du menu
    menu(&fond);
        //Quitte la SDL
    SDL_FreeSurface(fond);
    TTF_Quit();
    mySDL_Quit();
    return EXIT_SUCCESS;
}



