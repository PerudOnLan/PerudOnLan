#include "PerudUtils.h"
/**
* \brief raccourci pour voir si un bouton est cliqué
* \param SDL_Event event, SDL_Surface * rectangle, SDL_Rect pos
* \return Booleen
* \author Dede
* \date 07/04
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

int longueur_mot(char * mot)
    {
        int i = 0;
        while (mot[i] != '\0')
        {
            i++;
        }
        return i;
    }


void saisir (SDL_Surface * champ, SDL_Rect pos, char * mot, int longueur_max, SDL_Surface * fond)
    {
        int longueur = 0;
        Booleen continuer = VRAI;
        SDL_Event event;
        // on définit la police et les oculeurs de police
        TTF_Font *policePerudo = NULL;
        policePerudo = TTF_OpenFont("../../Documents/policePerudo.ttf", 30);
        SDL_Color couleurBlanche = {255,255,255} ;
        SDL_Color couleurViolette = {150,0,150};

        //on définit ce qui est écrit
        SDL_Surface *texteEntre = NULL;

        //On dit ou écrire
        SDL_Rect positionEntre;
        positionEntre.x = (pos.x) + ((champ->w)/20);
        positionEntre.y = (pos.y) + ((champ->h)/10);

        while (continuer)
        {
            SDL_EnableKeyRepeat(500,50);
            FE_WaitEvent(&event);
            switch(event.type)
            {
                case SDL_QUIT:
                    continuer = FAUX;
                break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            continuer = FAUX;
                        break;
                        case SDLK_DELETE:
                            if (longueur > 0)
                            longueur --;
                            mot[longueur]='\0';
                        break;
                        case SDLK_BACKSPACE:
                            if (longueur > 0)
                            longueur --;
                            mot[longueur]='\0';
                        break;
                        case SDLK_RETURN:
                            mot[longueur]='\0';
                            continuer = FAUX;
                        break;
                        case SDLK_SPACE:
                        break;
                        default:
                        break;
                    }
                    if (longueur < longueur_max)
                    {
                        SDL_EnableUNICODE(SDL_ENABLE);
                        if ((event.key.keysym.unicode >= (Uint16)33) && (event.key.keysym.unicode <= (Uint16)122))
                        {
                            mot[longueur]=(char)event.key.keysym.unicode;
                            longueur ++;
                        }
                    }
                SDL_FillRect(champ,NULL,VIOLET);
                SDL_BlitSurface(champ, NULL, fond, &pos);
                SDL_Flip(fond);
                texteEntre = TTF_RenderText_Shaded(policePerudo,mot,couleurBlanche, couleurViolette);
                SDL_BlitSurface(texteEntre, NULL, fond, &positionEntre);
                SDL_Flip(fond);
                printf("%d\n", longueur);
                printf("%s\n", mot);
                break;
                default:
                break;
            }
        }
        SDL_FreeSurface(texteEntre);
        TTF_CloseFont(policePerudo);
    }

