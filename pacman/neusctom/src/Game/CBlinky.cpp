#include <Game/CBlinky.h>

#include <stdlib.h>
#include <set>
#include <algorithm>
#include <utility>

CBlinky::CBlinky(int x, int y) : CGhost(x, y)
{
}
CBlinky::~CBlinky()
{
}
void CBlinky::draw(CWindow *window)
{
    window->print((int)'B', coords.first, coords.second, COLOR_PAIR(PAIR_RED_BLACK));
}
void CBlinky::update(CBoard *board, CPlayer *player)
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
            targetx = 0;
            targety = 0;
        }
        else
        {
            targetx = player->getX();
            targety = player->getY();
        }

        if (abs(coords.first - targetx) > abs(coords.second - targety))
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
