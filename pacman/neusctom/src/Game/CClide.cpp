#include <Game/CClide.h>

#include <stdlib.h>
#include <set>
#include <algorithm>
#include <utility>
#include <math.h>

CClide::CClide(int x, int y) : CGhost(x, y)
{
}
CClide::~CClide()
{
}
void CClide::draw(CWindow *window)
{
    window->print((int)'C', coords.first, coords.second, COLOR_PAIR(PAIR_ORANGE_BLACK));
}
void CClide::update(CBoard *board, CPlayer *player)
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
            targetx = board->get_height();
            targety = 0;
        }
        else
        {
            targetx = player->getX();
            targety = player->getY();
        }
        int x = abs(coords.first - targetx);
        int y = abs(coords.second - targety);
        if (sqrt(x * x + y * y) < 5)
        {
            if (abs(coords.first) > abs(coords.second))
            {
                if (coords.first > 0)
                    it = dirs.second.find(CGhost::LEFT);
                if (coords.first < 0)
                    it = dirs.second.find(CGhost::RIGHT);

                if (it == dirs.second.end())
                {
                    if (coords.second > 0)
                        it = dirs.second.find(CGhost::UP);
                    if (coords.second < 0)
                        it = dirs.second.find(CGhost::DOWN);
                }
            }
            else
            {
                if (coords.second > 0)
                    it = dirs.second.find(CGhost::UP);
                if (coords.second < 0)
                    it = dirs.second.find(CGhost::DOWN);

                if (it == dirs.second.end())
                {
                    if (coords.first > 0)
                        it = dirs.second.find(CGhost::LEFT);
                    if (coords.first < 0)
                        it = dirs.second.find(CGhost::RIGHT);
                }
            }
        }
        else
        {

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
