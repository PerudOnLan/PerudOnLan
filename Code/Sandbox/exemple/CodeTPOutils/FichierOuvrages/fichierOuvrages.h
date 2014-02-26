/**
 * @file fichierOuvrages.h
 *
 * Interface de gestion de collections d'ouvrages et d'acces fichier
 *
 * @version 1.2
 * @author Module projet informatique 1ere annee TELECOM SudParis (CSC3502)
 * @date  Decembre 2007, revision decembre 2010
 */


#ifndef _FICHIER_OUVRAGES_H
#define _FICHIER_OUVRAGES_H

#include "menu.h"
#include "bibliotheque.h"
#include <stdio.h>


#define PB_ACCES -1
#define PB_FORMAT -2
#define LOGFILE "bibliotheque.log"

typedef enum {INEXISTANT, INACCESSIBLE, CORROMPU} Anomalie;

/**
   purgeFichierEntree le stream @a stream jusqu'au premier 'saut de ligne' compris
*/
void purgeFichierEntree( FILE *stream );

/**
   permet d'inserer un ouvrage a la fin d'un fichier d'ouvrages.
   @param[in] nomfichier : nom du fichier dans lequel on insere l'ouvrage ouvrage
   @param[in] ouvrage : l'ouvrage a inserer en debut du fichier nomfichier
   @return -1 en cas d'echec, sinon 1
*/
int insererDansFichier( char nomfichier[], Ouvrage ouvrage);


/**
   permet de lire un fichier d'ouvrages et de les stocker dans une collection
   @param[in] nomfichier : nom du fichier dans lequel s'effectue la lecture des ouvrages
   @param[out] collection : collection des ouvrages lus dans le fichier nomfichier
   @return -1 en cas d'echec, sinon 1
*/
int lectureFichier( char nomfichier[], CollectionOuvrages collection);


/**
   permet d'ecrire dans un fichier une collection d'ouvrages
   @param[in] nomfichier : nom du fichier dans lequel s'effectue l'ecriture des ouvrages
   @param[in] collection : collection des ouvrages a ecrire dans le fichier nomfichier
   @return -1 en cas d'echec, sinon une valeur positive ou nulle
*/
int ecritureFichier( char nomfichier[], CollectionOuvrages collection);

#endif /* _FICHIER_OUVRAGES_H */
