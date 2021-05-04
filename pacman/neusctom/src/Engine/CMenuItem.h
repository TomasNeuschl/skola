#pragma once

#include <Engine/CWindow.h>

#include <string>

class CMenuItem
{
  public:
    /// Enumeration of posible menu item types.
    enum ItemType
    {
        ITEM,
        OPTION
    };

    /// Constructor that creates menu item with
    /// user-defined `id` number and label.
    ///
    CMenuItem(std::string label, int id);

    CMenuItem(){};
    virtual ~CMenuItem();

    /// Draws item on window `wind` at `x`, `y`
    /// with `width`.
    ///
    /// if this is current item, `highlight` is true.
    ///
    virtual void draw(CWindow *wind, int x, int y,
                      int width, bool highlight = false);

    /// Type of menu item.
    ItemType type;

    /// Text that will be shown on screen.
    std::string label;

    /// ID to identify this item.
    unsigned int id;
};