#pragma once
#include <vector>
#include "Character.h"
#include <iostream>

using namespace std;


class Enemy : public Character{
public:
    Enemy(int x, int y);

    ~Enemy();

    bool isAlive();

    virtual void shoot(vector<Laser>& Lasers,int startX, int startY);

protected:
    bool live;
};

