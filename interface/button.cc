#include "button.h"

Button::Button(float x_topleft, float y_topleft, float width, float height)
{
    bound = {x_topleft, y_topleft, width, height};
}

bool Button::isClicked(MouseButton mousebutton) {
    Vector2 mousePoint = GetMousePosition();
    bool ret = false;
    if (CheckCollisionPointRec(mousePoint, bound)) {
        if (IsMouseButtonReleased(mousebutton)) {
            ret = true;
        }
    }
    return ret;
}