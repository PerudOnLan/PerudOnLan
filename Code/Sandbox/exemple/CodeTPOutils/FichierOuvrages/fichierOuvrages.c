/**
 * @file fichierOuvrages.c
 *
 * Ce module implemente les fonctions du fichier fichierOuvrages.h
 *
 * @version 1.2
 * @author Module projet informatique 1ere annee TELECOM SudParis (CSC3502)
 * @date  Decembre 2007, revision decembre 2008
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "fichierOuvrages.h"
#include "collectionOuvrages.h"


void purgeFichierEntree( FILE *stream ) {
  while ((! feof(stream)) && (fgetc(stream) != '\n'));
}


int insererDansFichier( char nomfichier[], Ouvrage ouvrage) {
  FILE *fichbib;
  int cr;
  if ((fichbib= fopen(nomfichier, "a"))== NULL) {
    return PB_ACCES;
  }
  // Ecriture des informations dans le fichier
  cr = fprintf(fichbib,"%s\n%s\n%d\n\n",ouvrage.titre,ouvrage.nomAuteur,ouvrage.anneeEdition);
  fclose(fichbib);
  if (cr <= 0)
    return PB_ACCES;
  return OPERATION_OK;
}


int lectureFichier( char nomfichier[], CollectionOuvrages collection) {
  FILE *fichbib;
  FILE *logfile;
  Ouvrage ouvrage;
  int result;
  collection[0]= NULL;
  if ((fichbib= fopen(nomfichier, "r"))== NULL) {
    return PB_ACCES;
  }
  while (!feof(fichbib)) {
    result = 0;
    if (fgets( ouvrage.titre, TAILLE_MAX_TITRE, fichbib) == ouvrage.titre)
      result++;
    if (ouvrage.titre[strlen(ouvrage.titre)-1] == '\n')
      ouvrage.titre[strlen(ouvrage.titre)-1] = '\0';
    if (fgets( ouvrage.nomAuteur, TAILLE_MAX_AUTEUR, fichbib) == ouvrage.nomAuteur)
      result++;
    if (ouvrage.nomAuteur[strlen(ouvrage.nomAuteur)-1] == '\n')
      ouvrage.nomAuteur[strlen(ouvrage.nomAuteur)-1] = '\0';
    result += fscanf( fichbib, "%d", &ouvrage.anneeEdition);
      purgeFichierEntree( fichbib); // suppression '\n' suivant l'entier annee
      purgeFichierEntree( fichbib); // suppression saut de ligne entre deux ouvrages
    if (result==3)
      insererOuvrageDansCollection( collection, ouvrage);
    else 
      if (result != EOF) {
	if ((logfile = fopen(LOGFILE, "a"))== NULL) logfile = stderr;
	fprintf(logfile, "Format de ligne incorrect\n");
	fclose(logfile);
	return PB_FORMAT;
      }
  }
  fclose(fichbib);
  return OPERATION_OK;
}


int ecritureFichier( char nomfichier[], CollectionOuvrages collection) {
  FILE *fichbib;
  int i=0, cr = 0;
  if ((fichbib= fopen(nomfichier, "w"))== NULL) {
    return PB_ACCES;
  }
  // Condition sur cr pour sortir de boucle au premier probleme d'ecriture
  while ((collection[i]!=NULL) && (cr >= 0)) {
    cr = fprintf(fichbib,"%s\n%s\n%d\n\n",collection[i]->titre,collection[i]->nomAuteur,collection[i]->anneeEdition);
    i++;
  }
  fclose(fichbib);
  return cr;
}
