#include "file_manager.h"

void File_Manager::get_data(int level)
{
    for (auto &iter : filesystem::current_path())
    {
        if (iter.compare("build"))
        {
            _level_base_path /= iter;
        }
    }
    _level_base_path /= (std::to_string(level) + "level.txt");
    file_stream.open(_level_base_path);
    if (!file_stream)
    {
        std::cout << "cant open" << std::endl;
    }
    copy_lvl_fields(file_stream);
}

void File_Manager::copy_lvl_fields(ifstream &fields)
{
    string stream;
    _file_level = {};
    // get number of cups
    getline(fields, stream);
    _file_level.cups_num = stoi(stream);
    // get number of all existing points
    getline(fields, stream);
    _file_level.points_num = stoi(stream);
    // get coordinates of all existing points
    for (auto i = 0; i < _file_level.points_num; i++)
    {
        getline(fields, stream);
        _file_level.points_array.push_back(stream);
    }
    // get starting positions of all cups
    getline(fields, stream);
    std::istringstream iline(stream);
    for (auto i = 0; i < _file_level.cups_num; i++)
    {
        getline(iline, stream, ',');
        _file_level.start_cups_pos.push_back(stoi(stream));
    }
    // get winning position of all cups
    getline(fields, stream);
    iline.str(stream);
    iline.seekg(0);
    for (auto i = 0; i < _file_level.cups_num; i++)
    {
        getline(iline, stream, ',');
        _file_level.winning_cups_pos.push_back(stoi(stream));
    }
    // get number of conenctions
    getline(fields, stream);
    _file_level.number_of_connections = stoi(stream);
    // get pair of connections
    while (!fields.eof())
    {
        getline(fields, stream);
        _file_level.list_of_pair_connections.push_back(stream);
       // std::cout << stream<<std::endl;
    }
}

    int get_int_from_str(int number,string str){
        int res;
        istringstream buf(str);
        //getline(buf,res,',');
        // buf >> res;
        // std::cout<<res;
        // string pair;
        // pair = str;
    }