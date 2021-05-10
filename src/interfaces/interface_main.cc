#include "interface.h"
#include <cstdio>

extern InterfaceState state;
extern ModeState mode;

/* MAIN */

InterfaceMain::InterfaceMain() {}

void InterfaceMain::init()
{
    background = LoadTexture("../resources/bg_purple.png");
}

void InterfaceMain::draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);
    DrawText("KEY DANCE", 450, 100, 120, WHITE);
    if (((int)(GetTime() * 1.)) % 2 == 1)
        DrawText("Press Enter to Start", 420, 600, 70, WHITE);
    EndDrawing();
}

void InterfaceMain::update()
{
    if (IsKeyReleased(KEY_ENTER))
        state = INTERFACE_STATE_MUSIC_SWITCH;
}

InterfaceState InterfaceMain::end() { return state; }

bool InterfaceMain::is_end() { return state != origin_state; }