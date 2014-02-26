/**
 * @file bibliotheque.c
 *
 * Partie generique du module Bibliotheque
 *
 * @version 1.1
 * @author Module projet informatique 1ere annee TELECOM SudParis (CSC3502)
 * @date 28 nov. 2008
 */


#include <errno.h>     // pour utiliser errno et la valeur ENOENT
                       // ("man errno" pour en savoir plus)
#include <stdlib.h>
#include <time.h>
#include "bibliotheque.h"
#include "ouvrage.h"
#include "collectionOuvrages.h"
#include "fichierOuvrages.h"
#include "menu.h"


Bibliotheque nouvelleBibliotheque(char *nomFichier, char *nomBackUp) {
  FILE *logfile;
  Bibliotheque bibliotheque;
  int crtxt, crbak, errnotxt, errnobak, anomalie;
  bibliotheque = malloc(sizeof (Bibliotheque_struct));
  bibliotheque->collectionOuvrages[0] = NULL;
  strcpy(bibliotheque->nomFichier, nomFichier);
  strcpy(bibliotheque->nomBackUp, nomBackUp);
  crtxt = lectureFichier(bibliotheque->nomFichier, bibliotheque->collectionOuvrages);
  errnotxt = errno;
  if ((logfile = fopen(LOGFILE, "w"))== NULL) logfile = stderr;
  if (crtxt == OPERATION_OK){
    ecritureFichier(nomBackUp, bibliotheque->collectionOuvrages);
    fclose(logfile);
    return bibliotheque;
  }
  if (crtxt == PB_ACCES) {
    if (errnotxt == ENOENT) {
      anomalie = INEXISTANT;
      fprintf(logfile, "Fichier data.txt inexistant");
    }
    else {
      anomalie = INACCESSIBLE;
     fprintf(logfile, "Fichier data.txt inaccessible");
    }
  }
  if (crtxt == PB_FORMAT) {
    anomalie = CORROMPU;
    fprintf(logfile, "Fichier data.txt corrompu");
    //liberation memoire suite a lecture partielle
    viderCollectionOuvrages(bibliotheque->collectionOuvrages);
  }
  //tentative sur data.bak car data.txt inexistant, inaccessible ou corrompu
  fprintf(logfile, " => tentative de r'ecup'eration sur backup\n");
  crbak = lectureFichier(nomBackUp, bibliotheque->collectionOuvrages);
  errnobak = errno;
  if (crbak == OPERATION_OK) { // tentative reussie
    fprintf(logfile, "R'ecup'eration r'eussie sur fichier de backup\n");
    fclose(logfile);
    ecritureFichier(bibliotheque->nomFichier, bibliotheque->collectionOuvrages);
    return bibliotheque;
  }
  // abort apres affichage message explicatif
  if (crbak==PB_ACCES) {
    if (errnobak == ENOENT) {
      fprintf(logfile, "Fichier de backup inexistant");
      if (anomalie == INEXISTANT) {
	fprintf(logfile, " : d'emarrage avec un fichier vide\n");
	fclose(logfile);
	return bibliotheque;  /* vide */
      }
    }
    else
      fprintf(logfile, "Fichier de backup inaccessible");
  }
  if (crbak == PB_FORMAT) {
    fprintf(logfile, "Fichier de backup corrompu");
    viderCollectionOuvrages(bibliotheque->collectionOuvrages);
  }
  free(bibliotheque);
  fprintf(logfile, " : d'emarrage impossible\n");
  fclose(logfile);
  // Propagation de l'indication d'un probleme d'acces fichier
  return NULL;
}


void resetBibliotheque(Bibliotheque bibliotheque){
  FILE *logfile;
  char nomSnapshot[TAILLE_MAX_CHAINE], date[TAILLE_MAX_CHAINE];
  time_t nbsec;
  CollectionOuvrages tmpCollectionOuvrages;
  int crbak, errnobak;
  tmpCollectionOuvrages[0] = NULL;
  crbak = lectureFichier(bibliotheque->nomBackUp, tmpCollectionOuvrages);
  errnobak = errno;
  viderCollectionOuvrages(tmpCollectionOuvrages);
  if ((logfile = fopen(LOGFILE, "a"))== NULL) logfile = stderr;
  if (crbak==OPERATION_OK) { // tentative reussie
    time(&nbsec);
    strftime(date, TAILLE_MAX_CHAINE, "%m-%d-%H-%M-%S", localtime(&nbsec));
    // format "%Y-%m-%d-%H-%M-%S" pour avoir l'annee
    sprintf(nomSnapshot, "snapshot-%s.txt", date);
    ecritureFichier(nomSnapshot, bibliotheque->collectionOuvrages);
    viderCollectionOuvrages(bibliotheque->collectionOuvrages);
    crbak = lectureFichier(bibliotheque->nomBackUp, bibliotheque->collectionOuvrages);
    ecritureFichier(bibliotheque->nomFichier, bibliotheque->collectionOuvrages);
    fprintf(logfile, "Reset r'eussi sur fichier de backup (%s)\n", nomSnapshot);
    fclose(logfile);
    return;
 }
  fprintf(logfile, "Echec reprise de la collection initiale de la session\n");
  // abort apres affichage message explicatif
  if (crbak == PB_ACCES) {
    if (errnobak == ENOENT)
      fprintf(logfile, "Fichier de backup inexistant\n");
    else
      fprintf(logfile, "Fichier de backup inaccessible\n");
  }
  if (crbak == PB_FORMAT) {
    fprintf(logfile, "Fichier de backup corrompu\n");
    viderCollectionOuvrages(bibliotheque->collectionOuvrages);
  }
  fclose(logfile);
}


void supprimerBibliotheque(Bibliotheque bibliotheque){
  if (bibliotheque != NULL) {
	viderCollectionOuvrages(bibliotheque->collectionOuvrages);
    free(bibliotheque);
    bibliotheque = NULL;
  }
}


int ajouterOuvrage(Bibliotheque bibliotheque, Ouvrage ouvrage) {
  FILE *logfile;
  if (insererOuvrageDansCollection(bibliotheque->collectionOuvrages, ouvrage) == 0)
    return OPERATION_KO;
  if ((logfile = fopen(LOGFILE, "a"))== NULL) logfile = stderr;
  fprintf(logfile, "Ajout de %s\n", ouvrageToString(ouvrage));
  fclose(logfile);
  return insererDansFichier(bibliotheque->nomFichier, ouvrage);
}


int supprimerLesOuvragesDeAuteur(Bibliotheque bibliotheque, Auteur auteur) {
  FILE *logfile;

  Ouvrage ouvrage;
  ouvrage=initOuvrage("", auteur.nomAuteur, 0);  //ouvrage patron contenant seulement le nom de l'auteur
  if ((logfile = fopen(LOGFILE, "a"))== NULL) logfile = stderr;
  fprintf(logfile, "Suppression des ouvrages de %s\n", auteurToString(auteur));
  fclose(logfile);
  return supprimerLesOuvragesConformesPatron(bibliotheque, ouvrage);
}


void rechercherLesOuvragesDeAuteur(Bibliotheque bibliotheque, Auteur auteur, CollectionOuvrages collectionTrouve){
  Ouvrage ouvrage;  //ouvrage patron contenant seulement le nom de l'auteur
  ouvrage=initOuvrage("",auteur.nomAuteur,0);
  rechercherOuvrageDansCollection(bibliotheque->collectionOuvrages, ouvrage, collectionTrouve);
}


void afficherBibliotheque(Bibliotheque bibliotheque) {
	 if (nombreOuvrages(bibliotheque)==0)
	    afficher( "La collection est vide" );
	  else
	    afficherCollectionOuvrages(bibliotheque->collectionOuvrages);
}


int nombreOuvrages(Bibliotheque bibliotheque) {
  return nombreOuvragesCollection(bibliotheque->collectionOuvrages);
}

int supprimerLesOuvragesConformesPatron(Bibliotheque bibliotheque, Ouvrage ouvrage) {

#ifdef DEBUG
  afficher("Recherche sous collection dans la collection\n");
#endif
  supprimerOuvragesConformesPatron(bibliotheque->collectionOuvrages,ouvrage);
  return ecritureFichier(bibliotheque->nomFichier, bibliotheque->collectionOuvrages);
}

void rechercherLesOuvragesConformesAuPatron(Bibliotheque bibliotheque, Ouvrage ouvrage, CollectionOuvrages collectionTrouve){

#ifdef DEBUG
  afficher("rechercherDansCollection \n");
#endif
  rechercherOuvrageDansCollection(bibliotheque->collectionOuvrages, ouvrage, collectionTrouve);
}
