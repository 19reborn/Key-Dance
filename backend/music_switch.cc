#include "include/raylib.h"
#include "fileio.h"
#include <string>
#include <vector>
using std::vector;
using std::string;
class MUSIC_OPERN {
public:
    string filename;
    string username;
    int max_score = 0;
    float accRate = 0.0f;  //todo 准确率
    MUSIC_OPERN() {}
    MUSIC_OPERN(string fileName, string userName, int maxScore, float acc): 
        filename(fileName), username(userName), max_score(maxScore), accRate(acc) {}
};
class MUSIC_STATUS {
public:
    string name;
    string authorName;  //todo 曲师名字
    string bgPath;      //todo 曲绘(背景图片)路径
    int opernIdx;
    vector<MUSIC_OPERN> opern;
    MUSIC_OPERN& get_opern() {
        return opern[opernIdx];
    }
    void next_opern() {
        opernIdx = (opernIdx + 1) % opern.size();
    }
    void prev_opern() {
        opernIdx = (opernIdx + opern.size() - 1) % opern.size();
    }
};
// const int music_num = 4;
// string music_list[music_num] = {"AboutUs0.wav","AnotherMe.wav","cryout.wav","Burn.wav"};
vector<string> music_list;
vector<Sound> taps;

int init_music_list() {
    getJustCurrentFile("../songs/", music_list);
    return music_list.size();
}

vector<MUSIC_STATUS> init_music_vector(){
    int music_num = init_music_list();

    vector<MUSIC_STATUS> Music_list;
    for(int i=0;i<music_num;i++){
        Music_list.push_back(MUSIC_STATUS());
        Music_list[i].name = music_list[i].substr(0, music_list[i].find(".wav"));
        //todo 新增读入opern
        // 下面这个是用于表示创作模式的虚拟节点
        Music_list[i].opern.push_back(MUSIC_OPERN("", "", -1, -1));
    }
    return Music_list;
}

void init_taps(){
    //一定要预先InitAudioDevice()
    for(int i = 1;i<=14;i++){
        char tap_filename[30] = "../sounds/Tap 00.wav";
        tap_filename[21] = '0' + i/10;
        tap_filename[22] = '0' + i%10;  
        taps.push_back(LoadSound(tap_filename));
    }
}
void play_once(Sound &tap){
    //在主函数首先要调用InitAudioDevice()
    PlaySound(tap);
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
/*int main(){
    vector<MUSIC_STATUS> a = init_music_vector();
    InitAudioDevice();
    Music music = LoadMusicStream(a[3].name.c_str());
    play_once(music);
}*/
