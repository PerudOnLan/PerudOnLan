CC = gcc
CFLAGS = -m32 -g -Wall
SDLLIBS = -lSDLmain -lSDL -lSDL_image -lSDL_ttf -lSDL_net -lSDL_net2
PHEADERS =../../Sources_et_libs/headers
PLIBS=../../Sources_et_libs/libs

all: Perudo clean

Perudo : perudo.o menu.o jeu.o PerudUtils.o graphics.o
	$(CC) $(CFLAGS) perudo.o menu.o graphics.o jeu.o PerudUtils.o -L$(PLIBS) $(SDLLIBS) -o Perudo

perudo.o : perudo.c perudo.h couleurs.h menu.h jeu.h PerudUtils.h
	$(CC) $(CFLAGS) -I$(PHEADERS) -c perudo.c

menu.o : menu.c menu.h couleurs.h jeu.h graphics.h PerudUtils.h
	$(CC) $(CFLAGS) -I$(PHEADERS) -c menu.c

jeu.o : jeu.c jeu.h couleurs.h graphics.h  PerudUtils.h
	$(CC) $(CFLAGS) -I$(PHEADERS) -c jeu.c 

PerudUtils.o : PerudUtils.c PerudUtils.h
	$(CC) $(CFLAGS) -I$(PHEADERS) -c PerudUtils.c

graphics.o: graphics.c graphics.h couleurs.h PerudUtils.h
	$(CC) $(CFLAGS) -I$(PHEADERS) -c graphics.c 

doxygen : 
	doxygen ../../Documents/Doxygen/Doxyfile

clean : 
	rm -f perudo.o menu.o jeu.o PerudUtils.o testserveurv3.o testclientv3.o testsUnitaires.o ia.o graphics.o

serveur : server.o PerudUtils.o
	$(CC) $(CFLAGS) server.o PerudUtils.o -L$(PLIBS) $(SDLLIBS) -o Serveur

server.o : server.cpp
	$(CC) $(CFLAGS) -I$(PHEADERS) -c server.cpp

client : client.o PerudUtils.o
	$(CC) $(CFLAGS) client.o PerudUtils.o -L$(PLIBS) $(SDLLIBS) -o Client

client.o : client.cpp
	$(CC) $(CFLAGS) -I$(PHEADERS) -c client.cpp

testsUnitaires: testsUnitaires.o PerudUtils.o ia.o 	
	$(CC) $(CFLAGS) testsUnitaires.o PerudUtils.o ia.o -L$(PLIBS) $(SDLLIBS) -o TestsUnitaires

ia.o : ia.c
	$(CC) $(CFLAGS) -I$(PHEADERS) -c ia.c

testsUnitaires.o: testsUnitaires.c
	$(CC) $(CFLAGS) -I$(PHEADERS) -c testsUnitaires.c