/**
* \file jeu.c
* \brief code du jeu à proprement parler
* \author François, Dede
* \version 0.2
* \date 09/04
*
* Fichier destiné à accueillir la partie "jeu" du projet, c'est à dire la gestion des annonces, l'envoi de messages aux joueurs, et la gestion des callbacks.
*
*/


#include "jeu.h"

/**
* \fn int partie(SDL_Surface * fond)
* \brief Code de ce qu'il se passe en jeu
* \param fond le fond d'écran sur lequel s'affiche les choses
* \return EXIT_FAILURE ou EXIT_SUCCESS
* \author François
* \date 12/04
*/
int partie(SDL_Surface * fond) {

SDL_Color couleurNoire = { 0,0,0 } ;
SDL_Color couleurRouge = { 200,0,0};
SDL_Color couleurBlanche = {255,255,255};
SDL_Color couleurViolette = {150,0,150};

    //On remet le fond uniforme
    SDL_FillRect(fond,NULL,VERT);
    SDL_Flip(fond);

    //initialisation de l'aléatoire
    srandom(time(NULL)); // la seed pour le tirage des des

    //on récupère résolution et couleur des dés du joueur
    int resolution = 0;
    couleurDes couleur = rouge;

    recupInfos(&resolution, &couleur);

    //on crée les surfaces et polices dont on aura besoin
    SDL_Surface * texteAffiche = NULL;
    SDL_Rect positionTexte ;

        //initialisation de la police de saisie
        TTF_Font *policeSaisie = NULL;
        if ((policeSaisie = TTF_OpenFont("../../Documents/arcadeclassic.ttf", (fond->w)/15))==NULL)
        {
            SDL_GetError();
            fprintf(stderr,"Quelque chose cloche... Avez vous la police arcadeclassic.ttf ?");
            exit(EXIT_FAILURE);
        }

        //initialisation de la police d'affichage
        TTF_Font *policeAffichage = NULL;
        if ((policeAffichage = TTF_OpenFont("../../Documents/policePerudo.ttf", (fond->w)/15))==NULL)
        {
            SDL_GetError();
            fprintf(stderr,"Quelque chose cloche... Avez vous la police policePerudo.ttf ?");
            exit(EXIT_FAILURE);
        }

       //On crée le champ de saisie
        SDL_Surface *champSaisie = NULL;
        champSaisie = SDL_CreateRGBSurface(SDL_HWSURFACE,(fond->w)/2,(fond->h)/8, 32, 0, 0, 0, 0);
        SDL_FillRect(champSaisie,NULL,VIOLET);
        SDL_Rect positionChamp;

        //on positionne le champ de saisie
        positionChamp.x = (fond->w)/2 - ((champSaisie->w)/2);
        positionChamp.y = (fond->h)/2 - ((champSaisie->h)/2);
        SDL_BlitSurface(champSaisie,NULL,fond,&positionChamp);

        //on définit le nombre de joueurs
        int nb_de_joueurs;

        texteAffiche = TTF_RenderText_Solid(policeAffichage,"NOMBRE DE JOUEURS ?",couleurNoire);
        positionTexte.x = (fond->w)/2 - ((texteAffiche->w)/2);
        positionTexte.y = (positionChamp.y) - (texteAffiche->h);
        SDL_BlitSurface(texteAffiche,NULL,fond,&positionTexte);

    SDL_Flip(fond);

    //On effectue la saisie en en attendant une correcte
    do
    {
        char tampon[TAILLE_MAX+1]="";
        if ((saisir(champSaisie,positionChamp,VIOLET,policeSaisie,couleurBlanche,couleurViolette,tampon,1,fond)) == EXIT_FAILURE)
        {
            //ici, l'arrêt brutal de la  saisie signifie qu'on veut arrêter totalement le jeu
            return EXIT_FAILURE;
        }
        nb_de_joueurs= strtol(tampon,NULL,10);
    } while (nb_de_joueurs<2 || nb_de_joueurs>6) ;

    Joueur * joueurs=NULL; // les joueurs sont representes par un tableau
    if ((joueurs = malloc(nb_de_joueurs * (sizeof(Joueur))))==NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    Booleen continuer=VRAI; // sert a determiner si la partie est toujours en cours

    // maintenant on demande les noms des joueurs (temporaire, après on les récupérera)


    int i;
    for (i=0;i<nb_de_joueurs;i++)
    {
        //on "nettoie le pseudo"
        int j = 0;
        for(j=0;j<=TAILLE_MAX;j++)
        {
            joueurs[i].pseudo[j] = '\0';
        }
        char texte[16]="NOM DU JOUEUR X";
        texte[14] = ('0'+i);

        texteAffiche = TTF_RenderText_Solid(policeAffichage,texte,couleurNoire);
        positionTexte.x = (fond->w)/2 - ((texteAffiche->w)/2);

        SDL_FillRect(fond,NULL,VERT);
        SDL_Flip(fond);
        SDL_BlitSurface(champSaisie,NULL,fond,&positionChamp);
        SDL_BlitSurface(texteAffiche,NULL,fond,&positionTexte);
        SDL_Flip(fond);

        while ((longueur_mot(joueurs[i].pseudo))==0)
        {
            if ((saisir(champSaisie,positionChamp,VIOLET,policeSaisie,couleurBlanche,couleurViolette,joueurs[i].pseudo,TAILLE_MAX,fond))==EXIT_FAILURE)
            {
                //ici, l'arrêt brutal de la  saisie signifie qu'on veut arrêter totalement le jeu
                return EXIT_FAILURE;
            }

        }
    }

    Booleen premier_tour = VRAI; // pour l'initialisation
    while (continuer)  // la boucle principale, jusqu'a elimination d'un joueur
    {
        int i, j, k, tmp, joueur_actuel, nb_de_des_max; // initialisation des variables
        Booleen tour_de_jeu = VRAI; Annonce annonce_precedente, annonce; //encore d'autres
        if (premier_tour)
        {
            // pour le premier tour, on fixe certains parametres
            joueur_actuel=0;
            nb_de_des_max = nb_de_joueurs * 5;
            for (i=0;i<nb_de_joueurs;i++)
            {
                joueurs[i].nb_de_des = 5;
            }
        }
        for (i=0;i<nb_de_joueurs;i++)
        {
            for (k=0;k<6;k++)
            {
                joueurs[i].des[k]=0;
            }
            // tirage des des
            for (j=0;j<joueurs[i].nb_de_des;j++)
            {
                tmp = random()%6;
                for (k=0;k<6;k++)
                {
                    // on met les valeurs dans un tableau : la premiere case est le nombre de 1, la deuxieme le nombre de 2, etc...
                    if (tmp==k) {joueurs[i].des[k]++;}
                }
            }
        }
        for (i=0;i<nb_de_joueurs;i++)
        {
            fprintf(stdout, "\nDes du joueur %s :\n", joueurs[i].pseudo);
            for (k=0;k<6;k++)
            {
                fprintf(stdout, "%d ", joueurs[i].des[k]);  // pour controler si les annonces et le resultat sont coherents
            }
        }
        Booleen premiere_mise = VRAI; // encore pour la definition de certaines conditions

        // boucle secondaire, jusqu'a perte ou gain d'un de
        while (tour_de_jeu)
        {
            int m; int e; annonce.type = MISE; int somme = 0; // encore des variables

            // on fait ca si on a deja une mise avant, pour le jeu ce sera gere graphiquement
            if (!premiere_mise)
            {
                fprintf(stdout, "\nMenteur ? (0/1)\n");
                scanf("%d", &m);
                if (m==1)
                {
                    annonce.type = MENTEUR; // c'est ici qu'on determine le type pour l'union
                }
                else if (m==0)
                {
                    fprintf(stdout, "\nExact ? (0/1)\n");
                    scanf("%d", &e);
                    if (e==1)
                    {
                        annonce.type = EXACT;  // ou ici
                    }
                    else if (e==0)
                    {
                        annonce.type = MISE;  //ou la
                    }
                }
                else
                {
                    fprintf(stdout, "\nAnnonce incorrecte.\n");
                }
            }

            // gestion des differentes annonces en fonction des cas
            switch (annonce.type)
            {
                case MISE:
                {
                    Booleen annonce_incorrecte = VRAI; // pour s'assurer que le joueur fait une annonce correcte
                    while (annonce_incorrecte)
                    {
                        fprintf(stdout, "\nMise du joueur %s ?\n", joueurs[(joueur_actuel%nb_de_joueurs)].pseudo); // avec le modulo pour rester entre les differents joueurs
                        scanf ("%d %d", &annonce.info.mise.nombre, &annonce.info.mise.de);
                        if (premiere_mise) // un peu special puisqu'il n'y a pas d'annonce precedente
                        {
                            if (annonce.info.mise.de > 0 && annonce.info.mise.nombre > 0 && annonce.info.mise.de <7 && annonce.info.mise.nombre < nb_de_des_max) // pleins de conditions
                            {
                                annonce_precedente.info.mise.nombre = annonce.info.mise.nombre;
                                annonce_precedente.info.mise.de = annonce.info.mise.de;
                                fprintf(stdout, "Le joueur %s a mise : %d %d", joueurs[(joueur_actuel%nb_de_joueurs)].pseudo, annonce.info.mise.nombre, annonce.info.mise.de);
                                joueur_actuel++; // on passe au joueur suivant
                                premiere_mise = FAUX; // la premiere mise est faite
                                annonce_incorrecte = FAUX; // les conditions sont la pour ca
                            }
                            else
                            {
                                fprintf(stdout, "\nAnnonce incorrecte.\n");
                            }
                        }

                        else
                        {
                            if (annonce.info.mise.de > 0 && annonce.info.mise.nombre > 0 && annonce.info.mise.de <7 && annonce.info.mise.nombre <= nb_de_des_max
                                && ((annonce.info.mise.nombre == annonce_precedente.info.mise.nombre && annonce.info.mise.de > annonce_precedente.info.mise.de && annonce_precedente.info.mise.de != 1)
                                || (annonce.info.mise.nombre > annonce_precedente.info.mise.nombre && annonce.info.mise.de == annonce_precedente.info.mise.de)
                                || (annonce.info.mise.de == 1 && annonce.info.mise.nombre >= (annonce_precedente.info.mise.nombre+1)/2 && annonce_precedente.info.mise.de != 1)
                                || (annonce_precedente.info.mise.de == 1 && annonce.info.mise.nombre >= annonce_precedente.info.mise.nombre*2 +1))) // pleins pleins pleins de conditions
                            {
                                annonce_precedente.info.mise.nombre = annonce.info.mise.nombre;
                                annonce_precedente.info.mise.de = annonce.info.mise.de;
                                fprintf(stdout, "\nLe joueur %s a mise : %d %d\n", joueurs[(joueur_actuel%nb_de_joueurs)].pseudo, annonce.info.mise.nombre, annonce.info.mise.de);
                                joueur_actuel++;
                                annonce_incorrecte = FAUX;
                            }
                            else
                            {
                                fprintf(stdout, "\nAnnonce incorrecte.\n");
                            }
                        }
                    }
                    break;
                }
                case MENTEUR:
                {
                if (annonce_precedente.info.mise.de != 1) {
                for (i=0;i<nb_de_joueurs;i++) {
                    somme += joueurs[i].des[annonce_precedente.info.mise.de -1] + joueurs[i].des[0]; // on calcule pour verifier si il y a mensonge ou pas
                }
                }
                else {
                for (i=0;i<nb_de_joueurs;i++) {
                    somme += joueurs[i].des[0]; // on calcule pour verifier si il y a mensonge ou pas
                }
                }
                fprintf(stdout, "\nIl y a %d %d au total.\n", somme, annonce_precedente.info.mise.de);
                if (somme<annonce_precedente.info.mise.nombre) {
                    joueurs[(joueur_actuel-1)%nb_de_joueurs].nb_de_des--; // le joueur qui a fait la derniere annonce perd un de
                    fprintf(stdout, "\nMenteur !\n"); // c'est pas bien de mentir
                    joueur_actuel = (joueur_actuel-1)%nb_de_joueurs; // on recommence le tour suivant a partir du joueur precedent
                }
                else {
                    joueurs[joueur_actuel%nb_de_joueurs].nb_de_des--; // c'est le joueur actuel qui perd un de, et c'est lui qui fait la premiere mise au tour suivant
                    fprintf(stdout, "\nEh non, le compte y est !\n");
                }
                nb_de_des_max--; // globalement, il y a un de en moins (merci Captain Obvious)
                tour_de_jeu = FAUX; // fin du tour de jeu
                break;
            }
                case EXACT:
                {
                    if (annonce_precedente.info.mise.de != 1)
                    {
                        for (i=0;i<nb_de_joueurs;i++)
                        {
                            somme += joueurs[i].des[annonce_precedente.info.mise.de -1] + joueurs[i].des[0]; // on calcule pour verifier si il y a mensonge ou pas
                        }
                    }
                    else
                    {
                        for (i=0;i<nb_de_joueurs;i++)
                        {
                            somme += joueurs[i].des[0]; // on calcule pour verifier si il y a mensonge ou pas
                        }
                    }
                    fprintf(stdout, "\nIl y a %d %d au total.\n", somme, annonce_precedente.info.mise.de);
                    if (somme==annonce_precedente.info.mise.nombre)
                    {
                        fprintf(stdout, "\nGG, y'a que ca qui marche à ce jeu là.\n"); // on ne le dira jamais assez
                        if (joueurs[joueur_actuel%nb_de_joueurs].nb_de_des <5)
                        {
                            joueurs[joueur_actuel%nb_de_joueurs].nb_de_des++; // le joueur regagne un de, si il en avait moins de 5
                            nb_de_des_max++; // ca fait augmenter le nombre de des !
                        }
                    }
                    else
                    {
                        fprintf(stdout, "\nDommage, ce n'est pas exact.\n"); // Regle 2 : c'est toujours exact, sauf quand ca l'est pas
                        joueurs[joueur_actuel%nb_de_joueurs].nb_de_des--; // cette fois le joueur perd un de
                        nb_de_des_max--; // ...et du coup le nombre de des total diminue
                    }
                    tour_de_jeu = FAUX; // fin du tour de jeu aussi
                    break;
                }
                default:
                {
                    fprintf(stdout, "\nAnnonce incorrecte.\n"); // juste parce qu'il faut mettre un "default"
                }

            } // cette accolade est pour la fin du switch

        } // la on sort de la boucle secondaire
        premier_tour = FAUX; // a ce stade la le premier tour est fini
        for (i=0;i<nb_de_joueurs;i++)
        {
            if (joueurs[i].nb_de_des==0)
            {
                continuer = FAUX; // si un joueur tombe a 0 de, la partie s'arrete
                fprintf(stdout, "\nLe joueur %s est elimine.", joueurs[i].pseudo);
            }
        }
        if (continuer) fprintf(stdout, "\nNouveau tour de jeu :\n"); // sinon on continue
    } // sortie de la boucle principale
    free(joueurs);
    SDL_FreeSurface(champSaisie);
    SDL_FreeSurface(texteAffiche);
    TTF_CloseFont(policeSaisie);
    TTF_CloseFont(policeAffichage);
    return EXIT_SUCCESS;
} // fin de la procédure




/**
* \fn void klik(SDL_Surface * fond)
* \brief Code d'un mini-jeu
* \param fond le fond d'écran sur lequel s'affiche les choses
* \author Dede
* \date 5/04
*/

void klik(SDL_Surface * fond)
{

SDL_Color couleurNoire = { 0,0,0 } ;

    TTF_Font *policePerudo = NULL;
    if ((policePerudo = TTF_OpenFont("../../Documents/arcadeclassic.ttf", ((fond->w)/15)))==NULL)
    {
        SDL_GetError();
        fprintf(stderr,"Quelque chose cloche... Avez vous la police arcadeclassic.ttf ?");
        exit(EXIT_FAILURE);
    }
    SDL_Surface *R1 = NULL, *R2 = NULL, *R3 = NULL, *R4 = NULL, *R5 = NULL, *R6 = NULL;
    SDL_Rect posR1, posR2, posR3, posR4, posR5, posR6;

    //init dé rouge 1
    if ((R1 = IMG_Load("../../Documents/Des/R1.png"))==NULL)
    {
        fprintf(stderr,"impossible de charger l'image du dé R1");
        R1 = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
    }
    posR1.x = ((fond->w)/2)-40;
    posR1.y = ((fond->h)/2)-40;
    SDL_BlitSurface(R1,NULL,fond,&posR1);

    //init dé rouge 2
    if ((R2 = IMG_Load("../../Documents/Des/R2.png"))==NULL)
    {
        fprintf(stderr,"impossible de charger l'image du dé R2");
        R1 = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
    }
    posR2.x = ((fond->w)/2)-40;
    posR2.y = ((fond->h)/2)+80;
    SDL_BlitSurface(R2,NULL,fond,&posR2);

    //init dé rouge 3
    if ((R3 = IMG_Load("../../Documents/Des/R3.png"))==NULL)
    {
        fprintf(stderr,"impossible de charger l'image du dé R3");
        R1 = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
    }
    posR3.x = ((fond->w)/2)-40;
    posR3.y = ((fond->h)/2)+200;
    SDL_BlitSurface(R3,NULL,fond,&posR3);

    //init dé rouge 4
    if ((R4 = IMG_Load("../../Documents/Des/R4.png"))==NULL)
    {
        fprintf(stderr,"impossible de charger l'image du dé R4");
        R1 = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
    }
    posR4.x = ((fond->w)/2)+80;
    posR4.y = ((fond->h)/2)-40;
    SDL_BlitSurface(R4,NULL,fond,&posR4);

    //init dé rouge 5
    if ((R5 = IMG_Load("../../Documents/Des/R5.png"))==NULL)
    {
        fprintf(stderr,"impossible de charger l'image du dé R5");
        R1 = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
    }
    posR5.x = ((fond->w)/2)+80;
    posR5.y = ((fond->h)/2)+80;
    SDL_BlitSurface(R5,NULL,fond,&posR5);

    //init dé rouge 6
    if ((R6 = IMG_Load("../../Documents/Des/R6.png"))==NULL)
    {
        fprintf(stderr,"impossible de charger l'image du dé R6");
        R1 = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
    }
    posR6.x = ((fond->w)/2)+80;
    posR6.y = ((fond->h)/2)+200;
    SDL_BlitSurface(R6,NULL,fond,&posR6);


    long timerDebut = SDL_GetTicks();
    long timerActuel = timerDebut;
    char tempsRestant[] = "60";
    int indice = 0;
    int score = 0;

      //init du timer
    SDL_Surface *texteTimer = NULL;
    texteTimer = TTF_RenderText_Solid(policePerudo,tempsRestant, couleurNoire);
    SDL_Rect positionTimer;
    positionTimer.x = ((fond->w) -(texteTimer->w) -10);
    positionTimer.y = 10;

    SDL_BlitSurface(texteTimer, NULL, fond, &positionTimer);
    SDL_Flip(fond);

    Booleen continuer = VRAI;
    SDL_Event event;
    while (continuer && ((timerActuel-timerDebut)<60000))
    {
       for( indice=0 ; indice < 10 ; indice++)
       {
            FE_PollEvent(&event);
            switch(event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    if (estDans(event,R1,posR1))
                    {
                        score ++;   //on modifie la position des dés
                        posR1.x = random()%((fond->w)-80);
                        posR1.y = random()%((fond->h)-80);

                        posR2.x = random()%((fond->w)-80);
                        posR2.y = random()%((fond->h)-80);

                        posR3.x = random()%((fond->w)-80);
                        posR3.y = random()%((fond->h)-80);

                        posR4.x = random()%((fond->w)-80);
                        posR4.y = random()%((fond->h)-80);

                        posR5.x = random()%((fond->w)-80);
                        posR5.y = random()%((fond->h)-80);

                        posR6.x = random()%((fond->w)-80);
                        posR6.y = random()%((fond->h)-80);

                    }
                }
                break;
                case SDL_QUIT:
                    continuer = FAUX;
                break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                        continuer =FAUX;
                        break;
                        default:
                        break;
                    }
                break;
                default:
                break;
            }
        SDL_Delay(2);
        }
        SDL_FillRect(fond,NULL,VERT);
        posR1.x += (((random()%41)-20));           //on actualise
        posR1.x = (posR1.x)%((fond->w)-80);    //et on renormalise
        posR1.y += (((random()%41)-20));
        posR1.y = (posR1.y)%((fond->h)-80);

        posR2.x += (((random()%41)-20));           //on actualise
        posR2.x = (posR2.x)%((fond->w)-80);    //et on renormalise
        posR2.y += (((random()%41)-20));
        posR2.y = (posR2.y)%((fond->h)-80);

        posR3.x += (((random()%41)-20));           //on actualise
        posR3.x = (posR3.x)%((fond->w)-80);    //et on renormalise
        posR3.y += (((random()%41)-20));
        posR3.y = (posR3.y)%((fond->h)-80);

        posR4.x += (((random()%41)-20));           //on actualise
        posR4.x = (posR4.x)%((fond->w)-80);    //et on renormalise
        posR4.y += (((random()%41)-20));
        posR4.y = (posR4.y)%((fond->h)-80);

        posR5.x += (((random()%41)-20));           //on actualise
        posR5.x = (posR5.x)%((fond->w)-80);    //et on renormalise
        posR5.y += (((random()%41)-20));
        posR5.y = (posR5.y)%((fond->h)-80);

        posR6.x += (((random()%41)-20));           //on actualise
        posR6.x = (posR6.x)%((fond->w)-80);    //et on renormalise
        posR6.y += (((random()%41)-20));
        posR6.y = (posR6.y)%((fond->h)-80);

        SDL_BlitSurface(R1,NULL,fond,&posR1);
        SDL_BlitSurface(R2,NULL,fond,&posR2);
        SDL_BlitSurface(R3,NULL,fond,&posR3);
        SDL_BlitSurface(R4,NULL,fond,&posR4);
        SDL_BlitSurface(R5,NULL,fond,&posR5);
        SDL_BlitSurface(R6,NULL,fond,&posR6);
        SDL_Delay(20);
        timerActuel = SDL_GetTicks();

        tempsRestant[0]=(5-((timerActuel-timerDebut)/10000))+'0'; //les dizaines du timer
        tempsRestant[1]=(9-(((timerActuel-timerDebut)/1000))%10)+'0'; //les unités du timer

        texteTimer = TTF_RenderText_Solid(policePerudo,tempsRestant, couleurNoire);
        SDL_BlitSurface(texteTimer, NULL, fond, &positionTimer);
        SDL_Flip(fond);

    }
    SDL_FillRect(fond,NULL,VERT);
    SDL_Flip(fond);
    fprintf(stdout,"\nscore : %d\n",score);
    SDL_FreeSurface(R1);
    SDL_FreeSurface(R2);
    SDL_FreeSurface(R3);
    SDL_FreeSurface(R4);
    SDL_FreeSurface(R5);
    SDL_FreeSurface(R6);
    SDL_FreeSurface(texteTimer);
    TTF_CloseFont(policePerudo);
}

/**
* \fn int interface (int nbJoueurs)
* \brief aspect de l'interface
* \param fond le fond d'écran sur lequel s'affiche les choses
* \param nbJoueurs le nombre de joueurs dans la partie
* \author Dede
* \date 10/04
*/
int interface (SDL_Surface * fond, int nbJoueurs)
{
    couleurDes couleurJoueur = rouge;
    int resolution = 0;
    int i, j;
    recupInfos(&resolution, &couleurJoueur);
    //Chargement des gobelets
    SDL_Surface * gob[6];

    for(i=0;i<6;i++)
    {
        gob[i] = NULL;
    }

    char gobeletgrand[50]="../../Documents/Des/gobelet_grand_abwa";
    char gobeletmoyen[50]="../../Documents/Des/gobelet_moyen_rouge";
    char gobeletpetit[50]="../../Documents/Des/gobelet_petit_rouge";
    char couleur[10];

    if (nbJoueurs < 5)  //on ne charge alors que des gobelets moyens et le grand
    {
        // Cette partie sert à changer la chaîne pour l'appel de IMG_load
        conversionCouleur(couleur, couleurJoueur);
        for (j = 0; j< 7; j++)
        {
            gobeletgrand[j+34] = couleur[j];
        }
        if ((gob[0] = IMG_Load(gobeletgrand))==NULL)
            {
                fprintf(stderr,"impossible de charger l'image du gobelet 1 aka %s", gobeletgrand);
                gob[i] = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
            }

        // On change de taille
        for (i=1; i<nbJoueurs; i++)     //Boucle de remplissage des surfaces gobelets
        {
            couleurJoueur ++;
            couleurJoueur = (couleurJoueur)%6;
            conversionCouleur(couleur, couleurJoueur);
            for (j = 0;j<7; j++)
            {
                gobeletmoyen[j+34] = couleur[j];
            }
            if ((gob[i] = IMG_Load(gobeletmoyen))==NULL)
            {
                fprintf(stderr,"impossible de charger l'image du gobelet %d aka %s \n", i, gobeletmoyen);
                gob[i] = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
            }

        }

    }

    else
    {
    // Cette partie sert à changer la chaîne pour l'appel de IMG_load
        conversionCouleur(couleur, couleurJoueur);
        for (j = 0; j< 7; j++)
        {
            gobeletgrand[j+34] = couleur[j];
        }
        if ((gob[0] = IMG_Load(gobeletgrand))==NULL)
            {
                fprintf(stderr,"impossible de charger l'image du gobelet 1 aka %s", gobeletgrand);
                gob[i] = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
            }

        // On change de taille
        couleurJoueur ++;
        couleurJoueur = (couleurJoueur)%6;
        conversionCouleur(couleur, couleurJoueur);
        for (j = 0;j<7; j++)
        {
            gobeletmoyen[j+34] = couleur[j];
        }
        if ((gob[i] = IMG_Load(gobeletmoyen))==NULL)
        {
            fprintf(stderr,"impossible de charger l'image du gobelet %d aka %s \n", i, gobeletmoyen);
            gob[i] = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
        }

    /**
    TODO
    */
    }
/*    // Définition des positions des gobelets
    SDL_Rect pos1, pos2, pos3, pos4, pos5, pos6;

    pos1.x = ((fond->w)/2) -

    if (nbJoueurs < 5)
    {


    }
*/

FE_WaitEvent(NULL);
for (i=0; i<6; i++)
{
SDL_FreeSurface(gob[i]);
}

return EXIT_SUCCESS;
}
