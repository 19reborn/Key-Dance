#include "raylib.h"
#include "interface.h"
#include "music.hh"
#include "render.h"
#include <cstdio>
#define DEBUG

InterfaceState state = INTERFACE_STATE_MUSIC_SWITCH;
ModeState mode = MODE_PLAY;
InterfaceBase* interfaces[INTERFACE_STATE_TOT];

int main()
{
    /* Register interfaces */
    interfaces[INTERFACE_STATE_MAIN] = new InterfaceMain();
    interfaces[INTERFACE_STATE_MODE_SWITCH] = new InterfaceModeSwitch();
    interfaces[INTERFACE_STATE_MUSIC_SWITCH] = new InterfaceMusic();
    interfaces[INTERFACE_STATE_PLAY] = new InterfacePlay();
    InterfaceBase* g = interfaces[state];

    InitWindow(g->screenWidth, g->screenHeight, "game");
#ifdef DEBUG
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

        if(g->is_end()){
            #ifdef DEBUG
            printf("[debug] switching to interface %d\n", state);
            #endif
            state=g->end();
        }
        else {
            /* Draw */
            g->draw();
        }
    }
    //Close window and OpenGL context
    CloseWindow();
}