#ifndef SCOREDISP_H
#define SCOREDISP_H

#include "interface.h"
#include "raylib.h"
#include "./render.h"
#include "../backend/fileio.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <list>
using namespace std;

extern ScoreBoard scoreboard;

class InterfaceScoreDisp: public InterfaceBase {
private:
    string songName;
    string opernName;

    int highscore;

    Texture2D texture_background;
    Font font_caption;

    bool isEnd = false;
public:
    void init() {
        songName = SELECTED_SONG;
        opernName = SELECTED_OPERN;

        font_caption = LoadFontEx("../resources/bb2180.ttf", 96, 0, 0);
        string path = "../resources/song_bg/" + songName + ".png";
        if(!_access(path.c_str(), 0)) {
            texture_background = LoadTexture(path.c_str());
        } else {
            texture_background = LoadTexture("../resources/song_bg/default.png");
        }
        path = "../songs/" + songName + "/" + opernName + "/score.txt";
        if(!_access(path.c_str(), 0)) {
            FILE * fp = NULL;
            fp = fopen(path.c_str(), "r");
            if(!fp){
                printf("[ERROR] scoredisp file open error!\n");
                exit(1);
            }
            char line[100];
            fgets(line, 100, fp);
            highscore = atoi(line);
            fclose(fp);
        } else {
            highscore = 0;
        }
        
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
            // 曲名信息
            DrawRectangle(0, 60, 800, 100, Fade(BLACK, 0.5f));
            DrawTriangle({800, 160}, {900, 60}, {800, 60}, Fade(BLACK, 0.5f));
            DrawTextEx(font_caption, TextFormat("| %s", songName.c_str()), {380, 65}, 90, 0, WHITE);
            // 中心边框
            DrawRectangle(0, 250, 1600, 400, Fade(BLACK, 0.6f));
            DrawRectangle(0, 350, 1600, 200, Fade(WHITE, 0.4f));
            // 光栅化
            DrawTriangle({500, 320}, {370, 450}, {630, 450}, Fade(WHITE, 1.f));
            DrawTriangle({500, 580}, {630, 450}, {370, 450}, Fade(WHITE, 1.f));
            DrawTriangle({500, 330}, {380, 450}, {620, 450}, Fade(BLACK, 1.f));
            DrawTriangle({500, 570}, {620, 450}, {380, 450}, Fade(BLACK, 1.f));
            // 画ACC
            DrawTextEx(font_caption, TextFormat("ACC:%.2f%%", scoreboard.get_acc()), {207, 433}, 30, 0, WHITE);
            // 画分数
            DrawTextEx(font_caption, TextFormat("%08d", scoreboard.get_score()), {660, 410}, 80, 0, WHITE);
            // 画Combo //todo full combo特殊字幕
            DrawTextEx(font_caption, TextFormat("Max Combo: %d", scoreboard.maxCombo), {1060, 433}, 40, 0, WHITE);
            // 画各note个数
            DrawTextEx(font_caption, TextFormat("PURE"), {700, 610}, 30, 0, PINK);
            DrawTextEx(font_caption, TextFormat("FAR"), {900, 610}, 30, 0, ORANGE);
            DrawTextEx(font_caption, TextFormat("LOST"), {1100, 610}, 30, 0, GRAY);
            DrawTextEx(font_caption, TextFormat("%3d", scoreboard.pure), {700, 565}, 40, 0, WHITE);
            DrawTextEx(font_caption, TextFormat("%3d", scoreboard.far), {888, 565}, 40, 0, WHITE);
            DrawTextEx(font_caption, TextFormat("%3d", scoreboard.lost), {1095, 565}, 40, 0, WHITE);
            // 画评级
            Vector2 centerPos = {460, 375};
            if(scoreboard.get_score() <= 5000000) {
                DrawTextEx(font_caption, TextFormat("D"), centerPos, 150, 0, GRAY);
            } else if(scoreboard.get_score() <= 7000000) {
                DrawTextEx(font_caption, TextFormat("C"), centerPos, 150, 0, RED);
            } else if(scoreboard.get_score() <= 8000000) {
                DrawTextEx(font_caption, TextFormat("B"), centerPos, 150, 0, YELLOW);
            } else if(scoreboard.get_score() <= 9000000) {
                DrawTextEx(font_caption, TextFormat("A"), centerPos, 150, 0, ORANGE);
            } else if(scoreboard.get_score() <= 9500000) {
                DrawTextEx(font_caption, TextFormat("S"), centerPos, 150, 0, PURPLE);
            } else if(scoreboard.get_score() < 10000000) {
                DrawTextEx(font_caption, TextFormat("V"), centerPos, 150, 0, {233, 0, 233, 255});
            } else if(scoreboard.get_score() == 10000000) {
                DrawTextEx(font_caption, TextFormat("P"), centerPos, 150, 0, PINK);
            }
            // 画历史分
            if(scoreboard.get_score() > highscore)
                DrawTextEx(font_caption, TextFormat("NEW BEST"), {660, 280}, 40, 0, GREEN);
            DrawTextEx(font_caption, TextFormat("%08d", highscore), {960, 280}, 40, 0, WHITE);
            string fmt = scoreboard.get_score() > highscore? "+%8d" : "-%8d";
            DrawTextEx(font_caption, TextFormat(fmt.c_str(), abs(scoreboard.get_score() - highscore)), {1200, 280}, 40, 0, WHITE);
            // 两个遮罩
            DrawTriangle({0, 0}, {0, 900}, {400, 0}, Fade(BLACK, 0.8f));
            DrawTriangle({1600, 900}, {1600, 0}, {1200, 900}, Fade(BLACK, 0.8f));

        EndDrawing();

        if(IsKeyPressed(KEY_Q)) {isEnd = true;}
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