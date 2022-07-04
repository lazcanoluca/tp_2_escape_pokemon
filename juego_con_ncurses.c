#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define WINDOW_VERTICAL "|"
#define WINDOW_HORIZONTAL "-"
#define WINDOW_CORNER "+"
#define WALL '#'
#define DOOR_VERTICAL '|'
#define DOOR_HORIZONTAL '_'

#define MAX_INPUT 100

#define SALA_1
#define WIDTH_SALA_1 60
#define HEIGHT_SALA_1 30

#define SALA_EJ_02 "#######################################################################################################################################"
#define SALA_EJ_03 "#######################################################################################################################################"
#define SALA_EJ_04 "###               ###                                          ###                                                                  ###"
#define SALA_EJ_05 "###               ###                                          ###                                                                  ###"
#define SALA_EJ_06 "###               ###                                          ###                                                                  ###"
#define SALA_EJ_07 "###               ###                                          ###                                                                  ###"
#define SALA_EJ_08 "###               ###                                          ##########                                                           ###"
#define SALA_EJ_09 "###               ###                                          ##########                                                           ###"
#define SALA_EJ_10 "###               ###                                          ###                                                                   | "
#define SALA_EJ_11 "###               ###                                          ###                                                                   | "
#define SALA_EJ_12 "###               ###                                          ###                                                                   | "
#define SALA_EJ_13 "###               ###                                                                                                                | "
#define SALA_EJ_14 "###               ###                                                                                                                | "
#define SALA_EJ_15 "###               ###                                                                                                               ###"
#define SALA_EJ_16 "###               ###                                                                                                               ###"
#define SALA_EJ_17 "###                                                                                                                                 ###"
#define SALA_EJ_18 "###                                                       ######                                                                    ###"
#define SALA_EJ_19 "###                                                       ######                                         ##############################"
#define SALA_EJ_20 "###                                                       ######                                         ##############################"
#define SALA_EJ_21 "###                                                                                                      ###                        ###"
#define SALA_EJ_22 "###                                                                                                      ###                        ###"
#define SALA_EJ_23 "###                                                                                                      ###                        ###"
#define SALA_EJ_24 "###                              ###                                                                     ###                        ###"
#define SALA_EJ_25 "###                              ###                                                                     ###                        ###"
#define SALA_EJ_26 "###                              ###                                                                     ###                        ###"
#define SALA_EJ_27 "###                              ###                                                                                                ###"
#define SALA_EJ_28 "###                              ###                                                                                                ###"
#define SALA_EJ_29 "###                              ###                                                                                                ###"
#define SALA_EJ_30 "###                              ###                                                                                                ###"
#define SALA_EJ_31 "###                              ###                                                                                                ###"
#define SALA_EJ_32 "#######################################################################################################################################"
#define SALA_EJ_33 "#######################################################################################################################################"

// Color duos.
#define CYAN_ON_BLACK COLOR_PAIR(1)
#define BLACK_ON_WHITE COLOR_PAIR(2)
#define MAGENTA_ON_BLACK COLOR_PAIR(3)
#define GREEN_ON_WHITE COLOR_PAIR(4)

// Player states.
#define IDLE -1
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define INTERFACE_WIDTH 35
#define INVENTORY_HEIGHT 7

#define MAIN_TITLE_WIDTH 69
#define MAIN_TITLE_HEIGHT 14

#define MAIN_MENU_WIDTH 20
#define MAIN_MENU_HEIGHT 10

#define MAIN_SCREEN_HEIGHT MAIN_TITLE_HEIGHT + MAIN_MENU_HEIGHT
#define MAIN_SCREEN_WIDTH MAIN_TITLE_WIDTH

// Main title.
#define MAIN_TITLE_LINE_01 "     _____ _                 ____  _           _ _                   "
#define MAIN_TITLE_LINE_02 "    |_   _| |__   ___       | __ )(_)_ __   __| (_)_ __   __ _       "
#define MAIN_TITLE_LINE_03 "      | | | '_ \\ / _ \\      |  _ \\| | '_ \\ / _` | | '_ \\ / _` |      "
#define MAIN_TITLE_LINE_04 "      | | | | | |  __/      | |_) | | | | | (_| | | | | | (_| |      "
#define MAIN_TITLE_LINE_05 "      |_| |_| |_|\\___|      |____/|_|_| |_|\\__,_|_|_| |_|\\__, |      "
#define MAIN_TITLE_LINE_06 "                                                         |___/       "
#define MAIN_TITLE_LINE_07 "                 ___   __      _    ____   ____ ___ ___              "
#define MAIN_TITLE_LINE_08 "                / _ \\ / _|    / \\  / ___| / ___|_ _|_ _|             "
#define MAIN_TITLE_LINE_09 "               | | | | |_    / _ \\ \\___ \\| |    | | | |              "
#define MAIN_TITLE_LINE_10 "               | |_| |  _|  / ___ \\ ___) | |___ | | | |              "
#define MAIN_TITLE_LINE_11 "                \\___/|_|   /_/   \\_\\____/ \\____|___|___|             "
#define MAIN_TITLE_LINE_12 "                                                                     "
#define MAIN_TITLE_LINE_13 "                                                      by Luca Lazcano"

#define PLAYER_HEAD_RIGHT       "(>_>)"
#define PLAYER_MID_RIGHT        "/) )>"
#define PLAYER_BOT_RIGHT        " / / "

#define PLAYER_HEAD_LEFT        "(<_<)"
#define PLAYER_MID_LEFT         "<( (\\"
#define PLAYER_BOT_LEFT        " \\ \\ "

#define PLAYER_HEAD_UP		"\\^_^/"
#define PLAYER_MID_UP		" ( ) "
#define PLAYER_BOT_UP		" / \\ "

#define PLAYER_HEAD_DOWN        "(u_u)"
#define PLAYER_MID_DOWN		"/( )\\"
#define PLAYER_BOT_DOWN		" / \\ "

#define PLAYER_HEAD_IDLE	"(*_*)"
#define PLAYER_MID_IDLE		"/( )\\"
#define PLAYER_BOT_IDLE		" | | "

#define PLAYER_PARTY_HEAD_1	"(>_</"
#define PLAYER_PARTY_MID_1	"/( ) "
#define PLAYER_PARTY_BOT_1	" | | "

#define PLAYER_PARTY_HEAD_2	"\\>_<)"
#define PLAYER_PARTY_MID_2	" ( )\\"
#define PLAYER_PARTY_BOT_2	" | | "

#define PLAYER_AVATAR_WIDTH 5

#define CLEAR_PLAYER "      "

#define MAIN_MENU_PRE ">  "
#define MAIN_MENU_1 "JUGAR           p"
#define MAIN_MENU_2 "INSTRUCCIONES   i"
#define MAIN_MENU_3 "SALIR           q"

#define JUGAR 1
#define E_JUGAR 'p'
#define INSTRUCCIONES 2
#define E_INSTR 'i'
#define SALIR 3
#define E_SALIR 'q'

#define CANT_OPCIONES_MENU 3

#define PLAYER_MOVE 0
#define INTERFACE 2

#define MENU_BROWSE 0
#define EXIT 1
#define PLAY 2
#define INST 3


typedef struct gameScreen {
        WINDOW *scenario;
        WINDOW *inventory;
        WINDOW *interface;
} GameScreen;

typedef struct avatar {
	char Head[PLAYER_AVATAR_WIDTH+1];
	char Mid[PLAYER_AVATAR_WIDTH+1];
	char Bot[PLAYER_AVATAR_WIDTH+1];
} Avatar;

typedef struct player {
        int posX;
        int posY;
        int state;
	Avatar body;
} Player;


typedef struct mainScreen {
        WINDOW *title;
        WINDOW *menu;
} MainScreen;

typedef struct mainMenu {
        int selected;
} MainMenu;

typedef struct room {
	WINDOW *room;
	int width;
	int height;
} Room;

#pragma region UTILITIES

int window_height(WINDOW *window)
{
        int height;
        int width;
        getmaxyx(window, height, width);

        return height;
}

int window_width(WINDOW *window)
{
        int height;
        int width;
        getmaxyx(window, height, width);

        return width;
}

int console_width()
{
        return COLS;
}

int console_height()
{
        return LINES;
}


void initialize()
{
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        curs_set(FALSE);

        start_color();
        init_pair(1, COLOR_CYAN, COLOR_BLACK);
        init_pair(2, COLOR_BLACK, COLOR_WHITE);
        init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(4, COLOR_GREEN, COLOR_WHITE);
}

int offsetX(int containerX, int objectX)
{
        return containerX/2 - objectX/2;
}

int offsetY(int containerY, int objectY)
{
        return containerY/2 - objectY/2;
}

#pragma endregion

void draw_borders(WINDOW *window) {
        int x, y, i;
        getmaxyx(window, y, x);
        // 4 corners
        mvwprintw(window, 0, 0, WINDOW_CORNER);
        mvwprintw(window, y - 1, 0,WINDOW_CORNER);
        mvwprintw(window, 0, x - 1, WINDOW_CORNER);
        mvwprintw(window, y - 1, x - 1, WINDOW_CORNER);

        // sides
        for (i = 1; i < (y - 1); i++) {
                mvwprintw(window, i, 0, WINDOW_VERTICAL);
                mvwprintw(window, i, x - 1, WINDOW_VERTICAL);
        }

        // top and bottom
        for (i = 1; i < (x - 1); i++) {
                mvwprintw(window, 0, i, WINDOW_HORIZONTAL);
                mvwprintw(window, y - 1, i, WINDOW_HORIZONTAL);
        }
}

#pragma region GAME_SCREEN

WINDOW *GameScreenCreateScenario()
{
        int startX_scenario = 0;
        int startY_scenario = 0;
        int width_scenario = console_width() - INTERFACE_WIDTH;
        int height_scenario = console_height() - INVENTORY_HEIGHT;

        WINDOW *scenario = newwin(height_scenario, width_scenario, startY_scenario, startX_scenario);
        draw_borders(scenario);

	mvwprintw(scenario, 1, 	1,  SALA_EJ_02);
	mvwprintw(scenario, 2, 	1,  SALA_EJ_03);
	mvwprintw(scenario, 3, 	1,  SALA_EJ_04);
	mvwprintw(scenario, 4, 	1,  SALA_EJ_05);
	mvwprintw(scenario, 5, 	1,  SALA_EJ_06);
	mvwprintw(scenario, 6, 	1,  SALA_EJ_07);
	mvwprintw(scenario, 7, 	1,  SALA_EJ_08);
	mvwprintw(scenario, 8, 	1,  SALA_EJ_09);
	mvwprintw(scenario, 9,  1, SALA_EJ_10);
	mvwprintw(scenario, 10, 1, SALA_EJ_11);
	mvwprintw(scenario, 11, 1, SALA_EJ_12);
	mvwprintw(scenario, 12, 1, SALA_EJ_13);
	mvwprintw(scenario, 13, 1, SALA_EJ_14);
	mvwprintw(scenario, 14, 1, SALA_EJ_15);
	mvwprintw(scenario, 15, 1, SALA_EJ_16);
	mvwprintw(scenario, 16, 1, SALA_EJ_17);
	mvwprintw(scenario, 17, 1, SALA_EJ_18);
	mvwprintw(scenario, 18, 1, SALA_EJ_19);
	mvwprintw(scenario, 19, 1, SALA_EJ_20);
	mvwprintw(scenario, 20, 1, SALA_EJ_21);
	mvwprintw(scenario, 21, 1, SALA_EJ_22);
	mvwprintw(scenario, 22, 1, SALA_EJ_23);
	mvwprintw(scenario, 23, 1, SALA_EJ_24);
	mvwprintw(scenario, 24, 1, SALA_EJ_25);
	mvwprintw(scenario, 25, 1, SALA_EJ_26);
	mvwprintw(scenario, 26, 1, SALA_EJ_27);
	mvwprintw(scenario, 27, 1, SALA_EJ_28);
	mvwprintw(scenario, 28, 1, SALA_EJ_29);
	mvwprintw(scenario, 29, 1, SALA_EJ_30);
	mvwprintw(scenario, 30, 1, SALA_EJ_31);
	mvwprintw(scenario, 31, 1, SALA_EJ_32);
	mvwprintw(scenario, 32, 1, SALA_EJ_33);


	

        return scenario;
}

WINDOW *GameScreenCreateInterface()
{
        int startX_interface = console_width() - INTERFACE_WIDTH;
        int startY_interface = 0;
        int width_interface = INTERFACE_WIDTH;
        int height_interface = console_height();

        WINDOW *interface = newwin(height_interface, width_interface, startY_interface, startX_interface);
        draw_borders(interface);

        return interface;
}

WINDOW *GameScreenCreateInventory()
{
        int startX_inventory = 0;
        int startY_inventory = console_height() - INVENTORY_HEIGHT;
        int width_inventory = console_width() - INTERFACE_WIDTH;
        int height_inventory = INVENTORY_HEIGHT;

        
        WINDOW *inventory = newwin(height_inventory, width_inventory, startY_inventory, startX_inventory);
        draw_borders(inventory);

        return inventory;
}

GameScreen GameScreenCreate()
{
        GameScreen game_screen;

        game_screen.scenario = GameScreenCreateScenario();
        game_screen.interface = GameScreenCreateInterface();
        game_screen.inventory = GameScreenCreateInventory();

        return game_screen;
}

void GameScreenRefresh(GameScreen game_screen)
{
        wrefresh(game_screen.scenario);
        wrefresh(game_screen.interface);
        wrefresh(game_screen.inventory);
}

void GameScreenDelete(GameScreen game_screen)
{
        delwin(game_screen.scenario);
        delwin(game_screen.interface);
        delwin(game_screen.inventory);
}

int GameScreenInputHandler(int ch)
{
        if (ch == KEY_LEFT || ch == KEY_RIGHT || ch == KEY_DOWN || ch == KEY_UP) {
                // PlayerMove(game_screen.scenario, &player, ch);
                return PLAYER_MOVE;
        }
	else if (ch == '.') {
		return INTERFACE;
	}
        // else if (ch ==)
        
        // wrefresh(game_screen.scenario);
        // GameScreenRefresh(game_screen);
}

#pragma endregion

#pragma region PLAYER

Player PlayerCreate()
{
        Player player;
        return player;
}

void PlayerRender(WINDOW *window, Player *player)
{
        mvwprintw(window, player->posY, player->posX, player->body.Head);
        mvwprintw(window, player->posY+1, player->posX, player->body.Mid);
        mvwprintw(window, player->posY+2, player->posX, player->body.Bot);
}

Avatar PlayerSetBody(Player *player, int state)
{
	// Avatar body = player->;

	switch (state) {

		case IDLE:
			strcpy(player->body.Head, PLAYER_HEAD_IDLE);
			strcpy(player->body.Mid, PLAYER_MID_IDLE);
			strcpy(player->body.Bot, PLAYER_BOT_IDLE);
			break;
		
		case LEFT:
			strcpy(player->body.Head, PLAYER_HEAD_LEFT);
			strcpy(player->body.Mid, PLAYER_MID_LEFT);
			strcpy(player->body.Bot, PLAYER_BOT_LEFT);
			break;

		case RIGHT:
			strcpy(player->body.Head, PLAYER_HEAD_RIGHT);
			strcpy(player->body.Mid, PLAYER_MID_RIGHT);
			strcpy(player->body.Bot, PLAYER_BOT_RIGHT);
			break;

		case UP:
			strcpy(player->body.Head, PLAYER_HEAD_UP);
			strcpy(player->body.Mid, PLAYER_MID_UP);
			strcpy(player->body.Bot, PLAYER_BOT_UP);
			break;
		
		case DOWN:
			strcpy(player->body.Head, PLAYER_HEAD_DOWN);
			strcpy(player->body.Mid, PLAYER_MID_DOWN);
			strcpy(player->body.Bot, PLAYER_BOT_DOWN);
			break;
		
		default:
			break;
	}
	return player->body;
}

void PlayerInit(WINDOW *window, Player *player, int initialX, int initialY)
{
        (player->posX) = initialX;
        (player->posY) = initialY;
	(player->state) = IDLE;
	(player->body) = PlayerSetBody(player, IDLE);
	// Avatar body;
	// (player->body)
	// PlayerSetBody(player, IDLE);

	PlayerRender(window, player);
        // mvwprintw(window, player->posY, player->posX, "P");
}

void PlayerClear(WINDOW *window, int topLeftY, int topLeftX)
{
        mvwprintw(window, topLeftY, topLeftX, CLEAR_PLAYER);
        mvwprintw(window, topLeftY+1, topLeftX, CLEAR_PLAYER);
        mvwprintw(window, topLeftY+2, topLeftX, CLEAR_PLAYER);

}


void PlayerMove(WINDOW *window, Player *player, int ch)
{
        if (ch == KEY_LEFT) {
                (player->posX)--;
                PlayerClear(window, player->posY, player->posX+1);
		PlayerSetBody(player, LEFT);
        } else if (ch == KEY_RIGHT) {
                (player->posX)++;
                PlayerClear(window, player->posY, player->posX-1);
		PlayerSetBody(player, RIGHT);
        } else if (ch == KEY_UP) {
                (player->posY)--;
                PlayerClear(window, player->posY+1, player->posX);
		PlayerSetBody(player, UP);
        } else if (ch == KEY_DOWN) {
                (player->posY)++;
                PlayerClear(window, player->posY-1, player->posX);
		PlayerSetBody(player, DOWN);
        }
        PlayerRender(window, player);
}

// void PlayerRender(WINDOW *window, Player *player, int x, int y);

#pragma endregion


#pragma region MAIN_SCREEN

WINDOW *MainScreenCreateTitle()
{
        WINDOW *title = newwin(MAIN_TITLE_HEIGHT, MAIN_TITLE_WIDTH, offsetY(console_height(), MAIN_SCREEN_HEIGHT), offsetX(console_width(), MAIN_TITLE_WIDTH));


        // draw_borders(title);
        // start_color();
        wattron(title, CYAN_ON_BLACK);
        // printf("hola");
        mvwprintw(title, 1, 0, MAIN_TITLE_LINE_01);
        mvwprintw(title, 2, 0, MAIN_TITLE_LINE_02);
        mvwprintw(title, 3, 0, MAIN_TITLE_LINE_03);
        mvwprintw(title, 4, 0, MAIN_TITLE_LINE_04);
        mvwprintw(title, 5, 0, MAIN_TITLE_LINE_05);
        mvwprintw(title, 6, 0, MAIN_TITLE_LINE_06);
        mvwprintw(title, 7, 0, MAIN_TITLE_LINE_07);
        mvwprintw(title, 8, 0, MAIN_TITLE_LINE_08);
        mvwprintw(title, 9, 0, MAIN_TITLE_LINE_09);
        mvwprintw(title, 10, 0, MAIN_TITLE_LINE_10);
        mvwprintw(title, 11, 0, MAIN_TITLE_LINE_11);
        mvwprintw(title, 12, 0, MAIN_TITLE_LINE_12);
        wattroff(title, CYAN_ON_BLACK);

        wattron(title, MAGENTA_ON_BLACK);
        mvwprintw(title, 13, 0, MAIN_TITLE_LINE_13);
        wattroff(title, MAGENTA_ON_BLACK);
        // mvwprintw(title, 11, 0, MAIN_TITLE_LINE_01);

        return title;
}

WINDOW *MainScreenCreateMenu()
{
        WINDOW *menu = newwin(MAIN_MENU_HEIGHT, MAIN_MENU_WIDTH, offsetY(console_height(), MAIN_SCREEN_HEIGHT)+MAIN_TITLE_HEIGHT, offsetX(console_width(), MAIN_MENU_WIDTH));        

        return menu;
}

MainScreen MainScreenCreate()
{
        MainScreen main_screen;

        main_screen.title = MainScreenCreateTitle();
        main_screen.menu = MainScreenCreateMenu();

        return main_screen;
}

// void MainScreenUpdateMenu(WINDOW *menu, MainScreen main_screen,int selected)
// {
//         main_screen.menu = MainScreenCreateMenu(selected);
// }

void MainScreenRefresh(MainScreen main_screen)
{
        wrefresh(main_screen.title);
        wrefresh(main_screen.menu);
}

void MainScreenDelete(MainScreen main_screen)
{
        delwin(main_screen.title);
        delwin(main_screen.menu);
}

int MainScreenInputHandler(int ch)
{
        if (ch == KEY_UP || ch == KEY_DOWN) {
                return MENU_BROWSE;
        } else if (ch == 'q') {
		return EXIT;
	} else if (ch == 'p') {
		return PLAY;
	}
}

#pragma endregion

#pragma region MAIN_SCREEN_MENU

MainMenu MainMenuCreate()
{
        MainMenu main_menu;
        return main_menu;
}

void MainMenuInit(WINDOW *window, MainMenu *menu)
{
        (menu->selected) = JUGAR;

        wattron(window, GREEN_ON_WHITE);
        mvwprintw(window, 1, 0, MAIN_MENU_PRE);
        mvwprintw(window, 1, 3, MAIN_MENU_1);
        wattroff(window, GREEN_ON_WHITE);

        mvwprintw(window, 3, 3, MAIN_MENU_2);

        mvwprintw(window, 5, 3, MAIN_MENU_3);

}

void MainMenuUpdate(WINDOW *window, MainMenu *menu, int ch)
{
        if (ch == KEY_UP) {
                // (menu->selected)--;
                if ((menu->selected)-1 == 0)
                        (menu->selected) = CANT_OPCIONES_MENU;
                else (menu->selected)--;

        } else if (ch == KEY_DOWN) {
                // (menu->selected)++;

                if ((menu->selected)+1 == CANT_OPCIONES_MENU+1)
                        (menu->selected) = 1;
                else (menu->selected)++;
        }
	// else if (ch == E_SALIR || ( (ch == '\n') && (menu_selected == SALIR) )) {
		
	// }

        if (menu->selected == JUGAR) {
                wattron(window, GREEN_ON_WHITE);
                mvwprintw(window, 1, 0, MAIN_MENU_PRE);
                mvwprintw(window, 1, 3, MAIN_MENU_1);
                wattroff(window, GREEN_ON_WHITE);
        } else {
                mvwprintw(window, 1, 0, MAIN_MENU_PRE);
                mvwprintw(window, 1, 3, MAIN_MENU_1);
        }

        if (menu->selected == INSTRUCCIONES) {
                wattron(window, GREEN_ON_WHITE);
                mvwprintw(window, 3, 0, MAIN_MENU_PRE);
                mvwprintw(window, 3, 3, MAIN_MENU_2);
                wattroff(window, GREEN_ON_WHITE);
        } else {
                mvwprintw(window, 3, 0, MAIN_MENU_PRE);
                mvwprintw(window, 3, 3, MAIN_MENU_2);
        }

        if (menu->selected == SALIR) {
                wattron(window, GREEN_ON_WHITE);
                mvwprintw(window, 5, 0, MAIN_MENU_PRE);
                mvwprintw(window, 5, 3, MAIN_MENU_3);
                wattroff(window, GREEN_ON_WHITE);
        } else {
                mvwprintw(window, 5, 0, MAIN_MENU_PRE);
                mvwprintw(window, 5, 3, MAIN_MENU_3);
        }
}

#pragma region INTERFACE

void InterfaceScroll(WINDOW *console, int rows);

void InterfacePut(WINDOW *console, char *string);

void InterfaceGet(WINDOW *console)
{

	char str[MAX_INPUT];

	int consoleY = window_height(console) - 2;
	int consoleX = console_width() - INTERFACE_WIDTH + 4;

	wattron(console, GREEN_ON_WHITE);
	mvwprintw(console, consoleY, 1, "                                 ");
	mvwprintw(console, consoleY, 2, "> ");
	wattroff(console, GREEN_ON_WHITE);
	
	move(consoleY, consoleX);
	wrefresh(console);
	refresh();


	echo();
	// nocbreak();
	getstr(str);

	// cbreak();
	noecho();


	mvwprintw(console, consoleY-2, 2, "> ");
	mvwprintw(console, consoleY-2, 4, str);

	wattron(console, GREEN_ON_WHITE);
	mvwprintw(console, consoleY, 1, "                                 ");
	mvwprintw(console, consoleY, 2, "> ");
	move(consoleY, consoleX);

	wrefresh(console);
	refresh();
}

#pragma endregion

#pragma region ROOM

// Room RoomCreate(FILE *file, int width, int height)
// {
// 	Room room;
// 	room.width = width;
// 	room.height = height;

// 	WINDOW *room_window = newwin(height, width, 0, 0);

// 	room.room = WINDOW *scenario = newwin(height_scenario, width_scenario, startY_scenario, startX_scenario);
// }

#pragma endregion

#pragma endregion

int main(int argc, char const *argv[])
{

        int input;
        int ch;

	bool exit = false;

        initialize();
        refresh();

	// FILE *file = fopen("sala.txt", "w");
	// FILE *file_ej = fopen("sala_copy.txt", "r");

        MainScreen main_screen = MainScreenCreate();

        MainMenu main_menu = MainMenuCreate();
        MainMenuInit(main_screen.menu, &main_menu);

        MainScreenRefresh(main_screen);

        bool exit_main_screen = false;


        while ( !exit_main_screen && !exit) {

                int input = MainScreenInputHandler(ch = getch());

		if (input == EXIT) {
			exit = true;
		} else if (input == PLAY) {
			exit_main_screen = true;
		}
		
		else if (input == MENU_BROWSE ) {
                        MainMenuUpdate(main_screen.menu, &main_menu, ch);
                }

                MainScreenRefresh(main_screen);

        }

	MainScreenDelete(main_screen);


        GameScreen game_screen = GameScreenCreate();

        // Room room = RoomCreate(file_ej, 137, 34);
        // RoomInit(game_screen.scenario, &room);

        Player player = PlayerCreate();
        PlayerInit(game_screen.scenario, &player, 10, 25);

        GameScreenRefresh(game_screen);

        bool exit_game_screen = false;
      
        while( !exit_game_screen && !exit) {

                int input = GameScreenInputHandler(ch = getch());

		if (ch == KEY_F(1)) {
			exit = true;
		} else if (input == PLAYER_MOVE) {
                        PlayerMove(game_screen.scenario, &player, ch);
		} else if (input == EXIT) {
			exit = true;
		} else if (input == INTERFACE) {
			InterfaceGet(game_screen.interface);
			// exit = false;
		}
		
		// if (ch == 'l')
		// 	putwin(game_screen.scenario, file);

                // else if (input == INTERFACE)

                GameScreenRefresh(game_screen);
        }

        GameScreenDelete(game_screen);
	
	// fclose(file);
	// fclose(file_ej);
	endwin();
        return 0;
}
