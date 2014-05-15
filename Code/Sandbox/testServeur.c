#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "fastevents.h"
#include "net2.h"
#include "SDLUtils.h"

int main(int argc, char **argv)
{
  SDL_Event ev;                              // evenement  SDL
  char buf[1024];                            // taille message
  int len = 0;                               // compteurs
  int count = 0;
  int socks = 0;                             //nombre de socket client connectées
  int port = 5555;
  IPaddress *monIP = NULL;

  if((NET2_ResolveHost(monIP,"localhost",6666))!=0 || monIP==NULL)
    {
      fprintf(stderr,"errreur à la récupération de l'IP");
      return EXIT_FAILURE;
    }

  mySDLInitOrQuit(SDL_INIT_EVENTTHREAD |     // initialisation de la sdl
                  SDL_INIT_VIDEO |
                  SDL_INIT_NOPARACHUTE);


  NET2_TCPAcceptOn(port);

  while (FE_WaitEvent(&ev))                  //attente requete clients
  {
    switch (ev.type)
    {

    case SDL_USEREVENT:
      switch(NET2_GetEventType(&ev))
      {

// la connexion est acceptée

      case NET2_TCPACCEPTEVENT:
        printf("accept(%d)\n", NET2_GetSocket(&ev));
        printNET2Event(&ev);
        socks++;
        break;

        // en cas de reception d evenement

      case NET2_TCPRECEIVEEVENT:
        while (0 != (len = NET2_TCPRead(NET2_GetSocket(&ev), buf, sizeof(buf))))
        {
          count += len;
        }
        break;

        // en cas de deconnexion

      case NET2_TCPCLOSEEVENT:
        printf("close(%d)\n", NET2_GetSocket(&ev));
        printNET2Event(&ev);
        NET2_TCPClose(NET2_GetSocket(&ev));  // close the socket

        printf("count=%d\n", count); fflush(NULL);
        socks--;
        if (0 >= socks)
        {
          //exit(0);
        }
        //count = 0;
        break;

      case NET2_ERROREVENT: //en cas d erreur
        printf("Error: %s(%d)\n", NET2_GetEventError(&ev), NET2_GetSocket(&ev));
        printNET2Event(&ev);
        break;
      }
      break;

    case SDL_QUIT:
      mySDL_Quit();                          // nettoyage et quitte
      exit(0);
      break;
    }
  }

  mySDL_Quit();
}


