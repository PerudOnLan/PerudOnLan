/**
* \file menu.c
* \brief code du menu avant le jeu
* \author Dede
* \version 0.2
* \date 09/04
*
* Menu du jeu, disposant de plusieurs boutons : créer, rejoindre, options
*
*/

#include "menu.h"
/**
* \fn void menu(SDL_Surface * fond)
* \brief Menu du jeu, disposant de plusieurs boutons : créer, rejoindre, options
* \param fond Le fond de la fenêtre d'affichage, où on colle tout ce qu'il ya à afficher
* \author Dede
* \date 16/04
*
* Ce menu comporte 3 boutons visibles : Créer, permettant de se signaler comme hôte potentiel d'un partie; Rejoindre, pour se connecter à un hôte; et Options ,pour gérer divers paramètres du jeu
* De plus, il existe un bouton caché, en bas à gauche; permettant de rentrer des codes
*/
void menu(SDL_Surface * fond)
{

SDL_Color couleurNoire = { 0,0,0 } ;
SDL_Color couleurRouge = { 200,0,0};
SDL_Color couleurBlanche = {255,255,255};
SDL_Color couleurViolette = {150,0,150};

Booleen quitter = FAUX;
while(!quitter)
{
    Booleen continuer = VRAI;
    SDL_Event event;

    //On remet le fond uniforme
    SDL_FillRect(fond,NULL,VERT);
    SDL_Flip(fond);

    //chargement de la paco-police
    TTF_Font *policePerudo = NULL;
     if ((policePerudo = TTF_OpenFont("../../Documents/policePerudo.ttf", (fond->w)/15))==NULL)
        {
         SDL_GetError();
         fprintf(stderr,"Quelque chose cloche... Avez vous la police policePerudo.ttf ?");
         exit(EXIT_FAILURE);
        }

    //création des boutons:

    //Bouton créer : Surface

    SDL_Surface *boutonCreer = NULL;

    boutonCreer = SDL_CreateRGBSurface(SDL_HWSURFACE, ((fond->w)/2), ((fond->h)-200)/5, 32, 0, 0, 0, 0);
    SDL_FillRect(boutonCreer,NULL,ROUGE);
    SDL_Rect positionCreer;
    positionCreer.x = (fond->w)/4;
    positionCreer.y = 100;
    SDL_BlitSurface(boutonCreer,NULL,fond,&positionCreer);

    //Bouton créer : Texte

    SDL_Surface *texteCreer = NULL;
    texteCreer = TTF_RenderText_Shaded(policePerudo,"CREER", couleurNoire, couleurRouge);
    positionCreer.x = ((fond->w)/2) -(texteCreer->w / 2);
    positionCreer.y = (100+(((fond->h)-200)/10)) - (texteCreer->h /2);
    SDL_BlitSurface(texteCreer, NULL, fond, &positionCreer);
    //puis on rétablit la position initiale du bouton, afin de savoir où on clique
    positionCreer.x = (fond->w)/4;
    positionCreer.y = 100;

    //Bouton rejoindre: Surface

    SDL_Surface *boutonRejoindre = NULL;

    boutonRejoindre = SDL_CreateRGBSurface(SDL_HWSURFACE, (fond->w)/2,((fond->h)-200)/5 , 32, 0, 0, 0, 0);
    SDL_FillRect(boutonRejoindre,NULL,ROUGE);
    SDL_Rect positionRejoindre;
    positionRejoindre.x = (fond->w)/4;
    positionRejoindre.y = (100+(2*((fond->h)-200)/5));
    SDL_BlitSurface(boutonRejoindre,NULL,fond,&positionRejoindre);

    //Bouton rejoindre : Texte

    SDL_Surface *texteRejoindre = NULL;
    texteRejoindre = TTF_RenderText_Shaded(policePerudo,"REJOINDRE", couleurNoire, couleurRouge);
    positionRejoindre.x = ((fond->w)/2) -(texteRejoindre->w / 2);
    positionRejoindre.y = ((fond->h)/2) - (texteRejoindre->h /2);
    SDL_BlitSurface(texteRejoindre, NULL, fond, &positionRejoindre);
    //puis on rétablit la position initiale du bouton, afin de savoir où on clique
    positionRejoindre.x = (fond->w)/4;
    positionRejoindre.y = (100+(2*((fond->h)-200)/5));

    //Bouton options : Surface

    SDL_Surface *boutonOptions = NULL;

    boutonOptions = SDL_CreateRGBSurface(SDL_HWSURFACE, ((fond->w)/2), ((fond->h)-200)/5, 32, 0, 0, 0, 0);
    SDL_FillRect(boutonOptions,NULL,ROUGE);
    SDL_Rect positionOptions;
    positionOptions.x = (fond->w)/4;
    positionOptions.y = (100+(4*((fond->h)-200)/5));
    SDL_BlitSurface(boutonOptions,NULL,fond,&positionOptions);

    //Bouton options : Texte

    SDL_Surface *texteOptions = NULL;
    texteOptions = TTF_RenderText_Shaded(policePerudo,"OPTIONS", couleurNoire, couleurRouge);
    positionOptions.x = ((fond->w)/2) -(texteOptions->w / 2);
    positionOptions.y = (100+(9*((fond->h)-200)/10)) - (texteOptions->h /2);
    SDL_BlitSurface(texteOptions, NULL, fond, &positionOptions);
    //puis on rétablit la position initiale du bouton, afin de savoir où on clique
    positionOptions.x = (fond->w)/4;
    positionOptions.y = (100+(4*((fond->h)-200)/5));
    //Bouton cheats : Surface

    SDL_Surface *boutonCheats = NULL;

    boutonCheats = SDL_CreateRGBSurface(SDL_HWSURFACE,10, 10, 32, 0, 0, 0, 0);
    SDL_FillRect(boutonCheats,NULL,VERT);
    SDL_Rect positionCheats;
    positionCheats.x = 0;
    positionCheats.y = ((fond->h)-10);
    SDL_BlitSurface(boutonCheats,NULL,fond,&positionCheats);

    SDL_Flip(fond);
    //boucle principale

    while (continuer)
    {
        FE_WaitEvent(&event);
        switch(event.type)
            {
                case SDL_QUIT:
                    continuer = FAUX ;
                    quitter = VRAI;
                break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                        continuer = FAUX;
                        quitter = VRAI;
                        break;
                        case SDLK_c:
                         //début du jeu
                        partie(fond);
                        continuer = FAUX;
                        break;
                        case SDLK_r:
                        continuer = FAUX;
                        quitter = VRAI;
                        break;
                        case SDLK_o:
                        options(fond);
                        continuer=FAUX;
                        break;
                        default:
                        break;
                    }

                break;
                case SDL_MOUSEBUTTONDOWN:
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    if (estDans(event,boutonCreer,positionCreer))
                    {
                     //début du jeu
                       if((partie(fond))==EXIT_FAILURE)
                       {
                            // il y a eu un souci dans la partie, ce n'est pas grave, on ramène juste au menu, en le signalant
                            fprintf(stderr,"attention, il y a eu une erreur dans la partie !");
                       }
                        continuer = FAUX;
                    }
                    if (estDans(event,boutonRejoindre,positionRejoindre))
                    {
                        continuer = FAUX;
                        quitter = VRAI;
                    }
                    if  (estDans(event,boutonOptions,positionOptions))
                    {
                        options(fond);
                        continuer=FAUX;
                     }
                     if  (estDans(event,boutonCheats,positionCheats))
                    {
                    char saisie[11]= "          ";

                    //Définition de la surface de saisie
                    SDL_Surface *champSaisie = NULL;
                    champSaisie = SDL_CreateRGBSurface(SDL_HWSURFACE,320, 50, 32, 0, 0, 0, 0);
                    SDL_FillRect(champSaisie,NULL,VIOLET);
                    SDL_Rect positionChamp;
                    positionChamp.x = 0;
                    positionChamp.y = 0;
                    SDL_BlitSurface(champSaisie,NULL,fond,&positionChamp);
                    SDL_Flip(fond);

                    // on définit la police et les couleurs de police de saisie
                    TTF_Font *policeSaisie = NULL;
                    if ((policeSaisie = TTF_OpenFont("../../Documents/arcadeclassic.ttf", 30))==NULL)
                    {
                        SDL_GetError();
                        fprintf(stderr,"Quelque chose cloche... Avez vous la police arcadeclassic.ttf ?");
                        exit(EXIT_FAILURE);
                    }
                    //maintenant on lance la saisie
                    if ((saisir(champSaisie,positionChamp,VIOLET,policeSaisie,couleurBlanche,couleurViolette,saisie,10,fond)) == EXIT_FAILURE)
                    {
                        //Ici ce n'est pas grave si la saisie échoue, on ne fait rien
                    }
                    else
                    {
                    //on compare le code entré auw cheats valables
                    if(strcasecmp(saisie,"KLIKLEPACO")==0)
                        {
                        klik(fond);
                        }
                    }
                    //On remet le champ de cheat normal
                    SDL_FillRect(champSaisie,NULL,VERT);
                    SDL_BlitSurface(champSaisie,NULL,fond,&positionChamp);
                    SDL_Flip(fond);
                    SDL_FreeSurface(champSaisie);
                    continuer =FAUX;
                    TTF_CloseFont(policeSaisie);
                    }
                }
                break;
            }
    }
//On libère tout ce que l'on a alloué
 TTF_CloseFont(policePerudo);
 SDL_FreeSurface(boutonCreer);
 SDL_FreeSurface(texteCreer);
 SDL_FreeSurface(boutonRejoindre);
 SDL_FreeSurface(texteRejoindre);
 SDL_FreeSurface(boutonOptions);
 SDL_FreeSurface(texteOptions);
 SDL_FreeSurface(boutonCheats);
 }
}

/** \fn void options(SDL_Surface *fond)
* \param fond Le fond d'écran pour affichage
* \brief Le sous-menu d'options
*
* Ce sous-menu permet de paramétrer plusieurs options du jeu, en passant par le fichier config; comme la résolution ou la couleur de ses dés
*
*/

void options(SDL_Surface * fond)
{

SDL_Color couleurNoire = { 0,0,0 } ;
SDL_Color couleurBlanche = {255,255,255};


    int resolution = 0;
    couleurDes couleur = rouge;

    // on récupère les infos nécessaires
    recupInfos (& resolution, &couleur);

    Booleen continuer = VRAI, affichageChange, resolutionChange;
    SDL_Event event;
    //On ouvre le fichier de config pour pouvoir ensuite el modifier
    FILE* fconfig = NULL;
    if ((fconfig = fopen("config.ini","r+"))==NULL)
    {
        perror("fopen");
        fprintf(stderr,"\nAttention, options personnalisees impossibles a charger ! Verifiez config.ini \n");
        exit(EXIT_FAILURE);
    }

 //Grosse boucle d'affichage, au cas où la résolution change et où il faudrait tout rafficher

 do {
    resolutionChange = FAUX;

    //On remet le fond uniforme
    SDL_FillRect(fond,NULL,VERT);
    SDL_Flip(fond);

       //chargement de la paco-police
    TTF_Font *policePerudo = NULL;
  if ((policePerudo = TTF_OpenFont("../../Documents/arcadeclassic.ttf", ((fond->w)/15)))==NULL)
    {
        SDL_GetError();
        fprintf(stderr,"Quelque chose cloche... Avez vous la police arcadeclassic.ttf ?");
        exit(EXIT_FAILURE);
    }

    //Texte "Résolution"
    SDL_Rect positionTexte;
    positionTexte.x = (fond->w)/6 - 80;
    positionTexte.y = 50;

    SDL_Surface *texteResolution = NULL;
    texteResolution = TTF_RenderText_Solid(policePerudo,"RESOLUTION", couleurNoire);
    SDL_BlitSurface(texteResolution, NULL, fond, &positionTexte);

    //Texte "Couleur"
    positionTexte.x = 2*(fond->w)/3 - 80;
    positionTexte.y = 50;

    SDL_Surface *texteCouleur = NULL;
    texteCouleur = TTF_RenderText_Solid(policePerudo,"COULEUR", couleurNoire);
    SDL_BlitSurface(texteCouleur, NULL, fond, &positionTexte);


    //On s'occupe maintenant de la couleur des dés
    SDL_Surface *R1 = NULL, *V1 = NULL, *B1 = NULL, *J1 = NULL, *P1 = NULL, *O1 = NULL, *outliner = NULL, *antiOutliner = NULL;
    SDL_Rect posR1, posV1, posB1, posJ1, posP1, posO1, posOutliner;

    //affichage dé rouge 1
    if ((R1 = IMG_Load("../../Documents/Des/R1.png"))==NULL)
    {
        fprintf(stderr,"impossible de charger l'image du dé R1");
        R1 = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
    }
    posR1.x = 2*((fond->w)/3) - 80;
    posR1.y = 150;
    SDL_BlitSurface(R1,NULL,fond,&posR1);

    //affichage dé vert 1
    if ((V1 = IMG_Load("../../Documents/Des/V1.png"))==NULL)
    {
        fprintf(stderr,"impossible de charger l'image du dé V1");
        V1 = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
    }
    posV1.x = 2*((fond->w)/3) - 80;
    posV1.y = 90+((fond->h)/3);
    SDL_BlitSurface(V1,NULL,fond,&posV1);

    //affichage dé bleu 1
    if ((B1 = IMG_Load("../../Documents/Des/B1.png"))==NULL)
    {
        fprintf(stderr,"impossible de charger l'image du dé B1");
        B1 = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
    }
    posB1.x = 2*((fond->w)/3) - 80;
    posB1.y = 30 + 2*((fond->h)/3);
    SDL_BlitSurface(B1,NULL,fond,&posB1);

    //affichage dé jaune 1
    if ((J1 = IMG_Load("../../Documents/Des/J1.png"))==NULL)
    {
        fprintf(stderr,"impossible de charger l'image du dé J1");
        J1 = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
    }
    posJ1.x = 5*((fond->w)/6) - 80;
    posJ1.y = 150;
    SDL_BlitSurface(J1,NULL,fond,&posJ1);

    //affichage dé violet 1
    if ((P1 = IMG_Load("../../Documents/Des/P1.png"))==NULL)
    {
        fprintf(stderr,"impossible de charger l'image du dé P1");
        P1 = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
    }
    posP1.x = 5*((fond->w)/6) - 80;
    posP1.y = 90+((fond->h)/3);
    SDL_BlitSurface(P1,NULL,fond,&posP1);

    //affichage dé orange 1
    if ((O1 = IMG_Load("../../Documents/Des/O1.png"))==NULL)
    {
        fprintf(stderr,"impossible de charger l'image du dé O1");
        O1 = IMG_Load("../../Documents/Erreur_graphique.png") ; //On charge une image quand même pour indiquer que quelque chose cloche
    }
    posO1.x = 5*((fond->w)/6) - 80;
    posO1.y = 30 + 2*((fond->h)/3);
    SDL_BlitSurface(O1,NULL,fond,&posO1);

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

    posOutliner.x = posR1.x - 10;
    posOutliner.y = posR1.y - 10;
    //On définit la position des textes, qui ne changera pas, puisque la résolution ne change qu'après redémarrage
    SDL_Rect position640;
    position640.x = (fond->w)/6 - 80;
    position640.y = 150;

    SDL_Rect position800;
    position800.x = (fond->w)/6 - 80;
    position800.y = 90+((fond->h)/3);

    SDL_Rect position1280;
    position1280.x = (fond->w)/6 - 80;
    position1280.y = 30 + 2*((fond->h)/3);

    // on va définir une boucle d'affichage
    do {


        // on repasse la variable de boucle à "FAUX"
        affichageChange = FAUX;

        //On s'occupe des résolutions
        // 640*480
        SDL_Surface *texte640 = NULL;
        if (resolution==0)      //on change la couleur de la résolution déjà choisie
        texte640 = TTF_RenderText_Solid(policePerudo,"640x480", couleurBlanche);
        else
        texte640 = TTF_RenderText_Solid(policePerudo,"640x480", couleurNoire);

        SDL_BlitSurface(texte640, NULL, fond, &position640);

        //800*600
        //Texte
        SDL_Surface *texte800 = NULL;
        if (resolution==1)      //on change la couleur de la résolution déjà choisie
        texte800 = TTF_RenderText_Solid(policePerudo,"800x600", couleurBlanche);
        else
        texte800 = TTF_RenderText_Solid(policePerudo,"800x600", couleurNoire);

        SDL_BlitSurface(texte800, NULL, fond, &position800);

        //1280*960
        //Texte
        SDL_Surface *texte1280 = NULL;
        if (resolution==2)      //on change la couleur de la résolution déjà choisie
        texte1280 = TTF_RenderText_Solid(policePerudo,"1280x1024", couleurBlanche);
        else
        texte1280 = TTF_RenderText_Solid(policePerudo,"1280x1024", couleurNoire);

        SDL_BlitSurface(texte1280, NULL, fond, &position1280);

        //On met un outliner autour du dé de la couleur choisie
        SDL_BlitSurface(antiOutliner,NULL,fond,&posOutliner);
        SDL_Flip(fond);                                         //Ces deux lignes servent à effacer l'outliner précédent

        switch(couleur)
        {
            case rouge:
            posOutliner.x = posR1.x - 10;
            posOutliner.y = posR1.y - 10;
            break;
            case vert:
            posOutliner.x = posV1.x - 10;
            posOutliner.y = posV1.y - 10;
            break;
            case bleu:
            posOutliner.x = posB1.x - 10;
            posOutliner.y = posB1.y - 10;
            break;
            case jaune:
            posOutliner.x = posJ1.x - 10;
            posOutliner.y = posJ1.y - 10;
            break;
            case violet:
            posOutliner.x = posP1.x - 10;
            posOutliner.y = posP1.y - 10;
            break;
            case orange:
            posOutliner.x = posO1.x - 10;
            posOutliner.y = posO1.y - 10;
            break;
        }
        SDL_BlitSurface(outliner,NULL,fond,&posOutliner);
        //Et on affiche tout ça
        SDL_Flip(fond);

        //on relance le menu
        continuer = VRAI;
        while (continuer)
        {
            FE_WaitEvent(&event);
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
                    break;
                    case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button==SDL_BUTTON_LEFT)
                    {

                        if (estDans(event,texte640,position640))
                        {

                            if (resolution != 0)
                            {

                                char tampon[TAILLE_MAX];
                                rewind(fconfig);
                                fgets(tampon,5,fconfig);//on passe après le "res="
                                fputc('0',fconfig);
                                rewind(fconfig);
                                resolution = 0;
                                resolutionChange = VRAI;
                                continuer = FAUX;
                                fflush(fconfig);

                                if ((fond = SDL_SetVideoMode(640,480,32,SDL_DOUBLEBUF))==NULL)
                                {
                                fprintf(stderr,"Erreur au redimensionnement de la video : %s", SDL_GetError());
                                exit(EXIT_FAILURE);
                                }


                            }
                        }
                        if (estDans(event,texte800,position800))
                        {

                            if(resolution != 1)
                            {
                                char tampon[TAILLE_MAX];
                                rewind(fconfig);
                                fgets(tampon,5,fconfig);//on passe après le "res="
                                fputc('1',fconfig);
                                resolution = 1;
                                resolutionChange = VRAI;
                                continuer = FAUX;
                                fflush(fconfig);

                                if ((fond = SDL_SetVideoMode(800,600,32,SDL_DOUBLEBUF))==NULL)
                                {
                                fprintf(stderr,"Erreur au redimensionnement de la video : %s", SDL_GetError());
                                exit(EXIT_FAILURE);
                                }

                            }
                        }
                        if  (estDans(event,texte1280,position1280))
                        {
                            if(resolution !=2)
                            {
                                char tampon[TAILLE_MAX+1];
                                rewind(fconfig);
                                fgets(tampon,5,fconfig);//on passe après le "res="
                                fputc('2',fconfig);
                                resolution = 2;
                                resolutionChange = VRAI;
                                continuer = FAUX;
                                fflush(fconfig);

                                if ((fond = SDL_SetVideoMode(1280,1024,32,SDL_DOUBLEBUF))==NULL)
                                {
                                fprintf(stderr,"Erreur au redimensionnement de la video : %s", SDL_GetError());
                                exit(EXIT_FAILURE);
                                }

                            }
                        }

                        if (estDans(event,R1,posR1))
                        {
                            if(couleur != 0)
                            {
                                char tampon[TAILLE_MAX+1];
                                rewind(fconfig);
                                fgets(tampon,TAILLE_MAX,fconfig);//on vire la 1ere ligne
                                fgets(tampon,7,fconfig);// on passe après le "color"
                                fputc('0',fconfig);
                                couleur = 0;
                                affichageChange = VRAI;
                                continuer = FAUX;
                                fflush(fconfig);
                            }
                        }

                        if (estDans(event,V1,posV1))
                        {
                            if(couleur != 1)
                            {
                                char tampon[TAILLE_MAX+1];
                                rewind(fconfig);
                                fgets(tampon,TAILLE_MAX,fconfig);//on vire la 1ere ligne
                                fgets(tampon,7,fconfig);// on passe après le "color"
                                fputc('1',fconfig);
                                couleur = 1;
                                affichageChange = VRAI;
                                continuer = FAUX;
                                fflush(fconfig);
                            }
                        }

                        if (estDans(event,B1,posB1))
                        {
                            if(couleur != 2)
                            {
                                char tampon[TAILLE_MAX+1];
                                rewind(fconfig);
                                fgets(tampon,TAILLE_MAX,fconfig);//on vire la 1ere ligne
                                fgets(tampon,7,fconfig);// on passe après le "color"
                                fputc('2',fconfig);
                                couleur = 2;
                                affichageChange = VRAI;
                                continuer = FAUX;
                                fflush(fconfig);
                            }
                        }
                        if (estDans(event,J1,posJ1))
                        {
                            if(couleur != 3)
                            {
                                char tampon[TAILLE_MAX+1];
                                rewind(fconfig);
                                fgets(tampon,TAILLE_MAX,fconfig);//on vire la 1ere ligne
                                fgets(tampon,7,fconfig);// on passe après le "color"
                                fputc('3',fconfig);
                                couleur = 3;
                                affichageChange = VRAI;
                                continuer = FAUX;
                                fflush(fconfig);
                            }
                        }
                        if (estDans(event,P1,posP1))
                        {
                            if(couleur != 4)
                            {
                                char tampon[TAILLE_MAX+1];
                                rewind(fconfig);
                                fgets(tampon,TAILLE_MAX,fconfig);//on vire la 1ere ligne
                                fgets(tampon,7,fconfig);// on passe après le "color"
                                fputc('4',fconfig);
                                couleur = 4;
                                affichageChange = VRAI;
                                continuer = FAUX;
                                fflush(fconfig);
                            }
                        }
                        if (estDans(event,O1,posO1))
                        {
                            if(couleur != 5)
                            {
                                char tampon[TAILLE_MAX+1];
                                rewind(fconfig);
                                fgets(tampon,TAILLE_MAX,fconfig);//on vire la 1ere ligne
                                fgets(tampon,7,fconfig);// on passe après le "color"
                                fputc('5',fconfig);
                                couleur = 5;
                                affichageChange = VRAI;
                                continuer = FAUX;
                                fflush(fconfig);
                            }
                        }
                    }
                    break;
                }

        }

        //Et on free, c'est important
        SDL_FreeSurface(texte640);
        SDL_FreeSurface(texte800);
        SDL_FreeSurface(texte1280);
    } while (affichageChange);

SDL_FreeSurface(texteResolution);
SDL_FreeSurface(texteCouleur);
SDL_FreeSurface(R1);
SDL_FreeSurface(V1);
SDL_FreeSurface(B1);
SDL_FreeSurface(J1);
SDL_FreeSurface(P1);
SDL_FreeSurface(O1);
SDL_FreeSurface(outliner);
SDL_FreeSurface(antiOutliner);
TTF_CloseFont(policePerudo);

} while(resolutionChange);
fclose(fconfig);
}


