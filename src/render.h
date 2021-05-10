#ifndef RENDER_H
#define RENDER_H

#include "interface.h"
#include "raylib.h"
#include "../score/score.cpp"
// #include "./interfaces/public.cc"
// #include "../backend/block_build.cc"
// #include "../backend/music_switch.cc"
#include <direct.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <list>
using namespace std;

extern ModeState mode;
extern ScoreBoard scoreboard;
extern int createScore;
static int MODE = 1;
typedef enum{
	PLAY_NORMAL,
	PLAY_BACK,
	PLAY_AGAIN,
	PLAY_STALL,
	PLAY_FINISH,
	PLAY_NULL
}PLAY_STATUS;
PLAY_STATUS status;

extern string SELECTED_SONG;
extern string SELECTED_OPERN;

class InterfacePlay: public InterfaceBase{
	private:
		static double zero_time;
		static double start_time;
		static double end_time;
		static double getTime(){
			return GetTime()-zero_time;
		}
		bool waiting;
		bool isKeyDown(KeyboardKey &key){
			if(IsKeyDown(key)){
				//play_once(taps[1]);
				return true;
			}
			return false;
		}
		bool isKeyPressed(KeyboardKey &key){
			if(IsKeyPressed(key)){
				play_once(taps[0]);
				return true;
			}
			return false;
		}
		bool isKeyReleased(KeyboardKey &key){
			if(IsKeyReleased(key)){
				//play_once(taps[3]);
				return true;
			}
			return false;
		}
		class Effect{
			public:
			    Texture2D texture;
			    Rectangle frameRec;
			    int frames;
			    int currentFrame = 0;
			    int framesCounter = 0;
			    int framesSpeed = 8;  
			    Vector2 pos;
			    bool fade;
			    Effect() {}
			    Effect(const Texture2D& tex, const Vector2& position, bool fad=false, int f = 3, int fspeed = 8) {
			        texture = tex;
			        pos = position;
			        fade = fad;
			        frames = f;
			        framesSpeed = fspeed;
			        frameRec = { 0.0f, 0.0f, (float)texture.width/frames, (float)texture.height};
			    }
			    bool update() {
			        bool ret = false;
			        framesCounter++;
			        if (framesCounter >= (60/framesSpeed)) {
			            framesCounter = 0;
			            currentFrame++;
			            if (currentFrame >= frames) {
			                currentFrame = 0;
			                ret = true; // finished play once
			            }
			            frameRec.x = (float)currentFrame*(float)texture.width/frames;
			        }
			        return ret;
			    }
			    void draw() {
			        if(!fade) {
			            DrawTextureRec(texture, frameRec, pos, WHITE);
			        } else {
			            DrawTextureRec(texture, frameRec, pos, {255, 255, 255, (unsigned char)(255*(1-currentFrame/frames))});
			        }
			    }
			};
		list<Effect> curEffects;
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
				init_time = getTime();
				last_time = getTime() - real_init_time;
			}
		};
		float SPEED;
		float OFFSET;
		const float length = 27.50f;
		vector <Block> block_group;
		Texture2D texture_background;
		Texture2D texture_tap;
		Texture2D texture_tap_effect;
		Texture2D texture_pure_effect;
		Texture2D texture_far_effect;
		Texture2D texture_lost_effect;
		Music song;
		Camera camera;
		KeyboardKey tem_keyboard[4] = {KEY_D, KEY_F, KEY_J, KEY_K};
		void update_Block(vector<Block> & block_list){
			for(int i=0;i<4;i++){
				if (IsKeyPressed(tem_keyboard[i])&&(status!=PLAY_STALL)&&(!waiting)) 
					block_list.push_back(Block(getTime(),i));
				if (IsKeyDown(tem_keyboard[i])&&(status!=PLAY_STALL)&&(!waiting)){
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
		void draw_block(float t,int i,float k){
		   	float y = 0;    // to avoid warning
		    switch (i)
		    {
		    case 3:
		        y=-2.6;
		        break;
		    case 2:
		        y=-0.85;
		        break;
		    case 1:
		        y=0.85;
		        break;
		    case 0:
		        y=2.6;
		        break;
		    }
		    if(fabs(k)<2.0f){
		        DrawCubeTexture(texture_tap, { 1.3f-t, -0.2f, y }, 0.5f, 0.5f, 1.57f, SKYBLUE);
		    }
		    else{
		        DrawCubeTexture(texture_tap, { 1.3f-t, -0.2f, y }, fabs(k), 0.5f, 1.57f, {0, 233, 0, 255});
		    }
		};
		void input(string filename){
		    FILE * fp = NULL;
		    fp = fopen(filename.c_str(), "r");
		    if(!fp){
		        printf("[ERROR] render file open error!\n");
				printf("[INFO] filePath: %s\n", filename.c_str());
		        exit(1);
		    }

		    block_group.clear();    // 清空当前的

		    char line[100];
		    while(!feof(fp)){
		        fgets(line, 100, fp);
		        //第一个数表示block出现时间,第二个数表示block属于第几列,第三个数表示block的持续时间.
		        Block B(0,0);
		        string s="";
		        int i=0;
		        while(line[i]!=' '){
		            s+=line[i];
		            i++;
		        }
		        i++;
		        B.init_time=stof(s)-length/SPEED;
		        s="";
		        while(line[i]!=' '){
		            s+=line[i];
		            i++;
		        }
		        B.column=stoi(s)-1;
		        s="";
		        i++;
		        while(line[i]!=' '&&line[i]!='\n'){
		            s+=line[i];
		            i++;
		        }    
		        B.last_time=stof(s);
		        block_group.push_back(B);
		    }

			fclose(fp);
		}
		void show_effect(string typ, int trackNum){
		    Vector2 pos;
		    if(typ == "pure" || typ == "far" || typ == "lost") {
		        if(trackNum == 0) {
		            pos = {25.0f, 660.0f};
		        } else if (trackNum == 1) {
		            pos = {420.0f, 660.0f};
		        } else if (trackNum == 2) {
		            pos = {800.0f, 660.0f};
		        } else if (trackNum == 3) {
		            pos = {1180.0f, 660.0f};
		        }
		        if(typ == "pure") {
		            curEffects.push_back(Effect(texture_pure_effect, pos, true));
		        } else if(typ == "far") {
		            curEffects.push_back(Effect(texture_far_effect, pos, true));
		        } else if(typ == "lost") {
		            curEffects.push_back(Effect(texture_lost_effect, pos, true));
		        }
		    }
		};
		void save(vector <Block> &block_group){
		    FILE *fp;
			string path;
			int highscore = 0;

			string opernbak = SELECTED_OPERN;

			// 创造模式不需要存储最高分，游玩模式不需要存储scores
			if(mode == 0) {
				SELECTED_OPERN = "saved";
				//todo 创建文件夹
				// path = string(GetWorkingDirectory())  +  "\\..\\songs\\" + SELECTED_SONG + "\\" + SELECTED_OPERN;
				// string command = "mkdir " + path;
				// printf("[INFO] %s\n", command.c_str());
				// if(access((path+"\\score.txt").c_str(), F_OK) != -1);
				// 	system(command.c_str());
				// printf("[INFO] mkdir Done!");
				//todo 修改为用户名
				path = "../songs/" + SELECTED_SONG + "/" + SELECTED_OPERN + ".txt";
				printf("[INFO] %s\n", path.c_str());
				fp = fopen(path.c_str(), "w+");
				int bgsize = block_group.size();
				for(int i=0; i<bgsize; i++){
					if(i) fprintf(fp, "\n");
					fprintf(fp,"%f %d %f", block_group[i].init_time, block_group[i].column+1, block_group[i].last_time);
				}
				
				fclose(fp);

				SELECTED_OPERN = opernbak;

				string music_sampled ="../score/song_sampled/"+SELECTED_SONG+"_sampled.txt";
				//printf("%s\n",music_sampled.c_str());
				//printf("%s\n",path.c_str());
				createScore=score(path.c_str(),music_sampled.c_str(),0)*10000000;

			} else if(mode == 1) {
				path = "../songs/" + SELECTED_SONG + "/" + SELECTED_OPERN + "/score.txt";
				printf("[INFO] %s\n", path.c_str());
				// if(access(path.c_str(), F_OK) != -1) {
				// 	fp = fopen(path.c_str(), "r");
				// 	char line[100];
				// 	fgets(line, 100, fp);
				// 	highscore = atoi(line);
				// }
				if(scoreboard.get_score() >= highscore) {
					fp = fopen(path.c_str(), "w+");
					if(!fp){
						printf("[ERROR] render file open error!\n");
						exit(1);
					}
					fprintf(fp, "%d\n%.2f", scoreboard.get_score(), scoreboard.get_acc());
					fclose(fp);
				}
			}
		}
		void draw_frame(int mode,vector <Block> &block_group){
			if(status == PLAY_NORMAL)
				play_repeat(song);
		    //制作模式
		    if(mode == 0){
		        BeginDrawing();
		        ClearBackground(GRAY);
		        DrawTextureEx(texture_background, { 0, 0 }, 0.0f, 1.0f, WHITE);
		        BeginMode3D(camera);

		        DrawPlane({ 0.0f, 0.0f, 0.0f }, { 1000.0f, 7.17f }, {255, 255, 255, 120}); // Draw ground
		        DrawCubeWires({ 0.0f, -0.7f, 0.8f }, 1000.0f, 2.0f, 1.6f, LIGHTGRAY);
		        DrawCubeWires({ 0.0f, -0.7f, 2.4f }, 1000.0f, 2.0f, 1.6f, LIGHTGRAY);
		        DrawCubeWires({ 0.0f, -0.7f, -0.8f }, 1000.0f, 2.0f, 1.6f, LIGHTGRAY);
		        DrawCubeWires({ 0.0f, -0.7f, -2.4f }, 1000.0f, 2.0f, 1.6f, LIGHTGRAY);

		        if(isKeyPressed(tem_keyboard[1])&&(status!=PLAY_STALL)&&(!waiting))
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, 0.85f }, 0.5f, 0.9f, 1.57f, BLUE);
		        else
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, 0.85f }, 0.5f, 1.0f, 1.57f, WHITE);
		        if(isKeyPressed(tem_keyboard[0])&&(status!=PLAY_STALL)&&(!waiting))
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, 2.6f }, 0.5f, 0.9f, 1.5f, BLUE);
		        else
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, 2.6f }, 0.5f, 1.0f, 1.5f, WHITE);
		        if(isKeyPressed(tem_keyboard[2])&&(status!=PLAY_STALL)&&(!waiting))
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, -0.85f }, 0.5f, 0.9f, 1.57f, BLUE);
		        else
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, -0.85f }, 0.5f, 1.0f, 1.57f, WHITE);
		        if(isKeyPressed(tem_keyboard[3])&&(status!=PLAY_STALL)&&(!waiting))
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, -2.6f }, 0.5f, 0.9f, 1.5f, BLUE);    
		        else
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, -2.6f }, 0.5f, 1.0f, 1.5f, WHITE);    
		        for(auto i:block_group){
		            draw_block((getTime()-i.init_time+i.last_time/2)*SPEED+0.5f,i.column,-i.last_time*SPEED);
		        }

		        EndMode3D();
				if(waiting){
					DrawText(TextFormat("Start :%.2fs", length/SPEED-GetMusicTimePlayed(song)), 560, 300, 90, YELLOW);
				}
		        // DrawRectangle( 10, 10, 220, 70, Fade(SKYBLUE, 0.5f));
				DrawText(TextFormat("%.2fs/%.2fs", GetMusicTimePlayed(song), GetMusicTimeLength(song)), 50, 40, 40, PURPLE);
		        // DrawRectangleLines( 10, 10, 220, 70, BLUE);

		        // 绘制特效
		        //for(auto& effect: curEffects) {
		        //   effect.draw();
		        //}

		        // score board:
		        //scoreboard.draw();
		    }
		    else{
		        //游玩模式
		        BeginDrawing();
		        ClearBackground(GRAY);
		        DrawTextureEx(texture_background, { 0, 0 }, 0.0f, 1.0f, WHITE);
		        
		        BeginMode3D(camera);

		        DrawPlane({ 0.0f, 0.0f, 0.0f }, { 1000.0f, 7.17f }, {255, 255, 255, 120}); // Draw ground
		        DrawCubeWires({ 0.0f, -0.7f, 0.8f }, 1000.0f, 2.0f, 1.6f, LIGHTGRAY);
		        DrawCubeWires({ 0.0f, -0.7f, 2.4f }, 1000.0f, 2.0f, 1.6f, LIGHTGRAY);
		        DrawCubeWires({ 0.0f, -0.7f, -0.8f }, 1000.0f, 2.0f, 1.6f, LIGHTGRAY);
		        DrawCubeWires({ 0.0f, -0.7f, -2.4f }, 1000.0f, 2.0f, 1.6f, LIGHTGRAY);

		        if(IsKeyDown(tem_keyboard[1])&&(status!=PLAY_STALL)&&(!waiting))
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, 0.85f }, 0.5f, 0.9f, 1.57f, BLUE);
		        else
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, 0.85f }, 0.5f, 1.0f, 1.57f, WHITE);
		        if(IsKeyDown(tem_keyboard[0])&&(status!=PLAY_STALL)&&(!waiting))
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, 2.6f }, 0.5f, 0.9f, 1.5f, BLUE);
		        else
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, 2.6f }, 0.5f, 1.0f, 1.5f, WHITE);
		        if(IsKeyDown(tem_keyboard[2])&&(status!=PLAY_STALL)&&(!waiting))
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, -0.85f }, 0.5f, 0.9f, 1.57f, BLUE);
		        else
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, -0.85f }, 0.5f, 1.0f, 1.57f, WHITE);
		        if(IsKeyDown(tem_keyboard[3])&&(status!=PLAY_STALL)&&(!waiting))
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, -2.6f }, 0.5f, 0.9f, 1.5f, BLUE);    
		        else
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, -2.6f }, 0.5f, 1.0f, 1.5f, WHITE);    

		        auto i=block_group.begin(); 
		        while(i!=block_group.end()){
		            //单个节奏块
		            float dis = length-(getTime()-i->init_time-OFFSET)*SPEED;
		            // 1.2 >= dis >=0.7 lost
		            // 0.7 >= dis >=0.5 far
		            // 0.5 >= dis >=0.3 pure
		            // 0.3 >= dis >=0.1 far 
		            // 0.1 >= dis >=0.0 lost
		            if(i->last_time*SPEED<2.0f){
		                if(IsKeyPressed(tem_keyboard[i->column])&&(status!=PLAY_STALL)&&(!waiting)&&dis<=1.8f&&dis>=-1.2f){
		                    //正确地消除
		                    if(dis>=1.6f){
		                        show_effect("lost",i->column);
		                        scoreboard.update("lost");
		                    }
		                    else if(dis>=1.3f){
		                        show_effect("far",i->column);
								play_once(taps[0]);
		                        scoreboard.update("far");
		                    }
		                    else if(dis>=0.0f){
		                        show_effect("pure",i->column);
								play_once(taps[0]);
		                        scoreboard.update("pure");
		                    }
		                    else if(dis>=-0.6f){
		                        show_effect("far",i->column);
								play_once(taps[0]);
		                        scoreboard.update("far");
		                    }
		                    else{
		                        show_effect("lost",i->column);
								play_once(taps[0]);
		                        scoreboard.update("lost");
		                    }
		                    block_group.erase(i);
		                }
		                else{
		                    if(dis>=-1.6f){
		                        draw_block(length-(getTime()-i->init_time)*SPEED,i->column,i->last_time*SPEED);
		                        i++;
		                    }
		                    else{
		                            show_effect("lost",i->column);
		                            scoreboard.update("lost");
		                            block_group.erase(i);                        
		                    }
		                }
		            }            
		            else{
		                float start_dis = -length+(getTime()-i->init_time+i->last_time/2 - OFFSET)*SPEED+0.2f;
		                float end_dis = -length+(getTime()-i->init_time-i->last_time/2 - OFFSET)*SPEED+0.2f;
		                if(i->to_be_erase){
		                    if(end_dis<=0.0f){
		                        draw_block(length-(getTime()-i->init_time)*SPEED,i->column,i->last_time*SPEED);
		                        i++;              
		                    }   
		                    else{
		                        block_group.erase(i);
		                    }          
		                }
		                else{
		                    if(IsKeyPressed(tem_keyboard[i->column])&&(status!=PLAY_STALL)&&(!waiting)&&start_dis>=-0.2f&&start_dis<=0.9f){
		                        //正确地消除
		                        if(start_dis>=0.8f){
		                            show_effect("lost",i->column);
		                            scoreboard.update("lost");
		                        }
		                        else if(start_dis>=0.7f){
		                            show_effect("far",i->column);
									play_once(taps[0]);
		                            scoreboard.update("far");
		                        }
		                        else if(start_dis>=0.2f){
		                            show_effect("pure",i->column);
									play_once(taps[0]);
		                            scoreboard.update("pure");
		                        }
		                        else if(start_dis>=-0.1f){
		                            show_effect("far",i->column);
									play_once(taps[0]);
		                            scoreboard.update("far");
		                        }
		                        else{
		                            show_effect("lost",i->column);
									play_once(taps[0]);
		                            scoreboard.update("lost");
		                        }    
                                // block_group.erase(i);             
		                    }
		                    if(IsKeyDown(tem_keyboard[i->column])&&(status!=PLAY_STALL)&&(!waiting)&&start_dis>=0.0f){
		                        //if(end_dis>=0.5f){
		                        //    show_effect("lost",i->column);
		                        //    block_group.erase(i);
		                        //}
		                        if(end_dis<=0.0f){
		                            draw_block((i->last_time*SPEED-(-length+(getTime()-i->init_time+i->last_time/2)*SPEED+0.2f))/2,i->column,i->last_time*SPEED-(-length+(getTime()-i->init_time+i->last_time/2)*SPEED+0.2f));
		                            i++;
		                        }
		                        else{
		                            show_effect("pure",i->column);
									play_once(taps[0]);
		                            scoreboard.update("pure");
		                            block_group.erase(i);
		                        }
		                    }
		                    else if(IsKeyReleased(tem_keyboard[i->column])&&(status!=PLAY_STALL)&&(!waiting)&&start_dis>=0.0f){
		                        if(end_dis<0.0f){
		                            float dis=-end_dis;
		                            if(dis>=1.0f){
		                                show_effect("lost",i->column);
		                                scoreboard.update("lost");
		                            }
		                            else if(dis>=0.5){
		                                show_effect("far",i->column);
										play_once(taps[0]);
		                                scoreboard.update("far");
		                            }
		                            else{
		                                show_effect("pure",i->column);
										play_once(taps[0]);
		                                scoreboard.update("pure");
		                            }
		                            i->to_be_erase=true;
		                            draw_block(length-(getTime()-i->init_time)*SPEED,i->column,i->last_time*SPEED);
		                            i++;
		                        }
                                else{
                                    block_group.erase(i);
                                }
		                    }
		                    else{
		                        if(end_dis<=1.0f){
		                            draw_block(length-(getTime()-i->init_time)*SPEED,i->column,i->last_time*SPEED);
		                            i++;              
		                        }   
		                        else{
		                            show_effect("lost",i->column);
		                            scoreboard.update("lost");
		                            block_group.erase(i);
		                        }   
		                    }
		                }
		            }
		        }

		        EndMode3D();

		        // DrawRectangle( 10, 10, 220, 70, Fade(SKYBLUE, 0.5f));
				DrawText(TextFormat("%.2fs/%.2fs", GetMusicTimePlayed(song), GetMusicTimeLength(song)), 50, 40, 40, PURPLE);
		        // DrawRectangleLines( 10, 10, 220, 70, BLUE);

		        // 绘制特效
		        for(auto& effect: curEffects) {
		            effect.draw();
		        }
		        // DrawTextureRec(texture_tap_effect, frameRec_tap_effect, TRACK1, WHITE);  // Draw part of the texture
		        // DrawTextureRec(texture_tap_effect, frameRec_tap_effect, TRACK2, WHITE);  // Draw part of the texture
		        // DrawTextureRec(texture_tap_effect, frameRec_tap_effect, TRACK3, WHITE);  // Draw part of the texture
		        // DrawTextureRec(texture_tap_effect, frameRec_tap_effect, TRACK4, WHITE);  // Draw part of the texture 

		        // score board:
		        scoreboard.draw();

		    }
			if(status==PLAY_STALL){
				DrawRectangle( 0, 50, 1700, 700, Fade(BLACK, 0.5f));
			}
		    EndDrawing();  			
		}
		void init_song() {
			string songPath = "../songs/" + SELECTED_SONG + ".wav";
			// printf("[INFO] songPath=%s\n", songPath.c_str());
			string opernPath = "../songs/" + SELECTED_SONG + "/" + SELECTED_OPERN + ".txt";
			if(MODE == 1) input(opernPath);
			song = LoadMusicStream(songPath.c_str());
			//todo 这里并不能这样，因为一个hold并不算作1个note
			scoreboard = ScoreBoard(block_group.size());    		
		}
    public:
        void init(){
		   	InitAudioDevice();
			init_BGM_play();
			waiting=false;
			MODE = (int)mode;
		    //const int screenWidth = 1600;
		    //const int screenHeight = 900;
			status = PLAY_NORMAL;
		    block_group.clear();
			zero_time=GetTime();
			createScore = 0;
			SPEED=15.0f;
			OFFSET=0.05f;

			init_song();

		    init_taps();
		    //InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera first person");
		    // Load Textures
		    texture_background = LoadTexture("resources/single_conflict_resized.png");
		    texture_tap = LoadTexture("resources/tap-v1.png");
		    texture_tap_effect = LoadTexture("resources/tap-effect.png");
		    texture_pure_effect = LoadTexture("resources/pure-effect.png");
		    texture_far_effect = LoadTexture("resources/far-effect.png");
		    texture_lost_effect = LoadTexture("resources/lost-effect.png");

		    // Define the camera to look into our 3d world (position, target, up vector)
		    camera.position = { 2.0f, 2.8f, 0.0f };
		    camera.target = { 0.0f, 0.75f, 0.0f };
		    camera.up = { 0.0f, 0.5f, 0.0f };
		    camera.fovy = 80.0f;
		    camera.projection = CAMERA_PERSPECTIVE;
		    SetCameraMode(camera, CAMERA_CUSTOM); 

		    SetTargetFPS(60);                           // Set our game to run at 60 frames-per-second
        }
        void update(){
	        for(list<Effect>::iterator it = curEffects.begin(); it != curEffects.end(); ++it) {
	            // 所有特效都理应只播放一次
	            if(it->update()) {
	                curEffects.erase(it);
	            }
	        }
			if(GetMusicTimePlayed(song)<=length/SPEED-0.1)
				waiting = true;
			else
				waiting = false;
	        if(MODE!=1)
	            update_Block(block_group);
			//根据按键或鼠标操作控制暂停/返回上一界面/重新开始
			if(IsKeyPressed(KEY_ENTER)){
				if(status==PLAY_NORMAL){
					start_time=GetTime();
					status=PLAY_STALL;
				}
				else if(status==PLAY_STALL){
					status=PLAY_NORMAL;
				}
			}
			if(status==PLAY_STALL){
				zero_time+=GetTime()-start_time;
				start_time=GetTime();
			}
			if(IsKeyPressed(KEY_Q))
				status=PLAY_BACK;
			if(IsKeyPressed(KEY_R)){
				status=PLAY_NORMAL;

				init_BGM_play();

				zero_time=GetTime();
				block_group.clear();

				init_song();
			}
			if(GetMusicTimePlayed(song) >= GetMusicTimeLength(song) - 0.1) {
				status = PLAY_FINISH;
			}
        }
        void draw(){
        	draw_frame(MODE,block_group);
        }
		bool is_end(){
			if(status==PLAY_NORMAL||status==PLAY_STALL||status==PLAY_AGAIN)
				return false;
			else
				return true;
		}
		InterfaceState end(){
			if(status==PLAY_BACK){
				UnloadTexture(texture_background);
				UnloadTexture(texture_tap);    
				UnloadTexture(texture_tap_effect);
				UnloadTexture(texture_pure_effect);    
				UnloadTexture(texture_far_effect);
				UnloadTexture(texture_lost_effect);	

				return INTERFACE_STATE_MUSIC_SWITCH;
			}
			else if(status==PLAY_FINISH){
				save(block_group);
				return INTERFACE_STATE_SUMMARY;
			}
			//CloseWindow();        // Close window and OpenGL context
			return INTERFACE_STATE_NULL;
		}
};

double InterfacePlay::zero_time = 0.0f;
double InterfacePlay::start_time = 0.0f;
double InterfacePlay::end_time = 0.0f;

#endif