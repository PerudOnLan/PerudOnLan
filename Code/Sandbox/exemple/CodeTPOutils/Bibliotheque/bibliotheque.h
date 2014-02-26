/**
 * @file bibliotheque.h
 *
 * Interface du module Bibliotheque
 *
 * @version 1.1
 * @author Module projet informatique 1ere annee TELECOM SudParis (CSC3502)
 * @date 28 nov. 2008
 */

#ifndef BIBLIOTHEQUE_H_
#define BIBLIOTHEQUE_H_

#include "ouvrage.h"
#include "collectionOuvrages.h"

#include <stdlib.h>  //malloc
#include <string.h>  //strcpy


/**
 * @def TAILLE_MAX_CHAINE
 * Longueur maximum du nom du fichier associe a la bibliotheque
 */
#define TAILLE_MAX_CHAINE 80


/** \brief une collection d'ouvrages et deux fichiers de sauvegarde
 * Bibliotheque_struct : une bibliotheque est une collection d'ouvrages
 * cette collection d'ouvrage est sauvegardee dans un fichier
 */
typedef struct {
	char nomFichier[TAILLE_MAX_CHAINE]; /*!< Le nom du fichier de stockage */
	char nomBackUp[TAILLE_MAX_CHAINE]; /*!< Le nom du fichier de backup */
	CollectionOuvrages collectionOuvrages; /*!< L'acces a la representation memoire */
} Bibliotheque_struct;
/**
 * Bibliotheque est un pointeur sur un Bibliotheque_struct (transparent du
 * point de vue d'un utilisateur de Bibliotheque
 */
typedef  Bibliotheque_struct *Bibliotheque;


/*
 * Partie a implantation generique
 */

/** \brief création d'une variable de type Bibliothèque
 * creation d'une variable de type Bibliotheque (allocation dynamique),
 * lecture du fichier dont le nom est fourni en parametre et
 * chargement dans la collection d'ouvrages associee a la bibliotheque
 * @param[in] nomFichier : nom du Fichier de stockage
 * @param[in] nomBackUp : nom du Fichier de backup
 * @return le pointeur sur la bibliotheque creee ou NULL en cas d'echec
 */
Bibliotheque nouvelleBibliotheque(char *nomFichier, char *nomBackUp);

/** \brief Restauration de la bibliothèque à partir du fichier backup
 * reset de la Bibliotheque a partir du fichier de backup
 * @param[in,out] bibliotheque : bibliotheque a reseter
 */
void resetBibliotheque(Bibliotheque bibliotheque);

/** \brief Suppression de la bibliotheque et de tous ses ouvrages
 * suppression de toute la Bibliotheque (liberation memoire)
 * @param[in] bibliotheque : bibliotheque a supprimer
 */
void supprimerBibliotheque(Bibliotheque bibliotheque);

/** \brief Ajout d'un ouvrage dans la bibliothèque
 * ajouter un ouvrage dans la bibliotheque
 * @param[in,out] bibliotheque : bibliotheque a laquelle ajouter l'ouvrage
 * @param[in] ouvrage : ouvrage a ajouter
 * @return OPERATION_OK en cas d'ajout reussi, OPERATION_KO si la collection est pleine et PB_ACCES en cas de probleme d'acces fichier
*/
int ajouterOuvrage(Bibliotheque bibliotheque, Ouvrage ouvrage);

/** \brief suppression de tous les ouvrages d'un auteur
 * supprimer des ouvrages d'un auteur dans la bibliotheque
 * @param[in,out] bibliotheque : la bibliotheque
 * @param[in] auteur : auteur dont il faut supprimer tous les ouvrages
 * @return PB_ACCES en cas d'echec, sinon une valeur positive ou nulle
*/
int supprimerLesOuvragesDeAuteur(Bibliotheque bibliotheque, Auteur auteur);

/** \brief Recherche les ouvrages d'un auteur
 * rechercher des ouvrages d'un auteur dans la bibliotheque
 * @param[in] bibliotheque : la bibliotheque
 * @param[in] auteur : auteur dont on recherche la collection d'ouvrages
 * @param[out] collectionTrouve : collection d'ouvrages correspondant a cet auteur
*/
void rechercherLesOuvragesDeAuteur(Bibliotheque bibliotheque, Auteur auteur, CollectionOuvrages collectionTrouve);


/** \brief retourne l nombre d'ouvrages de la bibliothèque
   denombre les ouvrages d'une bibliotheque
   @param[in] bibliotheque : la bibliotheque a denombrer
   @return le nombre d'ouvrages de la bibliotheque
*/
int nombreOuvrages(Bibliotheque bibliotheque);

/** \brief Recherche les ouvrages conformes au patron
 * rechercher ouvrages dans la bibliotheque
 * le parametre ouvrage fournit un patron des ouvrages a chercher
 * (actuellement seule la conformite a l'auteur est realisee)
 * @param[in] bibliotheque : la bibliotheque
 * @param[in] ouvrage : patron des ouvrages a rechercher
 * @param[out] collectionTrouve : collection d'ouvrages correspondant a ce patron
*/
void rechercherLesOuvragesConformesAuPatron(Bibliotheque bibliotheque, Ouvrage ouvrage, CollectionOuvrages collectionTrouve);

/** \brief suppression des ouvrages qui sont conformes au patron
 * supprimer des ouvrages dans la bibliotheque
 * le parametre ouvrage fournit un patron des ouvrages a supprimer
 * tous les ouvrages se conformant a ce patron sont supprimes
 * (actuellement seule la conformite a l'auteur est realisee)
 * @param[in,out] bibliotheque : la bibliotheque
 * @param[in] ouvrage : patron des ouvrages a supprimer
 * @return PB_ACCES en cas d'echec, sinon une valeur positive ou nulle
*/
int supprimerLesOuvragesConformesPatron(Bibliotheque bibliotheque, Ouvrage ouvrage);

/*
 * Partie a implantation specifique pour chaque version (terminal/graphique)
 */

/** \brief afficher les ouvrages d'une bibliotheque
 * afficher tous les ouvrages d'une bibliotheque
 * @param[in] bibliotheque : la bibliotheque dont on veut afficher les ouvrages
 */
void afficherBibliotheque(Bibliotheque bibliotheque);



/** \brief afficher les ouvrages d'une collection d'ouvrages
 * Affiche l'ensemble des ouvrages de la collection @a collection
 * @param[in] collection : la collection a afficher
 */
void afficherCollectionOuvrages( CollectionOuvrages collection);

#endif /* BIBLIOTHEQUE_H_ */
