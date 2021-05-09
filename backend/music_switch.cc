#include "include/raylib.h"
#include <string>
#include <vector>
using std::vector;
using std::string;
struct MUSIC_OPERN
{
    string filename;
    string username;
    float max_score;
};
struct MUSIC_STATUS{
    string name;
    int node;
    vector<MUSIC_OPERN> opern;
};
const int music_num = 4;
string music_list[music_num] = {"AboutUs0.wav","AnotherMe.wav","Aventyr.wav","Burn.wav"};
vector<MUSIC_STATUS> init_music_vector(){
    vector<MUSIC_STATUS> Music_list;
    for(int i=0;i<music_num;i++){
        Music_list.push_back(MUSIC_STATUS());
        Music_list[i].name = "music/"+music_list[i];
        Music_list[i].node = i;
    }
    return Music_list;
}
void play_once(Music &music){
    //在主函数首先要调用InitAudioDevice()
    PlayMusicStream(music);
    float maxn = 0.0;
    while(maxn<=GetMusicTimePlayed(music)){
        maxn = GetMusicTimePlayed(music);
        UpdateMusicStream(music);
        
    }
}
bool IF_BGM_PLAYING = false;
void play_repeat(Music &music){
    if (IF_BGM_PLAYING == false){
        PlayMusicStream(music);
        IF_BGM_PLAYING = true;
    }
    else{
        UpdateMusicStream(music);
    }
}
void play_stop(Music & music){
    if (IF_BGM_PLAYING == false){
        printf("Error:the music you stopped hasn't been played!!!\n");
    }
    else{
        StopMusicStream(music);
        IF_BGM_PLAYING = true;
    }
}
int main(){
    vector<MUSIC_STATUS> a = init_music_vector();
    InitAudioDevice();
    Music music = LoadMusicStream(a[3].name.c_str());
    play_once(music);
}