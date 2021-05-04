#pragma once
#include <ctime>

struct Laser
{
public:
    Laser(int x, int y, int damage);

    int getx()const ;

    int gety()const ;

    void sety(int y);

    void move(int step);

    int getDamage()const;

    void setDamage(int d);

private:
    int x;
    int y;
    int damage;
    clock_t timeStart;
};