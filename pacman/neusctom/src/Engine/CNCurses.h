#pragma once

#include <ncurses.h>

enum ColourPairs
{
    PAIR_BLUE_BLUE = 30,
    PAIR_RED_BLACK,
    PAIR_YELLOW_BLACK,
    PAIR_BLUE_BLACK,
    PAIR_GREEN_BLACK,
    PAIR_WHITE_BLACK,
    PAIR_RED_WHITE,
    PAIR_BLACK_WHITE,
    PAIR_GREEN_WHITE,
    PAIR_PINK_BLACK,
    PAIR_ORANGE_BLACK
};

namespace CNCurses
{
    ///inicializes Ncurses
    ///
    void init();

    ///closes Ncurses
    ///
    void exit();

    ///return pressed key
    int get_input (int delay);

    extern int key_pressed;
}
