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
#include "../backend/block_build.cc"
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

#define MODE 1
#define SPEED 10.0f
const int length = 27.50;
const Vector2 TRACK1 = {160.0f, 700.0f};
const Vector2 TRACK2 = {550.0f, 700.0f};
const Vector2 TRACK3 = {930.0f, 700.0f};
const Vector2 TRACK4 = {1320.0f, 700.0f};
    // Effects
int currentFrame = 0;
int framesCounter = 0;
int framesSpeed = 8;            // Number of spritesheet frames shown by second

    // Score
    int score_score = 0;
    int score_combo = 0;
    int score_pure = 0;
    int score_far = 0;
    int score_lost = 0;

/*struct block{
    float init_time;
    int column;
    float last_time;
};
*/
vector <Block> block_group;
Texture2D texture_background;
Texture2D texture_tap;
Texture2D texture_tap_effect;
Rectangle frameRec_tap_effect;
Camera camera = { 0 };

void draw_block(float t,int i,float k){
    float y;
    switch (i)
    {
    case 3:
        y=-2.6;
        break;
    case 2:
        y=-0.85;
        break;
    case 1:
        y=0.85;
        break;
    case 0:
        y=2.6;
        break;
    }
    if(fabs(k)<0.5f){
        DrawCube((Vector3){ 1.3f-t, -0.2f, y }, 0.5f, 0.5f, 1.57f, RED);
    }
    else{
        DrawCube((Vector3){ 1.3f-t, -0.2f, y }, fabs(k), 0.5f, 1.57f, RED);
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
        Block B(0,0);
        string s="";
        int i=0;
        while(line[i]!=' '){
            s+=line[i];
            i++;
        }
        i++;
        B.init_time=stof(s);
        s="";
        while(line[i]!=' '){
            s+=line[i];
            i++;
        }
        B.column=stoi(s)-1;
        s="";
        i++;
        while(line[i]!=' '&&line[i]!='\n'){
            s+=line[i];
            i++;
        }    
        B.last_time=stof(s);
        block_group.push_back(B);
    }
}

void save(vector <Block> &block_group){
    FILE *fp;
    fp = fopen("./out.txt","w");
    for(auto i:block_group){
        fprintf(fp,"%f %d %f\n",i.init_time,i.column,i.last_time);
    }
}
void draw_frame(int mode,vector <Block> & block_group){
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

        auto i=block_group.begin(); 
        while(i!=block_group.end()){
            if(i->last_time*SPEED<0.5f){
                if(IsKeyPressed(tem_keyboard[i->column])&&length-(GetTime()-i->init_time)*SPEED<=0.8f){
                    block_group.erase(i);
                }
                else{
                    draw_block(length-(GetTime()-i->init_time)*SPEED,i->column,i->last_time*SPEED);
                    i++;
                }
            }            
            else{
                if(IsKeyDown(tem_keyboard[i->column])&&-length+(GetTime()-i->init_time+i->last_time/2)*SPEED>=-0.2f){
                    if(-length+(GetTime()-i->init_time-i->last_time/2)*SPEED>=-0.2f){
                        block_group.erase(i);
                    }
                    else{
                        draw_block((i->last_time*SPEED-(-length+(GetTime()-i->init_time+i->last_time/2)*SPEED+0.2f))/2,i->column,i->last_time*SPEED-(-length+(GetTime()-i->init_time+i->last_time/2)*SPEED+0.2f));
                        i++;
                    }
                }
                else{
                    draw_block(length-(GetTime()-i->init_time)*SPEED,i->column,i->last_time*SPEED);
                    i++;
                }
            }
        }
        /*
        for(auto i:block_group){
            if(i.last_time<0.5f){
                if(IsKeyDown(tem_keyboard[i.column])&&length-(GetTime()-i.init_time)*SPEED<=5){
                    block_group.erase(i);
                }
                else{
                    draw_block(length-(GetTime()-i.init_time)*SPEED,i.column,i.last_time*SPEED);
                }
            }
            else{
                if(IsKeyPressed(tem_keyboard[i.column])&&length-(GetTime()-i.init_time)*SPEED<=0){
                    draw_block(0,i.column,(i.last_time+length-(GetTime()-i.init_time))*SPEED);
                }
                else{
                    draw_block(length-(GetTime()-i.init_time)*SPEED,i.column,i.last_time*SPEED);
                }
            }
        }
        */
        
        DrawCube((Vector3){ 1.3f-27.50f, -0.4f, 0.85f }, 0.5f, 1.0f, 1.57f, BLUE);

        EndMode3D();

        DrawRectangle( 10, 10, 220, 70, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines( 10, 10, 220, 70, BLUE);

        DrawTextureRec(texture_tap_effect, frameRec_tap_effect, TRACK1, WHITE);  // Draw part of the texture
        DrawTextureRec(texture_tap_effect, frameRec_tap_effect, TRACK2, WHITE);  // Draw part of the texture
        DrawTextureRec(texture_tap_effect, frameRec_tap_effect, TRACK3, WHITE);  // Draw part of the texture
        DrawTextureRec(texture_tap_effect, frameRec_tap_effect, TRACK4, WHITE);  // Draw part of the texture 

           // score board:
        DrawText(TextFormat("SCORE: %08i", score_score), 1200, 10, 40, LIME);
        DrawText(TextFormat("%i COMBO!", score_combo), 600, 560, 80, VIOLET);
        DrawText(TextFormat("PURE: %i", score_pure), 1200, 50, 40, PINK);
        DrawText(TextFormat("FAR: %i", score_far), 1200, 90, 40, ORANGE);
        DrawText(TextFormat("LOST: %i", score_lost), 1200, 130, 40, GRAY);

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

        DrawCubeTexture(texture_tap, (Vector3){ 1.3f, -0.4f, 0.85f }, 0.3f, 1.0f, 1.57f, WHITE);
        DrawCubeTexture(texture_tap, (Vector3){ 1.3f, -0.4f, 2.6f }, 0.3f, 1.0f, 1.5f, WHITE);
        DrawCubeTexture(texture_tap, (Vector3){ 1.3f, -0.4f, -0.85f }, 0.3f, 1.0f, 1.57f, WHITE);
        DrawCubeTexture(texture_tap, (Vector3){ 1.3f, -0.4f, -2.6f }, 0.3f, 1.0f, 1.5f, WHITE);  

        for(auto i:block_group){
            draw_block((GetTime()-i.init_time+i.last_time/2)*SPEED+0.5f,i.column,-i.last_time*SPEED);
        }
        EndMode3D();

        DrawRectangle( 10, 10, 220, 70, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines( 10, 10, 220, 70, BLUE);

        DrawTextureRec(texture_tap_effect, frameRec_tap_effect, TRACK1, WHITE);  // Draw part of the texture
        DrawTextureRec(texture_tap_effect, frameRec_tap_effect, TRACK2, WHITE);  // Draw part of the texture
        DrawTextureRec(texture_tap_effect, frameRec_tap_effect, TRACK3, WHITE);  // Draw part of the texture
        DrawTextureRec(texture_tap_effect, frameRec_tap_effect, TRACK4, WHITE);  // Draw part of the texture

                   // score board:
        DrawText(TextFormat("SCORE: %08i", score_score), 1200, 10, 40, LIME);
        DrawText(TextFormat("%i COMBO!", score_combo), 600, 560, 80, VIOLET);
        DrawText(TextFormat("PURE: %i", score_pure), 1200, 50, 40, PINK);
        DrawText(TextFormat("FAR: %i", score_far), 1200, 90, 40, ORANGE);
        DrawText(TextFormat("LOST: %i", score_lost), 1200, 130, 40, GRAY); 

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
    block_group.clear();
    if(MODE==1){
        input();
    }
    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera first person");
    // Load Textures
    texture_background = LoadTexture("resources/single_conflict_resized.png");
    texture_tap = LoadTexture("resources/tap-v1.png");
    texture_tap_effect = LoadTexture("resources/tap-effect.png");

    frameRec_tap_effect = { 0.0f, 0.0f, (float)texture_tap_effect.width/3, (float)texture_tap_effect.height};
    // Generates some random columns

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
                // Update Effects
        
        framesCounter++;
        if (framesCounter >= (60/framesSpeed)) {
            framesCounter = 0;
            currentFrame++;
            if (currentFrame > 2) currentFrame = 0;
            frameRec_tap_effect.x = (float)currentFrame*(float)texture_tap_effect.width/3;
        }
        if(MODE!=1)
            update_Block(block_group);
        draw_frame(1,block_group);


        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture_background);
    UnloadTexture(texture_tap);    
    UnloadTexture(texture_tap_effect);    
    CloseWindow();        // Close window and OpenGL context

    save(block_group);

    return 0;
}