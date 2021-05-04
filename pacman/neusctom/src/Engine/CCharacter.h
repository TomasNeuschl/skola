#pragma once
#include <Game/CBoard.h>

class CCharacter
{
public:
    /// Enumeriation of directions where character
    /// can go.
    enum Direction
    {
        LEFT,
        DOWN,
        UP,
        RIGHT
    };

    /// Constructs character, `x` `y` are starting
    /// coordinates.
    CCharacter(int x, int y);
    CCharacter(std::pair<int, int> coords);
    virtual ~CCharacter();
    int getX() const;
    int getY() const;

    /// Moves character to `x` `y` coordinates.
    void move_to(int x, int y);

    void kill();

    /// Draws character to `window`.
    virtual void draw(CWindow *window)=0;

    /// pair of coodinates where character is.
    std::pair<int, int> coords;
    std::pair<int, int> next_coords;
    bool alive;

    /// Direction where character is going.
    Direction cur_dir;
};