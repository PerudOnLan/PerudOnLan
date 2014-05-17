/**
* \file PerudUtils.c
* \brief Fonctions utiles pour le projet
* \author Dede
* \version 0.2
* \date 09/04
*
* Diverses fonctions, majoritairement liées à la SDL, afin de nous simplifier la vie
*
*/


#include "PerudUtils.h"

/**
* \fn Booleen estDans (SDL_Event event, SDL_Surface * rectangle, SDL_Rect pos)
* \brief raccourci pour voir si un bouton est cliqué
* \param event l'évènement qui vient de se produire
* \param rectangle le rectangle dans lequel on teste la présence de l'évènement
* \param pos la position du coin en haut à gauche du rectangle
* \return Booleen - VRAI si l'évènement a eu lieu dans rectangle, FAUX sinon
* \author Dede
* \date 16/04
*/
Booleen estDans (SDL_Event event, SDL_Surface * rectangle, SDL_Rect pos)
{
    switch(event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    if (((event.button.x) > pos.x)&& ((event.button.x) < ((pos.x)+(rectangle->w)))
                        &&((event.button.y) > pos.y)&&((event.button.y)<((pos.y)+(rectangle->h))))
                    {
                        //On est dans le rectangle
                        return VRAI;
                    }
                    else
                    {
                        return FAUX;
                    }
               break;

               case SDL_MOUSEMOTION:
                    if (((event.motion.x) > pos.x)&& ((event.motion.x) < ((pos.x)+(rectangle->w)))
                        &&((event.motion.y) > pos.y)&&((event.motion.y)<((pos.y)+(rectangle->h))))
                    {
                        //On est dans le rectangle
                        return VRAI;
                    }
                    else
                    {
                        return FAUX;
                    }
               break;
               default:
                    {
                        fprintf(stderr,"Mauvais type d'évènement interprété : non localisable.");
                        return FAUX;
                    }
               break;

            }
}


/**
* \fn int longueur_mot(char * mot)
* \brief Longueur d'un mot
* \param mot La chaîne de caractères dont on veut évaluer la longueur
* \return -1 si mot ne contient pas \0 et n'est donc pas un vrai mot, sa longueur sinon
* \author Dede
* \date 16/04
*/
int longueur_mot(char * mot)
    {
        int i = 0;
        while (mot[i] != '\0' && i<TAILLE_MAX)
        {
            i++;
        }
        if (i<TAILLE_MAX)
        return i;
        else
        {
        fprintf(stderr,"l'objet %s n'est pas un mot valable", mot);
        return (-1);
        }
    }

/**
* \fn int saisir (SDL_Surface * champ, SDL_Rect pos, Uint32 couleurChamp, TTF_Font * police, SDL_Color couleurPolice, SDL_Color couleurFond, char * mot, int longueur_max, SDL_Surface * fond)
* \brief Permet de saisir du texte en interface graphique
* \param champ La surface de saisie
* \param pos La position du coin supérieur gauche de la surface de saisie
* \param couleurChamp La couleur du champ de saisie, format SDLMapRGB
* \param police Police de caractère utilisée pour la saisie
* \param couleurPolice La couleur de la police de saisie
* \param couleurFond couleur de fond de la saisie. Identique visuellement à la couleurChamp, mais au format SDL_Color
* \param mot La chaine de caractère à remplir
* \param longueur_max la longueur maximale de la saisie
* \param fond La surface qui sert de fond, comme dans tous les programmes qui ont besoin d'affichage
* \return EXIT_SUCCESS normalement ou EXIT_FAILURE si la saisie a été arrêtée en urgence
* \author Dede
* \date 16/04
*/
int saisir (SDL_Surface * champ, SDL_Rect pos, Uint32 couleurChamp, TTF_Font * police, SDL_Color couleurPolice, SDL_Color couleurFond, char * mot, int longueur_max, SDL_Surface * fond)
    {
        int longueur = 0;
        Booleen continuer = VRAI;
        SDL_Event event;
        //on définit ce qui est écrit
        SDL_Surface *texteEntre = NULL;

        //On dit ou écrire
        SDL_Rect positionEntre;
        positionEntre.x = (pos.x) + ((champ->w)/20);
        positionEntre.y = (pos.y) + ((champ->h)/10);

        //boucle principale, tant que rien n'a été saisie
        while (continuer||longueur==0)
        {
            SDL_EnableKeyRepeat(500,50);
            FE_WaitEvent(&event);
            switch(event.type)
            {
                case SDL_QUIT:
                    free(texteEntre);
                    return EXIT_FAILURE;
                break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:   //on force la sortie
                            free(texteEntre);
                            return EXIT_FAILURE;
                        break;
                        case SDLK_DELETE:   //on supprime le caractère précédent
                            if (longueur > 0)
                            longueur --;
                            mot[longueur]='\0';
                        break;
                        case SDLK_BACKSPACE:   //on supprime le caractère précédent de même
                            if (longueur > 0)
                            longueur --;
                            mot[longueur]='\0';
                        break;
                        case SDLK_RETURN:      //on valide la saisie, uniquement si la longueur est >0
                            if(longueur>0)
                            {
                                mot[longueur]='\0';
                                continuer = FAUX;
                            }
                            //on dégage le \n au casoù il ne serait pas consommé
                        break;
                        case SDLK_SPACE:       //l'espace ne sert à rien
                        break;
                        default:
                        break;
                    }
                    if (longueur < longueur_max)    //si on a encore de la place dans le mot
                    {
                        SDL_EnableUNICODE(SDL_ENABLE);  //on transforme la saisie en caractère si elle est présente en ASCII
                        if ((event.key.keysym.unicode >= (Uint16)33) && (event.key.keysym.unicode <= (Uint16)122))
                        {
                            mot[longueur]=(char)event.key.keysym.unicode;
                            longueur ++;
                        }
                    }
                    //On réaffiche le nouveau texte
                SDL_FillRect(champ,NULL,couleurChamp);
                SDL_BlitSurface(champ, NULL, fond, &pos);
                SDL_Flip(fond);

                texteEntre = TTF_RenderText_Shaded(police,mot,couleurPolice, couleurFond);
                SDL_BlitSurface(texteEntre, NULL, fond, &positionEntre);
                SDL_Flip(fond);
                /* Ca c'est du debug */
                printf("%d\n", longueur);
                printf("%s\n", mot);

                break;
                default:
                break;
            }
        }
        //on n'oublie pas de free à la fin
        SDL_FreeSurface(texteEntre);
        return EXIT_SUCCESS;
    }

/**
* \fn void recupInfos (int * resolution, couleurDes * couleur)
* \brief affecte les bonnes valeurs dans resolution et couleur
* \param &resolution l'adresse de la variable résolution
* \param &couleur l'adresse de la variable couleur
* \author Dede
* \date 3/05
*
* On a souvent besoin de récupérer les options que le joueur a choisies, d'où la création de cette fonction
*
*/
void recupInfos (int * resolution, couleurDes * couleur)
{
    FILE* fconfig = NULL;
    if ((fconfig = fopen("config.ini","r+"))==NULL)
    {
        perror("fopen");
        fprintf(stderr,"\nAttention, options personnalisees impossibles a charger ! Verifiez config.ini \n");
    }
    else
    {
        char tampon[10] = "";
        rewind(fconfig);
        fgets(tampon,5,fconfig); // On vide "res="
        (*resolution) = strtol((fgets(tampon,5,fconfig)),NULL,10); // on convertit le char en long
        fgets(tampon,7,fconfig); //on vide "color="
        (*couleur) = strtol((fgets(tampon,5,fconfig)),NULL,10); // Le chiffre donne directement la couleur, car couleurDes est un type énum
       //DEBUG fprintf(stdout,"abwa res = %d et couleur = %d\n",resolution,couleur);
    }
}

/**
* \fn void conversionCouleur (char * nom, char * lettreCouleur, couleurDes * couleur)
* \brief transforme l'entier couleurDes en une chaine de caractère
* \param nom la chaine de caractères à remplir
* \param &lettreCouleur l'adresse du caractère à changer
* \author Dede
* \date 3/05
*
* On a souvent besoin de récupérer les options que le joueur a choisies, d'où la création de cette fonction
*
*/

void conversionCouleur(char * nom, char * lettreCouleur, couleurDes couleur)
{
    switch (couleur)
    {
        case rouge:
            nom[0] = 'r';
            nom[1] = 'o';
            nom[2] = 'u';
            nom[3] = 'g';
            nom[4] = 'e';
            nom[5] = '\0';
        break;
        case vert:
            nom[0] = 'v';
            nom[1] = 'e';
            nom[2] = 'r';
            nom[3] = 't';
            nom[4] = '\0';
        break;
        case bleu :
            nom[0] = 'b';
            nom[1] = 'l';
            nom[2] = 'e';
            nom[3] = 'u';
            nom[4] = '\0';
        break;
        case jaune :
            nom[0] = 'j';
            nom[1] = 'a';
            nom[2] = 'u';
            nom[3] = 'n';
            nom[4] = 'e';
            nom[5] = '\0';
        break;
        case violet :
            nom[0] = 'v';
            nom[1] = 'i';
            nom[2] = 'o';
            nom[3] = 'l';
            nom[4] = 'e';
            nom[5] = 't';
            nom[6] = '\0';
        break;
        case orange :
            nom[0] = 'o';
            nom[1] = 'r';
            nom[2] = 'a';
            nom[3] = 'n';
            nom[4] = 'g';
            nom[5] = 'e';
            nom[6] = '\0';
        break;
    }
    if(lettreCouleur != NULL) //il est possible qu'on ne veuille pas de la lettre, auquel cas on appelle la fonction avec NULL en deuxième paramètre
    {
    switch(couleur)
        {
            case rouge:
            (*lettreCouleur) = 'R';
            break;
            case vert:
            (*lettreCouleur) = 'V';
            break;
            case bleu:
            (*lettreCouleur) = 'B';
            break;
            case jaune:
            (*lettreCouleur) = 'J';
            break;
            case orange:
            (*lettreCouleur) = 'O';
            break;
            case violet:
            (*lettreCouleur) = 'P';
            break;
        }
    }
}

