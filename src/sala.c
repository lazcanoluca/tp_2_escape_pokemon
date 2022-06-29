#include "estructuras.h"
#include "sala.h"
#include "objeto.h"
#include "interaccion.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../lib/tda_lista/lista.h"
// #include "lista.h"

#define MAX_LINEA 1024
#define ERROR -1

#define MSJ_OBJETO_YA_CONOCIDO "Nada nuevo, seguí buscando."
// #define MSJ_

struct sala {
	lista_t *objetos;
	lista_t *obj_conocidos;
	lista_t *obj_poseidos;
	lista_t *interacciones;
	bool escapada;
};


int comparador(void *elemento, void *contexto)
{
	struct objeto *objeto = (struct objeto *)elemento;
	return strcmp(objeto->nombre, (const char *)contexto);
	// return strcmp(elemento->nombre, contexto);
}

lista_t *lista_quitar_elemento(lista_t *lista, int (*comparador)(void *, void *), void *contexto)
{

	if (!lista || !comparador || lista_vacia(lista)) return NULL;

	for (size_t i = 0; i < lista_tamanio(lista); i++) {
		if (comparador(lista_elemento_en_posicion(lista, i), contexto) == 0) {
			struct objeto *quitado = (struct objeto *)lista_quitar_de_posicion(lista, i);
			if (!quitado)
				free(quitado);
		}
	}

	return lista;
}

bool agregar_objeto_conocido(sala_t *sala, const char *nombre_objeto)
{
	// Si ya se descubrió el elemento.
	if ( lista_buscar_elemento(sala->obj_conocidos, comparador, (void *)nombre_objeto) != NULL ) {
		printf("obj ya conocido\n");
		return false;
	}

	struct objeto *objeto = (struct objeto *)lista_buscar_elemento(sala->objetos, comparador, (void *)nombre_objeto);

	if (objeto != NULL) {
		lista_insertar(sala->obj_conocidos, objeto);
		return true;
	}

	return false;
}

void eliminar_objeto(sala_t *sala, const char *nombre_objeto)
{
	lista_quitar_elemento(sala->obj_poseidos, comparador, (void *)nombre_objeto);
	lista_quitar_elemento(sala->obj_conocidos, comparador, (void *)nombre_objeto);
	lista_quitar_elemento(sala->objetos, comparador, (void *)nombre_objeto);

}

// sala_t *sala_crear()
// {
// 	sala_t* sala = calloc(1, sizeof(sala_t));
// 	return sala;
// }

sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{
	FILE *archivo_objetos = fopen( objetos, "r" );
	if (archivo_objetos == NULL) return NULL;

	FILE *archivo_interacciones = fopen( interacciones, "r" );
	if (archivo_interacciones == NULL) return NULL;

	char linea[MAX_LINEA];

	sala_t *sala = malloc(sizeof(sala_t));

	if (sala == NULL) {
		free(sala);
		return NULL;
	}

	lista_t *lista_objetos = lista_crear();

	while ( fgets( linea, MAX_LINEA, archivo_objetos) != NULL) {

		if ( !(lista_objetos = lista_insertar( lista_objetos, objeto_crear_desde_string(linea) )) ) {
			free(sala);
			lista_destruir(lista_objetos);
			return NULL;
		}

	}

	sala->objetos = lista_objetos;
	
	lista_t *lista_interacciones = lista_crear();

	while( fgets( linea, MAX_LINEA, archivo_interacciones ) != NULL ) {

		if ( !(lista_interacciones = lista_insertar( lista_interacciones, interaccion_crear_desde_string(linea) )) ) {
			free(sala);
			lista_destruir(lista_interacciones);
			lista_destruir(lista_objetos);
			return NULL;
		}
	}

	sala->interacciones = lista_interacciones;

	fclose( archivo_objetos );
	fclose( archivo_interacciones );

	if (sala->interacciones->cantidad == 0) {
		sala_destruir(sala);
		return NULL;
	}

	sala->obj_conocidos = lista_crear();
	sala->obj_poseidos = lista_crear();

	agregar_objeto_conocido(sala, "habitacion");
	sala->escapada = false;

	return sala;
}

char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
	if (sala == NULL) {
		*cantidad = -1;
		return NULL;
	}

	if (cantidad == NULL) {
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
	if (sala == NULL) {
		*cantidad = -1;
		return NULL;
	}

	if (cantidad == NULL) {
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
		if (sala == NULL) {
		*cantidad = -1;
		return NULL;
	}

	if (cantidad == NULL) {
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
	// Si ya se posee el elemento.
	if ( lista_buscar_elemento(sala->obj_poseidos, comparador, (void *)nombre_objeto) != NULL ) {
		printf("Ya posees este objeto.");
		return false;
	}

	struct objeto *objeto = (struct objeto *)lista_buscar_elemento(sala->obj_conocidos, comparador, (void *)nombre_objeto);

	if (!objeto) {
		printf("Todavía no encontraste ninguno de estos.\n");
		return false;
	}

	if (!objeto->es_asible) {
		printf("No te lo podés llevar, ¡seguí intentando!\n");
		return false;
	}

	lista_insertar(sala->obj_poseidos, objeto);
	printf("Nuevo objeto adquirido: %s\n", nombre_objeto);
	return true;
}

char* sala_describir_objeto(sala_t *sala, const char *nombre_objeto)
{
	struct objeto *objeto;
	// struct objeto *objeto = ((struct objeto *)lista_buscar_elemento(sala->obj_conocidos, comparador, (void *)nombre_objeto) || (struct objeto *)lista_buscar_elemento(sala->obj_poseidos, comparador, (void *)nombre_objeto));

	if ( (objeto = (struct objeto *)lista_buscar_elemento(sala->obj_conocidos, comparador, (void *)nombre_objeto)) || 
	     (objeto = (struct objeto *)lista_buscar_elemento(sala->obj_poseidos, comparador, (void *)nombre_objeto))) {
		return objeto->descripcion;
	}


	// if ( objeto != NULL )
	// 	return objeto->descripcion;

	return NULL;
}

bool interactuar(sala_t *sala, struct interaccion *interaccion, const char *verbo, const char *objeto1, const char *objeto2,
		 void (*mostrar_mensaje)(const char *mensaje, enum tipo_accion accion, void *aux), void *aux)
{	
	switch (interaccion->accion.tipo) {

		case ACCION_INVALIDA:
			return false;

		case DESCUBRIR_OBJETO:
			printf("\n\nentró a descubrir objeto\n\n");
			if (agregar_objeto_conocido(sala, interaccion->accion.objeto)) {
				mostrar_mensaje(interaccion->accion.mensaje, interaccion->accion.tipo, aux);
			}
			break;

		case REEMPLAZAR_OBJETO:
			printf("\n\nentró a reemplazar objeto\n\n");
			eliminar_objeto(sala, objeto2);
			if (agregar_objeto_conocido(sala, interaccion->accion.objeto)) {
				mostrar_mensaje(interaccion->accion.mensaje, interaccion->accion.tipo, aux);
			}
			break;

		case ELIMINAR_OBJETO:
			printf("\n\nentró a eliminar objeto\n\n");
			eliminar_objeto(sala, objeto1);
			mostrar_mensaje(interaccion->accion.mensaje, interaccion->accion.tipo, aux);
			break;

		case MOSTRAR_MENSAJE:
			printf("\n\nentró a mostrar mensaje\n\n");
			mostrar_mensaje(interaccion->accion.mensaje, interaccion->accion.tipo, aux);
			break;

		case ESCAPAR:
		printf("\n\nentró a escapar\n\n");
			sala->escapada = true;
			break;

		default:
			break;
	}
	return true;
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

int sala_ejecutar_interaccion(sala_t *sala,
				const char *verbo,
				const char *objeto1,
				const char *objeto2,
				void (*mostrar_mensaje)(const char *mensaje, enum tipo_accion accion, void *aux),
				void *aux)
{
	if ( !lista_buscar_elemento(sala->obj_conocidos, comparador, (void *)objeto1) && !lista_buscar_elemento(sala->obj_poseidos, comparador, (void *)objeto1) ) {
		printf("No conoces o no tenes el objeto\n");
		return 0;
	}

	struct interaccion *interaccion;
	int cant_interacciones = 0;

	for ( size_t i = 0; i < sala->interacciones->cantidad; i++ ) {

		interaccion = (struct interaccion *)lista_elemento_en_posicion(sala->interacciones, i);

		if ( strcmp(interaccion->verbo, verbo) == 0 && interaccion_valida(interaccion, verbo, objeto1, objeto2) ) {
			printf("\nentró\n");
			interactuar(sala, interaccion, verbo, objeto1, objeto2, mostrar_mensaje, aux);
			cant_interacciones++;
		}
	}

	return cant_interacciones;
}


// bool sala_es_interaccion_valida(sala_t *sala, const char *verbo, const char *objeto1,
// 				const char *objeto2)
// {

// 	if (sala == NULL || verbo == NULL || objeto1 == NULL || objeto2 == NULL) return NULL;

// 	for ( int i = 0; i < sala->interacciones->cantidad; i++ ) {
// 		if (
// 			!strcmp( (struct interaccion *)lista_elemento_en_posicion(sala->interacciones, i)->verbo, verbo) &&
// 			!strcmp( (struct interaccion *)lista_elemento_en_posicion(sala->interacciones, i)->objeto, objeto1) &&
// 			!strcmp( (struct interaccion *)lista_elemento_en_posicion(sala->interacciones, i)->objeto_parametro, objeto2)
// 		) return true;
// 	}
// 	return false;
// }


bool sala_es_interaccion_valida(sala_t *sala,
				const char *verbo,
				const char *objeto1,
				const char *objeto2)
{

	if (!sala || !verbo || !objeto1 || !objeto2)
		return NULL;

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
	lista_destruir_todo(sala->objetos, free);
	lista_destruir_todo(sala->interacciones, free);
	lista_destruir(sala->obj_conocidos);
	lista_destruir(sala->obj_poseidos);
	free(sala);
}
