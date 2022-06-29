#include "pa2mm.h"
#include "src/estructuras.h"
#include "src/sala.h"
#include "src/objeto.h"
#include "src/interaccion.h"
#include "lib/tda_lista/lista.h"

#include "string.h"
#include <stdbool.h>

struct sala {
	lista_t *objetos;
	lista_t *obj_conocidos;
	lista_t *obj_poseidos;
	lista_t *interacciones;
	bool escapada;
};



void pruebas_crear_sala_l()
{
// 	habitacion;examinar;_;d:pokebola:Hay una pokebola en el piso
// 	habitacion;examinar;_;d:puerta:Hay una puerta vieja
// 	puerta;abrir;_;m:_:La puerta está cerrada con llave
// 	pokebola;abrir;_;d:llave:hay una llave dentro de la pokebola
// 	pokebola;abrir;_;e:pokebola:No necesitas mas la pokebola
// 	llave;abrir;puerta;r:puerta-abierta:La puerta se abre
// 	puerta-abierta;salir;_;g:_:Ganaste, pudiste escapar

	sala_t *sala = sala_crear_desde_archivos("ejemplo/objetos.txt", "ejemplo/interacciones.txt");

	// int cant_objetos = 0;
	// char **nombres = sala_obtener_nombre_objetos(sala, &cant_objetos);

	// pa2m_afirmar( cant_objetos == 5, "La sala se creó con la cantidad correcta de objetos (5)." );

	// for (int i = 0; i < cant_objetos; i++) {
	// 	printf("%i: %s\n", i, nombres[i]);
	// }

	pa2m_afirmar( lista_tamanio(sala->objetos) == 5, "La sala se creó con la cantidad correcta de objetos (5)." );
	pa2m_afirmar( lista_tamanio(sala->interacciones) == 7, "La sala se creó con la cantidad correcta de interacciones (7)." );

	pa2m_afirmar( sala_es_interaccion_valida(sala, "examinar", "habitacion", "_"), "'examinar habitacion _' es una interacción válida");
	pa2m_afirmar( sala_es_interaccion_valida(sala, "abrir", "puerta", "_"), "'abrir puerta _' es una interacción válida");
	pa2m_afirmar( sala_es_interaccion_valida(sala, "abrir", "pokebola", "_"), "'abrir puerta _' es una interacción válida");
	pa2m_afirmar( sala_es_interaccion_valida(sala, "abrir", "llave", "puerta"), "'abrir llave puerta' es una interacción válida");
	pa2m_afirmar( sala_es_interaccion_valida(sala, "salir", "puerta-abierta", "_"), "'salir puerta-abierta _' es una interacción válida");


	// struct interaccion *int1;
	// struct interaccion *int2;
	// struct interaccion *int3;
	// struct interaccion *int4;
	// struct interaccion *int5;
	// struct interaccion *int6;
	// struct interaccion *int7;

	// pa2m_afirmar( (int1 = interaccion_crear_desde_string("habitacion;examinar;_;d:pokebola:Hay una pokebola en el piso")) != NULL, "Se creó interacción.");
	// pa2m_afirmar( (int2 = interaccion_crear_desde_string("habitacion;examinar;_;d:puerta:Hay una puerta vieja")) != NULL, "Se creó interacción.");
	// pa2m_afirmar( (int3 = interaccion_crear_desde_string("puerta;abrir;_;m:_:La puerta está cerrada con llave")) != NULL, "");
	// pa2m_afirmar( (int4 = interaccion_crear_desde_string("pokebola;abrir;_;d:llave:hay una llave dentro de la pokebola")) != NULL, "Se creó interacción.");
	// pa2m_afirmar( (int5 = interaccion_crear_desde_string("pokebola;abrir;_;e:pokebola:No necesitas mas la pokebola")) != NULL, "Se creó interacción.");
	// pa2m_afirmar( (int6 = interaccion_crear_desde_string("llave;abrir;puerta;r:puerta-abierta:La puerta se abre")) != NULL, "Se creó interacción.");
	// pa2m_afirmar( (int7 = interaccion_crear_desde_string("puerta-abierta;salir;_;g:_:Ganaste, pudiste escapar")) != NULL, "Se creó interacción.");

	// lista_t *lista = lista_crear();

	// pa2m_afirmar( lista_insertar(lista, int1) != NULL, "Se insertó la interacción a la lista." );
	// pa2m_afirmar( lista_insertar(lista, int2) != NULL, "Se insertó la interacción a la lista." );
	// pa2m_afirmar( lista_insertar(lista, int3) != NULL, "Se insertó la interacción a la lista." );
	// pa2m_afirmar( lista_insertar(lista, int4) != NULL, "Se insertó la interacción a la lista." );
	// pa2m_afirmar( lista_insertar(lista, int5) != NULL, "Se insertó la interacción a la lista." );
	// pa2m_afirmar( lista_insertar(lista, int6) != NULL, "Se insertó la interacción a la lista." );
	// pa2m_afirmar( lista_insertar(lista, int7) != NULL, "Se insertó la interacción a la lista." );

	// pa2m_afirmar( lista_tamanio(lista) == 7, "La lista de interacciones tiene 7 elementos.");

	// pa2m_afirmar( sala_es_interaccion_valida())



}

void pruebasCrearObjeto()
{
	pa2m_afirmar(objeto_crear_desde_string(NULL) == NULL,
		     "No puedo crear un objeto a partir de un string NULL");
	pa2m_afirmar(objeto_crear_desde_string("") == NULL,
		     "No puedo crear un objeto a partir de un string vacío");
	pa2m_afirmar(objeto_crear_desde_string("a;b") == NULL,
		     "\"a;b\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string("a;;b") == NULL,
		     "\"a;;b\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string(";a;b") == NULL,
		     "\";a;b\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string("a;b;c") == NULL,
		     "\"a;b;c\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string("a;;true") == NULL,
		     "\"a;;true\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string(";a;false") == NULL,
		     "\";a;false\" no es un string objeto válido");

	struct objeto *objeto1 = objeto_crear_desde_string("nombre;desc;true");
	pa2m_afirmar(objeto1, "\"nombre;desc;true\" es un string objeto válido");
	pa2m_afirmar(strcmp(objeto1->nombre, "nombre") == 0, "El nombre del objeto es \"nombre\"");
	pa2m_afirmar(strcmp(objeto1->descripcion, "desc") == 0,
		     "La descripcion del objeto es \"desc\"");
	pa2m_afirmar(objeto1->es_asible == true, "El objeto es asible");

	struct objeto *objeto2 = objeto_crear_desde_string("A;Be;false\n");
	pa2m_afirmar(objeto2, "\"A;Be;false\\n\" es un string objeto válido");
	pa2m_afirmar(strcmp(objeto2->nombre, "A") == 0, "El nombre del objeto es \"A\"");
	pa2m_afirmar(strcmp(objeto2->descripcion, "Be") == 0,
		     "La descripcion del objeto es \"Be\"");
	pa2m_afirmar(objeto2->es_asible == false, "El objeto no es asible");

	free(objeto1);
	free(objeto2);
}

void pruebasCrearInteracciones()
{
	pa2m_afirmar(interaccion_crear_desde_string(NULL) == NULL,
		     "No puedo crear una interacción a partir de un string NULL");
	pa2m_afirmar(interaccion_crear_desde_string("") == NULL,
		     "No puedo crear una interacción a partir de un string vacío");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;c:d:e") == NULL,
		     "\"a;b;c:d:e\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;c;d") == NULL,
		     "\"a;b;c;d\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;c;d:e") == NULL,
		     "\"a;b;c;d:e\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;_;d:e") == NULL,
		     "\"a;b;_;d:e\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;_;de:f:g") == NULL,
		     "\"a;b;_;de:f:g\" no es un string interacción válido");

	struct interaccion *inter1 = interaccion_crear_desde_string("a;b;c;d:e:f");
	pa2m_afirmar(inter1, "\"a;b;c;d:e:f\" es un string interacción válido");
	pa2m_afirmar(strcmp(inter1->objeto, "a") == 0, "El nombre del objeto es \"a\"");
	pa2m_afirmar(strcmp(inter1->verbo, "b") == 0, "El verbo es \"b\"");
	pa2m_afirmar(strcmp(inter1->objeto_parametro, "c") == 0, "El segundo objeto es \"c\"");
	pa2m_afirmar(inter1->accion.tipo == DESCUBRIR_OBJETO,
		     "El tipo de acción es DESCUBRIR_OBJETO");
	pa2m_afirmar(strcmp(inter1->accion.objeto, "e") == 0, "El objeto de la acción es \"e\"");
	pa2m_afirmar(strcmp(inter1->accion.mensaje, "f") == 0, "El mensaje de la acción es \"f\"");

	struct interaccion *inter2 = interaccion_crear_desde_string("OB;VER;_;m:_:MSG");
	pa2m_afirmar(inter1, "\"OB;VER;_;m:_:MSG\" es un string interacción válido");
	pa2m_afirmar(strcmp(inter2->objeto, "OB") == 0, "El nombre del objeto es \"OB\"");
	pa2m_afirmar(strcmp(inter2->verbo, "VER") == 0, "El verbo es \"VER\"");
	pa2m_afirmar(strcmp(inter2->objeto_parametro, "") == 0, "El segundo objeto es vacío");
	pa2m_afirmar(inter2->accion.tipo == MOSTRAR_MENSAJE,
		     "El tipo de acción es MOSTRAR_MENSAJE");
	pa2m_afirmar(strcmp(inter2->accion.objeto, "") == 0, "El objeto de la acción es vacío");
	pa2m_afirmar(strcmp(inter2->accion.mensaje, "MSG") == 0,
		     "El mensaje de la acción es \"MSG\"");

	free(inter1);
	free(inter2);
}

void pruebas_crear_sala()
{
	pa2m_afirmar(sala_crear_desde_archivos("/ASD/ASD/", "dasD/sa2asdd") == NULL,
		     "No puedo crear la sala a partír de archivos inexistentes");

	pa2m_afirmar(sala_crear_desde_archivos("", "chanu/int.csv") == NULL,
		     "No puedo crear la sala sin objetos");

	pa2m_afirmar(sala_crear_desde_archivos("chanu/obj.dat", "chanu/vacio.txt") == NULL,
		     "No puedo crear la sala sin interacciones");

	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	pa2m_afirmar(sala != NULL, "Puedo crear la sala a partir de archivos no vacíos");
	// pa2m_afirmar(sala->cantidad_objetos == 9, "Se leyeron 9 objetos");
	// pa2m_afirmar(sala->cantidad_interacciones == 9, "Se leyeron 9 interacciones");

	sala_destruir(sala);
}

void pruebas_nombre_objetos()
{
	int cantidad = 0;
	pa2m_afirmar(sala_obtener_nombre_objetos(NULL, &cantidad) == NULL,
		     "No puedo obtener los nombres de objetos de una sala NULL");
	pa2m_afirmar(cantidad == -1, "La cantidad es -1 luego de invocar a la función");

	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	char **objetos = sala_obtener_nombre_objetos(sala, NULL);
	pa2m_afirmar(objetos != NULL,
		     "Puedo pedir el vector de nombres a la sala pasando cantidad NULL");

	char **objetos2 = sala_obtener_nombre_objetos(sala, &cantidad);
	pa2m_afirmar(objetos2 != NULL,
		     "Puedo pedir el vector de nombres a la sala pasando cantidad no NULL");
	pa2m_afirmar(cantidad == 9, "La cantidad de elementos del vector coincide con lo esperado");

	const char *esperados[] = { "habitacion",    "mesa",  "interruptor", "pokebola", "cajon",
				    "cajon-abierto", "llave", "anillo",	     "puerta" };

	int comparaciones_exitosas = 0;

	for (int i = 0; i < cantidad; i++)
		if (strcmp(objetos2[i], esperados[i]) == 0)
			comparaciones_exitosas++;

	pa2m_afirmar(comparaciones_exitosas == cantidad,
		     "Todos los nombres de objeto son los esperados");

	free(objetos);
	free(objetos2);
	sala_destruir(sala);
}

void pruebas_interacciones()
{
	pa2m_afirmar(sala_es_interaccion_valida(NULL, "hacer", NULL, NULL) == false,
		     "No es válido pedir interacciones de una sala NULL");

	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	pa2m_afirmar(sala_es_interaccion_valida(sala, NULL, "", "") == false, "No es válida una intearcción con verbo NULL");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "hacer", NULL, "") == false, "No es válida una intearcción con objeto NULL");

	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "habitacion", "") == true, "Puedo examinar la habitación");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "usar", "llave", "cajon") == true, "Puedo usar la llave en el cajón");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "abrir", "pokebola", "") == true, "Puedo abrir la pokebola");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "cajon-abierto", "") == true, "Puedo examinar el cajón abierto");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "romper", "todo", "") == false, "No puedo romper todo");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "abrir", "mesa", "") == false, "No puedo abrir la mesa");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "techo", "") == false, "No puedo examinar el techo");

	sala_destruir(sala);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de creación de objetos");
	pruebasCrearObjeto();

	pa2m_nuevo_grupo("Pruebas de creación de interacciones");
	pruebasCrearInteracciones();

	pa2m_nuevo_grupo("Pruebas de creación de sala");
	pruebas_crear_sala();

	pa2m_nuevo_grupo("Pruebas del vector de nombres");
	pruebas_nombre_objetos();

	pa2m_nuevo_grupo("Pruebas de interacciones");
	pruebas_interacciones();

	pa2m_nuevo_grupo("Pruebas");
	pruebas_crear_sala_l();

	return pa2m_mostrar_reporte();
}
