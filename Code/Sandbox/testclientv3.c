#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <SDL/SDL.h>
#include "net2.h"
#include "fastevents.h"
#include "SDLUtils.h"
#include "trace.h"
#include "jeu.h"
#include "PerudUtils.h"

int main(int argc, char **argv)
{
  SDL_Event ev;
  char buf[1024];
  int len = 0;
  int count = 0;
  int port = 6666;
  int limit = 1000;
  Annonce mess;
  IPaddress *monIP = NULL;

  mySDLInitOrQuit(SDL_INIT_EVENTTHREAD |
                  SDL_INIT_VIDEO |
                  SDL_INIT_NOPARACHUTE);

    printf("1 OK\n");
/*  if(((NET2_ResolveHost(monIP,"localhost",port))!=0) || (monIP==NULL))
    {
      fprintf(stderr,"erreur à la récupération de l'IP");
      return EXIT_FAILURE;
    }
printf("2 OK\n"); */

  if (-1 == NET2_TCPConnectTo("localhost", port))
  {
    printf("ConnectTo failed\n");
    exit(0);
  }

printf("3 OK\n");

  while (FE_WaitEvent(&ev))
  {
    switch (ev.type)
    {
    case SDL_USEREVENT:
      switch(NET2_GetEventType(&ev))
      {
      case NET2_TCPACCEPTEVENT:
        printf("accept\n");
        printf("4 OK\n");
        break;

      case NET2_TCPRECEIVEEVENT:
        while (0 != (len = NET2_TCPRead(NET2_GetSocket(&ev), buf, sizeof(buf))))
        {
          int i;

          printf("len=%d\n", len);
          count += len;
          SDL_Delay(100);
          for (i = 0; i < len; i++)
            {
                putchar(buf[i]);
            }
          putchar('\n');

          //envoi message
/*
        for (i = 0; i < limit; i++)
            {
                memset(buf, 0, sizeof(buf));
                //sprintf(buf, mess, i);
                NET2_TCPSend(NET2_GetSocket(&ev), buf, sizeof(buf));
                count += sizeof(buf);
            }
*/

        if (-1 == NET2_TCPSend(NET2_GetSocket(&ev), buf, len))
            {
                printf("RECIEVE SEND FAILED\n");
                NET2_TCPClose(NET2_GetSocket(&ev));
                printf("6.0 OK\n");
                break;
            }
        }

        if (count > 5000)
        {
	  printf ("\nfin du test\n");
	  NET2_TCPClose(NET2_GetSocket(&ev));
          exit(0);
        }
        printf("6.1 OK\n");
        break;



      case NET2_TCPCLOSEEVENT:
        printf("close\n");
        NET2_TCPClose(NET2_GetSocket(&ev));
        exit(0);
        printf("7 OK\n");
        break;



      case NET2_ERROREVENT:
        printf("Error: %s\n", NET2_GetEventError(&ev));
        exit(0);
        printf("8 OK\n");
        break;
      }
      break;



    case SDL_QUIT:
      mySDL_Quit();
      exit(0);
      printf("9 OK\n");
      break;
    }
  }
printf("10 OK\n");
  mySDL_Quit();
  return EXIT_SUCCESS;
}
