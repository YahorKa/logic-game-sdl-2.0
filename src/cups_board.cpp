#include "cups_board.h"

File_Manager level_manager;
SDL_colors_t colors_list;
Cups_Board::Cups_Board()
//    _level{level}
{
    init_level(1);
}

Cups_Board::~Cups_Board()
{
    // std::cout << "destructor" << std::endl;
}
// create single cup
Cup *Cups_Board::create_cup(int sequence)
{
    int x, y;
    // get starting codr of cups (take away in separate function)
    string temp;
    string xy_cord = std::move(level_manager.get_e_task().points_array[level_manager.get_e_task().start_cups_pos[sequence] - 1]);
    istringstream buf(xy_cord);
    getline(buf, temp, ',');
    x = stoi(temp);
    getline(buf, temp, ',');
    y = stoi(temp);
    return new Cup(x, y, CUPS_H, CUPS_W, colors_list.list[sequence]);
}

void Cups_Board::create_cups()
{
    _cups_array = new Cup *[level_manager.get_e_task().cups_num];
    for (int i = 0; i < level_manager.get_e_task().cups_num; i++)
    {
        *(_cups_array + i) = create_cup(i);
    }
}
// return start cord of the cup
vector<int> Cups_Board::find_cups_cord(int _i)
{
    vector<int> cord{_i, _i};
    return cord;
}
void Cups_Board::cups_board_render_update(SDL_Renderer *render)
{
    for (int i = 0; i < level_manager.get_e_task().cups_num; i++)

    {
        SDL_SetRenderDrawColor(render, _cups_array[i]->get_color()->r, _cups_array[i]->get_color()->g, _cups_array[i]->get_color()->b, 255);
        SDL_RenderFillRect(render, _cups_array[i]->get_rect());
    }
}

void Cups_Board::handle_mouse(int x, int y)
{
    SDL_Point mouse_cord{x,y};
    int num =level_manager.get_e_task().cups_num;
    for (int i = 0; i <num; i++)
    {

        if (SDL_PointInRect(&mouse_cord, _cups_array[i]->get_rect()))
        {
        _cups_array[i]->have_touch();
        }
    }
}

bool Cups_Board::read_write_file_task(int lvl)
{
    level_manager.get_data(lvl);
    return true; // or false
}

void Cups_Board::init_level(int lvl)
{
    read_write_file_task(lvl);
    // create cups
    create_cups();
    // create paths
    // create something else
}