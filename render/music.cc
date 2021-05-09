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

// 测试用
string musicName = "Just Testing";
string musicAuthor = "Justie Testie";
int highscore = 9978617;
double accrate = 97.86;
string scoreAuthor = "Create!";

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1600;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "Select your song");
    // Load Textures
    Texture2D texture_test = LoadTexture("resources/goodtek.png");
    Texture2D texture_return_button = LoadTexture("resources/return.png");
    Texture2D texture_settings_button = LoadTexture("resources/settings.png");
    Font font_caption = LoadFontEx("resources/bb2180.ttf", 96, 0, 0);

    SetTargetFPS(60);                           // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())                // Detect window close button or ESC key
    {
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(GRAY);
            DrawTextureEx(texture_test, { 0, 0 }, 0.0f, screenWidth / (float)texture_test.width, WHITE);
            // 手动光栅化！
            // 左上
                // 遮罩
            DrawTriangle({0, 0}, {0, 1200}, {400, 0}, Fade(BLACK, 0.2f));
                // 返回
            DrawRectangle(0, 20, 120, 100, Fade(BLACK, 0.5f));
            DrawTriangle({120, 120}, {160, 20}, {120, 20}, Fade(BLACK, 0.5f));
            DrawTextureEx(texture_return_button, { 30, 40 }, 0.0f, 0.3f, WHITE);
                // 曲名信息
            DrawRectangle(0, 150, 500, 200, Fade(BLACK, 0.5f));
            DrawTriangle({500, 350}, {660, 150}, {500, 150}, Fade(BLACK, 0.5f));
            DrawTextEx(font_caption, TextFormat("| %s", musicName.c_str()), {10, 160}, 90, 0, WHITE);
            DrawTextEx(font_caption, TextFormat("%s", musicAuthor.c_str()), {30, 265}, 60, 0, WHITE);
            // 右上
                // 设置
            DrawRectangle(1480, 20, 160, 100, Fade(BLACK, 0.5f));
            DrawTriangle({1480, 120}, {1480, 20}, {1440, 20}, Fade(BLACK, 0.5f));
            DrawTextureEx(texture_settings_button, { 1500, 40 }, 0.0f, 0.3f, WHITE);
            // 左下
                // 最高分、ACC
            DrawRectangle(0, 600, 700, 150, Fade(BLACK, 0.5f));
            DrawTriangle({700, 750}, {790, 600}, {700, 600}, Fade(BLACK, 0.5f));
            if(highscore <= 5000000) {
                DrawTextEx(font_caption, TextFormat("D"), {50, 600}, 150, 0, GRAY);
            } else if(highscore <= 7000000) {
                DrawTextEx(font_caption, TextFormat("C"), {50, 600}, 150, 0, RED);
            } else if(highscore <= 8000000) {
                DrawTextEx(font_caption, TextFormat("B"), {50, 600}, 150, 0, YELLOW);
            } else if(highscore <= 9000000) {
                DrawTextEx(font_caption, TextFormat("A"), {50, 600}, 150, 0, ORANGE);
            } else if(highscore <= 9500000) {
                DrawTextEx(font_caption, TextFormat("S"), {50, 600}, 150, 0, PURPLE);
            } else if(highscore < 10000000) {
                DrawTextEx(font_caption, TextFormat("V"), {50, 600}, 150, 0, {233, 0, 233, 255});
            } else if(highscore == 10000000) {
                DrawTextEx(font_caption, TextFormat("P"), {50, 600}, 150, 0, PINK);
            }
            DrawTextEx(font_caption, TextFormat("%08d", highscore), {170, 630}, 90, 0, WHITE);
            DrawTextEx(font_caption, TextFormat("%.2f%%", accrate), {580, 670}, 40, 0, WHITE);
                // 所选谱面
            DrawRectangle(0, 780, 400, 100, Fade(BLACK, 0.5f));
            DrawTriangle({400, 880}, {460, 780}, {400, 780}, Fade(BLACK, 0.5f));
            DrawTextEx(font_caption, TextFormat("%s", scoreAuthor.c_str()), {40, 800}, 60, 0, WHITE);
            // 右下
                // 遮罩
            DrawTriangle({1600, 400}, {1440, 900}, {1600, 900}, Fade(BLACK, 0.2f));
                // 歌曲位置, 例: 2/57
            DrawRectangle(1400, 760, 200, 120, Fade(WHITE, 0.9f));
            DrawTriangle({1400, 880}, {1400, 760}, {1340, 880}, Fade(WHITE, 0.9f));
            DrawTextEx(font_caption, TextFormat("2/57"), {1425, 790}, 60, 0, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture_test);
    UnloadTexture(texture_return_button);
    UnloadTexture(texture_settings_button);
    UnloadFont(font_caption);

    CloseWindow();        // Close window and OpenGL context

    return 0;
}