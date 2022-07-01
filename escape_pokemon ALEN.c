#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ERROR -1
#define MAX_STRING 100                                               

void imprimir_objetos_sala(sala_t *sala){

	int cantidad_objetos = 0;

	char **nombre_objetos = sala_obtener_nombre_objetos(sala, &cantidad_objetos);

	if(nombre_objetos == NULL || cantidad_objetos == ERROR){
		printf("Hubo un error al imprimir los objetos de la sala\n");
	}

	printf("\nObjetos...\n");

	for(int i = 0; i < cantidad_objetos; i++){
		printf("%i: %s\n", i, nombre_objetos[i]);
	}
	
	free(nombre_objetos);
}

void imprimir_interacciones_sala(sala_t *sala){

	printf("\nInteracciones...\n");

	printf("Examinar habitación: ");
	sala_es_interaccion_valida(sala, "examinar", "habitacion", "") ? printf("Válido\n") : printf("Inválido\n");

	printf("Abrir pokebola: ");
	sala_es_interaccion_valida(sala, "abrir", "pokebola", "") ? printf("Válido\n") : printf("Inválido\n");

	printf("Usar llave en el cajon: ");
	sala_es_interaccion_valida(sala, "usar", "llave", "cajon") ? printf("Válido\n") : printf("Inválido\n");

	printf("Quemar la mesa: ");
	sala_es_interaccion_valida(sala, "quemar", "mesa", "") ? printf("Válido\n") : printf("Inválido\n");
}

void mostrar_mensaje(const char *mensaje, enum tipo_accion accion, void *aux)
{
	printf("\n%s\n\n", mensaje);
}

void imprimir_objetos_conocidos(sala_t *sala)
{
	int cantidad_conocidos = 0;

	char **conocidos = sala_obtener_nombre_objetos_conocidos(sala, &cantidad_conocidos);
	if(!conocidos || cantidad_conocidos == ERROR){
		printf("\nHubo un error al imprimir los objetos conocidos\n");
	}
	printf("\nObjetos conocidos:\n\n");
	
	for (int i = 0; i < cantidad_conocidos; i++) {
		printf("%i: %s\n\n", i, conocidos[i]);
	}

	free(conocidos);
}

void imprimir_inventario(sala_t *sala)
{
	int cantidad_poseidos = 0;
	char **poseidos = sala_obtener_nombre_objetos_poseidos(sala, &cantidad_poseidos);
	if(!poseidos || cantidad_poseidos == ERROR){
		printf("\nHubo un error al imprimir los objetos del inventario\n");
	}
	
	printf("\nInventario:\n\n");
	
	for (int i = 0; i < cantidad_poseidos; i++) {
		printf("%i: %s\n\n", i, poseidos[i]);
	}
	free(poseidos);
}

void imprimir_introduccion()
{
        printf("\nAbrís los ojos.\n");
        sleep(2);
        printf("\nEstá todo oscuro.\n");
        sleep(2);
        printf("\nNo sabés dónde estás.\n");
        sleep(2);
        printf("\nEstás confundido y mareado.\n");
        sleep(2);
        printf("\nSeguro te la re pusiste en la pera anoche y estás tirado en algún callejón.\n");
        sleep(3);
        printf("\n\nAl prestar más atención, te das cuenta que estás en una especie de habitación.\n");
        sleep(3);
        printf("\nTe incorporas y miras a tu alrededor, en la oscuridad. Llegas a discernir lo que parece una pared.\n");
        sleep(3);
        printf("\nQuizás sea buena idea >examinar< con más detalle la habitación.\n\n\n");

        printf("(I) Inventario\t\t (C) Objetos descubiertos \t\t (A) Ayuda\n\n");

        printf("=================================================================================================================================================================\n\n");
}

int validar_opcion(sala_t *sala, char *comando, char *objeto1, char *objeto2, bool *ganado)
{
	if(!strcmp(comando, "A") || !strcmp(comando, "a")){

		printf("\nEstos son los comandos disponibles:\n\n");
		printf("\t-Para ver los objetos en el inventario ingresá (I).\n");
		printf("\t-Para ver los objetos con los que podes interactuar ingresá (C).\n");
		printf("\t-Para agarrar un objeto de la sala, ingresá 'agarrar' seguido del objeto.\n");
		printf("\t-Para ver la descripcion de un objeto, ingresá 'descripcion' seguido del objeto.\n");
		printf("\t-Para salir del juego ingresá 'salir'.\n");
		printf("\n\tTambién podés realizar las siguientes acciones seguidas de los objetos conocidos de la sala: \n\n\t\t-Examinar.\n\t\t-Usar.\n\t\t-Abrir.\n\t\t-Salir.\n\n");
	}

	else if(!strcmp(comando, "agarrar")){
		if(sala_agarrar_objeto(sala, objeto1)){
			printf("\nNuevo objeto en el inventario: %s\n\n", objeto1);
		}
		else{
			printf("\nNo se puede agarrar ese objeto\n\n");
		}				
	}

	else if(!strcmp(comando, "describir") && strcmp(objeto1, "") != 0){
		char *descripcion = sala_describir_objeto(sala, objeto1);
		if(descripcion){
			printf("\n%s\n", descripcion);
		}	
	}

	else if(!strcmp(comando, "salir") && !strcmp(objeto1, "")){
		system("clear");
		return -1;
	}

	else if((!strcmp(comando, "I") || !strcmp(comando, "i")) && !strcmp(objeto1, "")){
		imprimir_inventario(sala);
	}

	else if((!strcmp(comando, "C") || !strcmp(comando, "c")) && !strcmp(objeto1, "")){
		imprimir_objetos_conocidos(sala);
	}

	else if(strcmp(comando, "") != 0 && strcmp(objeto1, "") != 0){
		sala_ejecutar_interaccion(sala, comando, objeto1, objeto2, mostrar_mensaje, NULL);
	}

	if(sala_escape_exitoso(sala)){
                system("clear");
                
                                           
                                          
		*ganado = true;
		return -1;
	}

	return 0;
}

int iniciar_juego(sala_t *sala)
{
	bool ganado = false;

	while(ganado == false){

		char input[MAX_STRING];
		char comando[MAX_STRING];
		strcpy(comando, "");
		char objeto1[MAX_STRING];
		strcpy(objeto1, "");
		char objeto2[MAX_STRING];
		strcpy(objeto2, "");

                printf("> ");

                scanf(" %[^\n]", input);

		sscanf(input, "%s %s %s", comando, objeto1, objeto2);

		int opcion = validar_opcion(sala, comando, objeto1, objeto2, &ganado);

		if(opcion == -1){
			return -1;
		}
	}
        return 0;
}

void mostrar_instrucciones()
{
}

void menu_principal(sala_t *sala)
{
	char opcion;
	printf("\nESCAPE POKEMON\n\n");
	printf("> Iniciar el juego (J)\n\n");
	printf("> Instrucciones del juego (I)\n\n");
	printf("> Salir del juego (S)\n\n");

	scanf(" %c", &opcion);

	if(opcion == 'J' || opcion == 'j'){
		system("clear");
                //imprimir_introduccion();
		int salir = iniciar_juego(sala);
                if(salir == -1){
                        return;
                }
		menu_principal(sala);
	}
	else if(opcion == 'I' || opcion == 'i'){
		system("clear");
		mostrar_instrucciones();
	}
	else if(opcion == 'S' || opcion == 's'){

		printf("\nEstás seguro que querés salir del juego? (y/n): ");
		char opcion;
		scanf(" %c", &opcion);

		while(opcion != 'Y' && opcion != 'y' && opcion != 'N' && opcion != 'n'){
			printf("Ingrese una opción válida (y/n): ");
			scanf(" %c", &opcion);
		}
		if(opcion == 'Y' || opcion == 'y'){
			return;
		}
		else if(opcion == 'N' || opcion == 'n'){
			system("clear");
			menu_principal(sala);
		}	
	}
}

int main(int argc, char *argv[])
{
	if (argc != 3){
		return ERROR;
	}
	sala_t *sala = sala_crear_desde_archivos(argv[1], argv[2]);

	if (!sala) {
		printf("\nError al crear la sala de escape\n");
		return ERROR;
	}

	menu_principal(sala);

	//imprimir_objetos_sala(sala);
	//imprimir_interacciones_sala(sala);


	sala_destruir(sala);

	return 0;
}