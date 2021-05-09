#include "raylib.h"
#include "interface.h"
#include <cstdio>

InterfaceState state = INTERFACE_STATE_TEST;
InterfaceBase* interfaces[INTERFACE_STATE_TOT];

int main()
{
    interfaces[INTERFACE_STATE_TEST] = new InterfaceTest();
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
        /* Update */
        g->update();

        /* Draw */
        BeginDrawing();
        ClearBackground(RAYWHITE);
        g->draw();
        EndDrawing();
    }

    //Close window and OpenGL context
    CloseWindow();

}