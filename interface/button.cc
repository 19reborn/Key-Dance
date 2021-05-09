#include "raylib.h"

class Button {
private:
    Rectangle bound;
    
public:
    Button(float x_topleft, float y_topleft, float width, float height) {
        bound = {x_topleft, y_topleft, width, height};
    }
    bool isClicked(MouseButton mousebutton = MOUSE_LEFT_BUTTON) {
        Vector2 mousePoint = GetMousePosition();
        bool ret = false;
        if (CheckCollisionPointRec(mousePoint, bound)) {
            if (IsMouseButtonReleased(mousebutton)) {
                ret = true;
            }
        }
        return ret;
    }
};