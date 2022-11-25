//#include <SDL2/SDL.h>
#pragma once
#include "cup.h"
#include <utility>
#include <vector>

using vector = std::vector<std::pair<int, int>>;

class Cups_Board
{
public:
  Cups_Board(int level);
  ~Cups_Board();

  // enter file structure
  typedef struct File_Enter_Task_t
  {
    /* data */
    uint8_t cups_num;
    uint8_t points_num;
    std::pair<int, int> t;
    // vector point_cord{};
  } File_level;

  // init new level
  void init_level();

  inline File_level &get_e_task();


  bool read_write_file_task();
  inline void draw_cup();
  inline Cup ** get_array_addr(){
    return _cups_array;
  }

  Cup* create_cup(int x, int y, int w, int h);
  // calls in main_loop
  void cups_board_render_update(SDL_Renderer *render);

private:
  void move_cup();
  void create_cups();
  File_level _f_str;
  int _level;
  Cup *_cups_array[];
};
