/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 30/04/2020
 *
 * @note Structure inspired by https://gitlab.fit.cvut.cz/bernhdav/pa2-minesweeper/
 */
#pragma once

#include <string>
#include <iostream>

/**
 * Class to represent an interface between a user and the application.
 */
class Interface {
public:
    /**
     * Implicit constructor initializes the input and output with std::cin and std::cout.
     */
    Interface() : m_In(std::cin), m_Out(std::cout) {}

    /**
     * Constructor to initialize the input and output with the given streams.
     *
     * @param in[in,out]    The input stream.
     * @param out[in,out]   The output stream.
     */
    Interface(std::istream& in, std::ostream& out) : m_In(in), m_Out(out) {}

    /**
     * This method tries to read a command from the input stream.
     *
     * @return  The command given in by a user.
     */
    std::string get_command();

    /**
     * This method tries to read a path from the input stream.
     *
     * @return The command given in by a user.
     * @throws std::runtime_error if any error occurs.
     */
    std::string get_path(const std::string& str);

    /**
     * A getter for m_In end of file status.
     *
     * @return True if EOF, otherwise false.
     */
    bool eof() const { return m_In.eof(); }

    /**
     * This method will read a size_t number from the input stream.
     *
     * @return The input number.
     */
    size_t get_num();

    /**
     * This method will read an int number from the input stream.
     *
     * @return The input number.
     * @throws std::invalid_argument if an error occurs.
     */
    int get_int();

    /**
     * This method will read any string from the input stream.
     *
     * @return The input string;
     * @throws std::runtime_error if an error occurs.
     */
    std::string get_string();

    /**
     * This method prints a help for a command into the output.
     *
     * @param cmd_name[in]  Name of the command.
     * @param cmd_help[in]  Help for the command.
     *
     * @throws std::runtime_error if an error occurs.
     */
    void print_help(const std::string& cmd_name, const std::string& cmd_help) const;

    /**
     * Puts end of line to m_Out.
     *
     * @return This interface.
     * @throws std::runtime_error if an error occurs.
     */
    Interface& end_line();

    /**
     * Prints the whole file into the output stream.
     *
     * @param[in] path  Path to the file.
     * @return          This interface.
     * @throws std::runtime_error if an error occurs.
     */
    Interface& read_file(const std::string& path);

    /**
     * This method prints any given string into the output.
     *
     * @param[in] str   The string we want to print out.
     * @throws std::runtime_error if an error occurs.
     */
    Interface& print(const std::string& str);

    /**
     * This method clears the input line in order to avoid infinite looping on wrong input.
     *
     * @note Funtion taken from https://gitlab.fit.cvut.cz/bernhdav/pa2-minesweeper/
     */
    Interface& clear_line();

private:
    /**
     * The input stream associated with the interface.
     */
    std::istream& m_In;

    /**
     * The output stream associated with the interface.
     */
    std::ostream& m_Out;
};

