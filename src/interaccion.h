#ifndef INTERACCION_H_
#define INTERACCION_H_

#include "estructuras.h"

/*
 * Crea una interacción a partir del string.
 *
 * Esta función reserva memoria con malloc y la interacción devuelta debe ser
 * destruida con free.
 *
 * Devuelve la interacción creada o NULL en caso de error de memoria o formato
 * incorrecto del string.
 */
struct interaccion *interaccion_crear_desde_string(const char *string);

#endif // INTERACCION_H_
