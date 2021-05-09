#include "raylib.h"
#include "button.h"
#ifndef __INTERFACE_H__
#define __INTERFACE_H__

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

#endif
