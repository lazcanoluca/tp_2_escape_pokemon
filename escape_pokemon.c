#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

void imprimir_pokebola()
{
		puts(" \
				────────▄███████████▄────────\n \
				─────▄███▓▓▓▓▓▓▓▓▓▓▓███▄─────\n \
				────███▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓███────\n \
				───██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██───\n \
				──██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██──\n \
				─██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██─\n \
				██▓▓▓▓▓▓▓▓▓███████▓▓▓▓▓▓▓▓▓██\n \
				██▓▓▓▓▓▓▓▓██░░░░░██▓▓▓▓▓▓▓▓██\n \
				██▓▓▓▓▓▓▓██░░███░░██▓▓▓▓▓▓▓██\n \
				███████████░░███░░███████████\n \
				██░░░░░░░██░░███░░██░░░░░░░██\n \
				██░░░░░░░░██░░░░░██░░░░░░░░██\n \
				██░░░░░░░░░███████░░░░░░░░░██\n \
				─██░░░░░░░░░░░░░░░░░░░░░░░██─\n \
				──██░░░░░░░░░░░░░░░░░░░░░██──\n \
				───██░░░░░░░░░░░░░░░░░░░██───\n \
				────███░░░░░░░░░░░░░░░███────\n \
				─────▀███░░░░░░░░░░░███▀─────\n \
				────────▀███████████▀────────\n");
}

void mostrar_mensaje(const char *mensaje, enum tipo_accion accion, void *aux)
{
	printf("%s", mensaje);
}

int main(int argc, char *argv[])
{
	if (argc != 3) return -1;

	sala_t *sala = sala_crear_desde_archivos(argv[1], argv[2]);

	if (sala == NULL) {
		free(sala);
		printf("Error al crear la sala de escape\n");
		return -1;
	}

	//int cant_objetos = 0;
	bool condicion_salida = false;

	//char **nombres = sala_obtener_nombre_objetos(sala, &cant_objetos);

	while (condicion_salida == false)
	{
		char input[100];
		char comando[100];
		strcpy(comando, "");
		char objeto1[100];
		strcpy(objeto1, "");
		char objeto2[100];
		strcpy(objeto2, "");

		int cant_conocidos = 0;
		char **conocidos = sala_obtener_nombre_objetos_conocidos(sala, &cant_conocidos);
		printf("\nObjetos en conocidos:\n");
		
		for (int i = 0; i < cant_conocidos; i++) {
			printf("%i: %s\n", i, conocidos[i]);
		}
		free(conocidos);

		int cant_poseidos = 0;
		char **poseidos = sala_obtener_nombre_objetos_poseidos(sala, &cant_poseidos);
		printf("\nInventario:\n");
		
		for (int i = 0; i < cant_poseidos; i++) {
			printf("%i: %s\n", i, poseidos[i]);
		}
		free(poseidos);

		printf("\nIngrese una interaccion válida: ");
		fgets(input, 100, stdin);
		sscanf(input, "%s %s %s", comando, objeto1, objeto2);

		if(!strcmp(comando, "ayuda")){

			printf("\nComandos disponibles:\n");
			printf("-agarrar (objeto): para agarrar un objeto de la sala\n");
			printf("-describir (objeto): para ver una descripcion del objeto\n");
			printf("-salir: para salir del juego\n");
			printf("\nPodes realizar las siguientes acciones seguidas de los objetos de la sala:\n\tExaminar\n\tUsar\n\tAbrir\n\tSalir\n");
		}
		else if(!strcmp(comando, "agarrar")){
			sala_agarrar_objeto(sala, objeto1);				
		}
		else if(!strcmp(comando, "describir")){
			char *descripcion = sala_describir_objeto(sala, objeto1);
			if (!!descripcion)
				printf("%s\n", descripcion);
				
		}
		else if(!strcmp(comando, "salir") && strcmp(objeto1, "") == 0){
			condicion_salida = true;
		}
		else if(strcmp(comando, "") != 0 && strcmp(objeto1, "") != 0){
			sala_ejecutar_interaccion(sala, comando, objeto1, objeto2, mostrar_mensaje, NULL);
		}
		
		if(sala_escape_exitoso(sala)){
			printf("GANASTE\n");
			condicion_salida = true;
		}
		
	}

	// //Mostrar todos los objetos en la sala
	// printf("Objetos...\n");
	
	// for (int i = 0; i < cant_objetos; i++) {
	// 	printf("%i: %s\n", i, nombres[i]);
	// }

	// free(nombres);

	// //Mostrar si son válidas las siguientes interacciones
	// //1. examinar habitacion
	// //2. abrir pokebola
	// //3. usar llave cajon
	// //4. quemar mesa

	// printf("Interacciones...\n");

	// printf("Examinar la habitación: %s\n", sala_es_interaccion_valida(sala, "examinar", "habitacion", "_") ? "Válida" : "Inválida");
	// printf("Abrir pokebola: %s\n", sala_es_interaccion_valida(sala, "abrir", "pokebola", "_") ? "Válida" : "Inválida");
	// printf("Usar llave en el cajon: %s\n", sala_es_interaccion_valida(sala, "usar", "llave", "cajon") ? "Válida" : "Inválida");
	// printf("Quemar la mesa: %s\n", sala_es_interaccion_valida(sala, "quemar", "mesa", "_") ? "Válida" : "Inválida");
	
	sala_destruir(sala);

	return 0;
}
