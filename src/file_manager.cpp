#include "file_manager.h"

void File_Manager::get_data(int level)
{
    cout << "level" << level <<endl;
    cout << "filesystem::current_path()" << filesystem::current_path() <<endl;
    ifstream file_stream; // read level file
    // for (auto iter : filesystem::current_path())
    // {
    //      cout << "level" << level <<endl;
    //     if (iter.compare("build"))
    //     {
    //         _level_base_path /= iter;
    //     }
    // }  
    _level_base_path = filesystem::current_path().parent_path();
    filesystem::path levelFilePath = _level_base_path /= (std::to_string(level) + "level.txt");

    std::cout << "Trying to open file: " << levelFilePath << std::endl;

    file_stream.open(levelFilePath);
    if (!file_stream)
    {
        std::cout << "cant open" << std::endl;
    }
    copy_lvl_fields(file_stream);
    file_stream.close();
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
        std::istringstream point_pair(stream);
        string pair_f;
        string pair_s;
        getline(point_pair, pair_f, ',');
        getline(point_pair, pair_s, ',');
        _file_level.points_array.push_back({stoi(pair_f),stoi(pair_s)});
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
    // get number of connections
    getline(fields, stream);
    _file_level.number_of_connections = stoi(stream);
    // get pair of connections in int format
    while (!fields.eof())
    {
        getline(fields, stream);
        istringstream buf(stream);
        string val1, val2;
        getline(buf, val1, ',');
        getline(buf, val2, ',');
        _file_level.list_of_pair_connections.push_back(pair<int, int>{stoi(val1), stoi(val2)});
        // std::cout << stream<<std::endl;
    }
}
