#include <iostream>
#ifndef PROJEKT_BONUS_H
#define PROJEKT_BONUS_H


class Bonus {
public:
    Bonus(int x, int y);

    ~Bonus();

    int getX()const;

    int getY()const;

    void setY(int y);

    int getType()const;

    void move();

private:
    clock_t timeStart;
    int type;
    int x;
    int y;
};


#endif
