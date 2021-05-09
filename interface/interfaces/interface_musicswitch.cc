#include "interface.h"
#include <cstdio>

extern InterfaceState state;
extern ModeState mode;

/* MUSIC SWITCH */

InterfaceMusicSwitch::InterfaceMusicSwitch() {}

void InterfaceMusicSwitch::init() {}

void InterfaceMusicSwitch::draw()
{
    ClearBackground(RAYWHITE);
    DrawText("Choose your music!", 0, 0, 50, BLACK);
}

void InterfaceMusicSwitch::update() {}

void InterfaceMusicSwitch::end() {}