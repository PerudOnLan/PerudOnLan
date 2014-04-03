#ifndef _JEU_H
#define _JEU_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <unistd.h>
#include <time.h>
#include "SDLUtils.h"
#include "fastevents.h"
#include "couleurs.h"


void jeu(SDL_Rect * pos,SDL_Surface ** img, SDL_Surface ** fond);

#endif
