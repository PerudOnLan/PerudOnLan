CC = gcc
CFLAGS = -m32 -g
SDLLIBS = -lSDLmain -lSDL -lSDL_image -lSDL_ttf -lSDL_net -lSDL_net2
PHEADERS =../../Sources_et_libs/headers
PLIBS=../../Sources_et_libs/libs

all: Perudo clean

Perudo : perudo.o menu.o jeu.o PerudUtils.o 
	$(CC) $(CFLAGS) perudo.o menu.o jeu.o PerudUtils.o -L$(PLIBS) $(SDLLIBS) -o Perudo

perudo.o : perudo.c perudo.h couleurs.h menu.h jeu.h PerudUtils.h
	$(CC) $(CFLAGS) -I$(PHEADERS) -c perudo.c

menu.o : menu.c menu.h couleurs.h jeu.h PerudUtils.h
	$(CC) $(CFLAGS) -I$(PHEADERS) -c menu.c

jeu.o : jeu.c jeu.h couleurs.h PerudUtils.h
	$(CC) $(CFLAGS) -I$(PHEADERS) -c jeu.c 

PerudUtils.o : PerudUtils.c PerudUtils.h
	$(CC) $(CFLAGS) -I$(PHEADERS) -c PerudUtils.c

doxygen : 
	doxygen ../../Documents/Doxygen/Doxyfile

clean : Perudo
	rm -f perudo.o menu.o jeu.o PerudUtils.o