#include <Game/CStateGame.h>
#include <Game/CStateMenu.h>
#include <Engine/CStateManager.h>
#include <Engine/CDialog.h>
#include <Game/CBoardUtils.h>

#include <vector>
#include <string>

CStateGame::CStateGame() : game(NULL), will_exit(false)
{
}
CStateGame::CStateGame(std::string map, int difficulty) : game(NULL), will_exit(false), will_go_to_menu(false), map(map), difficulty(difficulty)
{
}

CStateGame::~CStateGame()
{
}

void CStateGame::load()
{
    try
    {
        game = new CGame(map, difficulty);
        game->start(); // level to chose
                       // load scores
    }
    catch (BadFileExeption &e)
    {

        delete game;
        game = NULL;
        std::vector<std::string> v = {"There was a problem with loading the map. ",
                                      "Please select another one."};
        CDialog::show(v, "ERROR");
        will_go_to_menu = true;
    }
}
void CStateGame::unload()
{
    delete game;
    game = NULL;
}
void CStateGame::update()
{
    if (will_go_to_menu)
        CStateManager::change(new CStateMenu());

    if (will_exit)
        CStateManager::quit();

    game->handle_input();
    game->update();

    if (game->will_exit())
    {
        if (game->high_score >= game->points)
            game->save_high_score();

        will_exit = true;
    }
    if (game->will_go_to_menu())
    {
        if (game->high_score >= game->points)
            game->save_high_score();

        CStateManager::change(new CStateMenu());
    }
}
void CStateGame::draw()
{
    if (!will_exit)
        game->draw();
}
