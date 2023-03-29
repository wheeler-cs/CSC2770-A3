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
        std::cout << (i + 1) << '\t' << v[i] << '\n';
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
 * @returns The success status of the read operation.
 * @retval false An error occurred while trying to open the file specifed (either it doesn't esist
 *         or user does not have suffienct permissions to access it.
 * @retval true The file specified could be found and was able to be opened and closed.
 * 
 * @note A return value of true does not necessarily indicate a successful reading of lines of text
 *       from a file, it simply indicates that the file exists.
 * 
 */
bool read_line_file (const std::string& f_name, std::vector<std::string>& v)
{
    std::ifstream f_load (f_name.c_str());
    std::string temp = "";

    if (f_load.is_open())
    {
        v.clear(); // Empty the vector that will store data

        std::getline (f_load, temp); // If initial getline fails, file is empty
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


/**
 * @fn write_line_file
 * 
 * @param f_name The name of the file the vector will be saved to.
 * @param v The vector of strings to be written to the file.
 * 
 * @brief Writes the contents of a string-containing vector to a file, with each element on its own
 *        line .
 * 
 * @pre Vector v is properly initialized and (should) contain strings.
 * @post Data within the vector v is written out to the file specified.
 * 
 * @returns The success status of the write operation.
 * @retval false A file could not be opened or created for a write operation. This is most likely
 *         due to file permissions.
 * @retval true File was successfully opened and the contents of the vector were written to it.
 * 
 * @see fn.hpp
 * 
 */
bool write_line_file (const std::string& f_name, const std::vector <std::string>& v)
{
    std::ofstream f_write (f_name.c_str());

    if (f_write.is_open())
    {
        // Loop through and print vector to file
        unsigned int v_size = v.size();
        for (unsigned int i = 0; i < v_size; i++)
            f_write << v[i] << '\n';
        f_write.close();
        return true;
    }
    else
        return false;
}


/**
 * @fn edit_line
 * 
 * @param lno Line number to be modified.
 * @param ltxt New text to be inserted at the specified line.
 * @param v Vector of strings to be modified by the operation.
 * 
 * @brief Modifies the text of a given line number.
 * 
 * The given line number of the text file is translated to an index number for the vector and
 * that text is overwritten with specified text. If the line number specified is out of bounds for
 * the text vector, the new text is just appended to the end.
 * 
 * @returns The current size of v.
 * 
 * @see fn.hpp
 * 
 */
unsigned int edit_line (int lno, const std::string& ltxt, std::vector <std::string>& v)
{
    if (lno > (int) v.size())
        v.push_back (ltxt);
    else
        v[--lno] = ltxt;

    return v.size();
}
