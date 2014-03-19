#ifndef _TESTSDL_H
#define _TESTSDL_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "SDLUtils.h"
#include "fastevents.h"

#define ROUGE SDL_MapRGB(fond->format,200,0,0)
#define VERT SDL_MapRGB(fond->format,10,180,30)
#define BLEU SDL_MapRGB(fond->format,0,0,200)

#define pROUGE SDL_MapRGB((*fond)->format,200,0,0)
#define pVERT SDL_MapRGB((*fond)->format,10,180,30)
#define pBLEU SDL_MapRGB((*fond)->format,0,0,200)

void jeu(SDL_Rect * pos,SDL_Surface ** img, SDL_Surface ** fond);



#endif
