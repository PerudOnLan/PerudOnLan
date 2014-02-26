/**
 * @file ouvrage-term.c
 *
 * Version "terminal" de la partie specifique du module Ouvrage
 *
 * @version 1.1
 * @author Module projet informatique 1ere annee TELECOM SudParis (CSC3502)
 * @date 28 nov. 2008
 */

#include <string.h>

#include "ouvrage.h"
//#include "util.h"

/* **
   affiche l'interface de saisie du nom de l'auteur d'un ouvrage
   @param intitule chaine de caracteres a afficher comme titre de l'ecran de saisie
*/
void afficherSaisieAuteur( char intitule[]);


/**
   affiche l'interface de saisie des informations
   d'un ouvrage (auteur, titre, annee)
   @param intitule chaine de caracteres a afficher comme titre de l'ecran de saisie
*/
void afficherSaisieOuvrage( char intitule[]);


/*
  implementation de la fonction afficherOuvrage() du fichier ouvrage.h
*/
void afficherOuvrage( Ouvrage ouvrage) {

  printf("%s\n\n", ouvrageToString(ouvrage) );
}

/*
  implementation de la fonction afficherAuteur() du fichier ouvrage.h
*/
void afficherAuteur(Auteur auteur) {

  printf("%s\n", auteur.nomAuteur );
}

/*
*/
void afficherSaisieOuvrage( char intitule[]) {

  printf ("%s \n",intitule);
  printf("Titre : ? Auteur : ? Annee : ? (aller a la ligne entre chaque item)\n");
}


/*
*/
void afficherSaisieAuteur( char intitule[]) {

  printf ("%s \n",intitule);
  printf("Auteur : ");
}


/*
  implementation de la fonction saisirOuvrage() du fichier ouvrage.h
*/
Ouvrage saisirOuvrage() {

  Ouvrage ouvrage= {"", "", 0};
  while (strcmp(ouvrage.titre,"") == 0 ||
	 strcmp(ouvrage.nomAuteur,"") == 0 ||
	 ouvrage.anneeEdition == 0) {
    //    if (fgets( ouvrage.titre, TAILLE_MAX_CHAINE, stdin) == ouvrage.titre)
    if (fgets( ouvrage.titre, TAILLE_MAX_TITRE, stdin) == ouvrage.titre)
      if (ouvrage.titre[strlen(ouvrage.titre)-1] == '\n')
	ouvrage.titre[strlen(ouvrage.titre)-1] = '\0';
    //    if (fgets( ouvrage.nomAuteur, TAILLE_MAX_CHAINE, stdin) == ouvrage.nomAuteur)
    if (fgets( ouvrage.nomAuteur, TAILLE_MAX_AUTEUR, stdin) == ouvrage.nomAuteur)
      if (ouvrage.nomAuteur[strlen(ouvrage.nomAuteur)-1] == '\n')
	ouvrage.nomAuteur[strlen(ouvrage.nomAuteur)-1] = '\0';
    while ( scanf( "%d",&ouvrage.anneeEdition) != 1){
      while ((! feof(stdin)) && (fgetc(stdin) != '\n'));
      printf("Saisissez un nombre pour l'annee !!!\nvotre choix : ");
    }
    // suppression du '\n' suivant l'entier annee
    while ((! feof(stdin)) && (fgetc(stdin) != '\n'));
    if (strcmp(ouvrage.titre,"") == 0 ||
	strcmp(ouvrage.nomAuteur,"") == 0 ||
	ouvrage.anneeEdition == 0) {
      afficherOuvrage(ouvrage);
      afficherSaisieOuvrage("Remplir tous les champs (la date ne doit pas etre 0)");
    }
  }
  return ouvrage;
}


/*
  implementation de la fonction saisirAuteur() du fichier ouvrage.h
*/
Auteur saisirAuteur()  {

  Auteur auteur = {""};
   while (strcmp(auteur.nomAuteur,"")==0) {
    //     if (fgets( auteur.nomAuteur, TAILLE_MAX_CHAINE, stdin) == auteur.nomAuteur)
    if (fgets( auteur.nomAuteur, TAILLE_MAX_AUTEUR, stdin) == auteur.nomAuteur)
      if (auteur.nomAuteur[strlen(auteur.nomAuteur)-1] == '\n')
	auteur.nomAuteur[strlen(auteur.nomAuteur)-1] = '\0';
    if (strcmp(auteur.nomAuteur,"")==0)
      afficherSaisieAuteur("Saisir le nom d'auteur");
  }
  return auteur;
}

