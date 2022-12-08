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
    string xy_cord = level_manager.get_e_task().points_array[level_manager.get_e_task().start_cups_pos[sequence] - 1];
    istringstream buf(xy_cord);
    getline(buf, temp, ',');
    x = stoi(temp);
    getline(buf, temp, ',');
    y = stoi(temp);
    return new Cup(x - CUPS_H / 2, y - CUPS_W / 2, CUPS_H, CUPS_W, colors_list.list[sequence]);
}

void Cups_Board::create_cups()
{
    _cups_array = new Cup *[level_manager.get_e_task().cups_num];
    for (int i = 0; i < level_manager.get_e_task().cups_num; i++)
    {
        *(_cups_array + i) = create_cup(i);
    }
}

void Cups_Board::create_paths(SDL_Renderer *render)
{
    // set color of paths
    SDL_SetRenderDrawColor(render, 135, 206, 250, 0);
    //_paths_cord.resize(level_manager.get_e_task().number_of_connections);
    for (auto it : level_manager.get_e_task().list_of_pair_connections)
    {
        // get pair of paths connections in string format
        int x, y, x1, y1;
        pair<string, string> pair;
        string temp;
        istringstream buf(it);
        getline(buf, temp, ',');
        pair.first = level_manager.get_e_task().points_array[stoi(temp) - 1];
        getline(buf, temp, ',');
        pair.second = level_manager.get_e_task().points_array[stoi(temp) - 1];
        buf.str(pair.first);
        buf.seekg(0);
        getline(buf, temp, ',');
        x = stoi(temp);
        getline(buf, temp, ',');
        y = stoi(temp);
        buf.str(pair.second);
        buf.seekg(0);
        getline(buf, temp, ',');
        x1 = stoi(temp);
        getline(buf, temp, ',');
        y1 = stoi(temp);
        SDL_RenderDrawLine(render, x, y, x1, y1);
        //_paths_cord.push_back(pair);
    }
}

void Cups_Board::cups_board_render_update(SDL_Renderer *render)
{
    // Draw paths. Unfothenetly we should perfom equlations in this func for static path, the beter way set away this func in init func
    create_paths(render);
    // Draw cups
    for (int i = 0; i < level_manager.get_e_task().cups_num; i++)
    {
        if (_cups_array[i]->get_touch())
        {
            SDL_Color color = std::move(colors_list.light_list[i]);
            SDL_SetRenderDrawColor(render, color.r, color.g, color.b, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(render, _cups_array[i]->get_color()->r, _cups_array[i]->get_color()->g, _cups_array[i]->get_color()->b, 255);
        }
        SDL_RenderFillRect(render, _cups_array[i]->get_rect());
    }
}

void Cups_Board::handle_mouse(int x, int y)
{
    SDL_Point mouse_cord{x, y};
    int num = level_manager.get_e_task().cups_num;
    for (int i = 0; i < num; i++)
    {
        if (SDL_PointInRect(&mouse_cord, _cups_array[i]->get_rect()))
        {
            if (_cups_array[i]->get_touch())
            {
                _cups_array[i]->set_touch(0);
            }
            else
            {
                _cups_array[i]->set_touch(1);
                show_available_move(_cups_array[i]->get_rect());
            }
        }
        else
            //_cups_array[i]->set_touch(0);
            if (_cups_array[i]->get_touch())
            {
                _cups_array[i]->set_touch(0);
                _cups_array[i]->move(x, y);
            }
    }
}
void Cups_Board::show_available_move(const SDL_Rect *rec)
{
    // std::cout << rec->x + rec->w / 2 << rec->y + rec->h / 2 << endl;
    //  find number of point

    int number_point = find_number_point(rec->x + (rec->w / 2), rec->y + (rec->h / 2));
    std::cout << number_point << endl;
    // chek all paths paths
    get_available_paths(number_point);

    //  draw availible cups
}
int Cups_Board::find_number_point(int rect_x, int rect_y)
{
    for (auto it = level_manager.get_e_task().points_array.begin(); it != level_manager.get_e_task().points_array.end(); it++)
    {
        string temp;
        istringstream buf(*it);
        getline(buf, temp, ',');
        int x = stoi(temp);
        getline(buf, temp, ',');
        int y = stoi(temp);
        std::cout << x << y << rect_x << rect_y << std::endl;

        if ((rect_x == x) && (rect_y == y))
        {
            return (it - level_manager.get_e_task().points_array.begin() + 1);
        }
    }
    cout << "ERROR CANT FIND POINT" << endl;
    return -1;
}
vector<int> Cups_Board::get_available_paths(int)
{
   //for (auto it: level_manager.get_e_task.)
    return vector<int>{};
}
void Cups_Board::init_level(int lvl)
{
    if (lvl > 1)
    { // clear dinamic arrays
    }
    level_manager.get_data(lvl);
    create_cups();
    // create_paths();
    //  create something else
}