/**
 * @file ouvrage.h
 * @version pi12/trunk/Application/Code/Ouvrage:1558
 * @author J Paul Gibson (Chantal Taconet, Daniel Ranc)
 * @date  26th January
 */

#ifndef OUVRAGE_H_
#define OUVRAGE_H_


#include <stdio.h>


/**
 * @def OPERATION_OK
 * Retour de fonction quand tout s'est bien pass'e
 */
#define OPERATION_OK 1
/**
 * @def OPERATION_KO
 * Retour de fonction quand un probleme a eu lieu
 */
#define OPERATION_KO 0

/** \brief Format d'affichage des informations d'un auteur
 */
#define FORMATAUTEUR "%20.20s"

/** \brief Format d'affichage des informations d'un ouvrage
*/
#define FORMATOUVRAGE "%60.60s %20.20s %10d"

/** \brief Format d'affichage des titres pour les informations d'un ouvrage dans une collection
*/
#define FORMATLEGENDEOUVRAGE "%60.60s %20.20s %10.10s\n"

/** \brief Taille maximale des chaines de caracteres utilisees pour le titre et l'auteur
 */
#define TAILLE_MAX_TITRE 60

/** \brief Taille maximale des chaines de caracteres utilisees pour le titre et l'auteur
 */
#define TAILLE_MAX_AUTEUR 20

/** \brief Structure de donnee representant l'auteur d'un ouvrage
 * Nécessaire pour le retour de saisirOuvrage qui ne peut pas être un array
 */
typedef struct {
  char nomAuteur [TAILLE_MAX_AUTEUR+1]; /**< \brief Le nom de l'auteur */
} Auteur;

/** \brief Structure de donnee representant le titre d'un Ouvrage
 */
//typedef char Titre [TAILLE_MAX_TITRE+1];

/** \brief Structure de donnee representant un ouvrage
 */
typedef struct {
  char titre[TAILLE_MAX_TITRE+1];      /**< \brief Le titre de l'ouvrage */
  char nomAuteur[TAILLE_MAX_AUTEUR+1];  /**< \brief Le nom de l'auteur */
  int anneeEdition;                     /**< \brief La date d'edition */
} Ouvrage;

/** \brief  Transforme un auteur en une chaine avant affichage vers l'utilisateur
 *
 * Partie a implantation generique pour toutes les versions (terminal/graphique):
 * <ul>
 * <li>  The Auteur.nomAuteur field will be padded out with spaces up to the maximum length defined by TAILLE_MAX_AUTEUR</li>
 * <li>  The padding of spaces will be done before the field value </li>
 * <li>  The value of the auteur parameter must <em> not </em> be changed by the function call.
 * <li>  A typical valid result will be <pre>"               author"</pre>
 * </ul>
 *
 * @param[in] auteur : l'auteur a transformer
 * @return la chaine de caracteres representant l'auteur donne en parametre
 */
char* auteurToString( Auteur auteur);

/** \brief Transforme un ouvrage en une chaine (titre, auteur, année) avant affichage vers l'utilisateur
 *
 * Partie a implantation generique pour toutes les versions (terminal/graphique) :
 * <ul>
 * <li>  The Ouvrage.titre field will be padded out with spaces up to the maximum length defined by TAILLE_MAX_TITRE</li>
 * <li>  The Ouvrage.nomAuteur field will be padded out with spaces up to the maximum length defined by TAILLE_MAX_AUTEUR</li>
 * <li>  The Ouvrage.anneeEdition attribute will be padded out with spaces up to the maximim length defined by INT_MAX</li>
 * <li>  The padding of spaces will be done before the field value </li>
 * <li>  There is an additional space between fields </li>
 * <li>  The value of the ouvrage parameter must <em> not </em> be changed by the function call.
 * <li>  A typical valid result will be <pre>"                                   title               author       2010"</pre>
 * </ul>
 *
 * @pre ouvrage != NULL
 * @param[in] ouvrage : l'ouvrage a transformer
 * @return la chaine de caracteres representant l'ouvrage donne en parametre dans l'ordre titre, auteur, puis année
*/
/** \brief retourne si un ouvrage est conforme à un patron
 *
 * La conformance est vérifié pour chacun des champs :
 * soit le champ du patron est nul  )
 *    (le premier caractère 'antislash + 0' pour une chaine -auteur et titre, ou égal à 0 pour un entier - annee)
 * soit le champ du patron est égal au champ de l'ouvrage
 * @pre ouvrage et patron != null
 * @param[in] ouvrage ouvrage dont on vérifie l'adéquation au patron
 * @param[in] ouvragePatron  patron de vérification
 * @return entier 0 ou 1 indiquant si l'ouvrage est conforme au patron
 */
int ouvrageCorrespondPatron(Ouvrage ouvrage, Ouvrage ouvragePatron);

/** \brief initialise les champs d'un ouvrage
 *
 * Tous les champs de l'ouvrage sont initialisés dans cette fonction
 * Les chaines de caractères sont copiées dans la limite des contenances des champs de l'ouvrage
 * @pre aucun des paramètres ne doit être omis (les chaines sont non nulles, l'année est non nulle)
 * @param[in] titre titre du livre
 * @param[in] nomAuteur nom de l'auteur
 * @param[in] anneeEdition année d'édition
 * @return l'ouvrage initialisé avec les 3 valeurs passées en paramètre
 */
Ouvrage initOuvrage(char titre[], char nomAuteur[], int anneeEdition);

char* ouvrageToString( Ouvrage ouvrage );

/** \brief Affiche les informations de l'ouvrage
 *
 *  Partie a implantation specifique pour chaque version (terminal/graphique)
 *
 *  @pre ouvrage != NULL
 *  @param[in] ouvrage : l'ouvrage a afficher
 */
void afficherOuvrage( Ouvrage ouvrage);

/** \brief Affiche les informations de l'auteur
 *
 *  Partie a implantation specifique pour chaque version (terminal/graphique)
 *
 *  @pre auteur != NULL
 *  @param[in] auteur : auteur a afficher
 */
void afficherAuteur( Auteur auteur);

/** \brief Permet la saisie des informations d'un ouvrage
 *
 *  Partie a implantation specifique pour chaque version (terminal/graphique)
 *  @return l'ouvrage saisi
 */
Ouvrage saisirOuvrage();

/** \brief Permet la saisie du nom de l'auteur d'un ouvrage
 *
 *  Partie a implantation specifique pour chaque version (terminal/graphique)
 *  @return le nom de l'auteur saisi
 */
Auteur saisirAuteur();


#endif /* OUVRAGE_H_ */
