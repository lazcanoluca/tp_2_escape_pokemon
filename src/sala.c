#include "estructuras.h"
#include "sala.h"
#include "objeto.h"
#include "interaccion.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lista.h"

#define MAX_LINEA 1024
#define ERROR -1

struct sala {
	lista_t *objetos;
	lista_t *obj_conocidos;
	lista_t *obj_poseidos;
	lista_t *interacciones;
	bool escapada;
};

typedef struct objeto objeto_t;

typedef struct interaccion interaccion_t;

int comparador(void *elemento, void *contexto)
{
	struct objeto *objeto = (struct objeto *)elemento;
	return strcmp(objeto->nombre, (const char *)contexto);
}

bool es_conocido(sala_t *sala, const char *nombre_objeto)
{
	return !lista_buscar_elemento(sala->obj_conocidos, comparador, (void *)nombre_objeto) ? false : true;
}

bool es_poseido(sala_t *sala, const char *nombre_objeto)
{
	return !lista_buscar_elemento(sala->obj_poseidos, comparador, (void *)nombre_objeto) ? false : true;
}

objeto_t *buscar_objeto(lista_t *lista, const char *nombre_objeto)
{
	return (objeto_t *)lista_buscar_elemento(lista, comparador, (void *)nombre_objeto);
}

lista_t *lista_quitar_elemento(lista_t *lista, const char *nombre_objeto, void (*funcion)(void *))
{
	if (!lista || lista_vacia(lista))
		return NULL;

	for (size_t i = 0; i < lista_tamanio(lista); i++) {

		if (comparador(lista_elemento_en_posicion(lista, i), (void *)nombre_objeto) == 0) {

			struct objeto *quitado = (struct objeto *)lista_quitar_de_posicion(lista, i);

			if (quitado && funcion != NULL)
				funcion(quitado);
		}

	}

	return lista;
}

bool quitar_conocido(sala_t *sala, const char *nombre_objeto)
{
	return !lista_quitar_elemento(sala->obj_conocidos, nombre_objeto, NULL) ? false : true;
}

bool quitar_poseido(sala_t *sala, const char *nombre_objeto)
{
	return !lista_quitar_elemento(sala->obj_poseidos, nombre_objeto, NULL) ? false : true;
}

bool destruir_objeto(sala_t *sala, const char *nombre_objeto)
{
	return !lista_quitar_elemento(sala->objetos, nombre_objeto, free) ? false : true;
}

bool agregar_objeto_conocido(sala_t *sala, const char *nombre_objeto)
{
	if (es_conocido(sala, nombre_objeto) || es_poseido(sala, nombre_objeto))
		return false;

	objeto_t *objeto = buscar_objeto(sala->objetos, nombre_objeto);

	if (objeto != NULL) {
		lista_insertar(sala->obj_conocidos, objeto);
		return true;
	}

	return false;
}

bool eliminar_objeto(sala_t *sala, const char *nombre_objeto)
{
	if(!sala || !nombre_objeto)
		return false;

	quitar_poseido(sala, nombre_objeto);
	quitar_conocido(sala, nombre_objeto);

	return destruir_objeto(sala, nombre_objeto) ? true : false;
}

lista_t *crear_lista_objetos(const char *objetos)
{
	char linea[MAX_LINEA];

	FILE *archivo_objetos = fopen(objetos, "r");

	if (!archivo_objetos) {
		return NULL;
	}


	lista_t *lista_objetos = lista_crear();

	if (!archivo_objetos) {
		fclose(archivo_objetos);
		return NULL;
	}


	while ( fgets( linea, MAX_LINEA, archivo_objetos) != NULL) {

		if ( !(lista_objetos = lista_insertar( lista_objetos, objeto_crear_desde_string(linea) )) ) {
			fclose(archivo_objetos);
			lista_destruir(lista_objetos);
			return NULL;
		}
	}

	fclose(archivo_objetos);

	return lista_objetos;

}

lista_t *crear_lista_interacciones(const char *interacciones)
{
	char linea[MAX_LINEA];

	FILE *archivo_interacciones = fopen(interacciones, "r");

	if (!archivo_interacciones) {
		return NULL;
	}


	lista_t *lista_interacciones = lista_crear();

	if (!lista_interacciones) {
		fclose(archivo_interacciones);
		return NULL;
	}


	while( fgets( linea, MAX_LINEA, archivo_interacciones ) != NULL ) {

		if ( !(lista_interacciones = lista_insertar( lista_interacciones, interaccion_crear_desde_string(linea) )) ) {
			fclose(archivo_interacciones);
			lista_destruir(lista_interacciones);
			return NULL;
		}
	}

	fclose(archivo_interacciones);

	return lista_interacciones;

}

bool es_asible(sala_t *sala, const char *nombre_objeto) {

	objeto_t *objeto = buscar_objeto(sala->objetos, nombre_objeto);

	if (objeto != NULL) {
		return objeto->es_asible;
	}

	return false;
}

bool interaccion_valida(struct interaccion *interaccion, const char *verbo, const char *objeto1, const char *objeto2)
{
	if (strcmp(interaccion->verbo, verbo) == 0 &&
		strcmp(interaccion->objeto, objeto1) == 0 &&
		(strcmp(interaccion->objeto_parametro, objeto2) == 0 || strcmp("_", objeto2) == 0)) {
		return true;
	}

	return false;
}

bool interactuar(sala_t *sala, struct interaccion *interaccion, const char *verbo, const char *objeto1, const char *objeto2,
		 void (*mostrar_mensaje)(const char *mensaje, enum tipo_accion accion, void *aux), void *aux)
{	
	switch (interaccion->accion.tipo) {

		case ACCION_INVALIDA:
			return false;

		case DESCUBRIR_OBJETO:

			if (agregar_objeto_conocido(sala, interaccion->accion.objeto)) {
				mostrar_mensaje(interaccion->accion.mensaje, interaccion->accion.tipo, aux);
				return true;
			}
			break;

		case REEMPLAZAR_OBJETO:

			if (eliminar_objeto(sala, objeto2) && agregar_objeto_conocido(sala, interaccion->accion.objeto)) {
				mostrar_mensaje(interaccion->accion.mensaje, interaccion->accion.tipo, aux);
				return true;
			}
			break;

		case ELIMINAR_OBJETO:

			if (eliminar_objeto(sala, objeto1)) {
				mostrar_mensaje(interaccion->accion.mensaje, interaccion->accion.tipo, aux);
				return true;
			}
			break;

		case MOSTRAR_MENSAJE:

			if (mostrar_mensaje != NULL) {
				mostrar_mensaje(interaccion->accion.mensaje, interaccion->accion.tipo, aux);
				return true;
			}
			break;

		case ESCAPAR:

			mostrar_mensaje(interaccion->accion.mensaje, interaccion->accion.tipo, aux);
			sala->escapada = true;
			return true;
			break;

		default:
			break;
	}

	return false;
}


sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{
	if (!objetos || !interacciones)
		return NULL;


	sala_t *sala = calloc(1, sizeof(sala_t));

	if (!sala) {
		sala_destruir(sala);
		return NULL;
	}


	sala->obj_conocidos = lista_crear();
	sala->obj_poseidos = lista_crear();

	if (!sala->obj_conocidos || !sala->obj_poseidos) {
		sala_destruir(sala);
		return NULL;
	}


	sala->interacciones = crear_lista_interacciones(interacciones);
	sala->objetos = crear_lista_objetos(objetos);

	if (!sala->interacciones || !sala->objetos || lista_vacia(sala->interacciones) || lista_vacia(sala->objetos)) {
		sala_destruir(sala);
		return NULL;
	}

	agregar_objeto_conocido(sala, "habitacion");

	return sala;
}

char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
	if (!sala) {
		*cantidad = -1;
		return NULL;
	}

	if (!cantidad) {
		int i = 0;
		cantidad = &i;
	}

	*cantidad = (int)sala->objetos->cantidad;
	char **nombres_objetos = malloc( (unsigned) (*cantidad) * ( sizeof(char *) ) );

	if (nombres_objetos == NULL) {
		free(nombres_objetos);
		*cantidad = -1;
		return NULL;
	}

	for( int i = 0; i < *cantidad; i++ ) {
		struct objeto *objeto = (struct objeto*)lista_elemento_en_posicion(sala->objetos, (size_t)i);
		nombres_objetos[i] = objeto->nombre;
	}

	return nombres_objetos;
}

char **sala_obtener_nombre_objetos_conocidos(sala_t *sala, int *cantidad)
{
	if (!sala) {
		*cantidad = -1;
		return NULL;
	}

	if (!cantidad) {
		int i = 0;
		cantidad = &i;
	}

	*cantidad = (int)sala->obj_conocidos->cantidad;
	char **nombres_objetos = malloc( (unsigned) (*cantidad) * ( sizeof(char *) ) );

	if (nombres_objetos == NULL) {
		free(nombres_objetos);
		*cantidad = -1;
		return NULL;
	}

	for( int i = 0; i < *cantidad; i++ ) {
		struct objeto *objeto = (struct objeto*)lista_elemento_en_posicion(sala->obj_conocidos, (size_t)i);
		nombres_objetos[i] = objeto->nombre;
	}

	return nombres_objetos;
}

char **sala_obtener_nombre_objetos_poseidos(sala_t *sala, int *cantidad)
{
	if (!sala) {
		*cantidad = -1;
		return NULL;
	}

	if (!cantidad) {
		int i = 0;
		cantidad = &i;
	}

	*cantidad = (int)sala->obj_poseidos->cantidad;
	char **nombres_objetos = malloc( (unsigned) (*cantidad) * ( sizeof(char *) ) );

	if (nombres_objetos == NULL) {
		free(nombres_objetos);
		*cantidad = -1;
		return NULL;
	}

	for( int i = 0; i < *cantidad; i++ ) {
		struct objeto *objeto = (struct objeto*)lista_elemento_en_posicion(sala->obj_poseidos, (size_t)i);
		nombres_objetos[i] = objeto->nombre;
	}

	return nombres_objetos;
}

bool sala_agarrar_objeto(sala_t *sala, const char *nombre_objeto)
{
	if (!sala || !nombre_objeto)
		return false;

	if (es_poseido(sala, nombre_objeto))
		return false;

	objeto_t *objeto = buscar_objeto(sala->obj_conocidos, nombre_objeto);

	if (!objeto || !objeto->es_asible)
		return false;

	quitar_conocido(sala, nombre_objeto);
	lista_insertar(sala->obj_poseidos, objeto);

	return true;
}

char* sala_describir_objeto(sala_t *sala, const char *nombre_objeto)
{
	if (!sala || !nombre_objeto)
		return NULL;

	objeto_t *objeto;

	if ( (objeto = buscar_objeto(sala->obj_conocidos, nombre_objeto)) || (objeto = buscar_objeto(sala->obj_poseidos, nombre_objeto)) ) 
		return objeto->descripcion;

	return NULL;
}

int sala_ejecutar_interaccion(sala_t *sala,
				const char *verbo,
				const char *objeto1,
				const char *objeto2,
				void (*mostrar_mensaje)(const char *mensaje, enum tipo_accion accion, void *aux),
				void *aux)
{

	if (!sala || !verbo || !objeto1)
		return 0;

	if ( !es_conocido(sala, objeto1) && !es_poseido(sala, objeto1) )
		return 0;

	if ( es_asible(sala, objeto1) && !es_poseido(sala, objeto1) )
		return 0;


	struct interaccion *interaccion;
	int cant_interacciones = 0;

	for ( size_t i = 0; i < sala->interacciones->cantidad; i++ ) {

		interaccion = (struct interaccion *)lista_elemento_en_posicion(sala->interacciones, i);

		if ( strcmp(interaccion->verbo, verbo) == 0 && interaccion_valida(interaccion, verbo, objeto1, objeto2) ) {

			if (interactuar(sala, interaccion, verbo, objeto1, objeto2, mostrar_mensaje, aux)) {
				cant_interacciones++;
			}
		}
	}

	return cant_interacciones;
}


bool sala_es_interaccion_valida(sala_t *sala,
				const char *verbo,
				const char *objeto1,
				const char *objeto2)
{

	if (!sala || !verbo || !objeto1)
		return false;

	struct interaccion *interaccion;

	for ( size_t i = 0; i < sala->interacciones->cantidad; i++ ) {

		interaccion = (struct interaccion *)lista_elemento_en_posicion(sala->interacciones, i);

		if (interaccion_valida(interaccion, verbo, objeto1, objeto2))
			return true;
	}

	return false;
}

bool sala_escape_exitoso(sala_t *sala)
{
	if (sala->escapada) return true;
	return false;
}

void sala_destruir(sala_t *sala)
{
	if (!sala) return;

	lista_destruir_todo(sala->objetos, free);
	lista_destruir_todo(sala->interacciones, free);
	lista_destruir(sala->obj_conocidos);
	lista_destruir(sala->obj_poseidos);
	free(sala);
}