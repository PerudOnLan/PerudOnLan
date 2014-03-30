/***************************************************
** cli-ipv6.c: tcp client -> exchange text messages with
**	tcp server
** Author: Eric Lallet.
** Last modification: 03/03/2014
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/poll.h>


#define SERVER_PORT 11201

#define LENMAX 1024

main(int argc, char *argv[]) {
    int sock, err;
    char line[LENMAX], port_str[10];
    struct addrinfo hint, *resultat, *pind;
    struct pollfd pollTab[2]; // 1st position for stdin,  2nd position for serv socket
    int connected = 1;
    FILE *serv;

    /***************************************************
    ** check arguments 
    */
    if (argc != 2) {
	fprintf(stderr,"Usage: mess <host>\n");
	exit(1);
    }

    /***************************************************
    ** give info for getaddrinfo:
    */
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_UNSPEC; /* try to connect to ipv4 or ipv6 */
    hint.ai_socktype = SOCK_STREAM; /* want a TCP connection */
    hint.ai_protocol = IPPROTO_IP;
    sprintf(port_str,"%d", SERVER_PORT);

    if ((err = getaddrinfo(argv[1], port_str, &hint, &resultat)) != 0) {
	fprintf(stderr,"%s: %s\n", argv[1], gai_strerror(err));
	exit(EXIT_FAILURE);
    }

    /* try to connect to one of addr */
    pind = resultat;

    while (pind != NULL) {
	if ((sock = socket(pind->ai_family, pind->ai_socktype, pind->ai_protocol)) == -1) {
	    pind = pind->ai_next;
	    continue;
	}
	if (connect(sock, pind->ai_addr, pind->ai_addrlen) != -1) {
	    break;
	}
	/* connect failed */
	perror("connect");
	close(sock);
	pind = pind->ai_next;
    }

    if (pind == NULL) {
	fprintf(stderr,"Can not establish any connection\n");
	exit(EXIT_FAILURE);
    }

 
    freeaddrinfo(resultat);



    if ((serv = fdopen(sock,"r+")) == NULL) {
	perror("fdopen sock");
	exit(EXIT_FAILURE);
    }

    while (connected) {
	pollTab[0].fd = 0;
	pollTab[0].events = POLLIN;
	pollTab[1].fd = sock;
	pollTab[1].events = POLLIN;
	
	if (poll(pollTab, 2, -1) == -1) {
	    perror("poll");
	    exit(EXIT_FAILURE);
	}
	
	if (pollTab[0].revents & POLLIN) {
	    // from stdin
	    if (fgets(line, sizeof(line), stdin) == NULL) {
		// stdin is closed
		connected = 0;
	    }
	    else {
		fputs(line, serv);
		fflush(serv);
	    }
	    
	}
	if (pollTab[1].revents & POLLIN) {
	    // from serv socket
	    if (fgets(line, sizeof(line), serv) == NULL) {
		// connection is closed
		connected = 0;
	    }
	    else {
		fputs(line, stdout);
		
	    }
	    
	}
	
	
    }
    printf("\nConnexion closed\n");
    exit(EXIT_SUCCESS);
}

