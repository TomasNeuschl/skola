//
// Created by tomas on 5.6.18.
//

#ifndef PROJEKT_ENEMYFLOCK_H
#define PROJEKT_ENEMYFLOCK_H

#include "Enemy.h"

class EnemyFlock {
public:

    EnemyFlock(int width);

    ~EnemyFlock();

    void move();

    vector<Enemy> enemies;

protected:
    int width;
    int direction=1;
    clock_t timeStart;
};


#endif
