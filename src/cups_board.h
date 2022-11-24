//#include <SDL2/SDL.h>
#pragma once
#include "cups.h"
#include <utility>
#include <vector>

using vector = std::vector<std::pair<int, int>>;

class Cups_Board
{
public:
  Cups_Board(int level);
  // enter file structure
  struct File_Task
  {
    /* data */
    uint8_t cups_num;
    uint8_t points_num;
    std::pair<int, int> t;
    // vector point_cord{};
  };

  // init new level
  void init_level();

  // calls in main_loop
  void cups_board_update(SDL_Renderer *render);
  inline File_Task &get_e_task();

  bool read_write_flight_task();
  inline void draw_cup();
  void create_cup();
  void move_cup();

private:
  File_Task _f_str;
  int _level;
  Cups _cups_array[];
};
