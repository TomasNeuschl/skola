#include <Engine/CWindow.h>

#include <sstream> // stringstream
#include <iostream>

CWindow::CWindow(int x, int y, int w, int h) : wind(NULL), x(x), y(y), width(w), height(h)
{
    this->border = true;
    wind = newwin(height, width, y, x);
}
CWindow::CWindow(CWindow *parent, int x, int y, int width, int height) : wind(NULL), label("")
{
    this->border = false;
    if (parent && parent->border)
    {
        if (y == 0)
            y = 1;
        if (x == 0)
            x = 1;
        if (height == 0)
            height = parent->height - 2;
        if (width == 0)
            width = parent->width - 2;
    }
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->wind = derwin(parent->wind, height, width, y, x);
}
CWindow::CWindow(int x, int y, int w, int h, bool border, std::string label) : wind(NULL), x(x), y(y), width(w), height(h), label(label)
{
    this->border = border;
    this->wind = newwin(height, width, y, x);
}
CWindow::CWindow(CWindow *parent, int x, int y, int width, int height, bool border, std::string label) : wind(NULL), label(label)
{
    this->border = border;

    if (parent->border)
    {
        if (y == 0)
            y = 1;
        if (x == 0)
            x = 1;
        if (height == 0)
            height = parent->height - 2;
        if (width == 0)
            width = parent->width - 2;
    }

    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->wind = derwin(parent->wind, height, width, y, x);
}

CWindow::~CWindow()
{
    if (wind)
        delwin(wind);
}
void CWindow::set_lower_text(std::string text)
{
    lower_text = text;
}

void CWindow::print_char(int c, int x, int y)
{
    mvwaddch(wind, y, x, c);
}

void CWindow::print(int c, int x, int y, int colour_pair)
{
    wattron(wind, A_BOLD);
    wattron(wind, colour_pair);
    mvwaddch(wind, y, x, c);
    wattroff(wind, colour_pair);
    wattroff(wind, A_BOLD);
}
void CWindow::clear()
{
    werase(wind);
    if (border)
        box(wind, 0, 0);
    if (!label.empty())
        print_str("[" + label + "]", 3, 0);
    if (!lower_text.empty())
        print_str("[" + lower_text + "]", 3, this->height - 1);
}
void CWindow::refresh()
{
    wrefresh(wind);
}
int CWindow::get_height() const
{
    return height;
}
int CWindow::get_width() const
{
    return width;
}
int CWindow::get_x() const
{
    return x;
}
int CWindow::get_y() const
{
    return y;
}
void CWindow::print_str(std::string str, int x, int y)
{
    if (!str.empty())
        mvwaddstr(wind, y, x, str.c_str());
}
void CWindow::print_str(std::string str, int x, int y, int colour_pair)
{
    if (!str.empty())
    {
        wattron(wind, A_BOLD);
        wattron(wind, colour_pair);
        mvwaddstr(wind, y, x, str.c_str());
        wattroff(wind, colour_pair);
        wattroff(wind, A_BOLD);
    }
}
