#include "perudo.h"



int main() {
    int nb_de_joueurs;
    printf("Combien de joueurs ?\n");
    scanf("%d", &nb_de_joueurs);
    partie(nb_de_joueurs);
    return EXIT_SUCCESS;
}


void partie(int nb_de_joueurs) {
    Joueur joueurs[nb_de_joueurs];
    Booleen continuer=VRAI;
    int i;
    for (i=0;i<nb_de_joueurs;i++) {
        printf("Quel nom voulez-vous utiliser pour le joueur %d ?\n", i+1);
        scanf("%s", &joueurs[i].pseudo);
        }
    Booleen premier_tour = VRAI;
    while (continuer) {
        int i; int j; int k; int tmp; int joueur_actuel; int nb_de_des_max;
        Booleen tour_de_jeu = VRAI; Annonce annonce_precedente; Annonce annonce;
        if (premier_tour) {
            joueur_actuel=0;
            nb_de_des_max = nb_de_joueurs * 5;
            for (i=0;i<nb_de_joueurs;i++) {
                joueurs[i].nb_de_des = 5;
            }
        }
        srand(time(NULL));
        for (i=0;i<nb_de_joueurs;i++) {
            for (k=0;k<6;k++) { joueurs[i].des[k]=0;}
            for (j=0;j<joueurs[i].nb_de_des;j++) {
                tmp = rand()%6;
                for (k=0;k<6;k++) {
                    if (tmp==k) {joueurs[i].des[k]++;}
                }
            }
        }
        for (i=0;i<nb_de_joueurs;i++) {
        printf("\nDes du joueur %d :\n", i+1);
        for (k=0;k<6;k++) {
                printf("%d ", joueurs[i].des[k]);
            }
        }
        Booleen premiere_mise = VRAI;
        while (tour_de_jeu) {
            int m; int e; annonce.type = MISE; int somme = 0;
            if (!premiere_mise) {
                printf("\nMenteur ? (0/1)\n");
                scanf("%d", &m);
                if (m==1) { annonce.type = MENTEUR; }
                else if (m==0) {
                    printf("\nExact ? (0/1)\n");
                    scanf("%d", &e);
                    if (e==1) { annonce.type = EXACT; }
                    else if (e==0) { annonce.type = MISE; }}
                else { printf("Annonce incorrecte.\n"); }
            }
            switch (annonce.type) {
            case MISE: {
                Booleen annonce_incorrecte = VRAI;
                while (annonce_incorrecte) {
                printf("\nMise du joueur %d ?\n", joueur_actuel%nb_de_joueurs +1);
                scanf ("%d %d", &annonce.info.mise.nombre, &annonce.info.mise.de);
                if (premiere_mise) {
                    if (annonce.info.mise.de > 0 && annonce.info.mise.nombre > 0 && annonce.info.mise.de <7 && annonce.info.mise.nombre < nb_de_des_max) {
                    annonce_precedente.info.mise.nombre = annonce.info.mise.nombre;
                    annonce_precedente.info.mise.de = annonce.info.mise.de;
                    joueur_actuel++;
                    premiere_mise = FAUX;
                    annonce_incorrecte = FAUX;
                    }
                    else { printf("Annonce incorrecte.\n"); }
                }
                else {
                if (annonce.info.mise.de > 0 && annonce.info.mise.nombre > 0 && annonce.info.mise.de <7 && annonce.info.mise.nombre <= nb_de_des_max
                    && ((annonce.info.mise.nombre == annonce_precedente.info.mise.nombre && annonce.info.mise.de > annonce_precedente.info.mise.de && annonce_precedente.info.mise.de != 1)
                    || (annonce.info.mise.nombre > annonce_precedente.info.mise.nombre && annonce.info.mise.de == annonce_precedente.info.mise.de)
                    || (annonce.info.mise.de == 1 && annonce.info.mise.nombre >= (annonce_precedente.info.mise.nombre+1)/2)
                    || (annonce_precedente.info.mise.de == 1 && annonce.info.mise.nombre >= annonce_precedente.info.mise.nombre*2 +1))) {
                    annonce_precedente.info.mise.nombre = annonce.info.mise.nombre;
                    annonce_precedente.info.mise.de = annonce.info.mise.de;
                    joueur_actuel++;
                    annonce_incorrecte = FAUX;
                }
                else { printf("Annonce incorrecte.\n"); }
                }
                }
                break;
            }
            case MENTEUR: {
                for (i=0;i<nb_de_joueurs;i++) {
                    somme += joueurs[i].des[annonce_precedente.info.mise.de -1];
                }
                if (somme<annonce_precedente.info.mise.nombre) {
                    joueurs[(joueur_actuel-1)%nb_de_joueurs].nb_de_des--;
                    printf("Menteur !\n");
                    joueur_actuel = (joueur_actuel-1)%nb_de_joueurs;
                }
                else {
                    joueurs[joueur_actuel%nb_de_joueurs].nb_de_des--;
                    printf("\nEh non, ils y sont !\n");
                }
                nb_de_des_max--;
                tour_de_jeu = FAUX;
                break;
            }
            case EXACT: {
                for (i=0;i<nb_de_joueurs;i++) {
                    somme += joueurs[i].des[annonce_precedente.info.mise.de -1];
                }
                if (somme==annonce_precedente.info.mise.nombre) {
                    printf("\nGG, y'a que ca qui marche a ce jeu la.\n");
                    if (joueurs[joueur_actuel%nb_de_joueurs].nb_de_des <5) {
                        joueurs[joueur_actuel%nb_de_joueurs].nb_de_des++;
                        nb_de_des_max++;
                    }
                }
                else {
                    printf("\nDommage, ce n'est pas exact.\n");
                    joueurs[joueur_actuel%nb_de_joueurs].nb_de_des--;
                    nb_de_des_max--;
                }
                tour_de_jeu = FAUX;
                break;
            }
            default: {
                printf("Annonce incorrecte.\n");
            }

            }

        }
        premier_tour = FAUX;
        for (i=0;i<nb_de_joueurs;i++) {
            if (joueurs[i].nb_de_des==0) {
                continuer = FAUX;
                printf("Le joueur %d est elimine.", i+1);
            }
        }
        if (continuer) printf("\nNouveau tour de jeu :\n");
    }
}
