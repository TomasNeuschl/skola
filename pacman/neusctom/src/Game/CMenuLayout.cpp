#include <Game/CMenuLayout.h>
#include <Engine/CNCurses.h>
#include <Engine/CWindow.h>

#include <vector>
#include <string>
#include <cstdlib>

CMenuLayout::CMenuLayout(int width, int height, CStateMenu *CState) : CLayout(width, height),
                                                                      CState(CState),
                                                                      menu(NULL),
                                                                      logo(NULL)
{
    window_init();
}
CMenuLayout::~CMenuLayout()
{
    window_exit();
}
void CMenuLayout::window_init()
{
    CLayout::window_init();

    logo = new CWindow(main_wind, 25, 0, 52, 16);
    menu = new CWindow(main_wind, 0, 0, 24, 0, true, "MENU");

    menu->refresh();
}
void CMenuLayout::window_exit()
{
    delete menu;
    delete logo;

    CLayout::window_exit();
}

void CMenuLayout::draw(CMenu *_menu)
{
    main_wind->clear();
    logo->clear();

    std::vector<std::string> pac_ascii = {"================================================.",
                                          "     .-.   .-.     .--.                         |",
                                          "    | OO| | OO|   / _.-' .-.   .-.  .-.   .''.  |",
                                          "    |   | |   |   \\  '-. '-'   '-'  '-'   '..'  |",
                                          "    '^^^' '^^^'    '--'                         |",
                                          "===============.  .-.  .================.  .-.  |",
                                          "               | |   | |                |  '-'  |",
                                          "               | |   | |                |       |",
                                          "               | ':-:' |                |  .-.  |",
                                          "               |  '-'  |                |  '-'  |",
                                          "==============='       '================'       |",
                                          "    ___________    ____   _____ _____    ____  _|"};

    for (unsigned int i = 0; i < pac_ascii.size(); ++i)
        logo->print_str(pac_ascii[i], 3, i, COLOR_PAIR(PAIR_RED_BLACK));

    logo->refresh();

    menu->clear();
    _menu->draw(menu);

    main_wind->refresh();
    menu->refresh();
    refresh();
}
void CMenuLayout::redraw()
{
}
