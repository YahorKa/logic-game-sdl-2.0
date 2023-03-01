#pragma once

#include <iostream>
#include <vector>
#include "SDL_rect.h"
#include <SDL2/SDL.h>
#include "SDL_thread.h"
#include <thread>
#include <mutex>
#include <utility>
#include "colors.h"
#include "file_manager.h"
#include <atomic>
#include <list>
#include <queue>


class Cup
{
public:
friend class Cups_Board;
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

    virtual inline const SDL_Color *get_color()
    {
        return &_color;
    }
    void move_cup(int, int, vector<int> &&v,deque<int> &&);
    bool get_touch();
    void set_touch(bool touch);

private:
    bool is_touching;
    bool is_moving;
    thread *thr;
    int smoothy_moving(int, int, Cup *);
    SDL_Rect rect;
    SDL_Color _color;
    SDL_Color _color_light;
    thread *thr2;

};
