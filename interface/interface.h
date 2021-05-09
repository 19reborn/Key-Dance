#include "raylib.h"
#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#define DEBUG 0

typedef enum {
    INTERFACE_STATE_NULL, 
    INTERFACE_STATE_MAIN, 
    INTERFACE_STATE_MODE_SWITCH, 
    INTERFACE_STATE_MUSIC_SWITCH, 
    INTERFACE_STATE_SUMMARY,
    INTERFACE_STATE_TEST, // ball drop
    INTERFACE_STATE_TOT
} InterfaceState;

class InterfaceBase {
    public:
        static const int screenWidth = 800;
        static const int screenHeight = 450;

        virtual void init();
        virtual void update();
        virtual void draw();
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
};

class InterfaceTest: public InterfaceBase {
    private:
    public:
        InterfaceTest();
        void init();
        void update();
        void draw();
};


#endif
