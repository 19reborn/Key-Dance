#ifndef __BUTTON_H__
#define __BUTTON_H__
#include "raylib.h"

typedef enum {
    BUTTON_STATE_NULL,
    BUTTON_STATE_FREE,
    BUTTON_STATE_HOLD,
    BUTTON_STATE_CLICKED
} ButtonState;

class Button {
    private:
        ButtonState button_state;
    public:
        Rectangle bound;
        Button(float x_topleft, float y_topleft, float width, float height);
        bool isClicked(MouseButton mousebutton = MOUSE_LEFT_BUTTON);
};

#endif