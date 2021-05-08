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

    // Define the camera to look into our 3d world (position, target, up vector)
    Camera camera = { 0 };
    camera.position = (Vector3){ 2.0f, 2.8f, 0.0f };
    camera.target = (Vector3){ 0.0f, 0.75f, 0.0f };
    camera.up = (Vector3){ 0.0f, 0.5f, 0.0f };
    camera.fovy = 80.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Generates some random columns


    SetCameraMode(camera, CAMERA_CUSTOM); // Set a first person camera mode

    SetTargetFPS(60);                           // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())                // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera);                  // Update camera
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


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture_background);
    UnloadTexture(texture_tap);
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}