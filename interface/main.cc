#include "raylib.h"
#include "interface.h"
#include <cstdio>

InterfaceState state = INTERFACE_STATE_MAIN;
ModeState mode = MODE_NULL;
InterfaceBase* interfaces[INTERFACE_STATE_TOT];

int main()
{
    interfaces[INTERFACE_STATE_MAIN] = new InterfaceMain();
    interfaces[INTERFACE_STATE_MODE_SWITCH] = new InterfaceModeSwitch();
    interfaces[INTERFACE_STATE_MUSIC_SWITCH] = new InterfaceMusicSwitch();
    InterfaceBase* g = interfaces[state];

    InitWindow(g->screenWidth, g->screenHeight, "sample game");
#if DEBUG
    printf("[debug] init window successful!\n");
#endif
    g->init();

    SetTargetFPS(60);

    //Main game loop
    //Detect window close button or ESC key
    while (!WindowShouldClose()) 
    {
        /* Switch Interface */
        g = interfaces[state];

        /* Update */
        g->update();

        /* Draw */
        BeginDrawing();
        g->draw();
        EndDrawing();
    }

    //Close window and OpenGL context
    CloseWindow();

}