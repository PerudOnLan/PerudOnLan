CC = gcc
CFLAGS = -Wall -g
SDLLIBS = -lSDLmain -lSDL -lSDL_image -lSDL_ttf -lSDL_net -lSDL_net2

all: testSDL clean

testSDL : testSDL.o
	$(CC) $(CFLAGS) testSDL.o -L$(HOME)/Boulot/PerudOnLan/Sources_et_libs/libs $(SDLLIBS) -o TestSDL 

testSDL.o : testSDL.c testSDL.h
	$(CC) $(CFLAGS) -I$(HOME)/Boulot/PerudOnLan/Sources_et_libs/headers -c testSDL.c

clean : testSDL
	rm -f testSDL.o