/**
 * @file bibliotheque-term.c
 *
 * Version "terminal" de la partie specifique du module Bibliotheque
 *
 * @version 1.1
 * @author Module projet informatique 1ere annee TELECOM SudParis (CSC3502)
 * @date 28 nov. 2008
 */

#include "bibliotheque.h"
#include <stdio.h>

/*
  implementation de la fonction afficherCollectionOuvrages() du fichier bibliotheque.h
*/
void afficherCollectionOuvrages( CollectionOuvrages collection) {

  printf("collection des ouvrages\n");
  printf(FORMATLEGENDEOUVRAGE, "Titre", "Auteur", "Annee");
  printf("\n");
  int i= 0;
  while (collection[i] != NULL){
    afficherOuvrage( *collection[i] );
    i++;
  }
  printf("\n\n");
}
