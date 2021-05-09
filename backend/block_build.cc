#include "include/raylib.h"
#include <vector>
#include <cstdio>
#include <string>
#include <stack>
using std::vector;
using std::string;
using std::stack;
KeyboardKey tem_keyboard[4] = {KEY_D, KEY_F, KEY_J, KEY_K};
struct Block {
    float init_time;
    float real_init_time;
    float last_time;
    int column;
    bool to_be_erase=false;
    Block(float _init_time, int _column){
        init_time = _init_time;
        real_init_time = init_time;
        last_time = 0;
        column = _column;
    }
    void update_down(){
        init_time = GetTime();
        last_time = GetTime() - real_init_time;
    }
};
void update_Block(vector<Block> & block_list){
    for(int i=0;i<4;i++){
        if (IsKeyPressed(tem_keyboard[i])) 
            block_list.push_back(Block(GetTime(),i));
        if (IsKeyDown(tem_keyboard[i])){
            int n = block_list.size();
            for(int j = n - 1; j>= 0;j--){
                if(block_list[j].column == i){
                    block_list[j].update_down();
                    break;
                }
            }
        }
    }
}
