/**
* \file jeu.h
* \brief code du jeu à proprement parler
* \author François,Dede
* \version 0.2
* \date 09/04
*/
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
#include "PerudUtils.h"
#include "couleurs.h"

typedef enum {MISE, MENTEUR, EXACT} Type;

typedef struct {
    Type type;
    union {
    struct {
        int nombre;
        int de;
    } mise;
        Booleen menteur;
        Booleen exact;
    } info;
} Annonce;

typedef struct {
    char pseudo[TAILLE_MAX+1];
    int des[6];
    int nb_de_des;
} Joueur;

int partie (SDL_Surface * fond);

void klik(SDL_Surface * fond);

#endif
