#pragma once
#include <vector>
#include "Laser.h"

using namespace std;

class Character {
public:
    Character();

    virtual ~Character();

    Character(int x, int y, int health);

    virtual void shoot(vector<Laser>& playerLasers,int startX, int startY){};

    int getx()const;

    int gety()const;

    void sety(int y);

    void setx(int x);

    int getHealth()const;

    void setHealth(int h);

protected:
    int x;
    int y;
    int health;
};