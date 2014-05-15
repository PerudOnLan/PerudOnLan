/* Et ça on dirait bien un serveur :) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SDL_net.h"
#include "PerudUtils.h"

int main(int argc, char **argv)
{
	TCPsocket sd, csd; /* Socket client*/
	IPaddress ip, *remoteIP;
	int quit, quit2;
	char buffer[512];

	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	/* Erreur si ResolveHost a NULL  */
	if (SDLNet_ResolveHost(&ip, NULL, 2000) < 0)
	{
		fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	/* Ouverture de la connection a partir de l'IP */
	if (!(sd = SDLNet_TCP_Open(&ip)))
	{
		fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	/* Attente de la connection et envoi donnée*/
	quit = FAUX;
	while (!quit)
	{
		/* Verification du csd durant la connection établie.Si il il a une nouvelle tentative alors on l'accepte et l'on utilise une autre socket */
		if ((csd = SDLNet_TCP_Accept(sd)))
		{

			/* Obtenir les adresses */
			if ((remoteIP = SDLNet_TCP_GetPeerAddress(csd)))
				/* Obtenir l'adresse et la configurer*/
				printf("Host connected: %x %d\n", SDLNet_Read32(&remoteIP->host), SDLNet_Read16(&remoteIP->port));
			else
				fprintf(stderr, "SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());

			quit2 = FAUX;
			while (!quit2)
			{
				if (SDLNet_TCP_Recv(csd, buffer, 512) > 0)
				{
					printf("Client : %s\n", buffer);

					if(strcmp(buffer, "exit") == 0)	/* Terminer la connection */
					{
						quit2 = VRAI;
						printf("Terminer la connection\n");
					}
					if(strcmp(buffer, "quit") == 0)	/* Quitter le programme*/
					{
						quit2 = VRAI;
						quit = VRAI;
						printf("Quitter le programme\n");
					}
				}
			}

			/* Close the client socket */
			SDLNet_TCP_Close(csd);
		}
	}

	SDLNet_TCP_Close(sd);
	SDLNet_Quit();

	return EXIT_SUCCESS;
}
