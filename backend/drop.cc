/*******************************************************************************************
*
*   raylib [core] example - Keyboard input
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <vector>
#include <cstdio>
#include <string>
using std::vector;
using std::string;

struct Block {
    Vector2 position;
    float speed;
    float showup_time;
    Block(float _init_x, float _init_y, float _speed) {
        position.x = _init_x;
        position.y = _init_y;
        speed = _speed;
        showup_time = GetTime();
    }
    void update_position() {
        position.y += speed;
    }
};

struct BlockList : public vector<Block> {
    void append(Block block) {
        push_back(block);
    }
};

void save_blocklist(BlockList block_list, const char* file_path) {
    FILE *fp = NULL;
    fp = fopen(file_path, "w+");
    if (fp == NULL) {
        printf("failed to open %s", file_path);
        return;
    }
    for (const Block& block : block_list) {
        fprintf(fp, "%.2f %.2f %.2f %.2f\n", block.position.x, block.position.y, block.speed, block.showup_time);
    }
    fclose(fp);
}



const int screenWidth = 800;
const int screenHeight = 450;

const float POSX_D = screenWidth / 5.0;
const float POSX_F = screenWidth / 5.0 * 2.0;
const float POSX_J = screenWidth / 5.0 * 3.0;
const float POSX_K = screenWidth / 5.0 * 4.0;

float get_posx_by_key(KeyboardKey key) {
    switch (key)
    {
    case KEY_D:
        return POSX_D;
    case KEY_F:
        return POSX_F;
    case KEY_J:
        return POSX_J;
    case KEY_K:
        return POSX_K;
    default:
        printf("wrong key in get_posx_by_key()");
        return 0.0;
    }
}


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    BlockList block_list;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

    Block block(screenWidth/2.0, 0, 2);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        /* 1 add new block */
        KeyboardKey key = KEY_NULL;
        if (IsKeyDown(KEY_D)) key = KEY_D;
        else if (IsKeyDown(KEY_F)) key = KEY_F;
        else if (IsKeyDown(KEY_J)) key = KEY_J;
        else if (IsKeyDown(KEY_K)) key = KEY_K;
        if (key != KEY_NULL) {
            float posx = get_posx_by_key(key);
            Block block(posx, 0, 2);
            block_list.append(block);
        }
        /* 2 update block position */
        for (Block& block : block_list) {
            block.update_position();
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);


            /* TODO: block out of screen should be skipped */
            for (const Block& block : block_list) {
                DrawCircleV(block.position, 50, MAROON);
                char sTime[15];
                sprintf(sTime, "%.2f", block.showup_time); 
                DrawText(sTime, block.position.x, block.position.y, 20, DARKGRAY);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    save_blocklist(block_list, "data/blocks_1.txt");

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}