#include "interface.h"
#include "raylib.h"
#include "../backend/block_build.cc"
#include "../backend/music_switch.cc"
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <list>
using namespace std;

class InterfacePlay: public InterfaceBase{
	private:
		bool isKeyDown(KeyboardKey &key){
			if(IsKeyDown(key)){
				play_repeat(taps[1]);
				return true;
			}
			return false;
		}
		bool isKeyPressed(KeyboardKey &key){
			if(IsKeyPressed(key)){
				play_once(taps[1]);
				return true;
			}
			return false;
		}
		bool isKeyReleased(KeyboardKey &key){
			if(IsKeyReleased(key)){
				play_once(taps[3]);
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
		class ScoreBoard{
			public:
			    int totNotes;
			    int combo = 0;
			    int pure = 0;
			    int far = 0;
			    int lost = 0;
			    ScoreBoard() {}
			    ScoreBoard(int tot): totNotes(tot) {}
			    int get_score() {
			        int perScore = 10000000 / totNotes + 1;
			        return min(perScore * pure + perScore * far / 2, 10000000);
			    }
			    double get_acc() {
			        if(pure + far + lost == 0) return 0;
			        return (pure + 0.5f*far) / (double)(pure + far + lost);
			    }
			    void update(string grade) {
			        if(grade == "pure") {
			            combo++;
			            pure++;
			        } else if(grade == "far") {
			            combo++;
			            far++;
			        } else if(grade == "lost") {
			            lost++;
			            combo = 0;
			        } else {
			            printf("[ERROR] Wrong Grade!\n");
			        }
			    }
			    void draw() {
			        DrawText(TextFormat("SCORE: %08i", get_score()), 1235, 10, 40, LIME);
			        if(combo < 50) {
			            DrawText(TextFormat("%i COMBO", combo), 600, 560, 80, VIOLET);
			        } else if(combo < 100) {
			            DrawText(TextFormat("%i COMBO!", combo), 600, 560, 80, PURPLE);
			        } else {
			            DrawText(TextFormat("%i COMBO!!!", combo), 600, 560, 80, PINK);
			        }
			        DrawText(TextFormat("PURE: %i", pure), 1350, 50, 40, PINK);
			        DrawText(TextFormat("FAR: %i", far), 1350, 90, 40, ORANGE);
			        DrawText(TextFormat("LOST: %i", lost), 1350, 130, 40, GRAY);
			        DrawText(TextFormat("ACC: %.2f%%", get_acc()), 1350, 170, 40, MAROON);
			    }
			} scoreboard;
		int SPEED;
		int OFFSET;
		const int length;
		vector <Block> block_group;
		Texture2D texture_background;
		Texture2D texture_tap;
		Texture2D texture_tap_effect;
		Texture2D texture_pure_effect;
		Texture2D texture_far_effect;
		Texture2D texture_lost_effect;
		Camera camera;
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
		    if(fabs(k)<0.5f){
		        DrawCubeTexture(texture_tap, { 1.3f-t, -0.2f, y }, 0.5f, 0.5f, 1.57f, SKYBLUE);
		    }
		    else{
		        DrawCubeTexture(texture_tap, { 1.3f-t, -0.2f, y }, fabs(k), 0.5f, 1.57f, {0, 233, 0, 255});
		    }
		};
		void input(string filename){
		    FILE * fp = NULL;
		    fp = fopen(filename.c_str(),"r");
		    if(!fp){
		        printf("file open error!\n");
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
		        B.init_time=stof(s);
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
		    fp = fopen("./out","w");
		    for(auto i:block_group){
		        fprintf(fp,"%f %d %f\n",i.init_time,i.column,i.last_time);
		    }
		}
		void draw_frame(int mode,vector <Block> &block_group){
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

		        if(isKeyDown(tem_keyboard[1]))
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, 0.85f }, 0.5f, 0.9f, 1.57f, BLUE);
		        else
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, 0.85f }, 0.5f, 1.0f, 1.57f, WHITE);
		        if(isKeyDown(tem_keyboard[0]))
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, 2.6f }, 0.5f, 0.9f, 1.5f, BLUE);
		        else
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, 2.6f }, 0.5f, 1.0f, 1.5f, WHITE);
		        if(isKeyDown(tem_keyboard[2]))
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, -0.85f }, 0.5f, 0.9f, 1.57f, BLUE);
		        else
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, -0.85f }, 0.5f, 1.0f, 1.57f, WHITE);
		        if(isKeyDown(tem_keyboard[3]))
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, -2.6f }, 0.5f, 0.9f, 1.5f, BLUE);    
		        else
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, -2.6f }, 0.5f, 1.0f, 1.5f, WHITE);    

		        for(auto i:block_group){
		            draw_block((GetTime()-i.init_time+i.last_time/2)*SPEED+0.5f,i.column,-i.last_time*SPEED);
		        }

		        EndMode3D();

		        DrawRectangle( 10, 10, 220, 70, Fade(SKYBLUE, 0.5f));
		        DrawRectangleLines( 10, 10, 220, 70, BLUE);

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

		        if(isKeyDown(tem_keyboard[1]))
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, 0.85f }, 0.5f, 0.9f, 1.57f, BLUE);
		        else
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, 0.85f }, 0.5f, 1.0f, 1.57f, WHITE);
		        if(isKeyDown(tem_keyboard[0]))
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, 2.6f }, 0.5f, 0.9f, 1.5f, BLUE);
		        else
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, 2.6f }, 0.5f, 1.0f, 1.5f, WHITE);
		        if(isKeyDown(tem_keyboard[2]))
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, -0.85f }, 0.5f, 0.9f, 1.57f, BLUE);
		        else
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, -0.85f }, 0.5f, 1.0f, 1.57f, WHITE);
		        if(isKeyDown(tem_keyboard[3]))
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, -2.6f }, 0.5f, 0.9f, 1.5f, BLUE);    
		        else
		            DrawCubeTexture(texture_tap, { 1.3f, -0.4f, -2.6f }, 0.5f, 1.0f, 1.5f, WHITE);    

		        auto i=block_group.begin(); 
		        while(i!=block_group.end()){
		            //单个节奏块
		            float dis = length-(GetTime()-i->init_time-OFFSET)*SPEED;
		            // 1.2 >= dis >=0.7 lost
		            // 0.7 >= dis >=0.5 far
		            // 0.5 >= dis >=0.3 pure
		            // 0.3 >= dis >=0.1 far 
		            // 0.1 >= dis >=0.0 lost
		            if(i->last_time*SPEED<0.5f){
		                if(isKeyPressed(tem_keyboard[i->column])&&dis<=0.9f&&dis>=-0.2f){
		                    //printf("%f\n",dis);
		                    //正确地消除
		                    if(dis>=0.8f){
		                        show_effect("lost",i->column);
		                        scoreboard.update("lost");
		                    }
		                    else if(dis>=0.7f){
		                        show_effect("far",i->column);
		                        scoreboard.update("far");
		                    }
		                    else if(dis>=0.2f){
		                        show_effect("pure",i->column);
		                        scoreboard.update("pure");
		                    }
		                    else if(dis>=-0.1f){
		                        show_effect("far",i->column);
		                        scoreboard.update("far");
		                    }
		                    else{
		                        show_effect("lost",i->column);
		                        scoreboard.update("lost");
		                    }
		                    block_group.erase(i);
		                }
		                else{
		                    if(dis>=-0.8f){
		                        draw_block(length-(GetTime()-i->init_time)*SPEED,i->column,i->last_time*SPEED);
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
		                float start_dis = -length+(GetTime()-i->init_time+i->last_time/2 - OFFSET)*SPEED+0.2f;
		                float end_dis = -length+(GetTime()-i->init_time-i->last_time/2 - OFFSET)*SPEED+0.2f;
		                if(i->to_be_erase){
		                    if(end_dis<=0.0f){
		                        draw_block(length-(GetTime()-i->init_time)*SPEED,i->column,i->last_time*SPEED);
		                        i++;              
		                    }   
		                    else{
		                        block_group.erase(i);
		                    }          
		                }
		                else{
		                    if(isKeyPressed(tem_keyboard[i->column])&&start_dis>=-0.2f&&start_dis<=0.9f){
		                        //printf("%f\n",dis);
		                        //正确地消除
		                        if(start_dis>=0.8f){
		                            show_effect("lost",i->column);
		                            scoreboard.update("lost");
		                        }
		                        else if(start_dis>=0.7f){
		                            show_effect("far",i->column);
		                            scoreboard.update("far");
		                        }
		                        else if(start_dis>=0.2f){
		                            show_effect("pure",i->column);
		                            scoreboard.update("pure");
		                        }
		                        else if(start_dis>=-0.1f){
		                            show_effect("far",i->column);
		                            scoreboard.update("far");
		                        }
		                        else{
		                            show_effect("lost",i->column);
		                            scoreboard.update("lost");
		                        }                 
		                    }
		                    if(isKeyDown(tem_keyboard[i->column])&&start_dis>=0.0f){
		                        //if(end_dis>=0.5f){
		                        //    show_effect("lost",i->column);
		                        //    block_group.erase(i);
		                        //}
		                        if(end_dis<=0.0f){
		                            draw_block((i->last_time*SPEED-(-length+(GetTime()-i->init_time+i->last_time/2)*SPEED+0.2f))/2,i->column,i->last_time*SPEED-(-length+(GetTime()-i->init_time+i->last_time/2)*SPEED+0.2f));
		                            i++;
		                        }
		                        else{
		                            show_effect("pure",i->column);
		                            scoreboard.update("pure");
		                            block_group.erase(i);
		                        }
		                    }
		                    else if(isKeyReleased(tem_keyboard[i->column])&&start_dis>=0.0f){
		                        if(end_dis<0.0f){
		                            float dis=-end_dis;
		                            if(dis>=1.0f){
		                                show_effect("lost",i->column);
		                                scoreboard.update("lost");
		                            }
		                            else if(dis>=0.5){
		                                show_effect("far",i->column);
		                                scoreboard.update("far");
		                            }
		                            else{
		                                show_effect("pure",i->column);
		                                scoreboard.update("pure");
		                            }
		                            i->to_be_erase=true;
		                            draw_block(length-(GetTime()-i->init_time)*SPEED,i->column,i->last_time*SPEED);
		                            i++;
		                        }
		                    }
		                    else{
		                        if(end_dis<=1.0f){
		                            draw_block(length-(GetTime()-i->init_time)*SPEED,i->column,i->last_time*SPEED);
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

		        DrawCube({ 1.3f-27.50f, -0.4f, 0.85f }, 0.5f, 1.0f, 1.57f, BLUE);

		        EndMode3D();

		        DrawRectangle( 10, 10, 220, 70, Fade(SKYBLUE, 0.5f));
		        DrawRectangleLines( 10, 10, 220, 70, BLUE);

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
		    EndDrawing();  			
		}
		void init_song(string songName){
			input(songName);
			//todo 这里并不能这样，因为一个hold并不算作1个note
			scoreboard = ScoreBoard(block_group.size());    			
		}
    public:
        void init(int mode):MODE(mode){
		    const int screenWidth = 1600;
		    const int screenHeight = 900;
		    block_group.clear();
		    if(MODE==1){
		        init_song("./tmp.txt");
		    }
		    InitAudioDevice();
		    init_taps();
		    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera first person");
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
	        if(MODE!=1)
	            update_Block(block_group);
        }
        void draw(){
        	draw_frame(MODE,block_group);
        }
		void end(){
			UnloadTexture(texture_background);
			UnloadTexture(texture_tap);    
			UnloadTexture(texture_tap_effect);
			UnloadTexture(texture_pure_effect);    
			UnloadTexture(texture_far_effect);
			UnloadTexture(texture_lost_effect);

			//CloseWindow();        // Close window and OpenGL context

			save(block_group);			
		}
};