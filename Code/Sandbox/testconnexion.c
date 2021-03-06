
#include "testconnexion.h"


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

  memset(next, 0, sizeof(next));
  mySDLInitOrQuit(SDL_INIT_EVENTTHREAD |
                  SDL_INIT_VIDEO |
                  SDL_INIT_NOPARACHUTE);

  NET2_TCPAcceptOn(addr->port);

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
        if (-1 == NET2_TCPSend(s, welcome, sizeof(welcome) - 1))
        {
          printf("WELCOME SEND FAILED\n");
        }
        next[s] = 0;
        break;

      case NET2_TCPRECEIVEEVENT:

        s = NET2_GetSocket(&ev);
        while (0 != (len = NET2_TCPRead(s, buf, sizeof(buf))))
        {
          int i;

          n = next[s];
          for (i = 0; i < len; i++)
          {
            if (welcome[n] != buf[i])
            {
              printf("\nout of sync %c != %c\n", welcome[n], buf[i]);
              exit(0);
            }
            n = (n + 1) % (sizeof(welcome) - 1);
          }
          next[s] = n;

          if (-1 == NET2_TCPSend(s, buf, len))
          {
            printf("RECIEVE SEND FAILED\n");
          }
        }
        break;

      case NET2_TCPCLOSEEVENT:
        printf("close(%d)\n", NET2_GetSocket(&ev));
    NET2_TCPClose(NET2_GetSocket(&ev));
        count--;
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
  }

  mySDL_Quit();
  return EXIT_SUCCESS;
}


void saveIPaddress(IPaddress *addr,FILE *server_list )
{
  rewind(server_list);
  fprintf(server_list,"host=%d.%d.%d.%d\n",
         ((addr->host >>  0) & 0xff),
         ((addr->host >>  8) & 0xff),
         ((addr->host >> 16) & 0xff),
         ((addr->host >> 24) & 0xff));

  fprintf(server_list,"port=%4d\n", addr->port);

  fflush(NULL);
}

IPaddress
