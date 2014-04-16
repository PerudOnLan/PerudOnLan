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
        largeurFenetre = strtol((fgets(tampon,6,fconfig)),NULL,10); // on convertit jusqu'à 4 chiffres en un long
        printf("%s", tampon);
        fgets(tampon,9,fconfig); //on vide "hauteur="
        hauteurFenetre = strtol((fgets(tampon,6,fconfig)),NULL,10); // on convertit jusqu'à 4 chiffres en un long
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
    TTF_Font *policePerudo = NULL;
    policePerudo = TTF_OpenFont("../../Documents/policePerudo.ttf", ((fond->w)/15));
    SDL_Color couleurNoire = { 0,0,0 } ;
    SDL_Color couleurRouge = { 200,0,0};

       // on définit la police et les couleurs de police de saisie
    TTF_Font *policeSaisie = NULL;
    policeSaisie = TTF_OpenFont("../../Documents/arcadeclassic.ttf", 30);
    SDL_Color couleurBlanche = {255,255,255} ;
    SDL_Color couleurViolette = {150,0,150};

    SDL_Rect positionCreer;
    positionCreer.x = 0;
    positionCreer.y = 0;

    SDL_Surface *texteTest = NULL;
    texteTest = TTF_RenderText_Shaded(policePerudo,"TEST", couleurNoire, couleurRouge);
    positionCreer.x = 300;
    positionCreer.y = 200;
    SDL_BlitSurface(texteTest, NULL, fond, &positionCreer);

        SDL_Surface *texteEssai = NULL;
    texteEssai = TTF_RenderText_Shaded(policeSaisie,"ESSAI", couleurBlanche, couleurViolette);
    positionCreer.x = 300;
    positionCreer.y = 280;
    SDL_BlitSurface(texteEssai, NULL, fond, &positionCreer);

    SDL_Flip(fond);
        //Quitte la SDL
    SDL_FreeSurface(texteTest);
    SDL_FreeSurface(texteEssai);
    TTF_CloseFont(policePerudo);
    TTF_CloseFont(policeSaisie);
    SDL_FreeSurface(fond);
    TTF_Quit();
    mySDL_Quit();
    return EXIT_SUCCESS;
}



