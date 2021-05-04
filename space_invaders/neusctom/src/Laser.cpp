#include "Laser.h"

Laser::Laser(int x, int y, int damage)
{
    this -> x = x;
    this -> y = y;
    this -> damage = damage;
    timeStart = clock ();
}

int Laser::getx() const
{
    return x;
}

int Laser::gety() const
{
    return y;
}

void Laser::sety(int y)
{
    this -> y = y;
}

void Laser::move(int step)
{
    clock_t timeTmp;
    double diff = 0;

    timeTmp = clock();
    diff = (double)( timeTmp - timeStart);
    diff = diff / CLOCKS_PER_SEC;
    if (diff >= (double) 0.05)
    {
        timeStart = timeTmp;
        sety(gety() + step);
    }
}

int Laser::getDamage() const
{
    return this -> damage;
}

void Laser::setDamage(int d)
{
    this -> damage = d;
}