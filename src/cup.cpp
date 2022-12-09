#include "cup.h"

Cup::Cup(int x, int y, int w, int h, const SDL_Color &color) : rect{x, y, w, h}, _color{color}
{
}
Cup::Cup() = default;
void Cup::set_touch(bool touch)
{
    if (touch)
    {
        if (is_touching)
        {
            return;
        }
        is_touching = 1;
    }
    if (!touch)
    {
        // _color.g -= 20;
        is_touching = 0;
    }
}

bool Cup::get_touch()
{
    return is_touching;
}
void Cup::move(int x, int y)
{
    rect.x = x - rect.w / 2;
    rect.y = y - rect.h / 2;
}