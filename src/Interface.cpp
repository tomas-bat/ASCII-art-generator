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

std::string Interface::get_path() {
    string path, out_path;
    if (!(m_Out << "Enter path to folder: /"))
        throw runtime_error("Unable to print output.");
    out_path += "/";
    getline(m_In, path);
    getline(m_In, path);
    if (m_In.fail()) {
        if (!(m_Out << "Wrong input."))
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

size_t Interface::get_num() const {
    size_t num;
    if (!(m_In >> num))
        m_Out << "Wrong input." << endl;
    return num;
}
