#pragma once

#include <Engine/CWindow.h>
#include <Engine/CMenuItem.h>
#include <Engine/CMenuItemOption.h>

#include <vector>
#include <string>

enum MenuIDs
{
  START_GAME,
  CHOOSE_LEVEL,
  OPTIONS,
  CREDITS,
  EXIT_GAME,
  END_GAME,
  HIGH_SCORES,
  BACK,
  RESUME,
  RESTART,
  MAIN_MENU
};

/// List of selectable options.
class CMenu
{
public:
  /// Constructor that creates menu at #x, #y
  ///
  CMenu(int x, int y, int width, int height);

  ///  Adds item to menu.
  void add(CMenuItem *item);

  ///  Adds blank item to menu.
  void add_blank();

  /// draws whole menu on #window.
  void draw(CWindow *window);

  /// Selects next in menu.
  void GoNextItem();

  /// Selects previous in menu.
  void GoPrevItem();

  /// Returns true if user selected an item that
  /// will quit menu.
  bool WillExit() const;

  /// Removes specific item with #id from menu.
  void RemoveByID(unsigned int id);

  /// Returns string - #label of current selected
  /// item in menu.
  std::string CurrentLabel();

  /// Handles input for menu, same as in
  /// global CInputManager
  void HandleInput();

  /// Returns #id of current selected item in menu.
  int CurrentID();

  /// Makes menu to be selectable again.
  void reset();

  virtual ~CMenu();

  /// std::vector container of all items in menu.
  std::vector<CMenuItem *> items;

  /// pointer to current item in menu.
  CMenuItem *current;

protected:
  /// Index of currently selected item.
  unsigned int cur_index;

  int x;
  int y;
  int width;
  int height;

  /// Is true if will exit from menu.
  bool will_exit;
  /// Is true if user selected an item.
  bool selected;

  /// Pointer to selected item.
  CMenuItem *selected_item;
};
