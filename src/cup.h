#pragma once

#include <iostream>
#include <vector>
#include "SDL_rect.h"
#include <SDL2/SDL.h>
#include "defines.h"
#include "file_manager.h"

class Cup
{
public:
    Cup(int x, int y, int w, int h, SDL_Color color);
    virtual ~Cup(){};

    virtual inline const SDL_Rect *get_rect()
    {
        return &rect;
    }
    uint8_t num{8};

    virtual inline const SDL_Color* get_color()
    {
        return &_color;
    }
    void cup_move();
    void have_touch();
    
private:
    SDL_Rect rect;
    SDL_Color _color;
};
