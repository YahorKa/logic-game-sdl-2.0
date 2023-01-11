#pragma once

#include <iostream>
#include <vector>
#include "SDL_rect.h"
#include <SDL2/SDL.h>
#include <utility>
#include "colors.h"
#include "file_manager.h"

class Cup
{
public:
    Cup(int x, int y, int w, int h, const SDL_Color &_color);
    Cup();
    // Cup &operator=(Cup &other)
    // {
    //     return *this;
    // }
    virtual ~Cup(){};
    virtual inline SDL_Rect *get_rect()
    {
        return &rect;
    }
    uint8_t num{8};

    virtual inline const SDL_Color *get_color()
    {
        return &_color;
    }
    void move(int, int, vector<int>&&v,vector<pair<int,int>>&);
    bool get_touch();
    void set_touch(bool touch);

private:
    bool is_touching;
    static int smoothy_moving(int,int,Cup*);
    SDL_Rect rect;
    SDL_Color _color;
    SDL_Color _color_light;
};

