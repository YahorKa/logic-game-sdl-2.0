#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <thread>
#include <vector>
// #include <sstream>

using namespace std;

class File_Manager
{
public:
    void get_data(int level);
    void copy_lvl_fields(ifstream &fields);
    // enter file structure

    typedef struct Enter_Data_t
    {
        /* data */
        uint8_t         cups_num;
        uint8_t         points_num;
        vector<string>  points_array;
        vector<uint8_t> start_cups_pos;
        vector<uint8_t> winning_cups_pos;
        uint8_t         number_of_connections;
        vector<string>  list_of_pair_connections;
    } Enter_Data;

    inline Enter_Data &get_e_task()
    {
        return _file_level;
    }

    int get_int_from_str(int number,string str);

private:
    ifstream file_stream; // read level file
    Enter_Data _file_level;
    filesystem::path _level_base_path;

};
