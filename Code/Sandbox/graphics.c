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
* \brief aspect de l'interface
* \param fond le fond d'écran sur lequel s'affiche les choses
* \param nbJoueurs le nombre de joueurs dans la partie
* \param gob, le tableau des gobelets
* \param positions, le tableau des positions des gobelets
* \author Dede
* \date 10/04
*/
int interface (SDL_Surface * fond, int nbJoueurs, SDL_Surface ** gob, SDL_Rect * positions)
{

SDL_Event event;

    // Définition des positions des gobelets
    SDL_Rect pos1; // pos2, pos3, pos4, pos5, pos6;

    pos1.x = ((fond->w)/2);
    pos1.y = ((fond)->h)/2;

/* Affichage de debug, qui marche */
SDL_FillRect(fond, NULL,VERT);
SDL_BlitSurface((gob[0]),NULL,fond,&pos1);
SDL_Flip(fond);
FE_WaitEvent(&event);

SDL_FillRect(fond, NULL,VERT);
SDL_BlitSurface((gob[1]),NULL,fond,&pos1);
SDL_Flip(fond);
FE_WaitEvent(&event);

SDL_FillRect(fond, NULL,VERT);
SDL_BlitSurface((gob[2]),NULL,fond,&pos1);
SDL_Flip(fond);
FE_WaitEvent(&event);

SDL_FillRect(fond, NULL,VERT);
SDL_BlitSurface((gob[3]),NULL,fond,&pos1);
SDL_Flip(fond);
FE_WaitEvent(&event);

SDL_FillRect(fond, NULL,VERT);
SDL_BlitSurface((gob[4]),NULL,fond,&pos1);
SDL_Flip(fond);
FE_WaitEvent(&event);

SDL_FillRect(fond, NULL,VERT);
SDL_BlitSurface((gob[5]),NULL,fond,&pos1);
SDL_Flip(fond);
FE_WaitEvent(&event);

int indice;
for (indice = 0; indice < nbJoueurs; indice ++)
{
    positions[indice].x = ((fond->w)/2);
    positions[indice].y = ((fond->h)/2);
}

return EXIT_SUCCESS;
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
    long timerDebut = SDL_GetTicks();
    long timerActuel = timerDebut;
    while(timerActuel - timerDebut < 3000)
    {

        SDL_FillRect(fond,NULL,VERT);
        for (i = 0; i<nbJoueurs; i++)
        {
            positions[i].x += (((random()%41)-20));           //on actualise
            positions[i].x = (positions[i].x)%((fond->w)-80);    //et on renormalise
            positions[i].y += (((random()%41)-20));
            positions[i].y = (positions[i].y)%((fond->h)-80);

            SDL_BlitSurface(gob[i],NULL,fond,&positions[i]);
        }
            SDL_Delay(40);
            timerActuel = SDL_GetTicks();
            SDL_Flip(fond);
    }

return EXIT_SUCCESS;
}
