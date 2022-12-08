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
  void cups_board_render_update(SDL_Renderer *);
  void handle_mouse(int x,int y);
  int find_number_point(int, int);
  vector<int> get_available_paths(int);

private:
  int _level;
  void create_cups();
  Cup*  create_cup(int sequence);
  void create_paths(SDL_Renderer *);
  void show_available_move(const SDL_Rect*);
  Cup ** _cups_array;
  SDL_Renderer *_paths;
};
