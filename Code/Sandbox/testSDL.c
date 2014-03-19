#include "testSDL.h"

int main(int argc, char *argv[])
{
    mySDLInitOrQuit(SDL_INIT_EVENTTHREAD | SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE);
    SDL_Surface *fond=NULL;
    SDL_Surface *deBleu = NULL;
    SDL_Rect positionDeBleu;

    if ((fond = SDL_SetVideoMode(640,480,32,SDL_RESIZABLE|SDL_DOUBLEBUF))==NULL)
    {
        fprintf(stderr,"Erreur à l'initialisation de la video : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("PerudOnLan",NULL);
    SDL_FillRect(fond,NULL,VERT);

    if ((deBleu = IMG_Load("de1.png"))==NULL)
    {
        fprintf(stderr,"impossible de charger l'image du dé");
    }
    positionDeBleu.x = 300;
    positionDeBleu.y = 220;
    SDL_BlitSurface(deBleu,NULL,fond,&positionDeBleu);

    SDL_Flip(fond);
    jeu(&positionDeBleu, &deBleu, &fond);

    SDL_FreeSurface(deBleu);
    SDL_FreeSurface(fond);
    mySDL_Quit();
    return EXIT_SUCCESS;
}




void jeu(SDL_Rect * pos, SDL_Surface ** img, SDL_Surface ** fond)
{
  int continuer = 1;
  SDL_Event event;

  while (continuer)
    {
      FE_WaitEvent(&event);
      switch(event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button==SDL_BUTTON_LEFT)
            {
                pos->x = event.button.x;
                pos->y = event.button.y;
            }
        break;
        case SDL_QUIT:
            continuer = 0;
        break;
        }
    SDL_FillRect(*fond,NULL,pVERT);
    SDL_BlitSurface(*img,NULL,*fond,pos);
    SDL_Flip(*fond);
    }
}
