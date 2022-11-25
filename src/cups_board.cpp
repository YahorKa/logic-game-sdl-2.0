#include "cups_board.h"
#include <iostream>

Cups_Board::Cups_Board(int level) : _f_str{3, 5, {100, 300}}
//    _level{level}
{
    std::cout<<"constructor"<<std::endl;
    init_level();

}

Cups_Board::~Cups_Board()
{
      std::cout<<"destructor"<<std::endl;

}

Cup *Cups_Board::create_cup(int x, int y, int w, int h)
{
    return new Cup(x, y, w, h);
}

void Cups_Board::create_cups()
{
    for (int i = 0; i < _f_str.cups_num; i++)
    {
        _cups_array[i] = create_cup(i * 100, 100, 50, 50);
    }
}

// calls in main_loop
void Cups_Board::cups_board_render_update(SDL_Renderer *render)
{
    for (int i = 0; i < _f_str.cups_num; i++)
    {
        SDL_SetRenderDrawColor(render, 0x00, 0x00, 255, 255);
        std::cout<<"i=" << i <<"_cups_array=" << _cups_array[i] << std::endl;
        SDL_RenderFillRect(render, &_cups_array[i]->rect);
    }
}

inline Cups_Board::File_level &Cups_Board::get_e_task()
{
    return _f_str;
}


bool Cups_Board::read_write_file_task()
{
    return true; // or false
}

void Cups_Board::init_level()
{
    read_write_file_task();
    // create cups
    create_cups();
    // create paths
    // create something else
}