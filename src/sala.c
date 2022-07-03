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
        // if (!lista || !comparador || !nombre_objeto)
        //         return NULL;
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

sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{
        if (!objetos || !interacciones)
                return NULL;
	// char linea[MAX_LINEA];


	// FILE *archivo_objetos = fopen( objetos, "r" );

	// if (!archivo_objetos)
        //         return NULL;

	// FILE *archivo_interacciones = fopen( interacciones, "r" );

	// if (!archivo_interacciones) {
        //         fclose(archivo_objetos);
        //         return NULL;
        // }


	sala_t *sala = calloc(1, sizeof(sala_t));

	if (!sala) {
                // fclose(archivo_objetos);
                // fclose(archivo_interacciones);
		sala_destruir(sala);
		return NULL;
	}


        sala->obj_conocidos = lista_crear();
	sala->obj_poseidos = lista_crear();
        
        if (!sala->obj_conocidos || !sala->obj_poseidos) {
                sala_destruir(sala);
                return NULL;
        }

        // if (!sala->obj_poseidos) {
        //         fclose(archivo_objetos);
        //         fclose(archivo_interacciones);
        //         lista_destruir(sala->obj_conocidos);
        //         free(sala);
        //         return NULL;
        // }


	// lista_t *lista_objetos = lista_crear();

	// while ( fgets( linea, MAX_LINEA, archivo_objetos) != NULL) {

	// 	if ( !(lista_objetos = lista_insertar( lista_objetos, objeto_crear_desde_string(linea) )) ) {
	// 		free(sala);
	// 		lista_destruir(lista_objetos);
	// 		return NULL;
	// 	}

	// }

	// sala->objetos = lista_objetos;

	

	// while( fgets( linea, MAX_LINEA, archivo_interacciones ) != NULL ) {

	// 	if ( !(lista_interacciones = lista_insertar( lista_interacciones, interaccion_crear_desde_string(linea) )) ) {
	// 		free(sala);
	// 		lista_destruir(lista_interacciones);
	// 		lista_destruir(lista_objetos);
	// 		return NULL;
	// 	}
	// }

	// lista_t *lista_interacciones = crear_lista_interacciones(interacciones);
        sala->interacciones = crear_lista_interacciones(interacciones);
        // lista_t *lista_objetos = crear_lista_objetos(objetos);
        sala->objetos = crear_lista_objetos(objetos);

        if (!sala->interacciones || !sala->objetos || lista_vacia(sala->interacciones) || lista_vacia(sala->objetos)) {
                // lista_destruir(sala->obj_conocidos);
                // lista_destruir(sala->obj_poseidos);
                // lista_destruir(lista_interacciones);
                // lista_destruir(lista_objetos);
                sala_destruir(sala);
                return NULL;
        }

	// sala->interacciones = lista_interacciones;
        // sala->objetos = lista_objetos;

	// fclose( archivo_objetos );
	// fclose( archivo_interacciones );

	// if (sala->interacciones->cantidad == 0 || sala->objetos->cantidad == 0) {
	// 	sala_destruir(sala);
	// 	return NULL;
	// }

	agregar_objeto_conocido(sala, "habitacion");
        // sala->escapada = false;

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
		// // printf("Ya posees este objeto.");
		return false;
	}

	struct objeto *objeto = (struct objeto *)lista_buscar_elemento(sala->obj_conocidos, comparador, (void *)nombre_objeto);

	if (!objeto) {
		// // printf("Todavía no encontraste ninguno de estos.\n");
		return false;
	}

	if (!objeto->es_asible) {
		// // printf("No te lo podés llevar, ¡seguí intentando!\n");
		return false;
	}

        // lista_quitar_elemento(sala->obj_conocidos, objeto, NULL);
        quitar_conocido(sala, nombre_objeto);
	lista_insertar(sala->obj_poseidos, objeto);
	// printf("Nuevo objeto adquirido: %s\n", nombre_objeto);
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

bool es_asible(sala_t *sala, const char *nombre_objeto) {
        struct objeto *objeto = (struct objeto *)lista_buscar_elemento(sala->objetos, comparador, (void *)nombre_objeto);

        if (objeto != NULL) {
                return objeto->es_asible;
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
			// printf("\n\nentró a descubrir objeto\n\n");
			if (agregar_objeto_conocido(sala, interaccion->accion.objeto)) {
                                // printf("descubrió objeto: %s\n", interaccion->accion.objeto);
				mostrar_mensaje(interaccion->accion.mensaje, interaccion->accion.tipo, aux);
                                return true;
			}
                        // eliminar_objeto(sala, )
			break;

		case REEMPLAZAR_OBJETO:
			// printf("\n\nentró a reemplazar objeto\n\n");
                        // Reemplaza objeto 2 por el objeto de la accion.
			// eliminar_objeto(sala, objeto2);
			if (eliminar_objeto(sala, objeto2) && agregar_objeto_conocido(sala, interaccion->accion.objeto)) {
				mostrar_mensaje(interaccion->accion.mensaje, interaccion->accion.tipo, aux);
                                return true;
			}
			break;

		case ELIMINAR_OBJETO:
			// printf("\n\nentró a eliminar objeto\n\n");
			if (eliminar_objeto(sala, objeto1)) {
			        mostrar_mensaje(interaccion->accion.mensaje, interaccion->accion.tipo, aux);
                                return true;
                        }
			break;

		case MOSTRAR_MENSAJE:
			// printf("\n\nentró a mostrar mensaje\n\n");
			if (mostrar_mensaje != NULL) {
                                mostrar_mensaje(interaccion->accion.mensaje, interaccion->accion.tipo, aux);
                                return true;
                        }
                        break;

		case ESCAPAR:
		// printf("\n\nentró a escapar\n\n");
                        mostrar_mensaje(interaccion->accion.mensaje, interaccion->accion.tipo, aux);
			sala->escapada = true;
                        return true;
			break;

		default:
			break;
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

int sala_ejecutar_interaccion(sala_t *sala,
				const char *verbo,
				const char *objeto1,
				const char *objeto2,
				void (*mostrar_mensaje)(const char *mensaje, enum tipo_accion accion, void *aux),
				void *aux)
{
	if ( !lista_buscar_elemento(sala->obj_conocidos, comparador, (void *)objeto1) && !lista_buscar_elemento(sala->obj_poseidos, comparador, (void *)objeto1) ) {
		// // printf("No conoces o no tenes el objeto\n");
		return 0;
	}

        // Si es asible y no lo poseo, no ejecuta interacción.
        if (es_asible(sala, objeto1) && !lista_buscar_elemento(sala->obj_poseidos, comparador, (void *)objeto1)) {
                // printf("No lo tenés.\n");
                return 0;
        }

	struct interaccion *interaccion;
	int cant_interacciones = 0;

	for ( size_t i = 0; i < sala->interacciones->cantidad; i++ ) {

		interaccion = (struct interaccion *)lista_elemento_en_posicion(sala->interacciones, i);

		if ( strcmp(interaccion->verbo, verbo) == 0 && interaccion_valida(interaccion, verbo, objeto1, objeto2) ) {
			// // printf("\nentró\n");
			if (interactuar(sala, interaccion, verbo, objeto1, objeto2, mostrar_mensaje, aux)) {
			        cant_interacciones++;
                                // printf("cont++ con %s y %s\n", objeto1, objeto2);
                        }
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
        if (!sala) return;

	lista_destruir_todo(sala->objetos, free);
	lista_destruir_todo(sala->interacciones, free);
	lista_destruir(sala->obj_conocidos);
	lista_destruir(sala->obj_poseidos);
	free(sala);
}


// #include "estructuras.h"
// #include "sala.h"
// #include "objeto.h"
// #include "interaccion.h"
// #include "lista.h"
// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>

// #define MAX_CARACTERES 1024
// #define CANT_OBJETOS 20
// #define ERROR -1

// struct sala {
// 	lista_t *objetos;
// 	lista_t *interacciones;
// 	lista_t *conocidos;
// 	lista_t *poseidos;
// 	bool escape_exitoso;
// };

// int comparador(void *elemento, void *contexto)
// {
// 	struct objeto *objeto = (struct objeto *)elemento;
// 	return strcmp(objeto->nombre, (const char *)contexto);
// }

// lista_t *crear_lista_objetos(FILE *archivo)
// {
// 	char linea[MAX_CARACTERES];
// 	lista_t *lista_objetos = lista_crear();
// 	if(!lista_objetos){
// 		return NULL;
// 	}
	
// 	while(fgets(linea, MAX_CARACTERES, archivo) != NULL){
		
// 		struct objeto *objeto = objeto_crear_desde_string(linea);
// 		if(!objeto){
// 			lista_destruir(lista_objetos);
// 			return NULL;
// 		}
// 		lista_objetos = lista_insertar(lista_objetos, objeto);
// 		if(!lista_objetos){
// 			free(objeto);
// 			lista_destruir(lista_objetos);
// 			return NULL;
// 		}	
// 	}
// 	return lista_objetos;
// }

// lista_t *crear_lista_interacciones(FILE *archivo)
// {
// 	char linea[MAX_CARACTERES];
// 	lista_t *lista_interacciones = lista_crear();
// 	if(!lista_interacciones){
// 		return NULL;
// 	}
	
// 	while(fgets(linea, MAX_CARACTERES, archivo) != NULL){
		
// 		struct interaccion *interaccion = interaccion_crear_desde_string(linea);
// 		if(!interaccion){
// 			lista_destruir(lista_interacciones);
// 			return NULL;
// 		}
// 		lista_interacciones = lista_insertar(lista_interacciones, interaccion);
// 		if(!lista_interacciones){
// 			free(interaccion);
// 			lista_destruir(lista_interacciones);
// 			return NULL;
// 		}	
// 	}
// 	return lista_interacciones;
// }

// bool conocer_objeto(sala_t *sala, const char *nombre_objeto)
// {
// 	if(!sala || !nombre_objeto){
// 		return false;
// 	}

// 	if(lista_buscar_elemento(sala->conocidos, comparador, (void *)nombre_objeto) != NULL){
// 		return false;
// 	}

// 	struct objeto *objeto = lista_buscar_elemento(sala->objetos, comparador, (void *)nombre_objeto);

// 	if(objeto){
// 		lista_insertar(sala->conocidos, objeto);
// 		return true;
// 	}

// 	return false;
// }

// sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
// {	
// 	if(!objetos || !interacciones){
// 		return NULL;
// 	}

// 	FILE *arch_objetos = fopen(objetos, "r");
// 	if(!arch_objetos){
//         	return NULL;
// 	}

// 	FILE *arch_interacciones = fopen(interacciones, "r");
// 	if(!arch_interacciones){
// 		fclose(arch_objetos);
//         	return NULL;
// 	}

// 	sala_t *sala = calloc(1, sizeof(struct sala));
// 	if(!sala){
// 		fclose(arch_objetos);
// 		fclose(arch_interacciones);
// 		return NULL;
// 	}	
	
// 	lista_t *lista_objetos = crear_lista_objetos(arch_objetos);
// 	if(!lista_objetos){
// 		fclose(arch_objetos);
// 		fclose(arch_interacciones);
// 		sala_destruir(sala);
// 		return NULL;
// 	}
// 	sala->objetos = lista_objetos;
// 	fclose(arch_objetos);

// 	lista_t *lista_interaccion = crear_lista_interacciones(arch_interacciones);
// 	if(!lista_interaccion){
// 		fclose(arch_interacciones);
// 		sala_destruir(sala);
// 		return NULL;
// 	}
// 	sala->interacciones = lista_interaccion;
// 	fclose(arch_interacciones);
	
// 	if(sala->interacciones->cantidad == 0 || sala->objetos->cantidad == 0){
// 		sala_destruir(sala);
// 		return NULL;
// 	}

// 	lista_t *lista_conocidos = lista_crear();
// 	if(!lista_conocidos){
// 		sala_destruir(sala);
// 		return NULL;
// 	}

// 	lista_t *lista_poseidos = lista_crear();
// 	if(!lista_poseidos){
// 		sala_destruir(sala);
// 		return NULL;
// 	}

// 	sala->conocidos = lista_conocidos;
// 	sala->poseidos = lista_poseidos;

// 	conocer_objeto(sala, "habitacion");
	
// 	return sala;
// }

// char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
// {
// 	if(!sala){
// 		*cantidad = ERROR;
// 		return NULL;
// 	}

// 	if(!cantidad){
// 		int i = 0;
// 		cantidad = &i;
// 	}

// 	*cantidad = (int)sala->objetos->cantidad;
// 	char **nombres_objetos = malloc((unsigned)(*cantidad) * (sizeof(char *)));

// 	if(!nombres_objetos) {
// 		*cantidad = ERROR;
// 		return NULL;
// 	}

// 	for(int i = 0; i < *cantidad; i++){
// 		struct objeto *objeto = (struct objeto*)lista_elemento_en_posicion(sala->objetos, (size_t)i);
// 		if(!objeto){
// 			free(nombres_objetos);
// 			return NULL;
// 		}
// 		nombres_objetos[i] = objeto->nombre;
// 	}

// 	return nombres_objetos;
// }

// char **sala_obtener_nombre_objetos_conocidos(sala_t *sala, int *cantidad)
// {
// 	if (!sala) {
// 		*cantidad = ERROR;
// 		return NULL;
// 	}

// 	if (!cantidad) {
// 		int i = 0;
// 		cantidad = &i;
// 	}

// 	*cantidad = (int)sala->conocidos->cantidad;

// 	char **conocidos = malloc((unsigned)(*cantidad) * (sizeof(char *)));

// 	if (!conocidos){
// 		*cantidad = ERROR;
// 		return NULL;
// 	}

// 	for(int i = 0; i < *cantidad; i++){
		
// 		struct objeto *objeto = (struct objeto*)lista_elemento_en_posicion(sala->conocidos, (size_t)i);
// 		conocidos[i] = objeto->nombre;
// 	}

// 	return conocidos;
// }

// char **sala_obtener_nombre_objetos_poseidos(sala_t *sala, int *cantidad)
// {
// 	if (!sala) {
// 		*cantidad = ERROR;
// 		return NULL;
// 	}

// 	if (!cantidad) {
// 		int i = 0;
// 		cantidad = &i;
// 	}

// 	*cantidad = (int)sala->poseidos->cantidad;
// 	char **poseidos = malloc((unsigned)(*cantidad) * (sizeof(char *)));

// 	if(!poseidos){
// 		*cantidad = ERROR;
// 		return NULL;
// 	}

// 	for(int i = 0; i < *cantidad; i++){
// 		struct objeto *objeto = (struct objeto*)lista_elemento_en_posicion(sala->poseidos, (size_t)i);
// 		poseidos[i] = objeto->nombre;
// 	}

// 	return poseidos;
// }

// bool sala_es_interaccion_valida(sala_t *sala, const char *verbo, const char *objeto1, const char *objeto2)
// {
// 	if(!sala || !verbo || !objeto1 || !objeto2){
// 		return NULL;
// 	}

// 	for(int i = 0; i < sala->interacciones->cantidad; i++){

// 		struct interaccion *interaccion = (struct interaccion *)lista_elemento_en_posicion(sala->interacciones, (size_t)i);

// 		if(strcmp(interaccion->verbo, verbo) == 0 &&
// 		strcmp(interaccion->objeto, objeto1) == 0 &&
// 		strcmp(interaccion->objeto_parametro, objeto2) == 0){
// 		 	return true;
// 		}	
// 	}

// 	return false;
// }

// bool sala_agarrar_objeto(sala_t *sala, const char *nombre_objeto)
// {
// 	if(!sala || !nombre_objeto){
// 		return false;
// 	}

// 	struct objeto *objeto_a_agarrar = lista_buscar_elemento(sala->poseidos, comparador, (void *)nombre_objeto);

// 	struct objeto *objeto_conocido = lista_buscar_elemento(sala->conocidos, comparador, (void *)nombre_objeto);
	
// 	if(!objeto_a_agarrar && objeto_conocido != NULL && objeto_conocido->es_asible){
// 		lista_insertar(sala->poseidos, objeto_conocido);
// 		return true;
// 	}

// 	return false;
// }

// char* sala_describir_objeto(sala_t* sala, const char *nombre_objeto)
// {
// 	if(!sala || !nombre_objeto){
// 		return NULL;
// 	}

// 	struct objeto *objeto_poseido = lista_buscar_elemento(sala->poseidos, comparador, (void *)nombre_objeto);

// 	struct objeto *objeto_conocido = lista_buscar_elemento(sala->conocidos, comparador, (void *)nombre_objeto);
	
// 	if(objeto_poseido){
// 		return objeto_poseido->descripcion;
// 	}
// 	else if(objeto_conocido){
// 		return objeto_conocido->descripcion;
// 	}

// 	return NULL;
// }

// lista_t *lista_quitar_elemento(lista_t *lista, int (*comparador)(void *, void *), void *contexto)
// {
// 	if (!lista || !comparador || lista_vacia(lista)){
// 		return NULL;
// 	}

// 	for (size_t i = 0; i < lista_tamanio(lista); i++) {
// 		struct objeto *objeto = lista_elemento_en_posicion(lista, i);
// 		if(!objeto){
// 			return NULL;
// 		}
// 		if(comparador(objeto, contexto) == 0){
// 			objeto = lista_quitar_de_posicion(lista, i);
// 			if(!objeto){
// 				return NULL;
// 			}
// 		}
// 	}

// 	return lista;
// }

// bool eliminar_objeto(sala_t *sala, const char *nombre_objeto)
// {
// 	if(!sala || !nombre_objeto){
// 		return false;
// 	}

// 	lista_t *poseidos = lista_quitar_elemento(sala->poseidos, comparador, (void *)nombre_objeto);
// 	lista_t *conocidos = lista_quitar_elemento(sala->conocidos, comparador, (void *)nombre_objeto);
// 	lista_t *objetos = lista_quitar_elemento(sala->objetos, comparador, (void *)nombre_objeto);

// 	if(!poseidos || !conocidos || !objetos){
// 		return false;
// 	}

// 	sala->poseidos = poseidos;
// 	sala->conocidos = conocidos;
// 	sala->objetos = objetos;

// 	return true;
// }

// bool interaccion_correcta(struct interaccion *interaccion, const char *verbo, const char *objeto1, const char *objeto2)
// {
// 	if (strcmp(interaccion->verbo, verbo) == 0 && 
// 	strcmp(interaccion->objeto, objeto1) == 0 && 
// 	strcmp(interaccion->objeto_parametro, objeto2) == 0){
// 		return true;
// 	}

// 	return false;
// }

// int ejecutar_accion(sala_t *sala, struct interaccion *interaccion, const char *objeto1, const char *objeto2, void (*mostrar_mensaje)(const char *mensaje, enum tipo_accion accion, void *aux), void *aux){

// 	int ejecutadas = 0;

// 	if(interaccion->accion.tipo == ACCION_INVALIDA){
// 		return ejecutadas;
// 	}
	
// 	else if(interaccion->accion.tipo == MOSTRAR_MENSAJE){
// 		ejecutadas++;
// 	}

// 	else if(interaccion->accion.tipo == ELIMINAR_OBJETO){
// 		if(eliminar_objeto(sala, objeto1)){
// 			ejecutadas++;
// 		}
// 	}

// 	else if(interaccion->accion.tipo == DESCUBRIR_OBJETO){
// 		if(conocer_objeto(sala, interaccion->accion.objeto)){
// 			ejecutadas++;
// 		}
// 	}

// 	else if(interaccion->accion.tipo == ESCAPAR){
// 		sala->escape_exitoso = true;
// 		ejecutadas++;
// 	}
	
// 	else if(interaccion->accion.tipo == REEMPLAZAR_OBJETO){
// 		if(eliminar_objeto(sala, objeto2) && conocer_objeto(sala, interaccion->accion.objeto)){
// 			ejecutadas++;
// 		}
// 	}

// 	mostrar_mensaje(interaccion->accion.mensaje, interaccion->accion.tipo, aux);

// 	return ejecutadas;
// }

// int sala_ejecutar_interaccion(sala_t *sala, const char *verbo, const char *objeto1, const char *objeto2, void (*mostrar_mensaje)(const char *mensaje, enum tipo_accion accion, void *aux), void *aux)
// {
// 	if(!sala || !verbo || !objeto1 || !objeto2 || !mostrar_mensaje){
// 		return 0;
// 	}

// 	if(!lista_buscar_elemento(sala->conocidos, comparador, (void *)objeto1) && !lista_buscar_elemento(sala->poseidos, comparador, (void *)objeto1)){

// 		return 0;
// 	}

// 	if(!sala_es_interaccion_valida(sala, verbo, objeto1, objeto2)){

// 		return 0;
// 	}
	
// 	int ejecutadas = 0;

// 	for(int i = 0; i < sala->interacciones->cantidad; i++){

// 		struct interaccion *interaccion = lista_elemento_en_posicion(sala->interacciones, (size_t)i);

// 		if(interaccion_correcta(interaccion, verbo, objeto1, objeto2)){
			
// 			ejecutadas = ejecutar_accion(sala, interaccion, objeto1, objeto2, mostrar_mensaje, aux);
// 		}			
// 	}

// 	return ejecutadas;
// }

// bool sala_escape_exitoso(sala_t *sala)
// {
// 	if(!sala){
// 		return false;
// 	}
// 	return sala->escape_exitoso;
// }

// void sala_destruir(sala_t *sala)
// {
// 	if(!sala){
// 		return;
// 	}

// 	lista_destruir_todo(sala->objetos, free);
// 	lista_destruir_todo(sala->interacciones, free);
// 	lista_destruir(sala->conocidos);
// 	lista_destruir(sala->poseidos);
// 	free(sala);
// }