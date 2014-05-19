/**
* \file graphics.h
* \brief code du jeu à proprement parler
* \author Dede
* \version 0.1
* \date 16/04
*/
#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <unistd.h>
#include <time.h>
#include "SDLUtils.h"
#include "fastevents.h"
#include "PerudUtils.h"
#include "couleurs.h"

int init_graphique (int nbJoueurs, SDL_Surface ** gob, SDL_Surface ** des);

Annonce interface (SDL_Surface * fond, int nbJoueurs, SDL_Surface ** gob, SDL_Rect *positions   );

int melange (SDL_Surface * fond, int nbJoueurs, SDL_Surface ** gob, SDL_Rect * positions);
#endif
