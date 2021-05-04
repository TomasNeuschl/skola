#include "Display.h"

Display::Display()
{
    initscr ();
    getmaxyx(stdscr, y, x);
    keypad (stdscr, TRUE);
    curs_set (0);
    noecho ();
    nodelay(stdscr,TRUE);
}

Display::~Display()
{
    endwin();
}


void Display::printLasers(vector<Laser> & playerLaser, vector<Laser> & enemyLaser)const
{
    for(auto & value: playerLaser) {
        mvprintw(value.gety(), value.getx(), "!");
    };
    for(auto & value: enemyLaser) {
        mvprintw(value.gety(), value.getx(), "*");
    };
}

void Display::printPlayer(Player &player)const
{
    mvprintw (player.gety() - 1, player.getx() - 1, "/^\\");
    mvprintw (player.gety(), player.getx() - 1, "###");

}

void Display::printEnemyes(vector<Enemy> enemyVector) const
{
    for(auto & value: enemyVector) {
        if(value.isAlive()){
            mvprintw(value.gety(), value.getx(), "\\^^/");
        }
    };
}

void Display::menu() const
{
    mvprintw (10, 10, "**************************************************");
    mvprintw (11, 10, "*************     SPACE INVADERS     *************");
    mvprintw (12, 10, "**************************************************");
    mvprintw (13, 10, "****        press space to start game         ****");
    mvprintw (14, 10, "****        press 'l' to print legend         ****");
    mvprintw (15, 10, "****         press 's' to print score         ****");
    mvprintw (16, 10, "****         press 'h' to print help          ****");
    mvprintw (17, 10, "****           press 'q' to quit              ****");
    mvprintw (18, 10, "****                                          ****");
    mvprintw (19, 10, "**************************************************");
}

void Display::help() const
{
    mvprintw (10, 10, "**************************************************");
    mvprintw (11, 10, "*************       GAME  HELP       *************");
    mvprintw (12, 10, "**************************************************");
    mvprintw (13, 10, "****        \"right arrow\"->move right         ****");
    mvprintw (14, 10, "****         \"left arrow\"->move left          ****");
    mvprintw (15, 10, "****           \"spacebar\"->shoot              ****");
    mvprintw (16, 10, "****                  \"q\"->quit               ****");
    mvprintw (17, 10, "****      press space to go back to menu      ****");
    mvprintw (18, 10, "**************************************************");
    while ((getch ()) != (int)' ');
    menu();
}

void Display::score()
{
    int c;

    mvprintw (10, 10, "**************************************************");
    mvprintw (11, 10, "*************       BEST SCORE       *************");
    mvprintw (12, 10, "**************************************************");
    mvprintw (13, 10, "****                                          ****");
    mvprintw (14, 10, "****                                          ****");
    mvprintw (15, 10, "****                 >%d<               ",getBest());
    mvprintw (16, 10, "****                                          ****");
    mvprintw (17, 10, "****      press space to go back to menu      ****");
    mvprintw (18, 10, "**************************************************");
    while (c != (int)' '){
        c = getch();
        if(c == 'r'){
            writeBest(0);
            mvprintw (15, 10, "****                 >%d<               ", getBest());

        }
    }
    menu();
}

void Display::winMessage(const int score)
{
    mvprintw (10, 10, "**************************************************");
    mvprintw (11, 10, "*************       YOU WON!!!       *************");
    mvprintw (12, 10, "**************************************************");
    mvprintw (13, 10, "****               Your score:                ****");
    mvprintw (14, 10, "                       %d",score);
    mvprintw (15, 10, "****              Best score yet:             ****");
    mvprintw (16, 10, "                       %d",getBest());
    mvprintw (17, 10, "****             press 'q' to quit            ****");
    mvprintw (18, 10, "**************************************************");
    while ((getch ()) != (int)'q');
    clear();
    menu();
}

void Display::loseMessage(const int score)
{
    mvprintw (10, 10, "**************************************************");
    mvprintw (11, 10, "*************      YOU  LOSE!!!      *************");
    mvprintw (12, 10, "**************************************************");
    mvprintw (13, 10, "****               Your score:                ****");
    mvprintw (14, 10, "                       %d",score);
    mvprintw (15, 10, "****              Best score yet:             ****");
    mvprintw (16, 10, "                       %d",getBest());
    mvprintw (17, 10, "****                                          ****");
    mvprintw (18, 10, "**************************************************");
    while ((getch ()) != (int)'q');
    clear();
    menu();
}

void Display::status(Player player,double d, double d1) const
{
    mvprintw (0, 0, "Score:%d || Live:%d\%", player.getScore(), player.getHealth());
    if(player.checkd()){
        mvprintw (0, 23, "Double score: %f",5 - d);
    }else{
        mvprintw (0, 23, "Double score: Disabled");
    }
    if(player.checkl()){
        mvprintw (0, 47, "Double lasers: %f",5 - d1);
    }else{
        mvprintw (0, 47, "Double lasers: Disabled");
    }
}

string Display::getFile()
{
    const char *homedir;

    if ((homedir = getenv("HOME")) == NULL)
        homedir = getpwuid(getuid()) -> pw_dir;

    string home = string(homedir) + "/.md.neusctom\0";
    return home;
}
int Display::getBest()
{
    ifstream fp (getFile().c_str());
    int best = 0;
    string content;
    if(fp.is_open() && fp.good())
    {
        getline(fp, content);
        best = (int)strtol(content.c_str(), NULL, 10);
        fp.close();
    }
    return best;
}
void Display::writeBest(int best)
{
    ofstream fp (getFile().c_str());
    if(fp.is_open())
    {
        fp << best;
        fp.close();
    }
}

void Display::printBonus(vector<Bonus> bonusVector) const
{
    for(auto & value: bonusVector) {
        if(value.getType() == 0){
            mvprintw(value.getY(), value.getX(), "L");
        }
        if(value.getType() == 1){
            mvprintw(value.getY(), value.getX(), "H");
        }
        if(value.getType() == 2){
            mvprintw(value.getY(), value.getX(), "D");
        }
    };
}

void Display::legend()const
{
    mvprintw (10, 10, "**************************************************");
    mvprintw (11, 10, "*************         LEGEND         *************");
    mvprintw (12, 10, "**************************************************");
    mvprintw (13, 10, "****                                          ****");
    mvprintw (14, 10, "****             L -> double lasers           ****");
    mvprintw (15, 10, "****             H -> full health             ****");
    mvprintw (16, 10, "****             D -> double score            ****");
    mvprintw (17, 10, "****      press space to go back to menu      ****");
    mvprintw (18, 10, "**************************************************");
    while ((getch ()) != (int)' ');
    menu();
}
