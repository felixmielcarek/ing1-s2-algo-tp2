###############################################################################
# ESIEE Paris
# Algorithmique et programmation pour l'ingénieur
#
# TP2 — Tableau dynamique
#
# Ce Makefile est fourni comme base de travail pour les étudiants.
# Ne pas modifier sa structure générale dans le cadre du TP.
###############################################################################

# Compilateur utilisé
CC = gcc

# Options de compilation :
# -Wall   : Active tous les avertissements de base
# -Wextra : Active des avertissements supplémentaires
# -g      : Génère les informations de débogage
# -O0     : Désactive les optimisations pour un meilleur débogage
CFLAGS = -Wall -Wextra -g -O0

# Bibliothèques utilisées (ajoutez d'autres si nécessaire)
LIBS = -lm

# Nom de l'exécutable final
EXEC = test_unit

# Liste des fichiers sources
SRC = test_unit.c vector.c

# Liste des fichiers objets (remplace .c par .o)
OBJ = $(SRC:.c=.o)

# Règle principale : compilation de l'exécutable
all: $(EXEC)

# Compilation de l'exécutable
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# Compilation des fichiers objets de manière générique
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

# Exécution avec Valgrind pour détecter les erreurs mémoire
valgrind: $(EXEC)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXEC)

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f $(OBJ) $(EXEC) *~

# Nettoyage complet (y compris les fichiers de sauvegarde et de débogage)
distclean: clean
	rm -f $(EXEC).gdb
	
###############################################################################
# End of Makefile
###############################################################################

