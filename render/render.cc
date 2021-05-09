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
#include <list>
using namespace std;

class Effect {
public:
    Texture2D texture;
    Rectangle frameRec;
    int frames;
    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 8;  
    Vector2 pos;
    bool fade;
    Effect() {}
    Effect(const Texture2D& tex, const Vector2& position, bool fad=false, int f = 3, int fspeed = 8) {
        texture = tex;
        pos = position;
        fade = fad;
        frames = f;
        framesSpeed = fspeed;
        frameRec = { 0.0f, 0.0f, (float)texture.width/frames, (float)texture.height};
    }
    bool update() {
        bool ret = false;
        framesCounter++;
        if (framesCounter >= (60/framesSpeed)) {
            framesCounter = 0;
            currentFrame++;
            if (currentFrame >= frames) {
                currentFrame = 0;
                ret = true; // finished play once
            }
            frameRec.x = (float)currentFrame*(float)texture.width/frames;
        }
        return ret;
    }
    void draw() {
        if(!fade) {
            DrawTextureRec(texture, frameRec, pos, WHITE);
        } else {
            DrawTextureRec(texture, frameRec, pos, {255, 255, 255, (unsigned char)(255*(1-currentFrame/frames))});
        }
    }
};
list<Effect> curEffects;

#define MODE 1
#define SPEED 5.0f   // Number of spritesheet frames shown by second
const int length = 27.50;
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
Texture2D texture_pure_effect;
Texture2D texture_far_effect;
Texture2D texture_lost_effect;
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

void show_effect(const string& typ, int trackNum) {
    Vector2 pos;
    if(typ == "pure" || typ == "far" || typ == "lost") {
        if(trackNum == 0) {
            pos = {25.0f, 660.0f};
        } else if (trackNum == 1) {
            pos = {420.0f, 660.0f};
        } else if (trackNum == 2) {
            pos = {800.0f, 660.0f};
        } else if (trackNum == 3) {
            pos = {1180.0f, 660.0f};
        }
        if(typ == "pure") {
            curEffects.push_back(Effect(texture_pure_effect, pos, true));
        } else if(typ == "far") {
            curEffects.push_back(Effect(texture_far_effect, pos, true));
        } else if(typ == "lost") {
            curEffects.push_back(Effect(texture_lost_effect, pos, true));
        }
    }
}

void save(vector <Block> &block_group){
    FILE *fp;
    fp = fopen("./out","w");
    for(auto i:block_group){
        fprintf(fp,"%f %d %f\n",i.init_time,i.column,i.last_time);
    }
}
void draw_frame(int mode,vector <Block> &block_group){
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
            //单个节奏块
            float dis = length-(GetTime()-i->init_time)*SPEED;
            // 1.2 >= dis >=0.7 lost
            // 0.7 >= dis >=0.5 far
            // 0.5 >= dis >=0.3 pure
            // 0.3 >= dis >=0.1 far 
            // 0.1 >= dis >=0.0 lost
            if(i->last_time*SPEED<0.5f){
                if(IsKeyPressed(tem_keyboard[i->column])&&dis<=0.9f&&dis>=-0.2f){
                    //printf("%f\n",dis);
                    //正确地消除
                    if(dis>=0.8f){
                        show_effect("lost",i->column);
                    }
                    else if(dis>=0.7f){
                        show_effect("far",i->column);
                    }
                    else if(dis>=0.2f){
                        show_effect("pure",i->column);
                    }
                    else if(dis>=-0.1f){
                        show_effect("far",i->column);
                    }
                    else{
                        show_effect("lost",i->column);
                    }
                    block_group.erase(i);
                }
                else{
                    if(dis>=-0.8f){
                        draw_block(length-(GetTime()-i->init_time)*SPEED,i->column,i->last_time*SPEED);
                        i++;
                    }
                    else{
                            show_effect("lost",i->column);
                            block_group.erase(i);                        
                    }
                }
            }            
            else{
                float start_dis = -length+(GetTime()-i->init_time+i->last_time/2)*SPEED+0.2f;
                float end_dis = -length+(GetTime()-i->init_time-i->last_time/2)*SPEED+0.2f;
                if(i->to_be_erase){
                    if(end_dis<=0.0f){
                        draw_block(length-(GetTime()-i->init_time)*SPEED,i->column,i->last_time*SPEED);
                        i++;              
                    }   
                    else{
                        block_group.erase(i);
                    }          
                }
                else{
                    if(IsKeyPressed(tem_keyboard[i->column])&&start_dis>=-0.2f&&start_dis<=0.9f){
                        //printf("%f\n",dis);
                        //正确地消除
                        if(start_dis>=0.8f){
                            show_effect("lost",i->column);
                        }
                        else if(start_dis>=0.7f){
                            show_effect("far",i->column);
                        }
                        else if(start_dis>=0.2f){
                            show_effect("pure",i->column);
                        }
                        else if(start_dis>=-0.1f){
                            show_effect("far",i->column);
                        }
                        else{
                            show_effect("lost",i->column);
                        }                 
                    }
                    if(IsKeyDown(tem_keyboard[i->column])&&start_dis>=0.0f){
                        //if(end_dis>=0.5f){
                        //    show_effect("lost",i->column);
                        //    block_group.erase(i);
                        //}
                        if(end_dis<=0.0f){
                            draw_block((i->last_time*SPEED-(-length+(GetTime()-i->init_time+i->last_time/2)*SPEED+0.2f))/2,i->column,i->last_time*SPEED-(-length+(GetTime()-i->init_time+i->last_time/2)*SPEED+0.2f));
                            i++;
                        }
                        else{
                            show_effect("pure",i->column);
                            block_group.erase(i);
                        }
                    }
                    else if(IsKeyReleased(tem_keyboard[i->column])&&start_dis>=0.0f){
                        if(end_dis<0.0f){
                            float dis=-end_dis;
                            if(dis>=1.0f){
                                show_effect("lost",i->column);
                            }
                            else if(dis>=0.5){
                                show_effect("far",i->column);
                            }
                            else{
                                show_effect("pure",i->column);
                            }
                            i->to_be_erase=true;
                            draw_block(length-(GetTime()-i->init_time)*SPEED,i->column,i->last_time*SPEED);
                            i++;
                        }
                    }
                    else{
                        if(end_dis<=1.0f){
                            draw_block(length-(GetTime()-i->init_time)*SPEED,i->column,i->last_time*SPEED);
                            i++;              
                        }   
                        else{
                            show_effect("lost",i->column);
                            block_group.erase(i);
                        }   
                    }
                }
            }
        }

        DrawCube((Vector3){ 1.3f-27.50f, -0.4f, 0.85f }, 0.5f, 1.0f, 1.57f, BLUE);

        EndMode3D();

        DrawRectangle( 10, 10, 220, 70, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines( 10, 10, 220, 70, BLUE);

        // 绘制特效
        for(auto& effect: curEffects) {
            effect.draw();
        }
        // DrawTextureRec(texture_tap_effect, frameRec_tap_effect, TRACK1, WHITE);  // Draw part of the texture
        // DrawTextureRec(texture_tap_effect, frameRec_tap_effect, TRACK2, WHITE);  // Draw part of the texture
        // DrawTextureRec(texture_tap_effect, frameRec_tap_effect, TRACK3, WHITE);  // Draw part of the texture
        // DrawTextureRec(texture_tap_effect, frameRec_tap_effect, TRACK4, WHITE);  // Draw part of the texture 

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

        // 绘制特效
        for(auto& effect: curEffects) {
            effect.draw();
        }
        // DrawTextureRec(texture_tap_effect, frameRec_tap_effect, TRACK1, WHITE);  // Draw part of the texture
        // DrawTextureRec(texture_tap_effect, frameRec_tap_effect, TRACK2, WHITE);  // Draw part of the texture
        // DrawTextureRec(texture_tap_effect, frameRec_tap_effect, TRACK3, WHITE);  // Draw part of the texture
        // DrawTextureRec(texture_tap_effect, frameRec_tap_effect, TRACK4, WHITE);  // Draw part of the texture

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
    int perScore = 10000000 / totNotes + 1;
    return min(perScore * pures + perScore * fars / 2, 10000000);
}
// 2 => pure, 1 => far, 0 => lost
int calc_note_grade(float standard, float actual) {
    float bias = fabs(actual - standard);
    // 75:100:120
    if(bias <= 0.03) {
        return 2;
    } else if(bias <= 0.07) {
        return 1;
    } else {
        return 0;
    }
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
    texture_pure_effect = LoadTexture("resources/pure-effect.png");
    texture_far_effect = LoadTexture("resources/far-effect.png");
    texture_lost_effect = LoadTexture("resources/lost-effect.png");

    // Define the camera to look into our 3d world (position, target, up vector)
    camera.position = (Vector3){ 2.0f, 2.8f, 0.0f };
    camera.target = (Vector3){ 0.0f, 0.75f, 0.0f };
    camera.up = (Vector3){ 0.0f, 0.5f, 0.0f };
    camera.fovy = 80.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    SetCameraMode(camera, CAMERA_CUSTOM); 

    SetTargetFPS(60);                           // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    show_effect("pure", 1);
    show_effect("far", 2);
    show_effect("lost", 3);
    show_effect("lost", 4);

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
        // framesCounter++;
        // if (framesCounter >= (60/framesSpeed)) {
        //     framesCounter = 0;
        //     currentFrame++;
        //     if (currentFrame > 2) currentFrame = 0;
        //     frameRec_tap_effect.x = (float)currentFrame*(float)texture_tap_effect.width/3;
        // }
        for(list<Effect>::iterator it = curEffects.begin(); it != curEffects.end(); ++it) {
            // 所有特效都理应只播放一次
            if(it->update()) {
                curEffects.erase(it);
            }
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
    UnloadTexture(texture_pure_effect);    
    UnloadTexture(texture_far_effect);
    UnloadTexture(texture_lost_effect);

    CloseWindow();        // Close window and OpenGL context

    save(block_group);

    return 0;
}