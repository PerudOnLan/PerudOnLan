#include "ia.h"




int d5 () {

    srand(time(NULL)) ;
    int res = floor((rand()/RAND_MAX)*5)+1 ;
    return res ;
}




int nombreValeurProbable(int valeur, int nbT, int nbDe, int de[6]) {

    if (valeur != 1)
        int res = (int)((float)(nbT - nbDe)/3 + 0.5) + de[valeur-1] + de[0] ;
    else
        int res = ((int)((float)(nbT - nbDe)/6 + 0.5) + de[0] ;

    return res ;
}



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
}




void valeurLePlus (int de[6], int *pNombre, int *pValeur, int valeur_precedente) {

    *pNombre = de[1];
    *pValeur = 2;
    for (i=2;i<6;i++) {

        if (de[i] >= *pNombre) {
            *pNombre = de[i] + de[0];
            *pValeur = i+1 ;
        }
    }

    if (valeur_precedente > *pNombre || de[0]>= 3)  {
        *pNombre = de[0];
        *pValeur = 1;
    }
}





Annonce cerveauIA (Annonce annonce_precedente, int de[6]) {

    int nb_de_des_max ;
    Joueur iA ;
    int commentProbable = nombreValeurProbable(annonce_precedente.info.mise.de, nb_de_des_max, iA.nb_de_des, iA.des) - annonce_precedente.info.mise.nombre + plusOuMoins(nb_de_des_max) ;

    switch (commentProbable) {

        case 3:
        case 2:

        case 1:
        case 0:
        case -1:

        case -2:
        case -3:

    }

    if (commentProbable >= 4) {}

    if (commentProbable <= -4)
}

























