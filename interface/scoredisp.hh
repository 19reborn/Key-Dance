#ifndef SCOREDISP_H
#define SCOREDISP_H

#include "interface.h"
#include "raylib.h"
#include "./render.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <list>
using namespace std;

class InterfaceScoreDisp: public InterfaceBase {
private:
    string songName;
    string opernName;
    ScoreBoard scoreboard;
    bool isEnd = false;

    Font font_caption;
public:
    void init() {
        font_caption = LoadFontEx("../resources/bb2180.ttf", 96, 0, 0);
        SetTargetFPS(60);
    }
    void update() {
        // do nothing.
    }
    void draw() {
        //todo 可能最好有个待机音乐？

        BeginDrawing();
            ClearBackground(GRAY);
            DrawTriangle({0, 0}, {0, 1200}, {400, 0}, Fade(BLACK, 0.2f));

        EndDrawing();
    }
    bool is_end() {
        if(!isEnd) return false;
        isEnd = false;
        return true;
    }
    InterfaceState end() {
        UnloadFont(font_caption);
        return INTERFACE_STATE_MUSIC_SWITCH;
    }
};

#endif