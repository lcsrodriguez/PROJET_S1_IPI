# Makefile général du projet
# Lucas RODRIGUEZ (ENSIIE 1A)

CC=gcc					# Compilateur
FLAGS=-Wall -Wextra			# Flags
TARGET=prog				# Nom du programme final (exécutable)

all: $(TARGET)			

$(TARGET): grid.o stack.o main.o
	$(CC) $(FLAGS) $^ -o $@

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@
