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

#define MY_PORT 25656
#define LGLEN	1024
#define CLIENTMAX 10
