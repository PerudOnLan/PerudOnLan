/**
 * @file menu.h
 * @version pi12/trunk/Application/Code/Ouvrage/TestOuvrage:1557
 * @author J Paul Gibson (Chantal Taconet, Daniel Ranc)
 * @date  26th January
 *
 * Module <em> projet informatique </em> 
 * 1ere annee TELECOM SudParis (CSC3502 -  see http://cours.it-sudparis.eu/moodle/course/view.php?id=40 )
 *
 * Interface du module Menu dedie a l'interaction utilisateur
 */

#ifndef _MENU_H
#define _MENU_H

#include "ouvrage.h"
#include "bibliotheque.h"

/** \brief  Ajout d'un ouvrage dans la bibliotheque
 *
 * Gestion de l'ajout d'un ouvrage dans la bibliothèque :
 * - saisie des informations (interactivité utilisateur)
 * - ajout dans la bibliotheque
 * - enregistrement dans le fichier associé
 *
 * Si l'ajout est résussi :
 * <ul>
 * <li> Mise à jour du fichier bibliothèque </li>
 * <li> Sinon : la raison de l'echec sera enregistrée dans le fichier log </li>
 *     <ul> <li> Impossible d'ajouter l'ouvrage dans le fichier de la bibliotheque </li>
 *          <li> Contient deja MAX ouvrages</li>
 *     </ul>
 * </ul>
 *  @pre bibliotheque !=NULL
 *  @param[in,out] bibliotheque : bibliotheque a laquelle ajouter l'ouvrage
 */
void choixAjouter(Bibliotheque bibliotheque);

/** \brief  Suppression de la collection des ouvrages correspondant a un auteur
 *
 * Partie a implantation generique:
 * <ul>
 * <li> Read the author identifier from the user interface </li>
 * <li> Attempt to remove all ouvrages in the bibliotheque written by the specified author</li>
 * <li> If the removal is successful then update the log file to record the removal</li>
 * <li> If the removal is not successful then record the failure in the log file together with the reason:</li>
 *     <ul> <li>  Impossible de supprimer des ouvrages du fichier de la bibliotheque</li>
 *     </ul>
 * </ul>
 *
 *  @pre bibliotheque !=NULL
 *  @param[in,out] bibliotheque : la bibliotheque
 */
void choixSupprimer(Bibliotheque bibliotheque);

/** \brief  Recherche dans la collection les ouvrages correspondant a un auteur et les afficher
 *
 * Partie a implantation generique:
 * <ul>
 * <li> Read the author identifier from the user interface </li>
 * <li> Find all the ouvrages in the bibliotheque that are written by the specified author</li>
 * <li> Present this information at the user interface
 * </ul>
 *
 *  @pre bibliotheque !=NULL
 *  @param[in,out] bibliotheque : la bibliotheque
 */
void choixRechercher(Bibliotheque bibliotheque);

/** \brief  Affichage la collection des Ouvrages
 *
 * Partie a implantation generique:
 *
 *  @pre bibliotheque !=NULL
 *  @param[in] bibliotheque : la bibliotheque
 */
void choixAfficher(Bibliotheque bibliotheque);

/** \brief  Reprend la collection initiale de la session (a l'aide du fichier backup)
 *
 * Partie a implantation generique:
 *
 *  @pre bibliotheque !=NULL
 *  @param[in,out] bibliotheque : la bibliotheque
 */
void choixReset(Bibliotheque bibliotheque);

/** \brief Initialisation de l'interface utilisateur
 *
 * Partie a implantation specifique pour chaque version (terminal/graphique):
 * 
 *  @return un code de retour entier: OPERATION_OK is ok, ou OPERATION_KO en cas de probleme
 */
int init();

/** \brief Affiche la chaine de caracteres
 *
 * Partie a implantation specifique pour chaque version (terminal/graphique):
 * 
 *  @param[in] msg : la chaine a afficher
 */
void afficher( char *msg);

/** \brief  Realise les differents traitements lies au choix de
 *          l'utilisateur a travers l'interface utilisateur
 *
 * Partie a implantation specifique pour chaque version (terminal/graphique):
 *
 *  @pre bibliotheque !=NULL
 *  @param[in,out] bibliotheque bibliotheque sur laquelle se fait les traitements
 */
void menu(Bibliotheque bibliotheque);

#endif //_MENU_H
