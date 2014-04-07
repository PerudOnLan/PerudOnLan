/**
* \file couleurs.h
* \brief Définition des couleurs utilisées
* \author Dede
* \version 0.1
* \date 06/04
*
* Définition au format "SDL_MapRGB(fond->format,R,V,B)" de chaque couleur dont on a besoin dans le programme
*
*/


#ifndef _COULEUR_H
#define _COULEUR_H
/** \def ROUGE
* \brief couleur rouge
*/
#define ROUGE SDL_MapRGB(fond->format,200,0,0)
/** \def VERT
* \brief couleur verte
*/
#define VERT SDL_MapRGB(fond->format,10,180,30)
/** \def BLEU
* \brief couleur bleue
*/
#define BLEU SDL_MapRGB(fond->format,0,0,200)
/** \def JAUNE
* \brief couleur jaune
*/
#define JAUNE SDL_MapRGB(fond->format,210,220,0)

#endif
