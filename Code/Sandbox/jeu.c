#include "jeu.h"


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
                        pos->x = random()%(((*fond)->w)-80);
                        pos->y = random()%(((*fond)->h)-80);
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
        pos->x += (((random()%41)-20));
        pos->x = (pos->x)%(((*fond)->w)-80);
        pos->y += (((random()%41)-20));
        pos->y = (pos->y)%(((*fond)->h)-80);

        SDL_BlitSurface(*img,NULL,*fond,pos);
        SDL_Flip(*fond);
        SDL_Delay(20);
        timerActuel = SDL_GetTicks();
        fprintf(stdout,"%ld\n",(timerActuel-timerDebut));
    }
    fprintf(stdout,"\nscore : %d\n",score);
  }
