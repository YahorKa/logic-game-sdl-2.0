#include "cup.h"
#include <algorithm>

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
        is_touching = 0;
    }
}

bool Cup::get_touch()
{
    return is_touching;
}
void Cup::move(int start, int end, vector<int> &&available_move, deque<int> &&path)
{
    while (!path.empty())
    { 
        smoothy_moving(start, path.front(), this);
        start = path.front();
        path.pop_front();
        return move(start, end, std::move(available_move), std::move(path));
    }
}