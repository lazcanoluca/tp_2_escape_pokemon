VALGRIND_FLAGS = --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2
CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
CC = gcc
FILES_EJ = ejemplo/objetos.txt ejemplo/interacciones.txt
OBJ_ESCAPE = src/*.c lib/tda_lista/*.c escape_pokemon.c
OBJ_PRUEBAS = src/*.c lib/tda_lista/*.c pruebas.c


# objects = src/*.c lib/tda_lista/*.c lib/game_engine/*.c escape_pokemon.c

# sala_escape : $(objects)
# 	gcc -o sala_escape $(objects)

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



# main.o : src/*.c
# 	gcc -c src/*.c

# interaccion.o : src/interaccion.c
# 	gcc -c src/interaccion.c

# objeto.o : src/objeto.c
# 	gcc -c src/objeto.c

# sala.o : src/sala.c
# 	gcc -c src/sala.c

# # game_engine.o : lib/game_engine/*.c
# # 	gcc -c lib/game_engine/*.c

# lista.o : lib/tda_lista/lista.c
# 	gcc -c lib/tda_lista/lista.c




# pruebas :

# valgrind-pruebas :


# run:

# clean:

# pruebas: compile run

# compile:
# 	gcc src/*c pruebas.c

# run:
# 	./pruebas

# pruebas: compile-pruebas run-pruebas

# compile-pruebas: src/*.c pruebas.c
# 	$(CC) $(CFLAGS) src/*.c pruebas.c -o pruebas

# run-pruebas:
# 	./pruebas

# compile-escape_pokemon: src/*.c escape_pokemon.c
# 	$(CC) $(CFLAGS) src/*.c escape_pokemon.c -o escape_pokemon