//#include <SDL2/SDL.h>
#pragma once

#include "cup.h"

#define CUPS_H 50
#define CUPS_W 50

class Cups_Board
{
public:
  Cups_Board();
  ~Cups_Board();

  // init new level
  void init_level(int lvl);

  bool read_write_file_task(int lvl);

  inline Cup ** get_array_addr(){
    return _cups_array;
  }

  // calls in main_loop
  void cups_board_render_update(SDL_Renderer *render);
  void handle_mouse(int x,int y);

private:

  void move_cup();
  vector<int> find_cups_cord(int _i);
  void create_cups();
  Cup*  create_cup(int sequence);
  //SDL_Color _colors[256];
  int _level;
  Cup ** _cups_array;

};
