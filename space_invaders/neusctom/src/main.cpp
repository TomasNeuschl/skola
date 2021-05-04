#include <iostream>
#include <ncurses.h>
#include "Game.h"
#include "Player.h"
#include "Display.h"

using namespace std;
int main() {
    int pick;
    Display display;
    Display a;
    Game game;
    display.menu();
    while ((pick = getch()) != (int)'q')
    {
        if (pick == (int)'h') display.help();
        if (pick == (int)'s') display.score();
        if (pick == (int)'l') display.legend();
        if (pick == (int)' ') game.start(display);
    }
    return 0;
}