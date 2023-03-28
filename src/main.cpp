#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "fn.hpp"

int main (int argc, char** argv) {
// Note: lines is a vector of strings

    std::cout << "Line Editor - Unix Edition\n";

    // Variables for prompt management
    std::string user_input = "";
    std::stringstream prompt_parser;

    // Variables to hold the operation and its parameter
    char operation = ' ';
    std::string param_1 = "",   // Normally holds file names for read/write ops
                param_2 = "";   // Holds text for replacement/insertion ops

    // Vector of strings
    std::vector <std::string> line_file;

    // Primary program loop
    do
    {
        operation = ' ';
        param_1 = param_2 = "";

        std::cout << "edlin> ";
        std::getline (std::cin, user_input);

        // Put user input into buffer for parsing
        prompt_parser << user_input;
        prompt_parser >> operation;

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
                break;
            case 'e':
                break;
            case '!':
                break;
            case 'q':
                std::cout << "Exiting the editor" << std::endl;
                exit(0);
            default:
                break;
        }

        // Reset buffer for next read
        prompt_parser.clear();
        prompt_parser.str("");

    }
    while (!feof (stdin));
}