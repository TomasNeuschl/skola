#include <vector>
#include <iostream>
#include <ncurses.h>
#include "Laser.h"
#include "Enemy.h"
#include "Bonus.h"
#include "Player.h"
#include "Display.h"
#include "EnemyFlock.h"

using namespace std;

class Game {
public:
    Game();

    ~Game();

    void start(Display &display);

private:

    void addEnemyes(EnemyFlock& enemies, int width);

    void enemyShoot(vector<Enemy>& enemies);

    void moveLasers(int max);

    bool checkPlayer(Player &player);

    bool checkEnemy(vector<Enemy> & enemyVector);

    bool checkLasers(Laser &laser, vector<Laser> &lasers);

    bool checkHeight(Player &player, EnemyFlock &flock)const;

    void spawnBonus(int x, int y);

    void movebonus(int max);

    void checkBonus(Player & player, Display & display);

    clock_t timeStart;

    bool quit;

    bool win;

    int direction;

    Player player;

    vector<Laser> playerLaser;

    vector<Laser> enemyLaser;

    vector<Bonus> bonusVector;
};
