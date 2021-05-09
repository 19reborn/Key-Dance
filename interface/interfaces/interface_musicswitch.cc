#include "interface.h"
#include <cstdio>

extern InterfaceState state;
extern ModeState mode;

/* MUSIC SWITCH */

InterfaceMusicSwitch::InterfaceMusicSwitch() {}

void InterfaceMusicSwitch::init() {}

void InterfaceMusicSwitch::draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Choose your music!", 0, 0, 50, BLACK);
    EndDrawing();
}

void InterfaceMusicSwitch::update() {}

InterfaceState InterfaceMusicSwitch::end() { return state; }

bool InterfaceMusicSwitch::is_end() { return state != origin_state; }