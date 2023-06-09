/**
 * @file main.cpp
 * @author Drew Wheeler
 * 
 * @brief Main driving file of the program.
 * 
 * @see edlin.hpp edlin.cpp
 * 
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "edlin.hpp"

int main (int argc, char** argv) {
// Note: lines is a vector of strings

    std::cout << "Line Editor - Unix Edition\n";

    // Variables for prompt management
    std::string user_input = "";
    std::stringstream prompt_parser;

    // Variables to hold the operation and its parameter
    char operation = ' ', space_check = ' ';
    std::string param_1 = "",   // Normally holds file names for read/write ops
                param_2 = "";   // Holds text for replacement/insertion ops

    // Vector of strings
    std::vector <std::string> line_file;

    // Primary program loop
    do
    {
        operation = ' ';
        param_1 = "";
        int lno = 0;

        std::cout << "edlin> ";
        std::getline (std::cin, user_input);

        // Put user input into buffer for parsing
        prompt_parser << user_input;
        prompt_parser >> operation;

        // Check for if a space comes after for certain operations
        prompt_parser.get (space_check);
        switch (operation)
        {
            case 'r':
            case 's':
            case 'e':
            case '!':
                if (space_check != ' ')
                {
                    std::cerr << "Operation requires a space between it and arguments" << std::endl;
                    operation = ' ';
                }
        }

        switch (operation)
        {
            case 'l':
                print_line_file (line_file);
                break;
            case 'r':
                prompt_parser >> param_1;
                if (!read_line_file (param_1, line_file))
                    std::cerr << "Cannot open " << param_1 << std::endl;
                break;
            case 's':
                prompt_parser >> param_1;
                if (!write_line_file (param_1, line_file))
                    std::cerr << "Cannot open " << param_1 << std::endl;
                break;
            case 'e':
                prompt_parser >> lno;
                prompt_parser.get (param_1[0]); // Get the left over ' ' between lno and text
                std::getline (prompt_parser, param_1);
                if (!prompt_parser.fail())
                    edit_line (lno, param_1, line_file);
                else
                    std::cerr << "Missing or malformed parameters for e operation" << std::endl;
                break;
            case '!':
                filter (line_file, user_input);
                break;
            case 'q':
                std::cout << "Exiting the editor" << std::endl;
                exit(0);
            case ' ':   // Kinda a hacky way to get around printing more output
                break;
            default:
                prompt_parser.clear();
                std::getline (prompt_parser, param_1);
                std::cerr << "Unable to resolve command " << param_1 << std::endl;
        }

        // Reset buffer for next read
        prompt_parser.clear();
        prompt_parser.str("");

    }
    while (!feof (stdin));

    return 0;
}
