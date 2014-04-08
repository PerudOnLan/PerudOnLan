#include "ia.h"

int main()
{
return 0;
}


int d5 () {

    srand(time(NULL)) ;
    int res = (rand()/RAND_MAX)*5+1 ;
    return res ;
}




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




void valeurLePlus (int des[6], int *pNombre, int *pValeur, int valeur_precedente, int nb_de_des) {

    *pNombre = des[1];
    *pValeur = 2;
    int i;
    for (i=2;i<6;i++) {

        if (des[i] >= *pNombre) {
            *pNombre = des[i] + des[0];
            *pValeur = i+1 ;
        }
    }

    if (valeur_precedente > *pNombre || des[0]>=(nb_de_des/2 +1) )  {
        *pNombre = des[0];
        *pValeur = 1;
    }
}





Annonce cerveauIA (Annonce annonce_precedente, int des[6]) {

    int nb_de_des_max ;
    Joueur iA ;
    int commentProbable = nombreValeurProbable(annonce_precedente.info.mise.de, nb_de_des_max, iA.nb_de_des, iA.des) - annonce_precedente.info.mise.nombre + plusOuMoins(nb_de_des_max) ;
    int lancer = d5() ;
    Annonce annonceIa ;
    int *pNombre;
    int *pValeur;

    switch (commentProbable) {

        case 3:
        case 2:

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
                    if (*pValeur != 1) {
                        annonceIa.info.mise.nombre = annonce_precedente.info.mise.nombre + 1;
                        annonceIa.info.mise.de = *pValeur;
                    }
                    else {
                        annonceIa.info.mise.nombre = (1 + annonce_precedente.info.mise.nombre)/2;
                        annonceIa.info.mise.de = *pValeur;
                    }
                    break;
                case 5:
                    if (iA.des[annonce_precedente.info.mise.de-1] < annonce_precedente.info.mise.nombre) {
                        annonceIa.info.exact.exact = VRAI;
                        break;
                    }
                    else {
                        annonceIa.info.mise.nombre = (1 + annonce_precedente.info.mise.nombre)/2;
                        annonceIa.info.mise.de = 1;
                        break;
                    }
            }

        //case -2:
       // case -3:

    }

   // if (commentProbable >= 4) {}

  //  if (commentProbable <= -4) {}
}

























