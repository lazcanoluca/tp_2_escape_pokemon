#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/ioctl.h>

#include "controlador.h"

#define C_BLACK	        "\e[30m"
#define C_RED	        "\e[31m"
#define C_GREEN	        "\e[32m"
#define C_YELLOW        "\e[33m"
#define C_BLUE	        "\e[34m"
#define C_MAGENTA       "\e[35m"
#define C_CYAN	        "\e[36m"
#define C_WHITE	        "\e[37m"
#define C_RESET	        "\e[0m"

#define MAIN_TITLE_WIDTH 69
#define MAIN_TITLE_HEIGHT 20

#define CANT_OPCIONES_MENU 3
#define JUGAR 1
#define INSTRUCCIONES 2
#define SALIR 3

#define ARROW_KEY_UP    
#define ARROW_KEY_DOWN  
#define ARROW_KEY_LEFT  
#define ARROW_KEY_RIGHT


struct winsize;

struct winsize console_size()
{
        struct winsize w;
        ioctl(0, TIOCGWINSZ, &w);

        return w;
}

int console_height()
{
        return console_size().ws_row;
}

int console_width()
{
        return console_size().ws_col;
}

void center_horizontal(int width)
{
        for (int i = 0; i < (console_width()/2) - (width/2); i++) {
                printf(" ");
        }
}

void center_vertical(int height)
{
        for (int i = 0; i < (console_height()/2) - (height/2); i++) {
                printf("\n");
        }
}

void main_title()
{
        printf(C_CYAN"");
        center_horizontal(MAIN_TITLE_WIDTH);
        puts("     _____ _                 ____  _           _ _                   ");
        center_horizontal(MAIN_TITLE_WIDTH);
        puts("    |_   _| |__   ___       | __ )(_)_ __   __| (_)_ __   __ _       ");
        center_horizontal(MAIN_TITLE_WIDTH);
        puts("      | | | '_ \\ / _ \\      |  _ \\| | '_ \\ / _` | | '_ \\ / _` | ");
        center_horizontal(MAIN_TITLE_WIDTH);
        puts("      | | | | | |  __/      | |_) | | | | | (_| | | | | | (_| |      ");
        center_horizontal(MAIN_TITLE_WIDTH);
        puts("      |_| |_| |_|\\___|      |____/|_|_| |_|\\__,_|_|_| |_|\\__, |   ");
        center_horizontal(MAIN_TITLE_WIDTH);
        puts("                                                         |___/       ");
        center_horizontal(MAIN_TITLE_WIDTH);
        puts("                 ___   __      _    ____   ____ ___ ___              ");
        center_horizontal(MAIN_TITLE_WIDTH); 
        puts("                / _ \\ / _|    / \\  / ___| / ___|_ _|_ _|           ");
        center_horizontal(MAIN_TITLE_WIDTH);
        puts("               | | | | |_    / _ \\ \\___ \\| |    | | | |           ");
        center_horizontal(MAIN_TITLE_WIDTH);
        puts("               | |_| |  _|  / ___ \\ ___) | |___ | | | |             ");
        center_horizontal(MAIN_TITLE_WIDTH);
        puts("                \\___/|_|   /_/   \\_\\____/ \\____|___|___|         ");
        printf(""C_RESET);

        printf("\n");
        center_horizontal(15);
        puts("by Luca Lazcano");

}   

void main_menu(int posicion)
{
        center_horizontal(29);
        if (posicion == 1) printf(C_GREEN">  ");
        else printf("   ");
        puts("JUGAR                  (j)"C_RESET);

        center_horizontal(29);
        if (posicion == 2) printf(C_GREEN">  ");
        else printf("   ");
        puts("INSTRUCCIONES          (i)"C_RESET);

        center_horizontal(29);
        if (posicion == 3) printf(C_GREEN">  ");
        else printf("   ");
        puts("SALIR                  (q)"C_RESET);
}

void main_screen(int selected)
{
        system("clear");

        center_vertical(MAIN_TITLE_HEIGHT);

        main_title();
        printf("\n\n\n");
        main_menu(selected);

        center_vertical(MAIN_TITLE_HEIGHT);
}

void input_handler(char input, bool *on_main_menu, int *selected, bool *exit)
{
        if (input == 'q') {
                (*on_main_menu) = false;
                (*exit) = true;
        }
        
        if (input == 'w') {
                if ((*selected)-1 == 0)
                        (*selected) = 3;
                else (*selected)--;
        }

        if (input == 's') {
                if ((*selected)+1 == CANT_OPCIONES_MENU+1)
                        (*selected) = 1;
                else (*selected)++;
        }

        if (input == '\n') {
                if ((*selected) == SALIR) {
                        (*on_main_menu) = false;
                        (*exit) = true;
                }
                // printf("yay");
        }
}

// void quit_greeting()
// {

// }


int main(int argc, char const *argv[])
{
        bool exit = false;
        bool on_main_menu = true;
        int selected = 1;

        // while (!exit) {
        // }
        
        while (on_main_menu) {
                main_screen(selected);
                char input;
                printf("your input: ");
                // scanf(" %c", &input);
                inicializar_controlador();
                input = getchar();
                terminar_controlador();
                input_handler(input, &on_main_menu, &selected, &exit);
        }
        system("clear");
        printf("Hasta luego vuelva prontos :)");
        return 0;
}
