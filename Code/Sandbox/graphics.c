/**
* \file graphics.c
* \brief code de la partie graphique propre au Perudo
* \author Dede
* \version 0.1
* \date 16/04
*
* Fichier destiné à accueillir la partie graphique du projet, c'est à dire la gestion de l'affichage...
*
*/


#include "graphics.h"



/**
* \fn int init_graphique (int nbJoueurs, SDL_Surface ** gob, SDL_Surface **des)
* \brief chargement de toutes les images
* \param nbJoueurs le nombre de joueurs dans la partie
* \param gob, le tableau des gobelets
* \param des, le tableau des dés de référence (le dé 1 à la bonne taille, de la bonne couleur)
* \author Dede
* \date 10/04
*/

int init_graphique (int nbJoueurs, SDL_Surface ** gob, SDL_Surface ** des)
{
    couleurDes couleurJoueur = rouge;
    int resolution = 0;
    int i, j;
    recupInfos(&resolution, &couleurJoueur);
    //Chargement des gobelets et du dé de référence pour chaque joueur
    for(i=0;i<nbJoueurs;i++)
    {
        gob[i] = NULL;
        des[i] = NULL;
    }

    char gobeletGrand[50]="../../Documents/Des/gobelet_grand_rouge";
    char gobeletMoyen[50]="../../Documents/Des/gobelet_moyen_rouge";
    char gobeletPetit[50]="../../Documents/Des/gobelet_petit_rouge";
    char deGrand[50]="../../Documents/Des/R1G.png";
    char deMoyen[50]="../../Documents/Des/R1M.png";
    char dePetit[50]="../../Documents/Des/R1P.png";

    char couleur[10];
    char lettreCouleur = 'R';

        /** Cette partie sert à changer la chaîne pour l'appel de IMG_load*/
        conversionCouleur(couleur, &lettreCouleur, couleurJoueur);
        for (j = 0; j< 7; j++)
        {
            gobeletGrand[j+34] = couleur[j];
        }

        deGrand[20] = lettreCouleur;

        /** et ici on charge effectivement les bonnes surfaces */
        if ((gob[0] = IMG_Load(gobeletGrand))==NULL)
            {
                fprintf(stderr,"impossible de charger l'image du gobelet 1 aka %s", gobeletGrand);
                gob[0] = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
            }
        if ((des[0] = IMG_Load(deGrand))==NULL)
            {
                fprintf(stderr,"impossible de charger l'image du de 1 aka %s", deGrand);
                des[0] = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
            }


    if (nbJoueurs < 5)  //on ne charge alors que des gobelets moyens et le grand
    {
        // On change de taille
        for (i=1; i<nbJoueurs; i++)     //Boucle de remplissage des surfaces gobelets
        {
            couleurJoueur ++;
            couleurJoueur = (couleurJoueur)%6;
            conversionCouleur(couleur, &lettreCouleur, couleurJoueur);
            for (j = 0;j<7; j++)
            {
                gobeletMoyen[j+34] = couleur[j];
            }
            deMoyen[20] = lettreCouleur;

            if ((gob[i] = IMG_Load(gobeletMoyen))==NULL)
            {
                fprintf(stderr,"impossible de charger l'image du gobelet %d aka %s \n", i, gobeletMoyen);
                gob[i] = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
            }
            if ((des[i] = IMG_Load(deMoyen))==NULL)
            {
                fprintf(stderr,"impossible de charger l'image du de 1 aka %s", deMoyen);
                des[i] = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
            }

        }
    }

    else
    {
        for (i=1; i<nbJoueurs; i++)     //Boucle de remplissage des surfaces gobelets
        {
            couleurJoueur ++;
            couleurJoueur = (couleurJoueur)%6;
            conversionCouleur(couleur, &lettreCouleur, couleurJoueur);

            if ( (i == 1) || ((nbJoueurs-i) == 1))  //on a besoin des images de taille moyenne
            {
                for (j = 0;j<7; j++)
                {
                    gobeletMoyen[j+34] = couleur[j];
                }
                deMoyen[20] = lettreCouleur;

                if ((gob[i] = IMG_Load(gobeletMoyen))==NULL)
                {
                    fprintf(stderr,"impossible de charger l'image du gobelet %d aka %s \n", i, gobeletMoyen);
                    gob[i] = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
                }
                if ((des[i] = IMG_Load(deMoyen))==NULL)
                {
                    fprintf(stderr,"impossible de charger l'image du de 1 aka %s", deMoyen);
                    des[i] = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
                }
            }
            else //on doit alors charger les petites images
            {
                for (j = 0;j<7; j++)
                {
                    gobeletPetit[j+34] = couleur[j];
                }
                dePetit[20] = lettreCouleur;

                if ((gob[i] = IMG_Load(gobeletPetit))==NULL)
                {
                    fprintf(stderr,"impossible de charger l'image du gobelet %d aka %s \n", i, gobeletPetit);
                    gob[i] = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
                }
                if ((des[i] = IMG_Load(dePetit))==NULL)
                {
                    fprintf(stderr,"impossible de charger l'image du de 1 aka %s", dePetit);
                    des[i] = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
                }
            }
        }
    }

return EXIT_SUCCESS;
}




/**
* \fn int interface (SDL_Surface * fond , int nbJoueurs, SDL_Surface ** gob)
* \brief aspect de l'interface, avec boutons cliquables
* \param fond le fond d'écran sur lequel s'affiche les choses
* \param nbJoueurs le nombre de joueurs dans la partie
* \param gob, le tableau des gobelets
* \param positions, le tableau des positions des gobelets
* \return annonce, l'annonce faite par le joueur
* \author Dede
* \date 10/04
*/
void interface (SDL_Surface * fond, int nbJoueurs, SDL_Surface ** gob, SDL_Rect * positions)
{
   TTF_Font *policePerudo = NULL;
    if ((policePerudo = TTF_OpenFont("../../Documents/policePerudo.ttf", (fond->w)/20))==NULL)
        {
         SDL_GetError();
         fprintf(stderr,"Quelque chose cloche... Avez vous la police policePerudo.ttf ?");
         exit(EXIT_FAILURE);
        }

    SDL_FillRect(fond, NULL,VERT);

    positions[0].x = (((fond->w)/2)-(((gob[0])->w)/2));
    positions[0].y = ((4*((fond->h)/5))-(((gob[0])->h)/2));
    SDL_BlitSurface((gob[0]),NULL,fond,&(positions[0]));

// affichage des gobelets
    switch(nbJoueurs)
    {
        case 2:
        positions[1].x = (((fond->w)/2)-(((gob[1])->w)/2));
        positions[1].y = (((fond->h)/4)-(((gob[1])->w)/2));
        SDL_BlitSurface((gob[1]),NULL,fond,&(positions[1]));

        break;

        case 3:
        positions[1].x = (5*((fond->w)/6)-(((gob[1])->w)/2));
        positions[1].y = (((fond->h)/4)-(((gob[1])->w)/2));
        SDL_BlitSurface((gob[1]),NULL,fond,&(positions[1]));


        positions[2].x = (((fond->w)/6)-(((gob[2])->w)/2));
        positions[2].y = (((fond->h)/4)-(((gob[2])->w)/2));
        SDL_BlitSurface((gob[2]),NULL,fond,&(positions[2]));

        break;

        case 4:
        positions[1].x = (5*((fond->w)/6)-(((gob[1])->w)/2));
        positions[1].y = (((fond->h)/2)-(((gob[1])->w)/2));
        SDL_BlitSurface((gob[1]),NULL,fond,&(positions[1]));


        positions[2].x = (((fond->w)/2)-(((gob[2])->w)/2));
        positions[2].y = (((fond->h)/6)-(((gob[2])->w)/2)) -50;
        SDL_BlitSurface((gob[2]),NULL,fond,&(positions[2]));


        positions[3].x = (((fond->w)/6)-(((gob[3])->w)/2));
        positions[3].y = (((fond->h)/2)-(((gob[3])->w)/2));
        SDL_BlitSurface((gob[3]),NULL,fond,&(positions[3]));

        break;

        case 5:
        positions[1].x = (5*((fond->w)/6)-(((gob[1])->w)/2));
        positions[1].y = (3*((fond->h)/5)-(((gob[1])->w)/2));
        SDL_BlitSurface((gob[1]),NULL,fond,&(positions[1]));


        positions[2].x = (5*((fond->w)/6)-(((gob[2])->w)/2));
        positions[2].y = (((fond->h)/5)-(((gob[2])->w)/2)) -50;
        SDL_BlitSurface((gob[2]),NULL,fond,&(positions[2]));


        positions[3].x = (((fond->w)/6)-(((gob[3])->w)/2));
        positions[3].y = (((fond->h)/5)-(((gob[3])->w)/2))-50;
        SDL_BlitSurface((gob[3]),NULL,fond,&(positions[3]));


        positions[4].x = (((fond->w)/6)-(((gob[4])->w)/2));
        positions[4].y = ((3*(fond->h)/5)-(((gob[4])->w)/2));
        SDL_BlitSurface((gob[4]),NULL,fond,&(positions[4]));

        break;

        case 6:
        positions[1].x = (5*((fond->w)/6)-(((gob[1])->w)/2));
        positions[1].y = (3*((fond->h)/5)-(((gob[1])->w)/2));
        SDL_BlitSurface((gob[1]),NULL,fond,&(positions[1]));


        positions[2].x = (5*((fond->w)/6)-(((gob[2])->w)/2));
        positions[2].y = (((fond->h)/5)-(((gob[2])->w)/2))+50;
        SDL_BlitSurface((gob[2]),NULL,fond,&(positions[2]));


        positions[3].x = (((fond->w)/2)-(((gob[3])->w)/2));
        positions[3].y = (((fond->h)/6)-(((gob[3])->w)/2)) -50;
        SDL_BlitSurface((gob[3]),NULL,fond,&(positions[3]));


        positions[4].x = (((fond->w)/6)-(((gob[4])->w)/2));
        positions[4].y = (((fond->h)/5)-(((gob[4])->w)/2))+50;
        SDL_BlitSurface((gob[4]),NULL,fond,&(positions[4]));


        positions[5].x = (((fond->w)/6)-(((gob[5])->w)/2));
        positions[5].y = ((3*(fond->h)/5)-(((gob[5])->w)/2));
        SDL_BlitSurface((gob[5]),NULL,fond,&(positions[5]));

        break;

        default:
        fprintf(stderr,"nombre de joueurs incorrects\n");
        break;
    }

    // Là on affiche
    SDL_Flip(fond);
}

/**
* \fn int melange (int nbJoueurs, SDL_Surface ** gob, SDL_Rect * positions)
* \brief animation de mélange
* \param nbJoueurs le nombre de joueurs dans la partie
* \param gob, le tableau des gobelets
* \param positions, le tableau des positions des gobelets
* \author Dede
* \date 10/04
*
* Après cette animation, il faut rappeler l'interface
*
*/

int melange (SDL_Surface * fond, int nbJoueurs, SDL_Surface ** gob, SDL_Rect * positions)
{
    int i;
    SDL_Rect pos[6];
    long timerDebut = SDL_GetTicks();
    long timerActuel = timerDebut;

    for (i = 0; i<nbJoueurs; i++)
    {
        pos[i]=positions[i];     //on sauvegarde les positions normales pour osciller autour de ça
    }
    while(timerActuel - timerDebut < 1000)
    {

        SDL_FillRect(fond,NULL,VERT);
        for (i = 0; i<nbJoueurs; i++)
        {
            pos[i].x = positions[i].x + (((random()%11)-5));           //on actualise
            pos[i].y = positions[i].y + (((random()%11)-5));
            SDL_BlitSurface(gob[i],NULL,fond,&pos[i]);
        }
            SDL_Delay(40);
            timerActuel = SDL_GetTicks();
            SDL_Flip(fond);
    }

return EXIT_SUCCESS;
}



int choixAnnonce(Annonce * annonce, SDL_Surface * fond, int nbJoueurs, SDL_Surface ** gob, SDL_Rect * positions)
{
    TTF_Font *policePerudo = NULL;
    if ((policePerudo = TTF_OpenFont("../../Documents/policePerudo.ttf", (fond->w)/20))==NULL)
        {
         SDL_GetError();
         fprintf(stderr,"Quelque chose cloche... Avez vous la police policePerudo.ttf ?");
         exit(EXIT_FAILURE);
        }
    SDL_Color couleurNoire = { 0,0,0 } ;
    SDL_Color couleurRouge = { 200,0,0};

    Booleen continuer = VRAI;
    annonce->type = ANNONCE_INVALIDE;
    SDL_Event event;

    SDL_Flip(fond);

   // position des boutons
    SDL_Surface * boutonMise;
    SDL_Surface * boutonMenteur;
    SDL_Surface * boutonExact;
    SDL_Rect positionMise, positionMenteur, positionExact;


    boutonMise = TTF_RenderText_Shaded(policePerudo,"MISE", couleurNoire, couleurRouge);
    positionMise.x = ((fond->w)/2) -(boutonMise->w/2);
    positionMise.y = ((((fond->h)/2))) - 6*(boutonMise->h/2);
    SDL_BlitSurface(boutonMise, NULL, fond, &positionMise);


    boutonMenteur = TTF_RenderText_Shaded(policePerudo,"MENTEUR", couleurNoire, couleurRouge);
    positionMenteur.x = ((fond->w)/2) -(boutonMenteur->w/2);
    positionMenteur.y = ((((fond->h)/2))) - 3*(boutonMenteur->h/2);
    SDL_BlitSurface(boutonMenteur, NULL, fond, &positionMenteur);


    boutonExact = TTF_RenderText_Shaded(policePerudo,"EXACT", couleurNoire, couleurRouge);
    positionExact.x = ((fond->w)/2) -(boutonExact->w/2);
    positionExact.y = ((((fond->h)/2)));
    SDL_BlitSurface(boutonExact, NULL, fond, &positionExact);

    SDL_Flip(fond);
    while(continuer)
        {
        FE_WaitEvent(&event);
        /**TODO Analyse réseau*/
        switch(event.type)
                {
                    case SDL_QUIT:
                        continuer = FAUX;
                    break;

                    case SDL_MOUSEBUTTONDOWN:
                        if(event.button.button==SDL_BUTTON_LEFT)
                        {
                            if (estDans(event,boutonMise,positionMise))
                            {
                                annonce->type = MISE;
                                demandeMise(annonce,fond);
                                continuer = FAUX;
                                 //demande de la mise
                                /** TODO */

                            }

                            if (estDans(event,boutonMenteur,positionMenteur))
                            {
                                annonce->type = MENTEUR;
                                annonce->info.menteur = VRAI;
                                continuer = FAUX;
                            }

                            if (estDans(event,boutonExact,positionExact))
                            {
                                annonce->type = EXACT;
                                annonce->info.exact = VRAI;
                                continuer = FAUX;
                            }
                        }
                    break;

                    default:
                    break;
                }
        }
    SDL_FreeSurface(boutonMise);
    SDL_FreeSurface(boutonMenteur);
    SDL_FreeSurface(boutonExact);
interface(fond, nbJoueurs,gob,positions);
return EXIT_SUCCESS;
}

int demandeMise(Annonce * annonce, SDL_Surface * fond)
{
    SDL_FillRect(fond,NULL,VERT);
    SDL_Color couleurViolette = {150,0,150};
    SDL_Color couleurBlanche = {255,255,255};
 //initialisation de la police de saisie
        TTF_Font *policeSaisie = NULL;
        if ((policeSaisie = TTF_OpenFont("../../Documents/arcadeclassic.ttf", (fond->w)/15))==NULL)
        {
            SDL_GetError();
            fprintf(stderr,"Quelque chose cloche... Avez vous la police arcadeclassic.ttf ?");
            exit(EXIT_FAILURE);
        }

       //On crée le champ de saisie
        SDL_Surface *champSaisie = NULL;
        champSaisie = SDL_CreateRGBSurface(SDL_HWSURFACE,(fond->w)/3,(fond->h)/8, 32, 0, 0, 0, 0);
        SDL_FillRect(champSaisie,NULL,VIOLET);
        SDL_Rect positionChamp;

        //on positionne le champ de saisie
        positionChamp.x = (fond->w)/4 - ((champSaisie->w)/2);
        positionChamp.y = (fond->h)/4 - ((champSaisie->h)/2);
        SDL_BlitSurface(champSaisie,NULL,fond,&positionChamp);


    SDL_Flip(fond);
    couleurDes couleur = rouge;
    char lettreCourante = 'R';
    recupInfos(NULL, &couleur);     // pour utiliser les dés de la bonne couleur pour l'affichage
    char deGrand[50]="../../Documents/Des/R1G.png";

    // on va charger les bonnes images
    conversionCouleur(NULL,&lettreCourante,couleur);
    deGrand[20] = lettreCourante;
    SDL_Surface *des[6], *outliner = NULL, *antiOutliner = NULL;
    SDL_Rect posDes[6], posOutliner;

    // Et on définit un outliner

    if ((outliner = IMG_Load("../../Documents/Des/outliner.png"))==NULL)
    {
        fprintf(stderr,"impossible de charger l'image du curseur");
        outliner = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
    }

    if ((antiOutliner = IMG_Load("../../Documents/Des/antiOutliner.png"))==NULL)
    {
        fprintf(stderr,"impossible de charger l'image réciproque du curseur");
        outliner = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
    }

    int i;
    for(i=0; i<6; i++)
    {
        lettreCourante = i+'1';
        deGrand[21] = lettreCourante;
        if ((des[i] = IMG_Load(deGrand))==NULL)
        {
            fprintf(stderr,"impossible de charger l'image du dé D%d", i);
            des[i] = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
        }

        if (i<3)                        //on affiche la colonne de gauche
        {
            posDes[i].x = 2*((fond->w)/3) - 80;
        }
        else                            //celle de droite
        {
            posDes[i].x = 5*((fond->w)/6) - 80;
        }

        if ((i%3)==0)                   //on affiche la première ligne
        {
            posDes[i].y = 150;
        }
        else if ((i%3)==1)              //la deuxième
        {
            posDes[i].y = 90+((fond->h)/3);
        }
        else if ((i%3)==2)              //la troisième
        {
            posDes[i].y = 30 + 2*((fond->h)/3);
        }

        SDL_BlitSurface(des[i],NULL,fond,&posDes[i]);
    }

    posOutliner.x = posDes[1].x - 10;
    posOutliner.y = posDes[1].y - 10;
    SDL_BlitSurface(outliner,NULL,fond,&posOutliner);

    SDL_Flip(fond);
SDL_Event event;
Booleen continuer = VRAI;
char tampon[10];
        while (continuer)
        {
            printf("abwaFE\n");
            FE_WaitEvent(&event);
            printf("%d\n", event.type);
            switch(event.type)
                {
                    case SDL_QUIT:
                        continuer = FAUX ;
                    break;

                    case SDL_KEYDOWN:
                        if (event.key.keysym.sym == SDLK_ESCAPE)
                        {
                            continuer = FAUX;
                        }
                        if (event.key.keysym.sym == SDLK_SPACE) // bouton neutre
                        {
                        }
                    break;

                    case SDL_MOUSEBUTTONDOWN:
                    printf("%d\n",event.button.button);
                    if(event.button.button==SDL_BUTTON_LEFT)
                    {
                        for (i=0; i<6; i++)
                        {
                            if (estDans(event,des[i],posDes[i]))
                            {
                                if(annonce->info.mise.de != i)
                                {
                                    annonce->info.mise.de = i;
                                    SDL_BlitSurface(antiOutliner,NULL,fond,&posOutliner);

                                    posOutliner.x = posDes[i].x - 10;
                                    posOutliner.y = posDes[i].y - 10;

                                    SDL_BlitSurface(outliner,NULL,fond,&posOutliner);
                                    SDL_Flip(fond);
                                }
                            }
                            if (estDans(event,champSaisie,positionChamp))
                            {
                                printf("abwa\n");
                                printf("wtf?\n");
                                saisir(champSaisie,positionChamp,VIOLET,policeSaisie,couleurBlanche,couleurViolette,tampon,2,fond);

                                printf("abwabwa\n");
                            }
                        }
                    }
                    break;
                    default:
                    break;
                }
        }
//sans oublier les free
for (i=0; i<6; i++)
{
    SDL_FreeSurface(des[i]);
}
SDL_FreeSurface(outliner);
SDL_FreeSurface(antiOutliner);
return EXIT_SUCCESS;
}
