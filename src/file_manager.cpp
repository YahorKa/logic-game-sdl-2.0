#include "file_manager.h"

void File_Manager::get_data(int level)
{
    for (auto &iter : filesystem::current_path()) // must be iterator not paths
    {
        if (iter.compare("build"))
        {
            _level_base_path /= iter;
        }
    }
    _level_base_path /= (std::to_string(level) + "level.txt");
    file_level.open(_level_base_path);
    if (!file_level)
    {
        std::cout << "cant open" << std::endl;
    }
    copy_lvl_fields(file_level);
}

void File_Manager::copy_lvl_fields(ifstream &fields)
{
    string stream;
    getline(fields, stream);
    _file_level.cups_num = stoi(stream);
    getline(fields, stream);
    _file_level.points_num = stoi(stream);

    // create vector_points
    
    for (auto i = 0; i < _file_level.points_num; i++)
    {
        //istream temp;
        getline(fields, stream, ',');
        _file_level.points_array.push_back(stream);
    }
        getline(fields, stream);
            std::cout << stream<< std::endl;
        getline(fields, stream,',');
        getline(fields, stream);

        _file_level.start_cups_pos.push_back(stream);
    std::cout << stream<< std::endl;
   // std::cout << std::to_string(_file_level.points_num) << stream <<std::endl;
}
