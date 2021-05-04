//#pragma once
#include "Game.h"


Game::Game(){
    this->quit=false;
    this->timeStart=clock();

}

Game::~Game()=default;

void Game::start(Display &display)      ///this function handles whole game
{
    win=false;
    quit=false;
    player.setHealth(100);
    EnemyFlock flock(display.x);        ///ensures that the enemies are spawned across whole width of play area

    addEnemyes(flock, display.x);       ///spawns enemies
    player.sety(display.y-1);           ///sets boundaries
    player.setmax(display.x-2);

    while (!quit) {                     ///game loop
        direction = getch ();
        switch (direction) {            ///handling of input
            case KEY_RIGHT:
                player.move(1);
                break;
            case KEY_LEFT:
                player.move(-1);
                break;
            case (int) ' ':
                if(player.checkl()){    ///if the bonus lasers are active spawns 2 lasers
                    player.shoot(playerLaser, player.getx() - 1, player.gety());
                    player.shoot(playerLaser, player.getx() + 1, player.gety());
                }else{
                    player.shoot(playerLaser, player.getx(), player.gety());
                }
                break;
            case (int) 'q':
                quit = true;
                win = false;
                break;
            default:break;
        }
        erase ();
        if(!quit){
            quit = checkPlayer(player);   ///check if player is alive
        }
        moveLasers(display.y);
        display.printLasers(playerLaser, enemyLaser);
        movebonus(display.y);
        checkBonus(player, display);     ///check if player have collected bonus
        display.printBonus(bonusVector);
        if(checkEnemy(flock.enemies)){  ///check collisions between lasers and enemies
            if(player.checkd()){        ///checks if double score bonus is active
                player.scores(100);
            }else{
                player.scores(50);
            }
            if(flock.enemies.empty()){
                quit = true;
                win = true;
            }
        }
        flock.move();
        display.printEnemyes(flock.enemies);
        display.printPlayer(player);
        display.printBonus(bonusVector);
        enemyShoot(flock.enemies);
        if(checkHeight(player, flock)){
            quit=true;
            win=false;
        }
    }
    if(display.getBest() < player.getScore()){    ///updating the best score
        display.writeBest(player.getScore());
    }
    if(win)display.winMessage(player.getScore());
    else display.loseMessage(player.getScore());
    bonusVector.clear();    ///cleaning of vectors for next game
    enemyLaser.clear();
    playerLaser.clear();

}

void Game::addEnemyes(EnemyFlock & flock, const int width)  ///function spawns enemyes cros whole width of playarea
{
    for (int enemyY = 1; enemyY < 3; enemyY++) {
        for (int enemyX = 0; enemyX < width - 5; enemyX += 5)
        {
            flock.enemies.emplace_back(Enemy(enemyX, enemyY));
        }
    }
}

void Game::enemyShoot(vector<Enemy>& enemies)   ///pick random enemy and shoot laser
{
    if(!enemies.empty()){
        clock_t timeTmp;
        double diff = 0;

        timeTmp = clock();
        diff = (double)( timeTmp - timeStart);
        diff = diff / CLOCKS_PER_SEC;
        if (diff>= (double) 0.15){               ///shoot laser every 0.15 seconds
            timeStart = timeTmp;
            unsigned long randEnemy = rand() % enemies.size();
            if(enemies[randEnemy].isAlive()){
                enemies[randEnemy].shoot(enemyLaser, enemies[randEnemy].getx() + 1, enemies[randEnemy].gety());
            }
        }
    }
}

void Game::moveLasers(const int max)  ///function for moving lasers and checking collisions between them
{
    for (auto laser = playerLaser.begin(); laser != playerLaser.end(); laser++) {
        laser -> move(-1);
        if(checkLasers(*laser, enemyLaser)){ ///checks for laser colisions
            playerLaser.erase(laser);
        }
        if(laser->getx() == 0){
            playerLaser.erase(laser);       ///erase laser if it reached the border
        }
        if(laser == playerLaser.end())break;
    }

    for (auto laser = enemyLaser.begin(); laser != enemyLaser.end(); laser++) {
        laser -> move(1);
        if(laser -> getx() == max){
            enemyLaser.erase(laser);        ///erase laser if it reached the border
        }
        if(laser == enemyLaser.end())break;
    }
}

void Game::movebonus(const int max)        ///function moves the bonus down
	{
    for (auto bonus = bonusVector.begin(); bonus != bonusVector.end(); bonus++) {
        bonus -> move();
        if(bonus -> getY() == max){             ///erase bonus if it reachd the border
            bonusVector.erase(bonus);
        }
        if(bonus == bonusVector.end())break;
    }
}

bool Game::checkPlayer(Player &player)     ///check for player-laser colisions
{
    for(auto & value: enemyLaser) {
        if(player.gety() == value.gety()){
            if((player.getx() - 1 <= value.getx()) && (player.getx() + 1 >= value.getx())){   ///check the whole width of player body
                player.setHealth(player.getHealth() - value.getDamage());
                value.setDamage(0);
                return player.getHealth() <= 0;
            }
        }
    }
    return false;
}

bool Game::checkEnemy(vector<Enemy> & enemyVector)     ///check for enemy-laser colisions
{
    for (auto laser = playerLaser.begin(); laser != playerLaser.end(); laser++) {
        for (auto enemy = enemyVector.begin(); enemy != enemyVector.end(); enemy++) {
            if(enemy -> gety() == laser -> gety()){
                if((enemy -> getx() <= laser -> getx()) && (enemy -> getx() + 4 >= laser -> getx())){ ///check the whole width of enemy ship
                    enemy -> setHealth(enemy -> getHealth() - laser -> getDamage());
                    playerLaser.erase(laser);             ///erase laser after colison
                    if(enemy -> getHealth() <= 0){
                        enemyVector.erase(enemy);
                        if(rand() % 10 == 0){           ///after killing an enemy there is 10% chance of bonus spawning
                            spawnBonus(enemy -> getx(), enemy -> gety());
                        }
                        return true;
                    }
                    return false;
                }
            }
        }
    }
    return false;
}

bool Game::checkLasers(Laser &laser, vector<Laser> &lasers)    ///check for laser-laser colisons
{
    for (auto enemy = lasers.begin(); enemy != lasers.end(); enemy++) {
        if((enemy -> getx() == laser.getx()) && (enemy -> gety() == laser.gety())){
            lasers.erase(enemy);
            return true;
        }
    }
    return false;
}

bool Game::checkHeight(Player &player, EnemyFlock& flock) const    ///check if enemies descended too low
{
    for(auto & value: flock.enemies) {
        if(player.gety() == value.gety()){
            return true;
        }
    }
    return false;
}

void Game::spawnBonus(int x, int y) {
    bonusVector.emplace_back(Bonus(x, y));
}

void Game::checkBonus(Player & player,Display & display)   ///checks if player have collected bonus
{
    for(auto & value: bonusVector) {
        if(player.gety() == value.getY()){    ///if bonus is collected, the start time is saved
            if((player.getx() <= value.getX()) && (player.getx() + 3 >= value.getX())){
                if(value.getType() == 0){
                    player.nowl();
                }
                if(value.getType() == 1){
                    player.setHealth(100);
                }
                if(value.getType() == 2){
                    player.nowd();
                }
            }
        }
    }
    clock_t timeTmp;
    double diffd = 0, diffl = 0;
    timeTmp = clock();
    diffd = (double)( timeTmp - player.getdClock());
    diffd = diffd / CLOCKS_PER_SEC;
    diffl = (double)( timeTmp - player.getlClock());
    diffl = diffl / CLOCKS_PER_SEC;
    if(diffl >= 5){       ///check if bonus is supposed to be active
        player.switchl();
    }
    if(diffd >= 5){       ///chceck if bonus is supposed to be active
        player.switchd();
    }
    display.status(player, diffd, diffl);
}