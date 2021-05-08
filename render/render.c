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
using namespace std;

#define SPEED 20.0f
const int length = 27.50;
const Vector2 TRACK1 = {160.0f, 700.0f};
const Vector2 TRACK2 = {550.0f, 700.0f};
const Vector2 TRACK3 = {930.0f, 700.0f};
const Vector2 TRACK4 = {1320.0f, 700.0f};

struct block{
    float init_time;
    int column;
    float last_time;
};
vector <block> block_group;
Texture2D texture_background;
Texture2D texture_tap;
Texture2D texture_tap_effect;
Camera camera = { 0 };

void draw_block(float t,int i,float k){
    float y;
    switch (i)
    {
    case 1:
        y=-2.6;
        break;
    case 2:
        y=-0.85;
        break;
    case 3:
        y=0.85;
        break;
    case 4:
        y=2.6;
        break;
    }
    if(k<1e-7&&k>-1e-7){
        DrawCube((Vector3){ 1.3f-t, -0.4f, y }, 0.2f, 1.0f, 1.57f, RED);
    }
    else{
        DrawCube((Vector3){ 1.3f-t, -0.4f, y }, k, 1.0f, 1.57f, RED);
    }
}

void input(){
    FILE * fp = NULL;
    fp = fopen("./tmp.txt","r");
    if(!fp){
        printf("file open error!\n");
        exit(1);
    }
    char line[100];
    while(!feof(fp)){
        fgets(line,100,fp);
        //第一个数表示block出现时间,第二个数表示block属于第几列,第三个数表示block的持续时间.
        block b;
        string s="";
        int i=0;
        while(line[i]!=' '){
            s+=line[i];
            i++;
        }
        i++;
        b.init_time=stof(s);
        s="";
        while(line[i]!=' '){
            s+=line[i];
            i++;
        }
        b.column=stoi(s);
        s="";
        i++;
        while(line[i]!=' '&&line[i]!='\n'){
            s+=line[i];
            i++;
        }    
        b.last_time=stof(s);
        block_group.push_back(b);
    }
}

void draw_frame(int mode,vector <block> block_group){
    if(mode == 1){
        //游玩模式
        BeginDrawing();
        ClearBackground(GRAY);
        DrawTextureEx(texture_background, (Vector2){ 0, 0 }, 0.0f, 1.0f, WHITE);
        
        BeginMode3D(camera);

        DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 1000.0f, 7.17f }, (Color){255, 255, 255, 120}); // Draw ground
        DrawCubeWires((Vector3){ 0.0f, -0.7f, 0.8f }, 1000.0f, 2.0f, 1.6f, LIGHTGRAY);
        DrawCubeWires((Vector3){ 0.0f, -0.7f, 2.4f }, 1000.0f, 2.0f, 1.6f, LIGHTGRAY);
        DrawCubeWires((Vector3){ 0.0f, -0.7f, -0.8f }, 1000.0f, 2.0f, 1.6f, LIGHTGRAY);
        DrawCubeWires((Vector3){ 0.0f, -0.7f, -2.4f }, 1000.0f, 2.0f, 1.6f, LIGHTGRAY);

        DrawCubeTexture(texture_tap, (Vector3){ 1.3f, -0.4f, 0.85f }, 0.5f, 1.0f, 1.57f, WHITE);
        DrawCubeTexture(texture_tap, (Vector3){ 1.3f, -0.4f, 2.6f }, 0.5f, 1.0f, 1.5f, WHITE);
        DrawCubeTexture(texture_tap, (Vector3){ 1.3f, -0.4f, -0.85f }, 0.5f, 1.0f, 1.57f, WHITE);
        DrawCubeTexture(texture_tap, (Vector3){ 1.3f, -0.4f, -2.6f }, 0.5f, 1.0f, 1.5f, WHITE);    

        for(auto i:block_group){
            draw_block(length-(GetTime()-i.init_time)*SPEED,i.column,i.last_time*SPEED);
        }
        DrawCube((Vector3){ 1.3f-27.50f, -0.4f, 0.85f }, 0.5f, 1.0f, 1.57f, BLUE);

        EndMode3D();

        DrawRectangle( 10, 10, 220, 70, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines( 10, 10, 220, 70, BLUE);

    }
    //制作模式
    else{
        BeginDrawing();
        ClearBackground(GRAY);
        DrawTextureEx(texture_background, (Vector2){ 0, 0 }, 0.0f, 1.0f, WHITE);
        BeginMode3D(camera);

        DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 1000.0f, 7.17f }, (Color){255, 255, 255, 120}); // Draw ground
        DrawCubeWires((Vector3){ 0.0f, -0.7f, 0.8f }, 1000.0f, 2.0f, 1.6f, LIGHTGRAY);
        DrawCubeWires((Vector3){ 0.0f, -0.7f, 2.4f }, 1000.0f, 2.0f, 1.6f, LIGHTGRAY);
        DrawCubeWires((Vector3){ 0.0f, -0.7f, -0.8f }, 1000.0f, 2.0f, 1.6f, LIGHTGRAY);
        DrawCubeWires((Vector3){ 0.0f, -0.7f, -2.4f }, 1000.0f, 2.0f, 1.6f, LIGHTGRAY);

        DrawCubeTexture(texture_tap, (Vector3){ -length, -0.4f, 0.85f }, 0.5f, 1.0f, 1.57f, WHITE);
        DrawCubeTexture(texture_tap, (Vector3){ -length, -0.4f, 2.6f }, 0.5f, 1.0f, 1.5f, WHITE);
        DrawCubeTexture(texture_tap, (Vector3){ -length, -0.4f, -0.85f }, 0.5f, 1.0f, 1.57f, WHITE);
        DrawCubeTexture(texture_tap, (Vector3){ -length, -0.4f, -2.6f }, 0.5f, 1.0f, 1.5f, WHITE);    
        for(auto i:block_group){
            draw_block(length+(GetTime()-i.init_time)*SPEED,i.column,-i.last_time*SPEED);
        }
        EndMode3D();

            DrawRectangle( 10, 10, 220, 70, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines( 10, 10, 220, 70, BLUE);       
    }
    EndDrawing();  
}

int calc_score(int totNotes, int pures, int fars, int losts = 0) {
    int perScore = 10000000 / totNotes;
    return perScore * pures + perScore * fars / 2;
}



int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1600;
    const int screenHeight = 900;
    input();
    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera first person");

    // Load Textures
    texture_background = LoadTexture("resources/single_conflict_resized.png");
    texture_tap = LoadTexture("resources/tap-v1.png");
    texture_tap_effect = LoadTexture("resources/tap-effect.png");

    // Define the camera to look into our 3d world (position, target, up vector)
    Camera camera = { 0 };
    camera.position = (Vector3){ 2.0f, 2.8f, 0.0f };
    camera.target = (Vector3){ 0.0f, 0.75f, 0.0f };
    camera.up = (Vector3){ 0.0f, 0.5f, 0.0f };
    camera.fovy = 80.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Generates some random columns

    // Effects
    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 8;            // Number of spritesheet frames shown by second
    Rectangle frameRec_tap_effect = { 0.0f, 0.0f, (float)texture_tap_effect.width/3, (float)texture_tap_effect.height};

    // Score
    int score_score = 0;
    int score_combo = 0;
    int score_pure = 0;
    int score_far = 0;
    int score_lost = 0;
    texture_background = LoadTexture("resources/single_conflict_resized.png");
    texture_tap = LoadTexture("resources/tap-v1.png");
    // Load Textures

    // Define the camera to look into our 3d world (position, target, up vector)
    camera.position = (Vector3){ 2.0f, 2.8f, 0.0f };
    camera.target = (Vector3){ 0.0f, 0.75f, 0.0f };
    camera.up = (Vector3){ 0.0f, 0.5f, 0.0f };
    camera.fovy = 80.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    SetCameraMode(camera, CAMERA_CUSTOM); 

    SetTargetFPS(60);                           // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())                // Detect window close button or ESC key
    {
        //----------------------------------------------------------------------------------
        // Draw
        //BeginDrawing();
        //ClearBackground(GRAY);
        //DrawTextureEx(texture_background, (Vector2){ 0, 0 }, 0.0f, 1.0f, WHITE);
        //----------------------------------------------------------------------------------
        draw_frame(1,block_group);


        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture_background);
    UnloadTexture(texture_tap);    
    CloseWindow();        // Close window and OpenGL context

    return 0;
}