#include "Enemy.h"

Enemy::Enemy(int x, int y):Character(x, y, 100)
{
    this -> live = true;
}

Enemy::~Enemy() {}

void Enemy::shoot(vector<Laser> &Lasers, int startX, int startY)
{
    int shotChance = rand() % 2;
    if (shotChance % 2 == 0)
    {
        Lasers.push_back(Laser(startX, startY, 35));
    }
}

bool Enemy::isAlive()
{
    return this -> live;
};
