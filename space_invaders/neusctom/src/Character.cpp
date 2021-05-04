#include "Character.h"

Character::Character()
{
}

Character::Character(int x, int y, int health)
{
	this->x=x;
	this->y=y;
	this->health=health;
}


Character::~Character()
{
}

int Character::getx()const
{
	return this->x;
}

int Character::gety()const
{
	return this->y;
}

void Character::sety(int y)
{
	this->y=y;
}

void Character::setx(int x)
{
	this->x=x;
}

int Character::getHealth() const
{
	return this->health;
}

void Character::setHealth(int h)
{
	this->health=h;
}



