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
    //todo 应该传入这些
    string songName = "Burn";
    string opernName;
    ScoreBoard scoreboard;
    bool isEnd = false;

    Texture2D texture_background;
    Font font_caption;
public:
    void init() {
        font_caption = LoadFontEx("../resources/bb2180.ttf", 96, 0, 0);
        string path = "../resources/song_bg/" + songName + ".png";
        texture_background = LoadTexture(path.c_str());
        SetTargetFPS(60);
    }
    void update() {
        // do nothing.
    }
    void draw() {
        //todo 可能最好有个待机音乐？

        BeginDrawing();
            ClearBackground(GRAY);
            DrawTextureEx(texture_background, { 0, 0 }, 0.0f, screenHeight / (float)texture_background.height, WHITE);
            // 两个遮罩
            DrawTriangle({0, 0}, {0, 900}, {400, 0}, Fade(BLACK, 0.2f));
            DrawTriangle({1600, 900}, {1600, 0}, {1200, 900}, Fade(BLACK, 0.2f));
            // 曲名信息
            DrawRectangle(0, 60, 500, 160, Fade(BLACK, 0.5f));
            DrawTriangle({500, 220}, {660, 60}, {500, 60}, Fade(BLACK, 0.5f));
            // DrawTextEx(font_caption, TextFormat("| %s", musicList[mlistidx].name.c_str()), {10, 160}, 90, 0, WHITE);

        EndDrawing();
    }
    bool is_end() {
        if(!isEnd) return false;
        isEnd = false;
        return true;
    }
    InterfaceState end() {
        UnloadTexture(texture_background);
        UnloadFont(font_caption);
        return INTERFACE_STATE_MUSIC_SWITCH;
    }
};

#endif