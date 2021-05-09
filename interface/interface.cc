#include "interface.h"
#include <cstdio>

extern InterfaceState state;

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
    
}