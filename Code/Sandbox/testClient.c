#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "net2.h"
#include "SDLUtils.h"
#include "fastevents.h"

int main(int argc, char **argv)
{
    SDL_Event ev;
  char buf[1024];                             // taille du message
  int i;                                     // compteur
  int s = -1;                                // socket
  int count = 0;                             // compteur message
  int limit = 1000;
  int port = 5555 ;
  IPaddress ip= -1;

  //Il faut récupérer l'ip sur la liste des IP disponibles

  mySDLInitOrQuit(SDL_INIT_EVENTTHREAD |     // initialisation de la  SDL
                  SDL_INIT_VIDEO |
                  SDL_INIT_NOPARACHUTE);

  if (-1 == (s = NET2_TCPConnectTo("localhost", port)))
  {
    printf("ConnectTo failed\n");
    exit(0);
  }

// creation de message et envoi

  for (i = 0; i < limit; i++)
  {
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "test #%08d\n", i);  // ion du messagecreat
    NET2_TCPSend(s, buf, sizeof(buf));       // envoi du message
  }

  printf("count=%d\n", count);               // dire combien de message ont été envoyé

  mySDL_Quit();                              // nettoyage
  return EXIT_SUCCESS;
}
