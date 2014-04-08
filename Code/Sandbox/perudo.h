#ifndef _PERUDO_H
#define _PERUDO_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "ia.h"

typedef enum {FAUX, VRAI} Booleen;

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
    char* pseudo;
    int des[6];
    int nb_de_des;
} Joueur;

void partie (int nb_de_joueurs);

#endif // _PERUDO_H
