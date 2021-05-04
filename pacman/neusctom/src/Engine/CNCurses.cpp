#include <Engine/CNCurses.h>
#include <sys/select.h>
#include <unistd.h>
#include <locale.h>

int CNCurses::key_pressed = ERR;

void CNCurses::init()
{
    setlocale(LC_CTYPE, "");
    cbreak();
    noecho();
    initscr();
    curs_set(0);
    start_color();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    init_color(COLOR_CYAN, 248, 24, 148);
    init_color(COLOR_MAGENTA, 255, 165, 0);
    init_pair(PAIR_RED_BLACK, COLOR_RED, COLOR_BLACK);
    init_pair(PAIR_PINK_BLACK, COLOR_CYAN, COLOR_BLACK);
    init_pair(PAIR_BLUE_BLUE, COLOR_BLUE, COLOR_BLUE);
    init_pair(PAIR_YELLOW_BLACK, COLOR_YELLOW, COLOR_BLACK);
    init_pair(PAIR_BLUE_BLACK, COLOR_BLUE, COLOR_BLACK);
    init_pair(PAIR_GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);
    init_pair(PAIR_WHITE_BLACK, COLOR_WHITE, COLOR_BLACK);
    init_pair(PAIR_RED_WHITE, COLOR_RED, COLOR_WHITE);
    init_pair(PAIR_BLACK_WHITE, COLOR_BLACK, COLOR_WHITE);
    init_pair(PAIR_ORANGE_BLACK, COLOR_MAGENTA, COLOR_BLACK);
    
    //ESCDELAY = 25;
    refresh();
}

void CNCurses::exit()
{
    erase();
    refresh();
    endwin();
}

int CNCurses::get_input(int delay)
{
    int retval = 0;
    int c=0;
    
    fd_set input;
    struct timeval timeout;

    timeout.tv_sec = 0;
    timeout.tv_usec = delay * 1000; // microseconds

    // If #delay_ms is -1, we'll wait infinitely
    // (sending NULL to #select())
    struct timeval *timeout_p = NULL;
    if (delay != -1)
        timeout_p = &timeout;

    FD_ZERO(&input);
    FD_SET(STDIN_FILENO, &input);

    retval = select(FD_SETSIZE, &input, NULL, NULL, timeout_p);

    // Ncurses' function that works without delay
    // (because we nodelay()'ed)
    c = getch();

    if ((retval == 1) && (c == ERR)) // ERROR
        return -1;

    if (retval == 0)
        return ERR; // Nothing was pressed.
            // This is an Ncurses internal value.

    return c;
}
