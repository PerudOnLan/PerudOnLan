/**
* \file ia.h
* \brief code de l'ia
* \author Artus, Fran�ois
* \version 0.2
* \date 08/04
*/
#ifndef _IA_H
#define _IA_H

#include <stdio.h>
#include <stdlib.h>
#include "perudo.h"


int d5 () ;
int nombreValeurProbable (int valeur, int nbT, int nbDe, int de[6]) ;
int plusOuMoins (int nbT) ;
Annonce cerveauIA (Annonce annonce_precedente, int de[6]) ;
void valeurLePlus (int de[6], int *pNombre, int *pValeur, int valeur_precedente, int nb_de_des) ;
Joueur creerIa();














#endif

