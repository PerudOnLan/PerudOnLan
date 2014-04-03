CC = gcc
CFLAGS = -g
SDLLIBS = -lSDLmain -lSDL -lSDL_image -lSDL_ttf -lSDL_net -lSDL_net2
PHEADERS =../../Sources_et_libs/headers
PLIBS=../../Sources_et_libs/libs

all: testSDL clean

testSDL : testSDL.o menu.o jeu.o
	$(CC) $(CFLAGS) testSDL.o menu.o jeu.o -L$(PLIBS) $(SDLLIBS) -o TestSDL 

testSDL.o : testSDL.c testSDL.h couleurs.h menu.h jeu.h
	$(CC) $(CFLAGS) -I$(PHEADERS) -c testSDL.c

menu.o : menu.c menu.h couleurs.h jeu.h
	$(CC) $(CFLAGS) -I$(PHEADERS) -c menu.c

jeu.o : jeu.c jeu.h couleurs.h
	$(CC) $(CFLAGS) -I$(PHEADERS) -c jeu.c 

clean : testSDL
	rm -f testSDL.o