# VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2
CFLAGS =-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
CC = gcc


pruebas: src/*.c pruebas.c pruebas
	$(CC) $(CFLAGS) src/*.c pruebas.c -o pruebas

escape_pokemon: src/*.c escape_pokemon.c escape_pokemon
	$(CC) $(CFLAGS) src/*.c escape_pokemon.c -o escape_pokemon