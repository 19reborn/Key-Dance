#include "include/raylib.h"
#include <string>
#include <cstdio>
using std::string;


void play_tap(int tap_type = 1){
    string num = "0";
    num[0] += tap_type;
    char tap_filename[30] = "../backend/music/Tap 00.wav";
    tap_filename[21] = '0' + tap_type/10;
    tap_filename[22] = '0' + tap_type%10;
    //InitWindow(800,450,"test");
    InitAudioDevice();
    Music tap_playing = LoadMusicStream(tap_filename);
    
    //Music test_BGM = LoadMusicStream("music/AnotherMe.wav");
    
    PlayMusicStream(tap_playing);
    
    float start_time = GetTime();
    float maxn = 0.0;
    while(maxn<=GetMusicTimePlayed(tap_playing)){
        
        maxn = GetMusicTimePlayed(tap_playing);
        UpdateMusicStream(tap_playing);
        //printf("%f/%f\n",GetMusicTimeLength(tap_playing),GetMusicTimePlayed(tap_playing));
    }
    UnloadMusicStream(tap_playing);
    CloseAudioDevice();
}
/*
int main(){
    int x;
    scanf("%d",&x);
    play_tap(x);
}
*/