#include "game.h"

//Global data...
const int screenWidth = 800;
const int screenHeight = 450;
int framesCounter = 0;
bool gameOver = false;
bool pause = false;

Food fruit = { 0 };
Snake snake[SNAKE_LENGTH] = { 0 };
Vector2 snakePosition[SNAKE_LENGTH] = { 0 };
bool allowMove = false;
Vector2 offset = { 0 };
int counterTail = 0;

Camera camera = {0};

