/**
* \file testsUnitaires.c
* \brief Les tests unitaires de quelques fonctions
* \author Fran�ois
* \version 0.1
* \date 18/05
*/

#include "testsUnitaires.h"

int main()
{
    test_longueur_mot();
    test_d5();
    test_nombreValeurProbable();
    test_valeurLePlus();
    return EXIT_SUCCESS;
}

/**
* \fn void test_longueur_mot()
* \brief Test de la fonction longueur_mot de PerudUtils
* \author Fran�ois
* \date 18/05
*/
void test_longueur_mot()
{
    char testIncorrect[2]="42";

    printf("\nTest de la fonction longueur_mot de PerudUtils\n\n");
    printf("Le resultat de la fonction avec le mot 'Coucou' est %d\n", longueur_mot("Coucou"));
    printf("Le resultat attendu est 6\n");
    printf("Le resultat de la fonction avec le mot 'Salut' est %d\n", longueur_mot("Salut"));
    printf("Le resultat attendu est 5\n");
    printf("Le resultat de la fonction avec le mot 'Catastrophique, ceci est bien trop long!' est %d\n", longueur_mot("Catastrophique, ceci est bien trop long!"));
    printf("Le resultat attendu est -1\n");
    printf("Le resultat de la fonction avec le mot 'Oups' est %d\n", longueur_mot("Oups"));
    printf("Le resultat attendu est 4\n");
    printf("Le resultat de la fonction avec la chaine {'4';'2'} est %d\n", longueur_mot(testIncorrect));
    printf("Le resultat attendu est  -1 \n");
}

/**
* \fn void test_d5()
* \brief Test de la fonction d5 de ia
* \author Fran�ois
* \date 18/05
*/
void test_d5()
{
    printf("\nTest de la fonction d5 de ia\n\n");
    int i;
    int comp=0;
    for(i=0;i<1000;i++)
    {
        if (d5() > 0 && d5() < 6)
        {
            comp++;
        }
    }
    printf("\nSur 1000 tirages, il y a %d resultats entre 1 et 5\n", comp);
}

/**
* \fn void test_nombreValeurProbable()
* \brief Test de la fonction nombreValeurProbable de ia
* \author Fran�ois
* \date 18/05
*/
void test_nombreValeurProbable()
{
    int test1[]= {0,2,1,2,0,0}, test2[]= {1,1,1,2,0,0}, test3[] = {0,0,0,1,0,1}, test4[]={0,2,1,2,0,0},test5[]={3,0,0,2,0,0};
    printf("\nTest de la fonction nombreValeurProbable de ia\n\n");
    printf("Le resultat de la fonction avec en parametres 2, 15, 5, [0,2,1,2,0,0] est %d\n", nombreValeurProbable(2, 15, 5, test1));
    printf("Le resultat attendu est 5\n");
    printf("Le resultat de la fonction avec en parametres 4, 20, 5, [1,1,1,2,0,0] est %d\n", nombreValeurProbable(4, 20, 5, test2));
    printf("Le resultat attendu est 8\n");
    printf("Le resultat de la fonction avec en parametres 1, 12, 2, [0,0,0,1,0,1] est %d\n", nombreValeurProbable(1, 12, 2, test3));
    printf("Le resultat attendu est 2\n");
    printf("Le resultat de la fonction avec en parametres 5, 15, 5, [0,2,1,2,0,0] est %d\n", nombreValeurProbable(5, 15, 5, test4));
    printf("Le resultat attendu est 3\n");
    printf("Le resultat de la fonction avec en parametres 1, 25, 5, [3,0,0,2,0,0] est %d\n", nombreValeurProbable(1, 25, 5, test5));
    printf("Le resultat attendu est 6\n");
}

/**
* \fn void test_valeurLePlus()
* \brief Test de la fonction valeurLePlus de ia
* \author Fran�ois
* \date 18/05
*/
void test_valeurLePlus()
{
    printf("\nTest de la fonction valeurLePlus de ia\n\n");
    int nombre = 0;
    int valeur = 0;
    int test1[]= {0,0,1,1,1,2}, test2[]= {1,0,2,1,1,0}, test3[] = {2,0,0,1,0,2}, test4[] = {1,1,1,1,1,0}, test5[] = {0,1,1,1,1,1};
    valeurLePlus(test1, &nombre, &valeur, 2, 15);
    printf("Le resultat de la fonction avec en parametres [0,0,1,1,1,2], 2, 15 est : %d %d\n", nombre, valeur);
    printf("Le resultat attendu est 2 6\n");
    valeurLePlus(test2, &nombre, &valeur, 5, 15);
    printf("Le resultat de la fonction avec en parametres [1,0,2,1,1,0], 5, 15 est : %d %d\n", nombre, valeur);
    printf("Le resultat attendu est 1 1\n");
    valeurLePlus(test3, &nombre, &valeur, 4, 15);
    printf("Le resultat de la fonction avec en parametres [2,0,0,1,0,2], 4, 15 est : %d %d\n", nombre, valeur);
    printf("Le resultat attendu est 4 6\n");
    valeurLePlus(test4, &nombre, &valeur, 3, 15);
    printf("Le resultat de la fonction avec en parametres [1,1,1,1,1,0], 3, 15 est : %d %d\n", nombre, valeur);
    printf("Le resultat attendu est 2 5\n");
    valeurLePlus(test5, &nombre, &valeur, 1, 15);
    printf("Le resultat de la fonction avec en parametres [0,1,1,1,1,1], 1, 15 est : %d %d\n", nombre, valeur);
    printf("Le resultat attendu est 1 6\n");
}
