#include "perudo.h"



int main() {
    int nb_de_joueurs;
    printf("Combien de joueurs ?\n");
    scanf("%d", &nb_de_joueurs);
    partie(nb_de_joueurs);
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
        if (premier_tour) { joueur_actuel=0; nb_de_des_max = nb_de_joueurs * 5; }
        srand(time(NULL));
        for (i=0;i<nb_de_joueurs;i++) {
            joueurs[i].nb_de_des = 5;
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
            printf("\nMise du joueur %d ?\n", joueur_actuel%nb_de_joueurs +1);
            scanf ("%d %d", &annonce.info.mise.nombre, &annonce.info.mise.de);
            annonce.type = MISE;
            switch (annonce.type) {
            case MISE: {
                if (premiere_mise) {
                    if (annonce.info.mise.de > 0 && annonce.info.mise.nombre > 0 && annonce.info.mise.de <7 && annonce.info.mise.nombre < nb_de_des_max) {
                    annonce_precedente.info.mise.nombre = annonce.info.mise.nombre;
                    annonce_precedente.info.mise.de = annonce.info.mise.de;
                    joueur_actuel++;
                    premiere_mise = FAUX;
                    }
                    else { printf("Annonce incorrecte."); }
                }
                else {
                if (annonce.info.mise.de > 0 && annonce.info.mise.nombre > 0 && annonce.info.mise.de <7 && annonce.info.mise.nombre < nb_de_des_max
                    && ((annonce.info.mise.nombre == annonce_precedente.info.mise.nombre && annonce.info.mise.de > annonce_precedente.info.mise.de)
                    || (annonce.info.mise.nombre > annonce_precedente.info.mise.nombre && annonce.info.mise.de == annonce_precedente.info.mise.de)
                    || (annonce.info.mise.de == 1 && annonce.info.mise.nombre >= (annonce_precedente.info.mise.nombre+1)/2)
                    || (annonce_precedente.info.mise.de == 1 && annonce.info.mise.nombre >= annonce_precedente.info.mise.nombre*2 +1))) {
                    annonce_precedente.info.mise.nombre = annonce.info.mise.nombre;
                    annonce_precedente.info.mise.de = annonce.info.mise.de;
                    joueur_actuel++;
                }
                else { printf("Annonce incorrecte."); }
                }
                break;
            }

            }

        }
        premier_tour = FAUX;
    }
}
