#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_net.h>

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL;
    SDL_Rect position;
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("SDL", NULL);
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
       SDL_Flip(ecran);
    SDL_FreeSurface(ecran);
    SDL_Quit();
    return EXIT_SUCCESS;
}
