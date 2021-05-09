#include "button.h"
#include "interface.h"
#include <cstdio>

extern InterfaceState state;

Button::Button(float x_topleft, float y_topleft, float width, float height)
{
    bound = {x_topleft, y_topleft, width, height};
    button_state = BUTTON_STATE_FREE;
}

bool Button::isClicked(MouseButton mousebutton) {
    Vector2 mousePoint = GetMousePosition();
    bool collision = CheckCollisionPointRec(mousePoint, bound);
    bool down = IsMouseButtonDown(mousebutton);
    bool up = IsMouseButtonUp(mousebutton);
    bool clicked = false;
    switch (button_state)
    {
    case BUTTON_STATE_FREE:
        if (collision && down)
            button_state = BUTTON_STATE_HOLD;
        break;
    case BUTTON_STATE_HOLD:
        if (collision && up)
            button_state = BUTTON_STATE_CLICKED;
        else if (!collision && up)
            button_state = BUTTON_STATE_FREE;
        break;
    case BUTTON_STATE_CLICKED:
        clicked = true;
        button_state = BUTTON_STATE_FREE;
        break;
    
    default:
        printf("[error] bad button state in Button::isClicked");
        break;
    }
    return clicked;
}