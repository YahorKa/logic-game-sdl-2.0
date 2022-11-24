#pragma once

#include <vector>
#include "SDL_rect.h"
#include <SDL2/SDL.h>

class Cups
{
public:
    Cups(int x, int y, int w, int h);

    // bool render(float x, float y);
    SDL_Rect rect;

private:
    float _cord_x, _cord_y, _w, _h;

    Cups *_cup;
};
