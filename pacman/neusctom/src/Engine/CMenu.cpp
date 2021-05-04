#include <Engine/CMenu.h>
#include <Engine/CNCurses.h>
#include <cstdlib>

CMenu::CMenu(int x, int y, int width, int height) : cur_index(0), x(x), y(y), width(width), height(height), will_exit(false), selected(false), current(NULL), selected_item(NULL)
{
}
CMenu::~CMenu()
{
    for (unsigned int i = 0; i < items.size(); ++i)
    {
        delete items[i];
        items[i] = NULL;
    }
    items.clear();
}
void CMenu::add(CMenuItem *item)
{
    unsigned i;
    items.push_back(item);
    for (i = 0; i < items.size(); ++i)
        if (items[i])
            break;

    current = items[i];
    cur_index = i;
}
void CMenu::add_blank()
{
    items.push_back(NULL);
}

void CMenu::draw(CWindow *window)
{
    unsigned draw_begin = 0;
    unsigned draw_end = items.size();

    for (unsigned cur_item = draw_begin, yoffset = 0; cur_item < draw_end; cur_item++, yoffset++)
    {
        if (!items[cur_item])
        {
            for (int i = 0; i < width; ++i)
            {
                window->print((int)'-', x + i, y + yoffset, COLOR_PAIR(PAIR_WHITE_BLACK));
            }
        }
        else
        {
            items[cur_item]->draw(window, x, y + yoffset, width, items[cur_item] == current);
        }
    }
}

void CMenu::HandleInput()
{
    //no pressed key
    if (CNCurses::key_pressed == ERR)
        return;

    if (CNCurses::key_pressed == KEY_UP)
        GoPrevItem();

    else if (CNCurses::key_pressed == KEY_DOWN)
        GoNextItem();

    else if (CNCurses::key_pressed == '\n')
    {
        if (current->type == CMenuItem::OPTION || current->type == CMenuItem::ITEM)
        {
            selected_item = current;
            selected = true;
        }
    }
}
void CMenu::GoNextItem()
{
    if (items.size() == 1)
    {
        cur_index = 0;
        current = *(items.begin());
        return;
    }

    if (items.size() == 0)
        return;

    if (cur_index != items.size() - 1)
    {
        cur_index++;
        current = items[cur_index];
    }
    if (!current)
        GoNextItem();
}
void CMenu::GoPrevItem()
{
    if (items.size() == 1)
    {
        cur_index = 0;
        current = items.front();
        return;
    }

    if (items.size() == 0)
        return;

    if (cur_index != 0)
    {
        cur_index--;
        current = items[cur_index];
    }
    if (!current)
        GoPrevItem();
}
bool CMenu::WillExit() const
{
    if (selected && selected_item)
    {
        return true;
    }
    return false;
}

void CMenu::RemoveByID(unsigned int id)
{
    std::vector<CMenuItem *>::iterator it = items.begin();

    while (it != items.end())
    {
        if ((*it)->id == id)
        {
            if (current == *it)
            {
                GoNextItem();
                cur_index--;
            }
            delete *it;
            *it = NULL;
            items.erase(it);
            return;
        }
        else
            it++;
    }
}

std::string CMenu::CurrentLabel()
{
    if (!current)
        GoNextItem();
    return current->label;
}
int CMenu::CurrentID()
{
    return current->id;
}
void CMenu::reset()
{
    selected_item = NULL;
    selected = false;
}