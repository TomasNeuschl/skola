#include <Engine/CLayout.h>
#include <Engine/CNCurses.h>

#include <iostream>
#include <cstdlib>

CLayout::CLayout(int width, int height)
{
    main_wind = NULL;
    needed_w = width;
    needed_h = height;
}
CLayout::~CLayout()
{
    window_exit();
}
void CLayout::window_init()
{
    int cur_h, cur_w;
    getmaxyx(stdscr, cur_h, cur_w);

    if (cur_w < needed_w || cur_h < needed_h)
    {
        CNCurses::exit();
        std::cerr << "console is too small." << std::endl
                  << "has to be atleast "<< needed_w << "x" << needed_h << std::endl;
        exit(EXIT_FAILURE);
    }
    screen_height = needed_h;
    screen_width = needed_w;

    clear();

    main_wind = new CWindow(cur_w / 2 - needed_w / 2, cur_h / 2 - needed_h / 2, CLayout::needed_w, CLayout::needed_h, true, "Pacman");

    main_wind->refresh();
}
void CLayout::window_exit()
{
    delete main_wind;
    main_wind = NULL;
}
void CLayout::draw()
{
}
