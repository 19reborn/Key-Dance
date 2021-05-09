#include "raylib.h"
#include "interface.h"
#include <cstdio>



InterfaceState state = INTERFACE_STATE_MAIN;
InterfaceBase* interfaces[INTERFACE_STATE_TOT];

int main()
{
    interfaces[0] = new InterfaceMain;
    g = interfaces[state];

    InitWindow(g->screenWidth, g->screenHeight, "sample game");
    g->init();

#if defined(PLATFORM_WEB)

    //emscripten_set_main_loop(UpdateDrawFrame, 60, 1);

#else

    SetTargetFPS(60);

    //Main game loop
    //Detect window close button or ESC key
    while (!WindowShouldClose()) 
    {
        g->update();
    }

#endif

    //Close window and OpenGL context
    CloseWindow();

}