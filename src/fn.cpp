/**
 * @file fn.cpp
 * @author Drew Wheeler
 * 
 * @brief Contains function definitions for operation-handling procedures in the program.
 * 
 * Functionality for each of the program's features has been broken down into individual functions
 * that are called as needed. This file contains the definitions of those functions.
 * 
 * @see fn.hpp main.cpp
 * 
 */

#include "fn.hpp"


/**
 * @fn print_line_file
 * 
 * @param v Constant reference to a vector of strings that will be printed out to terminal.
 * 
 * @brief Prints the contents of a vector element-by-element to individual rows on stdout.
 *
 * @post Assuming v is a non-empty vector, each element contained within it is printed as a line to
 *       stdout. 
 * 
 */
void print_line_file (const std::vector <std::string>& v)
{
    unsigned int v_size = v.size();

    for (unsigned int i = 0; i < v_size; i++)
    {
        std::cout << v[i] << '\n';
    }
}


/**
 * @fn read_line_file
 * 
 * @param f_name Name of file on disk to be opened and read from.
 * @param v Reference to the vector of strings to store the data.
 * 
 * @brief Contents of file specified are loaded into a vector, assuming the file isn't empty.
 * 
 * @pre f_name is a valid text file containing lines of text.
 * @post Vector passed in is emptied and contents of file are loaded into it line-by-line.
 * 
 * @returns bool
 * @retval false An error occurred while trying to open the file specifed (either it doesn't esist
 *         or user does not have suffienct permissions to access it.
 * @retval true The file specified could be found and was able to be opened and closed.
 * 
 * @note A return value of true does not necessarily indicate a successful reading of lines of text
 *       from a file, it simply indicates that the file exists.
 * 
 */
bool read_line_file (std::string f_name, std::vector<std::string>& v)
{
    std::ifstream f_load (f_name.c_str());
    std::string temp = "";

    if (f_load.is_open())
    {
        v.clear(); // Empty the vector that will store data

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
