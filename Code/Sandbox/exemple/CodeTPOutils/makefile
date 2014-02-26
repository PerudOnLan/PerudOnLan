# le binaire à construire (l'exécutable)
BIN = gestionBibliotheque

# Les chemins dans lesquels aller chercher les sources
REPERTOIRES = Ouvrage Menu Bibliotheque FichierOuvrages CollectionOuvrages

# Tous les fichiers sources : les .c trouvés dans le répertoire courant et les sous-répertoires 
SOURCES := $(wildcard *.c) $(foreach dir,$(REPERTOIRES),$(wildcard $(dir)/*.c))
# Tous les fichiers headers : les .h trouvés dans le répertoire courant et les sous-répertoires 
INCLUDES := $(wildcard *.h) $(foreach dir,$(REPERTOIRES),$(wildcard $(dir)/*.h))

# les options de compilations utilisées pour toute compilation :
# tous les warnings
# le debugueur (g)
# on indique les répertoires où peuvent se trouver les include (-Irepertoire1 -Irepertoire2)
INCLUDEDIRS = $(foreach dir, $(REPERTOIRES),-I$(dir) )
# Options de compilation par défaut Warnings all et répertoires où chercher les include
CFLAGS = -Wall -g $(INCLUDEDIRS)

all:  $(BIN) doc

# Options de VALGRIND
VALGRINDFLAGS =--leak-check=yes --leak-resolution=high --num-callers=40 --tool=memcheck --show-reachable=yes


$(BIN): $(SOURCES) $(INCLUDES)
	gcc $(CFLAGS) $(SOURCES) -o $(BIN)


# Production de la documentation doxygen
doc:
	doxygen doxy.conf

# Test de fuites memoire avec valgrind
valgrind: $(BIN)
	valgrind -v $(VALGRINDFLAGS) ./$(BIN) 2>&1

# Nettoyage du repertoire
clean:
	rm -f *.o */*.o *~ *.bak 

cleanall: clean cleandoc
	rm -f  $(BIN) 

cleandoc:
	rm -rf html latex

