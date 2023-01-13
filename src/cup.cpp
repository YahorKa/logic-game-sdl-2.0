#include "cup.h"
#include <algorithm>

int test(void *ptr)
{
    std::cout << "have tread" << std::endl;
    // while (1)
    // {
    // }
    return 0;
}

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

void Cup::move(int start, int end, vector<int> &&available_move, vector<pair<int, int>> &available_pair)
{
//std::thread thr(smoothy_moving);
    if (start < end)
    {
        for (auto pair : available_pair)
        {
            if (pair.first == start)
            {
               if (find(available_move.begin(),available_move.end(),pair.second) != available_move.end())
               { 
                // move to point?  smoothy_moving(start, pair.second, this
                //cout<<pair.second<<endl; 
                std::thread thread (&Cup::smoothy_moving,this, start, pair.second,this);
                thread.join();
                start = pair.second;
                if (start == end) return;
               }
            }
        }
    }
    else
    {
    }
}
