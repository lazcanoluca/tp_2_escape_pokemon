#include <ncurses.h>
#include <stdlib.h>

// #define WINDOW_VERTICAL '_'
// #define WINDOW_HORIZONTAL '-'
// #define WINDOW_CORNER '+'
#define WALL '#'
#define DOOR_VERTICAL '|'
#define DOOR_HORIZONTAL '_'

#define INTERFACE_WIDTH 35
#define INVENTORY_HEIGHT 7

typedef struct gameScreen {
        WINDOW *scenario;
        WINDOW *inventory;
        WINDOW *interface;
} GameScreen;

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

int console_width()
{
        return COLS;
}

int console_height()
{
        return LINES;
}
// void window_borders(WINDOW *window)
// {

// }

void draw_borders(WINDOW *window) {
        int x, y, i;
        getmaxyx(window, y, x);
        // 4 corners
        mvwprintw(window, 0, 0, "#");
        mvwprintw(window, y - 1, 0,"#");
        mvwprintw(window, 0, x - 1, "#");
        mvwprintw(window, y - 1, x - 1, "#");

        // sides
        for (i = 1; i < (y - 1); i++) {
                mvwprintw(window, i, 0, "#");
                mvwprintw(window, i, x - 1, "#");
        }

        // top and bottom
        for (i = 1; i < (x - 1); i++) {
                mvwprintw(window, 0, i, "#");
                mvwprintw(window, y - 1, i, "#");
        }
}

void initialize()
{
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        curs_set(FALSE);
}

// WINDOW *GameScreenCreateScenario()
// {

// }

// WINDOW *GameScreenCreateInterface()
// {


// }

// WINDOW *GameScreenCreateInventory()
// {

// }

GameScreen GameScreenCreate()
{
        GameScreen game_screen;

        int startX_scenario = 0;
        int startY_scenario = 0;
        int width_scenario = console_width() - INTERFACE_WIDTH;
        int height_scenario = console_height() - INVENTORY_HEIGHT;

        WINDOW *scenario = create_newwin(height_scenario, width_scenario, startY_scenario, startX_scenario);
        draw_borders(scenario);

        int startX_interface = console_width() - INTERFACE_WIDTH;
        int startY_interface = 0;
        int width_interface = INTERFACE_WIDTH;
        int height_interface = console_height();

        WINDOW *interface = create_newwin(height_interface, width_interface, startY_interface, startX_interface);
        draw_borders(interface);

        int startX_inventory = 0;
        int startY_inventory = height_scenario;
        int width_inventory = width_scenario;
        int height_inventory = INVENTORY_HEIGHT;

        
        WINDOW *inventory = create_newwin(height_inventory, width_inventory, startY_inventory, startX_inventory);
        draw_borders(inventory);

        // game_screen.scenario = GameScreenCreateScenario();
        // game_screen.interface = GameScreenCreateInterface();
        // game_screen.inventory = GameScreenCreateInventory();
        game_screen.scenario = scenario;
        game_screen.interface = interface;
        game_screen.inventory = inventory;

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

int main(int argc, char const *argv[])
{

        int ch;

        initialize();

        // GameScreen game_screen = GameScreenCreate();
        // GameScreenRefresh(game_screen);

        int startX_scenario = 0;
        int startY_scenario = 0;
        int width_scenario = console_width() - INTERFACE_WIDTH;
        int height_scenario = console_height() - INVENTORY_HEIGHT;

        WINDOW *scenario = create_newwin(height_scenario, width_scenario, startY_scenario, startX_scenario);
        draw_borders(scenario);

        int startX_interface = console_width() - INTERFACE_WIDTH;
        int startY_interface = 0;
        int width_interface = INTERFACE_WIDTH;
        int height_interface = console_height();

        WINDOW *interface = create_newwin(height_interface, width_interface, startY_interface, startX_interface);
        draw_borders(interface);

        int startX_inventory = 0;
        int startY_inventory = height_scenario;
        int width_inventory = width_scenario;
        int height_inventory = INVENTORY_HEIGHT;

        
        WINDOW *inventory = create_newwin(height_inventory, width_inventory, startY_inventory, startX_inventory);
        draw_borders(inventory);

        wrefresh(scenario);
        wrefresh(interface);
        wrefresh(inventory);

        // refresh();
      
        while( (ch = getch()) != KEY_F(1) ) {
                // GameScreenRefresh(game_screen);
                wrefresh(scenario);
                wrefresh(interface);
                wrefresh(inventory);
        }

        // GameScreenDelete(game_screen);

        delwin(scenario);
        delwin(interface);
        delwin(inventory);

		
	endwin();			/* End curses mode		  */
        return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0, 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}

void destroy_win(WINDOW *local_win)
{	
	/* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners 
	 * and so an ugly remnant of window. 
	 */
	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	/* The parameters taken are 
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window 
	 * 3. rs: character to be used for the right side of the window 
	 * 4. ts: character to be used for the top side of the window 
	 * 5. bs: character to be used for the bottom side of the window 
	 * 6. tl: character to be used for the top left corner of the window 
	 * 7. tr: character to be used for the top right corner of the window 
	 * 8. bl: character to be used for the bottom left corner of the window 
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	wrefresh(local_win);
	delwin(local_win);
}
