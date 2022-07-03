#include "pa2mm.h"

#include "src/sala.h"
#include "src/objeto.h"
#include "src/interaccion.h"

#include "string.h"
#include <stdbool.h>

int vector_contiene_elementos(char *elementos[], char *esperados[],
			      int cantidad)
{
	int encontrados = 0;
	for (int i = 0; i < cantidad; i++) {
		for (int j = 0; j < cantidad; j++) {
			if (strcmp(elementos[i], esperados[j]) == 0) {
				encontrados++;
				break;
			}
		}
	}
	return encontrados;
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
	pa2m_afirmar(objeto1,
		     "\"nombre;desc;true\" es un string objeto válido");
	pa2m_afirmar(strcmp(objeto1->nombre, "nombre") == 0,
		     "El nombre del objeto es \"nombre\"");
	pa2m_afirmar(strcmp(objeto1->descripcion, "desc") == 0,
		     "La descripcion del objeto es \"desc\"");
	pa2m_afirmar(objeto1->es_asible == true, "El objeto es asible");

	struct objeto *objeto2 = objeto_crear_desde_string("A;Be;false\n");
	pa2m_afirmar(objeto2, "\"A;Be;false\\n\" es un string objeto válido");
	pa2m_afirmar(strcmp(objeto2->nombre, "A") == 0,
		     "El nombre del objeto es \"A\"");
	pa2m_afirmar(strcmp(objeto2->descripcion, "Be") == 0,
		     "La descripcion del objeto es \"Be\"");
	pa2m_afirmar(objeto2->es_asible == false, "El objeto no es asible");

	free(objeto1);
	free(objeto2);
}

void pruebasCrearInteracciones()
{
	pa2m_afirmar(
		interaccion_crear_desde_string(NULL) == NULL,
		"No puedo crear una interacción a partir de un string NULL");
	pa2m_afirmar(
		interaccion_crear_desde_string("") == NULL,
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

	struct interaccion *inter1 =
		interaccion_crear_desde_string("a;b;c;d:e:f");
	pa2m_afirmar(inter1, "\"a;b;c;d:e:f\" es un string interacción válido");
	pa2m_afirmar(strcmp(inter1->objeto, "a") == 0,
		     "El nombre del objeto es \"a\"");
	pa2m_afirmar(strcmp(inter1->verbo, "b") == 0, "El verbo es \"b\"");
	pa2m_afirmar(strcmp(inter1->objeto_parametro, "c") == 0,
		     "El segundo objeto es \"c\"");
	pa2m_afirmar(inter1->accion.tipo == DESCUBRIR_OBJETO,
		     "El tipo de acción es DESCUBRIR_OBJETO");
	pa2m_afirmar(strcmp(inter1->accion.objeto, "e") == 0,
		     "El objeto de la acción es \"e\"");
	pa2m_afirmar(strcmp(inter1->accion.mensaje, "f") == 0,
		     "El mensaje de la acción es \"f\"");

	struct interaccion *inter2 =
		interaccion_crear_desde_string("OB;VER;_;m:_:MSG");
	pa2m_afirmar(inter1,
		     "\"OB;VER;_;m:_:MSG\" es un string interacción válido");
	pa2m_afirmar(strcmp(inter2->objeto, "OB") == 0,
		     "El nombre del objeto es \"OB\"");
	pa2m_afirmar(strcmp(inter2->verbo, "VER") == 0, "El verbo es \"VER\"");
	pa2m_afirmar(strcmp(inter2->objeto_parametro, "") == 0,
		     "El segundo objeto es vacío");
	pa2m_afirmar(inter2->accion.tipo == MOSTRAR_MENSAJE,
		     "El tipo de acción es MOSTRAR_MENSAJE");
	pa2m_afirmar(strcmp(inter2->accion.objeto, "") == 0,
		     "El objeto de la acción es vacío");
	pa2m_afirmar(strcmp(inter2->accion.mensaje, "MSG") == 0,
		     "El mensaje de la acción es \"MSG\"");

	free(inter1);
	free(inter2);
}

void pruebas_crear_sala()
{
	pa2m_afirmar(
		sala_crear_desde_archivos("/ASD/ASD/", "dasD/sa2asdd") == NULL,
		"No puedo crear la sala a partír de archivos inexistentes");

	pa2m_afirmar(sala_crear_desde_archivos("", "chanu/int.csv") == NULL,
		     "No puedo crear la sala sin objetos");

	pa2m_afirmar(sala_crear_desde_archivos("chanu/obj.dat",
					       "chanu/vacio.txt") == NULL,
		     "No puedo crear la sala sin interacciones");

	sala_t *sala =
		sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	pa2m_afirmar(sala != NULL,
		     "Puedo crear la sala a partir de archivos no vacíos");

	sala_destruir(sala);
}

void pruebas_nombre_objetos()
{
	int cantidad = 0;
	pa2m_afirmar(
		sala_obtener_nombre_objetos(NULL, &cantidad) == NULL,
		"No puedo obtener los nombres de objetos de una sala NULL");
	pa2m_afirmar(cantidad == -1,
		     "La cantidad es -1 luego de invocar a la función");

	sala_t *sala =
		sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	char **objetos = sala_obtener_nombre_objetos(sala, NULL);
	pa2m_afirmar(
		objetos != NULL,
		"Puedo pedir el vector de nombres a la sala pasando cantidad NULL");

	char **objetos2 = sala_obtener_nombre_objetos(sala, &cantidad);
	pa2m_afirmar(
		objetos2 != NULL,
		"Puedo pedir el vector de nombres a la sala pasando cantidad no NULL");
	pa2m_afirmar(
		cantidad == 9,
		"La cantidad de elementos del vector coincide con lo esperado");

	char *esperados[] = { "habitacion", "mesa",   "interruptor",
			      "pokebola",   "cajon",  "cajon-abierto",
			      "llave",	    "anillo", "puerta" };

	pa2m_afirmar(vector_contiene_elementos(objetos2, esperados, cantidad) ==
			     cantidad,
		     "Todos los nombres de objeto son los esperados");

	free(objetos);
	free(objetos2);
	sala_destruir(sala);
}

void pruebas_interacciones()
{
	pa2m_afirmar(sala_es_interaccion_valida(NULL, "hacer", NULL, NULL) ==
			     false,
		     "No es válido pedir interacciones de una sala NULL");

	sala_t *sala =
		sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	pa2m_afirmar(sala_es_interaccion_valida(sala, NULL, "", "") == false,
		     "No es válida una intearcción con verbo NULL");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "hacer", NULL, "") ==
			     false,
		     "No es válida una intearcción con objeto NULL");

	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "habitacion",
						"") == true,
		     "Puedo examinar la habitación");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "usar", "llave",
						"cajon") == true,
		     "Puedo usar la llave en el cajón");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "abrir", "pokebola",
						"") == true,
		     "Puedo abrir la pokebola");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar",
						"cajon-abierto", "") == true,
		     "Puedo examinar el cajón abierto");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "romper", "todo", "") ==
			     false,
		     "No puedo romper todo");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "abrir", "mesa", "") ==
			     false,
		     "No puedo abrir la mesa");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "techo",
						"") == false,
		     "No puedo examinar el techo");

	sala_destruir(sala);
}

struct contador_accion {
	int totales, invalidas, descubrir, reemplazar, eliminar, mostrar,
		escapar, desconocidas;
};

void contar_acciones(const char *mensaje, enum tipo_accion accion,
		     void *_contador)
{
	struct contador_accion *contador = _contador;
	contador->totales++;
	if (accion == DESCUBRIR_OBJETO) {
		contador->descubrir++;
	} else if (accion == REEMPLAZAR_OBJETO) {
		contador->reemplazar++;
	} else if (accion == ELIMINAR_OBJETO) {
		contador->eliminar++;
	} else if (accion == MOSTRAR_MENSAJE) {
		contador->mostrar++;
	} else if (accion == ESCAPAR) {
		contador->escapar++;
	} else {
		contador->desconocidas++;
	}
}

void pruebas_escenario_basico()
{
	sala_t *sala = NULL;

	pa2m_afirmar((sala = sala_crear_desde_archivos(
			      "chanu/obj_basico.txt",
			      "chanu/int_basico.txt")) != NULL,
		     "Puedo crear una sala con el escenario básico");

	//char *vacío[] = { };
	int cantidad = 0;
	char **vector = NULL;
	char *texto = NULL;
	char *todos_los_objetos[] = { "habitacion", "pokebola", "llave",
				      "puerta", "puerta-abierta" };

	char *vector_hpopu[] = { "habitacion", "pokebola", "puerta" };
	char *vector_hpu[] = { "habitacion", "puerta" };
	char *vector_hpulla[] = { "habitacion", "puerta", "llave" };
	char *vector_hpua[] = { "habitacion", "puerta-abierta" };

	struct contador_accion contadores;
	memset(&contadores, 0, sizeof(contadores));

	pa2m_afirmar((vector = sala_obtener_nombre_objetos(sala, &cantidad)),
		     "Puedo obtener los nombres de los objetos de la sala");

	pa2m_afirmar(cantidad == 5, "Obtuve 5 objetos");

	pa2m_afirmar(vector_contiene_elementos(vector, todos_los_objetos,
					       cantidad) == 5,
		     "Los objetos son los correctos");

	free(vector);

	pa2m_afirmar((vector = sala_obtener_nombre_objetos_conocidos(
			      sala, &cantidad)),
		     "Puedo obtener los nombres de los objetos conocidos");

	pa2m_afirmar(cantidad == 1, "Inicialmente solo se conoce un objeto");

	pa2m_afirmar(strcmp(vector[0], "habitacion") == 0,
		     "El elemento conocido es la habitación");

	free(vector);

	pa2m_afirmar((texto = sala_describir_objeto(sala, "habitacion")) !=
			     NULL,
		     "Puedo pedir la descripción de la sala");

	pa2m_afirmar(strcmp(texto,
			    "Una habitación de la que no podes escapar") == 0,
		     "La descripcion de la habitación es la correcta");

	pa2m_afirmar((vector = sala_obtener_nombre_objetos_poseidos(sala,
								    &cantidad)),
		     "Puedo obtener los nombres de los objetos poseidos");

	pa2m_afirmar(cantidad == 0, "El jugador no tiene ningún objeto");

	free(vector);

	pa2m_afirmar(sala_escape_exitoso(sala) == false,
		     "El escape aún no es exitoso");

	pa2m_afirmar(sala_agarrar_objeto(sala, "habitacion") == false,
		     "No puedo agarrar la sala");

	pa2m_afirmar(sala_agarrar_objeto(sala, "pokebola") == false,
		     "No puedo agarrar la pokebola (no la conozco)");

	pa2m_afirmar(sala_agarrar_objeto(sala, "llave") == false,
		     "No puedo agarrar la llave (no la conozco)");

	pa2m_afirmar(sala_agarrar_objeto(sala, "puerta") == false,
		     "No puedo agarrar la puerta (no la conozco)");

	pa2m_afirmar(sala_ejecutar_interaccion(sala, "abrir", "puerta", "",
					       contar_acciones,
					       &contadores) == 0,
		     "No puedo abrir la puerta (no la conozco)");

	pa2m_afirmar(sala_ejecutar_interaccion(sala, "salir", "puerta-abierta",
					       "", contar_acciones,
					       &contadores) == 0,
		     "No puedo salir por la puerta-abierta (no la conozco)");

	pa2m_afirmar(contadores.totales == 0,
		     "No se invocó la función de mostrar ninguna vez");

	pa2m_afirmar(
		(texto = sala_describir_objeto(sala, "pokebola")) == NULL,
		"No puedo pedir la descripción de la pokebola (no la conozco)");

	pa2m_afirmar(sala_ejecutar_interaccion(sala, "examinar", "habitacion",
					       "", contar_acciones,
					       &contadores) == 2,
		     "Examinar la habitacion ejecuta dos acciones");

	pa2m_afirmar(contadores.totales == 2 && contadores.descubrir == 2,
		     "Se mostraron 2 mensajes de tipo DESCUBRIR");

	pa2m_afirmar(
		(vector = sala_obtener_nombre_objetos_conocidos(sala,
								&cantidad)),
		"Puedo obtener los nombres de los objetos conocidos otra vez");

	pa2m_afirmar(cantidad == 3, "Ahora conozco 3 objetos");

	pa2m_afirmar(vector_contiene_elementos(vector, vector_hpopu, cantidad) ==
			     3,
		     "Los objetos son la habitación, pokebola y puerta");

	free(vector);

	pa2m_afirmar((vector = sala_obtener_nombre_objetos_poseidos(sala,
								    &cantidad)),
		     "Vuelvo a obtener los nombres de los objetos poseidos");

	pa2m_afirmar(cantidad == 0, "El jugador no todavía no tiene ningún objeto");

	free(vector);

	pa2m_afirmar(sala_agarrar_objeto(sala, "puerta") == false,
		     "No puedo agarrar la puerta (no es asible)");

	pa2m_afirmar(sala_agarrar_objeto(sala, "pokebola") == true,
		     "Puedo agarrar la pokebola");

	pa2m_afirmar((texto = sala_describir_objeto(sala, "pokebola")) !=
			     NULL,
		     "Puedo pedir la descripción de la pokebola");

	pa2m_afirmar(strcmp(texto,
			    "Una poquebola roja y blanca") == 0,
		     "La descripcion de la pokebola es la correcta");

	pa2m_afirmar(sala_agarrar_objeto(sala, "llave") == false,
		     "No puedo agarrar la llave (no la conozco)");

	pa2m_afirmar(sala_ejecutar_interaccion(sala, "examinar", "habitacion", "", contar_acciones, &contadores) == 0,
		     "Examinar la habitacion no vuelve a descubrir los objetos");

	pa2m_afirmar(contadores.totales == 2 && contadores.descubrir == 2,
		     "La cantidad de objetos descubiertos sigue siendo 2");


	pa2m_afirmar(
		(vector = sala_obtener_nombre_objetos_conocidos(sala,
								&cantidad)),
		"Puedo obtener los nombres de los objetos conocidos oooootra vez");

	pa2m_afirmar(cantidad == 2, "Ahora conozco 2 objetos");

	pa2m_afirmar(vector_contiene_elementos(vector, vector_hpu, cantidad) ==
			     2,
		     "Los objetos son la habitación y puerta");

	free(vector);

	pa2m_afirmar(sala_ejecutar_interaccion(sala, "abrir", "pokebola",
					       "", contar_acciones,
					       &contadores) == 2,
		     "Abrir la pokebola ejecuta 2 acciones");

	pa2m_afirmar(contadores.totales == 4 && contadores.descubrir == 3 && contadores.eliminar==1,
		     "Hasta ahora, los objetos descubiertos son 3 y los eliminados 1");

	pa2m_afirmar(sala_ejecutar_interaccion(sala, "examinar", "habitacion",
					       "", contar_acciones,
					       &contadores) == 0,
		     "Examinar la habitacion no vuelve a descubrir la pokebola");

	pa2m_afirmar(contadores.totales == 4 && contadores.descubrir == 3,
		     "La cantidad de objetos descubiertos sigue siendo 3");

	pa2m_afirmar(sala_agarrar_objeto(sala, "pokebola") == false,
		     "No puedo agarrar la pokebola (no existe mas)");

	pa2m_afirmar(
		(texto = sala_describir_objeto(sala, "pokebola")) == NULL,
		"No puedo pedir la descripción de la pokebola (no existe)");

	pa2m_afirmar(
		(vector = sala_obtener_nombre_objetos_conocidos(sala,
								&cantidad)),
		"Puedo obtener los nombres de los objetos conocidos ooooooooootra vez");

	pa2m_afirmar(cantidad == 3, "Ahora conozco 3 objetos");

	pa2m_afirmar(vector_contiene_elementos(vector, vector_hpulla, cantidad) ==
			     3,
		     "Los objetos son la habitación, puerta y llave");

	free(vector);

	pa2m_afirmar(sala_ejecutar_interaccion(sala, "abrir", "puerta",
					       "", contar_acciones,
					       &contadores) == 1,
		     "Abrir la puerta muestra un mensaje (no se puede)");


	pa2m_afirmar(contadores.totales == 5 && contadores.mostrar==1,
		     "Se invocó la función de mostrar con la acción MOSTRAR");

	pa2m_afirmar(sala_ejecutar_interaccion(sala, "salir", "puerta",
					       "", contar_acciones,
					       &contadores) == 0,
		     "No puedo salir por la puerta (no existe la acción)");

	pa2m_afirmar(contadores.totales == 5,
		     "No se invocó la función de mostrar");

	pa2m_afirmar(sala_agarrar_objeto(sala, "llave")==true, "Puedo agarrar la llave");

	pa2m_afirmar((vector = sala_obtener_nombre_objetos_poseidos(sala,
								    &cantidad)),
		     "Puedo obtener los nombres de los objetos poseidos una vez mas");

	pa2m_afirmar(cantidad == 1, "El jugador tiene un objeto");

	pa2m_afirmar(strcmp(vector[0], "llave")==0, "El objeto es la llave");

	free(vector);

	pa2m_afirmar(sala_ejecutar_interaccion(sala, "abrir", "llave",
					       "puerta", contar_acciones,
					       &contadores) == 1,
		     "Puedo 'abrir llave puerta' y se ejecuta una acción");

	pa2m_afirmar(contadores.totales == 6 && contadores.reemplazar==1,
		     "Se invocó la función de mostrar con la acción de tipo REEMPLAZO");

	pa2m_afirmar(
		(vector = sala_obtener_nombre_objetos_conocidos(sala,
								&cantidad)),
		"Puedo obtener los nombres de los objetos conocidos oooooooooooooooootra vez");

	pa2m_afirmar(cantidad == 2, "Ahora conozco 2 objetos");

	pa2m_afirmar(vector_contiene_elementos(vector, vector_hpua, cantidad) ==
			     2,
		     "Los objetos son la habitación y la puerta-abierta");

	free(vector);

	pa2m_afirmar(sala_ejecutar_interaccion(sala, "examinar", "habitacion",
					       "", contar_acciones,
					       &contadores) == 0,
		     "Examinar la habitacion no vuelve a descubrir la pokebola ni la puerta");

	pa2m_afirmar(contadores.totales == 6,
		     "No se invocó la función de mostrar");

	pa2m_afirmar((texto = sala_describir_objeto(sala, "puerta")) ==
			     NULL,
		     "No puedo describir mas la puerta (no existe mas)");

	pa2m_afirmar((texto = sala_describir_objeto(sala, "llave")) !=
			     NULL,
		     "Puedo pedir la descripción de la llave (todavía existe)");

	pa2m_afirmar(strcmp(texto,
			    "Llave con forma de pikachu") == 0,
		     "La descripcion de la llave es la correcta");

	pa2m_afirmar((texto = sala_describir_objeto(sala, "puerta-abierta")) !=
			     NULL,
		     "Puedo pedir la descripción de la puerta-abierta");

	pa2m_afirmar(strcmp(texto,
			    "La puerta está abierta, podes salir") == 0,
		     "La descripcion de la puerta-abierta es correcta");

	pa2m_afirmar(sala_agarrar_objeto(sala, "puerta-abierta") == false,
		     "No puedo agarrar la puerta-abierta");


	pa2m_afirmar(sala_ejecutar_interaccion(sala, "salir", "puerta-abierta",
					       "", contar_acciones,
					       &contadores) == 1,
		     "Puedo salir por la puerta abierta");

	pa2m_afirmar(contadores.totales == 7 && contadores.escapar==1,
		     "Se invocó la función de mostrar con la acción ESCAPAR");

	pa2m_afirmar(sala_escape_exitoso(sala)==true, "El escape es exitoso");

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

	pa2m_nuevo_grupo("Pruebas de funcionamiento del escenario básico completo");
	pruebas_escenario_basico();

	return pa2m_mostrar_reporte();
}
