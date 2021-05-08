#include "game.h"
#include "init.h"
#include "render.h"
#include "update.h"

int
main(void)
{
    InitWindow(screenWidth, screenHeight, "sample game: snake");
    InitGame();

#if defined(PLATFORM_WEB)

    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);

#else

    SetTargetFPS(60);

    //Main game loop
    //Detect window close button or ESC key
    while (!WindowShouldClose()) 
    {
        UpdateGame();
        DrawGame();
    }

#endif

    //Close window and OpenGL context
    CloseWindow();

    return 0;
}
