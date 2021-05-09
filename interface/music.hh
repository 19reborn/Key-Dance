#ifndef MUSIC_H
#define MUSIC_H

#include "interface.h"
#include "raylib.h"
#include "../backend/fileio.h"
#include "../backend/music_switch.cc"
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <list>
using namespace std;
extern ModeState mode;

class InterfaceMusic: public InterfaceBase {
private:
    vector<MUSIC_STATUS> musicList;
    int mlistSize;
    int mlistidx;
    Texture2D texture_return_button;
    Texture2D texture_settings_button;
    Font font_caption;
    vector<Music> BGMlst;
    vector<Texture2D> BGlst;
    int curSongidx;
    bool isEnd = false;
    
    bool isKeyPressed(KeyboardKey key){
      if(IsKeyPressed(key)){
          play_once(taps[0]);
          return true;
      }
      return false;
  }
public:
    string selectedSongName;
    string selectedOpern;

    void init() {
        printf("[debug] calling music init");
        //const int screenWidth = 1600;
        //const int screenHeight = 900;
        //InitWindow(screenWidth, screenHeight, "Select your song");
        // Load Textures
        texture_return_button = LoadTexture("../resources/return.png");
        texture_settings_button = LoadTexture("../resources/settings.png");
        font_caption = LoadFontEx("../resources/bb2180.ttf", 96, 0, 0);

        //InitAudioDevice();
		init_taps();
        
        musicList = init_music_vector();
        mlistSize = musicList.size();

        for(auto& music: musicList) {
            string path = "../songs/" + music.name + ".wav";
            BGMlst.push_back(LoadMusicStream(path.c_str()));
            path = "../resources/song_bg/";
            vector<string> bg_lst;
            getJustCurrentFile(path.c_str(), bg_lst);
            if(find(bg_lst.begin(), bg_lst.end(), music.name+".png") != bg_lst.end()) {
                string curPath = path + music.name + ".png";
                BGlst.push_back(LoadTexture(curPath.c_str()));
            } else {
                string curPath = path + "default.png";
                BGlst.push_back(LoadTexture(curPath.c_str()));
            }
        }

        SetTargetFPS(60);
    }
    void draw() {
        // 播放音乐
        play_repeat(BGMlst[curSongidx]);

        BeginDrawing();
            ClearBackground(GRAY);
            DrawTextureEx(BGlst[curSongidx], { 0, 0 }, 0.0f, screenHeight / (float)BGlst[curSongidx].height, WHITE);
            // 手动光栅化！
            // 左上
                // 遮罩
            DrawTriangle({0, 0}, {0, 1200}, {400, 0}, Fade(BLACK, 0.2f));
                // 返回
            DrawRectangle(0, 20, 120, 100, Fade(BLACK, 0.5f));
            DrawTriangle({120, 120}, {160, 20}, {120, 20}, Fade(BLACK, 0.5f));
            DrawTextureEx(texture_return_button, { 30, 40 }, 0.0f, 0.3f, WHITE);
                // 曲名信息
            DrawRectangle(0, 150, 500, 110, Fade(BLACK, 0.5f));
            DrawTriangle({500, 260}, {660, 150}, {500, 150}, Fade(BLACK, 0.5f));
            DrawTextEx(font_caption, TextFormat("| %s", musicList[mlistidx].name.c_str()), {10, 160}, 90, 0, WHITE);
            //todo 曲师姓名
            // DrawTextEx(font_caption, TextFormat("%s", musicList[mlistidx].authorName.c_str()), {30, 265}, 60, 0, WHITE);
            // 右上
                // 设置
            DrawRectangle(1480, 20, 160, 100, Fade(BLACK, 0.5f));
            DrawTriangle({1480, 120}, {1480, 20}, {1440, 20}, Fade(BLACK, 0.5f));
            DrawTextureEx(texture_settings_button, { 1500, 40 }, 0.0f, 0.3f, WHITE);
            // 左下
                // 最高分、ACC
            DrawRectangle(0, 600, 700, 150, Fade(BLACK, 0.5f));
            DrawTriangle({700, 750}, {790, 600}, {700, 600}, Fade(BLACK, 0.5f));
            const MUSIC_OPERN& curOpern = musicList[mlistidx].get_opern();
            const int& highscore = curOpern.max_score;
            if(highscore >= 0) {
                if(highscore <= 5000000) {
                    DrawTextEx(font_caption, TextFormat("D"), {50, 600}, 150, 0, GRAY);
                } else if(highscore <= 7000000) {
                    DrawTextEx(font_caption, TextFormat("C"), {50, 600}, 150, 0, RED);
                } else if(highscore <= 8000000) {
                    DrawTextEx(font_caption, TextFormat("B"), {50, 600}, 150, 0, YELLOW);
                } else if(highscore <= 9000000) {
                    DrawTextEx(font_caption, TextFormat("A"), {50, 600}, 150, 0, ORANGE);
                } else if(highscore <= 9500000) {
                    DrawTextEx(font_caption, TextFormat("S"), {50, 600}, 150, 0, PURPLE);
                } else if(highscore < 10000000) {
                    DrawTextEx(font_caption, TextFormat("V"), {50, 600}, 150, 0, {233, 0, 233, 255});
                } else if(highscore == 10000000) {
                    DrawTextEx(font_caption, TextFormat("P"), {50, 600}, 150, 0, PINK);
                }
            }
            //todo ACC率
            if(highscore >= 0)
                DrawTextEx(font_caption, TextFormat("%08d", highscore), {170, 630}, 90, 0, WHITE);
            if(curOpern.accRate >= 0)
                DrawTextEx(font_caption, TextFormat("%.2f%%", curOpern.accRate), {580, 670}, 40, 0, WHITE);
                // 所选谱面
            DrawRectangle(0, 780, 400, 100, Fade(BLACK, 0.5f));
            DrawTriangle({400, 880}, {460, 780}, {400, 780}, Fade(BLACK, 0.5f));
            if(highscore < 0)   // 创作模式
                DrawTextEx(font_caption, TextFormat("CREATE!"), {40, 800}, 60, 0, WHITE);
            else
                DrawTextEx(font_caption, TextFormat("%s", curOpern.username.c_str()), {40, 800}, 60, 0, WHITE);
            // 右下
                // 遮罩
            DrawTriangle({1600, 400}, {1440, 900}, {1600, 900}, Fade(BLACK, 0.2f));
                // 歌曲位置, 例: 2/57
            DrawRectangle(1400, 760, 200, 120, Fade(WHITE, 0.9f));
            DrawTriangle({1400, 880}, {1400, 760}, {1340, 880}, Fade(WHITE, 0.9f));
            DrawTextEx(font_caption, TextFormat("%d/%d", mlistidx+1, mlistSize), {1425, 790}, 60, 0, BLACK);

        EndDrawing();
    }
    void update() {
        //====================键盘操控=================
        if(isKeyPressed(KEY_W) || isKeyPressed(KEY_UP)) {
          curSongidx = (curSongidx - 1 + BGMlst.size()) % BGMlst.size();
          PlayMusicStream(BGMlst[curSongidx]); 
          mlistidx = (mlistidx + mlistSize - 1) % mlistSize;
        }
        if(isKeyPressed(KEY_S) || isKeyPressed(KEY_DOWN)) {
          curSongidx = (curSongidx + 1) % BGMlst.size();
          PlayMusicStream(BGMlst[curSongidx]); 
          mlistidx = (mlistidx + 1) % mlistSize;
        }
        if(isKeyPressed(KEY_A) || isKeyPressed(KEY_LEFT)) {
        	musicList[mlistidx].prev_opern();
        }
        if(isKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) {
            musicList[mlistidx].next_opern();
        }
        if(IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
            selectedSongName = musicList[mlistidx].name;
            selectedOpern = musicList[mlistidx].get_opern().filename;
            isEnd = true;
        }
    }
    InterfaceState end() {
        UnloadTexture(texture_return_button);
        UnloadTexture(texture_settings_button);
        UnloadFont(font_caption);

        for(auto& music: BGMlst) {
            UnloadMusicStream(music);
        }

        for(auto& text: BGlst) {
            UnloadTexture(text);
        }
        //CloseWindow(); 
        if(selectedOpern == "") {
            mode = MODE_GENERATE;
        } else {
            mode = MODE_PLAY;
        }
        return INTERFACE_STATE_PLAY;
    }
    bool is_end() {
        if(!isEnd) return false;
        isEnd = false;
        return true;
    }
};

#endif