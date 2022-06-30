#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include "sala.h"
#include "lista.h"
#include "estructuras.h"

#include "controlador/controlador.h"

#include <string.h>

#define MAX_FILAS 10
#define MAX_COLUMNAS 20

#define FIL_INICIAL 5
#define COL_INICIAL 1

#define FIL_POKEBOLA 7
#define COL_POKEBOLA 9

typedef struct sala {
	lista_t *objetos;
	lista_t *obj_conocidos;
	lista_t *obj_poseidos;
	lista_t *interacciones;
	bool escapada;
} sala_t;

static int comparador(void *elemento, void *contexto)
{
	struct objeto *objeto = (struct objeto *)elemento;
	return strcmp(objeto->nombre, (const char *)contexto);
	// return strcmp(elemento->nombre, contexto);
}

void main_menu()
{
        printf("\n \
╦  ┌─┐  ┌─┐┌─┐┌┬┐┌┐ ┬─┐┌─┐  ┌┬┐┌─┐  ╔╦╗┌─┐┌─┐ \n \
║  ├─┤  └─┐│ ││││├┴┐├┬┘├─┤   ││├┤   ║║║├─┤│   \n \
╩═╝┴ ┴  └─┘└─┘┴ ┴└─┘┴└─┴ ┴  ─┴┘└─┘  ╩ ╩┴ ┴└─┘ \n");

    printf("type q to quit\n");
    printf("type p to play\n");
    printf("type i for instructions\n");

}

void crear_escenario(sala_t *sala, int *x, int *y)
{
    system("clear");

    char matriz[MAX_FILAS][MAX_COLUMNAS];

    printf("\n");
    for (int i = 0; i < MAX_FILAS; i++){
        printf("#");
        for (int j = 0; j < MAX_COLUMNAS; j++){
            if (i == 0 || i == MAX_FILAS-1) {
                if ((j == 3 || j == 4 || j == 5) && !!lista_buscar_elemento(sala->obj_conocidos, comparador, "puerta") && i == 0) {
                    printf("_");
                } else {
                    printf("#");
                }
            } else if (i == *y && j == *x) {
                printf("p");
            } else if (i == FIL_POKEBOLA && j == COL_POKEBOLA && !!lista_buscar_elemento(sala->obj_conocidos, comparador, "pokebola")) {
                printf("O");
            } else if (i == FIL_POKEBOLA && j == COL_POKEBOLA && !!lista_buscar_elemento(sala->obj_conocidos, comparador, "llave")) {
                printf("{");
            }
            else {
                printf(" ");   
            }
        }
        printf("#");
        printf("\n");
    }
}

void mover_personaje(int *x, int *y, char movimiento){

    if (movimiento == 'w' && *y > 1){
        (*y)--;
    }
    if (movimiento == 's' && *y < MAX_FILAS-2){
        (*y)++;
    }
    if (movimiento == 'd' && *x < MAX_COLUMNAS-1){
        (*x)++;
    }
    if (movimiento == 'a' && *x > 1){
        (*x)--;
    }
}

bool es_movimiento_valido(char movimiento){
    return ((movimiento == 'w') || (movimiento == 's') || (movimiento == 'd') || (movimiento == 'a') || (movimiento == 'q'));
}

void pedir_movimiento(char* ref_movimiento){

    printf("Ingrese un movimiento: ");
    scanf(" %c", ref_movimiento);

    while (!(es_movimiento_valido(*ref_movimiento))){
            printf("Ingrese un movimiento valido: ");
            scanf(" %c", ref_movimiento);
    }
}

int main (int argc, char *argv[])
{
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);

    printf ("lines %d\n", w.ws_row);
    printf ("columns %d\n", w.ws_col);

    sala_t *sala = sala_crear_desde_archivos(argv[1], argv[2]);

    main_menu();
    inicializar_controlador();

    char movimiento;

    int y = FIL_INICIAL;
    int x = COL_INICIAL;

    while(movimiento != 'q'){
        crear_escenario(sala, &x, &y);
        pedir_movimiento(&movimiento);
        mover_personaje(&x, &y, movimiento);
        system("clear");
    }

    sala_destruir(sala);
    terminar_controlador();

    return 0;
}