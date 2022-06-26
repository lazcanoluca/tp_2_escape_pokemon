#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

	if (argc != 3) return -1;

	sala_t *sala = sala_crear_desde_archivos(argv[1], argv[2]);

	if (sala == NULL) {
		free(sala);
		printf("Error al crear la sala de escape\n");
		return -1;
	}

	int cant_objetos = 0;

	char **nombres = sala_obtener_nombre_objetos(sala, &cant_objetos);

	//Mostrar todos los objetos en la sala
	printf("Objetos...\n");
	
	for (int i = 0; i < cant_objetos; i++) {
		printf("%i: %s\n", i, nombres[i]);
	}

	free(nombres);

	//Mostrar si son válidas las siguientes interacciones
	//1. examinar habitacion
	//2. abrir pokebola
	//3. usar llave cajon
	//4. quemar mesa

	printf("Interacciones...\n");

	printf("Examinar la habitación: %s\n", sala_es_interaccion_valida(sala, "examinar", "habitacion", "_") ? "Válida" : "Inválida");
	printf("Abrir pokebola: %s\n", sala_es_interaccion_valida(sala, "abrir", "pokebola", "_") ? "Válida" : "Inválida");
	printf("Usar llave en el cajon: %s\n", sala_es_interaccion_valida(sala, "usar", "llave", "cajon") ? "Válida" : "Inválida");
	printf("Quemar la mesa: %s\n", sala_es_interaccion_valida(sala, "quemar", "mesa", "_") ? "Válida" : "Inválida");
	
	sala_destruir(sala);

	return 0;
}
