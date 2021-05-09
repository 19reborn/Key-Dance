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
#include "../backend/music_switch.cc"
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <list>
using namespace std;

vector<MUSIC_STATUS> musicList;
int mlistSize;
int mlistidx;
string selectedSongName;
string selectedOpern;

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

    musicList = init_music_vector();
    mlistSize = musicList.size();

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
            DrawTextEx(font_caption, TextFormat("| %s", musicList[mlistidx].name.c_str()), {10, 160}, 90, 0, WHITE);
            //todo 曲师姓名
            DrawTextEx(font_caption, TextFormat("%s", musicList[mlistidx].authorName.c_str()), {30, 265}, 60, 0, WHITE);
            // 右上
                // 设置
            DrawRectangle(1480, 20, 160, 100, Fade(BLACK, 0.5f));
            DrawTriangle({1480, 120}, {1480, 20}, {1440, 20}, Fade(BLACK, 0.5f));
            DrawTextureEx(texture_settings_button, { 1500, 40 }, 0.0f, 0.3f, WHITE);
            // 左下
                // 最高分、ACC
            DrawRectangle(0, 600, 700, 150, Fade(BLACK, 0.5f));
            DrawTriangle({700, 750}, {790, 600}, {700, 600}, Fade(BLACK, 0.5f));
            const MUSIC_OPERN& curOpern = musicList[mlistidx].get_opern();
            const int& highscore = curOpern.max_score;
            if(highscore >= 0) {
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
            }
            //todo ACC率
            if(highscore >= 0)
                DrawTextEx(font_caption, TextFormat("%08d", highscore), {170, 630}, 90, 0, WHITE);
            if(curOpern.accRate >= 0)
                DrawTextEx(font_caption, TextFormat("%.2f%%", curOpern.accRate), {580, 670}, 40, 0, WHITE);
                // 所选谱面
            DrawRectangle(0, 780, 400, 100, Fade(BLACK, 0.5f));
            DrawTriangle({400, 880}, {460, 780}, {400, 780}, Fade(BLACK, 0.5f));
            if(highscore < 0)   // 创作模式
                DrawTextEx(font_caption, TextFormat("CREATE!"), {40, 800}, 60, 0, WHITE);
            else
                DrawTextEx(font_caption, TextFormat("%s", curOpern.username.c_str()), {40, 800}, 60, 0, WHITE);
            // 右下
                // 遮罩
            DrawTriangle({1600, 400}, {1440, 900}, {1600, 900}, Fade(BLACK, 0.2f));
                // 歌曲位置, 例: 2/57
            DrawRectangle(1400, 760, 200, 120, Fade(WHITE, 0.9f));
            DrawTriangle({1400, 880}, {1400, 760}, {1340, 880}, Fade(WHITE, 0.9f));
            DrawTextEx(font_caption, TextFormat("%d/%d", mlistidx+1, mlistSize), {1425, 790}, 60, 0, BLACK);

            //====================键盘操控=================
            if(IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
                mlistidx = (mlistidx + mlistSize - 1) % mlistSize;
            }
            if(IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) {
                mlistidx = (mlistidx + 1) % mlistSize;
            }
            if(IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) {
                musicList[mlistidx].prev_opern();
            }
            if(IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) {
                musicList[mlistidx].next_opern();
            }
            if(IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
                selectedSongName = musicList[mlistidx].name;
            }

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