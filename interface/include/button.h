#include "raylib.h"

#ifndef __BUTTON_H__
#define __BUTTON_H__

class Button {
    private:
        
    public:
        Rectangle bound;
        Button(float x_topleft, float y_topleft, float width, float height);
        bool isClicked(MouseButton mousebutton = MOUSE_LEFT_BUTTON);
};

#endif