#include "cups_board.h"

//thread = SDL_CreateThread(Cup::smoothy_moving, "smoothy_moving", nullptr);
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

void Cups_Board::init_level(int lvl)
{
    level_manager.get_data(lvl);
    create_cups();
}

void Cups_Board::create_cups()
{
    _cups_array = new Cup *[level_manager._file_level.cups_num];
    for (int i = 0; i < level_manager._file_level.cups_num; i++)
    {
        int x, y;
        // get starting codr of cups (take away in separate function)
        string temp;
        string xy_cord = level_manager._file_level.points_array[level_manager._file_level.start_cups_pos[i] - 1];
        istringstream buf(xy_cord);
        getline(buf, temp, ',');
        x = stoi(temp);
        getline(buf, temp, ',');
        y = stoi(temp);
        *(_cups_array + i) = new Cup(x - CUPS_H / 2, y - CUPS_W / 2, CUPS_H, CUPS_W, colors_list.list[i]);
    }
}

void Cups_Board::create_paths(SDL_Renderer *render)
{
    // set color of paths
    SDL_SetRenderDrawColor(render, 135, 206, 250, 0);
    //_paths_cord.resize(level_manager._file_level.number_of_connections);
    for (auto it : level_manager._file_level.list_of_pair_connections)
    {
        // get pair of paths connections in string format
        int x, y, x1, y1;
        pair<string, string> pair;
        string temp;
        istringstream buf;
        pair.first = level_manager._file_level.points_array[it.first - 1];
        pair.second = level_manager._file_level.points_array[it.second - 1];
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
    SDL_Rect rect; // rect to draw available move
    // Draw paths. Unfothenetly we should perfom equlations every tick, the beter way is get away this func from init func
    create_paths(render);
    // Draw cups
    for (int i = 0; i < level_manager._file_level.cups_num; i++)
    {
        if (_cups_array[i]->get_touch())
        {
            SDL_Color color = move(colors_list.light_list[i]);
            SDL_SetRenderDrawColor(render, color.r, color.g, color.b, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(render, _cups_array[i]->get_color()->r, _cups_array[i]->get_color()->g, _cups_array[i]->get_color()->b, 255);
        }
        SDL_RenderFillRect(render, _cups_array[i]->get_rect());
    }

    // create available cups to move
    if (_free_paths.available_places.capacity())
    {
        Cup *implicit_cups = new Cup[_free_paths.available_places.capacity()];
        SDL_SetRenderDrawColor(render, _free_paths.color->r, _free_paths.color->g, _free_paths.color->b, 255);
        for (auto it = _free_paths.available_places.begin(); it != _free_paths.available_places.end(); ++it)
        {
            SDL_Rect rect = get_rect_point(*it);
            implicit_cups[it - _free_paths.available_places.begin()] = *new Cup(get_rect_point(*it).x, get_rect_point(*it).y,
                                                                                50, 50, *_free_paths.color);
            SDL_RenderFillRect(render, &rect);
        }
        delete[] implicit_cups;
    }
    // Draw wining position, please
    for (int i = 0; i < level_manager._file_level.cups_num; i++)
    {
        int x, y, offset_x =400, offset_y=200;
        SDL_Rect rect;
        string temp;
        string xy_cord = level_manager._file_level.points_array[level_manager._file_level.winning_cups_pos[i] - 1];
        istringstream buf(xy_cord);
        getline(buf, temp, ',');
        rect.x = stoi(temp)/1.3+offset_x;
        getline(buf, temp, ',');
        rect.y = stoi(temp)/1.3+offset_y;
        rect.h = 50;
        rect.w = 50;
        SDL_SetRenderDrawColor(render, colors_list.list[i].r,colors_list.list[i].g, colors_list.list[i].b, 255);
        SDL_RenderFillRect(render, &rect);
    }
}

void Cups_Board::handle_mouse(int x, int y)
{
    SDL_Point mouse_cord{x, y};
    int num = level_manager._file_level.cups_num;
    for (int i = 0; i < num; i++)
    {
        // check DO WE touch on of cups ?
        if (SDL_PointInRect(&mouse_cord, _cups_array[i]->get_rect()))
        {
            if (_cups_array[i]->get_touch())
            { // This cup was already touched and catch again, therefor set touch (0)
                _cups_array[i]->set_touch(0);
                _free_paths.available_places = {};
                _num_cup_is_checked = 0;
                return;
            }
            else
            { // catch one of cups !
                _cups_array[i]->set_touch(1);
                _free_paths.available_places = show_available_move(_cups_array[i]->get_rect());
                _free_paths.color = _cups_array[i]->get_color();
                _num_cup_is_checked = i + 1;
                return;
            }
        }
        else if (_cups_array[i]->get_touch())
        { //  This cup was already touched, and we want to move it
            SDL_Rect rect, start_rect;
            int start_point, target_point;
            _cups_array[i]->set_touch(0);
            _num_cup_is_checked = 0;
            start_rect = *_cups_array[i]->get_rect();
            for (auto it : _free_paths.available_places)
            { // check DO WE can to move it ?
                rect = get_rect_point(it);
                if (SDL_PointInRect(&mouse_cord, &rect))
                {
                   // _cups_array[i]->move(rect.x + (rect.w / 2), rect.y + (rect.h / 2));  need to rewrite
                   start_point = find_number_point(start_rect.x + (rect.w / 2),start_rect.y+ (rect.h / 2) );
                   target_point = it;
                   //_cups_array[i]->move(start_point,target_point, move(_free_paths.available_places), level_manager._file_level.list_of_pair_connections);
                   cout<<"*cup = "<<_cups_array[i]<<endl;
                   thr1 = new std::thread(&Cup::move,std::move(_cups_array[i]),start_point,target_point, move(_free_paths.available_places), std::ref(level_manager._file_level.list_of_pair_connections));
                   // _free_paths.available_places = {};
                    if (_check_winning_position())
                    {
                        cout << "You WIN!!!" << endl;
                        _level ++;
                        // Clear cups_Board
                    }
                    return;
                }
            }
            _free_paths.available_places = {};
        }
    }
}

// search number position in points array via coordinate
int Cups_Board::find_number_point(int rect_x, int rect_y)
{
    for (auto it = level_manager._file_level.points_array.begin(); it != level_manager._file_level.points_array.end(); it++)
    {
        string temp;
        istringstream buf(*it);
        getline(buf, temp, ',');
        int x = stoi(temp);
        getline(buf, temp, ',');
        int y = stoi(temp);
        // std::cout << x << y << rect_x << rect_y << std::endl;

        if ((rect_x == x) && (rect_y == y))
        {
            return (it - level_manager._file_level.points_array.begin() + 1);
        }
    }
    cout << "ERROR CANT FIND POINT" << endl;
    return -1;
}

SDL_Rect Cups_Board::get_rect_point(int number_point)
{
    int x, y;
    string val;
    istringstream buf(level_manager._file_level.points_array[number_point - 1]);
    getline(buf, val, ',');
    x = stoi(val);
    getline(buf, val, ',');
    y = stoi(val);
    return SDL_Rect{x - 25, y - 25, 50, 50};
}

vector<int> Cups_Board::show_available_move(const SDL_Rect *rec)
{
    int number_point = find_number_point(rec->x + (rec->w / 2), rec->y + (rec->h / 2));
    // chek all paths
    vector<int> available_places{};
    auto search_paths = [&](int num)
    {
    for (auto it : level_manager._file_level.list_of_pair_connections)
    {
        if (it.first == num)
        {
            if (check_point_free(it.second))
            {
                // cout << it.second << endl;
                if (check_point_repeat(available_places,it.second))available_places.push_back(it.second);
            }
        }
        if (it.second == num)
        {
            if (check_point_free(it.first))
            {
                // cout << it.first << endl;
                if (check_point_repeat(available_places,it.first))available_places.push_back(it.first);
            }
        }
    } };

    search_paths(number_point);
    while (1)
    {
        int cap = available_places.capacity();
        for (auto it : available_places)
        {
            search_paths(it);
        }
        if (cap == available_places.capacity()) // we found all available move
        {
            return available_places;
        }
        cap = available_places.capacity();
    }

    return available_places;
    //  draw availible cups
}

bool Cups_Board::check_point_repeat(vector<int> v, int num)
{
    for (auto it : v)
    {
        int count;
        if (num == it)
            return 0;
    }
    return 1;
}

bool Cups_Board::check_point_free(int point_number)
{
    for (int i = 0; i < level_manager._file_level.cups_num; i++)
    {
        if ((point_number) == find_number_point(_cups_array[i]->get_rect()->x + (_cups_array[i]->get_rect()->w) / 2,
                                                _cups_array[i]->get_rect()->y + (_cups_array[i]->get_rect()->h) / 2))
        {
            return false;
        }
    }
    return true;
}

bool Cups_Board::_check_winning_position()
{
    for (int i = 0; i < level_manager._file_level.cups_num; i++)
    {
        int point_number = find_number_point(_cups_array[i]->get_rect()->x + (_cups_array[i]->get_rect()->w) / 2,
                                             _cups_array[i]->get_rect()->y + (_cups_array[i]->get_rect()->h) / 2);
        if (point_number != level_manager._file_level.winning_cups_pos[i])
            return false;
    }
    return true;
}

int Cup::smoothy_moving(int start,int end,Cup* cup){
    SDL_Rect start_rect = Cups_Board::get_rect_point(start);
    SDL_Rect end_rect =  Cups_Board::get_rect_point(end);
    cout<<"*cup = "<<cup<<endl;
    // cout<<"start x:"<<start_rect.x<<"end x:"<<end_rect.x<<(end_rect.x - start_rect.x)/abs(end_rect.x - start_rect.x)<<endl;
    // cout<<"start y:"<<start_rect.y<<"end y:"<<end_rect.y<<(end_rect.y - start_rect.y)/abs(end_rect.y - start_rect.y)<<endl;
    while (!SDL_RectEquals(cup->get_rect(), &end_rect))
    {
        if (start_rect.x != end_rect.x)  cup->get_rect()->x += (end_rect.x - start_rect.x)/abs(end_rect.x - start_rect.x);
        if (start_rect.y != end_rect.y)  cup->get_rect()->y += (end_rect.y - start_rect.y)/abs(end_rect.y - start_rect.y);
         std::this_thread::sleep_for(std::chrono::milliseconds(10));
             //cout<<"x: "<<cup->get_rect()->x<<"y: "<<cup->get_rect()->y<<endl;
    }
    is_done = 1;
    return 0;
}