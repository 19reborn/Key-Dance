#include "raylib.h"
#include "interface.h"
#include "music.hh"
#include "render.h"
#include "scoredisp.hh"
#include <cstdio>

InterfaceState state = INTERFACE_STATE_MAIN;
ModeState mode = MODE_GENERATE;
InterfaceBase* interfaces[INTERFACE_STATE_TOT];

int main()
{
    /* Register interfaces */
    interfaces[INTERFACE_STATE_MAIN] = new InterfaceMain();
    interfaces[INTERFACE_STATE_MUSIC_SWITCH] = new InterfaceMusic();
    interfaces[INTERFACE_STATE_PLAY] = new InterfacePlay();
    interfaces[INTERFACE_STATE_SUMMARY] = new InterfaceScoreDisp();
    InterfaceBase* g = interfaces[state];

    InitWindow(g->screenWidth, g->screenHeight, "game");
#ifdef DEBUG
    printf("[debug] init window successful!\n");
#endif
    g->init();

    SetTargetFPS(60);
    InitAudioDevice();
    //Main game loop
    //Detect window close button or ESC key
    while (!WindowShouldClose()) 
    {


        /* Update */
        g->update();
        if(g->is_end()){
            #ifdef DEBUG
            printf("[debug] switching to interface %d\n", state);
            #endif
            state=g->end();
            g = interfaces[state];
            g->init();
        }
        else {
            /* Draw */
            g->draw();
        }
    }
    //Close window and OpenGL context
    CloseWindow();
}