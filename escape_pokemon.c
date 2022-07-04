
#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <string.h>

#define ERROR -1

void mostrar_mensaje(const char *mensaje, enum tipo_accion accion, void *aux)
{
	printf("%s\n", mensaje);
}

int main(int argc, char *argv[])
{
	if (argc != 3)
                return ERROR;

	sala_t *sala = sala_crear_desde_archivos(argv[1], argv[2]);

	if (!sala) {
		sala_destruir(sala);
		printf("Error al crear la sala de escape\n");
		return ERROR;
	}

	bool condicion_salida = false;

        /*INICIO JUEGO*/
        char input[100];
        char comando[100];
        strcpy(comando, "");
        char objeto1[100];
        strcpy(objeto1, "");
        char objeto2[100];
        strcpy(objeto2, "");

        system("clear");
        printf("\nAbrís los ojos con dificultad.\n");
        sleep(2);
        printf("\nLo primero que sentís es un fuerte dolor de cabeza.\n");
        sleep(2);
        printf("\nLuego te invade la oscuridad del lugar. No se ve nada.\n");
        sleep(2);
        printf("\nNo sabés dónde estás. No sabés dónde estabas. No sabés cómo llegaste.\n");
        sleep(2);
        printf("\nSeguro saliste anoche a festejar con tus amigos que les fue bien en Algoritmos II, \nla noche se descontroló, y ahora estás tirado en algún callejón.\n");
        sleep(3);
        printf("\n\nDe a poco tus ojos se acostumbran a la oscuridad. Al prestar más atención, llegas a discernir paredes.\n");
        sleep(3);
        printf("\nTe incorporas y miras a tu alrededor, en la oscuridad. Parece que estás en una especie de habitación.\n");
        sleep(3);
        printf("\nQuizás sea buena idea >examinar< con más detalle la habitación.\n\n\n");
        sleep(3);
        system("clear");


	while (condicion_salida == false)
	{
		int cant_conocidos = 0;
		char **conocidos = sala_obtener_nombre_objetos_conocidos(sala, &cant_conocidos);
		printf("\nLo que ves:\n");
		
		for (int i = 0; i < cant_conocidos; i++) {
			printf("\t- %s\n", conocidos[i]);
		}
		free(conocidos);

		int cant_poseidos = 0;
		char **poseidos = sala_obtener_nombre_objetos_poseidos(sala, &cant_poseidos);
		printf("\nTu inventario:\n");
		
		for (int i = 0; i < cant_poseidos; i++) {
			printf("\t -%s\n", poseidos[i]);
		}
		free(poseidos);
		printf("\n\n\n\na para ayuda ");
                printf("\n> ");
		fgets(input, 100, stdin);
		sscanf(input, "%s %s %s", comando, objeto1, objeto2);
                printf("\n");

		if(!strcmp(comando, "a") || !strcmp(comando, "ayuda")){

			printf("\nComandos disponibles:\n");
			printf("\t- agarrar <objeto>: para agarrar un objeto de la sala.\n");
			printf("\t- describir <objeto>: para ver una descripcion del objeto.\n");
                        printf("\t- <accion> <objeto>: para interactuar con, o usar, un objeto.\n");
                        printf("\t- <accion> <objeto1> <objeto2>: para interactuar sobre el objeto2 con el objeto1.\n");
			printf("\t- salir / q: para salir del juego\n");
                        printf("\t- ayuda / a: obtener ayuda\n");
		
                } else if(!strcmp(comando, "agarrar")){

			if(sala_agarrar_objeto(sala, objeto1))
                                printf("Objeto agregado al inventario: %s\n", objeto1);

		} else if(!strcmp(comando, "describir")){

			char *descripcion = sala_describir_objeto(sala, objeto1);
			if (descripcion)
				printf("%s\n", descripcion);

		} else if( (!strcmp(comando, "salir") || !strcmp(comando, "q")) && strcmp(objeto1, "") == 0){

			condicion_salida = true;

		} else if( strcmp(comando, "") != 0 && strcmp(objeto1, "") != 0 ){

			if (sala_ejecutar_interaccion(sala, comando, objeto1, objeto2, mostrar_mensaje, NULL) == 0)
                        {
                                printf("No se puede hacer eso, seguí probando.\n");
                        }

		}
		
		if(sala_escape_exitoso(sala)){
			printf("GANASTE\n");
			condicion_salida = true;
		}
	}
	
	sala_destruir(sala);

	return 0;
}
