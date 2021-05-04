//
// Created by tomas on 5.6.18.
//

#include "EnemyFlock.h"
#include <ncurses.h>
EnemyFlock::EnemyFlock(int width)
{
    this -> width = width;
}

EnemyFlock::~EnemyFlock()
{
}

void EnemyFlock::move()
{
    clock_t timeTmp;
    double diff = 0;
    bool swap = false;

    timeTmp = clock();
    diff = (double)( timeTmp - timeStart);
    diff = diff / CLOCKS_PER_SEC;
    if (diff >= (double) 0.5) {
        timeStart = timeTmp;
        for(auto & value: enemies) {
            if(value.isAlive()) {
                value.setx(value.getx() + direction);
                if ((value.getx() > width - 5) || (value.getx() < 1))swap = true;
            }
        };
        if (swap){
            direction *= -1;
            for(auto & value: enemies) {
                value.setx(value.getx() + direction);
                value.sety(value.gety() + 1);
            };
        }
    }
}