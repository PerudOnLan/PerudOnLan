/**
* \file menu.h
* \brief code du menu avant le jeu
* \author Dede
* \version 0.2
* \date 09/04
*/

#ifndef _MENU_H
#define _MENU_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "SDLUtils.h"
#include "fastevents.h"
#include "couleurs.h"
#include "PerudUtils.h"
#include "jeu.h"

void menu(SDL_Surface * fond);
void options(SDL_Surface * fond);

#endif
