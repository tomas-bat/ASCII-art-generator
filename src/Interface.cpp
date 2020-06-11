/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 30/04/2020
 */

#include <fstream>
#include "Interface.hpp"

using namespace std;

string Interface::get_command() {
    string command;
    if (!(m_Out << "Enter command:" << endl))
        throw runtime_error("Unable to print output.");
    if (!(m_In >> command)) {
        if (m_In.eof())
            return string();
        if (!(m_Out << "Wrong input."))
            throw runtime_error("Unable to print output.");
        else
            return string();
    }
    return command;
}

std::string Interface::get_path(const std::string& str) {
    string path, out_path;
    if (!(m_Out << "Enter path to " << str << ": /"))
        throw runtime_error("Unable to print output.");
    out_path += "/";
    getline(m_In, path);
    getline(m_In, path);
    if (m_In.eof())
        return string();
    if (m_In.fail()) {
        if (!(m_Out << endl << "Wrong input." << endl))
            throw runtime_error("Unable to print output.");
        else
            return string();
    }
    out_path += path;
    return out_path;
}

void Interface::print_help(const string& cmd_name, const std::string& cmd_help) const {
    if (!(m_Out << cmd_name << ": " << cmd_help << endl))
        throw runtime_error("Unable to print output.");
}

Interface& Interface::print(const string& str) {
    if (!(m_Out << str))
        throw runtime_error("Unable to print output.");
    return *this;
}

Interface& Interface::end_line() {
    if (!(m_Out << endl))
        throw runtime_error("Unable to print output.");
    return *this;
}

std::string Interface::get_string() {
    string input;
    if (!(m_In >> input))
        throw runtime_error("Unexpected error when reading a string from input.");
    return input;
}

size_t Interface::get_num() {
    size_t num;
    if (!(m_In >> num))
        throw invalid_argument("Wrong input.");
    return num;
}

Interface& Interface::read_file(const string& path) {
    ifstream file(path);
    if (!file)
        throw runtime_error("Unable to read file: " + path);
    if (!(m_Out << file.rdbuf()))
        throw runtime_error("Unexpected error when printing output.");
    file.close();
    return *this;
}

int Interface::get_int() {
    int num;
    if (!(m_In >> num))
        throw invalid_argument("Wrong input.");
    return num;
}

/**
 * @note This whole function taken from https://gitlab.fit.cvut.cz/bernhdav/pa2-minesweeper/
 */
Interface& Interface::clear_line() {
    m_In.clear();
    m_In.ignore(numeric_limits<streamsize>::max(), '\n');
    return *this;
}
