#include testclient.h

int main(int argc, char **argv)
{
  SDL_Event ev;
  char buf[1024];
  int len = 0;
  int count = 0;

  FILE* sauvegarde_net = fopen("server_list", "r"); // on récupère le fichier id_net de sauvegarde des données du serveur

    if (sauvegarde_net==NULL) {
        perror(fopen);
        fprintf(stderr, "impossible d'ouvrir le fichier");
        exit(EXIT_FAILURE);
        } // si on arrive pas a l'ouvrir on envoit une erreur

  mySDLInitOrQuit(SDL_INIT_EVENTTHREAD |
                  SDL_INIT_VIDEO |
                  SDL_INIT_NOPARACHUTE);


  if (-1 == NET2_TCPConnectToIP(ip))
  {
    printf("ConnectTo failed\n");
    exit(0);
  }

  while (FE_WaitEvent(&ev))
  {
    switch (ev.type)
    {
    case SDL_USEREVENT:
      switch(NET2_GetEventType(&ev))
      {
      case NET2_TCPACCEPTEVENT:
        printf("accept\n");
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


          if (-1 == NET2_TCPSend(NET2_GetSocket(&ev), buf, len))
          {
            printf("RECIEVE SEND FAILED\n");
            NET2_TCPClose(NET2_GetSocket(&ev));
            break;
          }
        }

        if (count > 5000)
        {
      printf ("\nfin du test\n");
      NET2_TCPClose(NET2_GetSocket(&ev));
          exit(0);
        }

        break;

      case NET2_TCPCLOSEEVENT:
        printf("close\n");
        NET2_TCPClose(NET2_GetSocket(&ev));
        exit(0);
        break;

      case NET2_ERROREVENT:
        printf("Error: %s\n", NET2_GetEventError(&ev));
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

void recuperationIP(IPaddress * ipARemplir, FILE * sauvegarde_net)
    {

    char ip[TAILLE_IP],port[TAILLE_PORT],tampon[10];
    fgets(tampon,6,sauvegarde_net); //on vide "host="
    fgets(ip,TAILLE_IP+1,sauvegarde_net); // on récupère l adresse ip dans la première ligne
    fgets(tampon,6,sauvegarde_net); //on vide "\nport="
    fgets(port,TAILLE_PORT+1,sauvegarde_net); // on récupère le port dans la seconde
    supprimerPoints(port, longueur_mot(port));

    }

private void supprimerPointsIP (char * ipTexte)
{
    int i = 0;
    while (i < TAILLE_IP   )
    {
        if(ipTexte[i] == '.')
            for (int j = i; j<TAILLE_IP; j++)
                ipTexte[j] = ipTexte[j+1];
    }

}
