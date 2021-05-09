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
    ClearBackground(RAYWHITE);
    DrawCircleV(this->pos, 50, MAROON);
}

void InterfaceTest::end() {}