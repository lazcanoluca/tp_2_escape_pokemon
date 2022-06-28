#include "estructuras.h"
#include "interaccion.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct accion *accion_crear_desde_string( struct accion *acc, const char *string )
{
	if (string == NULL)
		return NULL;

	char tipo;

	int parametros_leidos = sscanf(string, "%c:%[^:]:%[^\n]\n", &tipo, acc->objeto, acc->mensaje);

	if (parametros_leidos != 3)
		return NULL;

	if (!strcmp(acc->objeto, "_"))
		strcpy(acc->objeto, "");

	switch (tipo) {
		case 'd':
			acc->tipo = DESCUBRIR_OBJETO;
			break;
		case 'r':
			acc->tipo = REEMPLAZAR_OBJETO;
			break;
		case 'e':
			acc->tipo = ELIMINAR_OBJETO;
			break;
		case 'm':
			acc->tipo = MOSTRAR_MENSAJE;
			break;
		case 'g':
			acc->tipo = ESCAPAR;
			break;
		default:
			acc->tipo = ACCION_INVALIDA;
			break;
	};

	return acc;
}

struct interaccion *interaccion_crear_desde_string(const char *string)
{
	if (string == NULL) return NULL;

	struct interaccion *inte = malloc(sizeof( struct interaccion ));

	if (inte == NULL) {
		free(inte);
		return NULL;
	}

	char string_accion[1024];

	int parametros_leidos = sscanf(string, "%[^;];%[^;];%[^;];%[^\n]\n", inte->objeto, inte->verbo, inte->objeto_parametro, string_accion);
		
	if (parametros_leidos != 4) {
		free(inte);
		return NULL;
	}

	if (!strcmp(inte->objeto_parametro, "_")) strcpy(inte->objeto_parametro, "");

	struct accion *acc = malloc(sizeof( struct accion ));

	if (acc == NULL) {
		free(acc);
		free(inte);
		return NULL;
	}

	if (accion_crear_desde_string(acc, string_accion) == NULL) {
		free(acc);
		free(inte);
		return NULL;
	}

	inte->accion = *accion_crear_desde_string(acc, string_accion);

	free(acc);
	
	return inte;
}