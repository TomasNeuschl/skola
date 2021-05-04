
#include "Bonus.h"

Bonus::Bonus(int x, int y)
{
    this -> x = x;
    this -> y = y;
    type = rand() % 3;
    timeStart = clock();
}

Bonus::~Bonus() {

}

int Bonus::getType() const
{
    return type;
}

int Bonus::getX() const
{
    return x;
}

int Bonus::getY() const
{
    return y;
}

void Bonus::setY(int y)
{
    this -> y = y;
}

void Bonus::move()
{
    clock_t timeTmp;
    double diff = 0;

    timeTmp = clock();
    diff = (double)(timeTmp - timeStart);
    diff = diff / CLOCKS_PER_SEC;
    if (diff >= (double) 0.2) {
        timeStart = timeTmp;
        setY(getY() + 1);
    }
}