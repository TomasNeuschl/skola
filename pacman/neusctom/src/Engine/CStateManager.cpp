#include <Engine/CStateManager.h>
#include <Engine/CNCurses.h>
#include <Engine/CTime.h>
#include <stdlib.h>

CStateManager::CStateManager() : current_state(NULL)
{
}

void CStateManager::change(CState *new_state)
{
    throw CStateManagerChangeExeption(new_state);
}

void CStateManager::quit()
{
    throw CStateManagerQuitExeption();
}

void CStateManager::run(CState *init_state)
{
    current_state = init_state;
    current_state->load();

    while (true)
    {
        try
        {
            CNCurses::key_pressed = CNCurses::get_input(0);
            current_state->update();

            if (current_state)
                current_state->draw();

            CTime::delay_ms(100);
        }
        catch (CStateManagerChangeExeption &e)
        {
            current_state->unload();
            delete current_state;
            current_state = e.new_state;
            current_state->load();
        }
        catch (CStateManagerQuitExeption &e)
        {
            current_state->unload();
            delete current_state;
            current_state = NULL;
            break;
        }
    }
}

CStateManager::~CStateManager()
{
    if (current_state)
        current_state->unload();
    delete current_state;
    current_state = NULL;
}