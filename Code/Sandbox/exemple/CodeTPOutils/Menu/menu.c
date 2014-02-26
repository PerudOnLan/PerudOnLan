/**
   @file menu.c

   Implementation generique des fonctions du fichier d'interface menu.h

   @version 1.1
   @author Module projet informatique 1ere annee TELECOM SudParis (CSC3502)
   @date  Decembre 2007
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "fichierOuvrages.h"
#include "menu.h"


/*
   implemente la fonction du meme nom du fichier menu.h
*/
void choixAjouter(Bibliotheque bibliotheque) {
  FILE *logfile;
  Ouvrage ouvrage;
  int cr;
  ouvrage= saisirOuvrage();
  cr = ajouterOuvrage(bibliotheque, ouvrage);
  if ((logfile = fopen(LOGFILE, "a"))== NULL) logfile = stderr;
  if (cr == -1)
    fprintf(logfile, "Impossible d'ajouter l'ouvrage dans le fichier de la bibliotheque : %s",strerror(errno));
  else if (cr == 0)
   fprintf(logfile, "Impossible d'ajouter l'ouvrage dans la collection\n\t(elle contient deja %d ouvrages)\n\n", NB_MAX_OUVRAGES);
  fclose(logfile);
}


/*
  implemente la fonction du meme nom du fichier menu.h
*/
void choixSupprimer(Bibliotheque bibliotheque) {
  FILE *logfile;
  Auteur auteur;

  auteur = saisirAuteur();
  if (supprimerLesOuvragesDeAuteur(bibliotheque, auteur) == -1) {
    if ((logfile = fopen(LOGFILE, "a"))== NULL) logfile = stderr;
    fprintf(logfile, "Impossible de supprimer des ouvrages du fichier de la bibliotheque : %s",strerror(errno));
    fclose(logfile);
  }
}


/*
  implemente la fonction du meme nom du fichier menu.h
*/
void choixRechercher(Bibliotheque bibliotheque) {
  Auteur auteur;
  CollectionOuvrages collectionTrouve;

  auteur = saisirAuteur();
  rechercherLesOuvragesDeAuteur(bibliotheque, auteur, collectionTrouve);
  afficherCollectionOuvrages(collectionTrouve);
}


/*
  implemente la fonction du meme nom du fichier menu.h
*/
void choixAfficher(Bibliotheque bibliotheque) {
  afficherBibliotheque(bibliotheque);
}


/*
  implemente la fonction du meme nom du fichier menu.h
*/
void choixReset(Bibliotheque bibliotheque) {
  resetBibliotheque(bibliotheque);
}
