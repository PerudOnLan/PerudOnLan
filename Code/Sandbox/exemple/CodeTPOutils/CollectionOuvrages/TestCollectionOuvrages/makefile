# le binaire à construire (l'exécutable)
BIN = testsUnitaires

# Les chemins dans lesquels aller chercher les sources
REPERTOIRES = ../../Ouvrage ..

# Tous les sources (trouvés dans le répertoire courant et les répertoires du VPATH
SOURCES := $(wildcard *.c) $(foreach dir,$(REPERTOIRES),$(wildcard $(dir)/*.c))
# Tous les fichiers headers : les .h trouvés dans le répertoire courant et les sous-répertoires 
INCLUDES := $(wildcard *.h) $(foreach dir,$(REPERTOIRES),$(wildcard $(dir)/*.h))

# les options de compilations utilisées pour toute compilation :
# tous les warnings
# le debugueur (g)
# on indique les répertoires où peuvent se trouver les include (-I)
INCLUDEDIRS = $(foreach dir, $(REPERTOIRES),-I$(dir) ) -I../../Bibliotheque
CFLAGS = -Wall -g $(INCLUDEDIRS)

all:  $(BIN) 

# Dans cible: dependences

$(BIN): $(SOURCES) $(INCLUDES)
	gcc $(CFLAGS) $(SOURCES) -o $(BIN) 

clean:
	rm -f *.o */*.o *~ *.bak 

cleanall: clean
	rm -f  $(BIN) 

# DONOT DELETE	