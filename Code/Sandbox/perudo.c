#include "perudo.h"



int main() {
    int nb_de_joueurs;
    printf("Combien de joueurs ?\n");
    scanf("%d", &nb_de_joueurs);
    partie(nb_de_joueurs); /* tout est gere la */
    return EXIT_SUCCESS;
}


void partie(int nb_de_joueurs) {
    Joueur joueurs[nb_de_joueurs]; /* les joueurs sont representes par un tableau */
    Booleen continuer=VRAI; /* sert a determiner si la partie est toujours en cours */
    int i;
 /*   for (i=0;i<nb_de_joueurs;i++) {
        printf("Quel nom voulez-vous utiliser pour le joueur %d ?\n", i+1); // pas vraiment utile pour l'instant
        scanf("%s", (joueurs[i].pseudo));
        } */
    Booleen premier_tour = VRAI; /* pour l'initialisation */
    while (continuer)  /* la boucle principale, jusqu'a elimination d'un joueur */
        {int i; int j; int k; int tmp; int joueur_actuel; int nb_de_des_max; /* initialisation des variables */
        Booleen tour_de_jeu = VRAI; Annonce annonce_precedente; Annonce annonce; /*encore d'autres */
        if (premier_tour) {   /* pour le premier tour, on fixe certains parametres */
            joueur_actuel=0;
            nb_de_des_max = nb_de_joueurs * 5;
            for (i=0;i<nb_de_joueurs;i++) {
                joueurs[i].nb_de_des = 5;
            }
        }
        srandom(time(NULL)); /*la seed pour le tirage des des, srandom() sous Linux */
        for (i=0;i<nb_de_joueurs;i++) {
            for (k=0;k<6;k++) { joueurs[i].des[k]=0;}  /* tirage des des */
            for (j=0;j<joueurs[i].nb_de_des;j++) {
                tmp = random()%6;  /* random() sous Linux */
                for (k=0;k<6;k++) {
                    if (tmp==k) {joueurs[i].des[k]++;} /* on met les valeurs dans un tableau : la premiere case est le nombre de 1, la deuxieme le nombre de 2, etc... */
                }
            }
        }
        for (i=0;i<nb_de_joueurs;i++) {
        printf("\nDes du joueur %d :\n", i+1);
        for (k=0;k<6;k++) {
                printf("%d ", joueurs[i].des[k]);  /* pour controler si les annonces et le resultat sont coherents */
            }
        }
        Booleen premiere_mise = VRAI; /* encore pour la definition de certaines conditions */
        while (tour_de_jeu) {  /* boucle secondaire, jusqu'a perte ou gain d'un de */
            int m; int e; annonce.type = MISE; int somme = 0; /* encore des variables */
            if (!premiere_mise) { /* on fait ca si on a deja une mise avant, pour le jeu ce sera gere graphiquement */
                printf("\nMenteur ? (0/1)\n");
                scanf("%d", &m);
                if (m==1) { annonce.type = MENTEUR; } /* c'est ici qu'on determine le type pour l'union */
                else if (m==0) {
                    printf("\nExact ? (0/1)\n");
                    scanf("%d", &e);
                    if (e==1) { annonce.type = EXACT; } /* ou ici */
                    else if (e==0) { annonce.type = MISE; }} /* ou la */
                else { printf("\nAnnonce incorrecte.\n"); }
            }
            switch (annonce.type) {  /* gestion des differentes annonces en fonction des cas */
            case MISE: {
                Booleen annonce_incorrecte = VRAI; /* pour s'assurer que le joueur fait une annonce correcte */
                while (annonce_incorrecte) {
                printf("\nMise du joueur %d ?\n", joueur_actuel%nb_de_joueurs +1); /* avec le modulo pour rester entre les differents joueurs */
                scanf ("%d %d", &annonce.info.mise.nombre, &annonce.info.mise.de);
                if (premiere_mise) { /* un peu special puisqu'il n'y a pas d'annonce precedente */
                    if (annonce.info.mise.de > 0 && annonce.info.mise.nombre > 0 && annonce.info.mise.de <7 && annonce.info.mise.nombre < nb_de_des_max) /* pleins de conditions */ {
                    annonce_precedente.info.mise.nombre = annonce.info.mise.nombre;
                    annonce_precedente.info.mise.de = annonce.info.mise.de;
                    joueur_actuel++; /* on passe au joueur suivant */
                    premiere_mise = FAUX; /* la premiere mise est faite */
                    annonce_incorrecte = FAUX; /* les conditions sont la pour ca */
                    }
                    else { printf("\nAnnonce incorrecte.\n"); }
                }
                else {
                if (annonce.info.mise.de > 0 && annonce.info.mise.nombre > 0 && annonce.info.mise.de <7 && annonce.info.mise.nombre <= nb_de_des_max
                    && ((annonce.info.mise.nombre == annonce_precedente.info.mise.nombre && annonce.info.mise.de > annonce_precedente.info.mise.de && annonce_precedente.info.mise.de != 1)
                    || (annonce.info.mise.nombre > annonce_precedente.info.mise.nombre && annonce.info.mise.de == annonce_precedente.info.mise.de)
                    || (annonce.info.mise.de == 1 && annonce.info.mise.nombre >= (annonce_precedente.info.mise.nombre+1)/2 && annonce_precedente.info.mise.de != 1)
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
                    somme += joueurs[i].des[annonce_precedente.info.mise.de -1] + joueurs[i].des[0]; /* on calcule pour verifier si il y a mensonge ou pas */
                }
                if (somme<annonce_precedente.info.mise.nombre) {
                    joueurs[(joueur_actuel-1)%nb_de_joueurs].nb_de_des--; /* le joueur qui a fait la derniere annonce perd un de */
                    printf("\nMenteur !\n"); /* c'est pas bien de mentir */
                    joueur_actuel = (joueur_actuel-1)%nb_de_joueurs; /* on recommence le tour suivant a partir du joueur precedent */
                }
                else {
                    joueurs[joueur_actuel%nb_de_joueurs].nb_de_des--; /* c'est le joueur actuel qui perd un de, et c'est lui qui fait la premiere mise au tour suivant */
                    printf("\nEh non, le compte y est !\n");
                }
                nb_de_des_max--; /* globalement, il y a un de en moins (merci Captain Obvious) */
                tour_de_jeu = FAUX; /* fin du tour de jeu */
                break;
            }
            case EXACT: {
                for (i=0;i<nb_de_joueurs;i++) {
                    somme += joueurs[i].des[annonce_precedente.info.mise.de -1] + joueurs[i].des[0]; /* pareil que precedemment */
                }
                if (somme==annonce_precedente.info.mise.nombre) {
                    printf("\nGG, y'a que ca qui marche à ce jeu là.\n"); /* on ne le dira jamais assez */
                    if (joueurs[joueur_actuel%nb_de_joueurs].nb_de_des <5) {
                        joueurs[joueur_actuel%nb_de_joueurs].nb_de_des++; /* le joueur regagne un de, si il en avait moins de 5 */
                        nb_de_des_max++; /* ca fait augmenter le nombre de des ! */
                    }
                }
                else {
                    printf("\nDommage, ce n'est pas exact.\n"); /* Regle 2 : c'est toujours exact, sauf quand ca l'est pas */
                    joueurs[joueur_actuel%nb_de_joueurs].nb_de_des--; /* cette fois le joueur perd un de */
                    nb_de_des_max--; /* ...et du coup le nombre de des total diminue */
                }
                tour_de_jeu = FAUX; /* fin du tour de jeu aussi */
                break;
            }
            default: {
                printf("\nAnnonce incorrecte.\n"); /* juste parce qu'il faut mettre un "default" */
            }

            } /* cette accolade est pour la fin du switch */

        } /* la on sort de la boucle secondaire */
        premier_tour = FAUX; /* a ce stade la le premier tour est fini */
        for (i=0;i<nb_de_joueurs;i++) {
            if (joueurs[i].nb_de_des==0) {
                continuer = FAUX; /* si un joueur tombe a 0 de, la partie s'arrete */
                printf("\nLe joueur %d est elimine.", i+1);
            }
        }
        if (continuer) printf("\nNouveau tour de jeu :\n"); /* sinon on continue */
    } /* sortie de la boucle principale */
} /* fin de la procédure */
