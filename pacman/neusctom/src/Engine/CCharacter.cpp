#include <Engine/CCharacter.h>

CCharacter::CCharacter(int x, int y) : alive(true), cur_dir(CCharacter::RIGHT)
{
    coords.first = x;
    coords.second = y;
    next_coords = coords;
}
CCharacter::CCharacter(std::pair<int, int> coords) : coords(coords), next_coords(coords), alive(true), cur_dir(CCharacter::RIGHT)
{
}
CCharacter::~CCharacter()
{
}
int CCharacter::getX() const
{
    return coords.first;
}
int CCharacter::getY() const
{
    return coords.second;
}

void CCharacter::kill()
{
    alive = false;
}

void CCharacter::move_to(int x, int y)
{
    coords.first = x;
    coords.second = y;
}