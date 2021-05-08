#ifndef __SNAKE__
#define __SNAKE__

#include "raylib.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

#define SNAKE_LENGTH   256
#define SQUARE_SIZE     31

typedef struct Snake {
    Vector2 position;
    Vector2 size;
    Vector2 speed;
    Color color;
} Snake;

typedef struct Food {
    Vector2 position;
    Vector2 size;
    bool active;
    Color color;
} Food;

extern const int screenWidth;
extern const int screenHeight;

extern int framesCounter;
extern bool gameOver;
extern bool pause;

extern Food fruit;
extern Snake snake[SNAKE_LENGTH];
extern Vector2 snakePosition[SNAKE_LENGTH];
extern bool allowMove;
extern Vector2 offset;
extern int counterTail;

extern Camera camera;

#endif
