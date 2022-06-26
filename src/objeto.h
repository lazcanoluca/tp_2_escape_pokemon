#ifndef OBJETO_H_
#define OBJETO_H_

#include "estructuras.h"

/*
 * Crea un objeto a partir del string.
 *
 * Esta función reserva memoria con malloc y el objeto devuelto debe ser
 * destruido con free.
 *
 * Devuelve el objeto creado o NULL en caso de error de memoria o formato
 * incorrecto del string.
 */
struct objeto *objeto_crear_desde_string(const char *string);

#endif // OBJETO_H_
