#include "raylib.h"
#include "button.h"
#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#define DEBUG 0

typedef enum {
    INTERFACE_STATE_NULL, 
    INTERFACE_STATE_MAIN, 
    INTERFACE_STATE_MODE_SWITCH, 
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
    public:
        static const int screenWidth = 1600;
        static const int screenHeight = 900;

        virtual void init();
        virtual void update();
        virtual void draw();
        virtual void end();
};

// just fot test
class InterfaceTest: public InterfaceBase {
    private:
        Vector2 pos;
    public:
        InterfaceTest();
        void init();
        void update();
        void draw();
        void end();
};

class InterfaceMain: public InterfaceBase {
    private:
    public:
        Button bt_start;
        Button bt_quit;

        InterfaceMain();
        void init();
        void update();
        void draw();
        void end();
};

class InterfaceModeSwitch: public InterfaceBase {
    private:
    public:
        Button bt_play;
        Button bt_generate;

        InterfaceModeSwitch();
        void init();
        void update();
        void draw();
        void end();
};

class InterfaceMusicSwitch: public InterfaceBase {
    private:
    public:
        InterfaceMusicSwitch();
        void init();
        void update();
        void draw();
        void end();
};



#endif
