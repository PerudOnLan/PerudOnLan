#include "PerudUtils.h"

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
