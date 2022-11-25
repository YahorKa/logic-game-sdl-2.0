#include "cups_board.h"

Cups_Board::Cups_Board() : _f_str{7, 5, {100, 300}}
//    _level{level}
{
    init_level();
}

Cups_Board::~Cups_Board()
{
    std::cout << "destructor" << std::endl;
}

Cup *Cups_Board::create_cup(int x, int y, int w, int h)
{
    return new Cup(x, y, w, h);
}

void Cups_Board::create_cups()
{
    _cups_array = new Cup*[_f_str.cups_num];
    for (int i = 0; i < _f_str.cups_num; i++)
    {
        *(_cups_array+i) = create_cup(i * 100, 100, 50, 50);
    }
}

void Cups_Board::cups_board_render_update(SDL_Renderer *render)
{
    SDL_Rect rect;
    for (int i = 0; i < _f_str.cups_num; i++)
    {
        if (i == 1)
        {
            BLUE_COLOR
        }
        else
        {
            YELLOW_COLOR
        }
        //rect = *_cups_array[i]->get_rect();
        SDL_RenderFillRect(render, _cups_array[i]->get_rect());
    }
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