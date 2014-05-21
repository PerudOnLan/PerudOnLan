#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <SDL/SDL.h>
#include "net2.h"
#include "fastevents.h"
#include "SDLUtils.h"
#include "trace.h"
#include "PerudUtils.h"

int main(int argc, char **argv)
{
  SDL_Event ev;
  char welcome[] = "Test de connexion PerudOnLan";
  char buf[1024];
  int len = 0;
  int count = 0;
  int s = -1;
  int next[0xffff];
  int n = -1;
  int port = 6666;
  int nbrjoueurs;
  int message =42;
  Annonce mess;
/*
  if(argc =! 2) {
  fprintf(stderr, "Mauvaise utilistation: nbr joueurs");
  exit(1);
  }

  nbrjoueurs = argv[1][0]-'0';

  if (nbrjoueurs <1 || nbrjoueurs > 6 )
    {
    fprintf(stderr, "Mauvaise utilistation: nbr joueurs");
    exit(1);
    }
*/

  memset(next, 0, sizeof(next));

  mySDLInitOrQuit(SDL_INIT_EVENTTHREAD |
                  SDL_INIT_VIDEO |
                  SDL_INIT_NOPARACHUTE);

  NET2_TCPAcceptOn(port);
/*
  if(count>nbrjoueurs) {
    fprintf(stderr, "Le nombre maximal de joueur a été atteint");
    exit(0);
    }
*/
  while (FE_WaitEvent(&ev))
  {
    switch (ev.type)
    {
    case SDL_USEREVENT:
      switch (NET2_GetEventType(&ev))
      {
      case NET2_TCPACCEPTEVENT:
        count++;
        printf("accept(%d)\n", NET2_GetSocket(&ev));
        s = NET2_GetSocket(&ev);
        if (-1 == write(s, "plop", sizeof("plop")-1))
        {
          printf("WELCOME SEND FAILED\n");
        }
        NET2_TCPSend(s, buf, len)
        next[s] = 0;
        break;

      case NET2_TCPRECEIVEEVENT:

        s = NET2_GetSocket(&ev);
        while (0 != (len = read(s, welcome, sizeof(welcome) -1)))
        {
          int i;



          if (-1 == write(s, welcome, sizeof(welcome)))
          {
            printf("Erreur de reception message\n");
          }
        }




      break;

      case NET2_TCPCLOSEEVENT:
        printf("close(%d)\n", NET2_GetSocket(&ev));
	NET2_TCPClose(NET2_GetSocket(&ev));
        count--;
        /*if (0 >= count)
        {
          exit(0);
        }
	*/
        break;
      case NET2_ERROREVENT:
        printf("Error: %s(%d)\n", NET2_GetEventError(&ev), NET2_GetSocket(&ev));
        exit(0);
        break;
      }
      break;

    case SDL_QUIT:
      mySDL_Quit();
      exit(0);
      break;
    }
    /* if (fwrite(&message, sizeof(int) , 1, NET2_GetSocket(&ev)) != 0 )
    {
    printf("%d",message);
    }
*/
    }
  mySDL_Quit();
  return EXIT_SUCCESS;
}

