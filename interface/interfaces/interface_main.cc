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
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("This is main page", 0, 0, 50, BLACK);
    DrawRectangleRec(bt_start.bound, GREEN);
    DrawText("START", bt_start.bound.x, bt_start.bound.y, 20, BLACK);
    DrawRectangleRec(bt_quit.bound, SKYBLUE);
    EndDrawing();
}

void InterfaceMain::update()
{
    if (bt_start.isClicked())
        state = INTERFACE_STATE_MUSIC_SWITCH;
    else if (bt_quit.isClicked())
        state = INTERFACE_STATE_NULL;
}

InterfaceState InterfaceMain::end() { return state; }

bool InterfaceMain::is_end() { return state != origin_state; }