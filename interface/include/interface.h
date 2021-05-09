#ifndef __INTERFACE_H__
#define __INTERFACE_H__
#include "raylib.h"
#include "button.h"
#include <string>
using namespace std;

#define DEBUG 1

typedef enum {
    INTERFACE_STATE_NULL, 
    INTERFACE_STATE_MAIN, 
    INTERFACE_STATE_MUSIC_SWITCH, 
    INTERFACE_STATE_PLAY,
    INTERFACE_STATE_GENERATE,
    INTERFACE_STATE_SUMMARY,
    INTERFACE_STATE_TEST, // ball drop
    INTERFACE_STATE_TOT
} InterfaceState;

typedef enum {
    MODE_GENERATE,
    MODE_PLAY,
    MODE_NULL
} ModeState;

class InterfaceBase {
    private:
        static Button bt_goback;
    public:
        static const int screenWidth = 1600;
        static const int screenHeight = 900;

        virtual void init();
        virtual void update();
        virtual void draw();
        virtual InterfaceState end();
        virtual bool is_end();

        static void draw_goback_button(InterfaceState prev_interface);
};

// just fot test
class InterfaceTest: public InterfaceBase {
    private:
        static const InterfaceState origin_state = INTERFACE_STATE_TEST;
        Vector2 pos;
    public:
        InterfaceTest();
        void init();
        void update();
        void draw();
        InterfaceState end();
        bool is_end();
};

class InterfaceMain: public InterfaceBase {
    private:
        static const InterfaceState origin_state = INTERFACE_STATE_MAIN;
        Texture2D background;
    public:

        InterfaceMain();
        void init();
        void update();
        void draw();
        InterfaceState end();
        bool is_end();
};

class ScoreBoard{
public:
	int totNotes;
	int maxCombo = 0;
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
		return (pure + 0.5f*far)*100 / (double)(pure + far + lost);
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
		maxCombo = max(maxCombo, combo);
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
	void init() {
		totNotes = 0;
		combo = maxCombo = 0;
		pure = far = lost = 0;
	}
};

#endif
