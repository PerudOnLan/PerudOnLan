#ifndef _PERUDUTILS_H
#define _PERUDUTILS_H

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

typedef enum {FAUX, VRAI} Booleen;

Booleen estDans(SDL_Event event, SDL_Surface * rectangle, SDL_Rect pos);

#endif
