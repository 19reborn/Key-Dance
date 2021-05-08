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

#define SPEED 5

const Vector2 TRACK1 = {160.0f, 700.0f};
const Vector2 TRACK2 = {550.0f, 700.0f};
const Vector2 TRACK3 = {930.0f, 700.0f};
const Vector2 TRACK4 = {1320.0f, 700.0f};

void draw_block(float t,int i,float k){
    if(!t){
        DrawCube((Vector3){ 1.3f, -0.4f, 0.85f }, 0.5f, 1.0f, 1.57f, SKYBLUE);
    }
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1600;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera first person");

    // Load Textures
    Texture2D texture_background = LoadTexture("resources/single_conflict_resized.png");
    Texture2D texture_tap = LoadTexture("resources/tap-v1.png");
    Texture2D texture_tap_effect = LoadTexture("resources/tap-effect.png");

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
    Rectangle frameRec_tap_effect = { 0.0f, 0.0f, (float)texture_tap_effect.width/3, (float)texture_tap_effect.height };


    SetCameraMode(camera, CAMERA_CUSTOM); // Set a first person camera mode

    SetTargetFPS(60);                           // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())                // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera);                  // Update camera

        // Update Effects
        framesCounter++;
        if (framesCounter >= (60/framesSpeed)) {
            framesCounter = 0;
            currentFrame++;
            if (currentFrame > 2) currentFrame = 0;
            frameRec_tap_effect.x = (float)currentFrame*(float)texture_tap_effect.width/3;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
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
            
            
            EndMode3D();

            DrawRectangle( 10, 10, 220, 70, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines( 10, 10, 220, 70, BLUE);

            DrawTextureRec(texture_tap_effect, frameRec_tap_effect, TRACK1, WHITE);  // Draw part of the texture
            DrawTextureRec(texture_tap_effect, frameRec_tap_effect, TRACK2, WHITE);  // Draw part of the texture
            DrawTextureRec(texture_tap_effect, frameRec_tap_effect, TRACK3, WHITE);  // Draw part of the texture
            DrawTextureRec(texture_tap_effect, frameRec_tap_effect, TRACK4, WHITE);  // Draw part of the texture


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture_background);
    UnloadTexture(texture_tap);
    UnloadTexture(texture_tap_effect);
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}