/**
* \file ia.c
* \brief code de l'ia
* \author Artus, François
* \version 0.2
* \date 08/04
*
* Fichier contenant le code de l'ia : son comportement lors d'une phase de jeu.
*
*/
#include "ia.h"

/**
* \fn int d5 ()
* \brief Lancement d'un de a 5 faces
* \author Artus
* \date 07/04
*/
int d5 () {

    srand(time(NULL)) ;
    int res = (rand()/RAND_MAX)*5+1 ;
    return res ;
}



/**
* \fn int nombreValeurProbable(int valeur, int nbT, int nbDe, int des[6])
* \brief Calcul d'un nombre probable des dés présents en jeu
* \param valeur la valeur du dé dont on veut connaitre le nombre probable en jeu
* \param nbT nombre total de dés en jeu
* \param nbDe nombre de dés de l'ia
* \param des[6] les valeurs des dés de l'ia
* \author Artus
* \date 07/04
*/

int nombreValeurProbable(int valeur, int nbT, int nbDe, int des[6]) {

    int res;
    if (valeur != 1){
        res = (int)((float)(nbT - nbDe)/3 + 0.5) + des[valeur-1] + des[0] ;
    }
    else{
        res = (int)((float)(nbT - nbDe)/6 + 0.5) + des[0] ;
    }
    return res ;
}


/**
* \fn int plusOuMoins (int nbT)
* \brief Renvoie un nombre qui modifie le comportement de l'ia et le rend moins prévisible
* \param nbT nombre total de dés en jeu
* \author Artus
* \date 07/04
*/
int plusOuMoins (int nbT) {

    if ( (nbT>0) && (nbT<=15) ) {

        int lancer = d5() ;

        switch (lancer) {

            case 1:
            case 2:
                return -1 ;
                break ;
            case 3:
                return 0 ;
                break ;
            case 4:
            case 5:
                return +1 ;
                break ;
        }
    }

    else if ( (nbT>15) && (nbT<=30)){

        int lancer = d5() ;

        switch (lancer) {

            case 1:
                return -2 ;
                break ;
            case 2:
                return -1 ;
                break ;
            case 3:
                return 0 ;
                break ;
            case 4:
                return +1 ;
                break ;
            case 5:
                return +2 ;
                break ;
        }
    }
    return 0;
}



/**
* \fn void valeurLePlus (int des[6], int *pNombre, int *pValeur, int valeur_precedente, int nb_de_des)
* \brief Ce que l'ia peut jouer en prenant le moins de risques
* \param des[6] les valeurs des dés de l'ia
* \param valeur_precedente la valeur qui a été pariée avant
* \param nb_de_des le nombre de dés en jeu
* \author Artus
* \date 07/04
*/
void valeurLePlus (int des[6], int *pNombre, int *pValeur, int valeur_precedente, int nb_de_des) {

    int i;
    for (i=2;i<6;i++) {

        if (des[i] + des[0] >= *pNombre) {
            *pNombre = des[i] + des[0];
            *pValeur = i+1 ;
        }
    }

    if (valeur_precedente > *pNombre || des[0]>=(nb_de_des/2 +1) )  {
        *pNombre = des[0];
        *pValeur = 1;
    }
}


/**
* \fn Joueur creerIa ()
* \brief Création d'une ia
* \author Artus
* \date 07/04
*/
Joueur creerIa () {

    srand(time(NULL));
    Joueur iA ;
    int i;
    int tmp;
    for (i=0;i<5;i++) {
        tmp = random()%6;
        iA.des[tmp]++;
    }
    iA.nb_de_des = 5;
    return iA;
}




/**
* \fn Annonce cerveauIA (Annonce annonce_precedente, int des[6])
* \brief Le cerveau de l'ia : son comportement quand elle doit faire une annonce
* \param annonce_precedente l'annonce du joueur précédent
* \param nb_de_des_max le nombre total de des dans la partie
* \param Joueur iA l'instance d'iA considérée
* \author Artus, François
* \date 08/04
*/
Annonce cerveauIA (Annonce annonce_precedente, int nb_de_des_max, Joueur iA) {

    if (annonce_precedente.type != MISE) {
        fprintf(stderr, "annonce erronee, on ne peut surrencherir que sur une mise");
        exit (EXIT_FAILURE);
    }
    int commentProbable = nombreValeurProbable(annonce_precedente.info.mise.de, nb_de_des_max, iA.nb_de_des, iA.des) - annonce_precedente.info.mise.nombre + plusOuMoins(nb_de_des_max) ;
    int lancer = d5() ;
    Annonce annonceIa ;
    int *pNombre = NULL;
    int *pValeur = NULL;

    annonceIa.type = ANNONCE_INVALIDE;

    switch (commentProbable) {

        case 3:
        case 2:
            switch (lancer) {
                case 1:
                case 2:
                    annonceIa.info.mise.de = annonce_precedente.info.mise.de;
                    annonceIa.info.mise.nombre = annonce_precedente.info.mise.nombre + 1;
                    break;
                case 3:
                case 4:
                    valeurLePlus(iA.des, pNombre, pValeur, annonce_precedente.info.mise.de, nb_de_des_max) ;
                    if (annonce_precedente.info.mise.de != 1 && *pValeur != 1) {    /*cas où mise precedente n'est pas paco, et notre meilleur jeu n'est pas paco.*/
                        annonceIa.info.mise.nombre = annonce_precedente.info.mise.nombre; /* on part sur notre valeur la plus probable (si supérieure à la pcédente, géré dans valeurLePlus */
                        annonceIa.info.mise.de = *pValeur;
                    }
                    else {
                        if (annonce_precedente.info.mise.de != 1) {/*cas ou mise precedente pas pacos*/
                        annonceIa.info.mise.nombre = (1 + annonce_precedente.info.mise.nombre)/2;
                        annonceIa.info.mise.de = *pValeur;
                        }
                        else {  /*cas ou mise precedente paco*/
                            if (*pValeur == 1) { /*cas ou meilleur jeu pacos*/
                                annonceIa.info.mise.de = annonce_precedente.info.mise.de;
                                annonceIa.info.mise.nombre = annonce_precedente.info.mise.nombre + 1;
                            }
                            else { /*cas ou meilleur jeu pas pacos*/
                                annonceIa.info.mise.de = *pValeur;
                                annonceIa.info.mise.nombre = annonce_precedente.info.mise.nombre*2 + 1;
                                }
                        }
                    }
                    break;
                case 5:
                     if (iA.des[annonce_precedente.info.mise.de-1] < annonce_precedente.info.mise.nombre) {
                        annonceIa.info.exact = VRAI;
                        break;
                    }
                    else {
                        annonceIa.info.mise.nombre = (1 + annonce_precedente.info.mise.nombre)/2;
                        annonceIa.info.mise.de = 1;
                        break;
                    }

            }

        case 1:
        case 0:
        case -1:
            switch (lancer) {
                case 1:
                    annonceIa.info.mise.de = annonce_precedente.info.mise.de;
                    annonceIa.info.mise.nombre = annonce_precedente.info.mise.nombre + 1;
                    return annonceIa;
                    break;
                case 2:
                case 3:
                case 4:
                    valeurLePlus(iA.des, pNombre, pValeur, annonce_precedente.info.mise.de, nb_de_des_max) ;
                    if (annonce_precedente.info.mise.de != 1 && *pValeur != 1) {    /*cas où mise precedente n'est pas paco, et notre meilleur jeu n'est pas paco.*/
                        annonceIa.info.mise.nombre = annonce_precedente.info.mise.nombre;
                        annonceIa.info.mise.de = *pValeur;
                    }
                    else {
                        if (annonce_precedente.info.mise.de != 1) {/*cas ou mise precedente pas pacos*/
                        annonceIa.info.mise.nombre = (1 + annonce_precedente.info.mise.nombre)/2;
                        annonceIa.info.mise.de = *pValeur;
                        }
                        else {  /*cas ou mise precedente paco*/
                            if (*pValeur == 1) { /*cas ou meilleur jeu pacos*/
                                annonceIa.info.mise.de = annonce_precedente.info.mise.de;
                                annonceIa.info.mise.nombre = annonce_precedente.info.mise.nombre + 1;
                            }
                            else { /*cas ou meilleur jeu pas pacos*/
                                annonceIa.info.mise.de = *pValeur;
                                annonceIa.info.mise.nombre = annonce_precedente.info.mise.nombre*2 + 1;
                                }
                        }
                    }
                    break;
                case 5:
                    if (iA.des[annonce_precedente.info.mise.de-1] < annonce_precedente.info.mise.nombre) {
                        annonceIa.info.exact = VRAI;
                        break;
                    }
                    else {
                        annonceIa.info.mise.nombre = (1 + annonce_precedente.info.mise.nombre)/2;
                        annonceIa.info.mise.de = 1;
                        break;
                    }
            }

        case -2:
        case -3:
            switch (lancer) {
                case 1:
                    annonceIa.info.mise.de = annonce_precedente.info.mise.de;
                    annonceIa.info.mise.nombre = annonce_precedente.info.mise.nombre + 1;
                    return annonceIa;
                    break;
                case 2:
                case 3:
                    if (iA.des[annonce_precedente.info.mise.de-1] < annonce_precedente.info.mise.nombre) {
                        annonceIa.info.menteur = VRAI;
                        break;
                    }
                    else {
                        annonceIa.info.mise.nombre = (1 + annonce_precedente.info.mise.nombre)/2;
                        annonceIa.info.mise.de = 1;
                        break;
                    }
                case 4:
                    valeurLePlus(iA.des, pNombre, pValeur, annonce_precedente.info.mise.de, nb_de_des_max) ;
                    if (annonce_precedente.info.mise.de != 1 && *pValeur != 1) {    /*cas où mise precedente n'est pas paco, et notre meilleur jeu n'est pas paco.*/
                        annonceIa.info.mise.nombre = annonce_precedente.info.mise.nombre;
                        annonceIa.info.mise.de = *pValeur;
                    }
                    else {
                        if (annonce_precedente.info.mise.de != 1) {/*cas ou mise precedente pas pacos*/
                        annonceIa.info.mise.nombre = (1 + annonce_precedente.info.mise.nombre)/2;
                        annonceIa.info.mise.de = *pValeur;
                        }
                        else {  /*cas ou mise precedente paco*/
                            if (*pValeur == 1) { /*cas ou meilleur jeu pacos*/
                                annonceIa.info.mise.de = annonce_precedente.info.mise.de;
                                annonceIa.info.mise.nombre = annonce_precedente.info.mise.nombre + 1;
                            }
                            else { /*cas ou meilleur jeu pas pacos*/
                                annonceIa.info.mise.de = *pValeur;
                                annonceIa.info.mise.nombre = annonce_precedente.info.mise.nombre*2 + 1;
                                }
                        }
                    }
                    break;
                case 5:
                    if (iA.des[annonce_precedente.info.mise.de-1] < annonce_precedente.info.mise.nombre) {
                        annonceIa.info.exact = VRAI;
                        break;
                    }
                    else {
                        annonceIa.info.mise.nombre = (1 + annonce_precedente.info.mise.nombre)/2;
                        annonceIa.info.mise.de = 1;
                        break;
                    }
            }

                default:
                // on gère les autres cas de façon générique après
                break;
    }

    if (commentProbable >= 4) {
        switch(lancer) {
            case 1:
            case 2:
                annonceIa.info.mise.de = annonce_precedente.info.mise.de;
                annonceIa.info.mise.nombre = annonce_precedente.info.mise.nombre + 2;
                return annonceIa;
                break;
            case 3:
            case 4:
                valeurLePlus(iA.des, pNombre, pValeur, annonce_precedente.info.mise.de, nb_de_des_max) ;
                    if (annonce_precedente.info.mise.de != 1 && *pValeur != 1) {    /*cas où mise precedente n'est pas paco, et notre meilleur jeu n'est pas paco.*/
                        annonceIa.info.mise.nombre = annonce_precedente.info.mise.nombre;
                        annonceIa.info.mise.de = *pValeur;
                    }
                    else {
                        if (annonce_precedente.info.mise.de != 1) {/*cas ou mise precedente pas pacos*/
                        annonceIa.info.mise.nombre = (1 + annonce_precedente.info.mise.nombre)/2;
                        annonceIa.info.mise.de = *pValeur;
                        }
                        else {  /*cas ou mise precedente paco*/
                            if (*pValeur == 1) { /*cas ou meilleur jeu pacos*/
                                annonceIa.info.mise.de = annonce_precedente.info.mise.de;
                                annonceIa.info.mise.nombre = annonce_precedente.info.mise.nombre + 1;
                            }
                            else { /*cas ou meilleur jeu pas pacos*/
                                annonceIa.info.mise.de = *pValeur;
                                annonceIa.info.mise.nombre = annonce_precedente.info.mise.nombre*2 + 1;
                                }
                        }
                    }
                    break;
                case 5:
                    annonceIa.info.mise.de = 1; /*on veut continuer sur les pacos de manière effrontee!!*/
                    if (annonce_precedente.info.mise.de == 1) {
                        annonceIa.info.mise.nombre = annonce_precedente.info.mise.nombre +2 ;
                    }
                    else {
                        annonceIa.info.mise.nombre = (1 + annonce_precedente.info.mise.nombre)/2 + 1;
                    }
                    break;
                default:
                //normalement inatteignable
                break;
        }
    }

    if (commentProbable <= -4) {
        switch (lancer) {
            case 1:
            case 2:
            case 3:
            case 4:
                if (iA.des[annonce_precedente.info.mise.de-1] < annonce_precedente.info.mise.nombre) {
                        annonceIa.info.menteur = VRAI;
                        break;
                    }
                    else {
                        annonceIa.info.mise.nombre = (1 + annonce_precedente.info.mise.nombre)/2;
                        annonceIa.info.mise.de = 1;
                        break;
                    }
            case 5:
                annonceIa.info.mise.de = annonce_precedente.info.mise.de;
                annonceIa.info.mise.nombre = annonce_precedente.info.mise.nombre + 1;
                return annonceIa;
                break;
            default:
            //inatteignable normalement
            break;
        }
    }
    return annonceIa;
}

























