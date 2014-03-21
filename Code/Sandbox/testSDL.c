#include "testSDL.h"

int main(int argc, char *argv[])
{
    //initialisation de la randomisation
    printf("\nrandom pliz ? \n");
    int seed = 0;
    scanf("%d",&seed);
    srandom(seed);
    //init SDL
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

    //début du jeu
    jeu(&positionDeBleu, &deBleu, &fond);

    //Quitte la SDL
    SDL_FreeSurface(deBleu);
    SDL_FreeSurface(fond);
    mySDL_Quit();
    return EXIT_SUCCESS;
}




void jeu(SDL_Rect * pos, SDL_Surface ** img, SDL_Surface ** fond)
{
    int score = 0;
  int continuer = 1;
  SDL_Event event;

  while (continuer)
    {
      FE_PollEvent(&event);
      switch(event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button==SDL_BUTTON_LEFT)
            {
                if ((((event.button.x) - (pos->x))>0)&&(((event.button.x) - (pos->x))<50)&&(((event.button.y) - (pos->y))>0)&&(((event.button.y) - (pos->y)<57)))
                {
                    score ++;
                    pos->x = random()%590;
                    pos->y = random()%423;
                }
       /*         else
                {
                continuer = 0;
                fprintf(stdout,"\nscore : %d\n",score);
                }
        */
            }
        break;
        case SDL_QUIT:
            continuer = 0;
            fprintf(stdout,"\nscore : %d\n",score);
        break;
        }
    SDL_FillRect(*fond,NULL,pVERT);
    pos->x += (((random()%21)-10));
    pos->x = (pos->x)%590;
    pos->y += (((random()%21)-10));
    pos->y = (pos->y)%423;

    SDL_BlitSurface(*img,NULL,*fond,pos);
    SDL_Flip(*fond);
    }
}
