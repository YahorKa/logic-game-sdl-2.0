// #include <SDL2/SDL.h>
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

  void cups_board_render_update(SDL_Renderer *);
  void handle_mouse(int x, int y);

private:
  void create_cups();
  void create_paths(SDL_Renderer *);
  vector<int> show_available_move(const SDL_Rect *);
  int find_number_point(int, int);
  SDL_Rect get_rect_point(int number_point);
  bool check_point_free(int);
  bool check_point_repeat(vector<int>, int);

  void init_level(int lvl);
  struct Cups_board_free_paths
  {
    vector<int> available_places;
    const SDL_Color *color;
  };

  int _level;
  int _num_cup_is_checked; // number of cup is cheked [1 ... N]
  Cup **_cups_array;
  Cup *implicit_array; // array of available move
  SDL_Renderer *_paths;
  Cups_board_free_paths _free_paths;
};
