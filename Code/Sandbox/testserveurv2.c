/*euh... chez moi ça a plus une gueule de client :) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SDL_net.h"
#include "SDL.h"

int main(int argc, char **argv)
{
	IPaddress ip;		/* addresse du serveur */
	TCPsocket sd;		/* paramètre Socket  */
	int quit, len;
	char buffer[512];

	/* test paramètres*/
	if (argc < 3)
	{
		fprintf(stderr, "Usage: %s host port\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	/* Resolution de la connection à l'Hôte*/
	if (SDLNet_ResolveHost(&ip, argv[1], atoi(argv[2])) < 0)
	{
		fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	/* Ouverture de la connection a partir de l'adresse IP */
	if (!(sd = SDLNet_TCP_Open(&ip)))
	{
		fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	/* envoi de messages */
	quit = 0;
	while (!quit)
	{
		printf("messages:\n>");
		scanf("%s", buffer);

		len = strlen(buffer) + 1;
		if (SDLNet_TCP_Send(sd, (void *)buffer, len) < len)
		{
			fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
			exit(EXIT_FAILURE);
		}

		if(strcmp(buffer, "exit") == 0)
			quit = 1;
		if(strcmp(buffer, "quit") == 0)
			quit = 1;
	}

	SDLNet_TCP_Close(sd);
	SDLNet_Quit();

	return EXIT_SUCCESS;
}
