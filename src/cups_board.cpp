#include "cups_board.h"

File_Manager level_manager;
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
    // get starting codr of cups
    string temp;
    string xy_cord = std::move(level_manager.get_e_task().points_array[level_manager.get_e_task().start_cups_pos[sequence] - 1]);
    istringstream buf(xy_cord);
    getline(buf,temp,',');
    x = stoi(temp);
    getline(buf,temp,',');
    y = stoi(temp);
    return new Cup(x, y, 50, 50);
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
        if (i == 1)
        {
            BLUE_COLOR
        }
        else
        {
            YELLOW_COLOR
        }
        // rect = *_cups_array[i]->get_rect();
        SDL_RenderFillRect(render, _cups_array[i]->get_rect());
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