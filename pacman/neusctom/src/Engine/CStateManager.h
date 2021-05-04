#pragma once

#include <Engine/CState.h>

class CStateManager
{
private:
  CState *current_state;

public:
  CStateManager();

  ///changes to new state
  ///
  static void change(CState *new_state);

  ///ends game ane cleans state
  ///
  static void quit();

  ///main game loop
  ///
  void run(CState *state);
  virtual ~CStateManager();
};

class CStateManagerChangeExeption
{
public:
  CStateManagerChangeExeption(CState *_new_state)
  {
    new_state = _new_state;
  }

  CState *new_state;
};

class CStateManagerQuitExeption
{
public:
  CStateManagerQuitExeption()
  {
    
  }
};