#include "raylib.h"

#ifndef __BUTTON_H__
#define __BUTTON_H__

typedef enum {
    BUTTON_STATE_NULL,
    BUTTON_STATE_FREE,
    BUTTON_STATE_HOLD,
    BUTTON_STATE_CLICKED
} ButtonState;

class Button {
    private:
        ButtonState b
    public:
        Rectangle bound;
        Button(float x_topleft, float y_topleft, float width, float height);
        bool isClicked(MouseButton mousebutton = MOUSE_LEFT_BUTTON);
};

#endif