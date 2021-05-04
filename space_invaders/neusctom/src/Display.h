#ifndef PROJEKT_DISPLAY_H
#define PROJEKT_DISPLAY_H

#include <pwd.h>
#include <ctime>
#include <vector>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include "Bonus.h"
#include "Laser.h"
#include "Enemy.h"
#include "Player.h"

using namespace std;

class Display {
public:
    Display();

    ~Display();

    void printLasers(vector<Laser> &playerLaser, vector<Laser> &enemyLaser)const ;

    void printPlayer(Player &player)const ;

    void printEnemyes(vector<Enemy> enemyVector)const ;

    void menu()const ;

    void help()const ;

    void score();

    int x;

    int y;

    void winMessage( int score);

    void loseMessage(int score);

    void status(Player player,double d, double d1)const;

    void writeBest(int best);

    int getBest();

    string getFile();

    void printBonus(vector<Bonus> bonusVector)const;

    void legend()const;
};

#endif