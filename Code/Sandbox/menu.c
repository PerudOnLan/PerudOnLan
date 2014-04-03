#include "menu.h"

void menu(SDL_Surface ** fond)
{
    int continuer = 1;
    SDL_Event event;
    //chargement de la paco-police
    TTF_Font *policePerudo = NULL;
    policePerudo = TTF_OpenFont("../../Documents/policePerudo.ttf", (((*fond)->w)/15));
    SDL_Color couleurNoire = { 0,0,0 } ;
    SDL_Color couleurRouge = { 200,0,0};

    SDL_Surface *boutonCreer = NULL;

    boutonCreer = SDL_CreateRGBSurface(SDL_HWSURFACE, (((*fond)->w)/2), (((*fond)->h)-200)/5, 32, 0, 0, 0, 0);
    SDL_FillRect(boutonCreer,NULL,pROUGE);
    SDL_Rect positionCreer;
    positionCreer.x = ((*fond)->w)/4;
    positionCreer.y = 100;
    SDL_BlitSurface(boutonCreer,NULL,*fond,&positionCreer);

    SDL_Surface *texteCreer = NULL;
    texteCreer = TTF_RenderText_Shaded(policePerudo,"CREER", couleurNoire, couleurRouge);
    positionCreer.x = (((*fond)->w)/2) -(texteCreer->w / 2);
    positionCreer.y = (100+((((*fond)->h)-200)/10)) - (texteCreer->h /2);
    SDL_BlitSurface(texteCreer, NULL, *fond, &positionCreer);

    SDL_Surface *boutonRejoindre = NULL;

    boutonRejoindre = SDL_CreateRGBSurface(SDL_HWSURFACE, ((*fond)->w)/2,(((*fond)->h)-200)/5 , 32, 0, 0, 0, 0);
    SDL_FillRect(boutonRejoindre,NULL,pROUGE);
    SDL_Rect positionRejoindre;
    positionRejoindre.x = ((*fond)->w)/4;
    positionRejoindre.y = (100+(2*(((*fond)->h)-200)/5));
    SDL_BlitSurface(boutonRejoindre,NULL,*fond,&positionRejoindre);

    SDL_Surface *texteRejoindre = NULL;
    texteRejoindre = TTF_RenderText_Shaded(policePerudo,"REJOINDRE", couleurNoire, couleurRouge);
    positionRejoindre.x = (((*fond)->w)/2) -(texteRejoindre->w / 2);
    positionRejoindre.y = (((*fond)->h)/2) - (texteRejoindre->h /2);
    SDL_BlitSurface(texteRejoindre, NULL, *fond, &positionRejoindre);

    SDL_Surface *boutonOptions = NULL;

    boutonOptions = SDL_CreateRGBSurface(SDL_HWSURFACE, (((*fond)->w)/2), (((*fond)->h)-200)/5, 32, 0, 0, 0, 0);
    SDL_FillRect(boutonOptions,NULL,pROUGE);
    SDL_Rect positionOptions;
    positionOptions.x = ((*fond)->w)/4;
    positionOptions.y = (100+(4*(((*fond)->h)-200)/5));
    SDL_BlitSurface(boutonOptions,NULL,*fond,&positionOptions);

    SDL_Surface *texteOptions = NULL;
    texteOptions = TTF_RenderText_Shaded(policePerudo,"OPTIONS", couleurNoire, couleurRouge);
    positionOptions.x = (((*fond)->w)/2) -(texteOptions->w / 2);
    positionOptions.y = (100+(9*(((*fond)->h)-200)/10)) - (texteOptions->h /2);
    SDL_BlitSurface(texteOptions, NULL, *fond, &positionOptions);

    SDL_Flip(*fond);

    while (continuer)
    {
        FE_WaitEvent(&event);
        switch(event.type)
            {
                case SDL_QUIT:
                    continuer = 0;
                break;
                case SDL_MOUSEBUTTONDOWN:
                if(event.button.button==SDL_BUTTON_LEFT)
                {

                    if (((event.button.x) > ((*fond)->w)/4)&&((event.button.x) <(3*((*fond)->w)/4))
                        &&(((event.button.y) > 100)&&((event.button.y)<(100+((((*fond)->h)-200)/5)))))
                    {
                     //début du jeu
                        SDL_Surface *R1 = NULL;
                        SDL_Rect posR1;
                        if ((R1 = IMG_Load("../../Documents/Des/R1.png"))==NULL)
                        {
                            fprintf(stderr,"impossible de charger l'image du dé");
                        }
                        posR1.x = (((*fond)->w)/2)-40;
                        posR1.y = (((*fond)->h)/2)-40;
                        SDL_BlitSurface(R1,NULL,*fond,&posR1);
                        SDL_Flip(*fond);
                        jeu(&posR1, &R1, fond);
                        continuer = 0;
                        SDL_FreeSurface(R1);
                        TTF_CloseFont(policePerudo);
                    }
                    if (((event.button.x) > ((*fond)->w)/4)&&((event.button.x) < (3*((*fond)->w)/4))
                        &&(((event.button.y) > (100+(2*((((*fond)->h)-200)/5))))&&((event.button.y) <(100+(3*((((*fond)->h)-200)/5))))))
                    {
                        continuer = 0;
                    }
                    if (((event.button.x) > ((*fond)->w)/4)&&((event.button.x) < (3*((*fond)->w)/4))
                        &&(((event.button.y) > (100+(4*((((*fond)->h)-200)/5))))&&((event.button.y) <(((*fond)->h)-100))))
                    {
                        continuer=0;
                    }
                }
                break;
            }
    }
}

