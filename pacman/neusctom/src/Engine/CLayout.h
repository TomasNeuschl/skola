#pragma once

#include <Engine/CWindow.h>

/// Main Layout for things on screen.
class CLayout
{
  public:
    CLayout(int width, int height);
    ~CLayout();
    virtual void window_init();
    virtual void window_exit();
    virtual void draw();

    /// Layout's main window.
    CWindow *main_wind;

    int screen_width;
    int screen_height;
    int needed_w;
    int needed_h;
};