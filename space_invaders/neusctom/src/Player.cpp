//#pragma once
#include "Player.h"

Player::Player():Character (1,0,100){
    this->l= false;
    this->d= false;

}

Player::~Player()
{
}

void Player::move(int m)
{
    if(m == -1 && x > 1) x --;
    if(m == 1 && x < max) x ++;
}

void Player::setmax(int max)
{
    this -> max = max;
}

void Player::shoot(vector<Laser> &playerLasers, int startX, int startY) {
    playerLasers.push_back(Laser(startX, startY, 50));
}

int Player::getScore() const
{
    return this -> score;
}

void Player::scores(int points)
{
    this -> score += points;
}

bool Player::checkl() const
{
    return this -> l;
}

bool Player::checkd() const
{
    return this -> d;
}

void Player::switchl()
{
        l = false;
}

void Player::switchd()
{
    d = false;
}
clock_t Player::getlClock() const
{
    return lstart;
}

clock_t Player::getdClock() const
{
    return dstart;
}

void Player::nowl()
{
    l = true;
    lstart = clock();
}

void Player::nowd()
{
    d = true;
    dstart = clock();
}
