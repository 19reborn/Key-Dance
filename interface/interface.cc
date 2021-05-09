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

/* MODE SWITCH */
InterfaceModeSwitch::InterfaceModeSwitch() :
bt_play(screenWidth/2. - screenWidth/10., screenHeight/3., screenWidth/5., screenHeight/5.),
bt_generate(screenWidth/2. - screenWidth/10., screenHeight/3.*2., screenWidth/5., screenHeight/5.)
{}

void InterfaceModeSwitch::init() {}

void InterfaceModeSwitch::draw()
{
    ClearBackground(RAYWHITE);
    DrawText("This is mode switch page", 0, 0, 50, BLACK);
    DrawRectangleRec(bt_play.bound, GREEN);
    DrawText("PLAY", bt_play.bound.x, bt_play.bound.y, 20, BLACK);
    DrawRectangleRec(bt_generate.bound, SKYBLUE);
    DrawText("GENERATE", bt_generate.bound.x, bt_generate.bound.y, 20, BLACK);
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

void InterfaceModeSwitch::end() {}

InterfaceMusicSwitch::InterfaceMusicSwitch() {}

void InterfaceMusicSwitch::init() {}

void InterfaceMusicSwitch::draw()
{
    ClearBackground(RAYWHITE);
    DrawText("Choose your music!", 0, 0, 50, BLACK);
}

void InterfaceMusicSwitch::update() {}

void InterfaceMusicSwitch::end() {}