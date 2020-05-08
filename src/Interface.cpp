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
    if (m_In.eof()) {
        clear_line();
        return command;
    }
    if (!(m_In >> command)) {
        if (!(m_Out << "Wrong input."))
            throw runtime_error("Unable to print output.");
        else
            return string();
    }
    return command;
}

void Interface::print_help(const string& cmd_name, const std::string& cmd_help) const {
    if (!(m_Out << cmd_name << ": " << cmd_help << endl))
        throw runtime_error("Unable to print output.");
}

void Interface::print(const string& str) const {
    if (!(m_Out << str))
        throw runtime_error("Unable to print output.");
}

void Interface::clear_line() const {
    m_In.clear();
    m_In.ignore(numeric_limits<streamsize>::max(), '\n');
}
