/**
* \file PerudUtils.c
* \brief Fonctions utiles pour le projet
* \author Dede
* \version 0.2
* \date 09/04
*/

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

#define TAILLE_MAX 10

/**
*\enum Booleen
*/
typedef enum
{
    FAUX,           /** <Valeur Fausse */
    VRAI            /** <Valeur vraie */
} Booleen;

Booleen estDans(SDL_Event event, SDL_Surface * rectangle, SDL_Rect pos);

int longueur_mot(char * mot);

void saisir (SDL_Surface * champ, SDL_Rect pos, Uint32 couleurChamp, TTF_Font * police, SDL_Color couleurPolice, SDL_Color couleurFond, char * mot, int longueur_max, SDL_Surface * fond);

#endif
