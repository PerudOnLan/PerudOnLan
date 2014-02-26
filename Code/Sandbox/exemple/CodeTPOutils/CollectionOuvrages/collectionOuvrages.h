/**
 * @file collectionOuvrages.h
 * @version pi12/trunk/Application/Code/CollectionOuvrages:1558
 * @author J Paul Gibson (Chantal Taconet, Daniel Ranc)
 * @date  26th January
 */

#ifndef _collection_OUVRAGES_H
#define _collection_OUVRAGES_H

//#include "menu.h"
//#include "bibliotheque.h"
#include "ouvrage.h"
#include <stdio.h>
/**
 * @def NB_MAX_OUVRAGES
 * Nombre maximum d'ouvrages dans la collection d'une bibliotheque
 */
#define  NB_MAX_OUVRAGES  100
/**
 * @a collectionOuvrages : tableau de NB_MAX_OUVRAGES pointeurs sur @a Ouvrage
 * Le dernier element de la collection est l'élément NULL
 */
typedef Ouvrage* CollectionOuvrages[NB_MAX_OUVRAGES+1];


int nombreOuvragesCollection( CollectionOuvrages collection);

/** \brief   Insertion de l'ouvrage ouvrage dans la collection collection
 *
 * @pre    collection != NULL
 * @param[in,out] collection : la collection dans laquelle l'insertion est effectuee
 * @param[in] ouvrage : l'ouvrage a inserer
 * @return OPERATION_KO en cas d'echec pour collection pleine, sinon OPERATION_OK
 */
int insererOuvrageDansCollection( CollectionOuvrages collection, Ouvrage ouvrage);


/** \brief Permet de rechercher dans la collection d'ouvrages tous le(s) ouvrages(s) conformes à un patron
 *   ouvrage.
 *
 *  <ul>
 *  <li> La recherche est faite sur tous les critères remplis :  </li>
 *  <li> Pour le titre et l'auteur si le premier caractère est nul le test ne sera pas fait, pour l'année si l'année est nulle le test ne sera pas éffectué</li>
 *  <li> le resultat de la recherche est stocke dans la collection d'ouvrages collectionTrouve</li>
 *  <li> collectionTrouve doit être vidé de tous ses elements avant que la recherche ne commence</li>
 * </ul>
 * @pre  collection != NULL && collectionTrouve !=NULL
 * @param[in] collection : collection d'ouvrages dans laquelle s'effectue la recherche
 * @param[in] ouvrage : contient les critères de recherche
 * @param[out] collectionTrouve : sous collection des ouvrages dont le nom d'auteur est identique a celui du parametre ouvrage
 * @return OPERATION_OK ou OPERATION_KO (si une des collections est NULL)
 */
int rechercherOuvrageDansCollection( CollectionOuvrages collection, Ouvrage ouvrage, CollectionOuvrages collectionTrouve);
/** \brief Permet de supprimer de la collection d'ouvrages l'ouvrage à l'indice i
 *
 * @pre  indice compris entre 0 et taille de la collection
 * @param[in,out] collection : collection de laquelle on supprime l'ouvrage.
 * @param[in] indice : indice de l'ouvrage a supprimer de la collection.
 *
 * @todo  This function is not yet fully specified and its implementation is not ready to be tested
 */
void supprimerOuvrageCollectionIndice(CollectionOuvrages collection, int indice);

/** \brief Permet de supprimer dans la collection d'ouvrages tous le(s) ouvrages(s) conformes à un patron
 *   ouvrage.
 *
 *  <ul>
 *  <li> La recherche est faite sur tous les critères remplis :  </li>
 *  <li> Pour le titre et l'auteur si le premier caractère est nul le test ne sera pas fait, pour l'année si l'année est nulle le test ne sera pas éffectué</li>
 * </ul>
 * @pre  collection != NULL && collectionTrouve !=NULL
 * @param[in,out] collection : collection d'ouvrages dans laquelle s'effectue la recherche
 * @param[in] ouvragePatron : contient les critères de recherche
 * @return OPERATION_OK ou OPERATION_KO (si la collection est NULL)
 */
int supprimerOuvragesConformesPatron( CollectionOuvrages collection, Ouvrage ouvragePatron);

/** \brief Permet de vider la collection d'ouvrages
 *
 * @pre  collection != NULL
 * @param[in,out] collection : collection d'ouvrages a vider.
 *
 * @todo  fonction a reecrire
 */
void viderCollectionOuvrages(CollectionOuvrages collection);

#endif /* _collection_OUVRAGES_H */
