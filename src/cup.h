#pragma once

#include <iostream>
#include <vector>
#include "SDL_rect.h"
#include <SDL2/SDL.h>
#include "defines.h"

class Cup
{
public:
    Cup(int x, int y, int w, int h);
virtual ~Cup(){};

    virtual inline const SDL_Rect* get_rect(){
        return &rect;
    }
    uint8_t num{8};

private:
    SDL_Rect rect;
   
};
