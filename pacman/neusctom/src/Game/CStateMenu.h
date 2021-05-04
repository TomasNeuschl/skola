#pragma once

#include <Engine/CMenu.h>
#include <Engine/CState.h>
#include <Game/CMenuLayout.h>

class CStateMenu : public CState
{
  friend class CMenuLayout;

public:
  CStateMenu();
  virtual ~CStateMenu();
  void load();
  void unload();
  void update();
  void draw();

private:
  CMenu *menu;
  CMenu *levels;
  CMenu *options;
  bool menu_levels;
  bool menu_options;
  CMenuLayout *layout;
  unsigned int difficulty;

  void CreateMainMenu();
  void CreateLevelsMenu();
  void CreateOptionsMenu();
};