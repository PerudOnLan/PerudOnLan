/**
 * @file ouvrage.c
 *
 * Partie generique de l'implementation du module Ouvrage
 *
 * @version 1.1
 * @author Module projet informatique 1ere annee TELECOM SudParis (CSC3502)
 * @date 28 nov. 2008
 */

#include "ouvrage.h"
#include <string.h>

/*
*/
char* ouvrageToString( Ouvrage ouvrage) {

  static char ligne[256];

  sprintf( ligne, FORMATOUVRAGE, ouvrage.titre, ouvrage.nomAuteur, ouvrage.anneeEdition);
  return ligne;
}

/*
*/

char* auteurToString( Auteur auteur) {

  static char ligne[256];

  sprintf( ligne, FORMATAUTEUR, auteur.nomAuteur);
  return ligne;
}

int ouvrageCorrespondPatron(Ouvrage ouvrage, Ouvrage ouvragePatron){
	  int auteurDefiniDansPatron;
	  int titreDefiniDansPatron;
	  int anneeDefinieDansPatron;
	  int auteurOK;
	  int titreOK;
	  int anneeOK;

	  auteurDefiniDansPatron=ouvragePatron.nomAuteur[0]!='\0';
	  titreDefiniDansPatron=ouvragePatron.titre[0]!='\0';
	  anneeDefinieDansPatron=ouvragePatron.anneeEdition!=0;
	  // dans le patron :
	  //    soit le champ est non défini (chaine vide ou entier nul) et donc aucune vérification est faite
	  //    soit le champ est défini et on teste l'égalité
	  auteurOK= !auteurDefiniDansPatron || (auteurDefiniDansPatron && strcmp(ouvrage.nomAuteur, ouvragePatron.nomAuteur) == 0);
	  titreOK= !titreDefiniDansPatron || (titreDefiniDansPatron && strcmp(ouvrage.titre, ouvragePatron.titre) == 0);
	  anneeOK= !anneeDefinieDansPatron || (ouvragePatron.anneeEdition == ouvrage.anneeEdition) ;

	  return auteurOK && anneeOK && titreOK;
}

Ouvrage initOuvrage(char titre[], char nomAuteur[], int anneeEdition) {
	Ouvrage ouvrage;
	strncpy(ouvrage.titre, titre, TAILLE_MAX_TITRE);
	strncpy(ouvrage.nomAuteur, nomAuteur, TAILLE_MAX_AUTEUR);
	ouvrage.anneeEdition=anneeEdition;

	return ouvrage;
}
