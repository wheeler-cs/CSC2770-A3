#include "fn.hpp"

void print_line_file (const std::vector <std::string>& v)
{
    unsigned int v_size = v.size();

    for (unsigned int i = 0; i < v_size; i++)
    {
        std::cout << v[i] << '\n';
    }
}


bool read_line_file (std::string f_name, std::vector<std::string>& v)
{
    std::ifstream f_load (f_name.c_str());
    std::string temp = "";

    if (f_load.is_open())
    {
        std::getline (f_load, temp);
        while (!f_load.eof())
        {
            v.push_back (temp);
            std::getline (f_load, temp);
        }
        f_load.close();
        return true;
    }
    else
        return false;
}
