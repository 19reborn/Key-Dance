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

#define MAX_COLUMNS 20

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1600;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera first person");

    // Load Textures
    Texture2D background = LoadTexture("resources/tracktest.png");

    // Define the camera to look into our 3d world (position, target, up vector)
    Camera camera = { 0 };
    camera.position = (Vector3){ 4.0f, 2.0f, 0.0f };
    camera.target = (Vector3){ 0.0f, 0.5f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
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

            ClearBackground(RAYWHITE);

            // Draw a 2D background
            // DrawTextureEx(background, (Vector2){ 0, 0 }, 0.0f, 2.0f, WHITE);

            BeginMode3D(camera);

                DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 10.0f, 10.0f }, LIGHTGRAY); // Draw ground
                DrawCube((Vector3){ 0.0f, 0.0f, 2.0f }, 2.0f, 2.0f, 1.0f, MAROON);
                
                // Draw a background "plane" in 3D
                DrawCubeTexture(background, (Vector3){0.0f, 0.0f, 0.0f}, 10.0f, 0.0f, 10.0f, WHITE);

            EndMode3D();

            DrawRectangle( 10, 10, 220, 70, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines( 10, 10, 220, 70, BLUE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}