#include "perudo.h"



int main() {
    int nb_de_joueurs;
    printf("Combien de joueurs ?\n");
    scanf("%d", &nb_de_joueurs);
    partie(nb_de_joueurs); /* tout est géré là */
    return EXIT_SUCCESS;
}


void partie(int nb_de_joueurs) {
    Joueur joueurs[nb_de_joueurs]; /* les joueurs sont représentés par un tableau */
    Booleen continuer=VRAI; /* sert à déterminer si la partie est toujours en cours */
    int i;
    for (i=0;i<nb_de_joueurs;i++) {
        printf("Quel nom voulez-vous utiliser pour le joueur %d ?\n", i+1); /* pas vraiment utile pour l'instant */
        scanf("%s", &joueurs[i].pseudo);
        }
    Booleen premier_tour = VRAI; /* pour l'initialisation */
    while (continuer)  /* la boucle principale, jusqu'à élimination d'un joueur */
        {int i; int j; int k; int tmp; int joueur_actuel; int nb_de_des_max; /* initialisation des variables */
        Booleen tour_de_jeu = VRAI; Annonce annonce_precedente; Annonce annonce; /*encore d'autres */
        if (premier_tour) {   /* pour le premier tour, on fixe certains paramètres */
            joueur_actuel=0;
            nb_de_des_max = nb_de_joueurs * 5;
            for (i=0;i<nb_de_joueurs;i++) {
                joueurs[i].nb_de_des = 5;
            }
        }
        srand(time(NULL)); /*la seed pour le tirage des dés, srandom() sous Linux */
        for (i=0;i<nb_de_joueurs;i++) {
            for (k=0;k<6;k++) { joueurs[i].des[k]=0;}  /* tirage des dés */
            for (j=0;j<joueurs[i].nb_de_des;j++) {
                tmp = rand()%6;  /* random() sous Linux */
                for (k=0;k<6;k++) {
                    if (tmp==k) {joueurs[i].des[k]++;} /* on met les valeurs dans un tableau : la première case est le nombre de 1, la deuxième le nombre de 2, etc... */
                }
            }
        }
        for (i=0;i<nb_de_joueurs;i++) {
        printf("\nDes du joueur %d :\n", i+1);
        for (k=0;k<6;k++) {
                printf("%d ", joueurs[i].des[k]);  /* pour contrôler si les annonces et le résultat sont cohérents */
            }
        }
        Booleen premiere_mise = VRAI; /* encore pour la définition de certaines conditions */
        while (tour_de_jeu) {  /* boucle secondaire, jusqu'à perte ou gain d'un dé */
            int m; int e; annonce.type = MISE; int somme = 0; /* encore des variables */
            if (!premiere_mise) { /* on fait ça si on a déjà une mise avant, pour le jeu ce sera géré graphiquement */
                printf("\nMenteur ? (0/1)\n");
                scanf("%d", &m);
                if (m==1) { annonce.type = MENTEUR; } /* c'est ici qu'on détermine le type pour l'union */
                else if (m==0) {
                    printf("\nExact ? (0/1)\n");
                    scanf("%d", &e);
                    if (e==1) { annonce.type = EXACT; } /* ou ici */
                    else if (e==0) { annonce.type = MISE; }} /* ou là */
                else { printf("\nAnnonce incorrecte.\n"); }
            }
            switch (annonce.type) {  /* gestion des différentes annonces en fonction des cas */
            case MISE: {
                Booleen annonce_incorrecte = VRAI; /* pour s'assurer que le joueur fait une annonce correcte */
                while (annonce_incorrecte) {
                printf("\nMise du joueur %d ?\n", joueur_actuel%nb_de_joueurs +1); /* avec le modulo pour rester entre les différents joueurs */
                scanf ("%d %d", &annonce.info.mise.nombre, &annonce.info.mise.de);
                if (premiere_mise) { /* un peu spécial puisqu'il n'y a pas d'annonce précédente */
                    if (annonce.info.mise.de > 0 && annonce.info.mise.nombre > 0 && annonce.info.mise.de <7 && annonce.info.mise.nombre < nb_de_des_max) /* pleins de conditions */ {
                    annonce_precedente.info.mise.nombre = annonce.info.mise.nombre;
                    annonce_precedente.info.mise.de = annonce.info.mise.de;
                    joueur_actuel++; /* on passe au joueur suivant */
                    premiere_mise = FAUX; /* la première mise est faite */
                    annonce_incorrecte = FAUX; /* les conditions sont là pour ça */
                    }
                    else { printf("\nAnnonce incorrecte.\n"); }
                }
                else {
                if (annonce.info.mise.de > 0 && annonce.info.mise.nombre > 0 && annonce.info.mise.de <7 && annonce.info.mise.nombre <= nb_de_des_max
                    && ((annonce.info.mise.nombre == annonce_precedente.info.mise.nombre && annonce.info.mise.de > annonce_precedente.info.mise.de && annonce_precedente.info.mise.de != 1)
                    || (annonce.info.mise.nombre > annonce_precedente.info.mise.nombre && annonce.info.mise.de == annonce_precedente.info.mise.de)
                    || (annonce.info.mise.de == 1 && annonce.info.mise.nombre >= (annonce_precedente.info.mise.nombre+1)/2)
                    || (annonce_precedente.info.mise.de == 1 && annonce.info.mise.nombre >= annonce_precedente.info.mise.nombre*2 +1))) /* pleins pleins pleins de conditions */ {
                    annonce_precedente.info.mise.nombre = annonce.info.mise.nombre;
                    annonce_precedente.info.mise.de = annonce.info.mise.de;
                    joueur_actuel++;
                    annonce_incorrecte = FAUX;
                }
                else { printf("\nAnnonce incorrecte.\n"); }
                }
                }
                break;
            }
            case MENTEUR: {
                for (i=0;i<nb_de_joueurs;i++) {
                    somme += joueurs[i].des[annonce_precedente.info.mise.de -1]; /* on calcule pour vérifier si il y a mensonge ou pas */
                }
                if (somme<annonce_precedente.info.mise.nombre) {
                    joueurs[(joueur_actuel-1)%nb_de_joueurs].nb_de_des--; /* le joueur qui a fait la dernière annonce perd un dé */
                    printf("\nMenteur !\n"); /* c'est pas bien de mentir */
                    joueur_actuel = (joueur_actuel-1)%nb_de_joueurs; /* on recommence le tour suivant à partir du joueur précédent */
                }
                else {
                    joueurs[joueur_actuel%nb_de_joueurs].nb_de_des--; /* c'est le joueur actuel qui perd un dé, et c'est lui qui fait la première mise au tour suivant */
                    printf("\nEh non, le compte y est !\n");
                }
                nb_de_des_max--; /* globalement, il y a un dé en moins (merci Captain Obvious) */
                tour_de_jeu = FAUX; /* fin du tour de jeu */
                break;
            }
            case EXACT: {
                for (i=0;i<nb_de_joueurs;i++) {
                    somme += joueurs[i].des[annonce_precedente.info.mise.de -1]; /* pareil que précédemment */
                }
                if (somme==annonce_precedente.info.mise.nombre) {
                    printf("\nGG, y'a que ca qui marche a ce jeu la.\n"); /* on ne le dira jamais assez */
                    if (joueurs[joueur_actuel%nb_de_joueurs].nb_de_des <5) {
                        joueurs[joueur_actuel%nb_de_joueurs].nb_de_des++; /* le joueur regagne un dé, si il en avait moins de 5 */
                        nb_de_des_max++; /* ça fait augmenter le nombre de dés ! */
                    }
                }
                else {
                    printf("\nDommage, ce n'est pas exact.\n"); /* Règle 2 : c'est toujours exact, sauf quand ça l'est pas */
                    joueurs[joueur_actuel%nb_de_joueurs].nb_de_des--; /* cette fois le joueur perd un dé */
                    nb_de_des_max--; /* ...et du coup le nombre de dé total diminue */
                }
                tour_de_jeu = FAUX; /* fin du tour de jeu aussi */
                break;
            }
            default: {
                printf("\nAnnonce incorrecte.\n"); /* juste parce qu'il faut mettre un "default" */
            }

            } /* cette accolade est pour la fin du switch */

        } /* là on sort de la boucle secondaire */
        premier_tour = FAUX; /* à ce stade là le premier tour est fini */
        for (i=0;i<nb_de_joueurs;i++) {
            if (joueurs[i].nb_de_des==0) {
                continuer = FAUX; /* si un joueur tombe à 0 dé, la partie s'arrete */
                printf("\nLe joueur %d est elimine.", i+1);
            }
        }
        if (continuer) printf("\nNouveau tour de jeu :\n"); /* sinon on continue */
    } /* sortie de la boucle principale */
} /* fin de la procédure */
