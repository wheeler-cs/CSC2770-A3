/**
 * @file fn.hpp
 * @author Drew Wheeler
 * 
 * @brief Contains function prototypes to extend functionality of program.
 * 
 * Each individual operation the line editor is capable of is handled through a function call, and
 * passed in the parameters that are needed.
 * 
 * @see fn.cpp
 * 
 */

#ifndef FN_HPP
#define FN_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void print_line_file (const std::vector <std::string>&);
bool read_line_file (std::string, std::vector <std::string>&);

#endif