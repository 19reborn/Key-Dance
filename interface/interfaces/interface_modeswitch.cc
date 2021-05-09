#include "interface.h"
#include <cstdio>

extern InterfaceState state;
extern ModeState mode;

/* MODE SWITCH */
InterfaceModeSwitch::InterfaceModeSwitch() :
bt_play(screenWidth/2. - screenWidth/10., screenHeight/3., screenWidth/5., screenHeight/5.),
bt_generate(screenWidth/2. - screenWidth/10., screenHeight/3.*2., screenWidth/5., screenHeight/5.)
{}

void InterfaceModeSwitch::init() {}

void InterfaceModeSwitch::draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("This is mode switch page", 0, 0, 50, BLACK);
    DrawRectangleRec(bt_play.bound, GREEN);
    DrawText("PLAY", bt_play.bound.x, bt_play.bound.y, 20, BLACK);
    DrawRectangleRec(bt_generate.bound, SKYBLUE);
    DrawText("GENERATE", bt_generate.bound.x, bt_generate.bound.y, 20, BLACK);
    EndDrawing();
}

void InterfaceModeSwitch::update()
{
    if (bt_play.isClicked()) {
        state = INTERFACE_STATE_MUSIC_SWITCH;
        mode = MODE_PLAY;
    }
    else {
        state = INTERFACE_STATE_MUSIC_SWITCH;
        mode = MODE_GENERATE;
    }
}

InterfaceState InterfaceModeSwitch::end() { return state; }

bool InterfaceModeSwitch::is_end() { return state != origin_state; }