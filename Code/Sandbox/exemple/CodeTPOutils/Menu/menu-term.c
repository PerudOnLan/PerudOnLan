/**
 * @file menu-term.c
 *
 * Ce module implemente les fonctions specifiques du fichier menu.h, pour
 * l'interface utilisateur en mode terminal
 *
 * @version 1.2
 * @author Module projet informatique 1ere annee TELECOM SudParis (CSC3502)
 * @date  Decembre 2007, revision decembre 2008
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "menu.h"
#include "fichierOuvrages.h"

extern void afficherSaisieOuvrage( char intitule[]);
extern void afficherSaisieAuteur( char intitule[]);


/*
  implementation de la fonction init() du fichier menu.h
*/
int init() {

  system("clear");
  printf("\tBienvenue dans biblio\nApplication de Gestion des ouvrages\n");
  printf("\n\n");

  return OPERATION_OK;
}


/*
*/
void quit() {

  printf("A bientot\n\n");
}


/*
  implementation de la fonction afficher() du fichier menu.h
*/
void afficher( char *msg) {

  printf("%s\n", msg);
}




/**
   ensemble des valeurs representant une des fonctionnalites du programme principal
*/
typedef enum {
  QUIT, AJOUT, SUPPRIME, RECHERCHE, AFFICHE, RESET
} Choix;


/**
   affiche le menu offert par l'application
   (Ajout, Suppression, Recherche et Affichage)
*/
void afficherMenu() {

  printf("%d : Quittez l'application\n", QUIT);
  printf("%d : Ajouter un ouvrage\n", AJOUT);
  printf("%d : Supprimer les ouvrages d'un auteur\n", SUPPRIME);
  printf("%d : Rechercher les ouvrages d'un auteur\n", RECHERCHE);
  printf("%d : Afficher la collection\n", AFFICHE);
  printf("%d : Reprendre la collection initiale de la session\n", RESET);
}


/**
   @return la valeur correspondant a la fonctionnalite
   que doit executer le programme principal
*/
Choix choix() {

  int entree = 0;
  printf("votre choix : ");
  while (scanf("%d",&entree) != 1){
    while ((! feof(stdin)) && (fgetc(stdin) != '\n'));
    printf("Saisissez un chiffre !!!\nvotre choix : ");
  }
  // suppression '\n' suivant l'entier choix saisi au clavier
  while ((! feof(stdin)) && (fgetc(stdin) != '\n'));
  return entree;
}


/*
  implementation de la fonction menu() du fichier menu.h
*/
void menu(Bibliotheque bibliotheque) {

  Choix reponse;
  afficherMenu();

  while ((reponse=choix())!=QUIT) {
    switch (reponse) {

    case AJOUT :
      afficherSaisieOuvrage( "Ajouter un ouvrage, saisir les informations utiles");
      choixAjouter(bibliotheque);
      break;

    case SUPPRIME :
      afficherSaisieAuteur( "Supprimer quel auteur ?");
      choixSupprimer(bibliotheque);
      break;

    case RECHERCHE :
      afficherSaisieAuteur( "Rechercher quel auteur ?");
      choixRechercher(bibliotheque);
      break;

    case AFFICHE :
      choixAfficher(bibliotheque);
      break;

    case RESET :
      choixReset(bibliotheque);
      break;

    default :
      printf("Erreur dans le choix du menu\n");
    }
    afficherMenu();
  }

  supprimerBibliotheque(bibliotheque);
  quit();
  exit(EXIT_SUCCESS);

}
