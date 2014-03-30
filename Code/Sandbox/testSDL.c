#include "testSDL.h"

int main(int argc, char *argv[])
{
    //initialisation de la randomisation
    int seed = time(NULL);
    srandom(seed);
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
    if ((fond = SDL_SetVideoMode(640,480,32,SDL_DOUBLEBUF))==NULL)
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


void jeu(SDL_Rect * pos, SDL_Surface ** img, SDL_Surface ** fond)
{
    long timerDebut = SDL_GetTicks();
    long timerActuel = timerDebut;
    int indice = 0;
    int score = 0;
    int continuer = 1;
    int modifW = 0;
    int modifH = 0;
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
                    if ((((event.button.x) - (pos->x))>0)&&(((event.button.x) - (pos->x))<80)&&(((event.button.y) - (pos->y))>0)&&(((event.button.y) - (pos->y)<80)))
                    {
                        score ++;
                        pos->x = random()%560;
                        pos->y = random()%400;
                    }
                }
                break;
                case SDL_QUIT:
                    continuer = 0;
                break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_UP:
                        modifW = 12;
                        modifH = 9 ;
                        break;
                        case SDLK_DOWN:
                        modifW = -12;
                        modifH = -9;
                        break;
                    }
                    if (((*fond )= SDL_SetVideoMode((((*fond)->w)+modifW),(((*fond)->h)+modifH),32,SDL_DOUBLEBUF))==NULL)
                    {
                    fprintf(stderr,"Erreur au redimensionnement de la video : %s", SDL_GetError());
                    exit(EXIT_FAILURE);
                    }
                    printf("%d %d", modifW, modifH);
                    SDL_FillRect(*fond,NULL,pVERT);
                    pos->x += (((random()%21)-10));
                    pos->x = (pos->x)%(((*fond)->w)-80);
                    pos->y += (((random()%21)-10));
                    pos->y = (pos->y)%(((*fond)->h)-80);
                    SDL_BlitSurface(*img,NULL,*fond,pos);
                    SDL_Flip(*fond);
                break;
            }
        SDL_Delay(2);
        }
        SDL_FillRect(*fond,NULL,pVERT);
        pos->x += (((random()%21)-10));
        pos->x = (pos->x)%(((*fond)->w)-80);
        pos->y += (((random()%21)-10));
        pos->y = (pos->y)%(((*fond)->h)-80);

        SDL_BlitSurface(*img,NULL,*fond,pos);
        SDL_Flip(*fond);
        SDL_Delay(20);
        timerActuel = SDL_GetTicks();
        fprintf(stdout,"%ld\n",(timerActuel-timerDebut));
    }
    fprintf(stdout,"\nscore : %d\n",score);
  }


void menu(SDL_Surface ** fond)
{
    int continuer = 1;
    SDL_Event event;
    //chargement de la paco-police
    TTF_Font *policePerudo = NULL;
    policePerudo = TTF_OpenFont("../../Documents/policePerudo.ttf", 36);
    SDL_Color couleurNoire = { 0,0,0 } ;
    SDL_Color couleurRouge = { 200,0,0};

    SDL_Surface *boutonCreer = NULL;

    boutonCreer = SDL_CreateRGBSurface(SDL_HWSURFACE, 320, 56, 32, 0, 0, 0, 0);
    SDL_FillRect(boutonCreer,NULL,pROUGE);
    SDL_Rect positionCreer;
    positionCreer.x = 160;
    positionCreer.y = 100;
    printf ("init 1 OK");
    SDL_BlitSurface(boutonCreer,NULL,*fond,&positionCreer);

    SDL_Surface *texteCreer = NULL;
    texteCreer = TTF_RenderText_Shaded(policePerudo,"CREER", couleurNoire, couleurRouge);
    positionCreer.x = 320 -(texteCreer->w / 2);
    positionCreer.y = 128 - (texteCreer->h /2);
    SDL_BlitSurface(texteCreer, NULL, *fond, &positionCreer);

    SDL_Surface *boutonRejoindre = NULL;

    boutonRejoindre = SDL_CreateRGBSurface(SDL_HWSURFACE, 320, 56, 32, 0, 0, 0, 0);
    SDL_FillRect(boutonRejoindre,NULL,pROUGE);
    SDL_Rect positionRejoindre;
    positionRejoindre.x = 160;
    positionRejoindre.y = 212;
    printf ("init 2 OK");
    SDL_BlitSurface(boutonRejoindre,NULL,*fond,&positionRejoindre);

    SDL_Surface *texteRejoindre = NULL;
    texteRejoindre = TTF_RenderText_Shaded(policePerudo,"REJOINDRE", couleurNoire, couleurRouge);
    positionRejoindre.x = 320 -(texteRejoindre->w / 2);
    positionRejoindre.y = 240 - (texteRejoindre->h /2);
    SDL_BlitSurface(texteRejoindre, NULL, *fond, &positionRejoindre);

    SDL_Surface *boutonOptions = NULL;

    boutonOptions = SDL_CreateRGBSurface(SDL_HWSURFACE, 320, 56, 32, 0, 0, 0, 0);
    SDL_FillRect(boutonOptions,NULL,pROUGE);
    SDL_Rect positionOptions;
    positionOptions.x = 160;
    positionOptions.y = 324;
    printf ("init 2 OK");
    SDL_BlitSurface(boutonOptions,NULL,*fond,&positionOptions);

    SDL_Surface *texteOptions = NULL;
    texteOptions = TTF_RenderText_Shaded(policePerudo,"OPTIONS", couleurNoire, couleurRouge);
    positionOptions.x = 320 -(texteOptions->w / 2);
    positionOptions.y = 352 - (texteOptions->h /2);
    SDL_BlitSurface(texteOptions, NULL, *fond, &positionOptions);

    SDL_Flip(*fond);

    while (continuer)
    {
        FE_PollEvent(&event);
        switch(event.type)
            {
                case SDL_QUIT:
                    continuer = 0;
                break;
                case SDL_MOUSEBUTTONDOWN:
                if(event.button.button==SDL_BUTTON_LEFT)
                {

                    if (((event.button.x) > 160)&&((event.button.x) <480)
                        &&(((event.button.y) > 100)&&((event.button.y)<156)))
                    {
                     //début du jeu
                        SDL_Surface *R1 = NULL;
                        SDL_Rect posR1;
                        if ((R1 = IMG_Load("../../Documents/Des/R1.png"))==NULL)
                        {
                            fprintf(stderr,"impossible de charger l'image du dé");
                        }
                        posR1.x = 300;
                        posR1.y = 220;
                        SDL_BlitSurface(R1,NULL,*fond,&posR1);
                        SDL_Flip(*fond);
                        jeu(&posR1, &R1, fond);
                        continuer = 0;
                        SDL_FreeSurface(R1);
                        TTF_CloseFont(policePerudo);
                    }
                    if (((event.button.x) > 160)&&((event.button.x) < 480)
                        &&(((event.button.y) > 212)&&((event.button.y) <268)))
                    {
                        continuer = 0;
                    }
                    if (((event.button.x) > 160)&&((event.button.x) < 480)
                        &&(((event.button.y) > 324)&&((event.button.y) <380)))
                    {
                        continuer = 0;
                    }
                }
                break;
            }
    }
}
