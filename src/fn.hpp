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

#include <sys/wait.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

void print_line_file (const std::vector <std::string>&);
bool read_line_file (const std::string&, std::vector <std::string>&);
bool write_line_file (const std::string&, const std::vector <std::string>&);
unsigned int edit_line (int, const std::string&, std::vector <std::string>&);
void filter (std::vector <std::string>&, const std::string&);

#endif