/*******************************************************************************************
*
*   raylib [core] example - 3d camera first person
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <list>
using namespace std;

// MUSIC_STATUS m;

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1600;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "Select your song");
    // Load Textures
    Texture2D texture_test = LoadTexture("resources/goodtek.png");

    SetTargetFPS(60);                           // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())                // Detect window close button or ESC key
    {
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(GRAY);
            DrawTextureEx(texture_test, { 0, 0 }, 0.0f, screenWidth / (float)texture_test.width, WHITE);
            // 左上
            DrawRectangle(0, 20, 160, 100, Fade(BLACK, 0.5f));
            DrawRectangle(0, 150, 600, 200, Fade(BLACK, 0.5f));
            DrawTriangle({0, 0}, {0, 1200}, {400, 0}, Fade(BLACK, 0.2f)); 
            // 右上
            DrawRectangle(1440, 20, 160, 100, Fade(BLACK, 0.5f));
            // 左下
            DrawRectangle(0, 600, 700, 150, Fade(BLACK, 0.5f));
            DrawRectangle(0, 780, 400, 100, Fade(BLACK, 0.5f));
            // 右下
            DrawRectangle(1400, 760, 200, 120, Fade(BLACK, 0.5f));
            DrawTriangle({1600, 400}, {1440, 900}, {1600, 900}, Fade(BLACK, 0.2f));

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture_test);

    CloseWindow();        // Close window and OpenGL context

    return 0;
}