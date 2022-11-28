#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <thread>
#include <vector>
// #include <sstream>

using namespace std;
using vector_points = vector<std::pair<int, int>>;

class File_Manager
{
public:

    void get_data(int level);
    void copy_lvl_fields(ifstream &fields);
    // enter file structure

    typedef struct Enter_Data_t
    {
        /* data */
        uint8_t cups_num;
        uint8_t points_num;
        vector<string> points_array;
        vector<string> start_cups_pos;

        // vector point_cord{};
    } Enter_Data;

    inline Enter_Data &get_e_task()
    {
        return _file_level;
    }

private:
    ifstream file_level; // read level file
    //    if (file_level == nullptr){std::cout << SDL_GetError() <<"path base"<<SDL_GetBasePath();};
    Enter_Data _file_level;
    filesystem::path _level_base_path;

};
