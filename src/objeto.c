#include "objeto.h"
#include "estructuras.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define DELIM ";"

struct objeto *objeto_crear_desde_string(const char *string)
{
	if (!string) return NULL;

	char es_asible[6];

	struct objeto *obj = malloc(sizeof( struct objeto ));

	if (obj == NULL) {
		free(obj);
		return NULL;
	}

	int parametros_leidos = sscanf(string, "%[^;];%[^;];%[^\n]\n", obj->nombre, obj->descripcion, es_asible);

	if( parametros_leidos != 3 ) {
		free(obj);
		return NULL;
	}

	if( !strcmp( es_asible, "true" )) {
		obj->es_asible = true;
	} else if (!strcmp( es_asible, "false" )) {
		obj->es_asible = false;
	} else {
		free(obj);
		return NULL;
	}
	
	return obj;
}
