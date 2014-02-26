/**
 * \mainpage Application exemple CSC3502 : gestion d'une bibliotheque
 *
 * Les fonctionnalités de cette application sont les suivantes :
 * <ul>
 * <li> lister les ouvrages d'une bibliothèque</li>
 * <li> ajouter un ouvrage dans la bibliothèque</li>
 * <li> supprimer des ouvrages de la bibliothèque</li>
 * <li> rechercher des ouvrages dans la bibliothèque</li>
 * </ul>
 *
 * @file main.c
 *
 * Programme principal pour la gestion d'une bibliotheque
 * (version terminal, gtk ou glade)
 *
 * @version 1.1
 * @author Module projet informatique 1ere annee TELECOM SudParis (CSC3502)
 * @date  Decembre 2007
*/

#include <stdio.h>
#include <stdlib.h>

#include "menu.h"


int main( int argc, char *argv[]) {
  // les donnees de la bibliotheque sont sauvegardees dans un fichier
  // ce qui permet de ne pas perdre les donnees entre deux executions
  char nomFichier[] = "data.txt";
  char nomBackUp[] = "data.bak";

  Bibliotheque bibliotheque;

  // creation d'une bibliotheque initialisee a partir du fichier
  bibliotheque = nouvelleBibliotheque(nomFichier, nomBackUp);

  if (bibliotheque == NULL) {
    printf("Impossible de creer la bibliotheque\n");
    return EXIT_FAILURE;
  }

  // initialisation de l'interface utilisateur
  if (init() == 0) {
      printf("Probleme d'initialisation de l'interface utilisateur\n");
      return EXIT_FAILURE;
  }

  // boucle d'interaction utilisateur
  menu(bibliotheque);

  return EXIT_SUCCESS;
}
