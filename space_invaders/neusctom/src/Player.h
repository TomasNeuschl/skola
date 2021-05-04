#pragma once
#include <vector>
#include "Character.h"
#include <ncurses.h>

using namespace std;

class Player : public Character {
public:
    Player();

    ~Player();

    virtual void shoot(vector<Laser>& playerLasers,int startX, int startY);

    void move(int m);

    void setmax(int max);


    int getScore()const;

    void scores(int points);

    bool checkl()const ;

    bool checkd()const ;

    void switchl();

    void switchd();

    void nowl();

    void nowd();

    clock_t getlClock()const ;

    clock_t getdClock()const ;

private:
    int max;
    int score=0;
    bool l;
    bool d;
    clock_t lstart;
    clock_t dstart;
};