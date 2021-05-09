#include "button.h"
#include <cstdio>

float Button::last_hit_time = 0.;

Button::Button(float x_topleft, float y_topleft, float width, float height)
{
    bound = {x_topleft, y_topleft, width, height};
}

bool Button::isClicked(MouseButton mousebutton) {
    Vector2 mousePoint = GetMousePosition();
    bool collision = CheckCollisionPointRec(mousePoint, bound);
    bool released = IsMouseButtonReleased(mousebutton);
    bool clicked = collision && released;
#if DEBUG
    printf("[debug]collision = %d, released = %d\n", collision, released);
#endif
    return clicked;
}