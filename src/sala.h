#ifndef SALA_H_
#define SALA_H_

#include <stdbool.h>

typedef struct sala sala_t;
enum tipo_accion{
	ACCION_INVALIDA,
	DESCUBRIR_OBJETO,
	REEMPLAZAR_OBJETO,
	ELIMINAR_OBJETO,
	MOSTRAR_MENSAJE,
	ESCAPAR
};

/*
 * Crea una sala de escape a partir de un par de archivos.
 *
 * El string objetos es el path a un archivo con la definicion de los objetos
 * mientras que interacciones es el path a un archivo con la definicion de las
 * interacciones de los objetos.
 *
 * Devuelve una sala de escape creada con los datos leidos de los archivos o
 * NULL en caso de encontrar algún error en el proceso.
 *
 * La sala de escape devuelta debe ser liberada con la función de destrucción de
 * la sala antes de finalizar el programa.
 */
sala_t *sala_crear_desde_archivos(const char *objetos,
				  const char *interacciones);

/*
 * Devuelve un vector dinámico reservado con malloc que contiene los nombres de
 * todos los objetos existentes en la sala de escape.
 *
 * En la variable cantidad (si no es nula) se guarda el tamanio del vector de
 * nombres.
 *
 * El vector devuelto debe ser liberado con free.
 *
 * En caso de error devuelve NULL y pone cantidad en -1.
 */
char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad);

/*
 * Devuelve un vector dinámico reservado con malloc que contiene los nombres de
 * todos los objetos actualmente conocidos por el jugador en la sala de escape.
 * No incluye los objetos poseidos por el jugador.
 *
 * En la variable cantidad (si no es nula) se guarda el tamanio del vector de
 * nombres.
 *
 * El vector devuelto debe ser liberado con free.
 *
 * En caso de error devuelve NULL y pone cantidad en -1.
 */
char **sala_obtener_nombre_objetos_conocidos(sala_t *sala, int *cantidad);

/*
 * Devuelve un vector dinámico reservado con malloc que contiene los nombres de
 * todos los objetos actualmente en posesión del jugador.
 *
 * En la variable cantidad (si no es nula) se guarda el tamanio del vector de
 * nombres.
 *
 * El vector devuelto debe ser liberado con free.
 *
 * En caso de error devuelve NULL y pone cantidad en -1.
 */
char **sala_obtener_nombre_objetos_poseidos(sala_t *sala, int *cantidad);

/*
 * Hace que un objeto conocido y asible pase a estar en posesión del jugador.
 *
 * Devuelve true si pudo agarrar el objeto o false en caso de error (por ejemplo
 * el objeto no existe o existe pero no es asible o si dicho objeto ya está en
 * posesión del jugador).
 */
bool sala_agarrar_objeto(sala_t *sala, const char *nombre_objeto);

/*
 * Obtiene la descripción de un objeto conocido o en posesión del usuario.
 *
 * Devuelve NULL en caso de error.
 */
char* sala_describir_objeto(sala_t* sala, const char *nombre_objeto);

/*
 * Ejecuta una o mas interacciones en la sala de escape. Cuando una interacción
 * tenga un mensaje para mostrar por pantalla, se invocará la función
 * mostrar_mensaje (si no es NULL) con el mensaje a mostrar, el tipo de acción que representa el
 * mensaje y un puntero auxiliar del usuario.
 *
 * Devuelve la cantidad de interacciones que pudo ejecutar o 0 en caso de error.
 *
 */
int sala_ejecutar_interaccion(sala_t *sala, const char *verbo,
			      const char *objeto1, const char *objeto2,
			      void (*mostrar_mensaje)(const char *mensaje,
						      enum tipo_accion accion,
						      void *aux),
			      void *aux);

/*
 * Devuelve true si existe una interacción válida utilizando el verbo en objeto1
 * y objeto2. Objeto1 siempre es el nombre de un objeto. Objeto2 puede ser un
 * string vacío para interacciones que no necesitan dos objetos.
 *
 * Devuelve false si la interacción no existe o si se encuentra algún error.
 */
bool sala_es_interaccion_valida(sala_t *sala, const char *verbo,
				const char *objeto1, const char *objeto2);

/*
 * Devuelve true si se pudo escapar de la sala. False en caso contrario o si no existe la sala.
 */
bool sala_escape_exitoso(sala_t *sala);

/*
 * Destruye la sala de escape liberando toda la memoria reservada.
 */
void sala_destruir(sala_t *sala);

#endif // SALA_H_
