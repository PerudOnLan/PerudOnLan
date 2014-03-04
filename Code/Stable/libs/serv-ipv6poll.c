/***************************************************
** serv-ipv6.c: tcp socket server for multi-client
** Author: Eric Lallet
** Last modification: 25/03/2003 
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/poll.h>
#include <string.h>
#include <stdlib.h>

#define MY_PORT 11201

#define LGLEN	1024
#define CLIENTMAX 10

name_from_addr(int af, const struct sockaddr *addr, char *name, int size) {
    char dst[INET6_ADDRSTRLEN];
    struct addrinfo hint, *res;

    switch (af) {
    case AF_INET: {
	struct sockaddr_in  addr4;
	memcpy(&addr4, addr, sizeof(addr4));
	if (!inet_ntop(AF_INET, &(addr4.sin_addr), dst, sizeof(dst))) {
	    strncpy(name,"Unknown", size);
	    return(1);
	}
	break;
    }
    case AF_INET6: {
	struct sockaddr_in6  addr6;
	memcpy(&addr6, addr, sizeof(addr6));
	if (!inet_ntop(AF_INET6, &(addr6.sin6_addr), dst, sizeof(dst))) {
	    strncpy(name,"Unknown", size);
	    return(1);

	}
	break;
    }

    }

    memset(&hint, 0, sizeof(hint));
    hint.ai_flags = AI_NUMERICHOST | AI_CANONNAME;
    if (getaddrinfo(dst, NULL, &hint, &res) != 0) {
	strncpy(name, dst, size);
    }
    else {
	if (res->ai_canonname) {
	    strncpy(name, res->ai_canonname, size);
	}
	else {
	    strncpy(name, dst, size);
	}
	freeaddrinfo(res);
    }
    return(0);
}


main() {
    int socka;			/* socket for bind/listen/accept */
    int sockc;			/* socket connected to the client */
    int err;
    struct client_st {
	FILE *sockf;
	char hostname[MAXHOSTNAMELEN];
    } client[CLIENTMAX];	/* client list */
 
   struct pollfd poll_tab[CLIENTMAX+1];

    int poll_cli[CLIENTMAX+1];
    int poll_nb, poll_ind;
    int addr_len;		
    int cli_ind, cli_ind2;
    int ruse = 1;
    struct sockaddr_storage his_addr;
    char line1[LGLEN];	/* line from client */
    char line2[MAXHOSTNAMELEN+LGLEN];	/* line to client */
    char port_str[10];
    struct addrinfo hint, *resultat, *pind;




    /***************************************************
    ** prepare the server socket: socket+bind+listen
    */
    hint.ai_flags =  AI_PASSIVE ;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_protocol = IPPROTO_IP;
    sprintf(port_str,"%d", MY_PORT);


    /* on tente ipv6 en premier */
    hint.ai_family = AF_INET6;
    if ((err = getaddrinfo(NULL,port_str, &hint, &resultat)) != 0) {
	fprintf(stderr,"getaddrinfo: %s\n", gai_strerror(err));
	exit(EXIT_FAILURE);
    }

    /* 1 -> socket TCP */ 
    if ((socka = socket(resultat->ai_family, resultat->ai_socktype, resultat->ai_protocol)) == -1) {
	/* va pour ipv4 */
	freeaddrinfo(resultat);
	hint.ai_family = AF_INET;
	if ((err = getaddrinfo(NULL,port_str, &hint, &resultat)) != 0) {
	    fprintf(stderr,"getaddrinfo: %s\n", gai_strerror(err));
	    exit(EXIT_FAILURE);
	}
	if ((socka = socket(resultat->ai_family, resultat->ai_socktype, resultat->ai_protocol)) == -1) {
	    perror("socket");
	    exit(EXIT_FAILURE);
	}
    }

    /* to avoid "socket allrady in use" minutes after closing the old socket */
    if (setsockopt(socka,SOL_SOCKET, SO_REUSEADDR,&ruse,sizeof(ruse)) == -1 ) {
	perror("setsokopt");
	exit(EXIT_FAILURE);
    }
    if (bind(socka, resultat->ai_addr, resultat->ai_addrlen) == -1) {
	perror("bind");
	exit(EXIT_FAILURE);
    }
    freeaddrinfo(resultat);

    /* 3 -> listen on this socket */
    if (listen(socka, 5) == -1) {
	perror("listen");
	exit(EXIT_FAILURE);
    }


    /***************************************************
    ** several initialisations
    */
    for (cli_ind = 0 ; cli_ind < CLIENTMAX; cli_ind++) {
	client[cli_ind].sockf = NULL;
    }

    /***************************************************
    ** main loop
    */
    while (1) {
	
	// accept socket on 1st position
	poll_tab[0].fd = socka;
	poll_tab[0].events = POLLIN;

	// clients sockets on other positions
	for (cli_ind = 0, poll_nb = 0 ; cli_ind < CLIENTMAX; cli_ind++) {
	    if (client[cli_ind].sockf != NULL) {
		poll_nb++;
		poll_tab[poll_nb].fd = fileno(client[cli_ind].sockf);
		poll_tab[poll_nb].events = POLLIN;
		poll_cli[poll_nb] = cli_ind;
	    }
	}

	// waiting for an event
	if (poll(poll_tab, poll_nb+1, -1) == -1) {
	    perror("poll");
	    exit(EXIT_FAILURE);
	}

	/* somethings to do */

	/* 1> are there any messages from clients ? */
	for (poll_ind = 1 ; poll_ind <= poll_nb; poll_ind++) {
	    if (poll_tab[poll_ind].revents & POLLIN)  {
		if (fgets(line1, LGLEN, client[poll_cli[poll_ind]].sockf) == NULL) {
		    /* select restarted because a client had closed its connection */
		    fclose(client[poll_cli[poll_ind]].sockf);
		    client[poll_cli[poll_ind]].sockf = NULL;
		}
		else {
		    /* there was a message: send it to all clients */
		    sprintf(line2,"%s> %s",client[poll_cli[poll_ind]].hostname,line1);
		    for (cli_ind2 = 0; cli_ind2 < CLIENTMAX ; cli_ind2++) {
			if (client[cli_ind2].sockf != NULL) {
			    if (fputs(line2,client[cli_ind2].sockf) <= 0) {
				fclose(client[cli_ind2].sockf);
				client[cli_ind2].sockf = NULL;
			    }
			    else {
				fflush(client[cli_ind2].sockf);
			    }
			}
		    }
		}
	    }
	}

	/* 2> is there any new client to accept ? */
	if (poll_tab[0].revents & POLLIN) {
	    addr_len = sizeof(his_addr);
	    if ((sockc = accept(socka, (struct sockaddr *) &his_addr, &addr_len)) == -1 ){
		perror("accept");
		exit(EXIT_FAILURE);
	    }
	    /* try to find a place for the new client */
	    for (cli_ind2 = 0; cli_ind2 < CLIENTMAX ; cli_ind2++) {
		if (client[cli_ind2].sockf == NULL) break;
	    }
	    if (cli_ind2 < CLIENTMAX) {
		/* try to find hostname of the client */
		name_from_addr(his_addr.ss_family,(struct sockaddr *) &his_addr, client[cli_ind2].hostname, MAXHOSTNAMELEN);

		
		/* build a FILE * fron socket: fgets et fputs are
		** usefull for managing lines of text.
		*/
		if ((client[cli_ind2].sockf = fdopen(sockc, "r+")) == NULL) {
		    perror("fdopen");
		    exit(EXIT_FAILURE);
		}
	    }
	    else {
		/* no more place. close connection with the new client */
		close(sockc);
	    }
	}
    }
}
