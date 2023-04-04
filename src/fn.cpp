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


/**
 * @fn filter
 * 
 * @param lines String-containing vector representing a text file.
 * @param user_cmd Command supplied by user.
 * 
 * @brief Executes an external program by forking a child process from parent to modify a single
 *        line of text in the file.
 * 
 * Function creates a child process and launches an external program using Unix system calls. Pipes
 * are setup such that the spawned process reroutes output to the parent process. The spawned
 * process takes in a line of text, executes a terminal command, and sends its output back to the
 * main program.
 * 
 */
void filter (std::vector <std::string>& lines, const std::string& user_cmd)
{
    // Parse and read in line number and Unix command
    int lno = 0;
    char buffer_clear = ' ';
    std::string ucmd = "";

    std::stringstream cmd_parser (user_cmd);

    // Clear out "! " from buffer
    cmd_parser.get (buffer_clear);
    cmd_parser.get (buffer_clear);
    // Get line number specified and covert to an index by decrementing
    cmd_parser >> lno;
    lno--;
    // Clear ' ' from buffer and get rest of command
    cmd_parser.get (buffer_clear);
    std::getline (cmd_parser, ucmd);

    // Create two pipes for communication between parent and child
    int from_parent[2] = {0},
        to_parent[2] = {0},
        p_id = 0;

    if (pipe (from_parent) != 0)
    {
        std::cerr << "Could not create pipe `from_parent`"
                  << "\n\tErrno: " << errno;
    }
    else if (pipe (to_parent) != 0)
    {
        std::cerr << "Could not create pipe `to_parent`"
                  << "\n\tErrno: " << errno;
    }
    // Pipes created successfully, try spawn child process
    else
    {
        p_id = fork();

        // Current process is the parent
        if (p_id > 0)
        {
            close (from_parent[0]); // Close read end of from_parent
            close (to_parent[1]);   // Close write end of to_parent

            // Write lines to write end of from_parent
            FILE* write_child = fdopen (from_parent[1], "w");
            if (write_child == NULL)    // Write file descriptor couldn't be opened
            {
                std::cerr << "Could not open file descriptor for parent to write to child"
                          << "\n\tErrno: " << errno;
                close (from_parent[1]);
                close (to_parent[0]);
                return;
            }
            fprintf (write_child, lines[lno].c_str());
            fclose (write_child);

            // Read line from read end of to_parent
            FILE* read_child = fdopen (to_parent[0], "r");
            if (read_child == NULL)  // Read file descriptor couldn't be opened
            {
                std::cerr << "Could not open file descriptor for parent to read from child"
                          << "\n\tErrno: " << errno;
                close (from_parent[1]);
                close (to_parent[0]);
                return;
            }

            char ln[255];
            if (fgets (ln, 255, read_child) != NULL)
            {
                if (!feof (read_child))
                {
                    if (!ferror (read_child))
                    {
                        lines[lno] = ln;
                        // Some commands have a trailing newline, which isn't needed; pop it off
                        if (lines[lno][lines[lno].size() - 1] == '\n')
                        {
                            lines[lno].pop_back();
                        }
                    }
                    else
                    {
                        std::cerr << "An error occurred while reading from child"
                                  << "\n\tErrno: " << errno;
                    }
                }
            }

            // Close read descriptor and wait for child to terminate
            int w_status = 0;
            fclose (read_child);
            wait (&w_status);
        }
        // Curent process is the child
        else if (p_id == 0)
        {
            // Copy file descriptors to stdin/stdout
            dup2 (from_parent[0], 0);
            dup2 (to_parent[1], 1);

            // Close pipes
            close (to_parent[0]);
            close (to_parent[1]);
            close (from_parent[0]);
            close (from_parent[1]);

            // Setup argv array for new process
            char** child_argv = new char*[4]();
            child_argv[0] = const_cast <char*> ("/bin/sh");
            child_argv[1] = const_cast <char*> ("-c");
            child_argv[2] = const_cast <char*> (ucmd.c_str());
            child_argv[3] = NULL;    // Null-terminate the argv vector

            // Setup PATH variable for child process to parent's value
            std::string temp = "PATH=";
            temp += getenv ("PATH");
            char* env_array[2];
            env_array[0] = const_cast <char*> (temp.c_str());
            env_array[1] = NULL;

            // Execute external command
            execve (child_argv[0], child_argv, env_array);

            // This code shouldn't be executed, unless the external program couldn't be executed
            std::cerr << "Could not execute external program"
                      << "\n\tErrno: " << errno;
            delete[] child_argv;
            exit(1);
        }
        // Something went wrong and a child couldn't be spawned
        else {
            std::cerr << "Could not spawn child process"
                      << "\n\tErrno: " << errno;
        }
    }

    // Close pipes created for parent-child pair
    close (from_parent[0]);
    close (from_parent[1]);
    close (to_parent[0]);
    close (to_parent[1]);    
}
