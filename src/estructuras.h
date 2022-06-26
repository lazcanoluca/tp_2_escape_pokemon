#ifndef ESTRUCTURAS_H_
#define ESTRUCTURAS_H_

#include <stdbool.h>
#include "sala.h"

#define MAX_NOMBRE 20
#define MAX_VERBO  20
#define MAX_TEXTO  200

struct accion {
	enum tipo_accion tipo;
	char objeto[MAX_NOMBRE];
	char mensaje[MAX_TEXTO];
};

struct interaccion {
	char objeto[MAX_NOMBRE];
	char verbo[MAX_VERBO];
	char objeto_parametro[MAX_NOMBRE];
	struct accion accion;
};

struct objeto {
	char nombre[MAX_NOMBRE];
	char descripcion[MAX_TEXTO];
	bool es_asible;
};

#endif // ESTRUCTURAS_H_
