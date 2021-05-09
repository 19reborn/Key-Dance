#include "interface.h"
#include <cstdio>

extern InterfaceState state;
extern ModeState mode;

/* MAIN */

InterfaceMain::InterfaceMain() : 
bt_start(screenWidth/2. - screenWidth/10., screenHeight/3., screenWidth/5., screenHeight/5.),
bt_quit(screenWidth/2. - screenWidth/10., screenHeight/3.*2., screenWidth/5., screenHeight/5.)
{}

void InterfaceMain::init() {}

void InterfaceMain::draw()
{
    ClearBackground(RAYWHITE);
    DrawText("This is main page", 0, 0, 50, BLACK);
    DrawRectangleRec(bt_start.bound, GREEN);
    DrawRectangleRec(bt_quit.bound, SKYBLUE);
}

void InterfaceMain::update()
{
    if (bt_start.isClicked())
        state = INTERFACE_STATE_MODE_SWITCH;
    else if (bt_quit.isClicked())
        state = INTERFACE_STATE_NULL;
}

void InterfaceMain::end() {}
