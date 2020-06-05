/**
 * @author Tomáš Batěk <batekto2@fit.cvut.cz>
 * @date 30/04/2020
 */

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
    m_Out << endl;
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
    if (!(m_In >> num)) {
        if (!(m_Out << "Wrong input." << endl))
            throw runtime_error("Unable to print output.");

    }
    return num;
}
