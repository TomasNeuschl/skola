#pragma once

#include <Engine/CMenuItem.h>
#include <Engine/CWindow.h>

#include <string>

/// Menu item that also has a back-light, if is selected.
class CMenuItemOption : public CMenuItem
{
  public:
    CMenuItemOption(std::string label, int id,
                    unsigned int &asigned_value);
    virtual ~CMenuItemOption();

    /// Draws item on window `wind` at `x`, `y`
    /// with `width`.
    ///
    /// If this is current item, `highlight` is true.
    ///
    virtual void draw(CWindow *wind, int x, int y,
                      int width, bool highlight = false);

    /// Reference to asigned value.
    unsigned int &asigned_value;
};