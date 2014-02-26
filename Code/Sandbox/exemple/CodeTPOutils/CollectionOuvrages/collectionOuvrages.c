/**
 * @file collectionOuvrages.c
 *
 * Ce module implemente les fonctions du fichier collectionOuvrages.h
 *
 * Attention des erreurs sont introduites pour illustrer
 * L'intérêt des tests unitaires ainsi que du débogueur
 *
 * @version pi12/trunk/Application/Code/CollectionOuvrages:1558
 * @author J Paul Gibson (Chantal Taconet, Daniel Ranc)
 * @date  26th January
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "collectionOuvrages.h"

int nombreOuvragesCollection( CollectionOuvrages collection) {
  int i=0;
  while (collection[i]!=NULL) {
    i++;
  }
  return i-1;
}


int insererOuvrageDansCollection( CollectionOuvrages collection, Ouvrage ouvrage) {
  int i=0;
  // Recherche de la premiere case disponible en fin de collection
  // La collection va de 0 à NB_MAX_OUVRAGES compris (taille NB_MAX_OUVRAGES+1)
  for (i=0; i<NB_MAX_OUVRAGES && collection[i]!=NULL; i++);
  //while ((i< NB_MAX_OUVRAGES) && (collection[i++]!=NULL));
  if (i==NB_MAX_OUVRAGES) {
	  printf("Collection Ouvrages pleine: NB_MAX_OUVRAGES=%d", NB_MAX_OUVRAGES);
	  return OPERATION_KO;
  }
  // Allocation d'une structure Ouvrage et remplissage
  collection[i]= malloc(sizeof(Ouvrage));
  *(collection[i])=ouvrage;

  collection[i+1]=NULL;
  return OPERATION_OK;
}

int rechercherOuvrageDansCollection( CollectionOuvrages collection, Ouvrage ouvragePatron, CollectionOuvrages collectionTrouve) {
  int i=0, j=0;

  if (collectionTrouve==NULL || collection==NULL) return OPERATION_KO;
  while (collection[i]!=NULL) {
    if ( ouvrageCorrespondPatron(*(collection[i]), ouvragePatron)) {
      // Construction progressive de collectionTrouve avec chaque occurrence trouvee
      collectionTrouve[j] = collection[i];
      j++;
    }
    i++;
  }
  collectionTrouve[j]=NULL; // pour terminer la collection trouvee par un pointeur NULL
  return OPERATION_OK;
}

int supprimerOuvragesConformesPatron( CollectionOuvrages collection, Ouvrage ouvragePatron) {
  int i=0;

  if (collection==NULL) return OPERATION_KO;
  while (collection[i]!=NULL) {
    if ( ouvrageCorrespondPatron(*(collection[i]), ouvragePatron)) {
      // Construction progressive de collectionTrouve avec chaque occurrence trouvee
      supprimerOuvrageCollectionIndice(collection, i);
    } else {
    	i++;
    }
  }
  return OPERATION_OK;
}

void supprimerOuvrageCollectionIndice(CollectionOuvrages collection, int indice) {
	int tailleCollection;
	int i;
	tailleCollection=nombreOuvragesCollection(collection);
	if (indice>=0 && indice<tailleCollection) {
		if (tailleCollection==1) {
			free(collection[0]);
			collection[0]=NULL;
			return;
		}
		free(collection[indice]);
		for (i=indice;i<tailleCollection;i++) {
			collection[i]=collection[i+1];
		}
		collection[tailleCollection-1]=NULL;
	} else {
		printf("Suppression impossible indice=%d\n", indice);
	}
}

void viderCollectionOuvrages(CollectionOuvrages collection) {
	  int tailleCollection;
	  int i;

	  tailleCollection=nombreOuvragesCollection(collection);
	  for (i=0;i<tailleCollection;i++){
		  free(collection[i]);
		  collection[i]=0;
	  }
}
