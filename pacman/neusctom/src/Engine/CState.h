#pragma once

///Abstract class for states that occur during game
///
class CState
{
  public:
    CState(){};
    ///function to draw menu or game
    ///

    virtual void draw() = 0;
    ///loads all resources needed for state
    ///
    virtual void load() = 0;
    ///destroy all state resources
    ///
    virtual void unload() = 0;
    ///calculate all changes that happened
    ///
    virtual void update() = 0;

    virtual ~CState(){};
};