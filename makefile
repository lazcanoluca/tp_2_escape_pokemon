VALGRIND_FLAGS = -s --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2
CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
CC = gcc
FILES_EJ = ejemplo/objetos.txt ejemplo/interacciones.txt
OBJ_ESCAPE = src/*.c escape_pokemon.c
OBJ_PRUEBAS = src/*.c pruebas.c
OBJ_PRUEBAS_CHANU = src/*.c pruebas_chanutron.c

all: clean valgrind

escape_pokemon : $(OBJ_ESCAPE)
	$(CC) $(CFLAGS) $(OBJ_ESCAPE) -o escape_pokemon

valgrind : escape_pokemon
	valgrind $(VALGRIND_FLAGS) ./escape_pokemon $(FILES_EJ)

pruebas : $(OBJ_PRUEBAS)
	$(CC) $(CFLAGS) $(OBJ_PRUEBAS) -o pruebas

pruebas_chanu : $(OBJ_PRUEBAS_CHANU)
	$(CC) $(CFLAGS) $(OBJ_PRUEBAS_CHANU) -o pruebas_chanu

valgrind-pruebas : pruebas
	valgrind $(VALGRIND_FLAGS) ./pruebas

valgrind-pruebas_chanu : pruebas_chanu
	valgrind $(VALGRIND_FLAGS) ./pruebas_chanu

game_engine : game_engine.c
	$(CC) controlador.o game_engine.c -o game_engine
	./game_engine

juego_con_ncurses : juego_con_ncurses.c
	$(CC) juego_con_ncurses.c -lncurses -o juego_con_ncurses

clean:
	rm -f escape_pokemon pruebas *.o