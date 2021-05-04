#include <Game/CPinky.h>

#include <stdlib.h>
#include <set>
#include <algorithm>
#include <utility>

CPinky::CPinky(int x, int y) : CGhost(x, y)
{
}
CPinky::~CPinky()
{
}
void CPinky::draw(CWindow *window)
{
    window->print((int)'P', coords.first, coords.second, COLOR_PAIR(PAIR_PINK_BLACK));
}
void CPinky::update(CBoard *board, CPlayer *player)
{
    Direction next_dir;
    std::pair<bool, std::set<CGhost::Direction>> dirs = on_crossroad(board);
    int targetx;
    int targety;
    if (dirs.first)
    {
        auto it(dirs.second.begin());
        if (is_frightened())
        {
            targetx = board->get_width();
            targety = board->get_height();
        }
        else
        {
           targetx = player->getX();
           targety = player->getY();
        }
        int offx = 0;
        int offy = 0;
        switch (player->cur_dir)
        {
        case CPlayer::LEFT:
            offx = -3;
            break;
        case CPlayer::RIGHT:
            offx = 3;
            break;
        case CPlayer::UP:
            offy = 3;
            break;
        case CPlayer::DOWN:
            offy = -3;
            break;
        }
        if (abs(coords.first - targetx + offx) > abs(coords.second - targety + offy))
        {
            if (coords.first > targetx)
                it = dirs.second.find(CGhost::LEFT);
            if (coords.first < targetx)
                it = dirs.second.find(CGhost::RIGHT);

            if (it == dirs.second.end())
            {
                if (coords.second > targety)
                    it = dirs.second.find(CGhost::UP);
                if (coords.second < targety)
                    it = dirs.second.find(CGhost::DOWN);
            }
        }
        else
        {
            if (coords.second > targety)
                it = dirs.second.find(CGhost::UP);
            if (coords.second < targety)
                it = dirs.second.find(CGhost::DOWN);

            if (it == dirs.second.end())
            {
                if (coords.first > targetx)
                    it = dirs.second.find(CGhost::LEFT);
                if (coords.first < targetx)
                    it = dirs.second.find(CGhost::RIGHT);
            }
        }

        if (it == dirs.second.end())
        {
            it = dirs.second.begin();
            advance(it, rand() % dirs.second.size());
        }

        next_dir = *it;
    }
    else
        next_dir = *(dirs.second.begin());

    switch (next_dir)
    {
    case CPlayer::LEFT:
        coords.first--;
        break;
    case CPlayer::RIGHT:
        coords.first++;
        break;
    case CPlayer::UP:
        coords.second--;
        break;
    case CPlayer::DOWN:
        coords.second++;
        break;
    }
    cur_dir = next_dir;
}
