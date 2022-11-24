#include "cups_board.h"

Cups_Board::Cups_Board(int level) //: _f_str{3, 5, {100, 300}},
                                  //    _level{level}
{
}

// calls in main_loop
void Cups_Board::cups_board_update(SDL_Renderer *render)
{

    SDL_Rect rect1 = {10, 10, 50, 50};
    SDL_SetRenderDrawColor(render, 0x00, 0x00, 255, 255);
    SDL_RenderFillRect(render, &rect1);
    SDL_Rect rect2 = {70, 10, 50, 50};
    SDL_RenderDrawRect(render, &rect2);
}
inline Cups_Board::File_Task &Cups_Board::get_e_task()
{
    return _f_str;
}
bool Cups_Board::read_write_flight_task()
{
    return true; // or false
}
void Cups_Board::init_level()
{
    read_write_flight_task();
    //create cups
    //create paths
    //create something else
}