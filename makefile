VALGRIND_FLAGS = --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2
CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
CC = gcc
FILES_EJ = ejemplo/objetos.txt ejemplo/interacciones.txt
OBJ_ESCAPE = src/*.c escape_pokemon.c
OBJ_PRUEBAS = src/*.c pruebas.c

all: clean valgrind

escape_pokemon : $(OBJ_ESCAPE)
	$(CC) $(CFLAGS) $(OBJ_ESCAPE) -o escape_pokemon

valgrind : escape_pokemon
	valgrind $(VALGRIND_FLAGS) ./escape_pokemon $(FILES_EJ)

pruebas : $(OBJ_PRUEBAS)
	$(CC) $(CFLAGS) $(OBJ_PRUEBAS) -o pruebas

valgrind-pruebas : pruebas
	valgrind $(VALGRIND_FLAGS) ./pruebas

clean:
	rm -f escape_pokemon pruebas *.o