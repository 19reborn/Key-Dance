#include "interface.h"
#include <cstdio>

extern InterfaceState state;
extern ModeState mode;

/* TEST */

InterfaceTest::InterfaceTest()
{
    this->pos = {screenWidth/2.0, 0.0};
}

void InterfaceTest::init() {}

void InterfaceTest::update()
{
    this->pos.y += 2;
}

void InterfaceTest::draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawCircleV(this->pos, 50, MAROON);
    EndDrawing();
}

InterfaceState InterfaceTest::end() { return state; }

bool InterfaceTest::is_end() { return state != origin_state; }