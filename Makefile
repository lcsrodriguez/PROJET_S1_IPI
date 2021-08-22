# Makefile général du projet
# Lucas RODRIGUEZ (ENSIIE 1A)

# Variables globales
CC=gcc						# Compilateur
FLAGS=-Wall -Wextra			# Flags
TARGET=prog					# Nom du programme final (exécutable)


all: $(TARGET)			

$(TARGET): grid.o stack.o main.o
	$(CC) $(FLAGS) $^ -o $@

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

# Commande pour supprimer les fichiers objets
clean:
    rm -rf *.o

# Commande pour supprimer tout ce qui peut être regénéré
mrproper: clean
    rm -rf $(TARGET)