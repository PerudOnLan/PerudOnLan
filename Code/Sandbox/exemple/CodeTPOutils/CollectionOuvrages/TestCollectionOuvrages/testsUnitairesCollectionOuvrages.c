/**
 * @file testsCollectionOuvrages.c
 * @version pi12/trunk/Application/Code/Ouvrage/TestOuvrage:1644
 * @author J Paul Gibson  (Chantal Taconet, Daniel Ranc)
 * @date  27th January 2012
 *
 *
 * Using console (no CUnit) to illustrate Unit tests on the collectionOuvrages.c functions:
 * <ul>
 * <li> collectionOuvrages.nombreOuvragesCollection </li>
 * <li> collectionOuvrages.insererOuvrageDansCollection </li>
 * <li> collectionOuvrages.rechercherOuvrageDansCollection </li>
 * <li> collectionOuvrages.supprimerOuvragecollection </li>
 * <li> collectionOuvrages.viderCollectionOuvrages </li>
 * </ul>
 *
 */

#include <stdio.h>
#include <string.h>
#include "ouvrage.h"
#include "collectionOuvrages.h"

/** \brief The collection under test
 */
static CollectionOuvrages collOuvrages;

/** \brief Used to temporarily store  the collection under test, in order to check for unwanted side-effects
 */
static CollectionOuvrages ouvragesCopy;

/** \brief The ouvrage that can be used in testing behaviour of the collection under test
 */
static Ouvrage ouvrage;

/** \brief The ouvrage used for initialising the elements in the collection under test when it is full or half-full
 */
static Ouvrage ouvrageRemplissage;

/** \brief The total number of failed assertions when executing the tests
 */
static int errorCount;


/** \brief Initialise an empty collection of ouvrages
 *
 * @return 0 on successful completion
 */
int init_suite_collectionvide(void){

	// Creation d'une collection vide
	collOuvrages[0]=NULL;
	ouvragesCopy[0]=NULL;
	return 0;
}

/** \brief  Initialise a  half-full collection of ouvrages with the same ouvrage multiple times
 *
 * <ul>
 * <li> Creates an ouvrage "title  author 2011"</li>
 * <li> Half fills the collection under test with this ouvrage </li>
 * <li> Ensures that the collection copy is consistent with the collection under test </li>
 * </ul>
 * @return 0 on successful completion
 */
int init_suite_collectionmoitie(void){

	int i;

        // Use of new initialisation function initOuvrage - update by Chantal
	ouvrageRemplissage=initOuvrage("title", "author", 2011);
	collOuvrages[0]=NULL;
	ouvragesCopy[0]=NULL;

	// Creation d'une collection à moitié pleine
	for (i=0; i<NB_MAX_OUVRAGES/2;i++){
		insererOuvrageDansCollection(collOuvrages, ouvrageRemplissage);
		insererOuvrageDansCollection(ouvragesCopy, ouvrageRemplissage);
	}

	return 0;
}

/** \brief  Initialise a  full collection of ouvrages with the same ouvrage multiple times
 *
 * <ul>
 * <li> Creates an ouvrage "title  author 2011"</li>
 * <li> Fills the collection under test with this ouvrage </li>
 * <li> Ensures that the collection copy is consistent with the collection under test </li>
 * </ul>
 * @return 0 on successful completion
 */
int init_suite_collectionpleine(void){

	int i;
	ouvrageRemplissage=initOuvrage("title", "author", 2011);
	collOuvrages[0]=NULL;
	ouvragesCopy[0]=NULL;

	// Creation d'une collection pleine
	for (i=0; i<NB_MAX_OUVRAGES; i++){
		insererOuvrageDansCollection(collOuvrages, ouvrageRemplissage);
		insererOuvrageDansCollection(ouvragesCopy, ouvrageRemplissage);
	}

	return 0;
}

/** \brief The suite cleanup function - resets all collection elements to NULL
 *
 * @return 0 on successful completion
 */
int clean_suite(void){

	int i;
	for (i=0; i<NB_MAX_OUVRAGES; i++){
		collOuvrages[i]=NULL;
		ouvragesCopy[i]=NULL;
	}
	return 0;
}

/** \brief Unit Test collectionOuvrages.nombreOuvragesCollection: an empty collection has 0 elements
 */
void testNombreCollectionVide(void){

	init_suite_collectionvide();
        if (collOuvrages!=NULL){
             printf("** ASSERT -- an empty collection has 0 elements");
             if (nombreOuvragesCollection (collOuvrages) == 0) printf ("\n TRUE\n"); 
              else {printf ("\n FALSE\n");errorCount++;}
           }

}


/** \brief Unit Test collectionOuvrages.nombreOuvragesCollection: the count of elements in collection is correct when it is half full
 */
void testNombreCollectionMoitie(void){

        init_suite_collectionmoitie();
        if (collOuvrages!=NULL){ 
             printf("** ASSERT -- the count of elements in collection is correct when it is half full");
             if (NB_MAX_OUVRAGES/2==nombreOuvragesCollection (collOuvrages)) printf ("\n TRUE\n"); 
               else {printf ("\n FALSE\n");errorCount++;}
           }

}

/** \brief Unit Test collectionOuvrages.nombreOuvragesCollection: the count of elements in collection is correct when it is  full
 */
void testNombreCollectionPleine(void){

        init_suite_collectionpleine();
        if (collOuvrages!=NULL) { 
             printf("** ASSERT -- the count of elements in collection is correct when it is  full");
             if (NB_MAX_OUVRAGES==nombreOuvragesCollection (collOuvrages)) printf ("\n TRUE\n"); 
              else {printf ("\n FALSE\n");errorCount++;}
           }

}



/** \brief Unit Test Suite for collectionOuvrages.nombreOuvragesCollection
 * 	<ul>
 *	 <li> Une collection vide</li>
 *       <li> Une collection à moitié pleine </li>
 *       <li> Une collection pleine </li>
 *      </ul>
 */
void testNombreOuvragesCollection(void){

        printf("\n\n**** Test Suite function nombreOuvragesCollection de CollectionOuvrages  ****\n\n");

        testNombreCollectionVide();
        clean_suite();

        testNombreCollectionMoitie();
        clean_suite();

        testNombreCollectionPleine();
        clean_suite();
}






/** \brief Unit Test collectionOuvrages.insererOuvrageDansCollection : collection vide
 *
 * <ul>
 * <li> add an ouvrage and check that it is the only element of the collection </li>
 * <li> search the collection for the author of the added ouvrage and check that we find the same ouvrage </li>
 * <li> search the collection for an author different to that of the added ouvrage and check that the result is empty </li>
 * </ul>
 */
void testInsererDansCollectionVide(void){ 

	init_suite_collectionvide();
	int retour;
	CollectionOuvrages ouvragesTrouves;

	ouvragesTrouves[0]=NULL;

	ouvrage=initOuvrage("Another title", "Another author", 2011);

	/* add an ouvrage */

        printf("** Add an ouvrage to an empty collection\n");
	retour=insererOuvrageDansCollection ( collOuvrages, ouvrage);

	if (retour==OPERATION_OK) {

		/* and check that it is the only element of the collection */
		printf("** ASSERT -- it is the only element in the collection");
                if (1==nombreOuvragesCollection(collOuvrages)) printf ("\n TRUE\n"); 
                 else {printf ("\n FALSE\n");errorCount++;}

		/* search the collection for the author of the added ouvrage  */
		rechercherOuvrageDansCollection(collOuvrages, ouvrage, ouvragesTrouves);
                printf("** ASSERT -- searching the collection for the author of the added ouvrage returns a single element");
                if (1==nombreOuvragesCollection(ouvragesTrouves)) printf ("\n TRUE\n"); 
                 else {printf ("\n FALSE\n");errorCount++;}
		
		/* and check that we find the same ouvrage for that author */
                printf("** ASSERT -- check that names are the same");
                if (!strcmp(ouvragesTrouves[0]->nomAuteur, ouvrage.nomAuteur)) printf ("\n TRUE\n"); 
                 else {printf ("\n FALSE\n");errorCount++;}
                printf("** ASSERT -- check that titles are the same");
                if (!strcmp(ouvragesTrouves[0]->titre, ouvrage.titre)) printf ("\n TRUE\n");
                 else {printf ("\n FALSE\n");errorCount++;}		
                printf("** ASSERT -- check that years are the same");
                if (ouvragesTrouves[0]->anneeEdition == ouvrage.anneeEdition) printf ("\n TRUE\n"); 
                 else {printf ("\n FALSE\n");errorCount++;}
                
	}
}



/** \brief Unit Test collectionOuvrages.insererOuvrageDansCollection : collection moitie vide
 *
 * add two ouvrages by an author not in the collection and check that:
 * <ul>
 * <li> the return value is OPERATION_OK in both cases</li>
 * <li> the number in the collection has been increased by 2</li>
 * <li> we can find both of them in the  collection after insertion</li>
 * <li> we can find all the original ouvrages that were in the collection before the insertion </li>
 * </ul>
 */

void testInsererDansCollectionMoitie(void){

        init_suite_collectionmoitie();
	int number;
	int retour;
	CollectionOuvrages ouvragesTrouves;

	ouvragesTrouves[0]=NULL;

	ouvrage=initOuvrage("different title", "different author", 2010);

	number = nombreOuvragesCollection(collOuvrages);

	// add two ouvrages by an author not in the collection
	retour=insererOuvrageDansCollection ( collOuvrages, ouvrage);
	retour=insererOuvrageDansCollection ( collOuvrages, ouvrage);

       printf("\n** Add two ouvrages by an author not in a collection which is already half full\n");

	if (retour==OPERATION_OK) {
		
                printf("** ASSERT -- the number in collection has been increased by 2");
                if (nombreOuvragesCollection(collOuvrages)==2+number) printf ("\n TRUE\n"); 
                 else {printf ("\n FALSE\n");errorCount++;}

                printf("** ASSERT -- we can find both of them in the  collection after insertion");
                rechercherOuvrageDansCollection(collOuvrages, ouvrage, ouvragesTrouves);
                if (2==nombreOuvragesCollection(ouvragesTrouves)) printf ("\n TRUE\n"); 
                 else {printf ("\n FALSE\n");errorCount++;}

                printf("** ASSERT -- we can find all the original ouvrages that were in the collection before the insertion");
		rechercherOuvrageDansCollection(collOuvrages, initOuvrage("","author",0), ouvragesTrouves);
		if (NB_MAX_OUVRAGES/2==nombreOuvragesCollection(ouvragesTrouves)) printf ("\n TRUE\n"); 
                 else {printf ("\n FALSE\n");errorCount++;}

	}
}

/** \brief Unit Test collectionOuvrages.insererOuvrageDansCollection : collection pleine
 *
 * <ul>
 * <li> tests "OPERATION_KO en cas d'echec pour collection pleine" </li>
 * <li> check no side effects on original collection </li>
 */
void testInsererDansCollectionPleine(void){

        init_suite_collectionpleine();
	int retour;
	int i;
	int differences;

	init_suite_collectionpleine();
        printf("\n** Initialise  a collection which is already full\n");

        printf("** ASSERT -- the collection is full");
                if (NB_MAX_OUVRAGES==nombreOuvragesCollection (collOuvrages)) printf ("\n TRUE\n"); 
                 else {printf ("\n FALSE\n");errorCount++;}

        printf("** Attempt to add a new ouvrage to the full collection\n");
	ouvrage=initOuvrage("another title", "another author", 2011);
	retour=insererOuvrageDansCollection ( collOuvrages, ouvrage);

        printf("\n** ASSERT -- the collection returns OPERATION_KO");
                if (OPERATION_KO==retour) printf ("\n TRUE\n"); 
                 else {printf ("\n FALSE\n");errorCount++;}

        // Count differences between old and new collection to check that there are no side-effects
	differences =0;
	i=0;
	while (collOuvrages[i]!=NULL) {
		if (strcmp(collOuvrages[i]->titre, ouvragesCopy[i]->titre)!=0) differences++;
		if (strcmp(collOuvrages[i]->nomAuteur, ouvragesCopy[i]->nomAuteur)!=0) differences++;
		if (collOuvrages[i]->anneeEdition != ouvragesCopy[i]->anneeEdition) differences++;
		i++;
	}

        printf("** ASSERT -- no side effects on original collection");
                if (differences ==0) printf ("\n TRUE\n"); 
                 else {printf ("\n FALSE\n");errorCount++;}

}

/** \brief Unit Test Suite for collectionOuvrages.insererOuvrageDansCollection
 * 	<ul>
 *	 <li> Insertion dans une collection vide</li>
 *       <li> Insertion dans une collection à moitié pleine </li>
 *       <li> Insertion dans une collection pleine </li>
 *      </ul>
 */
void testInsererOuvrageDansCollection(void){

        printf("\n\n**** Test Suite function insererOuvrageDansCollection de CollectionOuvrages  ****\n\n");

        testInsererDansCollectionVide();
        clean_suite();

        testInsererDansCollectionMoitie();
        clean_suite();

        testInsererDansCollectionPleine();
        clean_suite();
}





/** \brief Unit Test collectionOuvrages.rechercherOuvrageDansCollection : ouvrage(s) trouvé(s)
 *
 *  Tests that we find all titles by the  same author :
 * <ul>
 * <li> adding 3 ouvrages- two different titles and two common titles - by the same author 
 *      and counting them after the search for that author</li>
 * <li> pass a non-empty ouvragesTrouves parameter to test that it is emptied by the function before the search starts</li>
 * <li> check no side effects on original collection after the search</li>
 * </ul>
 *  Tests that we find all titles in the  same year :
 * <ul>
 * <li> checking for any title or author but specifying a specific year
 * </ul>
 */
void testRechercheTrouve(void){

	init_suite_collectionmoitie();
	CollectionOuvrages ouvragesTrouves;
	int differences =0;
	int i=0;


        printf("** Tests that we find all titles by the  same author\n");
        printf("** Adding 3 ouvrages to a half full collection - two different titles and two common titles - by author1 \n");
	ouvrage=initOuvrage("title1", "author1", 2011);
	insererOuvrageDansCollection ( collOuvrages, ouvrage);
	insererOuvrageDansCollection ( collOuvrages, ouvrage);
	insererOuvrageDansCollection ( ouvragesCopy, ouvrage);
	insererOuvrageDansCollection ( ouvragesCopy, ouvrage);
	ouvrage=initOuvrage("title2", "author1", 2010);
	insererOuvrageDansCollection ( collOuvrages, ouvrage);
	insererOuvrageDansCollection ( ouvragesCopy, ouvrage);

	ouvragesTrouves[0]=NULL;
	insererOuvrageDansCollection ( ouvragesTrouves, ouvrage);

        printf("** ASSERT --  the collection used to store the result of the search is not empty");
                if (nombreOuvragesCollection(ouvragesTrouves)>0) printf ("\n TRUE\n"); 
                 else {printf ("\n FALSE\n");errorCount++;}

        printf("** Search for any books by author1\n");
	rechercherOuvrageDansCollection(collOuvrages, initOuvrage("","author1",0), ouvragesTrouves);

        printf("** ASSERT --  the resulting collection contains only the 3 elements found");
                if (nombreOuvragesCollection(ouvragesTrouves)==3) printf ("\n TRUE\n"); 
                 else {printf ("\n FALSE\n");errorCount++;}

        printf("** ASSERT --  the number of elements in the original collection has not been changed by the search");
                if (nombreOuvragesCollection(collOuvrages) == nombreOuvragesCollection(ouvragesCopy)) printf ("\n TRUE\n");    
                 else {printf ("\n FALSE\n");errorCount++;}


        // count the differences between the collection before and after the search in order to verify absence of side effects
	while (i<nombreOuvragesCollection(collOuvrages)) {
		if (strcmp(collOuvrages[i]->titre, ouvragesCopy[i]->titre)!=0) differences++;
		if (strcmp(collOuvrages[i]->nomAuteur, ouvragesCopy[i]->nomAuteur)!=0) differences++;
		if (collOuvrages[i]->anneeEdition != ouvragesCopy[i]->anneeEdition) differences++;
		i++;
	}

        printf("** ASSERT --  no side effects on the collection being searched");
                if (differences ==0) printf ("\n TRUE\n"); 
                 else {printf ("\n FALSE\n");errorCount++;}

        printf("** Tests that we find all titles in the  same year\n");
        rechercherOuvrageDansCollection(collOuvrages, initOuvrage("","",2011), ouvragesTrouves);
        printf("** ASSERT --  found the correct number of ouvrages for the specified year");
                if (nombreOuvragesCollection(ouvragesTrouves)==52) printf ("\n TRUE\n");  
                 else {printf ("\n FALSE\n");errorCount++;}

}

/** \brief Unit Test collectionOuvrages.rechercherOuvrageDansCollection : aucune ouvrage trouvé
 *
 * <ul>
 * <li> tests that we have an empty collection as the result of a search that finds no matching ouvrages </li>
 * <li> check no side effects on original collection </li>
 * </ul>
 */
void testRecherchePasTrouve(void){

        init_suite_collectionmoitie();
	int i=0;
	int differences=0;
	CollectionOuvrages ouvragesTrouves;

	ouvragesTrouves[0] = NULL;

	ouvrage=initOuvrage("another title", "another author", 2011);

        printf("\n** Search for an overage that is not in a half full collection\n");
	rechercherOuvrageDansCollection(collOuvrages, ouvrage, ouvragesTrouves);

        printf("** ASSERT --  we have an empty collection as the result of a search that finds no matching ouvrages");
                if (nombreOuvragesCollection(ouvragesTrouves)==0) printf ("\n TRUE\n");  
                 else {printf ("\n FALSE\n");errorCount++;}

        printf("** ASSERT --  the number of elements in the original collection has not been changed by the search");
                if (nombreOuvragesCollection(collOuvrages) == nombreOuvragesCollection(ouvragesCopy)) printf ("\n TRUE\n");  
                 else {printf ("\n FALSE\n");errorCount++;}


        // count the differences between the collection before and after the search in order to verify absence of side effects
	while (i<nombreOuvragesCollection(collOuvrages)) {
		if (strcmp(collOuvrages[i]->titre, ouvragesCopy[i]->titre)!=0) differences++;
		if (strcmp(collOuvrages[i]->nomAuteur, ouvragesCopy[i]->nomAuteur)!=0) differences++;
		if (collOuvrages[i]->anneeEdition != ouvragesCopy[i]->anneeEdition) differences++;
		i++;
	}

        printf("** ASSERT --  no side effects on the collection being searched");
                if (differences ==0)  printf ("\n TRUE\n");  
                 else {printf ("\n FALSE\n");errorCount++;}

}

/** \brief Unit Test Suite for collectionOuvrages.rechercherOuvrageDansCollection
 * 	<ul>
 *	 <li> Recherche d'un auteur qui est dans la collection</li>
 *       <li> Recherche d'un annee qui est dans la collection</li>
 *       <li> Recherche d'un auteur qui n'est pas dans la collection</li>
 *      </ul>
 */
void testRechercherOuvrageDansCollection(void){

        printf("\n\n**** Test Suite function rechercherOuvrageDansCollection de CollectionOuvrages  ****\n\n");

        testRechercheTrouve();
        clean_suite();

        testRecherchePasTrouve();
        clean_suite();
}



/** \brief Unit Test collectionOuvrages.supprimerOuvrageCollectionIndice :  supprimer has no effect on empty collection
 *
 */
void testSupprimerOuvrageCollectionParIndiceVide(void){

      init_suite_collectionvide();
      supprimerOuvrageCollectionIndice(collOuvrages, 0);
      printf("** ASSERT --  no change to size of the empty collection when we try to remove the front element");
                if (nombreOuvragesCollection(collOuvrages)==0)  printf ("\n TRUE\n");  
                 else {printf ("\n FALSE\n");errorCount++;}
}

/** \brief Unit Test collectionOuvrages.supprimerOuvrageCollectionIndice :  supprimer has no effect when index is out of bounds
 *
 */
void testSupprimerOuvrageCollectionParIndice_OOB(void) {

       init_suite_collectionmoitie();
       supprimerOuvrageCollectionIndice(collOuvrages, -1);
       printf("** ASSERT --  no change to size of the non-empty collection when we try to remove the -1th element");
                if (nombreOuvragesCollection(collOuvrages)==NB_MAX_OUVRAGES/2)  printf ("\n TRUE\n");  
                 else {printf ("\n FALSE\n");errorCount++;}

       supprimerOuvrageCollectionIndice(collOuvrages, NB_MAX_OUVRAGES/2+1);
       printf("** ASSERT --  no change to size of the non-empty collection when we try to remove an element which is bigger than the maximum");
                if (nombreOuvragesCollection(collOuvrages)==NB_MAX_OUVRAGES/2)  printf ("\n TRUE\n");  
                 else {printf ("\n FALSE\n");errorCount++;}

}

/** \brief Unit Test collectionOuvrages.supprimerOuvrageCollectionIndice :  supprimer from half-full collection removes the correct element
 *
 */
void testSupprimerOuvrageCollectionParIndiceMoitie(void) {
	
        init_suite_collectionmoitie();
        int tailleCollection;
	Ouvrage ouvrageNouveau;
	Ouvrage dernierOuvrage;

	tailleCollection=nombreOuvragesCollection(collOuvrages);
	ouvrageNouveau=initOuvrage("titre","auteur",120);
	*(collOuvrages[tailleCollection-2])=ouvrageNouveau;
	dernierOuvrage=*(collOuvrages[tailleCollection-1]);

	supprimerOuvrageCollectionIndice(collOuvrages, 0);

        printf("** ASSERT --  supprimer removes only one element");
        if (nombreOuvragesCollection(collOuvrages)==tailleCollection-1)  printf ("\n TRUE\n");  
                 else {printf ("\n FALSE\n");errorCount++;}
	
        printf("** ASSERT --  supprimer removes the correct element");
        if (ouvrageCorrespondPatron(*(collOuvrages[tailleCollection-3]), ouvrageNouveau) &&
            ouvrageCorrespondPatron(*(collOuvrages[tailleCollection-2]), dernierOuvrage))  printf ("\n TRUE\n");  
                 else {printf ("\n FALSE\n");errorCount++;}
}


/** \brief Unit Test collectionOuvrages.supprimerOuvrageCollectionIndice :  supprimer correctly removes the last element of a full collection
 *
 * @todo Add more tests for collectionOuvrages.supprimerOuvrageCollectionIndice
 */
void testSupprimerOuvrageCollectionParIndicePleineFin(void) {

        init_suite_collectionpleine();
	int tailleCollection;
	Ouvrage ouvrageNouveau;

	tailleCollection=nombreOuvragesCollection(collOuvrages);
	ouvrageNouveau=initOuvrage("titre","auteur",120);
	*(collOuvrages[tailleCollection-2])=ouvrageNouveau;

	supprimerOuvrageCollectionIndice(collOuvrages, tailleCollection-1);

        printf("** ASSERT --  removing the last element of a full collection reduces its size by 1");
        if (nombreOuvragesCollection(collOuvrages)==(tailleCollection-1))  printf ("\n TRUE\n");  
                 else {printf ("\n FALSE\n");errorCount++;}

       // SHOULD ADD MORE COMPLETE TESTS
}



/** \brief Unit Test Suite for collectionOuvrages.supprimerOuvrageCollectionIndice
 * 	<ul>
 *       <li> supprimer has no effect on empty collection</li>
 *       <li> supprimer has no effect when index is out of bounds</li>
 *       <li> supprimer from half full collection removes the correct element</li>
 *       <li> supprimer can remove the last element of a full collection </li>
 *      </ul>
 */
void testSupprimerOuvrageDansCollection(void){ 

        printf("\n\n**** Test Suite function supprimerOuvrageCollectionIndice de CollectionOuvrages  ****\n\n");


        testSupprimerOuvrageCollectionParIndiceVide();
        clean_suite();

        testSupprimerOuvrageCollectionParIndice_OOB();
        clean_suite();

        testSupprimerOuvrageCollectionParIndiceMoitie();
        clean_suite();

        testSupprimerOuvrageCollectionParIndicePleineFin();
        clean_suite();
}

/** \brief Unit Test collectionOuvrages.supprimerOuvragesConformesPatron :  remove specific element that is not in the collection
 *
 */
void testSupprimerOuvragesConformesNoMatch(void){

        init_suite_collectionpleine();
	int count = nombreOuvragesCollection(collOuvrages);

	ouvrage=initOuvrage("another title", "another author",2011);

	supprimerOuvragesConformesPatron(collOuvrages, ouvrage);

        printf("** ASSERT --  removing a specific element that is not in the collection does not change the size of the collection");
        if (count==nombreOuvragesCollection(collOuvrages))  printf ("\n TRUE\n");  
                 else {printf ("\n FALSE\n");errorCount++;}

}

/** \brief Unit Test collectionOuvrages.supprimerOuvragesConformesPatron :  removing an ouvrage pattern from a collection where no elements match
 *
 */
void supprimerNoCommon(void){

	init_suite_collectionmoitie();

	int count;
	Ouvrage ouvrage1, ouvrage2;
	count = nombreOuvragesCollection(collOuvrages);

	ouvrage1=initOuvrage("title1", "author1",2011);
	ouvrage2=initOuvrage("title2", "author2",2011);

	supprimerOuvragesConformesPatron(collOuvrages, ouvrage1);
	supprimerOuvragesConformesPatron(collOuvrages, ouvrage2);

        printf("** ASSERT --  removing an ouvrage pattern from a collection where no elements match does not change the size of the collection");
        if (count==nombreOuvragesCollection(collOuvrages))  printf ("\n TRUE\n");  
                 else {printf ("\n FALSE\n");errorCount++;}

}

/** \brief Unit Test collectionOuvrages.supprimerOuvragecollection :  removing an ouvrage pattern from a collection where a subset of elements match
 *
 */
void supprimerSomeCommon(void){

	init_suite_collectionmoitie();
	int count;


	ouvrage=initOuvrage("title1", "author1", 2011);
	insererOuvrageDansCollection ( collOuvrages, ouvrage);
	insererOuvrageDansCollection ( collOuvrages, ouvrage);

	ouvrage=initOuvrage("title2", "author2", 2012);

	insererOuvrageDansCollection ( collOuvrages, ouvrage);

	ouvrage=initOuvrage("title3", "author1", 2012);

	insererOuvrageDansCollection ( collOuvrages, ouvrage);

	count = nombreOuvragesCollection(collOuvrages);

	supprimerOuvragesConformesPatron(collOuvrages, initOuvrage("", "author1", 0));

        printf("** ASSERT --  removing an ouvrage which matches 3 elements results in a size reduction of 3");
        if (count == nombreOuvragesCollection(collOuvrages)+3)  printf ("\n TRUE\n");  
                 else {printf ("\n FALSE\n");errorCount++;}

}

/** \brief Unit Test collectionOuvrages.supprimerOuvragesConformesPatron :  removing an ouvrage pattern from a collection of multiple elements of the same ouvrage leaves an empty collection 
 *
 */
void supprimerAll(void){

       init_suite_collectionmoitie();
	supprimerOuvragesConformesPatron(collOuvrages, ouvrageRemplissage);
        printf("** ASSERT --  removing an ouvrage pattern from a collection of multiple elements of the same ouvrage leaves an empty collection");
        if (nombreOuvragesCollection(collOuvrages)==0)  printf ("\n TRUE\n");  
                 else {printf ("\n FALSE\n");errorCount++;}

}


/** \brief Unit Test Suite for collectionOuvrages.supprimerOuvragesConformesPatron
 * 	<ul>
 *       <li> Removing specific element that is not in the collection </li>
 *       <li> Removing an ouvrage pattern from a collection where no elements match</li>
 *	 <li> Removing an ouvrage pattern from a collection where a subset of elements matc</li>
 *	 <li> Removing an ouvrage pattern from a collection of multiple elements of the same ouvrage leaves an empty collection</li>
 *      </ul>
 */
void testSupprimerOuvragesConformesPatron(void){ 

        printf("\n\n**** Test Suite function supprimerOuvragesConformesPatron de CollectionOuvrages  ****\n\n");


        testSupprimerOuvragesConformesNoMatch();
        clean_suite();

        supprimerNoCommon();
        clean_suite();

        supprimerSomeCommon();
        clean_suite();

        supprimerAll();
        clean_suite();
}



/** \brief Unit Test collectionOuvrages.viderCollectionOuvrages - tests emptying an already empty collection
 */
void testViderVide(void){
	
	viderCollectionOuvrages(collOuvrages);
        printf("** ASSERT --  emptying an already empty collection leaves an empty collection");
        if (nombreOuvragesCollection(collOuvrages)==0)  printf ("\n TRUE\n");  
                 else {printf ("\n FALSE\n");errorCount++;}

}

/** \brief Unit Test collectionOuvrages.viderCollectionOuvrages - tests emptying a half-full collection
 */
void testViderMoitieVide(void){

	viderCollectionOuvrages(collOuvrages);
        printf("** ASSERT --  emptying a half full collection leaves an empty collection");
        if (nombreOuvragesCollection(collOuvrages)==0)  printf ("\n TRUE\n");  
                 else {printf ("\n FALSE\n");errorCount++;}
}

/** \brief Unit Test collectionOuvrages.viderCollectionOuvrages - tests emptying a full collection
 */
void testViderPleine(void){

	viderCollectionOuvrages(collOuvrages);
        printf("** ASSERT --  emptying a  full collection leaves an empty collection");
        if (nombreOuvragesCollection(collOuvrages)==0)  printf ("\n TRUE\n");  
                 else {printf ("\n FALSE\n");errorCount++;}
}


/** \brief Unit Test Suite for collectionOuvrages.supprimerOuvragesConformesPatron
 * 	<ul>
 *	 <li> Une collection vide</li>
 *       <li> Une collection à moitié pleine </li>
 *       <li> Une collection pleine </li>
 *      </ul>
 */
void testViderCollectionOuvrages(void){ 

        printf("\n\n**** Test Suite function viderCollectionOuvrages de CollectionOuvrages  ****\n\n");

	init_suite_collectionvide();
        testViderVide();
        clean_suite();
        init_suite_collectionmoitie();
        testViderMoitieVide();
        clean_suite();
        init_suite_collectionpleine();
        testViderPleine();
        clean_suite();
}

/** \brief  Main test execution of suites through standard console
 *
 * <ul>  
 * <li> execute the tests of the nombreOuvragesCollection  suite</li>
 * 	<ul>
 *	 <li> Une collection vide</li>
 *       <li> Une collection à moitié pleine </li>
 *       <li> Une collection pleine </li>
 *      </ul>
 * <li> execute the tests of the insererOuvrageDansCollection suite</li>
 * 	<ul>
 *	 <li> Insertion dans une collection vide</li>
 *       <li> Insertion dans une collection à moitié pleine </li>
 *       <li> Insertion dans une collection pleine </li>
 *      </ul>
 * <li> execute the tests of the rechercherOuvrageDansCollection suite</li>
 * 	<ul>
 *	 <li> Recherche d'un auteur qui est dans la collection</li>
 *       <li> Recherche d'un auteur qui n'est pas dans la collection</li>
 *      </ul>
 * <li> execute the tests of the supprimerOuvrageCollectionIndice suite
 * 	<ul>
 *       <li> supprimer has no effect on empty collection</li>
 *       <li> supprimer has no effect when index is out of bounds</li>
 *       <li> supprimer from half full collection removes the correct element</li>
 *       <li> supprimer can remove the last element of a full collection </li>
 *      </ul>
 * <li> execute the tests of the supprimerOuvragesConformesPatron suite</li>
 * 	<ul>
 *       <li> Supprimer une sous collection vide </li>
 *       <li> Supprimer une sous collection avec aucune element en commun</li>
 *	 <li> Supprimer une sous collection avec plusieurs elements en commun</li>
 *	 <li> Supprimer tous les ouvrages, en utilisant une copie de la collection</li>
 *      </ul>
 * <li> execute the tests of the viderCollectionOuvrages suite</li>
 * 	<ul>
 *	 <li> Une collection vide</li>
 *       <li> Une collection à moitié pleine </li>
 *       <li> Une collection pleine </li>
 *      </ul>
 * <li> run all test suites for each function to be tested</li>
 * </ul>
 */
int main( int argc, char *argv[]) {

        errorCount =0;

        printf("\n\n******* TestCollectionOuvrages - execute all unit test suites ********");

	/* execute the tests of the nombreOuvragesCollection  suite */
        testNombreOuvragesCollection();

        /* execute the tests of the insererOuvrageDansCollection  suite */
        testInsererOuvrageDansCollection();

        /* execute the tests of the rechercherOuvrageDansCollection  suite */
        testRechercherOuvrageDansCollection();

        /* execute the tests of the supprimerOuvrageDansCollection  suite */
         testSupprimerOuvrageDansCollection();

         /* execute the tests of the supprimerOuvragesConformesPatron  suite */
         testSupprimerOuvragesConformesPatron();

         /* execute the tests of the viderCollectionOuvrages suite */
         testViderCollectionOuvrages();

        printf("\n\n******* All unit test suites executed ********\n");
        printf("******* Number of failed assertions = %i ********\n", errorCount);

        return errorCount;

      
}



