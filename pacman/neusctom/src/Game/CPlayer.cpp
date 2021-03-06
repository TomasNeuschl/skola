#include <Game/CPlayer.h>

CPlayer::CPlayer(int x, int y) : CCharacter(x, y), next_dir(CPlayer::RIGHT)
{
    coords.first = x;
    coords.second = y;
    next_coords = coords;
}
CPlayer::CPlayer(std::pair<int, int> coords) : CCharacter(coords), next_dir(CPlayer::RIGHT)
{
}
CPlayer::~CPlayer()
{
}
void CPlayer::move(Direction dir)
{
    next_dir = dir;
}
bool CPlayer::is_alive() const
{
    return alive;
}
void CPlayer::update(CBoard *board)
{
    switch (next_dir)
    {
    case CPlayer::LEFT:
        next_coords.first--;
        break;
    case CPlayer::RIGHT:
        next_coords.first++;
        break;
    case CPlayer::UP:
        next_coords.second--;
        break;
    case CPlayer::DOWN:
        next_coords.second++;
        break;
    }
    if (!board->is_wall(next_coords.first, next_coords.second))
    {
        coords = next_coords;
        cur_dir = next_dir;

        return;
    }

    std::pair<int, int> tmp_coords(coords);
    if (next_dir != cur_dir)
    {
        switch (cur_dir)
        {
        case CPlayer::LEFT:
            tmp_coords.first--;
            break;
        case CPlayer::RIGHT:
            tmp_coords.first++;
            break;
        case CPlayer::UP:
            tmp_coords.second--;
            break;
        case CPlayer::DOWN:
            tmp_coords.second++;
            break;
        }
        if (!board->is_wall(tmp_coords.first, tmp_coords.second))
        {
            coords = tmp_coords;
            next_coords = coords;
            return;
        }
    }

    next_coords = coords;
}
void CPlayer::draw(CWindow *window)
{
    switch (cur_dir)
    {
    case CPlayer::LEFT:
        window->print_char((int)'>', coords.first, coords.second);
        break;
    case CPlayer::RIGHT:
        window->print_char((int)'<', coords.first, coords.second);
        break;
    case CPlayer::UP:
        window->print_char((int)'v', coords.first, coords.second);
        break;
    case CPlayer::DOWN:
        window->print_char((int)'^', coords.first, coords.second);
        break;
    }
}
